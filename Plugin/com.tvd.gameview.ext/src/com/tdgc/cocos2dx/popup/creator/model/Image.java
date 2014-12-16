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

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Point;
import com.tdgc.cocos2dx.popup.creator.model.basic.Size;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;
import com.tvd.gameview.ext.value.validate.Validator;

public class Image implements Comparable<Image> {
	
	public Image() {
		this.mId = null;
		this.mPhonyPath = null;
		this.mRealPath = null;
		this.mAnchorPoint = new Point(0.5f, 0.5f);
		this.mXmlTagName = "image";
		this.mIsAddToInterfaceBuilder = true;
		this.mLocationInInterfaceBuilder = new Point(10, 10);
		this.mIsExists = false;
		this.mIsResource = false;
	}
	
	public Image(String phonyPath) {
		this();
		this.setPhonyPath(phonyPath);
	}
	
	public Image(String phonyPath, String locationInView) {
		this(phonyPath);
		this.setLocationInInterfaceBuilder(locationInView);
	}
	
	public Image(String pId, String pRealPath, String pPhonyPath) {
		this();
		this.setId(pId);
		this.setRealPath(pRealPath);
		this.setPhonyPath(pPhonyPath);
	}
	
	public Image(String pId, String pRealPath, String pPhonyPath,
			boolean pIsBg, CommonObject pParent) {
		this();
		this.setId(pId);
		this.setRealPath(pRealPath);
		this.setPhonyPath(pPhonyPath);
		this.setIsBackground(true);
		this.setParent(pParent);
	}
	
	//change
	public void setPhonyPath(String pPhonyPath) {
		if(pPhonyPath == null) {
			return;
		}
		this.mPhonyPath = pPhonyPath.trim();
		if(this.mRealPath == null) {
			this.mRealPath = this.mPhonyPath;
		}
		if(this.mId == null) {
			this.setId(StringUtils.convertPhonyPathToId(this.mPhonyPath));
		}
		if(mRealPath != null) {
			mName = mRealPath;
			if(mRealPath.contains("/")) {
				mName = mRealPath.substring(mRealPath.lastIndexOf('/') + 1);
			}
		}
	}
	
	public String createImageViewTag(String pImagePath) 
			throws IOException {
		StringBuilder builder = new StringBuilder(StringUtils.tab(5));
		Point point = this.mLocationInInterfaceBuilder;
		if(mRealPath == null) {
			builder.append("<imageView userInteractionEnabled=\"NO\" contentMode=\"scaleToFill\" ")
				.append("horizontalHuggingPriority=\"251\" verticalHuggingPriority=\"251\" ")
				.append("id=\"" + getImageViewId() + "\">\n")
				.append(StringUtils.tab(6))
				.append("<rect key=\"frame\" x=\"" + point.getX() + "\" y=\"" + point.getY() + "\" ")
				.append("width=\"" + mSize.getWidth() +"\" height=\""+ mSize.getHeight() +"\" />\n")
				.append(StringUtils.tab(6))
				.append("<autoresizingMask key=\"autoresizingMask\" flexibleMaxX=\"YES\" " +
						"flexibleMaxY=\"YES\" />\n")
				.append(StringUtils.tab(5))
	            .append("</imageView>\n");
		} else {
			File file = new File(pImagePath + "/" + mRealPath);
			if(!file.exists()) {
				System.err.println("ERROR::createImageViewTag::file " + file + " not exists");
				return "";
			}
			BufferedImage image = ImageIO.read(file);
		    int width = image.getWidth();
		    int height = image.getHeight();
		    mSize = new Size(width, height);
		    
			builder.append("<imageView opaque=\"NO\" clipsSubviews=\"YES\" ")
				.append("multipleTouchEnabled=\"YES\" contentMode=\"scaleToFill\" ")
				.append("image=\"" + mName + "\" id=\"" + getImageViewId() + "\">\n")
				.append(StringUtils.tab(6))
				.append("<rect key=\"frame\" x=\"" + point.getX() + "\" y=\"" + point.getY() + "\" ")
				.append("width=\"" + width/2 +"\" height=\""+ height/2 +"\" />\n")
				.append(StringUtils.tab(6))
				.append("<autoresizingMask key=\"autoresizingMask\"/>\n")
				.append(StringUtils.tab(5))
	            .append("</imageView>\n");
		}
		return builder.toString();
	}
	
	public String createImageTag() {
		if(mSize == null) {
			System.err.println("ERROR::createImageTag image " 
					+ mRealPath + " has size = " + mSize);
			return "";
		}
		StringBuilder builder = new StringBuilder(StringUtils.tab(2));
		builder.append("<image name=\"" + mName + "\" ")
			.append("width=\"" + mSize.getWidth() + "\" ")
			.append("height=\"" + mSize.getHeight() + "\" />\n");
		
		return builder.toString();
	}
	
	public String createWidgetsTag(String pId, String pImagePath) throws IOException {
		mImageViewId = pId;
		BufferedImage image = ImageIO.read(new File(pImagePath + "/" + mRealPath));
	    int width = image.getWidth();
	    int height = image.getHeight();
	    String imageDirectory = pImagePath.substring(
	    		pImagePath.lastIndexOf('/') + 1);
	    mSize = new Size(width, height);
		StringBuilder builder = new StringBuilder(StringUtils.tab(1));
		builder.append("<widgets xsi:type=\"model:Image\" ")
			.append("id=\"" + mImageViewId + "\" ")
			.append("x=\"" + 100 + "\" ")
			.append("y=\"" + 100 + "\" ")
			.append("width=\"" + width/2 + "\" ")
			.append("height=\"" + height/2 + "\" ")
			.append("measuredWidth=\"" + width/2 + "\" ")
			.append("measuredHeight=\"" + height/2 + "\" ")
			.append("src=\"assets/" + imageDirectory + "/" + mRealPath + "\" ")
			.append("/>\n");
		return builder.toString();
	}
	
	public void fetchSize(String physicalPath) {
		File file = new File(physicalPath);
		if(!file.exists()) {
			System.err.println("ERROR::fetchSize::file " + file + " not exists");
			return;
		}
		BufferedImage image = null;
		try {
			image = ImageIO.read(file);
			int width = image.getWidth();
		    int height = image.getHeight();
		    setSize(width/2, height/2);
		} catch (IOException e) {
			e.printStackTrace();
		}
	    
	}
	
	@Override
	public int compareTo(Image o) {
		return Integer.parseInt(this.mParent.getZIndex())
				- Integer.parseInt(o.mParent.getZIndex());
	}
	
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("{\n")
			.append("\t\"image\" : {\n")
			.append("\t\t\"id\" : " + "\"" + mId + "\",\n")
			.append("\t\t\"real-path\" : " + "\"" + mRealPath + "\",\n")
			.append("\t\t\"phony-path\" : " + "\"" + mPhonyPath + "\"\n")
			.append("\t}\n")
			.append("}");
		return builder.toString();
	}
	
	public void replaceWithAnother(Image another) {
		mId = another.mId;
		mImageViewId = another.mImageViewId;
		mRealPath = another.mRealPath;
		mPhonyPath = another.mPhonyPath;
		mName = another.mName;
		mSize = another.mSize;
		mX = another.mX;
		mY = another.mY;
		mParent = another.mParent;
		mAnchorPoint = another.mAnchorPoint;
		mTabCount = another.mTabCount;
		mXmlTagName = another.mXmlTagName;
		mLocationInInterfaceBuilder = another.mLocationInInterfaceBuilder;
		mIsBackground = another.mIsBackground;
		mIsExists = another.mIsExists;
		mIsAddToInterfaceBuilder = another.mIsAddToInterfaceBuilder;
	}

	public void setId(String pId) {
		this.mId = pId.replace(" ", "_")
				.replace("\t", "_")
				.replace("-", "_")
				.replace("__", "_");
	}
	
	public void setRealPath(String pRealPath) {
		this.mRealPath = pRealPath;
	}
	
	public String getId() {
		return this.mId;
	}
	
	public String getRealPath() {
		return this.mRealPath;
	}
	
	public String getPhonyPath() {
		return this.mPhonyPath;
	}
	
	public boolean isBackground() {
		return this.mIsBackground;
	}
	
	public void setIsBackground(boolean pBackground) {
		this.mIsBackground = pBackground;
	}
	
	public void setX(float pX) {
		this.mX = pX + mAnchorPoint.getX()*mSize.getWidth()/2;
	}
	
	public float getX() {
		return this.mX;
	}
	
	public void setY(float pY) {
		this.mY = pY + mAnchorPoint.getY()*mSize.getHeight()/2;
	}
	
	public void setXY(float pX, float pY) {
		this.mX = pX;// + mAnchorPoint.getX()*mSize.getWidth();
		this.mY = pY;// + mAnchorPoint.getY()*mSize.getHeight();
		this.setLocationInInterfaceBuilder(pX, pY);
		this.mParent.setLocationInView(pX, pY);
	}
	
	public void alignFollowParrent() {
		try {
			if(mParent.getLocationInView() == null || mSize == null) {
				System.err.println("ERROR:: name = " + this.getRealPath() + " has "
						+ "parent.getLocationInView == null\n"
						+ "size = " + mSize);
				return;
			}
			float x = mParent.getLocationInView().getX();
			float y = mParent.getLocationInView().getY();
			CommonObject parentOfParent = mParent.getParent();
			if(parentOfParent != null
					&& parentOfParent.getLocationInView() != null) {
				x = x - parentOfParent.getLocationInView().getX();
				y = y - parentOfParent.getLocationInView().getY();
				
				parentOfParent = parentOfParent.getParent();
			}
			mAnchorPoint = mParent.getAnchorPoint();
			float anchorpointY = 1 - mAnchorPoint.getY();
			x = x + mAnchorPoint.getX()*mSize.getWidth();
			if(mParent.getParent() != null
					&& mParent.getParent().getViewSize() != null) {
				y = mParent.getParent().getViewSize().getHeight() - 
					(y + anchorpointY*mSize.getHeight());
			} else {
				y = y + anchorpointY*mSize.getHeight();
			}
			this.mX = x;
			this.mY = y;
			mParent.setPosition(x, y);
			
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void fetchLocationInViewFromParent() {
		try {
			if(mParent.getLocationInView() == null) {
				System.err.println("ERROR:: name = " + this.getRealPath() + " has "
						+ "parent.getLocationInView == null");
				return;
			}
			float x = mParent.getLocationInView().getX();
			float y = mParent.getLocationInView().getY();
			CommonObject parentOfParent = mParent.getParent();
			if(parentOfParent != null) {
				x = x - parentOfParent.getLocationInView().getX();
				y = y - parentOfParent.getLocationInView().getY();
				
				parentOfParent = parentOfParent.getParent();
			}
			mAnchorPoint = mParent.getAnchorPoint();
			float anchorpointY = 1 - mAnchorPoint.getY();
			x = x + mAnchorPoint.getX()*mSize.getWidth();
			if(mParent.getParent() != null) {
				y = mParent.getParent().getViewSize().getHeight() - 
					(y + anchorpointY*mSize.getHeight());
			} else {
				y = y + anchorpointY*mSize.getHeight();
			}
			this.mX = x;
			this.mY = y;
			mParent.setPosition(x, y);
			
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public float getY() {
		return this.mY;
	}
	
	public String getImageViewId() {
		return this.mImageViewId;
	}
	
	public void setParent(CommonObject pParent) {
		this.mTabCount = pParent.getTabCount() + 1;
		pParent.setImage(this);
		
		this.mParent = pParent;
		String anchopointString = null;
		while (pParent != null && anchopointString == null) {
			anchopointString = pParent.getAnchorPointString();
			pParent = pParent.getParent();
		}
		if(anchopointString != null 
				&& Validator.isValidDoubleValueString(anchopointString)) {
			mAnchorPoint = Point.parsePoint(anchopointString);
		}

		if(mParent != null && mParent.isNextItemInArray()) {
			Interface itf = new Interface(mParent);
			itf.setImage(this);
		}
	}
	
	public Size getSize() {
		return this.mSize;
	}
	
	public void setSize(String size) {
		if(Validator.isValidDoubleValueString(size)) {
			String wh[] = size.split(",");
			this.setSize(Float.parseFloat(wh[0]), 
					Float.parseFloat(wh[1]));
		}
	}
	
	public void setSize(Size size) {
		this.mSize = size;
		if(mParent != null) {
			this.mParent.setSize(size);
		}
	}
	
	public void setSize(float w, float h) {
		setSize(new Size(w, h));
	}
	
	public void setImageViewId(String id) {
		mImageViewId = id;
	}
	
	public CommonObject getParent() {
		return this.mParent;
	}
	
	public void setTabCount(int tabCount) {
		this.mTabCount = tabCount;
	}
	
	public int getTabCount() {
		return this.mTabCount;
	}
	
	public void setAddToInterfaceBuilder(boolean value) {
		this.mIsAddToInterfaceBuilder = value;
	}
	
	public boolean isAddToInterfaceBuilder() {
		return this.mIsAddToInterfaceBuilder;
	}
	
	public void setLocationInInterfaceBuilder(String location) {
		if(Validator.isValidDoubleValueString(location)) {
			String strs[] = location.split(", ");
			this.setLocationInInterfaceBuilder(
					Float.parseFloat(strs[0]), Float.parseFloat(strs[1]));
		}
	}
	
	public void setLocationInInterfaceBuilder(float x, float y) {
		this.setLocationInInterfaceBuilder(new Point(x, y));
	}
	
	public void setLocationInInterfaceBuilder(Point location) {
		this.mLocationInInterfaceBuilder = location;
		if(mParent != null) {
			this.mParent.setLocationInView(location);
		}
	}
	
	public void setLocationInInterfaceBuilder(Point location,
			boolean setForParent) {
		this.mLocationInInterfaceBuilder = location;
		if(mParent != null && setForParent) {
			this.mParent.setLocationInView(location);
		}
	}
	
	public Point getLocationInInterfaceBuilder() {
		return this.mLocationInInterfaceBuilder;
	}
	
	public void setExists(boolean isExists) {
		this.mIsExists = isExists;
	}
	
	public boolean isExists() {
		return mIsExists;
	}
	
	public Point getPosition() {
		return new Point(mX, mY);
	}
	
	public void setPosition(float x, float y) {
		this.mX = x;
		this.mY = y;
	}
	
	public void setXMLTagName(String tagName) {
		this.mXmlTagName = tagName;
	}
	
	public String getXMLTagName() {
		return this.mXmlTagName;
	}
	
	public void setResource(boolean isResource) {
		this.mIsResource = isResource;
	}
	
	public boolean isResource() {
		return this.mIsResource;
	}
	
	public String toXML(boolean includeSize) {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " ")
			.append(Attribute.ID + "=\"" + mId + "\" ");

		if(mIsAddToInterfaceBuilder) {
			builder.append("\n" + tab + "\t")
				.append(Attribute.LOCATION_IN_INTERFACEBUILDER + "=\"") 
				.append(mLocationInInterfaceBuilder + "\"");
				
			if(includeSize && mSize != null) {
				builder.append("\n" + tab + "\t");
				builder.append(Attribute.WIDTH + "=\"" + mSize.getWidth() + "\" ")
					.append(Attribute.HEIGHT + "=\"" + mSize.getHeight() + "\"");
			} 
		}
		if(mPhonyPath != null) {
			builder.append("\n" + tab + "\t")
				.append(Attribute.PHONY_PATH + "=\"" + mPhonyPath + "\" ");
		}
		builder.append(" />");
		
		return builder.toString();
	}
	
	public String toXML() {
		return toXML(true);
	}
	
	public Image clone() {
		Image img = new Image();
		img.mId = mId;
		img.mImageViewId = mImageViewId;
		img.mRealPath = mRealPath;
		img.mPhonyPath = mPhonyPath;
		img.mName = mName;
		img.mXmlTagName = mXmlTagName;
		
		img.mSize = mSize;
		
		img.mAnchorPoint = mAnchorPoint;
		img.mLocationInInterfaceBuilder = mLocationInInterfaceBuilder;
		
		img.mX = mX;
		img.mY = mY;
		
		img.mParent = mParent;
		img.mTabCount = mTabCount;
		img.mIsBackground = mIsBackground;
		img.mIsExists = mIsExists;
		img.mIsAddToInterfaceBuilder = mIsAddToInterfaceBuilder;
		img.mIsResource = mIsResource;
		
		return img;
	}
	
	private String mId;
	private String mImageViewId;
	private String mRealPath;
	private String mPhonyPath;
	private String mName;
	private String mXmlTagName;
	
	private Size mSize;
	
	private Point mAnchorPoint;
	private Point mLocationInInterfaceBuilder;
	
	private float mX;
	private float mY;
	
	private CommonObject mParent;
	
	private int mTabCount;
	
	private boolean mIsBackground;
	private boolean mIsExists;
	protected boolean mIsAddToInterfaceBuilder;
	protected boolean mIsResource;
}
