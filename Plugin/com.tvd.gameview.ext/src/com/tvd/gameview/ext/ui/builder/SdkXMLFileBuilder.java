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

package com.tvd.gameview.ext.ui.builder;

import java.util.Map;

import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IncrementalProjectBuilder;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;

import com.tvd.gameview.ext.ui.internal.SdkXMLFileVisitor;

public class SdkXMLFileBuilder extends IncrementalProjectBuilder {

	@Override
	protected IProject[] build(int kind, Map<String, String> args,
			IProgressMonitor monitor) throws CoreException {
		System.out.println("SdkFileBuilder::build kind = " + kind);
		if(kind == FULL_BUILD) {
			fullBuild(getProject(), monitor);
		} else {
			incrementalBuild(getProject(), 
					monitor, getDelta(getProject()));
		}
		return null;
	}
	
	private void incrementalBuild(IProject project, 
			IProgressMonitor monitor, IResourceDelta delta) throws CoreException {
		System.out.println("SdkFileBuilder::incrementalBuild kind = " + delta);
		if(delta == null) {
			fullBuild(project, monitor);
		} else {
			delta.accept(new SdkXMLFileVisitor());
		}
	}
	
	private void fullBuild(IProject project, IProgressMonitor monitor) 
			throws CoreException {
		project.accept(new SdkXMLFileVisitor(), IResource.NONE);
	}
	
	public static final String ID = "com.tvd.gameview.ext.SdkXMLFileBuilder";
}
