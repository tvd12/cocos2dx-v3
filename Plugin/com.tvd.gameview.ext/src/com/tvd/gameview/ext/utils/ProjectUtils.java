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

package com.tvd.gameview.ext.utils;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IAdaptable;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.QualifiedName;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.IViewPart;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PlatformUI;

import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.xml.XmlFileBuilder;
import com.tvd.gameview.ext.model.ViewModel;
import com.tvd.gameview.ext.views.BuildingTreeViewer;

public class ProjectUtils {
	
	public static IProject[] getProjects() {
		IProject[] projects = ResourcesPlugin.getWorkspace().getRoot().getProjects();
		
		return projects;
	}
	
	public static IResource extractSelection(ISelection sel) {
	      if (!(sel instanceof IStructuredSelection))
	          return null;
	       IStructuredSelection ss = (IStructuredSelection) sel;
	       Object element = ss.getFirstElement();
	       if (element instanceof IResource)
	          return (IResource) element;
	       if (!(element instanceof IAdaptable))
	          return null;
	       IAdaptable adaptable = (IAdaptable)element;
	       Object adapter = adaptable.getAdapter(IResource.class);
	       
	       return (IResource) adapter;
	   }
	
	public static IResource extractResource(IEditorPart editor) {
	      IEditorInput input = editor.getEditorInput();
	      if (!(input instanceof IFileEditorInput)) {
	         return null;
	      }
	      
	      return ((IFileEditorInput)input).getFile();
	   }
	
	public static IProject getActiveProject() {
		IWorkbenchWindow workbenchWindow = null;
		IWorkbenchPage workbenchPage = null;
		IWorkbench workbench = PlatformUI.getWorkbench();
		if(workbench != null) {
			workbenchWindow = workbench.getActiveWorkbenchWindow();
			IResource resource = extractSelection(workbenchWindow
						.getSelectionService()
						.getSelection());
			if(resource != null) {
				return resource.getProject();
			}
		}
		if(workbenchWindow != null) {
			workbenchPage = workbenchWindow.getActivePage();
		}
		if(workbenchPage != null) {
			IEditorPart editorPart = workbenchPage.getActiveEditor();
			if(editorPart != null) {
				IResource resource = extractResource(editorPart).getProject();
				if(resource != null) {
					return resource.getProject();
				}
			}
		}
		
		return null;
	}
	
	public static IProject getActiveSdkProject() {
		IProject project = getActiveProject();
		if(project != null) {
			if(findSdkProject(project.getName()) != null) {
				return project;
			}
		}
		
		return null;
	}
	
	public static List<IProject> getSdkProjects() {
		IProject[] projects = getProjects();
		List<IProject> result = new ArrayList<IProject>();
		for(IProject project : projects) {
			try {
				if(project.hasNature("com.tvd.gameview.ext.SdkFileNature")) {
					result.add(project);
				}
			} catch (CoreException e) {
				e.printStackTrace();
			}
		}
		
		return result;
	}
	
	public static List<String> getSdkProjectNames() {
		IProject[] projects = getProjects();
		List<String> result = new ArrayList<String>();
		for(IProject project : projects) {
			try {
				String persistentProperty = 
						project.getPersistentProperty(new QualifiedName("tvd", "author"));
				if(persistentProperty != null && persistentProperty.equals("tvd")) {
					result.add(project.getName());
				}
			} catch (CoreException e) {
				e.printStackTrace();
			}
		}
		
		return result;
	}
	
	public static IProject findSdkProject(String pName) {
		List<IProject> projects = getSdkProjects();
		IProject result = null;
		for(IProject project : projects) {
			if(project.getName().equals(pName)) {
				result = project;
			}
		}
		
		return result;
	}
	
	public static List<ViewModel> getViewInProject(IProject project) {
		List<ViewModel> results = new ArrayList<ViewModel>();
		try {
			IFolder xmlFolder = project.getFolder("resources/xml");
			if(xmlFolder.exists()) {
				IResource deviceFolders[] = xmlFolder.members();
				for(int i = 0 ; i < deviceFolders.length ; i++) {
					if(deviceFolders[i].getType() == IResource.FOLDER) {
						IResource viewFiles[] = ((IFolder)deviceFolders[i]).members();
						for(int j = 0 ; j < viewFiles.length ; j++) {
							if(viewFiles[j].getType() == IResource.FILE
									&& viewFiles[j].getName().endsWith(".xml")) {
								boolean contain = false;
								for(int k = 0 ; k < results.size() ; k++) {
									if(results.get(k).getName().equals(viewFiles[j].getName())) {
										contain = true;
									}
								}
								if(!contain) {
									results.add(new ViewModel(viewFiles[j].getName(), false));
								}
							}
						}
					}
					
				}
			}
		} catch (CoreException e) {
			e.printStackTrace();
		}
		
		return results;
	}
	
	/**
	 * after create new xml file, add it to file list 
	 * and update building tree on view part
	 */
	public static void updateBuildingTreeViewPart() {
		System.out.println("updateBuildingTreeViewPart = 1");
		IWorkbench workbench = PlatformUI.getWorkbench();
		if(workbench == null) {
			return;
		}
		System.out.println("updateBuildingTreeViewPart = 2");
		IWorkbenchWindow workbenchWindow = workbench.getActiveWorkbenchWindow();
		if(workbenchWindow == null) {
			return;
		}
		System.out.println("updateBuildingTreeViewPart = 3");
		IWorkbenchPage workbenchPage = workbenchWindow.getActivePage();
		if(workbenchPage == null) {
			return;
		}
		System.out.println("updateBuildingTreeViewPart = 4");
		IViewPart viewPart = workbenchPage
				.findView(BuildingTreeViewer.class.getName());
		if(viewPart == null) {
			return;
		}
		System.out.println("updateBuildingTreeViewPart = 5");
		BuildingTreeViewer buildingTreeView = (BuildingTreeViewer)viewPart;
		buildingTreeView.update();
	}
	
	public static String[] getDevices(IProject project) 
			throws CoreException {
		InputStream inp = 
				project.getFile("src/com/properties/global.properties")
				.getContents();
		String devicesStr = MessageUtils.getString(inp, "devices");
		if(devicesStr == null || devicesStr.equals("")) {
			return null;
		}
		String devices[] = devicesStr.contains(",")
				? devicesStr.split(",") : new String[] {devicesStr};
		for(int i = 0 ; i < devices.length ; i++) {
			devices[i] = devices[i].trim();
		}
		
		return devices;
	}
	
	public static List<String> getDeviceFolderNames(IProject project) {
		List<String> results = new ArrayList<String>();
		IResource xmlResource = project.getFolder("resources/xml");
		if(xmlResource.exists()) {
			try {
				IResource deviceResources[] = ((IFolder)xmlResource).members();
				for(int i = 0 ; i < deviceResources.length ; i++) {
					if(deviceResources[i].getType() == IResource.FOLDER
							&& !deviceResources[i].getName().equals("xsd")) {
						results.add(deviceResources[i].getName());
					}
				}
			} catch (CoreException e) {
				e.printStackTrace();
			}
			
		}
		
		return results;
	}
	
	public static void createXMLFileWithBuilder(IProject project, XmlFileBuilder builder,
			String type, boolean override) {
		try {
			Config.getInstance().setProject(project);
			String devices[] = getDevices(project);
			if(devices == null || devices.length == 0) {
				return;
			}
			for(int i = 0 ; i < devices.length ; i++) {
				
				//version 1.0
//				String xmlContent = builder.buildFor(devices[i]);
//				StringBuilder strBuilder = new StringBuilder("<view ");
//				strBuilder.append("xmlns=\"http://www.tvd.com/tools\"\n");
//				strBuilder.append("\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
//				strBuilder.append("\t\txsi:schemaLocation=\"http://www.tvd.com/tools ../xsd/view.xsd\"\n\t\t");
//				xmlContent = xmlContent.replace("<view ", strBuilder.toString());
//				xmlContent = XmlFormatter.format(xmlContent);
				
				//version 2.0
				String xmlContent = builder.buildXMLViewFor(type, devices[i]);
				IFile newFile = project.getFile(
						new Path(builder.getOutputFilePath()));
				if(newFile.exists()) {
					if(override) {
						newFile.delete(true, null);
					}
				}
				if(!newFile.exists()) {
					//push xml content into stream
					InputStream inputStream = new ByteArrayInputStream(xmlContent.getBytes());
					
					//create new visible file and show to project
					newFile.create(inputStream, true, null);
				}
			}
		} catch(CoreException e) {
			e.printStackTrace();
		}
	}
	
}
