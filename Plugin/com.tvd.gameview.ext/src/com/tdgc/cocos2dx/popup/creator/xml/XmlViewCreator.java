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

package com.tdgc.cocos2dx.popup.creator.xml;

import java.util.List;

import com.tdgc.cocos2dx.popup.creator.constants.Strings;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.file.FileParser;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.AdvancedCell;
import com.tdgc.cocos2dx.popup.creator.model.Cell;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.ItemGroup;
import com.tdgc.cocos2dx.popup.creator.model.Menu;
import com.tdgc.cocos2dx.popup.creator.model.MenuItem;
import com.tdgc.cocos2dx.popup.creator.model.Progressbar;
import com.tdgc.cocos2dx.popup.creator.model.Resource;
import com.tdgc.cocos2dx.popup.creator.model.Sprite;
import com.tdgc.cocos2dx.popup.creator.model.Table;
import com.tdgc.cocos2dx.popup.creator.model.View;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class XmlViewCreator {
	
	public XmlViewCreator(String pInputPath) {
		this.mInputPath = pInputPath;
	}
	
	public XmlViewCreator(String pInputPath, String pDevice) {
		this(pInputPath);
		this.mDevice = pDevice;
		this.mInterfaceBuilder = "";
	}
	
	public XmlViewCreator(String pInputPath, String pDevice, String pInterfaceBuilder) {
		this(pInputPath, pDevice);
		this.mInterfaceBuilder = pInterfaceBuilder;
	}
	
	public XmlViewCreator(String pInputPath, String pType, String pDevice, 
			String pInterfaceBuilder) {
		this(pInputPath, pDevice, pInterfaceBuilder);
		this.mType = pType;
	}
	
	public View fetchView() {
		FileParser parser = new FileParser(mInputPath);
		mFilePaths = parser.getFilePaths(true);
		mRootPath = mFilePaths.get(0);
		mView = createView(mRootPath);

		createBackgroundImage(mView);
		createResource(mView);
		
		createNextItems(mView, 0, true);
		mView.update();
		
		return mView;
	}
	
	private View createView(String fullPath) {
		View view = new View();
		String type = fullPath.substring(fullPath.lastIndexOf("_") + 1);
		fullPath = (type.trim().equals(mType)) ? fullPath : fullPath + "_" + mType;
		view.setClassName(StringUtils.convertToClassName(fullPath, 
				Config.getInstance().getDefaultViewSuffix()));
		view.setSuper(Strings.DEFAULT);
		view.setBackgroundName(Strings.DEFAULT);
		view.setSize(Config.getInstance().getDefaultScreenSizeString(mDevice));
		
		view.setPrefix(StringUtils.detectPrefix(type) + "_" +
				fullPath.substring(0, fullPath.lastIndexOf("_")));
		view.setType(mType);
		view.setComment("");
		view.setPositionName(StringUtils.getSpritePostionName(
				StringUtils.getObjectPositioName(fullPath)));
		view.setPosition(Strings.DEFAULT);
		view.setDefinePath(Config.getInstance().getDefinePath());
		view.setParametersPath(Config.getInstance().getParametersPath());
		view.setImagesInputPath(Config.getInstance().getImagesInputPath());
		view.setImagesPath(Config.getInstance().getImagesPath() + "/" + mDevice);
		view.setXibContainerPath(Config.getInstance().getXibContainerPath() + "/" + mDevice);
		view.setScreenContainerPath(Config.getInstance().getScreenContainerPath() + "/" + mDevice);
		view.setAndroidContainerPath(Config.getInstance().getAndroidContainerPath() + "/" + mDevice);
		view.setInterfaceBuilder(mInterfaceBuilder);
		view.setClassPath(Config.getInstance().getClassPath());
		
		return view;
	}
	
	private void createBackgroundImage(View view) {
		String backgroundPath = mRootPath + "/background";
		for(int i = 1 ; i < mFilePaths.size() ; i++) {
			String fullPath = mFilePaths.get(i).trim();
			if(fullPath.equals(backgroundPath)) {
				mFilePaths.remove(i);
				Image image = createImageItem(view, mFilePaths.get(i));
				image.setXMLTagName(Tag.BACKGROUND_IMAGE);
				view.setBackgroundImage(image);
				mFilePaths.remove(i);
				return;
			}
		}
	}
	
	private void createResource(View view) {
		String resourcePath = mRootPath + "/resource";
		for(int i = 1 ; i < mFilePaths.size() ; i++) {
			String fullPath = mFilePaths.get(i).trim();
			if(fullPath.equals(resourcePath)) {
				mFilePaths.remove(i);
				Resource resource = new Resource();
				resource.setTabCount(view.getTabCount() + 1);
				while(i < mFilePaths.size()
						&& mFilePaths.get(i).contains(fullPath)) {
					String filePath = mFilePaths.get(i);
					if(filePath.endsWith(".png")) {
						Image img = new Image(filePath);
						img.setAddToInterfaceBuilder(false);
						resource.addImage(img);
					}
					mFilePaths.remove(i);
				} 
				view.addResource(resource);
				return;
			}
		} 
	}
	
	/**
	 * 
	 * @param pParent
	 * @param pParentPath
	 * @param pSetPosition
	 * 
	 * sprites
	 * 		sprite
	 * 			image
	 * 			sprites
	 */
	private void createSpriteItems(CommonObject pParent, String pParentPath,
			boolean pSetPosition) {
		ItemGroup items = createItemGroup(pParent, ItemGroup.Type.SPRITE);
		Sprite sprite = null;
		for(int i = 0 ; i < mFilePaths.size() ;) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createSpriteItems::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			} else if(fullPath.endsWith(Tag.PROGRESSBAR)) {
				mFilePaths.remove(i);
				createProgressbarItem(sprite, fullPath);
				continue;
			} 
			sprite = new Sprite();
			sprite.setParent(pParent);
			items.addItem(sprite);
			sprite.setVisible(true);
			sprite.setIsBackground(false);
			sprite.setComment("");
			
			if(pSetPosition) {
				sprite.setAnchorPoint(Strings.DEFAULT);
				sprite.setPosition(50, 50);
			} 
			else  {
				sprite.setIsUnlocated(true);
			}
			String posName = StringUtils.getSpritePostionName(fullPath);
			sprite.setPositionName(mType, posName);
			sprite.setZIndex(0);
			if(!fullPath.endsWith(".png")) {
				createImageTag(sprite, fullPath);
				createNextItems(sprite, i, true);
			} else if(fullPath.endsWith(".png")) {
				Image image = createImageItem(sprite, fullPath);
				sprite.setImage(image);
				mFilePaths.remove(i);
				
			}
		}
//		createNextItems(pParent, 0, false);
	}
	
	private void createMenuItemItems(CommonObject pParent, String pParentPath) {
//		System.out.println("createMenuItemItems::parentpath = " + pParentPath);
		ItemGroup items = createItemGroup(pParent, ItemGroup.Type.MENUITEM);
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
//			System.out.println("createMenuItemItems::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			MenuItem item = (MenuItem)createItem(Tag.MENUITEM, fullPath, items);
			item.setParent(pParent);
			item.setTabCount(items.getTabCount() + 1);
			createNextItems(item, i, true, false);
			item.update();
		}
//		createNextItems(pParent, 0, false);
	}
	
	private void createMenuItems(CommonObject pParent, String pParentPath) {
		ItemGroup items = createItemGroup(pParent, ItemGroup.Type.MENU);
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
//			System.out.println("createMenuItems::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			Menu item = (Menu)createItem(Tag.MENU, fullPath, items);
			item.setParent(pParent);
			item.setTabCount(items.getTabCount() + 1);
			createNextItems(item, i, true);
			item.update();
		}
//		createNextItems(pParent, 0, false);
	}
	
	private void createTableItems(CommonObject pParent, String pParentPath) {
		ItemGroup items = createItemGroup(pParent, ItemGroup.Type.TABLE);
		
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
//			System.out.println("createTableItems::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			Table item = (Table)createItem(Tag.TABLE, fullPath, items, "5, 10");
			item.setParent(pParent);
			item.setSize(200, 250);
			Image image = new Image();
			image.setParent(item);
			image.setId(StringUtils.convertPhonyPathToId(
					fullPath + "/background"));
			image.setSize(200, 250);
			item.setTabCount(items.getTabCount() + 1);
			image.setTabCount(item.getTabCount() + 1);
			item.setImage(image);
			item.setRows(1);
			item.setColumns(1);
			item.setComment("");
			
			mFilePaths.remove(i);
			createCellItem(item, fullPath);
			break;
		}
//		createNextItems(pParent, 0, false);
	}
	
	private void createCellItem(CommonObject pParent, String pParentPath) {
		Cell item = new Cell();
		item.setParent(pParent);
		
		//add basic Item
		item.setAnchorPoint(Strings.DEFAULT);
		item.setPosition(50, 50);
		item.setSize(200, 100);
		Image image = new Image();
		image.setParent(item);
		image.setId(StringUtils.convertPhonyPathToId(
				pParentPath + "/cell/background"));
		image.setSize(200, 100);
		image.setTabCount(item.getTabCount() + 1);
		item.setImage(image);
		
		//add attributes
		AdvancedCell adCell = (AdvancedCell)item.getAdvancedObject();
		adCell.setClassName(StringUtils.convertToClassName(mRootPath + "_cell", "View"));
		adCell.setSuper("default");
		adCell.setPrefix(StringUtils.detectPrefix("cell") + "_" +
				mRootPath);
		item.setComment("");
		item.setParent(pParent);
		
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
//			System.out.println("createCellItems::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			createNextItems(item, i, true);
			break;
		}
	}
	
	private void createProgressbarItem(CommonObject pParent, String pParentPath) {
		Progressbar item = new Progressbar();
		item.setParent(pParent);
		item.setComment("");
		item.setParent(pParent);
		
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createProgressbarItem::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			Sprite sprite = new Sprite();
			item.setSprite(sprite);
			sprite.setParent(item);
			
			String posName = StringUtils.getSpritePostionName(fullPath);
			sprite.setPositionName(mType, posName);
			item.setPositionName(mType, posName);
			sprite.setImage(createImageItem(sprite, fullPath));
			item.getSprite().getImage().setAddToInterfaceBuilder(false);
			createNextItems(sprite, i, true);
			break;
		}
	}
	
	@SuppressWarnings("unused")
	private void createResourceItem(CommonObject pParent, String pParentPath) {
	}
	
	public String getOutputFileName() {
		
//		System.out.println("root = " + mRootPath);
		return mRootPath + ".xml";
	}
	
	private ItemGroup createItemGroup(CommonObject pParent, int pType, boolean addGroup) {
		ItemGroup group = new ItemGroup(pType);
		group.setIsArray(false);
		if(addGroup) { 
			pParent.addItemGroup(group);
		}
		group.setTabCount(pParent.getTabCount() + 1);
		
		return group;
	}
	
	private ItemGroup createItemGroup(CommonObject pParent, int pType) {
		return createItemGroup(pParent, pType, true);
	}
	
	private CommonObject createItem(String pTag, String pFullPath, ItemGroup pGroup) {
		return createItem(pTag, pFullPath, pGroup, "0, 0");
	}
	
	private CommonObject createItem(String pTag, String pFullPath, ItemGroup pGroup,
			String pPositionString) {
		CommonObject item = pGroup.createNewItem(true);
		item.setComment("");
		item.setPositionName(mType, StringUtils.getObjectPositioName(pFullPath));
		item.setAnchorPoint("default");
		item.setPosition(pPositionString);
		item.setZIndex(0);
		item.setTabCount(pGroup.getTabCount() + 1);
		
		return item;
	}
	
	private boolean createNextItems(CommonObject pParent, int pIndexOfPath, 
			boolean pDeleteParentPath, boolean pSetPosition) {
		if(mFilePaths.size() == 0) {
			return false;
		}
		String parentPath = mFilePaths.get(pIndexOfPath);
		if(pDeleteParentPath) {
			mFilePaths.remove(pIndexOfPath);
		}
		for(int i = 0 ; i < mFilePaths.size() ;) {
			String fullPath = mFilePaths.get(i).trim();
//			System.out.println("createNextItems::fullpath = " + fullPath
//					+ " " + pDeleteParentPath);
			if(fullPath.equals(parentPath + "/" + Tag.SPRITES)) {
				this.mFilePaths.remove(i);
				createSpriteItems(pParent, fullPath, pSetPosition);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.TABLES)) {
				this.mFilePaths.remove(i);
				createTableItems(pParent, fullPath);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.MENUS)) {
				this.mFilePaths.remove(i);
				createMenuItems(pParent, fullPath);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.MENUITEMS)) {
				this.mFilePaths.remove(i);
				createMenuItemItems(pParent, fullPath);
			} 
			else {
				i++;
			}
		}
		return true;
	}
	
	protected boolean createNextItems(CommonObject pParent, int pIndexOfPath, 
			boolean pDeleteParentPath) {
		return createNextItems(pParent, pIndexOfPath, pDeleteParentPath, true);
	}
	
	protected void createImageTag(CommonObject parent, String parentPath) {
		for(int i = 1 ; i < mFilePaths.size() ; i++) {
			String fullPath = mFilePaths.get(i);
			int lastIndexOfParentPath = fullPath.indexOf(parentPath) 
					+ parentPath.length() + 1;
			String imageName = fullPath.substring(lastIndexOfParentPath);
//			System.out.println("imageName = " + imageName);
			if(!imageName.contains("/") && imageName.endsWith(".png")) {
				Image image = createImageItem(parent, fullPath);
				if(parent instanceof Sprite) {
					((Sprite)parent).setImage(image);
				}
				mFilePaths.remove(i);
				
				return;
			}
		}
	}
	
	protected Image createImageItem(CommonObject parent, String phonyPath) {
		Image image = new Image();
		image.setParent(parent);
		image.setId(StringUtils.convertPhonyPathToId(phonyPath));
		image.setPhonyPath(phonyPath);
		image.setTabCount(parent.getTabCount() + 1);
		image.fetchSize(mInputPath.substring(0, mInputPath.lastIndexOf('/')) 
				+ "/" + phonyPath);
		
		return image;
	}
	
	@SuppressWarnings("unused")
	private String checkGroup(String fullPath) {
		if(fullPath.endsWith(Tag.SPRITES)) {
			return Tag.SPRITES;
		} else if(fullPath.endsWith(Tag.TABLES)) {
			return Tag.TABLES;
		}
		
		return null;
	}
	
	private List<String> mFilePaths;
	private String mInputPath;
	private String mDevice;
	private String mInterfaceBuilder;
	private String mRootPath;
	private View mView;
	private String mType;
}