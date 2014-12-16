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
package com.tvd.gameview.ext.model;

import java.util.List;

import org.eclipse.core.resources.IProject;
import org.eclipse.jdt.core.IJavaProject;
import org.eclipse.jdt.ui.JavaElementLabelProvider;
import org.eclipse.jface.viewers.ILabelProvider;
import org.eclipse.jface.window.Window;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.dialogs.ElementListSelectionDialog;

import com.tvd.gameview.ext.utils.ProjectUtils;

public class ProjectChooserHelper {

	public static IJavaProject chooseJavaProject(Shell shell) {
		ILabelProvider labelProvider = new JavaElementLabelProvider();
		ElementListSelectionDialog dialog = new ElementListSelectionDialog(shell, 
				labelProvider);
		dialog.setTitle("Project selection");
		String message = "Please select a project";
		dialog.setMessage(message);

        // set the elements in the dialog. These are opened android projects.
        dialog.setElements(ProjectUtils.getSdkProjects().toArray(new Object[0]));
        if(dialog.open() == Window.OK) {
        	return (IJavaProject)dialog.getFirstResult();
        }
        
        return null;
	}
	
	
	public static class ProjectCombo extends Combo implements SelectionListener {

		public ProjectCombo(Composite parent) {
			super(parent, SWT.BORDER | SWT.FLAT | SWT.READ_ONLY);
			mInitialProject = ProjectUtils.getActiveSdkProject();
			mProject = mInitialProject;
			mAvailableProjects = ProjectUtils.getSdkProjects();
			String items[] = new String[mAvailableProjects.size() + 1];
			items[0] = "--- Choose Project ---";
			int selectionIndex = 0;
			for (int i = 0, n = mAvailableProjects.size(); i < n; i++) {
                IProject project = mAvailableProjects.get(i).getProject();
                items[i + 1] = project.getName();
                if (project == mInitialProject) {
                    selectionIndex = i + 1;
                }
            }
			this.setItems(items);
			this.select(selectionIndex);
			
			this.addSelectionListener(this);
		}

		@Override
		public void widgetSelected(SelectionEvent e) {
			int selectionIndex = getSelectionIndex();
            if (selectionIndex > 0 && mAvailableProjects != null
                    && selectionIndex <= mAvailableProjects.size()) {
                // selection index 0 is "Choose Project", all other projects are offset
                // by 1 from the selection index
                mProject = mAvailableProjects.get(selectionIndex - 1).getProject();
            } else {
                mProject = null;
            }
		}

		@Override
		public void widgetDefaultSelected(SelectionEvent e) {
			
		}
		
		public void setSelectedProject(IProject project) {
            mProject = project;

            int selectionIndex = 0;
            for (int i = 0, n = mAvailableProjects.size(); i < n; i++) {
                if (project == mAvailableProjects.get(i).getProject()) {
                    selectionIndex = i + 1; // +1: Slot 0 is reserved for "Choose Project"
                    select(selectionIndex);
                    break;
                }
            }
        }
		
		public IProject getSelectedProject() {
            return mProject;
        }
		
		@Override
        protected void checkSubclass() {
            // Disable the check that prevents subclassing of SWT components
        }
		
		protected IProject mInitialProject;
		protected List<IProject> mAvailableProjects;
		protected IProject mProject;
	}
}
