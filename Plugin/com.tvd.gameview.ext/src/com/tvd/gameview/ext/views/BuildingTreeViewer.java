/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
 * 
 * This file is part of com.tvd.gameview.ext.
 * com.tvd.gameview.ext is free eclipse plug-in: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * com.tvd.gameview.ext is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with com.tvd.gameview.ext.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.tvd.gameview.ext.views;

import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.dialogs.ProgressMonitorDialog;
import org.eclipse.jface.operation.IRunnableWithProgress;
import org.eclipse.jface.resource.FontRegistry;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.ImageRegistry;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.ResourceManager;
import org.eclipse.jface.viewers.DelegatingStyledCellLabelProvider;
import org.eclipse.jface.viewers.DoubleClickEvent;
import org.eclipse.jface.viewers.IDoubleClickListener;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.jface.viewers.TreeViewer;
import org.eclipse.jface.viewers.Viewer;
import org.eclipse.jface.viewers.ViewerFilter;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.part.ViewPart;

import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.View;
import com.tdgc.cocos2dx.popup.creator.utils.NotificationCenter;
import com.tdgc.cocos2dx.popup.creator.xml.XmlFetcher;
import com.tvd.gameview.ext.constants.Constant;
import com.tvd.gameview.ext.model.ProjectChooserHelper;
import com.tvd.gameview.ext.model.ViewModel;
import com.tvd.gameview.ext.utils.ProjectUtils;

/***
 * 
 * @author Dung Ta Van
 *
 * @class BuildingListView: create a view in category Game view
 * Design tree:
 * 	export images
 *	export xib template
 *		export for iphone
 *		export for ipad
 *	export screen template
 *		export for iphone
 *		export for ipad
 *	export positions
 *		declare positions
 *		implement positions
 *	export source code
 *		declare class
 *		implement class
 */
public class BuildingTreeViewer extends ViewPart implements IDoubleClickListener {
	
	public BuildingTreeViewer() {
	}

	@Override
	public void createPartControl(Composite parent) {
		ResourceManager resourceManager = JFaceResources.getResources();
		LocalResourceManager localResourceManager = 
				new LocalResourceManager(resourceManager, parent);
		
		ImageRegistry imageRegistry = new ImageRegistry(localResourceManager);
		URL iconURL = this.getClass().getResource("/icons/3_menuitem.gif");
		imageRegistry.put("iconURL", ImageDescriptor.createFromURL(iconURL));
		FontRegistry fontRegistry = JFaceResources.getFontRegistry();
		
		mTreeViewer = new TreeViewer(parent,
				SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		mTreeViewer.setData("REVERSE", Boolean.TRUE);
		mTreeViewer.setLabelProvider(new DelegatingStyledCellLabelProvider(
				new BuildingListLabelProvider(imageRegistry, fontRegistry)));
		
		mTreeViewer.setContentProvider(new BuildingListContentProvider());
		mTreeViewer.addDoubleClickListener(this);
		
		mTreeViewer.setFilters(new ViewerFilter[] {
			new BuildingTreeViewerFilter()
		});
		
		this.update();
		
		this.getSite().setSelectionProvider(mTreeViewer);
		mSelectionListener = new BuildingListSelectionListener(mTreeViewer, 
				getSite().getPart());
		this.getSite().getWorkbenchWindow().getSelectionService()
			.addSelectionListener(mSelectionListener);
		ResourcesPlugin.getWorkspace()
			.addResourceChangeListener(new SdkFileChangeListener(this));
		
		// Create menu and toolbars.
        createActions();
        createMenu();
        createToolbar();
		
	}
	
	public void createActions() {
		final Shell shell = this.getSite().getShell();
		mAddAction = new Action() {
			@Override
			public void run() {
				ProjectChooserHelper.chooseJavaProject(shell);
			}
		};
		mRemoveAction = new Action() {
			@Override
			public void run() {
				if(mSelectedElement != null) {
					mSelectedElement.setEnable(false);
					mTreeViewer.refresh();
					mSelectedElement = null;
				}
			}
		};
		mRefreshAction = new Action() {
			@Override
			public void run() {
				update();
			}
		};
		mAddAction.setImageDescriptor(getImageDescriptor("/icons/6_plus.gif"));
		mRemoveAction.setImageDescriptor(getImageDescriptor("/icons/5_minus.gif"));
		mRefreshAction.setImageDescriptor(getImageDescriptor("/icons/7_refresh.png"));
		
		mHelpAction = new Action("Help") {
			public void run() {
			}
		};
		
		mTreeViewer.addSelectionChangedListener(new ISelectionChangedListener() {
			
			@Override
			public void selectionChanged(SelectionChangedEvent event) {
				updateActionEnablement();
			}
		});
	}
	
	private void updateActionEnablement() {
        IStructuredSelection sel = 
                (IStructuredSelection)mTreeViewer.getSelection();
        mRemoveAction.setEnabled(sel.size() > 0);
        if(sel.getFirstElement() != null 
        		&& sel.getFirstElement() instanceof BuildingListElement) {
        	mSelectedElement
        		= (BuildingListElement)sel.getFirstElement();
        }
	}
	
	/**
     * Create menu.
     */
    private void createMenu() {
    	IMenuManager mgr = getViewSite().getActionBars().getMenuManager();
    	mgr.add(mHelpAction);
    }
    
    /**
     * Create toolbar.
     */
    private void createToolbar() {
    	IToolBarManager mgr = getViewSite().getActionBars().getToolBarManager();
    	mgr.add(mAddAction);
    	mgr.add(mRemoveAction);
    	mgr.add(mRefreshAction);
    }
	
	 /**
     * Returns the image descriptor with the given relative path.
     */
    private ImageDescriptor getImageDescriptor(String relativePath) {
        return ImageDescriptor.createFromURL(BuildingTreeViewer.class
        		.getResource(relativePath));
    }
	
	@Override
	public void doubleClick(DoubleClickEvent event) {
		Viewer viewer = event.getViewer();
		ISelection sel = viewer.getSelection();
		Object selectedValue = null;
		if(!(sel instanceof IStructuredSelection) || sel.isEmpty()) {
			selectedValue = null;
		} else {
			selectedValue = ((IStructuredSelection)sel).getFirstElement();
			if(selectedValue instanceof BuildingListElement) {
				final BuildingListElement element = (BuildingListElement)selectedValue;
				System.out.println(element.info());
				
				if(element.getFilePath() == null 
						|| element.getFilePath().equals("")) {
					return;
				}
				
				Config.getInstance().setProject(element.getProject());
				final IFile xmlFile = element.getProject().getFile(element.getFilePath());
				final XmlFetcher xmlFetcher = new XmlFetcher();
				final View view = xmlFetcher.fetchView(xmlFile);
//				view.setProject(element.getProject());
				Shell shell = this.getSite().getShell();
				
				if(xmlFetcher.isError()) {
					processErrors(xmlFetcher, shell, element.getFilePath());
					return;
				}
				
				if(view.isExported()) {
					MessageDialog.openError(shell, "View exporting error", 
					view.getClassName() + " has exported, change exported=\"false\" to continue!");
					return;
				}
				
				ProgressMonitorDialog dialog = new ProgressMonitorDialog(shell);
				try {
					dialog.run(true, true, new IRunnableWithProgress() {
						
						@Override
						public void run(IProgressMonitor monitor) 
								throws InvocationTargetException, InterruptedException {
							export(element, view, xmlFetcher, xmlFile);
						}
					});
				} catch (InvocationTargetException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				String error = NotificationCenter.getInstance().getTopError();
				if(error != null) {
					MessageDialog.openError(shell, view.getClassName() + " exporting error", 
							error);
				}
				
			}
		}
	}
	
	private void processErrors(XmlFetcher xmlFetcher, Shell shell, String filePath) {
		int warningCount = xmlFetcher.getWarningCount();
		int fatalErrorCount = xmlFetcher.getFatalErrorCount();
		int nonFatalErrorCount = xmlFetcher.getNonFatalErrorCount();
		if(fatalErrorCount > 0) {
			NotificationCenter.e(fatalErrorCount + " fatal errors detected");
			MessageDialog.openError(shell, "Xml parsing error!", 
					fatalErrorCount + " fatal errors detected in file " + filePath);
		} else if(nonFatalErrorCount > 0) {
			NotificationCenter.e(nonFatalErrorCount + " non-fatal errors detected");
			MessageDialog.openError(shell, "Xml parsing error!", 
					nonFatalErrorCount + " non-fatal errors detected in file " + filePath);
		}
		if(warningCount > 0) {
			NotificationCenter.w(warningCount + " warnings detected");
		}
	}
	
	private void export(BuildingListElement element, View view,
			XmlFetcher xmlFetcher, IFile xmlFile) {
		exportImages(element, view);
		
		declareIdentifiers(element, view);
		implementIdentifiers(element, view);
		exportIdentifiers(element, view);
		
		declarePositions(element, view);
		implementPositionsForDevice(element, view, xmlFetcher, xmlFile);
		
		exportXibTemplateForDevice(element, view);
		exportScreenTemplateForDevice(element, view);
		exportAndroidTemplateForDevice(element, view);
		
		declareClass(element, view);
		implementClass(element, view);
		exportSourceCode(element, view);
	}

	private void exportImages(BuildingListElement element, View view) {
		String device = element.getDevice();
		if(device != null && !device.equals("")) {
			BuildingListElement parentOfDeviceElement = element.getParent();
			if(parentOfDeviceElement.getName()
					.equals(Constant.TreeElement.EXPORT_IMAGES)) {
				System.out.println("Exporting images...");
				view.exportImages();
				System.out.println("Done!");
				System.out.println("===============================================================");
			}
		}
	}
	
	private void declareIdentifiers(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.DECLARE_IDS)) {
			System.out.println("declaring identifiers...");
			view.exportDeclaringImageIds();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void implementIdentifiers(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.IMPLEMENT_IDS)) {
			System.out.println("implementing identifiers...");
			view.exportImplementedImageIds();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void exportIdentifiers(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.EXPORT_IDS)) {
			System.out.println("exporting identifiers...");
			view.exportDeclaringImageIds();
			view.exportImplementedImageIds();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void declarePositions(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.DECLARE_POSITIONS)) {
			System.out.println("declaring positions...");
			view.exportDeclaringPositions();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void implementPositionsForDevice(BuildingListElement element, View view,
			XmlFetcher xmlFetcher, IFile xmlFile) {
		String device = element.getDevice();
		if(device != null && !device.equals("")) {
			BuildingListElement parentOfDeviceElement = element.getParent();
			if(parentOfDeviceElement.getName()
					.equals(Constant.TreeElement.IMPLEMENT_POSITIONS)) {
				System.out.println("Implementing position for " + element.getDevice()
						+ " device...");
				//get position from Interface builder file
				try {
					view.refreshXMLFile();
					view = xmlFetcher.fetchView(xmlFile);
					view.setProject(element.getProject());
				} catch(CoreException e) {
					e.printStackTrace();
				}
				view.exportImplementedPositions(device);
				System.out.println("Done!");
				System.out.println("===============================================================");
			}
		}
	}
	
	private void exportXibTemplateForDevice(BuildingListElement element, View view) {
		String device = element.getDevice();
		if(device != null && !device.equals("")) {
			BuildingListElement parentOfDeviceElement = element.getParent();
			if(parentOfDeviceElement.getName()
					.equals(Constant.TreeElement.EXPORT_XIB_TPL)) {
				System.out.println("Implementing position for " + element.getDevice()
						+ " device...");
				view.exportXibTemplate(element.getDevice(), view.getProject(), false);
				System.out.println();
				System.out.println("Done!");
				System.out.println("===============================================================");
			}
		}
	}
	
	private void exportScreenTemplateForDevice(BuildingListElement element, View view) {
		String device = element.getDevice();
		if(device != null && !device.equals("")) {
			BuildingListElement parentOfDeviceElement = element.getParent();
			if(parentOfDeviceElement.getName()
					.equals(Constant.TreeElement.EXPORT_SCREEN_TPL)) {
				System.out.println("Implementing position for " + element.getDevice()
						+ " device...");
				view.exportScreenTemplate(element.getDevice(), view.getProject());
				System.out.println("Done!");
				System.out.println("===============================================================");
			}
		}
	}
	
	private void exportAndroidTemplateForDevice(BuildingListElement element, View view) {
		String device = element.getDevice();
		if(device != null && !device.equals("")) {
			BuildingListElement parentOfDeviceElement = element.getParent();
			if(parentOfDeviceElement.getName()
					.equals(Constant.TreeElement.EXPORT_ANDROID_TPL)) {
				System.out.println("Implementing position for " + element.getDevice()
						+ " device...");
				//view.exportImplementedPositions(device);
				System.out.println("Comming soon!");
				System.out.println("===============================================================");
			}
		}
	}
	
	private void declareClass(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.DECLARE_CLASS)) {
			System.out.println("Declaring " + view.getClassName()
					+ " class for view...");
			view.exportHeaderCode();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void implementClass(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.IMPLEMENT_CLASS)) {
			System.out.println("Implementing " + view.getClassName()
					+ " class for view...");
			view.exportImplementedCode();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	private void exportSourceCode(BuildingListElement element, View view) {
		if(element.getName().equals(Constant.TreeElement.EXPORT_SRC_CODE)) {
			System.out.println("Exporting " + view.getClassName()
					+ " class for view...");
			view.exportHeaderCode();
			view.exportImplementedCode();
			System.out.println("Done!");
			System.out.println("===============================================================");
		}
	}
	
	@Override
	public void setFocus() {
		
	}

	@Override
	public void dispose() {
		if(mSelectionListener != null) {
			this.getSite().getWorkbenchWindow().getSelectionService()
				.removeSelectionListener(mSelectionListener);
			mSelectionListener = null;
		}
		super.dispose();
	}
	
	private Object[] createInput() {
		String[] strs = {
				"export images", //0 
					//devices
				"export xib template", //1
					//devices
				"export screen template", //2
					//devices
				"export android template", //3
					//devices
				"export identifiers", //4
					//declare identifiers 4.1
					//implement identifiers 4.2
				"export positions", //5
					//"declare positions", 5.1
					//"implement positions", 5.2
						//implement for device 5.2.x
				"export source code", //6 
					//"declare class", //6.1
					//"implement class", //6.2	
		};
		
		List<IProject> sdkProjects = ProjectUtils.getSdkProjects();
		Object input[] = new Object[sdkProjects.size()];
		for(int i = 0 ; i < sdkProjects.size() ; i++) {
			
			//project menuitem in treeview
			BuildingListElement projectElement = 
					new BuildingListElement("export views of " 
							+ sdkProjects.get(i).getName() + " project",
							sdkProjects.get(i));
			
			//get all view in project
			List<ViewModel> viewModels = 
					ProjectUtils.getViewInProject(sdkProjects.get(i)); 
			
			//device array
			String devices[] = null;
			try {
				devices = ProjectUtils.getDevices(sdkProjects.get(i));
			} catch(CoreException e) {
				e.printStackTrace();
			}
			if(devices == null || devices.length == 0) {
				return new Object[] {new BuildingListElement("iphone")};
			}
			
			for(int k = 0 ; k < viewModels.size() ; k++) {
				
				BuildingListElement elements[] = 
						new BuildingListElement[strs.length];
				
			    for(int j = 0 ; j < elements.length ; j++) {
			    	elements[j] = new BuildingListElement(strs[j]);
			    	elements[j].setTag(j);
			    }
			    
			    elements[4].addChild(new BuildingListElement(Constant.TreeElement.DECLARE_IDS));
			    elements[4].addChild(new BuildingListElement(Constant.TreeElement.IMPLEMENT_IDS));
			    elements[5].addChild(new BuildingListElement("declare positions"));
			    elements[5].addChild(new BuildingListElement("implement positions"));
			    elements[6].addChild(new BuildingListElement("declare class"));
			    elements[6].addChild(new BuildingListElement("implement class"));
				
				if(!viewModels.get(k).isDone()) {
					String name = "export building list of " + 
							viewModels.get(k).getName() + " view";
					for(int j = 0 ; j < devices.length ; j++) {
				    	String device = devices[j].trim();
				    	BuildingListElement deviceElement = 
				    			new BuildingListElement("export for " + device, device);
				    	String filePath = "resources/xml/" + device
				    			+ "/" + viewModels.get(k).getName();
				    	deviceElement.setFilePath(filePath);
				    	elements[0].addChild(deviceElement.copy());
				    	elements[1].addChild(deviceElement.copy());
				    	elements[2].addChild(deviceElement.copy());
				    	elements[3].addChild(deviceElement.copy());
				    	
				    	BuildingListElement implementForDeviceElement
				    			= new BuildingListElement("implement for " + device, device);
				    	implementForDeviceElement.setFilePath(filePath);
				    	elements[5].getChildAt(1).addChild(implementForDeviceElement);
				    }
					BuildingListElement viewElement = new BuildingListElement(name, elements);
					viewElement.setFilePath("resources/xml/" + devices[0]
				    			+ "/" + viewModels.get(k).getName());
					projectElement.addChild(viewElement);
					viewElement.update();
				}
			}
			input[i] = projectElement;
		}
		
		return input;
	}
	
	public void update() {
		mTreeViewer.setInput(createInput());
		mTreeViewer.refresh();
	}
	
	public TreeViewer getTreeViewer() {
		return mTreeViewer;
	}
	
	public static final String ID = BuildingTreeViewer.class.getName();
	
	private ISelectionListener mSelectionListener;
	private TreeViewer mTreeViewer;
	private BuildingListElement mSelectedElement;
	
	private Action mRemoveAction;
	private Action mAddAction;
	private Action mRefreshAction;
	private Action mHelpAction;
}
