/**
 * Copyright (c) 2014 Dung Ta Van . All rights reserved.
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

package com.tvd.gameview.ext;

import java.io.File;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.BundleContext;

import com.tvd.gameview.ext.constants.Constant;

/**
 * The activator class controls the plug-in life cycle
 */
public class GameViewSdk extends AbstractUIPlugin {

	public static abstract class CheckSdkErrorHandler {
		public abstract boolean handleError(String message);
        public abstract boolean handleWarning(String message);
        protected void setErrorMessage(String replaceAll) {
			
		}
        protected void showMessage(String replaceAll) {
			
		}
	}

	// The plug-in ID
	public static final String PLUGIN_ID = "com.tvd.gameview.ext.plugin"; //$NON-NLS-1$

	// The shared instance
	private static GameViewSdk plugin;
	
	/**
	 * The constructor
	 */
	public GameViewSdk() {
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext context) throws Exception {
		super.start(context);
		plugin = this;
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext context) throws Exception {
		plugin = null;
		super.stop(context);
	}

	/**
	 * Returns the shared instance
	 *
	 * @return the shared instance
	 */
	public static GameViewSdk getDefault() {
		return plugin;
	}
	
	public static ImageDescriptor getImageDescriptor(String path) {
		return imageDescriptorFromPlugin(PLUGIN_ID, path);
	}

	public boolean checkSdkLocationAndId(String fileName,
			CheckSdkErrorHandler checkSdkErrorHandler) {
		File file = new File(fileName + "/" 
				+ Constant.GLOBAL_PROJECT_CONFIG_FILE);
		if(!file.exists()) {
			checkSdkErrorHandler.handleError("Invalid location");
			checkSdkErrorHandler.handleWarning("Invalid location");
		}
		
		return file.exists();
	}

}
