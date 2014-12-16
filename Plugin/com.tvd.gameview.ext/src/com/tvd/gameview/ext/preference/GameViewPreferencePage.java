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

package com.tvd.gameview.ext.preference;

import java.io.File;

import org.eclipse.jface.preference.DirectoryFieldEditor;
import org.eclipse.jface.preference.FieldEditorPreferencePage;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPreferencePage;

import com.tvd.gameview.ext.GameViewSdk;
import com.tvd.gameview.ext.constants.Key;
import com.tvd.gameview.ext.utils.MessageUtils;

public class GameViewPreferencePage extends FieldEditorPreferencePage implements
		IWorkbenchPreferencePage {

	public GameViewPreferencePage() {
	}

	public GameViewPreferencePage(int style) {
		super(style);
	}

	public GameViewPreferencePage(String title, int style) {
		super(title, style);
	}

	public GameViewPreferencePage(String title, ImageDescriptor image, int style) {
		super(title, image, style);
	}

	@Override
	public void init(IWorkbench workbench) {
		this.setPreferenceStore(GameViewSdk.getDefault().getPreferenceStore());
	}

	@Override
	protected void createFieldEditors() {
		final DirectoryFieldEditor directory = 
				new SdkDirectoryFieldEditor(Key.TEMPLATE_ROOT, "Sdk Root", 
						this.getFieldEditorParent());
		directory.setStringValue(
				this.getPreferenceStore().getString(Key.TEMPLATE_ROOT));
		this.addField(directory);
	}
	

	/**
	 * 
	 * @author Dzung Ta Van
	 *
	 * reference https://android.googlesource.com/platform/development/+/d2f2b1d7b77d06bce8cf9340171cf6c25cd720c4/tools/eclipse/plugins/com.android.ide.eclipse.adt/src/com/android/ide/eclipse/adt/preferences/AndroidPreferencePage.java
	 */
	private static class SdkDirectoryFieldEditor extends DirectoryFieldEditor {
	    public SdkDirectoryFieldEditor(String name, String labelText, Composite parent) {
	        super(name, labelText, parent);
	        setEmptyStringAllowed(false);
	    }
	    /**
	     * Method declared on StringFieldEditor and overridden in DirectoryFieldEditor.
	     * Checks whether the text input field contains a valid directory.
	     *
	     * @return True if the apply/ok button should be enabled in the pref panel
	     */
	    @Override
	    protected boolean doCheckState() {
	        String fileName = getTextControl().getText();
	        fileName = fileName.trim();
	        
	        if (fileName.indexOf(',') >= 0 || fileName.indexOf(';') >= 0) {
	            this.setErrorMessage(MessageUtils.getString("invalid_location"));
	            return false;  // Apply/OK must be disabled
	        }
	        
	        File file = new File(fileName);
	        if (!file.isDirectory()) {
	        	this.setErrorMessage(JFaceResources.getString(
	                "DirectoryFieldEditor.errorMessage")); //$NON-NLS-1$
	            return false;
	        }
	        boolean ok = GameViewSdk.getDefault().checkSdkLocationAndId(fileName,
	                new GameViewSdk.CheckSdkErrorHandler() {
	            @Override
	            public boolean handleError(String message) {
	            	this.setErrorMessage(message.replaceAll("\n", " ")); //$NON-NLS-1$ //$NON-NLS-2$
	                return false;  // Apply/OK must be disabled
	            }
	
				@Override
	            public boolean handleWarning(String message) {
	            	this.showMessage(message.replaceAll("\n", " ")); //$NON-NLS-1$ //$NON-NLS-2$
	                return true;  // Apply/OK must be enabled
	            }
	        });
	        if (ok) clearMessage();
	        return ok;
	    }
	    @Override
	    public Text getTextControl(Composite parent) {
	        setValidateStrategy(VALIDATE_ON_KEY_STROKE);
	        return super.getTextControl(parent);
	    }
	}
}
