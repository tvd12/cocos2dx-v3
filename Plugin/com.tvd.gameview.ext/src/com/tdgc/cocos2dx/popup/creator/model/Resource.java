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
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class Resource implements IContainer {
	
	public Resource() {
		this.mImages = new ArrayList<Image>();
		this.mXmlTagName = Tag.RESOURCE;
	}

	@Override
	public void addImage(Image image) {
		image.setTabCount(this.getTabCount() + 1);
		image.setResource(true);
		this.mImages.add(image);
	}
	
	@Override
	public void setContainerParent(IContainer parent) {
		this.mParent = parent;
	}

	@Override
	public IContainer getContainerParent() {
		return mParent;
	}
	
	public List<Image> getImages() {
		return this.mImages;
	}
	
	public Image getImage(int index) {
		if(mImages.size() > index) {
			return this.mImages.get(index);
		}
		return null;
	}
	
	public void update() {
		//do something
	}
	
	public void setTabCount(int tabCount) {
		this.mTabCount = tabCount;
	}
	
	public int getTabCount() {
		return mTabCount;
	}
	
	public void setComment(String pComment) {
		this.mComment = pComment;
	}
	
	public String getComment() {
		return this.mComment;
	}
	
	public String toXML() {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " ")
			.append(Attribute.COMMENT + "=\"" + "resource for view" + "\">\n");
		for(Image img : mImages) {
			img.setAddToInterfaceBuilder(false);
			builder.append(img.toXML()).append("\n");
		}
		builder.append(tab).append("</" + mXmlTagName + ">");
		
		return builder.toString();
	}
	
	private List<Image> mImages;
	private int mTabCount;
	private String mXmlTagName;
	private IContainer mParent;
	private String mComment;
}
