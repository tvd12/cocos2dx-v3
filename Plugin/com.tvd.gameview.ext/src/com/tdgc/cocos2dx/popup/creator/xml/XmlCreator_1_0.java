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

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Constants;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.file.FileParser;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class XmlCreator_1_0 {
	
	public XmlCreator_1_0(String pInputPath) {
		this.mInputPath = pInputPath;
	}
	
	public XmlCreator_1_0(String pInputPath, String pDevice) {
		this(pInputPath);
		this.mDevice = pDevice;
		this.mInterfaceBuilder = "";
	}
	
	public XmlCreator_1_0(String pInputPath, String pDevice, String pInterfaceBuilder) {
		this(pInputPath, pDevice);
		this.mInterfaceBuilder = pInterfaceBuilder;
	}
	
	public Document parseFilePaths() {
		FileParser parser = new FileParser(mInputPath);
		mFilePaths = parser.getFilePaths(true);
		mRootPath = mFilePaths.get(0);
		
		DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder docBuilder;

		try {
			docBuilder = docFactory.newDocumentBuilder();
			
			// root elements
			mDocument = docBuilder.newDocument();
			Element rootElement = createRootElement(mFilePaths.get(0));
			mDocument.appendChild(rootElement);
			
			createBackgroundImageElement(rootElement);
			createNextElements(rootElement, 0, true);
			
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		}
 
		return mDocument;
	}
	
	private Element createRootElement(String pStr) {
		Element rootElement = mDocument.createElement(Tag.VIEW);
		
		
		rootElement.setAttribute(Attribute.CLASS_NAME, 
				StringUtils.convertToClassName(pStr, "View"));
		rootElement.setAttribute(Attribute.SUPER, "default");
		String type = pStr.substring(pStr.lastIndexOf("_") + 1);
		rootElement.setAttribute(Attribute.PREFIX,
				StringUtils.detectPrefix(type) + "_" +
				pStr.substring(0, pStr.lastIndexOf("_")));
		rootElement.setAttribute(Attribute.TYPE, 
				type);
		
		rootElement.setAttribute(Attribute.COMMENT, "");
		
//		rootElement.setAttribute("xmlns", "http://www.tvd.com/tools" );
//		rootElement.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance" );
//		rootElement.setAttribute("xsi:schemaLocation", "http://www.tvd.com/tools ../xsd/view.xsd");
		
		Element positionName = mDocument.createElement(Tag.POSITION_NAME);
		positionName.appendChild(mDocument.createTextNode("default"));
		rootElement.appendChild(positionName);
		
		Element position = mDocument.createElement(Tag.POSITION);
		position.appendChild(mDocument.createTextNode("default"));
		rootElement.appendChild(position);
		
		Element definePath = mDocument.createElement(Tag.DEFINE_PATH);
		definePath.appendChild(mDocument.createTextNode(
				Config.getInstance().getDefinePath()));
		rootElement.appendChild(definePath);
		
		Element parametersPath = mDocument.createElement(Tag.PARAMETERS_PATH);
		parametersPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getParametersPath()));
		rootElement.appendChild(parametersPath);
		
		Element imagesInputPath = mDocument.createElement(Tag.IMAGES_INPUTPATH);
		imagesInputPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getImagesInputPath()));
		rootElement.appendChild(imagesInputPath);
		
		Element imagesPath = mDocument.createElement(Tag.IMAGES_PATH);
		imagesPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getImagesPath() + "/" + mDevice));
		rootElement.appendChild(imagesPath);
		
		Element xibContainerPath = mDocument.createElement(Tag.XIBCONTAINER_PATH);
		xibContainerPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getXibContainerPath() + "/" + mDevice));
		rootElement.appendChild(xibContainerPath);
		
		Element screenContainerPath = mDocument.createElement(Tag.SCREENCONTAINER_PATH);
		screenContainerPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getScreenContainerPath() + "/" + mDevice));
		rootElement.appendChild(screenContainerPath);
		
		Element androidContainerPath = mDocument.createElement(Tag.ANDROIDCONTAINER_PATH);
		androidContainerPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getAndroidContainerPath() + "/" + mDevice));
		rootElement.appendChild(androidContainerPath);
		
		if(mInterfaceBuilder.equals(Constants.XIB)) {
			xibContainerPath.setAttribute("used", "true");
		} else if(mInterfaceBuilder.equals(Constants.SCREEN)) {
			screenContainerPath.setAttribute("used", "true");
		} else if(mInterfaceBuilder.equals(Constants.ANDROID)) {
			androidContainerPath.setAttribute("used", "true");
		}
		
		Element classPath = mDocument.createElement(Tag.CLASS_PATH);
		classPath.appendChild(mDocument.createTextNode(
				Config.getInstance().getClassPath()));
		rootElement.appendChild(classPath);
		
		return rootElement;
	}
	
	private void createBackgroundImageElement(Element pRoot) {
		String backgroundPath = mRootPath + "/background";
		for(int i = 1 ; i < mFilePaths.size() ; i++) {
			String fullPath = mFilePaths.get(i).trim();
			if(fullPath.equals(backgroundPath)) {
				mFilePaths.remove(i);
				Element image = mDocument.createElement("image");
				pRoot.appendChild(image);
				image.setAttribute("id", StringUtils.convertPhonyPathToId(mFilePaths.get(i)));
				image.setAttribute(Attribute.PHONY_PATH, mFilePaths.get(i));
//				image.appendChild(mDocument.createTextNode(createTextNodeWithTabs(
//						image, mFilePaths.get(i))));
				mFilePaths.remove(i);
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
	private void createSpriteElements(Element pParent, String pParentPath,
			boolean pSetPosition) {
		Element items = createGroupElement(pParent, Tag.SPRITES);
		if(items == null) {
			return;
		}
		for(int i = 0 ; i < mFilePaths.size() ;) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createSpriteElements::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			String posName = StringUtils.getSpritePostionName(fullPath);
			Element sprite = mDocument.createElement(Tag.SPRITE);
			items.appendChild(sprite);
			sprite.setAttribute(Attribute.VISIBLE, "true");
			sprite.setAttribute(Attribute.BACKGROUND, "false");
			sprite.setAttribute(Attribute.COMMENT, "");
			
			Element positionName = mDocument.createElement(Tag.POSITION_NAME);
			positionName.appendChild(mDocument.createTextNode(posName));
			if(pSetPosition) {
				Element anchorPoint = mDocument.createElement(Tag.ANCHORPOINT);
				anchorPoint.appendChild(mDocument.createTextNode("default"));
				sprite.appendChild(anchorPoint);
				
				Element position = mDocument.createElement(Tag.POSITION);
				position.appendChild(mDocument.createTextNode("0, 0"));
				sprite.appendChild(position);
			} 
			else  {
				positionName.setAttribute(Attribute.UNLOCATED, "true");
			}
			
			sprite.appendChild(positionName);
			
			Element zindex = mDocument.createElement(Tag.Z_INDEX);
			zindex.appendChild(mDocument.createTextNode("0"));
			sprite.appendChild(zindex);
			
			
			if(!fullPath.contains(".png")) {
				createImageTag(sprite, fullPath);
				createNextElements(sprite, i, true);
			} else if(fullPath.contains(".png")) {
				Element image = mDocument.createElement("image");
				sprite.appendChild(image);
				image.setAttribute("id", StringUtils.convertPhonyPathToId(fullPath));
				image.setAttribute(Attribute.PHONY_PATH, fullPath);
//				image.appendChild(mDocument.createTextNode(
//						createTextNodeWithTabs(image, fullPath)));
				mFilePaths.remove(i);
				
			}
		}
		createNextElements(pParent, 0, false);
	}
	
	private void createMenuItemElements(Element pParent, String pParentPath) {
		System.out.println("createMenuItemElements::parentpath = " + pParentPath);
		Element items = createGroupElement(pParent, Tag.MENUITEMS);
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createMenuItemElements::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			System.out.println("call from 1");
			Element element = createElement(Tag.MENUITEM, fullPath, items);
			createNextElements(element, i, true, false);
		}
		System.out.println("call from 2");
		createNextElements(pParent, 0, false);
	}
	
	private void createMenuElements(Element pParent, String pParentPath) {
		Element items = createGroupElement(pParent, Tag.MENUS);
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createMenuElements::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			Element element = createElement(Tag.MENU, fullPath, items);
			createNextElements(element, i, true);
		}
		createNextElements(pParent, 0, false);
	}
	
	private void createTableElements(Element pParent, String pParentPath) {
		Element items = createGroupElement(pParent, Tag.TABLES);
		
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createTableElements::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			Element element = createElement(Tag.TABLE, fullPath, items, "5, 10");
			Element sizeElement = mDocument.createElement(Tag.SIZE);
			sizeElement.appendChild(mDocument.createTextNode(300 + ", " + 350));
			element.appendChild(sizeElement);
			Element imageElement = mDocument.createElement(Tag.IMAGE);
			imageElement.setAttribute(Attribute.ID, StringUtils.convertPhonyPathToId(
					fullPath + "/background"));
			imageElement.setAttribute(Attribute.WIDTH, "300");
			imageElement.setAttribute(Attribute.HEIGHT, "350");
			element.appendChild(imageElement);
			
			element.setAttribute(Attribute.ROWS, "1");
			element.setAttribute(Attribute.COLUMNS, "1");
			element.setAttribute("comment", "");
			mFilePaths.remove(i);
			createCellElements(element, fullPath);
			break;
		}
		createNextElements(pParent, 0, false);
	}
	
	private void createCellElements(Element pParent, String pParentPath) {
		Element element = mDocument.createElement(Tag.CELL);
		
		//add basic element
		Element anchorPoint = mDocument.createElement(Tag.ANCHORPOINT);
		anchorPoint.appendChild(mDocument.createTextNode("default"));
		element.appendChild(anchorPoint);
			
		Element position = mDocument.createElement(Tag.POSITION);
		position.appendChild(mDocument.createTextNode("50, 50"));
		element.appendChild(position);
		
		Element sizeElement = mDocument.createElement(Tag.SIZE);
		sizeElement.appendChild(mDocument.createTextNode(200 + ", " + 100));
		element.appendChild(sizeElement);
		
		//add image element
		Element imageElement = mDocument.createElement(Tag.IMAGE);
		imageElement.setAttribute(Attribute.ID, StringUtils.convertPhonyPathToId(
				pParentPath + "/cell/background"));
		imageElement.setAttribute(Attribute.WIDTH, "200");
		imageElement.setAttribute(Attribute.HEIGHT, "100");
		element.appendChild(imageElement);
		
		//add attributes
		element.setAttribute(Attribute.CLASS_NAME, 
				StringUtils.convertToClassName(mRootPath + "_cell", "View"));
		element.setAttribute(Attribute.SUPER, "default");
		element.setAttribute(Attribute.PREFIX,
				StringUtils.detectPrefix("cell") + "_" +
				mRootPath);
		element.setAttribute("comment", "");
		pParent.appendChild(element);
		
		for(int i = 0 ; i < mFilePaths.size() ; ) {
			String fullPath = mFilePaths.get(i);
			System.out.println("createCellElements::fullpath = " + fullPath);
			if(!fullPath.contains(pParentPath)) {
				break;
			}
			createNextElements(element, i, true);
			break;
		}
	}
	
	@SuppressWarnings("unused")
	private void createResourceElement(Element pParent, String pParentPath) {
		Element items = mDocument.createElement(Tag.RESOURCE);
		items.setAttribute(Attribute.NAME, "ItemGroup");
		items.setAttribute(Attribute.COMMENT, "create resources");
		pParent.appendChild(items);
	}
	
	public String getOutputFileName() {
		return mRootPath + ".xml";
	}
	
	@SuppressWarnings("unused")
	private String createTextNodeWithTabs(Node pParent, String pText) {
		StringBuilder builder = new StringBuilder();
		int numberOfParent = 0;
		while(pParent != null) {
			numberOfParent ++;
			pParent = pParent.getParentNode();
		}
		String tabs = StringUtils.tab(numberOfParent - 2);
		builder.append("\n")
			.append(tabs)
			.append("\t" + pText)
			.append("\n")
			.append(tabs);
		
		return builder.toString();
	}
	
	private Element createGroupElement(Element pParent, String pGroupName) {
		Element group = mDocument.createElement(pGroupName);
		group.setAttribute("array", "false");
		group.setAttribute(Attribute.COMMENT, "create group of elements");
		pParent.appendChild(group);
		
		return group;
	}
	
	private Element createElement(String pTag, String pFullPath, Element pGroup) {
		return createElement(pTag, pFullPath, pGroup, "0, 0");
	}
	
	private Element createElement(String pTag, String pFullPath, Element pGroup,
			String pPositionString) {
		Element element = mDocument.createElement(pTag);
		element.setAttribute("comment", "");
		
		String posName = StringUtils.getObjectPositioName(pFullPath);
		Element positionName = mDocument.createElement(Tag.POSITION_NAME);
		positionName.appendChild(mDocument.createTextNode(posName));
		element.appendChild(positionName);
			
		Element anchorPoint = mDocument.createElement(Tag.ANCHORPOINT);
		anchorPoint.appendChild(mDocument.createTextNode("default"));
		element.appendChild(anchorPoint);
			
		Element position = mDocument.createElement(Tag.POSITION);
		position.appendChild(mDocument.createTextNode(pPositionString));
		element.appendChild(position);
		
		Element zindex = mDocument.createElement(Tag.Z_INDEX);
		zindex.appendChild(mDocument.createTextNode("0"));
		element.appendChild(zindex);
		
		pGroup.appendChild(element);
		
		return element;
	}
	
	private boolean createNextElements(Element pParent, int pIndexOfPath, 
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
			System.out.println("createNextElements::fullpath = " + fullPath
					+ " " + pDeleteParentPath);
			if(fullPath.equals(parentPath + "/" + Tag.SPRITES)) {
				this.mFilePaths.remove(i);
				createSpriteElements(pParent, fullPath, pSetPosition);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.TABLES)) {
				this.mFilePaths.remove(i);
				createTableElements(pParent, fullPath);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.MENUS)) {
				this.mFilePaths.remove(i);
				createMenuElements(pParent, fullPath);
			} 
			else if(fullPath.equals(parentPath + "/" + Tag.MENUITEMS)) {
				this.mFilePaths.remove(i);
				createMenuItemElements(pParent, fullPath);
			}
			else {
				i++;
			}
		}
		return true;
	}
	
	protected boolean createNextElements(Element pParent, int pIndexOfPath, 
			boolean pDeleteParentPath) {
		return createNextElements(pParent, pIndexOfPath, pDeleteParentPath, true);
	}
	
	protected void createImageTag(Element parent, String parentPath) {
		for(int i = 1 ; i < mFilePaths.size() ; i++) {
			String fullPath = mFilePaths.get(i);
			int lastIndexOfParentPath = fullPath.indexOf(parentPath) 
					+ parentPath.length() + 1;
			String imageName = fullPath.substring(lastIndexOfParentPath);
			System.out.println("imageName = " + imageName);
			if(!imageName.contains("/") && imageName.endsWith(".png")) {
				Element image = mDocument.createElement(Tag.IMAGE);
				parent.appendChild(image);
				image.setAttribute(Attribute.ID, StringUtils.convertPhonyPathToId(fullPath));
				image.setAttribute(Attribute.PHONY_PATH, fullPath);
//				image.appendChild(mDocument.createTextNode(createTextNodeWithTabs(image, fullPath)));
				mFilePaths.remove(i);
				
				return;
			}
		}
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
	private Document mDocument;
	private String mInputPath;
	private String mDevice;
	private String mInterfaceBuilder;
	private String mRootPath;
}