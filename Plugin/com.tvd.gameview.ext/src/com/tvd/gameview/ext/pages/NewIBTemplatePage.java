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

package com.tvd.gameview.ext.pages;

import java.util.Iterator;
import java.util.List;

import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IProject;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;

import com.tvd.gameview.ext.constants.Constant;
import com.tvd.gameview.ext.model.ProjectChooserHelper;
import com.tvd.gameview.ext.model.ProjectChooserHelper.ProjectCombo;
import com.tvd.gameview.ext.utils.ProjectUtils;
import com.tvd.gameview.ext.value.validate.Validator;

public class NewIBTemplatePage extends WizardPage {

	public NewIBTemplatePage(String pageName, ISelection selection) {
		super(pageName);
		this.setPageComplete(false);
		this.mSelection = selection;
	}
	
	@Override
	public void dispose() {
		super.dispose();
	}

	@Override
	public void createControl(Composite parent) {
		Composite composite = new Composite(parent, SWT.NULL);
		composite.setFont(parent.getFont());
		
		this.initializeDialogUnits(parent);
		
		composite.setLayout(new GridLayout(2, false));
		composite.setLayoutData(new GridData(GridData.FILL_BOTH));
		
		this.createSizeGroup(composite);
		this.createOrientationGroup(composite);
		this.createSeparator(composite);
		this.createInterfaceBuildersGroup(composite);
		this.createDeviceFolderGroup(composite);
		this.createSeparator(composite);
		this.createProjectsGroup(composite);
		this.mDeviceFolderCommbo.refresh();
		
		this.setErrorMessage(null);
		this.setMessage(null);
		this.setControl(composite);
		
		this.setPageComplete(false);
	}
	
	protected boolean validatePage() {
		boolean valid = true;
		String message = null;
		String sizeText = mSizeText.getText();
		if(sizeText == null || sizeText.equals("")) {
			valid = false;
			message = "Size can not null";
		} 
		else if(!Validator.isValidDoubleValueString(sizeText)) {
			valid = false;
			message = "Invalid size, change to another (i.e 320, 480)";
		} 
		else if(mOrientationCombo.getSelectionIndex() == 0) {
			valid = false;
			message = "Select a device orientation, plz!";
		}
		else if(mInterfaceBuilderCombo.getSelectionIndex() == 0) {
			valid = false;
			message = "Select a interface builder, plz!";
		}
		else if(mDeviceFolderCommbo.getSelectionIndex() == 0) {
			valid = false;
			message = "Select a device folder, plz!";
		}
		else if(mProjectCombo.getSelectionIndex() == 0) {
			valid = false;
			message = "Select a project, plz!";
		}
		setErrorMessage(message);
		setPageComplete(valid);
		return valid;
	}
	
	private void createProjectsGroup(Composite parent) {
        String tooltip = "The Interface Builder template file will be created.";
        Label label = new Label(parent, SWT.NONE);
        label.setText("Project: ");
        label.setToolTipText(tooltip);
        
        mProjectCombo = new GameViewProjectCombo(parent);
    }
	
	private void createInterfaceBuildersGroup(Composite parent) {
		String tooltip = "Interface Builder for view.";
        Label label = new Label(parent, SWT.NONE);
        label.setText("Interface builder: ");
        label.setToolTipText(tooltip);
        this.mInterfaceBuilderCombo = new InterfaceBuilderCombo(parent);
	}
	
	private void createOrientationGroup(Composite parent) {
		String tooltip = "Device orientation.";
        Label label = new Label(parent, SWT.NONE);
        label.setText("Device orientation: ");
        label.setToolTipText(tooltip);
        this.mOrientationCombo = new OrientationBuilderCombo(parent);
	}
	
	private void createDeviceFolderGroup(Composite parent) {
		String tooltip = "Device folder.";
        Label label = new Label(parent, SWT.NONE);
        label.setText("Device folder: ");
        label.setToolTipText(tooltip);
        this.mDeviceFolderCommbo = new DeviceFolderCombo(parent);
	}
	
	private void createSizeGroup(Composite parent) {
		Label label = new Label(parent, SWT.NONE);
		label.setText("Device size: ");
		label.setToolTipText("Set size for device");
		
		this.mSizeText = new Text(parent, SWT.BORDER | SWT.FILL);
		this.mSizeText.setText("320, 480");
		this.mSizeText.setToolTipText("i.e 320, 480");
		
		GridData gd = new GridData(GridData.GRAB_HORIZONTAL);
        gd.horizontalAlignment = SWT.FILL;
		this.mSizeText.setLayoutData(gd);
		
		this.mSizeText.addModifyListener(new ModifyListener() {
			
			@Override
			public void modifyText(ModifyEvent e) {
				validatePage();
			}
		});
	}
	
	@SuppressWarnings("unused")
	private void emptyCell(Composite parent) {
        new Label(parent, SWT.NONE);
    }

	private class GameViewProjectCombo extends ProjectChooserHelper.ProjectCombo {

		public GameViewProjectCombo(Composite parent) {
			super(parent);
		}
		
		@Override
		public void widgetSelected(SelectionEvent e) {
			super.widgetSelected(e);
			mDeviceFolderCommbo.refresh();
			validatePage();
		}
	}
	
	private void createSeparator(Composite composite) {
		Label rootSeparator = new Label(composite, SWT.SEPARATOR | SWT.HORIZONTAL);
        GridData gd = new GridData(GridData.GRAB_HORIZONTAL);
        gd.horizontalAlignment = SWT.FILL;
        gd.horizontalSpan = 3;
        rootSeparator.setLayoutData(gd);
	}
	
	private class InterfaceBuilderCombo extends Combo 
		implements SelectionListener {

		public InterfaceBuilderCombo(Composite parent, int style) {
			super(parent, style);
		}
		
		public InterfaceBuilderCombo(Composite parent) {
			super(parent, SWT.BORDER | SWT.FLAT | SWT.READ_ONLY);
			String items[] = {
				"--- Choose interface builder ---",
				"Xib - Xcode Interface Builder",
				"Screen - WireframeSketcher Wireframing Screen",
				"Android - Android Development Layout"
			};
			this.setItems(items);
			this.select(0);
			
			this.addSelectionListener(this);
		}

		@Override
		public void widgetSelected(SelectionEvent e) {
			switch (getSelectionIndex()) {
			case 1:
				mInterfaceBuilder = "Xib";
				break;
			case 2:
				mInterfaceBuilder = "Screen";
				break;
			case 3:
				mInterfaceBuilder = "Android";
				break;

			default:
				break;
			}
			validatePage();
		}

		@Override
		public void widgetDefaultSelected(SelectionEvent e) {
		}
		
		@Override
        protected void checkSubclass() {
            // Disable the check that prevents subclassing of SWT components
        }
		
		public String getInterfaceBuilder() {
			return mInterfaceBuilder;
		}
		
		private String mInterfaceBuilder;
		
	}
	
	private class OrientationBuilderCombo extends Combo 
		implements SelectionListener {

		public OrientationBuilderCombo(Composite parent, int style) {
			super(parent, style);
		}
		
		public OrientationBuilderCombo(Composite parent) {
			super(parent, SWT.BORDER | SWT.FLAT | SWT.READ_ONLY);
			String items[] = {
				"--- Choose device orientation ---",
				"Portrait",
				"Landscape"
			};
			this.setItems(items);
			this.select(0);
			
			this.addSelectionListener(this);
		}
	
		@Override
		public void widgetSelected(SelectionEvent e) {
			switch (getSelectionIndex()) {
			case 1:
				mOrientation = Constant.Orientation.PORTRAIT;
				break;
			case 2:
				mOrientation = Constant.Orientation.LANDSCAPE;
			default:
				break;
			}
			validatePage();
		}
	
		@Override
		public void widgetDefaultSelected(SelectionEvent e) {
		}
		
		@Override
	    protected void checkSubclass() {
	        // Disable the check that prevents subclassing of SWT components
	    }
		
		public int getOrientation() {
			return mOrientation;
		}
		
		private int mOrientation;
	
	}
	
	private class DeviceFolderCombo extends Combo 
		implements SelectionListener {

		public DeviceFolderCombo(Composite parent, int style) {
			super(parent, style);
		}
		
		public DeviceFolderCombo(Composite parent) {
			super(parent, SWT.BORDER | SWT.FLAT | SWT.READ_ONLY);
			String items[] = {
				"--- Choose device folder ---",
			};
			this.setItems(items);
			this.select(0);
			this.refresh();
			this.addSelectionListener(this);
		}
	
		@Override
		public void widgetSelected(SelectionEvent e) {
			validatePage();
		}

		@Override
		public void widgetDefaultSelected(SelectionEvent e) {
			
		}
		
		@Override
	    protected void checkSubclass() {
	        // Disable the check that prevents subclassing of SWT components
	    }
		
		private void refresh() {
			IProject project = getSelectedProject();
			if(project != null) {
				List<String> deviceFolders = 
						ProjectUtils.getDeviceFolderNames(project);
				String items[] = new String[deviceFolders.size() + 1];
				items[0] = "--- Choose device folder ---";
				IFolder folder = getSelectedFolder();
				int selectionIndex = 0;
				for(int i = 0 ; i < deviceFolders.size() ; i++) {
					items[i + 1] = deviceFolders.get(i);
					if(folder != null && folder.getProject() == project
							&& folder.getName().equals(items[i + 1])) {
						selectionIndex = i + 1;
					}
				}
				this.setItems(items);
				this.select(selectionIndex);
			}
		}
		
		private IFolder getSelectedFolder() {
			if(mSelection instanceof IStructuredSelection) {
				Iterator<?> it = ((IStructuredSelection)mSelection).iterator();
				while(it.hasNext()) {
					Object object = (Object)it.next();
					if(object instanceof IFolder) {
						return (IFolder)object;
					}
				}
			}
			
			return null;
		}
		
		public String getDeviceFolder() {
			return getItem(getSelectionIndex());
		}
		
	}
	
	public String getInterfaceBuilder() {
		return mInterfaceBuilderCombo
				.getInterfaceBuilder();
	}
	
	public IProject getSelectedProject() {
		if(mProjectCombo == null) {
			return null;
		}
		return mProjectCombo
				.getSelectedProject();
	}
	
	public int getDeviceOrientation() {
		return mOrientationCombo.getOrientation();
	}
	
	public String getSize() {
		return mSizeText.getText().trim();
	}
	
	public String getWidth() {
		return getSize().split(",")[0].trim();
	}
	
	public String getHeight() {
		return getSize().split(",")[1].trim();
	}
	
	public String getDeviceFolder() {
		return mDeviceFolderCommbo.getDeviceFolder();
	}
	
	private ProjectCombo mProjectCombo;
	private InterfaceBuilderCombo mInterfaceBuilderCombo;
	private OrientationBuilderCombo mOrientationCombo;
	private DeviceFolderCombo mDeviceFolderCommbo;
	
	private ISelection mSelection;
	
	private Text mSizeText;
	
}
