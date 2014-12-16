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

import java.util.List;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.ModelType;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.basic.AdvancedObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Parameter;
import com.tdgc.cocos2dx.popup.creator.model.basic.Point;
import com.tdgc.cocos2dx.popup.creator.model.basic.Size;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class Sprite extends CommonObject {
	
	public Sprite() {
		super();
		this.mSuffix = "Sprite";
		this.mDeclareObjectName = "CCSprite";
		this.mType = ModelType.SPRITE;
		this.mImage = null;
		this.mXmlTagName = Tag.SPRITE;
		this.mIsUnlocated = false;
		
		this.mTemplateName = "CCSprite";
		this.mTemplateFile = "sprite.template";
	}
	
	public Sprite(Image img) {
		this();
		img.setParent(this);
	}
	
	public AdvancedObject createAdvancedObject() {
		setAdvancedObject(new AdvancedSprite());

		return mAdvancedObject;
	}
	
	@Override
	public void setPositionName(String pPositionName) {
		super.setPositionName(pPositionName);
	}

	@Override
	public String implement(boolean pInfunction) {
		StringBuilder builder = new StringBuilder("\n");
		if(mIsGenerateClass) {
			setTemplateName("Common");
		}
		String template = fetchTemplate(pInfunction);
		
		String imageName = "";
		if(mImage == null) {
			imageName = ((Sprite)mBackground).getImage().getId();
		} else {
			imageName = mImage.getId();
		}
		
		String parentName = Config.getInstance()
				.getDefaultBackgroundOnSupers(mParent.getType());
		if(mParent != null) {
			parentName = mParent.getName();
		}
		
		String extendClassName = (mAdvancedObject != null)
				? mAdvancedObject.getClassName()
				: "";
		template = template.replace("{var_name}", mName)
			.replace("{position_name}", mPositionName)
			.replace("{tab}", "\t")
			.replace("{parent_name}", parentName)
			.replace("{image_name}", imageName)
			.replace("{z-index}", mZIndex)
			.replace("{tag_name}", mTagName)
			.replace("{extend_class_name}", extendClassName);
		builder.append(template);
		
		return builder.toString();
	}
	
	@Override
	public void setLocationInView(float x, float y) {
		super.setLocationInView(x, y);
	}
	
	public void setPosition(Point point) {
		if(mIsUnlocated) {
			mParent.setPosition(point);
		}
		super.setPosition(point);
	}
	
	@Override
	public void setSize(Size size) {
		super.setSize(size);
	}
	
	@Override
	public void setParent(CommonObject parent) {
		super.setParent(parent);
	}
	
	public void setUnlocated(boolean unlocated) {
		this.mIsUnlocated = unlocated;
	}
	
	public void setProgressbar(Progressbar bar) {
		this.mProgressbar = bar;
	}
	
	public Progressbar getProgressbar() {
		return this.mProgressbar;
	}
	
	@Override
	public CommonObject clone() {
		Sprite sprite = new Sprite();
		sprite.mImage = mImage;
		this.setAllPropertiesForObject(sprite);
		
		return sprite;
	}
	
	@Override
	public String toXML() {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		StringBuilder generateClassString = new StringBuilder();
		StringBuilder exportedAtt = new StringBuilder();
		StringBuilder parameterTags = new StringBuilder();
		if(mIsGenerateClass) {
			List<Parameter> params = mAdvancedObject.getParameters();
			for(int i = 0 ; i < params.size() ; i++) {
				parameterTags.append("\n" + tab)
					.append(params.get(i).toXML());
			}
			generateClassString.append("\n\t\t" + tab)
				.append(Attribute.GENERATE_CLASS + "=\"true\" ");
			exportedAtt.append(Attribute.EXPORTED)
				.append("=\"" + mAdvancedObject.isExported() + "\"");
		}
		builder.append("<" + mXmlTagName + " " + Attribute.VISIBLE + "=\"true\" ")
			.append(Attribute.COMMENT + "=\"\"")
			.append(generateClassString)
			.append(exportedAtt)
			.append(">");
		builder.append(parameterTags);
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION_NAME + " " + Attribute.VALUE 
					+ "=\"" + mXmlPositionName + "\" ");
		if(!mIsUnlocated) {
			builder.append("/>");
			builder.append("\n" + tab + "\t")
			.append("<" + Tag.ANCHORPOINT + " " + Attribute.VALUE 
					+ "=\"" + mAnchorPointString + "\" />");
			builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION + " " + Attribute.VALUE 
					+ "=\"" + mPosition + "\" />");
			builder.append("\n" + tab + "\t")
			.append("<" + Tag.Z_INDEX + " " + Attribute.VALUE 
					+ "=\"" + mZIndex + "\" />");
		} else {
			builder.append(Attribute.UNLOCATED + "=\"true\" />");
		}
		builder.append("\n" + mImage.toXML());
		
		builder.append("\n")
			.append(super.toXML());
			
		if(mProgressbar != null) {
			builder.append(mProgressbar.toXML());
		}
		builder.append(tab)
			.append("</" + mXmlTagName + ">");
		
		builder.append("\n");
		
		return builder.toString();
	}
	
	protected Progressbar mProgressbar;
}
