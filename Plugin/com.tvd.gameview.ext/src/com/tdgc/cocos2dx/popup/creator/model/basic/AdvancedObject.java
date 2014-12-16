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

package com.tdgc.cocos2dx.popup.creator.model.basic;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import org.eclipse.core.resources.IProject;

import com.tdgc.cocos2dx.popup.creator.constants.Strings;
import com.tdgc.cocos2dx.popup.creator.file.FileUtils;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.ItemGroup;
import com.tdgc.cocos2dx.popup.creator.model.Menu;
import com.tdgc.cocos2dx.popup.creator.model.Progressbar;
import com.tdgc.cocos2dx.popup.creator.utils.NotificationCenter;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;
import com.tdgc.cocos2dx.popup.creator.utils.ViewUtils;

public class AdvancedObject extends CommonObject {
	
	public AdvancedObject() {
		super();
		this.mParameters = new ArrayList<Parameter>();
		this.mProperties = new ArrayList<Property>();
		this.mLabelGroupInView = new ArrayList<ItemGroup>();
		this.mSpriteGroupInView = new ArrayList<ItemGroup>();
		this.mMenuItemGroupInView = new ArrayList<ItemGroup>();
		this.mMenuGroupInView = new ArrayList<ItemGroup>();
		this.mTableGroupInView = new ArrayList<ItemGroup>();
		
		this.mAdvancedChilds = new ArrayList<AdvancedObject>();
		
		this.mProgressGroup = new ItemGroup(ItemGroup.Type.PROGRESSBAR);
		
		this.mSuper = Config.getInstance().getDefaultSuper(mSuffix);
		this.mBackgroundName = Strings.DEFAULT;
		this.mIsNewClass = true;
		this.mIsExported = false;
	}
	
	@Override
	public String declare() {
		//export child
		for(AdvancedObject child : mAdvancedChilds) {
			if(child.getBacsicObject() != null
					&& child.getBacsicObject().isGenerateClass()) {
				if(child.isExported()) {
					System.out.println("INFO::" + child.getClassName() + " is exported");
				} else {
					child.exportSourceCode();
					child.setExported(true);
				}
			}
		}
		String superDeclare = new StringBuilder()
			.append(ViewUtils.declareGroups(mLabelGroupInView))
			.append("\n")
			.append(ViewUtils.declareGroups(mSpriteGroupInView))
			.append("\n")
			.append(ViewUtils.declareGroups(mMenuItemGroupInView))
			.append("\n")
			.append(ViewUtils.declareGroups(mMenuGroupInView))
			.append("\n")
			.append(ViewUtils.declareGroups(mTableGroupInView))
			.append("\n")
			.append(mProgressGroup.declare())
			.toString();
		
		Date createdDate = Calendar.getInstance().getTime();
		String classNamePrefix = StringUtils.convertToClassName(
				mPrefix.substring(mPrefix.indexOf("_") + 1), "");
		char firstChar = ("" + classNamePrefix.charAt(0)).toLowerCase().charAt(0);
		classNamePrefix = classNamePrefix.replace(classNamePrefix.charAt(0), firstChar);
		
		String propertiesDeclare = StringUtils.standardizeCode(superDeclare
				+ declareProperties());
		FileUtils fileUtils = new FileUtils();
		String customSourceCode = fileUtils.findCustomSourceCode(
				mClassPath + "/" + mDirectoryName + "/" + mClassName + ".h");
		String template = fileUtils.fetchTemplate(
				getClassDeclaringTemplateName(),
				getClassTemplateFilePath(), getProject());
		String result = template.replace("{class_name}", mClassName)
				.replace("{author}", System.getProperty("user.name"))
				.replace("{project_name}", getProject().getName())
				.replace("{created_date}", createdDate.toString())
				.replace("{super_name}", mSuper)
				.replace("//{properties_declare}", propertiesDeclare)
				.replace("//{menuitem_tags}", createMenuItemTags())
				.replace("//{extend_functions}", StringUtils.standardizeCode(
						createExtendFunctions(true)))
				.replace("{class_name_prefix}", classNamePrefix)
				.replace("//{parameters}", declareParameters())
				.replace("//{n}", "\n")
				.replace("//{custom_source_code}", customSourceCode.trim())
				.replace("//{importings}", createImportDirectives());
		
		StringBuilder tagBuilder = new StringBuilder()
			.append(ViewUtils.createElementTags(mLabelGroupInView, 100))
			.append(ViewUtils.createElementTags(mMenuGroupInView, 200))
			.append(ViewUtils.createElementTags(mMenuItemGroupInView, 300))
			.append(ViewUtils.createElementTags(mSpriteGroupInView, 400));
		result = result.replace("//{element_tags}", tagBuilder.toString());
	
		return StringUtils.standardizeCode(result);
	}

	@Override
	public String implement(boolean pInfunction) {
		this.setParentForMenuItems();
		
		Date createdDate = Calendar.getInstance().getTime();
		String classNamePrefix = StringUtils.convertToClassName(
				mPrefix.substring(mPrefix.indexOf("_") + 1), "");
		char firstChar = ("" + classNamePrefix.charAt(0)).toLowerCase().charAt(0);
		classNamePrefix = classNamePrefix.replace(classNamePrefix.charAt(0), firstChar);
		
		FileUtils fileUtils = new FileUtils();
		String customSourceCode = fileUtils.findCustomSourceCode(
				mClassPath + "/" + mDirectoryName + "/" + mClassName + ".cpp");
		String template = fileUtils.fetchTemplate(
				getClassImplementingTemplateName(), 
				getClassTemplateFilePath(), getProject());	
		
		String result = template.replace("{author}", System.getProperty("user.name"))
				.replace("{project_name}", getProject().getName())
				.replace("{created_date}", createdDate.toString())
				.replace("{super_name}", mSuper)
				.replace("//{add_menus}", StringUtils.standardizeCode(
						ViewUtils.implementGroups(mMenuGroupInView)))
				.replace("//{add_menuitems}", StringUtils.standardizeCode(
						ViewUtils.implementGroups(mMenuItemGroupInView)))
				.replace("//{add_sprites}", StringUtils.standardizeCode(
						ViewUtils.implementGroups(mSpriteGroupInView)))
				.replace("{class_name_prefix}", classNamePrefix)
				.replace("//{add_labels}", StringUtils.standardizeCode(
						ViewUtils.implementGroups(mLabelGroupInView)))
				.replace("//{add_tables}", StringUtils.standardizeCode(
						ViewUtils.implementGroups(mTableGroupInView)))
				.replace("//{add_progressbars}", mProgressGroup.implement(false))
				.replace("//{extend_functions}", StringUtils.standardizeCode(
						createExtendFunctions(false)))
				.replace("{callback_function}", classNamePrefix + "MenuItemCallback")
				.replace("{class_name}", mClassName)
				.replace("//{parameters}", declareParameters())
				.replace("//{importing_params}", importingParams())
				.replace("//{assigning_area}", assigningArea())
				.replace("//{n}", "\n")
				.replace("//{custom_source_code}", customSourceCode.trim())
				.replace("//{importings}", createImportDirectives());
		
		for(int i = 0 ; i < mProperties.size() ; i++) {
			String mark = "\"${param" + i + "}\"";
			result = result.replace(mark, mProperties.get(i).getName());
		}

		return StringUtils.standardizeCode(result);
	}
	
	public String declarePositions() {
		StringBuilder builder = new StringBuilder("\n");
		builder.append(ViewUtils.declarePositionGroups(mLabelGroupInView))
			.append("\n")
			.append(ViewUtils.declarePositionGroups(mSpriteGroupInView))
			.append("\n")
			.append(ViewUtils.declarePositionGroups(mMenuItemGroupInView))
			.append("\n")
			.append(ViewUtils.declarePositionGroups(mMenuGroupInView))
			.append("\n")
			.append(ViewUtils.declarePositionGroups(mTableGroupInView));
		
		return builder.toString();
	}
	
	@Override
	public String implementPositions() {
		StringBuilder builder = new StringBuilder("\n");
		builder.append(ViewUtils.implementPositionGroups(mLabelGroupInView))
			.append("\n")
			.append(ViewUtils.implementPositionGroups(mSpriteGroupInView))
			.append("\n")
			.append(ViewUtils.implementPositionGroups(mMenuItemGroupInView))
			.append("\n")
			.append(ViewUtils.implementPositionGroups(mMenuGroupInView))
			.append("\n")
			.append(ViewUtils.implementPositionGroups(mTableGroupInView));
		
		return builder.toString();
	}
	
	public String createImportDirectives() {
		String template = new FileUtils().fetchTemplate("Import", 
				"src/com/template/import.template", getProject());
		StringBuilder builder = new StringBuilder();
		createImportDirectives(this, builder, template);
		
		return builder.toString();
	}
	
	public void createImportDirectives(AdvancedObject obj, 
			StringBuilder builder, String template) {
		for(AdvancedObject child : obj.getAdvancedChilds()) {
			if(child.getBacsicObject() != null
					&& child.getBacsicObject().isGenerateClass()) {
				builder.append(template.replace("{class_name}", 
						child.getClassName()))
					.append("\n");
			}
			createImportDirectives(child, builder, template);
		}
		
	}
	
	public String createImportDirective() {
		String template = new FileUtils().fetchTemplate("Import", 
				"src/com/template/import.template", getProject());
		template = template.replace("{class_name}", mClassName);
		
		return template;
	}
	
	public void exportHeaderCode() {
		if(isExported()) {
			NotificationCenter.i("Header code of " + mClassName + " exported!");
			return;
		}
		String path = getClassPath() + "/" 
				+ getDirectoryName() + "/" + getClassName()
				+ ".h";
		String fileContent = declare();
		new FileUtils().setContent(fileContent).writeToFile(path, false);
	}
	
	public void exportImplementedCode() {
		if(isExported()) {
			NotificationCenter.i("Implemented code of " + mClassName + " exported!");
			return;
		}
		String path = getClassPath() + "/" 
				+ getDirectoryName() + "/" + getClassName()
				+ ".cpp";
		String fileContent = implement(false);
		new FileUtils().setContent(fileContent).writeToFile(path, false);
	}
	
	public void exportSourceCode() {
		if(isExported()) {
			NotificationCenter.i("Source code of " + mClassName + " exported!");
			return;
		}
		exportHeaderCode();
		exportImplementedCode();
	}
	
	protected String createMenuItemTags() {
		return ViewUtils.createElementTags(mMenuItemGroupInView, 1001);
	}
	
	public void addParameter(Parameter pParameter) {
		pParameter.setTabCount(getTabCount() + 1);
		this.mParameters.add(pParameter);
		this.mProperties.add(new Property(pParameter));
	}
	
	protected String declareParameters() {
		if(mParameters.size() == 0) {
			return "//{parameters}";
		}
		StringBuilder builder = new StringBuilder();
		int size = mParameters.size();
		for(int i = 0 ; i < size ; i++) {
			if(i > 0) {
				builder.append("\t\t\t\t\t\t\t");
			}
			builder.append(mParameters.get(i));
			if(i < size - 1) {
				builder.append(", \n");
			}
		}
		
		return builder.toString().trim();
	}
	
	protected String declareProperties() {
		StringBuilder builder = new StringBuilder("\n");
		for(int i = 0 ; i < mProperties.size() ; i++) {
			builder.append("\t" + mProperties.get(i))
				.append("\n");
		}
		
		return builder.toString();
	}
	
	protected String importingParams() {
		int size = mParameters.size();
		if(size == 0) {
			return "//{importing_params}";
		}
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < size ; i++) {
			if(i > 0) {
				builder.append("\t\t\t");
			}
			builder.append(mParameters.get(i).getName());
			if(i < size - 1) {
				builder.append(", \n");
			}
			
		}
		return builder.toString().trim();
	}
	
	protected String assigningArea() {
		StringBuilder builder = new StringBuilder("\n");
		for(int i = 0 ; i < mProperties.size() ; i++) {
			builder.append("\t" + mProperties.get(i).getName())
				.append(" = ")
				.append(mParameters.get(i).getName())
				.append(";\n");
		}
		
		return builder.toString();
	}
	
	protected void setParentForMenuItems() {
		CommonObject parent = new Menu();
		parent.setName(Config.getInstance().getDefaultMenuOnSuper(mType));
		parent.setProject(getProject());
		for(int i = 0 ; i < mMenuItemGroups.size() ; i++) {
			for(int j = 0 ; j < mMenuItemGroups.get(i).getItems().size() ; j++) {
				mMenuItemGroups.get(i).getItems().get(j).setParent(parent);
			}
		}
	}
	
	private String createExtendFunctions(boolean pInHeader) {
		StringBuilder builder = new StringBuilder();
		return builder.toString();
	}
	
	//for items group management
	public void pushBackGroup(ItemGroup group) {
		switch (group.getType()) {
		case ItemGroup.Type.LABLE:
			pushBackLabelGroup(group);
			break;
		case ItemGroup.Type.MENU:
			pushBackMenuGroup(group);
			break;
		case ItemGroup.Type.MENUITEM:
			pushBackMenuItemGroup(group);
			break;
		case ItemGroup.Type.SPRITE:
			pushBackSpriteGroup(group);
			break;
		case ItemGroup.Type.TABLE:
			pushBackTableGroup(group);
			break;
		default:
			break;
		}
	}
	
	protected void pushBackLabelGroup(ItemGroup group) {
		this.mLabelGroupInView.add(group);
	}
	protected void pushBackSpriteGroup(ItemGroup group) {
		this.mSpriteGroupInView.add(group);
	}
	protected void pushBackMenuItemGroup(ItemGroup group) {
		this.mMenuItemGroupInView.add(group);
	}
	protected void pushBackMenuGroup(ItemGroup group) {
		this.mMenuGroupInView.add(group);
	}
	protected void pushBackTableGroup(ItemGroup group) {
		this.mTableGroupInView.add(group);
	}
	
	public void setClassName(String pClassName) {
		this.mClassName = pClassName;
	}
	
	public String getClassName() {
		return this.mClassName;
	}
	
	public void setBackgroundName(String bgName) {
		this.mBackgroundName = bgName;
	}
	
	public String getBackgroundName() {
		if(mBackgroundName == null) {
			mBackgroundName = Strings.DEFAULT;
		}
		return mBackgroundName;
	}
	
	public void addProgressbars(Progressbar bar) {
		this.mProgressGroup.addItem(bar);
	}
	
	public ItemGroup getProgressbars() {
		return this.mProgressGroup;
	}
	
	public void setAdvancedParent(AdvancedObject parent) {
		parent.addAdvancedChild(this);
		this.mAdvancedParent = parent;
		this.setDirectoryName(parent.getDirectoryName());
		this.setClassPath(parent.getClassPath());
	}
	
	public void addAdvancedChild(AdvancedObject child) {
		this.mAdvancedChilds.add(child);
	}
	
	public AdvancedObject getAdvancedParent() {
		return this.mAdvancedParent;
	}
	
	public List<AdvancedObject> getAdvancedChilds() {
		return this.mAdvancedChilds;
	}
	
	public String getClassDeclaringTemplateName() {
		return this.mTemplateName + " class declaring";
	}
	
	public String getClassImplementingTemplateName() {
		return this.mTemplateName + " class implementing";
	}
	
	public String getClassTemplateFilePath() {
		return this.getTemplateFilePath();
	}
	
	@Override
	public void setType(String type) {
		super.setType(type);
		if(type != null && type.trim().length() > 0
				&& mTemplateFile == null) {
			mTemplateFile = type + ".template";
		}
	}
	
	public void setClassPath(String mClassPath) {
		this.mClassPath = mClassPath;
	}

	public void setDirectoryName(String mDirectoryName) {
		this.mDirectoryName = mDirectoryName;
	}
	
	public void setBasicObject(CommonObject obj) {
		this.mBasicObject = obj;
	}
	
	public CommonObject getBacsicObject() {
		return this.mBasicObject;
	}
	
	public List<Parameter> getParameters() {
		return this.mParameters;
	}
	
	public String getDirectoryName() {
		return this.mDirectoryName;
	}
	
	public String getClassPath() {
		return mClassPath;
	}
	
	public List<ItemGroup> getLabelGroupInView() {
		return mLabelGroupInView;
	}

	public List<ItemGroup> getSpriteGroupInView() {
		return mSpriteGroupInView;
	}

	public List<ItemGroup> getMenuItemGroupInView() {
		return mMenuItemGroupInView;
	}

	public List<ItemGroup> getMenuGroupInView() {
		return mMenuGroupInView;
	}

	public List<ItemGroup> getTableGroupInView() {
		return mTableGroupInView;
	}
	
	public void setExported(boolean isExported) {
		this.mIsExported = isExported;
	}
	
	public boolean isExported() {
		return mIsExported;
	}
	
	@Override
	public IProject getProject() {
		IProject project = mProject;
		AdvancedObject parent = mAdvancedParent;
		while(mProject == null && parent != null) {
			project = parent.mProject;
			parent = parent.getAdvancedParent();
		}
		
		return project;
	}
	
	@Override
	public CommonObject clone() {
		AdvancedObject obj = new AdvancedObject();
		this.setAllPropertiesForObject(obj);
		obj.mBackgroundName = mBackgroundName;
		obj.mClassName = mClassName;
		
		obj.mParameters = mParameters;
		obj.mProperties = mProperties;
		obj.mLabelGroupInView = mLabelGroupInView;
		obj.mSpriteGroupInView = mSpriteGroupInView;
		obj.mMenuGroupInView = mMenuGroupInView;
		obj.mMenuItemGroupInView = mMenuItemGroupInView;
		obj.mTableGroupInView = mTableGroupInView;
		
		obj.mProgressGroup = mProgressGroup;
		
		obj.mAdvancedParent = mAdvancedParent;
		
		return obj;
	}
	
	protected String mBackgroundName;
	protected String mClassName;
	protected String mClassPath;
	protected String mDirectoryName;
	
	protected List<Parameter> mParameters;
	protected List<Property> mProperties;
	protected List<ItemGroup> mLabelGroupInView;
	protected List<ItemGroup> mSpriteGroupInView;
	protected List<ItemGroup> mMenuItemGroupInView;
	protected List<ItemGroup> mMenuGroupInView;
	protected List<ItemGroup> mTableGroupInView;
	protected CommonObject mBasicObject;
	
	private ItemGroup mProgressGroup;
	
	private AdvancedObject mAdvancedParent;
	private List<AdvancedObject> mAdvancedChilds;
	
	protected boolean mIsExported;
}
