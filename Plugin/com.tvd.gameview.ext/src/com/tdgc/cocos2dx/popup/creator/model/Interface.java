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
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class Interface {
	
	public Interface() {
		this.mXmlTagName = Tag.NEXT;
	}
	
	public Interface(CommonObject core) {
		this();
		this.mCore = core;
		this.mCore.setInterface(this);
	}
	
	public Interface(CommonObject core, Image img) {
		this(core);
		this.mImage = img;
		this.mCore.setInterface(this);
		this.mImage.setTabCount(mCore.getTabCount() + 1);
		this.mImage.setParent(mCore);
	}
	
	public void setImage(Image image) {
		this.mImage = image;
	}
	
	public Image getImage() {
		return this.mImage;
	}
	
	public void setCore(CommonObject core) {
		this.mCore = core;
	}
	
	public CommonObject getCore() {
		return this.mCore;
	}
	
	public String toXML() {
		String tab = StringUtils.tab(mCore.getTabCount());
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " ")
			.append(Attribute.VISIBLE + "=\"true\" ")
			.append(Attribute.COMMENT + "=\"\">");
		builder.append("\n" + tab + "\t");
		builder.append("<" + Tag.POSITION + " " + Attribute.VALUE 
				+ "=\"" + mCore.getPositionString() + "\" />");

		builder.append("\n" + mImage.toXML());
		builder.append("\n")
			.append(tab)
			.append("</" + mXmlTagName + ">");
		
		builder.append("\n");
		
		return builder.toString();
	}
	
	private CommonObject mCore;
	private String mXmlTagName;
	private Image mImage;
}
