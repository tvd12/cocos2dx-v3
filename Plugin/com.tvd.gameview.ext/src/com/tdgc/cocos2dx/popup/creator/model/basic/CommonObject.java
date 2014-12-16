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
import java.util.List;

import org.eclipse.core.resources.IProject;

import com.tdgc.cocos2dx.popup.creator.constants.Strings;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.file.FileUtils;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.Interface;
import com.tdgc.cocos2dx.popup.creator.model.ItemGroup;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;
import com.tvd.gameview.ext.value.validate.Validator;

public abstract class CommonObject extends BasicObject {
	
	public CommonObject() {
		mMenuGroups = new ArrayList<ItemGroup>();
		mSpriteGroups = new ArrayList<ItemGroup>();
		mLabelGroups = new ArrayList<ItemGroup>();
		mMenuItemGroups = new ArrayList<ItemGroup>();
		mTableGroups = new ArrayList<ItemGroup>();
		
		mSuper = Config.getInstance().getDefaultSuper(mPrefix);
		mZIndex = "0";
		mAnchorPoint = new Point(0.5f, 0.5f);
		mAnchorPointString = "0.5, 0.5";
		mPosition = new Point(0, 0);
		mTabCount = 0;
		mReferenceCount = 0;
		mPositionNamePrefix = "";
		mIsVisible = true;
		mIsBackground = false;
		mComment = "";
		mReferenceCount = 0;
		mIsAddToGroup = true;
		mIsNewClass = false;
		mIsNextItemInArray = false;
		mIsGenerateClass = false;
	}
	
	public abstract String implement(boolean pInfunction);
	
	public abstract CommonObject clone();
	
	public AdvancedObject createAdvancedObject() { return null; }
	
	public void update() {}
	
	public String declare() {
		StringBuilder builder = new StringBuilder();
		String template = new FileUtils().fetchTemplate(
				getDeclaringTemplateName(), 
				getTemplateFilePath(), getProject());
		template = template.replace("{var_name}", mName)
				.replace("{tab}", "");
		builder.append(template.trim());
		return builder.toString();
	}
	
	public String declarePositions() {
		StringBuilder builder = new StringBuilder();
		if(mPositionName != null 
				&& mPositionString != null
				&& !mPositionString.equals(Strings.DEFAULT)) {
			String template = new FileUtils().fetchTemplate(
					getDeclaringPositionTemplateName(), 
					getPostionTemplateFilePath(), getProject());
			builder.append(template.replace("{var_name}", mPositionName)
					.replace("{tab}", "").trim());
		} else {
			System.err.println("ERROR::declarePositions " 
					+ " mPositionName = " + mPositionName
					+ "\nPositionString = " + mPositionString);
		}
		if(mIsGenerateClass && mAdvancedObject != null) {
			builder.append(mAdvancedObject.declarePositions());
		} 
		else {
//			System.out.println("INFO::declarePositions mIsGenerateClass = "
//					+ mIsGenerateClass + " mAdvancedObject = " + mAdvancedObject);
		}
		
		return builder.toString();
	}
	
	public String implementPositions() {
		
		String template = new FileUtils().fetchTemplate(
				getImplementingPositionTemplateName(), 
				getPostionTemplateFilePath(), getProject());
		StringBuilder builder = new StringBuilder();
		if(mPositionString != null 
				&& mPositionName != null
				&& !mPositionString.equals(Strings.DEFAULT)) {
			String spaces = StringUtils.space(60 - mPositionName.length());
			template = template.replace("{var_name}", mPositionName)
					.replace("{position}", mPositionString)
					.replace("{tab}", "\t")
					.replace("{spaces}", spaces);
			builder.append(template.trim());
		}
		
		if(mIsGenerateClass && mAdvancedObject != null) {
			builder.append(mAdvancedObject.implementPositions());
		} 
		else {
//			System.out.println("INFO::declarePositions mIsGenerateClass = "
//					+ mIsGenerateClass + " mAdvancedObject = " + mAdvancedObject);
		}
		
		return builder.toString().trim();
	}
	
	//change
	public void setPositionName(String pPrefix, String pPositionName) {
		this.mPositionNamePrefix = pPrefix;
		this.setPositionName(pPositionName.replace("__", "_"));
	}
	public void setPositionName(String pPositionName) {
		try {
		//name of position in xml file, it must not change
		mXmlPositionName = pPositionName;
		
		mTagName = StringUtils.convertToTagName(pPositionName, this.getType());
		
		mName = StringUtils.convertToNormalProperty(pPositionName + "_" + mSuffix);
		if(pPositionName.trim().equals(Strings.DEFAULT)
				|| this.mIsBackground) {
			mPositionName = null;
			return;
		}
		if(pPositionName.contains(Tag.POSITION)) {
			pPositionName = pPositionName.replace(Tag.POSITION, "place");
		}
		this.mPositionName = pPositionName.toUpperCase() + "_" + mSuffix.toUpperCase();
		this.mPositionName = mPositionNamePrefix.toUpperCase() + "_" + mPositionName 
				+ "_POSITION";
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void setNewPositionName(String pPositionName) {
		mPositionName = pPositionName;
	}
	
	public String getInfunctionName() {
		return mName.substring(0, 2).toLowerCase().charAt(1)
				+ mName.substring(2);
	}
	
	public void replacePositionName(String pNewPosName) {
		this.mPositionName = pNewPosName;
	}
	
	public void setName(String pName) {
		this.mName = pName;
	}
	
	public String getName() {
		return this.mName;
	}
	
	public String getPositionName() {
		return this.mPositionName;
	}
	
	public void setPrefix(String pPrefix) {
		this.mPrefix = pPrefix;
	}
	
	public String getPrefix() {
		return this.mPrefix;
	}
	
	public void setSuffix(String pSuffix) {
		this.mSuffix = pSuffix;
	}
	
	public String getSuffix() {
		return this.mSuffix;
	}
	
	public void addItemGroup(ItemGroup group) {
		group.setContainer(this);
		group.pushBack();
	}
	
	public void addMenuItemGroup(ItemGroup pMenuItemGroup) {
		this.mMenuItemGroups.add(pMenuItemGroup);
	}
	
	public void addMenuGroup(ItemGroup pMenuGroup) {
		this.mMenuGroups.add(pMenuGroup);
	}
	
	public void addSpriteGroup(ItemGroup pSpriteGroup) {
		this.mSpriteGroups.add(pSpriteGroup);
	}
	
	public void addLabelGroup(ItemGroup pLabelGroup) {
		this.mLabelGroups.add(pLabelGroup);
	}
	
	public void addTableGroup(ItemGroup pTableGroup) {
		this.mTableGroups.add(pTableGroup);
	}
	
	public void setComment(String pComment) {
		this.mComment = pComment;
	}
	
	public String getComment() {
		return this.mComment;
	}
	
	public void setSuper(String pSuper) {
		if(!pSuper.equals("default")) {
			this.mSuper = pSuper;
		}
	}
	
	public String getSuper() {
		return this.mSuper;
	}
	
	public void setType(String pType) {
		this.mType = pType;
		this.mPositionNamePrefix = pType;
		
		if(mTemplateFile == null && pType != null) {
			mTemplateFile = pType + ".template";
		}
		if(mTemplateName == null && pType != null) {
			mTemplateName = Config.getInstance().getDefaultTemplateName(pType);
		}
	}
	
	public String getType() {
		return this.mType;
	}
	
	//==========set and get position==========
	public void setPosition(Point pPosition) {
		this.mPosition = pPosition;
		this.mPositionString = pPosition.toString();
	}
	
	public void setPosition(float pX, float pY) {
		this.setPosition(new Point(pX, pY));
	}
	
	public void setPosition(String pPosition) {
		this.mPositionString = pPosition;
		if(!pPosition.equals(Strings.DEFAULT) &&
				Validator.isValidDoubleValueString(pPosition)) {
			String strs[] = pPosition.split(",");
			setPosition(Float.parseFloat(strs[0]), 
					Float.parseFloat(strs[1]));
		}
	}
	
	public Point getPosition() {
		return this.mPosition;
	}
	
	public String getPositionString() {
		return this.mPositionString;
	}
	
	//========== end set and get position==========
	
	//========== set and get anchorpoint==========
	public void setAnchorPoint(Point pPoint) {
		this.mAnchorPoint = pPoint;
		this.mAnchorPointString = pPoint.toString();
	}
	
	public void setAnchorPoint(float pX, float pY) {
		setAnchorPoint(new Point(pX, pY));
	}
	
	public void setAnchorPoint(String pAnchorPoint) {
		if(!pAnchorPoint.equals(Strings.DEFAULT)
				&& Validator.isValidDoubleValueString(pAnchorPoint)) {
			String values[] = pAnchorPoint.split(",");
			this.setAnchorPoint(new Point(Float.parseFloat(values[0]),
					Float.parseFloat(values[1])));
		}
	}
	
	public String getAnchorPointString() {
		return this.mAnchorPointString;
	}
	
	public String getDeclareObjectName() {
		return this.mDeclareObjectName;
	}
	
	//========== end set and get anchorpoint==========
	
	//========== set and get size==========
	public void setSize(Size size) {
		this.mSize = size;
		this.mSizeString = size.toString();
	}
	
	public void setSize(float w, float h) {
		setSize(new Size(w, h));
	}
	
	public Size getSize() {
		if(mSize == null) {
			mSize = mImage.getSize();
		}
		
		return mSize;
	}
	
	public void setSize(String pSize) {
		this.mSizeString = pSize;
		
		if(!pSize.equals(Strings.DEFAULT)
				&& Validator.isValidDoubleValueString(pSize)) {
			String strs[] = pSize.split(",");
			setSize(Float.parseFloat(strs[0]), 
					Float.parseFloat(strs[1]));
		}
	}
	
	public String getSizeString() {
		return this.mSizeString;
	}
	
	//========== end set and get size==========
	
	public void setParent(CommonObject pParent) {
		this.mParent = pParent;
		this.mParent.addChild(this);
		if(pParent == null) {
			return;
		}
		if(mPositionTemplateName == null) {
			this.mPositionTemplateName = pParent.getPositionTemplateName();
		}
		if(mPositionTemplateFile == null) {
			this.mPositionTemplateFile = pParent.getPositionTemplateFile();
		}
		if(mSizeTemplateName == null) {
			this.mSizeTemplateName = pParent.getSizeTemplateName();
		}
		if(mSizeTemplateFile == null) {
			this.mSizeTemplateFile = pParent.getSizeTemplateFile();
		}
	}
	
	public CommonObject getParent() {
		return this.mParent;
	}
	
	public void addChild(CommonObject child) {
		
	}
	
	
	public CommonObject getBackground() {
		return this.mBackground;
	}
	
	public void setBackground(CommonObject pBackground)	{
		if(this.mBackground == null) {
			this.mBackground = pBackground;
		}
	}
	
	public void setIsBackground(boolean pIsBackground) {
		this.mIsBackground = pIsBackground;
	}
	
	public boolean isBackground() {
		return this.mIsBackground;
	}
	
	public void setIsUnlocated(boolean pIsUnlocated) {
		this.mIsUnlocated = pIsUnlocated;
	}
	
	public boolean isUnlocated() {
		return this.mIsUnlocated;
	}
	
	public void setZIndex(String pZIndex) {
		if(Validator.isNumeric(pZIndex)) {
			this.mZIndex = pZIndex;
		}
	}
	
	public void setZIndex(int zIndex) {
		this.mZIndex = "" + zIndex;
	}
	
	public String getZIndex() {
		return this.mZIndex;
	}
	
	protected String declareObjects(List<ItemGroup> pObjs) {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < pObjs.size() ; i++) {
			builder.append("\t");
			builder.append(pObjs.get(i).declare())
				.append("\n");
		}
		
		return builder.toString();
	}
	
	protected String implementObjects(List<ItemGroup> pObjs, boolean pInfunction) {
		StringBuilder builder = new StringBuilder("\n");
		if(mComment != null && !mComment.equals("")) {
			builder.append("\t//" + mComment + "\n");
		}
		for(int i = 0 ; i < pObjs.size() ; i++) {
			builder.append(pObjs.get(i).implement(pInfunction))
				.append("\n");
		}
		
		return builder.toString();
	}
	
	protected String declarePosition(List<ItemGroup> pObjs) {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < pObjs.size() ; i++) {
			builder.append("\t");
			builder.append(pObjs.get(i).declarePosition());
		}
		return builder.toString();
	}
	
	protected String implementPosition(List<ItemGroup> pObjs) {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < pObjs.size() ; i++) {
			builder.append("\t");
			builder.append(pObjs.get(i).implementPosition());
		}
		return builder.toString();
	}
	
	public void setProject(IProject project) {
		this.mProject = project;
	}
	
	public IProject getProject() {
		IProject project = mProject;
		CommonObject parent = mParent;
		while(mProject == null && parent != null) {
			project = parent.mProject;
			parent = parent.getParent();
		}
		
		return project;
	}
	
	public void setLocationInView(Point p) {
		mLocationInView = p;
		if(isNextItemInArray()) {
			mInterface.getImage().setLocationInInterfaceBuilder(p, false);
		}
	}
	
	public void setLocationInView(float x, float y) {
		setLocationInView(new Point(x, y));
	}
	
	public void setLocationInView(String location) {
		if(Validator.isValidDoubleValueString(location)) {
			String xy[] = location.split(",");
			this.setLocationInView(Float.parseFloat(xy[0]), 
					Float.parseFloat(xy[1]));
		}
	}
	
	public Point getLocationInView() {
		if(mLocationInView == null) {
			mLocationInView = mImage.getLocationInInterfaceBuilder();
		}
		return mLocationInView;
	}
	
	public String getXmlPositionName() {
		return mXmlPositionName;
	}
	
	public int getViewType() {
		return mViewType;
	}
	
	public String getTagName() {
		return this.mTagName;
	}
	
	public void setTagName(String tagName) {
		this.mTagName = tagName;
	}
	
	public Point getAnchorPoint() {
		return mAnchorPoint;
	}
	
	public List<ItemGroup> getLabelGroups() {
		return this.mLabelGroups;
	}
	
	public List<ItemGroup> getMenuGroups() {
		return this.mMenuGroups;
	}
	
	public List<ItemGroup> getSpriteGroups() {
		return this.mSpriteGroups;
	}
	
	public List<ItemGroup> getMenuItemGroups() {
		return this.mMenuItemGroups;
	}
	
	public List<ItemGroup> getTableGroups() {
		return this.mTableGroups;
	}
	
	public void setTabCount(int tabCount) {
		this.mTabCount = tabCount;
	}
	
	public int getTabCount() {
		return this.mTabCount;
	}
	
	/**
	 * to xml implement
	 * @return
	 */
	public String toXML() {
		StringBuilder builder = new StringBuilder();
		builder.append(buildXMLFromItemGroups(mSpriteGroups))
			.append(buildXMLFromItemGroups(mLabelGroups))
			.append(buildXMLFromItemGroups(mMenuGroups))
			.append(buildXMLFromItemGroups(mMenuItemGroups))
			.append(buildXMLFromItemGroups(mTableGroups));
		
		return builder.toString();
		
	}
	
	public String toXML(boolean isNextItemInArray) {
		if(isNextItemInArray) {
			return this.mInterface.toXML();
		} else {
			return this.toXML();
		}
	}
	
	private StringBuilder buildXMLFromItemGroups(List<ItemGroup> groups) {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < groups.size() ; i++) {
			builder.append(groups.get(i).toXML());
		}
		
		return builder;
	}
	
	public void setVisible(boolean visible) {
		this.mIsVisible = visible;
	}
	
	public boolean getVisible() {
		return this.mIsVisible;
	}
	
	public String getPositionNamePrefix() {
		return mPositionNamePrefix;
	}
	
	public void setReferenceCount(int rfc) {
		this.mReferenceCount = rfc;
	}
	
	public int getReferenceCount() {
		return this.mReferenceCount;
	}
	
	public void setAddToGroup(boolean isAddToGroup) {
		this.mIsAddToGroup = isAddToGroup;
	}
	
	public boolean isAddToGroup() {
		return this.mIsAddToGroup;
	}
	
	public void setNewClass(boolean isNewClass) {
		this.mIsNewClass = isNewClass;
	}
	
	public boolean isNewClass() {
		return this.mIsNewClass;
	}
	
	public String getTemplateName(boolean pInfunction) {
		String templateName = mTemplateName;
		if(mIsUnlocated) {
			templateName += " unlocated";
		}
		if(pInfunction) {
			templateName += " in function";
			mName = getInfunctionName();
		} else {
			templateName += " implementing";
		}
		
		return templateName;
	}
	
	public String fetchTemplate(boolean pInfunction) {
		String template = new FileUtils().fetchTemplate(
				getTemplateName(pInfunction), 
				getTemplateFilePath(), getProject());
		
		return template;
	}
	
	public void setInterface(Interface itf) {
		this.mInterface = itf;
	}
	
	public Interface getInterface() {
		return this.mInterface;
	}
	
	public void setNextItemInArray(boolean isItemInArray) {
		this.mIsNextItemInArray = isItemInArray;
	}
	
	public boolean isNextItemInArray() {
		return this.mIsNextItemInArray;
	}
	
	public void setGenerateClass(boolean isGenerateClass) {
		this.mIsGenerateClass = isGenerateClass;
	}
	
	public boolean isGenerateClass() {
		return this.mIsGenerateClass;
	}
	
	public void locationInViewWithPosition() {
		CommonObject parent = mParent;
		Point pos = getPosition();
		Point acp = getAnchorPoint();
		Size sz = getSize();
		float x = (pos.getX() - sz.getWidth() * acp.getX());
		float y = (pos.getY() - sz.getHeight() * (1 - acp.getY()));
		Point location = new Point(x, y);
		if(parent != null) {
			y = mParent.getSize().getHeight() - 
					(pos.getY() + sz.getHeight() * (1 - acp.getY()));
			location = new Point(x, y);
			location.add(parent.getLocationInView());
		}
		this.setLocationInView(location);
	}
	
	public void setAdvancedObject(AdvancedObject obj) {
		this.mAdvancedObject = obj;
		this.mAdvancedObject.setBasicObject(this);
	}
	
	public AdvancedObject getAdvancedObject() {
		return this.mAdvancedObject;
	}
	
	public Size getViewSize() {
		return getSize();
	}
	
	public void setImage(Image pImage) {
		this.mImage = pImage;
	}
	
	public Image getImage() {
		return this.mImage;
	}
	
	public void addCellGroup(ItemGroup cellGroup) {
		this.mCellGroups.add(cellGroup);
	}
	
	public List<ItemGroup> getCellGroups() {
		return this.mCellGroups;
	}
	
	public void setAllPropertiesForObject(CommonObject obj) {
		super.setAllPropertiesForObject(obj);
		
		obj.mTabCount = mTabCount;
		obj.mViewType = mViewType;
		obj.mReferenceCount = mReferenceCount;
		
		obj.mIsAddToGroup = mIsAddToGroup;
		obj.mIsNewClass = mIsNewClass;
		obj.mIsBackground = mIsBackground;
		obj.mIsUnlocated = mIsUnlocated;
		obj.mIsVisible = mIsVisible;
		
		obj.mPosition = mPosition;
		obj.mAnchorPoint = mAnchorPoint;
		obj.mLocationInView = mLocationInView;
		
		obj.mSize = mSize;
		
		obj.mMenuItemGroups = mMenuItemGroups;
		obj.mLabelGroups = mLabelGroups;
		obj.mSpriteGroups = mSpriteGroups;
		obj.mMenuGroups = mMenuGroups;
		obj.mTableGroups = mTableGroups;
		
		obj.mBackground = mBackground;
		obj.mParent = mParent;
		
		obj.mXmlPositionName = mXmlPositionName;
		obj.mPrefix = mPrefix;
		obj.mTagName = mTagName;
		obj.mSuffix = mSuffix;
		obj.mPositionName = mPositionName;
		obj.mName = mName;
		obj.mAnchorPointString = mAnchorPointString;
		obj.mSuper = mSuper;
		obj.mComment = mComment;
		obj.mType = mType;
		obj.mPositionString = mPositionString;
		obj.mSizeString = mSizeString;
		
		obj.mDeclareObjectName = mDeclareObjectName;
		obj.mZIndex = mZIndex;
		obj.mXmlTagName = mXmlTagName;
		obj.mPositionNamePrefix = mPositionNamePrefix;
	}
 	
	
	protected int mTabCount;
	protected int mViewType;
	protected int mReferenceCount;
	
	protected boolean mIsAddToGroup;
	protected boolean mIsNewClass;
	protected boolean mIsBackground;
	protected boolean mIsUnlocated;
	protected boolean mIsVisible;
	protected boolean mIsNextItemInArray;
	protected boolean mIsGenerateClass;
	
	protected Point mPosition;
	protected Point mAnchorPoint;
	protected Point mLocationInView;
	
	protected Size mSize;
	
	protected List<ItemGroup> mMenuItemGroups;
	protected List<ItemGroup> mLabelGroups;
	protected List<ItemGroup> mSpriteGroups;
	protected List<ItemGroup> mMenuGroups;
	protected List<ItemGroup> mTableGroups;
	protected List<ItemGroup> mCellGroups;
	
	protected CommonObject mBackground;
	protected CommonObject mParent;
	
	protected String mXmlPositionName;
	protected String mPrefix;
	protected String mTagName;
	protected String mSuffix;
	protected String mPositionName;
	protected String mName;
	protected String mAnchorPointString;
	protected String mSuper;
	protected String mComment;
	protected String mType;
	protected String mPositionString;
	protected String mSizeString;

	protected String mDeclareObjectName;
	protected String mZIndex;
	protected String mXmlTagName;
	protected String mPositionNamePrefix;
	
	protected Interface mInterface;
	
	protected AdvancedObject mAdvancedObject;
	
	protected Image mImage;
	
	protected IProject mProject;
}
