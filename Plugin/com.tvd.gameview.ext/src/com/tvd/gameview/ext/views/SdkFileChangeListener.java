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

import java.io.InputStream;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceChangeEvent;
import org.eclipse.core.resources.IResourceChangeListener;
import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IResourceDeltaVisitor;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.ui.part.ViewPart;

import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tvd.gameview.ext.utils.ProjectUtils;

public class SdkFileChangeListener implements IResourceChangeListener {

	public SdkFileChangeListener(ViewPart viewPart) {
		mViewPart = viewPart;
	}
	
	@Override
	public void resourceChanged(IResourceChangeEvent event) {
		if(event.getSource() != null) {
			IResource res = event.getResource();
			try {
		         switch (event.getType()) {
		            case IResourceChangeEvent.PRE_CLOSE:
		               System.out.print("Project ");
		               System.out.print(res.getFullPath());
		               System.out.println(" is about to close.");
		               break;
		            case IResourceChangeEvent.PRE_DELETE:
		               System.out.print("Project ");
		               System.out.print(res.getFullPath());
		               System.out.println(" is about to be deleted.");
		               break;
		            case IResourceChangeEvent.POST_CHANGE:
		               System.out.println("Resources have changed.");
		               event.getDelta().accept(new SdkResourceDeltaVisitor());
		               break;
		            case IResourceChangeEvent.PRE_BUILD:
		               System.out.println("Build about to run.");
		               event.getDelta().accept(new SdkResourceDeltaVisitor());
		               break;
		            case IResourceChangeEvent.POST_BUILD:
		               System.out.println("Build complete.");
		               event.getDelta().accept(new SdkResourceDeltaVisitor());
		               break;
		         }
			} catch(CoreException e) {
				e.printStackTrace();
			}
		}
	}
	
	private class SdkResourceDeltaVisitor implements IResourceDeltaVisitor {
	      public boolean visit(IResourceDelta delta) {
	    	  IResource res = delta.getResource();
              String fullPath = res.getFullPath().toString();
              if(fullPath == null 
           		   || fullPath.equals("")
           		   || fullPath.trim().equals("/")) {
           	   return true;
              }
	         switch (delta.getKind()) {
	            case IResourceDelta.ADDED:
	               System.out.print("Resource ");
	               System.out.print(res.getFullPath());
	               System.out.println(" was added.");
	               if(fullPath.contains("resources/xml") && 
	            		   res.getType() == IResource.FOLDER) {
	            	   //copyXMLFilesToDevicesFolder(fullPath);
	               }
	               break;
	            case IResourceDelta.REMOVED:
	               System.out.print("Resource ");
	               System.out.print(res.getFullPath());
	               System.out.println(" was removed.");
	               if((fullPath.contains("resources/xml")
	            		   && res.getName().endsWith(".xml"))) {
	            	   updateTreeViewer();
	               }
	               if(fullPath.lastIndexOf('/') == 0
	            		   || !fullPath.contains("/")) {
	            	   updateTreeViewer();
	               }
	               break;
	            case IResourceDelta.CHANGED:
	               System.out.print("Resource ");
	               System.out.print(res.getFullPath());
	               System.out.println(" has changed.");
	               String fullPathStr = res.getFullPath().toString();
	               if(res.getName().equals("global.properties")) {
	            	   updateTreeViewer();
	               } else if(fullPathStr
	            		   .endsWith("src/com/config/default.properties")) {
	            	   Config config = Config.getInstance();
	            	   if(config.getProject() == null) {
	            		   config.setProject(res.getProject());
	            	   } else {
	            		   config.reloadConfigs();
	            	   }
	               } else if(fullPathStr.contains("resources/xml/")
	            		   && fullPathStr.endsWith(".xml")) {
	            	   
	               }
	               break;
	         }
	         return true; // visit the children
	      }
	}
	
	private void updateTreeViewer() {
		if(mViewPart instanceof BuildingTreeViewer) {
 		   final BuildingTreeViewer tree = (BuildingTreeViewer)mViewPart;
 		   tree.getTreeViewer().getControl().getDisplay().asyncExec(new Runnable() {
				
				@Override
				public void run() {
					tree.update();
				}
			});
 	   }
	}
	
	@SuppressWarnings("unused")
	private void copyXMLFilesToDevicesFolder(String fullPath) {
		String projectName = fullPath.substring(1);
  	   	projectName = projectName.substring(0, projectName.indexOf('/'));
  	   	IProject project = ProjectUtils.findSdkProject(projectName);
  	   	if(project != null) {
			try {
				String devices[] = ProjectUtils.getDevices(project);
				if(devices == null || devices.length == 0) {
					return;
				}
				String folderPath = "resources/xml/" + devices[0];
		  		IFolder folder = project.getFolder(folderPath);
		  		IResource[] members = folder.members();
		  		String newFolder = fullPath.substring(fullPath.lastIndexOf("resources/xml"));
		  		
				for(int i = 0 ; i < members.length ; i++) {
					String fileName = members[i].getName();
					if(members[i].getType() == IResource.FILE
							&& fileName.endsWith(".xml")) {
						String newFilePath = newFolder + "/" + fileName;
						IFile newFile = project.getFile(newFilePath);
						InputStream inputStream = project.getFile(folderPath + "/" + fileName)
								.getContents();
						if(!newFile.exists()) {
							newFile.create(inputStream, true, null);
						}
					}
      		}
      		   
			} catch (CoreException e) {
				e.printStackTrace();
			}
  	   }
	}
	
	private ViewPart mViewPart;
	
}
