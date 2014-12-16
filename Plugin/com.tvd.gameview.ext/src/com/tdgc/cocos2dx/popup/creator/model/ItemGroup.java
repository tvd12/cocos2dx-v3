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

package com.tdgc.cocos2dx.popup.creator.model;

import java.util.ArrayList;
import java.util.List;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;
import com.tdgc.cocos2dx.popup.creator.utils.ViewUtils;
import com.tvd.gameview.ext.value.validate.Validator;

public class ItemGroup {
	public ItemGroup(int pType) {
		super();
		this.mType = pType;
		this.mItems = new ArrayList<CommonObject>();
		this.mIsArray = false;
		this.mArrayLength = 0;
		this.mValidArray = false;
		this.mReferenceCount = 0;
		this.mIsAddToView = true;
		this.mBlockComment = "comment to your source code, plz!";
	}
	
	public String declare() {
		if(mItems.size() == 0) {
			return "";
		}
		StringBuilder builder = new StringBuilder("\n");
		if(mValidArray) {
			String declareObjetName = mItems.get(0).getDeclareObjectName();
			builder.append("\t" + declareObjetName + "* " + mArrayName)
			.append(";\n");
		}
		else {
			for(int i = 0 ; i < mItems.size() ; i++) {
				builder.append("\t" + mItems.get(i).declare())
					.append("\n");
			}
		}
		return builder.toString();
	}
	
	public String implement(boolean pInfunction) {
		declare();
		if(mReferenceCount > 0) {
			return "";
		}
		
		StringBuilder builder = new StringBuilder(comment(1));
		if(mValidArray) {
			String name = mItems.get(0).getName();
			String newName = name.substring(0, name.lastIndexOf('[')) + "[i]";
			String positionName = mItems.get(0).getPositionName();
			String newPositionName = positionName.substring(0, positionName.lastIndexOf('[')) + "[i]";
			for(int i = 0 ; i < mArrayLength ; i++) {
				mItems.get(i).setName(newName);
				mItems.get(i).setNewPositionName(newPositionName);
			}
			builder.append("\tfor(int i = 0 ; i < " + mArrayLength + " ; i++) {\n");
			
			StringBuilder builderForObj = new StringBuilder();
			builderForObj.append(mItems.get(0).implement(false))
				.append("\n");
			
			ViewUtils.unlockAddingGroupToView(mItems.get(0));
			ViewUtils.implementObject(mItems.get(0), builderForObj);
			String strs[] = builderForObj.toString()
					.replace("//{n}", "\n")
					.split("\n");
			for(int i = 0 ; i < strs.length ; i++) {
				builder.append("\t" + strs[i] + "\n");
			}
			builder.append("\t}");
			
			for(int i = 0 ; i < mArrayLength ; i++) {
				String oldName = mItems.get(i).getName().replace("[i]", 
						"[" + i + "]");
				String oldPositionName = mItems.get(i).getPositionName().replace("[i]", 
						"[" + i + "]");
				mItems.get(i).setName(oldName);
				mItems.get(i).setNewPositionName(oldPositionName);
			}
			
			processArray();
		} 
		else {
			for(int i = 0  ; i < mItems.size() ; i++) {
				CommonObject item = mItems.get(i);
				if(item.getReferenceCount() > 0) {
					continue;
				}
				builder.append("\t" + item.implement(pInfunction).trim())
					.append("\n");
				builder.append("//{n}");
				item.setReferenceCount(item.getReferenceCount() + 1);
			}
		}
		String result = builder.toString();
		return (result.equals(comment(1))) 
				? "" : result;
	}
	
	public String declarePosition() {
		StringBuilder builder = new StringBuilder();
		if(mValidArray) {
			builder.append("\t")
				.append(mItems.get(0).declarePositions().trim()
					.replace(mItems.get(0).getPositionName(), mPositionArrayName))
				.append("\n");
		} else {
			for(int i = 0 ; i < mItems.size() ; i++) {
				String pos = mItems.get(i).declarePositions();
				if(!pos.trim().equals("")) {
					builder.append("\t" + pos).append("\n");
				}
			}
		}
		return builder.toString();
	}
	
	public String implementPosition() {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < mItems.size() ; i++) {
			String pos = mItems.get(i).implementPositions();
			if(!pos.trim().equals("")) {
				builder.append("\t" + pos).append("\n");
			}
		}
		
		return builder.toString();
	}
	
	public String createElementTags(int begin) {
		StringBuilder builder = new StringBuilder("\n");
		for(int i = 0 ; i < mItems.size() ; i++) {
			builder.append("\t\t" + mItems.get(i).getTagName())
			.append(" = " + (begin + i))
			.append(",\n");
		}
		return builder.toString();
	}
	
	public void pushBack() {
		switch (mType) {
		case Type.MENU:
			mContainer.addMenuGroup(this);
			mXmlTagName = Tag.MENUS;
			break;
			
		case Type.MENUITEM:
			mContainer.addMenuItemGroup(this);
			mXmlTagName = Tag.MENUITEMS;
			break;
			
		case Type.SPRITE:
			mContainer.addSpriteGroup(this);
			mXmlTagName = Tag.SPRITES;
			break;
			
		case Type.TABLE:
			mContainer.addTableGroup(this);
			mXmlTagName = Tag.TABLES;
			break;
			
		case Type.LABLE:
			mContainer.addLabelGroup(this);
			mXmlTagName = Tag.LABELS;
			break;
		case Type.CELL:
			mContainer.addCellGroup(this);
			break;
		default:
			break;
		}
		if(mIsArray && mArrayLength > 0 && mItems.size() > 0) {
			ViewUtils.blockAddingGroupToView(mItems.get(0));
		}
		
	}
	
	public void update() {
		if(!mValidArray) {
			checkArray();
		}
	}
	
	protected boolean checkArray() {
		if(mIsArray && mArrayLength > 0) {
			mValidArray = true;
			if(mItems.size() < mArrayLength) {
				addNewItemToArray();
			}
			processArray();
		}
		
		return mValidArray;
	}
	
	private void addNewItemToArray() {
		if(mValidArray) {
			CommonObject obj = mItems.get(0);
			for(int i = 1 ; i < mArrayLength ; i++) {
				CommonObject newObj = obj.clone();
				Image img = new Image();
				img.setId(obj.getXmlPositionName() + "_" 
						+ mItems.size());
				img.setSize(obj.getSize());
				img.setLocationInInterfaceBuilder(
						img.getLocationInInterfaceBuilder());
				new Interface(newObj, img);
				newObj.setNextItemInArray(true);
				addItem(newObj);
			}
			mValidArray = true;
		} 
	}
	
	private void processArray() {
		if(mValidArray) {
			CommonObject obj = mItems.get(0);
			this.mArrayName = obj.getName() + "s[" + mArrayLength + "]";
			this.mPositionArrayName = obj.getPositionName()
					+ "S[" + mArrayLength + "]";
			for(int i = 1 ; i < mArrayLength ; i++) {
				CommonObject newObj = mItems.get(i);
				newObj.setName(newObj.getName() + "s[" + i + "]");
				newObj.setNewPositionName(newObj.getPositionName() + "S[" + i + "]");
				newObj.setTagName(newObj.getTagName() + i);
			}
			obj.setName(obj.getName() + "s[0]");
			obj.setNewPositionName(obj.getPositionName() + "S[0]");
			mValidArray = true;
		} 
	}
	
	public String createExtendFunction() {
		if(mResources != null) {
		}
		return "";
	}
	
	public void addItem(CommonObject pObject) {
		if(mIsArray && mItems.size() > mArrayLength - 1) {
			return;
		}
		this.mItems.add(pObject);
		pObject.setTabCount(mTabCount + 1);
	}
	
	public void setBlockComment(String pBlockComment) {
		this.mBlockComment = pBlockComment;
	}
	
	public void setResources(Resource pResources) {
		this.mResources = pResources;
	}
	
	public String getBlockComment() {
		return this.mBlockComment;
	}
	
	public Resource getResources() {
		return this.mResources;
	}
	
	public void setIsArray(boolean pIsArray) {
		this.mIsArray = pIsArray;
	}
	
	public void setIsArray(String isArray) {
		if(isArray != null) {
			setIsArray(Boolean.parseBoolean(isArray));
		}
	}
	
	public boolean isArray() {
		return this.mIsArray;
	}
	
	public void setType(int pType) {
		this.mType = pType;
	}
	
	public int getType() {
		return this.mType;
	}
	
	public void setContainer(CommonObject pContainer) {
		this.mContainer = pContainer;
		this.mTabCount = mContainer.getTabCount() + 1;
	}
	
	public CommonObject getContainer() {
		return this.mContainer;
	}
	
	public void setBeforeGroup(ItemGroup pBeforeGroup) {
		this.mBeforeGroup = pBeforeGroup;
	}
	
	public ItemGroup getBeforeGroup() {
		if(this.mBeforeGroup != null) {
			return this.mBeforeGroup;
		} else {
			return this;
		}
	}
	
	public String getNodesArrayName() {
		return this.mNodesArrayName;
	}
	
	public List<CommonObject> getItems() {
		return this.mItems;
	}
	
	public void setArrayLength(int length) {
		mArrayLength = length;
	}
	
	public void setArrayLength(String length) {
		if(length != null && Validator.isNumeric(length)) {
			setArrayLength(Integer.parseInt(length));
		}
	}
	
	public int getArrayLength() {
		return this.mArrayLength;
	}
	
	public void setReferenceCount(int rfc) {
		mReferenceCount = rfc;
	}
	
	public interface Type {
		public static final int MENU 		= 1000;
		public static final int MENUITEM 	= 1001;
		public static final int SPRITE 		= 1002;
		public static final int TABLE 		= 1003;
		public static final int LABLE 		= 1004;
		public static final int VIEW 		= 1005;
		public static final int RESOURCE 	= 1006;
		public static final int PROGRESSBAR = 1007;
		public static final int CELL		= 1008;
	}
	
	private String comment(int pNumberOfTab) {
		String tab = StringUtils.tab(pNumberOfTab);
		StringBuilder builder = new StringBuilder();
		builder.append(tab + "//" + mBlockComment + "\n");
		
		return builder.toString();
	}
	
	public String toXML() {
		String comment = "create group of " + mXmlTagName; 
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " " + Attribute.ARRAY + "=\"" + mIsArray + "\" ");
		if(mArrayLength > 1) {
			builder.append(Attribute.LENGTH + "=\"" + mArrayLength + "\" ");
		}
		builder.append(Attribute.COMMENT + "=\"" + comment + "\">")
			.append("\n");
		for(int i = 0 ; i < mItems.size() ; i++) {
			CommonObject item = mItems.get(i);
			builder.append(item.toXML(item.isNextItemInArray()));
		}
		builder.append(tab + "</" + mXmlTagName + ">").append("\n");
		
		return builder.toString();
	}
	
	public CommonObject createNewItem(boolean addToGroup) {
		CommonObject obj = null;
		switch (mType) {
		case Type.MENU:
			obj = new Menu();
			break;
			
		case Type.MENUITEM:
			obj = new MenuItem();
			break;
			
		case Type.SPRITE:
			obj = new Sprite();
			break;
			
		case Type.TABLE:
			obj = new Table();
			break;
			
		case Type.LABLE:
			obj = new Label();
			break;
		default:
			break;
		}
		if(addToGroup) {
			this.addItem(obj);
		}
		return obj;
	}
	
	public CommonObject createNewItem() {
		return createNewItem(false);
	}
	
	public int getTabCount() {
		return mTabCount;
	}
	
	public void setTabCount(int tabCount) {
		mTabCount = tabCount;
	}
	
	public void setAddToView(boolean addToView) {
		this.mIsAddToView = addToView;
	}
	
	public boolean isAddToView() {
		return this.mIsAddToView;
	}
	
	public CommonObject cloneFromTheFirstItem() {
		if(mItems.size() > 0) {
			return mItems.get(0).clone();
		}
		
		return null;
	}
	
	protected int mTabCount;
	protected List<CommonObject> mItems;
	protected String mBlockComment;
	protected Resource mResources;
	protected boolean mIsArray;
	protected int mType;
	protected CommonObject mContainer;
	protected ItemGroup mBeforeGroup;
	protected String mNodesArrayName;
	protected int mArrayLength;
	protected boolean mValidArray;
	protected String mArrayName;
	protected String mPositionArrayName;
	protected boolean mIsAddToView;
	
	private int mReferenceCount;
	private String mXmlTagName;
}
