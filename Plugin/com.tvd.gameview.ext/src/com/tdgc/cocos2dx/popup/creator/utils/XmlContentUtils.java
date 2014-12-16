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

package com.tdgc.cocos2dx.popup.creator.utils;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.Label;

public class XmlContentUtils {
	public static String replaceSpritePosition(String pFileContent, Image pImg) {
		if(pImg == null || pImg.getSize() == null) {
			return pFileContent;
		}
		
		String contents[] = pFileContent.split("\n");
		String newPosition = pImg.getX() + ", " + pImg.getY();
		
		String newSize = pImg.getSize().toString();
		String sizeOpenTag = "<" + Tag.SIZE + ">";
 		String sizeCloseTag = "</" + Tag.SIZE + ">";
		
		for(int i = 0 ; i < contents.length ; i++) {
			if(contents[i].contains(pImg.getId())) {
				while(!(contents[--i].contains(Tag.POSITION) && contents[i].contains(Attribute.VALUE))) {
					if(contents[i].contains(sizeOpenTag)) {
						String currentSize = contents[i].substring(
								contents[i].indexOf(sizeOpenTag) + sizeOpenTag.length(),
								contents[i].indexOf(sizeCloseTag));
						contents[i] = contents[i].replace(currentSize, newSize);
					}
				}
				String currentPosition = contents[i].substring(
						contents[i].indexOf('"') + 1,
						contents[i].lastIndexOf('"'));
				if(!currentPosition.equals("default")) {
					contents[i] = contents[i].replace(currentPosition, newPosition);
				}
				break;
			}
		}
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < contents.length ; i++) {
			builder.append(contents[i])
				.append("\n");
		}
		
		return builder.toString();
	}
	
	public static String replaceSpritePosition(String pFileContent, Label pLabel) {
		String contents[] = pFileContent.split("\n");
		String newPosition = pLabel.getPosition().getX() + ", " 
				+ pLabel.getPosition().getY();
		String openTag = "<" + Tag.POSITION + ">";
		String closeTag = "</" + Tag.POSITION + ">";
		for(int i = 0 ; i < contents.length ; i++) {
			if(contents[i].contains(pLabel.getXmlPositionName())) {
				while(!contents[++i].contains(openTag));
				String currentPosition = contents[i].substring(
						contents[i].indexOf(openTag) + openTag.length(),
						contents[i].indexOf(closeTag));
				if(!currentPosition.equals("default")) {
					contents[i] = contents[i].replace(currentPosition, newPosition);
				}
				break;
			}
		}
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < contents.length ; i++) {
			builder.append(contents[i])
				.append("\n");
		}
		
		return builder.toString();
	}
}
