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

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.ModelType;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Point;
import com.tdgc.cocos2dx.popup.creator.model.basic.Size;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;
import com.tdgc.cocos2dx.popup.creator.utils.ViewUtils;
import com.tvd.gameview.ext.value.validate.Validator;

public class Progressbar extends CommonObject {
	
	public Progressbar() {
		super();
		mSuffix = "Progressbar";
		mDeclareObjectName = "Progressbar";
		mType = ModelType.PROGRESSBAR;
		mXmlTagName = Tag.PROGRESSBAR;
		mProgressbarType = "kCCProgressTimerTypeBar";
		mAnchorPoint = new Point(0, 0);
		mAnchorPointString = mAnchorPoint.toString();
		mMidPoint = new Point(0, 0);
		mBarChangeRate = new Point(1, 0);
		
		mTemplateName = "CCProgressTimer";
		mTemplateFile = "progressbar.template";
		
		mPercent = 30;
		mIsAddToGroup = false;
	}
	
	public Progressbar(String pName) {
		super();
		this.mName = pName;
		mSuffix = "Progressbar";
	}
	
	@Override
	public void setPositionName(String pPositionName) {
		super.setPositionName(pPositionName);
	}
	
	@Override
	public String implement(boolean pInfunction) {
		if(pInfunction && isBackground()) {
			return "";
		}
		
		StringBuilder builder = new StringBuilder("\n");
		String template = fetchTemplate(pInfunction);
		
		String parentName = Config.getInstance()
				.getDefaultBackgroundOnSupers(mParent.getType());
		if(mParent != null) {
			parentName = mParent.getName();
		}
		builder.append(mSprite.implement(true));
		ViewUtils.implementObject(mSprite, builder);
		template = template.replace("{var_name}", mName)
			.replace("{tab}", "\t")
			.replace("{sprite_name}", mSprite.getName())
			.replace("{progress_type}", mProgressbarType)
			.replace("{anchorpoint}", mAnchorPointString)
			.replace("{mid_point}", mMidPoint.toString())
			.replace("{bar_change_rate}", mBarChangeRate.toString())
			.replace("{percent}", "" + mPercent)
			.replace("{parent_name}", parentName)
			.replace("{var_name}", mName)
			.replace("{z-index}", mZIndex);
			
		builder.append(template);
		
		return builder.toString();
	}
	
	@Override
	public CommonObject clone() {
		Progressbar menuItem = new Progressbar();
		this.setAllPropertiesForObject(menuItem);
		
		return menuItem;
	}
	
	@Override
	public void addSpriteGroup(ItemGroup group) {
		super.addSpriteGroup(group);
		if(validate()) {
			ItemGroup spriteGroup = this.mSpriteGroups.get(0);
			for(int i = 1 ; i < spriteGroup.getItems().size() ; i++) {
				((Sprite)spriteGroup.getItems().get(i))
					.getImage().setAddToInterfaceBuilder(false);
			}
			group.setAddToView(false);
		}
	}
	
	@Override
	public void setParent(CommonObject parent) {
		super.setParent(parent);
		this.setTabCount(parent.getTabCount() + 1);
		if(parent instanceof Sprite) {
			((Sprite)parent).setProgressbar(this);
		}
	}
	
	@Override
	public void addChild(CommonObject child) {
		this.setSprite((Sprite)child);
	}
	
	@Override
	public void update() {
		if(mSprite != null && mSprite.getImage() != null) {
			mSprite.getImage().setAddToInterfaceBuilder(false);
		}
	}
	
	@Override
	public Point getLocationInView() {
		return mParent.getLocationInView();
	}
	
	@Override
	public Size getSize() {
		return mParent.getSize();
	}
	
	public void setMidPoint(Point point) {
		this.mMidPoint = point;
	}
	
	public void setMidPoint(float x, float y) {
		this.setMidPoint(new Point(x, y));
	}
	
	public void setMidPoint(String point) {
		setMidPoint(Point.parsePoint(point));
	}
	
	public void setBarChangeRate(Point point) {
		this.mBarChangeRate = point;
	}
	
	public void setBarChangeRate(float x, float y) {
		this.setBarChangeRate(new Point(x, y));
	}
	
	public void setBarChangeRate(String point) {
		setBarChangeRate(Point.parsePoint(point));
	}
	
	public void setPercent(float percent) {
		this.mPercent = percent;
	}
	
	public void setPercent(String percent) {
		if(Validator.isNumeric(percent)) {
			this.mPercent = Float.parseFloat(percent);
		}
	}
	
	public void setProgressbarType(String type) {
		this.mProgressbarType = type;
	}
	
	public boolean validate() {
		boolean valid = true;
		if(mSpriteGroups.size() != 1) {
			valid = false;
		} else {
			int size = mSpriteGroups.get(0).getItems().size();
			if(size != 2) {
				valid = false;
			} else {
				
			}
		}
		
		return valid;
	}
	
	public void setSprite(Sprite sprite) {
		sprite.setIsUnlocated(true);
		sprite.setTabCount(mTabCount + 1);
		sprite.setUnlocated(true);
		sprite.setAddToGroup(false);
		this.mSprite = sprite;
	}
	
	public Sprite getSprite() {
		return this.mSprite;
	}
	
	@Override
	public String toXML() {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " ") 
			.append(Attribute.TEMPLATE_NAME + "=\""+ mTemplateName + "\" ")
			.append(Attribute.VISIBLE + "=\"true\" ")
			.append(Attribute.COMMENT + "=\"\">");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.TYPE + " " + Attribute.VALUE 
				+ "=\"" + mProgressbarType + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.MID_POINT + " " + Attribute.VALUE 
			+ "=\"" + mMidPoint + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.BAR_CHANGE_RATE + " " + Attribute.VALUE 
			+ "=\"" + mBarChangeRate + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.PERCENT + " " + Attribute.VALUE 
					+ "=\"" + mPercent + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION_NAME + " " + Attribute.VALUE 
					+ "=\"" + mXmlPositionName + "\" "
					+ Attribute.UNLOCATED + "=\"true\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.ANCHORPOINT + " " + Attribute.VALUE 
				+ "=\"" + mAnchorPoint + "\" />");
		
		builder.append("\n")
			.append(mSprite.toXML())
			.append(tab)
			.append("</" + mXmlTagName + ">");
		
		builder.append("\n");
		
		return builder.toString();
	}
	
	protected String mProgressbarType;
	protected Point mMidPoint;
	protected Point mBarChangeRate;
	protected float mPercent;
	private Sprite mSprite;
}
