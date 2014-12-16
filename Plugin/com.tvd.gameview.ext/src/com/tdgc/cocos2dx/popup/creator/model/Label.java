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
import com.tdgc.cocos2dx.popup.creator.constants.Strings;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Point;
import com.tdgc.cocos2dx.popup.creator.model.basic.Size;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class Label extends CommonObject {
	
	public Label() {
		super();
		this.mSuffix = "Label";
		this.mDeclareObjectName = "CCLabelTTF";
		this.mType = ModelType.LABEL;
		this.setPosition(10, 10);
		this.mXmlTagName = Tag.LABEL;
		this.mLocationInView = new Point(10, 10);
		this.mFontName = "HelveticaNeue";
		this.mFontFamily = "Helvetica Neue";
		this.mFontSizeFloat = 17.0f;
		
		this.mTemplateName = "CCLabelTTF";
		this.mTemplateFile = "label.template";
		
		this.mRed = 255; 
		this.mGreen = 255; 
		this.mBlue = 255;
		this.mAlpha = 255;
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
		String textVar = (mTextVar == null)
				? mText : mTextVar;
		String fontSizeVar = (mFontSizeVar == null) 
				? ("" + mFontSizeFloat) : mFontSizeVar;
		String fontNameVar = (mFontNameVar == null) 
				? ("\"" + mFontName + "\"") : mFontName;
		
		template = template.replace("{var_name}", mName)
			.replace("{tab}", "\t")
			.replace("{parent_name}", parentName)
			.replace("{anchorpoint}", mAnchorPointString)
			.replace("{position_name}", mPositionName)
			.replace("{label_text}", textVar)
			.replace("{label_font}", fontNameVar)
			.replace("{label_font_size}", fontSizeVar)
			.replace("{z-index}", mZIndex)
			.replace("{red}", "" + mRed)
			.replace("{green}", "" + mGreen)
			.replace("{blue}", "" + mBlue)
			.replace("{alpha}", "" + mAlpha);
		builder.append(template);
		
		return builder.toString();
	}
	
	public String createLabelTagForXib() {
		StringBuilder builder = new StringBuilder(StringUtils.tab(4) + "<label")
			.append(" opaque=\"NO\" clipsSubviews=\"YES\"")
			.append(" userInteractionEnabled=\"NO\"")
			.append(" contentMode=\"left\"")
			.append(" horizontalHuggingPriority=\"251\"")
			.append(" verticalHuggingPriority=\"251\"")
			.append(" text=\"" + mText + "\"")
			.append(" lineBreakMode=\"tailTruncation\"")
			.append(" baselineAdjustment=\"alignBaselines\"")
			.append(" adjustsFontSizeToFit=\"NO\"")
			.append(" id=\""+ mLabelViewId + "\">");
		float width = (mText.length()*mFontSizeFloat)/2;
		builder.append("\n" + StringUtils.tab(5))
			.append("<rect key=\"frame\" x=\""+ mLocationInView.getX() 
					+"\" y=\""+ mLocationInView.getY() + "\" "
					+ "width=\"" + width + "\" "
					+ "height=\"" + mFontSizeFloat + "\" />");
		builder.append("\n" + StringUtils.tab(5))
			.append("<autoresizingMask key=\"autoresizingMask\""
				+ " flexibleMaxX=\"YES\" flexibleMaxY=\"YES\" />");
		builder.append("\n" + StringUtils.tab(5))
			.append("<fontDescription key=\"fontDescription\" "
				+ "name=\""+ mFontName +"\" family=\""+ mFontFamily + "\" pointSize=\"" 
					+ mFontSizeFloat + "\" />");
		builder.append("\n" + StringUtils.tab(5))
			.append("<color key=\"textColor\" red=\"" + mRed/255.0 + "\" "
					+ "green=\"" + mGreen/255.0 + "\" "
					+ "blue=\"" + mBlue/255.0 + "\" "
					+ "alpha=\"" + mAlpha/255.0 + "\" colorSpace=\"calibratedRGB\" />");
		builder.append("\n" + StringUtils.tab(5))
			.append("<nil key=\"highlightedColor\" />\n");
		builder.append(StringUtils.tab(4) + "</label>");
		
		return builder.toString();
	}
	
	public void alignFollowParrent() {
		try {
			float x = this.getLocationInView().getX();
			float y = this.getLocationInView().getY();
			CommonObject parent = getParent();
			if(parent != null) {
				x = x - parent.getLocationInView().getX();
				y = y - parent.getLocationInView().getY();
				
				parent = parent.getParent();
			}
			
			float anchorpointY = 1 - mAnchorPoint.getY();
			x = x + mAnchorPoint.getX()*mSize.getWidth();
			if(mParent != null) {
				y = mParent.getSize().getHeight() - 
					(y + anchorpointY*mSize.getHeight());
			} else {
				y = y + anchorpointY*mSize.getHeight();
			}
			
			this.setPosition(x, y);
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void setText(String pText) {
		this.mText = pText;
	}
	
	public void setFontName(String pFontName) {
		if(pFontName == null || pFontName.trim().length() == 0
				|| pFontName.equals(Strings.DEFAULT)) {
			return;
		}
		this.mFontName = pFontName;
	}
	
	public String getFontName() {
		return this.mFontName;
	}
	
	public String getText() {
		return this.mText;
	}
	
	public float getFontSizeFloat() {
		return this.mFontSizeFloat;
	}
	
	public String getFontSizeVar() {
		return this.mSizeString;
	}
	
	public void setShadow(boolean pIsShadow) {
		this.mIsShadow = pIsShadow;
	}
	
	public void setDimension(Size pDimension) {
		this.mDimension = pDimension;
	}
	
	public void setFontSizeFloat(String pFontSize) {
		mFontSizeFloat = Float.parseFloat(pFontSize);
	}
	
	public void setFontSizeVar(String pFontSize) {
		this.mFontSizeVar = pFontSize;
	}
	
	public void setLabelViewId(String id) {
		this.mLabelViewId = id;
	}
	
	public String getLabelViewId() {
		return this.mLabelViewId;
	}
	
	public void setFontFamily(String family) {
		if(family == null || family.trim().length() == 0
				|| family.equals(Strings.DEFAULT)) {
			return;
		}
		this.mFontFamily = family;
	}
	
	public void setFontNameVar(String varname) {
		this.mFontNameVar = varname;
	}
	
	public void setTextVar(String varname) {
		this.mTextVar = varname;
	}
	
	public void setRGBA(short red, short green, short blue, short alpha) {
		this.mRed = red;
		this.mGreen = green;
		this.mBlue = blue;
		this.mAlpha = alpha;
	}
	
	@Override
	public CommonObject clone() {
		Label label = new Label();
		this.setAllPropertiesForObject(label);
		return label;
	}
	
	@Override
	public String toXML() {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " " + Attribute.VISIBLE + "=\"true\" ")
			.append(Attribute.COMMENT + "=\"\">");
		
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.TEXT + " " + Attribute.VALUE 
				+ "=\"" + mText + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.FONT + " " + Attribute.NAME 
				+ "=\"" + mFontName + "\" ")
				.append(Attribute.FAMILY + "=\"" + mFontFamily + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.FONT_COLOR + " " + Attribute.RED + "=\"" + mRed + "\" ")
			.append(Attribute.GREEN + "=\"" + mGreen + "\" ")
			.append(Attribute.BLUE + "=\"" + mBlue + "\" ")
			.append(Attribute.ALPHA + "=\"" + mAlpha + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.FONT_SIZE + " " + Attribute.VALUE 
				+ "=\"" + mFontSizeFloat + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION_NAME + " " + Attribute.VALUE 
					+ "=\"" + mXmlPositionName + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.ANCHORPOINT + " " + Attribute.VALUE 
					+ "=\"" + mAnchorPointString + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION + " " + Attribute.VALUE 
					+ "=\"" + mPosition + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.LOCATION_IN_INTERFACEBUILDER + " " + Attribute.VALUE 
					+ "=\"" + mLocationInView + "\" />");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.Z_INDEX + " " + Attribute.VALUE 
					+ "=\"" + mZIndex + "\" />");
		
		builder.append("\n")
			.append(tab)
			.append("</" + mXmlTagName + ">");
		
		builder.append("\n");
		
		return builder.toString();
	}
	
	protected String mFontFamily;
	protected String mLabelViewId;
	protected Size mDimension;
	protected String mText;
	protected String mTextVar;
	protected String mFontName;
	protected String mFontSizeVar;
	protected String mFontNameVar;
	
	protected boolean mIsShadow;
	
	protected float mFontSizeFloat;
	
	private short mRed, mGreen, mBlue, mAlpha;
	
}
