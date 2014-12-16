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

import org.eclipse.core.resources.IProject;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;

import com.tvd.gameview.ext.constants.Constant;
import com.tvd.gameview.ext.file.FileActions;
import com.tvd.gameview.ext.pages.NewIBTemplatePage;

public class NewInterfaceBuilderTemplate extends Wizard implements INewWizard {

	public NewInterfaceBuilderTemplate() {
		this.setWindowTitle("Create Interface Builder template");
	}

	@Override
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		this.mSelection = selection;
	}
	
	@Override
	public void addPages() {
		super.addPages();
		mNewIBTemplatePage = new NewIBTemplatePage("Interface Builder Template",
				mSelection);
		mNewIBTemplatePage.setTitle("From Game View Project");
		mNewIBTemplatePage.setDescription("Create a Interface Builder template");
		
		this.addPage(mNewIBTemplatePage);
	}

	@Override
	public boolean performFinish() {
		createTemplateFile();
		return true;
	}
	
	private void createTemplateFile() {
		NewIBTemplatePage page = (NewIBTemplatePage)mNewIBTemplatePage;
		IProject project = page.getSelectedProject();
		int orientation = page.getDeviceOrientation();
		String ib = page.getInterfaceBuilder().trim().toLowerCase();
		String width = page.getWidth();
		String height = page.getHeight();
		String deviceFolder = page.getDeviceFolder();
		String filext = "xib";
		String orientationTag = "";
		if(ib.equals("xib")) {
			if(orientation == Constant.Orientation.LANDSCAPE) {
				StringBuilder orientationTagBuilder = new StringBuilder()
					.append("<simulatedOrientationMetrics "
							+ "key=\"simulatedOrientationMetrics\" "
							+ "orientation=\"landscapeRight\"/>")
					.append("\n\t\t\t")
					.append("<simulatedScreenMetrics "
						+ "key=\"simulatedOrientationMetrics\" "
						+ "orientation=\"landscapeRight\"/>");
				orientationTag = orientationTagBuilder.toString();
			}
		}
		String templateContent = FileActions.readFromFile(
				getClass().getResourceAsStream("/com/tvd/ib/template/"
						+ ib + "_template." + filext));
		templateContent = templateContent.replace("{width}", width)
				.replace("{height}", height)
				.replace("<!--{orientation}-->", orientationTag);
		
		FileActions.writeToFile(project, 
				"resources/" + ib + "/" + deviceFolder, 
				"template." + filext, 
				templateContent);
	}

	private WizardPage mNewIBTemplatePage;
	private ISelection mSelection;
}
