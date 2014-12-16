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

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;

public class XmlFormatter_1_0 {
	public XmlFormatter_1_0(String xml) {
		mXmlContent = xml;
	}
	
	public void setLineWidth(int width) {
		mLineWidth = width;
	}
	
	public String format() {
		String strs[] = mXmlContent.split("\n");
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < strs.length ; i++) {
			
		}
		
		return builder.toString();
	}
	
	public static String format(String xmlContent) {
		String strs[] = xmlContent.split("\n");
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < strs.length ; i++) {
			String str = strs[i];
			if(strs[i].contains(Tag.IMAGE) &&
					strs[i].contains(Attribute.PHONY_PATH)) {
				StringBuilder tab = new StringBuilder();
				for(int j = 0 ; j < strs[i].length() ; j++) {
					if(strs[i].charAt(j) != '<') {
						tab.append(strs[i].charAt(j));
					} else {
						break;
					}
				}
				tab.append("\t\t");
				str = strs[i].replace(Attribute.PHONY_PATH + "=", 
						"\n" + tab.toString() + Attribute.PHONY_PATH + "=");
			}
			if(str.endsWith("\"/>")) {
				str = str.replace("\"/>", "\" />");
			}
			builder.append(str).append("\n");
		}
		
		return builder.toString();
	}
	
	@SuppressWarnings("unused")
	private int mLineWidth;
	private String mXmlContent;
}
