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

import org.eclipse.jface.preference.DirectoryFieldEditor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Group;
import org.eclipse.ui.dialogs.WizardNewProjectCreationPage;

import com.tvd.gameview.ext.utils.MessageUtils;

public class GameViewMainPage extends WizardNewProjectCreationPage {

	public GameViewMainPage(String pageName) {
		super(pageName);
	}

	@Override
	public void createControl(Composite parent) {
		super.createControl(parent);
		Composite composite = (Composite)getControl();
		Group group = new Group(composite, SWT.NONE);
		group.setText(MessageUtils.getString("game_project"));
		group.setLayout(new GridLayout());
		group.setLayoutData(new GridData(
		         GridData.HORIZONTAL_ALIGN_FILL));
		
		mGameProjectLocation = new DirectoryFieldEditor("location", 
				"Location", group);
		mGameProjectLocation.setFocus();
		mGenerateTemplate = new Button(group, SWT.CHECK);
		mGenerateTemplate.setText("Create template");
		mGenerateTemplate.setSelection(true);
		mGenerateTemplate.setEnabled(false);
		
		mGameProjectLocation.getTextControl(group).addModifyListener(
				new ModifyListener() {
					
					@Override
					public void modifyText(ModifyEvent e) {
						if(validatePage()) {
							GameViewMainPage.this.setPageComplete(true);
							GameViewMainPage.this.setErrorMessage(null);
						}
					}
		});
	}
	
	@Override
	protected boolean validatePage() {
		if(mGameProjectLocation != null) {
			String projectLocation = mGameProjectLocation.getStringValue();
			if(projectLocation == null || projectLocation.equals("")) {
				this.setErrorMessage("Invalid game template location");
				return false;
			}
		} 
		return super.validatePage();
	}
	
	public DirectoryFieldEditor getGameProjectLocation() {
		return this.mGameProjectLocation;
	}
	
	private DirectoryFieldEditor mGameProjectLocation;
	private Button mGenerateTemplate;
}
