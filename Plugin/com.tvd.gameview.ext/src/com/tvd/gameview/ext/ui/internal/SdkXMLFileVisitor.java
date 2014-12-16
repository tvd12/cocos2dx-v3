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

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IResourceDeltaVisitor;
import org.eclipse.core.resources.IResourceProxy;
import org.eclipse.core.resources.IResourceProxyVisitor;
import org.eclipse.core.runtime.CoreException;

import com.tvd.gameview.ext.utils.ProjectUtils;

public class SdkXMLFileVisitor implements IResourceProxyVisitor,
		IResourceDeltaVisitor {

	@Override
	public boolean visit(IResourceDelta delta) throws CoreException {
//		System.out.println("SdkXMLFileVisitor::visit::delta");
		boolean deleted = (IResourceDelta.REMOVED & delta.getKind()) != 0;
		IResource resource = delta.getResource();
		String name = resource.getName();
		String fullPath = resource.getFullPath().toString();
		IProject project = resource.getProject();
		if(name.endsWith(".xml") && fullPath.contains("resources/xml")) {
			if(deleted) {
				System.out.println("file " + name + " has deleted");
				String devices[] = ProjectUtils.getDevices(project);
				if(devices != null && devices.length > 0) {
					for(String device : devices) {
						IFile file = project.getFile("resources/xml/" + device + "/" + name);
						if(file.exists()) {
							file.delete(true, null);
						}
					}
				}
			}
		}
		return true;
	}
	
	@Override
	public boolean visit(IResourceProxy proxy) throws CoreException {
//		System.out.println("SdkXMLFileVisitor::visit::proxy");
		return true;
	}
	
}
