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

package com.tdgc.cocos2dx.popup.creator.global;

import java.util.Map;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;

import com.tdgc.cocos2dx.popup.creator.constants.Constants;
import com.tdgc.cocos2dx.popup.creator.file.FileUtils;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.Resource;

public class Config {
	
	private Config() {
		mDefaultNormalPrefix 			= "m";
	}

	public static Config getInstance() {
		if(sInstance == null) {
			synchronized (Config.class) {
				if(sInstance == null) {
					sInstance = new Config();
				}
			}
		}
		
		return sInstance;
	}
	
	public void loadConfigs() {
		
		IFile file = mProject.getFile("src/com/config/default.properties");
		FileUtils fileUtils = new FileUtils();
		String fileContent = fileUtils.readFromFile(file);
		mDefaultTemplateNames = fileUtils.fetchDefaultKeyValues(
				"Template name", fileContent);
		mDefaultSupers = fileUtils.fetchDefaultKeyValues(
				"Super name", fileContent);
		mDefaultBackgroundOnSupers = fileUtils.fetchDefaultKeyValues(
				"Background on super", fileContent);
		mDefaultMenuOnSupers = fileUtils.fetchDefaultKeyValues(
				"Menu on super", fileContent);
		mDefaultNormalPrefix = fileUtils.fetchDefaultValue(
				"normal_prefix", "Prefix and Suffix", fileContent);
		mDefaultViewSuffix = fileUtils.fetchDefaultValue(
				"view_suffix", "Prefix and Suffix", fileContent);
		mDefaultScreenSize = fileUtils.fetchDefaultKeyValues(
				"Screen size", fileContent);
		
		mDefaultBackgroundImages = fileUtils.fetchDefaultBackgroundImages(
				"Background image on super", fileContent);
		mDefaultExitResources = fileUtils.fetchDefaultExitResource(
				"Exit button on super", fileContent);
		
		if(mDefaultViewSuffix == null 
				|| mDefaultViewSuffix.trim().length() == 0
				|| mDefaultViewSuffix.equals("default")) {
			mDefaultViewSuffix = "";
		}
		
		System.out.println("Config just have loaded");
	}
	
	public void reloadConfigs() {
		loadConfigs();
		System.out.println("Config just have reloaded");
	}
	
	public void setProject(IProject project) {
		if(mProject != project) {
			this.mProject = project;
			this.loadConfigs();
		}
	}
	
	public IProject getProject() {
		return mProject;
	}
	
	public String getDefaultSuper(String type) {
		return getDefaultValue(mDefaultSupers, type, "DefaultSuper");
	}
	
	public String getDefaultBackgroundOnSupers(String pViewType) {
		return getDefaultValue(mDefaultBackgroundOnSupers, pViewType, 
				"this");
	}
	
	public String getProjectName() {
		return mProjectName;
	}

	public void setProjectName(String mProjectName) {
		this.mProjectName = mProjectName;
	}

	public String getDefaultNormalPrefix() {
		return mDefaultNormalPrefix;
	}

	public void setDefaultNormalPrefix(String mDefaultNormalPrefix) {
		this.mDefaultNormalPrefix = mDefaultNormalPrefix;
	}

	public void setDefaultSupers(Map<String, String> mDefaultSupers) {
		this.mDefaultSupers = mDefaultSupers;
	}

	public String getDefinePath() {
		return mDefinePath;
	}

	public void setDefinePath(String mDefinePath) {
		this.mDefinePath = mDefinePath;
	}

	public String getParametersPath() {
		return mParametersPath;
	}

	public void setParametersPath(String mParametersPath) {
		this.mParametersPath = mParametersPath;
	}

	public String getImagesInputPath() {
		return mImagesInputPath;
	}

	public void setImagesInputPath(String mImagesInputPath) {
		this.mImagesInputPath = mImagesInputPath;
	}

	public String getImagesPath() {
		return mImagesPath;
	}

	public void setImagesPath(String mImagesPath) {
		this.mImagesPath = mImagesPath;
	}

	public String getXibContainerPath() {
		return mXibContainerPath;
	}

	public void setXibContainerPath(String mXibContainerPath) {
		this.mXibContainerPath = mXibContainerPath;
	}

	public String getClassPath() {
		return mClassPath;
	}

	public void setClassPath(String mClassPath) {
		this.mClassPath = mClassPath;
	}

	public String getScreenContainerPath() {
		return mScreenContainerPath;
	}

	public void setScreenContainerPath(String mScreenContainerPath) {
		this.mScreenContainerPath = mScreenContainerPath;
	}

	public void setAndroidContainerPath(String path) {
		this.mAndroidContainerPath = path;
	}
	
	public String getAndroidContainerPath() {
		return this.mAndroidContainerPath;
	}
	
	public int getProgrammingType() {
		return Constants.NORMAL;
	}
	
	public String getDefaultMenuOnSuper(String superType) {
		return getDefaultValue(mDefaultMenuOnSupers, superType, "mMenu");
	}
	
	public String getDefaultTemplateName(String superType) {
		return getDefaultValue(mDefaultTemplateNames, superType, 
				"Common");
	}
	
	public Image getDefaultBackgroundImage(String type) {
		return mDefaultBackgroundImages.get(type);
	}
	
	public Resource getDefaultExitResource(String viewType) {
		return mDefaultExitResources.get(viewType);
	}
	
	public String getDefaultScreenSizeString(String device) {
		return getDefaultValue(mDefaultScreenSize, device, "320, 480");
	}
	
	public String getDefaultViewSuffix() {
		return mDefaultViewSuffix;
	}
	
	private String getDefaultValue(Map<String, String> keyValues, 
			String key, String defaultValue) {
		String value = keyValues.get(key);
		if(value == null || value.trim().length() == 0) {
			value = defaultValue;
		}
		return value;
	}
	
	private String mProjectName;
	private String mDefaultNormalPrefix;
	private String mDefaultViewSuffix;
	
	private Map<String, String> mDefaultSupers;
	private Map<String, String> mDefaultBackgroundOnSupers;
	private Map<String, String> mDefaultMenuOnSupers;
	private Map<String, String> mDefaultTemplateNames;
	private Map<String, Image>  mDefaultBackgroundImages;
	private Map<String, Resource> 	mDefaultExitResources;
	private Map<String, String> mDefaultScreenSize;
	
	private String mDefinePath;
	private String mParametersPath;
	private String mImagesInputPath;
	private String mImagesPath;
	private String mXibContainerPath;
	private String mClassPath;
	private String mScreenContainerPath;
	private String mAndroidContainerPath;
	
	private IProject mProject;
	
	private static Config sInstance;
	
}
