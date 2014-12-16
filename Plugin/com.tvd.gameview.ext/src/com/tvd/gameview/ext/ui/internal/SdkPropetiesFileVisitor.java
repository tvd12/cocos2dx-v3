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

package com.tvd.gameview.ext.ui.internal;

import java.io.InputStream;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IMarker;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IResourceDeltaVisitor;
import org.eclipse.core.resources.IResourceProxy;
import org.eclipse.core.resources.IResourceProxyVisitor;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.ui.statushandlers.StatusManager;

import com.tdgc.cocos2dx.popup.creator.file.FileUtils;
import com.tdgc.cocos2dx.popup.creator.utils.NotificationCenter;
import com.tvd.gameview.ext.GameViewSdk;
import com.tvd.gameview.ext.utils.MessageUtils;
import com.tvd.gameview.ext.utils.ProjectUtils;

public class SdkPropetiesFileVisitor implements IResourceProxyVisitor,
	IResourceDeltaVisitor {	

	@Override
	public boolean visit(IResourceDelta delta) throws CoreException {
//		System.out.println("SdkPropetiesFileVisitor::visit::delta.getKind = " + delta.getKind());
		boolean deleted = (IResourceDelta.REMOVED & delta.getKind()) != 0;
		boolean changed = (IResourceDelta.CHANGED & delta.getKind()) != 0;
		IResource resource = delta.getResource();
		String name = resource.getName();
		if(name.endsWith(".properties")) {
			if(deleted) {
				System.out.println("file " + name + " has deleted");
			} else if(changed) {
				processPropertiesResource(resource);
			}
		} 
		return true;
	}
	
	@Override
	public boolean visit(IResourceProxy proxy) throws CoreException {
//		System.out.println("SdkPropetiesFileVisitor::visit::proxy");
		String name = proxy.getName();
		if(name != null && name.endsWith(""))
			processPropertiesResource(proxy.requestResource());
		return true;
	}
	
	private void processPropertiesResource(IResource resource) 
			throws CoreException {
		if(resource instanceof IFile && resource.exists()) {
			try {
				IFile file = (IFile)resource;
				String name = file.getName();
				IProject project = resource.getProject();
				if(name.equals("global.properties")) {
					processGlobalPropertiesResource(project);
				} 
				if(name.endsWith(".properties")) {
					processPropertiesFormat(resource);
				}
			} catch (CoreException e) {
				throw new CoreException(new Status(Status.ERROR,
						GameViewSdk.PLUGIN_ID, "Failed to generate resource", e));
			}
		}
	}
	
	private void processPropertiesFormat(IResource resource) 
			throws CoreException {
		String fileContent = new FileUtils().readFromFile((IFile)resource);
		String lineContents[] = fileContent.split("\n");
		boolean keyValueError = false;
		boolean formatError = false;
		String error = "Error in file " + resource.getName() 
				+ ". Invalid format at line numbers ";
		for(int i = 0 ; i < lineContents.length ; i++) {
			String lineContent = lineContents[i].trim();
			if(lineContent.length() == 0) {
				continue;
			}
			int k = i + 1;
			if(lineContent.contains("=")) {
				String keyValue[] = lineContent.split("=");
				if(keyValue.length < 2) {
					error += k + ", ";
					keyValueError = true;
					makeErrorMarker(resource, "Invalid format key/value", 
							k, lineContent, "KeyValueMarker");
					NotificationCenter.e("Invalid format key/value");
				}
			} 
			else {
				if(lineContent.charAt(0) != '#') {
					error += k + ", ";
					formatError = true;
					makeErrorMarker(resource, "Invalid format content, add '#' at begin", 
							k, lineContent, "FormatMarker");
					NotificationCenter.e("Invalid format content, add '#' at begin");
				}
			}
		}
		if(keyValueError || formatError) {
			error += "use '#' at begin of line or fill value for key";
			StatusManager statusManager = StatusManager.getManager();
			Status status = new Status(IStatus.ERROR, 
				GameViewSdk.PLUGIN_ID, error);
			statusManager.handle(status, StatusManager.LOG);
		} 
		
		if(!keyValueError) {
			resource.deleteMarkers("com.tvd.gameview.ext.ui.KeyValueMarker", 
					true, IResource.DEPTH_INFINITE);
		} 
		if(!formatError) {
			NotificationCenter.i("Delete markers with id com.tvd.gameview.ext.ui.FormatMarker");
			resource.deleteMarkers("com.tvd.gameview.ext.ui.FormatMarker", 
					true, IResource.DEPTH_INFINITE);
		}
	}
	
	private void makeErrorMarker(IResource resource, String message, 
			int lineNumber, String lineContent, String type) 
					throws CoreException{
		IMarker marker = resource.createMarker(
				"com.tvd.gameview.ext.ui." + type);
		marker.setAttribute(IMarker.SOURCE_ID, resource.getLocalTimeStamp());
		marker.setAttribute(IMarker.SEVERITY, IMarker.SEVERITY_ERROR);
		marker.setAttribute(IMarker.MESSAGE, message);
		marker.setAttribute(IMarker.LINE_NUMBER, lineNumber);
		marker.setAttribute(IMarker.CHAR_START, lineContent);
		marker.setAttribute(IMarker.CHAR_END, lineContent);
	}
	
	private void processGlobalPropertiesResource(IProject project) 
			throws CoreException {
		InputStream inputStream = 
				project.getFile("src/com/properties/global.properties")
				.getContents();
		String deviceStr = MessageUtils.getString(inputStream, "devices");
		
		//if have no device, do nothing
		if(deviceStr == null || deviceStr.equals("")) {
			return;
		}
		
		//get divces
		String devices[] = (deviceStr.contains(",")) 
				? deviceStr.split(",") : new String[] {deviceStr};
				
		//create new devices if have any device added
		createNewDevices(project, devices);
		
	}
	
	private void createNewDevices(IProject project, String devices[]) 
			throws CoreException {
		for(int i = 0 ; i < devices.length ; i++) {
			String device = devices[i].trim();
			IFolder xml = project.getFolder("resources/xml/" + device);
			if(!xml.exists()) {
				xml.create(true, true, null);
			}
			IFolder xib = project.getFolder("resources/xib/" + device);
			if(!xib.exists()) {
				xib.create(true, true, null);
			}
			IFolder screen = project.getFolder("resources/screen/" + device);
			if(!screen.exists()) {
				screen.create(true, true, null);
			}
			IFolder android = project.getFolder("resources/android/" + device);
			if(!android.exists()) {
				android.create(true, true, null);
			}
		}
		//deleted device if have any device deleted
		deleteDevices(project, devices);
		
	}
	
	private void deleteDevices(IProject project, String devices[]) 
			throws CoreException {
		
		List<String> deviceFolderNames = ProjectUtils.getDeviceFolderNames(project);
		
		for(int i = 0 ; i < deviceFolderNames.size() ; i++) {
			String savedDevice = deviceFolderNames.get(i);
			boolean deleted = true;
			for(int k = 0 ; k < devices.length ; k++) {
				if(savedDevice.equals(devices[k].trim())) {
					deleted = false;
				}
			}
			if(deleted) {
				IFolder xml = project.getFolder("resources/xml/" + savedDevice);
				if(xml.exists()) {
					xml.delete(true, null);
				}
				IFolder xib = project.getFolder("resources/xib/" + savedDevice);
				if(xib.exists()) {
					xib.delete(true, null);
				}
				IFolder screen = project.getFolder("resources/screen/" + savedDevice);
				if(screen.exists()) {
					screen.delete(true, null);
				}
				IFolder android = project.getFolder("resources/android/" + savedDevice);
				if(android.exists()) {
					android.delete(true, null);
				}
			}
		}
	}
}
