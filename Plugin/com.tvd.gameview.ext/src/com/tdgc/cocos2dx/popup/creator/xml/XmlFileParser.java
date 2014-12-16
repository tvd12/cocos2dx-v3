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

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Constants;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.model.AdvancedCell;
import com.tdgc.cocos2dx.popup.creator.model.Cell;
import com.tdgc.cocos2dx.popup.creator.model.IContainer;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.ItemGroup;
import com.tdgc.cocos2dx.popup.creator.model.Label;
import com.tdgc.cocos2dx.popup.creator.model.Menu;
import com.tdgc.cocos2dx.popup.creator.model.MenuItem;
import com.tdgc.cocos2dx.popup.creator.model.Progressbar;
import com.tdgc.cocos2dx.popup.creator.model.Resource;
import com.tdgc.cocos2dx.popup.creator.model.Sprite;
import com.tdgc.cocos2dx.popup.creator.model.Table;
import com.tdgc.cocos2dx.popup.creator.model.View;
import com.tdgc.cocos2dx.popup.creator.model.basic.AdvancedObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Parameter;

public class XmlFileParser extends DefaultHandler {
	
	@Override
	public void startDocument() throws SAXException {
	}
	
	@Override
	public void startElement(String namespaceURI, String localName,
			String qName, Attributes atts) throws SAXException {
		try {
		if(qName.equals(Tag.VIEW)) {
			mView = new View();
			mView.setClassName(getAttributeValue(Attribute.CLASS_NAME, atts));
			mView.setPrefix(getAttributeValue(Attribute.PREFIX, atts));
			mView.setSuper(getAttributeValue(Attribute.SUPER, atts));
			mView.setSuffix(getAttributeValue(Attribute.TYPE, atts));
			mView.setType(getAttributeValue(Attribute.TYPE, atts));
			mView.setBackgroundName(getAttributeValue(Attribute.BACKGROUND_NAME, atts));
			mView.setComment(getAttributeValue(Attribute.COMMENT, atts));
			mView.setSize(getAttributeValue(Attribute.SIZE, atts));
			mView.setTemplateName(
					getAttributeValue(Attribute.TEMPLATE_NAME, atts));
			mView.setTemplateFile(
					getAttributeValue(Attribute.TEMPLATE_FILE, atts));
			mView.setExported(
					getBoolean(getAttributeValue(Attribute.EXPORTED, atts)));
			mCurrentObject = mView;
			mPositionPrefix = mView.getPrefix();
			mAdvancedObject = mView;
			mCurrentContainer = mView;
		} else if(qName.equals(Tag.SPRITE)
				|| qName.equals(Tag.TABLE)
				|| qName.equals(Tag.MENU)
				|| qName.equals(Tag.MENUITEM)
				|| qName.equals(Tag.LABEL)
				|| qName.equals(Tag.CELL)
				|| qName.equals(Tag.PROGRESSBAR)
				|| (qName.equals(Tag.NEXT)
						&& mCurrentGroup.isArray())) {
			CommonObject parent = mCurrentObject;
			if(qName.equals(Tag.SPRITE)) {
				mCurrentObject = new Sprite();
			}
			else if(qName.equals(Tag.TABLE)) {
				mCurrentObject = new Table();
				Table table = (Table)mCurrentObject;
				table.setRows(getIntNumber(getAttributeValue(Attribute.ROWS, atts)));
				table.setColumns(getIntNumber(getAttributeValue(Attribute.COLUMNS, atts)));
			}
			else if(qName.equals(Tag.MENU)) {
				mCurrentObject = new Menu();
			}
			else if(qName.equals(Tag.MENUITEM)) {
				mCurrentObject = new MenuItem();
			}
			else if(qName.equals(Tag.LABEL)) {
				Label label = new Label();
				mView.addLabel(label);
				mCurrentObject = label;
			} 
			else if(qName.equals(Tag.CELL)) {
				Cell cell = new Cell();
				mCell = (AdvancedCell)cell.getAdvancedObject();
				mCell.setClassName(getAttributeValue(Attribute.CLASS_NAME, atts));
				mCell.setPrefix(getAttributeValue(Attribute.PREFIX, atts));
				mCell.setSuper(getAttributeValue(Attribute.SUPER, atts));
				mCurrentObject = cell;
				mCell.setAdvancedParent(mAdvancedObject);
				mAdvancedObject = mCell;
				ItemGroup cellGroup = new ItemGroup(ItemGroup.Type.CELL);
				cellGroup.setContainer(parent);
				cellGroup.setBeforeGroup(mCurrentGroup);
				cellGroup.addItem(mCell);
				mCurrentGroup = cellGroup;
			}
			else if(qName.equals(Tag.PROGRESSBAR)) {
				Progressbar progressbar = new Progressbar();
				mCurrentObject = progressbar;
				mAdvancedObject.addProgressbars(progressbar);
			}
			else if(qName.equals(Tag.NEXT)) {
				mCurrentObject = mCurrentGroup.cloneFromTheFirstItem();
				mCurrentObject.setNextItemInArray(true);
			}
			
			mCurrentObject.setComment(
					getAttributeValue(Attribute.COMMENT, atts));
			mCurrentObject.setVisible(getBoolean(
					getAttributeValue(Attribute.VISIBLE, atts)));
			mCurrentObject.setTemplateName(
					getAttributeValue(Attribute.TEMPLATE_NAME, atts));
			mCurrentObject.setTemplateFile(
					getAttributeValue(Attribute.TEMPLATE_FILE, atts));
			mCurrentObject.setParent(parent);
			
			if(mCurrentObject.isAddToGroup()) {
				mCurrentGroup.addItem(mCurrentObject);
			}
			
			boolean generateClass = getBoolean(
					getAttributeValue(Attribute.GENERATE_CLASS, atts));
			if(generateClass) {
				mCurrentObject.setGenerateClass(true);
				AdvancedObject adv = mCurrentObject.createAdvancedObject();
				adv.setAdvancedParent(mAdvancedObject);
				mAdvancedObject = adv;
				mAdvancedObject.setExported(
						getBoolean(getAttributeValue(Attribute.EXPORTED, atts)));
			}
		}
		else if(qName.equals(Tag.RESOURCE)) {
			Resource resource = new Resource();
			resource.setComment(getAttributeValue(Attribute.COMMENT, atts));
			resource.setContainerParent(mCurrentContainer);
			mView.addResource(resource);
			mCurrentContainer = resource;
		}
		else if(qName.equals(Tag.IMAGE)
				|| qName.equals(Tag.BACKGROUND_IMAGE)) {
			mCurrentImage = new Image();
			mCurrentImage.setId(getAttributeValue(Attribute.ID, atts));
			mCurrentImage.setRealPath(getAttributeValue(Attribute.REAL_PATH, atts));
			mCurrentImage.setPhonyPath(getAttributeValue(Attribute.PHONY_PATH, atts));
			mCurrentImage.setIsBackground(
					getBoolean(getAttributeValue(Attribute.BACKGROUND, atts)));
			mCurrentImage.setLocationInInterfaceBuilder(
					getAttributeValue(Attribute.LOCATION_IN_INTERFACEBUILDER, atts));
			String width = getAttributeValue(Attribute.WIDTH, atts);
			String height = getAttributeValue(Attribute.HEIGHT, atts);
			if(width != null && height != null) {
				mCurrentImage.setSize(getFloatNumber(width), getFloatNumber(height));
			}
			if(qName.equals(Tag.BACKGROUND_IMAGE)) {
				mCurrentImage.setXMLTagName(Tag.BACKGROUND_IMAGE);
				mView.setBackgroundImage(mCurrentImage);
			} else {
				mCurrentContainer.addImage(mCurrentImage);
				if(!mCurrentImage.isResource()) {
					mCurrentImage.setParent(mCurrentObject);
				}
			}
		}
		else if(qName.equals(Tag.SPRITES)
				|| qName.equals(Tag.TABLES)
				|| qName.equals(Tag.MENUS)
				|| qName.equals(Tag.MENUITEMS)
				|| qName.equals(Tag.LABELS)) {
			ItemGroup beforGroup = mCurrentGroup;
			if(qName.equals(Tag.TABLES)) {
				mCurrentGroup = new ItemGroup(ItemGroup.Type.TABLE);
			}
			else if(qName.equals(Tag.SPRITES)) {
				mCurrentGroup = new ItemGroup(ItemGroup.Type.SPRITE);
			} 
			else if(qName.equals(Tag.MENUS)) {
				mCurrentGroup = new ItemGroup(ItemGroup.Type.MENU);
			}
			else if(qName.equals(Tag.MENUITEMS)) {
				mCurrentGroup = new ItemGroup(ItemGroup.Type.MENUITEM);
			} 
			else if(qName.equals(Tag.LABELS)) {
				mCurrentGroup = new ItemGroup(ItemGroup.Type.LABLE);
			}
			mCurrentGroup.setIsArray(getBoolean(
					getAttributeValue(Attribute.ARRAY, atts)));
			mCurrentGroup.setArrayLength(getAttributeValue(Attribute.LENGTH, atts));
			mCurrentGroup.setContainer(mCurrentObject);
			mCurrentGroup.setBlockComment(
					getAttributeValue(Attribute.COMMENT, atts));
			mCurrentGroup.setBeforeGroup(beforGroup);
		} 
		else if(qName.equals(Tag.POSITION_NAME)) {
			mCurrentObject.setPositionName(mPositionPrefix, 
					getAttributeValue(Attribute.VALUE, atts));
			mCurrentObject.setIsUnlocated(
					getBoolean(getAttributeValue(Attribute.UNLOCATED, atts)));
		}
		else if(qName.equals(Tag.PARAMETER)) {
			mCurrentParameter = new Parameter();
			mCurrentParameter.setName(getAttributeValue(Attribute.NAME, atts));
			mCurrentParameter.setType(getAttributeValue(Attribute.TYPE, atts));
			mCurrentParameter.setKind(getAttributeValue(Attribute.KIND, atts));
			mAdvancedObject.addParameter(mCurrentParameter);
		}
		else if(qName.equals(Tag.XIBCONTAINER_PATH)) {
			boolean used = getBoolean(getAttributeValue(Attribute.USED, atts));
			if(used) {
				mView.setInterfaceBuilder(Constants.XIB);
			}
			mView.setXibContainerPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.SCREENCONTAINER_PATH)) {
			boolean used = getBoolean(getAttributeValue(Attribute.USED, atts));
			if(used) {
				mView.setInterfaceBuilder(Constants.SCREEN);
			}
			mView.setScreenContainerPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.ANDROIDCONTAINER_PATH)) {
			boolean used = getBoolean(getAttributeValue(Attribute.USED, atts));
			if(used) {
				mView.setInterfaceBuilder(Constants.ANDROID);
			}
			mView.setAndroidContainerPath(getAttributeValue(Attribute.VALUE, atts));
		} else if(qName.equals(Tag.DEFINE_PATH)) {
			mView.setDefinePath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.PARAMETERS_PATH)) {
			mView.setParametersPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.IMAGES_INPUTPATH)) {
			mView.setImagesInputPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.IMAGES_PATH)) {
			mView.setImagesPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.CLASS_PATH)) {
			mView.setClassPath(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.ANCHORPOINT)) {
			mCurrentObject.setAnchorPoint(getAttributeValue(Attribute.VALUE, atts));
		} 
		else if(qName.equals(Tag.POSITION)) {
			mCurrentObject.setPosition(getAttributeValue(Attribute.VALUE, atts));
		} 
		else if(qName.equals(Tag.TEXT)) {
			((Label)mCurrentObject).setText(getAttributeValue(Attribute.VALUE, atts));
			((Label)mCurrentObject).setTextVar(getAttributeValue(Attribute.VARNAME, atts));
		}
		else if(qName.equals(Tag.FONT)) {
			Label label = (Label)mCurrentObject;
			label.setFontName(getAttributeValue(Attribute.NAME, atts));
			label.setFontFamily(getAttributeValue(Attribute.FAMILY, atts));
		}
		else if(qName.equals(Tag.FONT_SIZE)) {
			Label label = (Label)mCurrentObject;
			label.setFontSizeFloat(getAttributeValue(Attribute.VALUE, atts));
			label.setFontSizeVar(getAttributeValue(Attribute.VARNAME, atts));
		}
		else if(qName.equals(Tag.LOCATION_IN_INTERFACEBUILDER)) {
			Label label = (Label)mCurrentObject;
			label.setLocationInView(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.Z_INDEX)) {
			mCurrentObject.setZIndex(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.SIZE)) {
			mCurrentObject.setSize(getAttributeValue(Attribute.VALUE, atts));
		}
		else if(qName.equals(Tag.TYPE)
				|| qName.equals(Tag.MID_POINT)
				|| qName.equals(Tag.BAR_CHANGE_RATE)
				|| qName.equals(Tag.PERCENT)) {
			if(mCurrentObject instanceof Progressbar) {
				Progressbar progressbar = (Progressbar)mCurrentObject;
				String value = getAttributeValue(Attribute.VALUE, atts);
				if(qName.equals(Tag.TYPE)) {
					progressbar.setType(value);
				} else if(qName.equals(Tag.MID_POINT)) {
					progressbar.setMidPoint(value);
				} else if(qName.equals(Tag.BAR_CHANGE_RATE)) {
					progressbar.setBarChangeRate(value);
				} else if(qName.equals(Tag.PERCENT)) {
					progressbar.setPercent(value);
				}
			}
		}
		else if(qName.equals(Tag.EXIT_IMAGE)) {
			String position = getAttributeValue(
					Attribute.POSITION, atts);
			String locationInItfbd = getAttributeValue(
					Attribute.LOCATION_IN_INTERFACEBUILDER, atts);
			mView.setExitSpritePosition(position);
			mView.setExitImageLocationInView(locationInItfbd);
		}
		else if(qName.equals(Tag.FONT_COLOR)) {
			int red = getIntNumber(getAttributeValue(Attribute.RED, atts));
			int green = getIntNumber(getAttributeValue(Attribute.GREEN, atts));
			int blue = getIntNumber(getAttributeValue(Attribute.BLUE, atts));
			String alphaStr = getAttributeValue(Attribute.ALPHA, atts);
			int alpha = getIntNumber(((alphaStr == null) ? "1": alphaStr));
			if(mCurrentObject instanceof Label) {
				((Label)mCurrentObject).setRGBA((short)red, 
						(short)green, (short)blue, (short)alpha);
			}
		}
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
		
		
	@Override
	public void endDocument() throws SAXException {
	}
	
	@Override
	public void endElement(String namespaceURI, String localName, 
			String qName) throws SAXException {
		try {
		if(qName.equals(Tag.SPRITES)
				|| qName.equals(Tag.TABLES)
				|| qName.equals(Tag.MENUS)
				|| qName.equals(Tag.MENUITEMS)
				|| qName.equals(Tag.LABELS)) {
			mCurrentGroup.pushBack();
			addGroupToView(mCurrentGroup);
			mCurrentGroup.update();
			mCurrentGroup = mCurrentGroup.getBeforeGroup();
		}
		else if(qName.equals(Tag.SPRITE)
				|| qName.equals(Tag.TABLE)
				|| qName.equals(Tag.MENUITEM)
				|| qName.equals(Tag.MENU)
				|| qName.equals(Tag.LABEL)
				|| qName.equals(Tag.RESOURCE)
				|| qName.equals(Tag.PROGRESSBAR)
				|| qName.equals(Tag.CELL)
				|| (qName.equals(Tag.NEXT)
						&& mCurrentGroup.isArray())) {
			if(qName.equals(Tag.CELL)) {
				mCurrentGroup.pushBack();
				mCurrentGroup = mCurrentGroup.getBeforeGroup();
			}
			if(mCurrentObject.getAdvancedObject() != null) {
				mAdvancedObject.update();
				mAdvancedObject = mAdvancedObject.getAdvancedParent();
			} 
			mCurrentObject.update();
			mCurrentObject = mCurrentObject.getParent();
		} 
		else if(qName.equals(Tag.RESOURCE)) {
			mCurrentContainer = mCurrentContainer.getContainerParent();
		}
		else if(qName.equals(Tag.VIEW)) {
			mView.update();
		}
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void characters(char[] ch, int start, int length) {
		String text = new String(ch, start, length).trim();
		if(text.length() == 0) {
			return;
		}
	}
	
	private String getAttributeValue(String attName, Attributes atts) {
		String result = null;
		for(int i = 0 ; i < atts.getLength() ; i++) {
			String thisAtt = atts.getQName(i);
			if(attName.equals(thisAtt)) {
				result = atts.getValue(i);
				return result.trim();
			}
		}
		return result;
	}
	
	private int getIntNumber(String value) {
		return (int)getFloatNumber(value);
	}
	
	private float getFloatNumber(String value) {
		float result = 0;
		try {
			result = Float.parseFloat(value);
		} catch(NumberFormatException e) {
			e.printStackTrace();
		} catch (NullPointerException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	private boolean getBoolean(String pValue) {
		boolean result = false;
		try {
			result = Boolean.parseBoolean(pValue);
		} catch(NullPointerException e) {
			e.printStackTrace();
		} catch (NumberFormatException e) {
			e.printStackTrace();
		}
		
		return result;
	}
	
	private void addGroupToView(ItemGroup group) {
		mAdvancedObject.pushBackGroup(group);
	}
	
	public View getView() {
		return this.mView;
	}
	
	protected IContainer mCurrentContainer;
	protected CommonObject mCurrentObject;
	protected ItemGroup mCurrentGroup;
	protected View mView;
	protected AdvancedCell mCell;
	protected AdvancedObject mAdvancedObject;
	protected Image mCurrentImage;
	protected Parameter mCurrentParameter;
	protected String mPositionPrefix;
}
