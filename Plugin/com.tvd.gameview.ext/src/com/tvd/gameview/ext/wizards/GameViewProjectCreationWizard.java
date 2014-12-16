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

package com.tvd.gameview.ext.wizards;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IProjectDescription;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IConfigurationElement;
import org.eclipse.core.runtime.IExecutableExtension;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.NullProgressMonitor;
import org.eclipse.core.runtime.QualifiedName;
import org.eclipse.core.runtime.SubProgressMonitor;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.actions.WorkspaceModifyOperation;
import org.eclipse.ui.dialogs.WizardNewProjectCreationPage;
import org.eclipse.ui.wizards.newresource.BasicNewProjectResourceWizard;
import org.eclipse.ui.wizards.newresource.BasicNewResourceWizard;
import org.eclipse.jdt.core.IClasspathEntry;
import org.eclipse.jdt.core.IJavaProject;
import org.eclipse.jdt.core.JavaCore;
import org.eclipse.jdt.launching.JavaRuntime;
import org.eclipse.jdt.ui.wizards.JavaCapabilityConfigurationPage;

import com.tvd.gameview.ext.constants.Constant;
import com.tvd.gameview.ext.constants.Key;
import com.tvd.gameview.ext.pages.GameViewMainPage;
import com.tvd.gameview.ext.support.CustomProjectSupport;
import com.tvd.gameview.ext.ui.natures.SdkFileNature;
import com.tvd.gameview.ext.utils.MessageUtils;

public class GameViewProjectCreationWizard extends Wizard 
		implements IExecutableExtension, INewWizard {

	private WizardNewProjectCreationPage mMainPage;
	private JavaCapabilityConfigurationPage mJavaPage;
	
	private IConfigurationElement mConfigElement;

	private IWorkbench mWorkbench;
	public GameViewProjectCreationWizard() {
		setWindowTitle("New Game View Project");
	}

	/* (non-Javadoc)
	 * @see org.eclipse.core.runtime.IExecutableExtension#setInitializationData(org.eclipse.core.runtime.IConfigurationElement, java.lang.String, java.lang.Object)
	 */
	public void setInitializationData(IConfigurationElement cfig, 
			String propertyName, Object data) {
		//  The config element will be used in <code>finishPage to set the result perspective.
		mConfigElement= cfig;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.IWorkbenchWizard#init(org.eclipse.ui.IWorkbench, org.eclipse.jface.viewers.IStructuredSelection)
	 */
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		mWorkbench= workbench; 
	}

	/* (non-Javadoc)
	 * @see Wizard#addPages
	 */	
	public void addPages() {
		super.addPages();
		mMainPage= new GameViewMainPage("game_view_main_page");
		mMainPage.setTitle(MessageUtils.getString("game_view_main_page_title"));
		mMainPage.setDescription(MessageUtils.getString(
				"game_view_main_page_description"));
		
		// the main page
		addPage(mMainPage);
		
		// the Java build path configuration page
		mJavaPage= new JavaCapabilityConfigurationPage() {
			public void setVisible(boolean visible) {
				// need to override to react to changes on first page
				updatePage();
				super.setVisible(visible);
			}
		};
		addPage(mJavaPage);
		
		//	TODO: add your pages here
	}
	
	private void updatePage() {
		IJavaProject jproject= JavaCore.create(mMainPage.getProjectHandle());
		if (!jproject.equals(mJavaPage.getJavaProject())) {
			IClasspathEntry[] buildPath= {
				JavaCore.newSourceEntry(jproject.getPath().append("src")),
				JavaRuntime.getDefaultJREContainerEntry()
			};
			IPath outputLocation= jproject.getPath().append("bin");		
			mJavaPage.init(jproject, outputLocation, buildPath, false);	
			
			String paths[] = {"src/com/template", "src/com/properties",
					"src/com/config",
					"resources/screen/iphone", "resources/screen/ipadhd",
					"resources/xib/iphone", "resources/xib/ipadhd",
					"resources/xml/iphone", "resources/xml/ipadhd",
					"resources/android/iphone", "resources/android/ipadhd",
					"resources/xml/xsd"
					};
			CustomProjectSupport.createFolders(jproject, paths);
			
			GameViewMainPage mainPage = (GameViewMainPage)mMainPage;
//			CustomProjectSupport.copySourceCodeFiles(mainPage
//					.getGameProjectLocation().getStringValue());
			
			StringBuilder globalContent = new StringBuilder(Key.GAME_PROJECT_LOCATION + " = "
					+ mainPage.getGameProjectLocation().getStringValue());
			globalContent.append("\ndevices = iphone, ipadhd");
			CustomProjectSupport.writeFile(jproject, Constant.Folder.PROPERTIES, 
					Constant.File.GLOBAL, globalContent.toString());
		
			try {
				jproject.getProject().setPersistentProperty(
						new QualifiedName("tvd", "author"), "tvd");
				jproject.getProject().setPersistentProperty(
						new QualifiedName("tvd", "devices"), "iphone, ipadhd");
				
				this.addProjectNature(jproject.getProject(), SdkFileNature.ID);
			} catch (CoreException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void finishPage(IProgressMonitor monitor) 
			throws InterruptedException, CoreException {
		if (monitor == null) {
			monitor= new NullProgressMonitor();
		}
		try {		
			monitor.beginTask(MessageUtils.getString("create_project_task"), 3); // 3 steps

			IProject project= mMainPage.getProjectHandle();
			IPath locationPath= mMainPage.getLocationPath();
		
			// create the project
			IProjectDescription desc= project.getWorkspace()
					.newProjectDescription(project.getName());
			if (!mMainPage.useDefaults()) {
				desc.setLocation(locationPath);
			}
			project.create(desc, new SubProgressMonitor(monitor, 1));
			project.open(new SubProgressMonitor(monitor, 1));
			
			updatePage();
			mJavaPage.configureJavaProject(new SubProgressMonitor(monitor, 1));
			// TODO: configure your page / nature
	
			// change to the perspective specified in the plugin.xml		
			BasicNewProjectResourceWizard.updatePerspective(mConfigElement);
			BasicNewResourceWizard.selectAndReveal(project, 
					mWorkbench.getActiveWorkbenchWindow());
			
		} finally {
			monitor.done();
		}
	}

	/* (non-Javadoc)
	 * @see Wizard#performFinish
	 */		
	public boolean performFinish() {
		WorkspaceModifyOperation op= new WorkspaceModifyOperation() {
			protected void execute(IProgressMonitor monitor) throws CoreException, 
					InvocationTargetException, InterruptedException {
				finishPage(monitor);
			}
		};
		try {
			getContainer().run(false, true, op);
		} catch (InvocationTargetException e) {
			return false; // TODO: should open error dialog and log
		} catch  (InterruptedException e) {
			return false; // canceled
		}
		return true;
	}
			
	private void addProjectNature(IProject project, String nature) 
			throws CoreException {
			IProjectDescription description = project.getDescription();
			List<String> natures = new ArrayList<String>(
					Arrays.asList(description.getNatureIds()));
			if(!natures.contains(natures)) {
				natures.add(nature);
				description.setNatureIds(natures.toArray(new String[0]));
				project.setDescription(description, null);
			}
			
		}

}