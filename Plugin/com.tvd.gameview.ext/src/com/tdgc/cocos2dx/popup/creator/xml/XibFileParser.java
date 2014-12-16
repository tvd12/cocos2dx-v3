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

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.log.Log;
import com.tdgc.cocos2dx.popup.creator.model.Image;
import com.tdgc.cocos2dx.popup.creator.model.Label;

public class XibFileParser extends DefaultHandler {
	
	public XibFileParser(List<Image> pImages, List<Label> pLabels) {
		this.mImages = pImages;
		this.mLabels = pLabels;
	}
	
	@Override
	public void startDocument() throws SAXException {
		mParentQName = "";
	}
	
	@Override
	public void startElement(String namespaceURI, String localName,
			String qName, Attributes atts) throws SAXException {
		try {
		if(qName.equals(Tag.IMAGE_VIEW)) {
			String id = getAttributeValue(Attribute.ID, atts);
			for(int i = 0 ; i < mImages.size() ; i++) {
				if( mImages.get(i).getImageViewId() != null
						&& mImages.get(i).getImageViewId().equals(id)) {
					mCurrentImage = mImages.get(i);
					break;
				}
			}
			mParentQName = qName;
		}
		else if(qName.equals(Tag.LABEL)) {
			String id = getAttributeValue(Attribute.ID, atts);
			for(int i = 0 ; i < mLabels.size() ; i++) {
				if(mLabels.get(i).getLabelViewId().equals(id)) {
					mCurrentLabel = mLabels.get(i);
					break;
				}
			}
			mParentQName = qName;
		}
		else if(qName.equals(Tag.RECT)) {
			float x = getNumber(getAttributeValue(Attribute.X, atts));
			float y = getNumber(getAttributeValue(Attribute.Y, atts));
			float width = getNumber(getAttributeValue(Attribute.WIDTH, atts));
			float height = getNumber(getAttributeValue(Attribute.HEIGHT, atts));
			if(mParentQName.equals(Tag.IMAGE_VIEW) && mCurrentImage != null) {
				mCurrentImage.setSize(width, height);
				mCurrentImage.setXY(x, y);
			} 
			else if(mParentQName.equals(Tag.LABEL) && mCurrentLabel != null) {
				mCurrentLabel.setSize(width, height);
				mCurrentLabel.setLocationInView(x, y);
			}
		}
		else if(qName.equals(Tag.FONT_DESCRIPTION)) {
			if(mParentQName.equals(Tag.LABEL) && mCurrentLabel != null) {
				mCurrentLabel.setFontName(getAttributeValue(Attribute.NAME, atts));
				mCurrentLabel.setFontFamily(getAttributeValue(Attribute.FAMILY, atts));
				mCurrentLabel.setFontSizeFloat(getAttributeValue(Attribute.POINT_SIZE, atts));
			}
		}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
		
		
	@Override
	public void endDocument() throws SAXException {
	}
	
	@Override
	public void endElement(String namespaceURI, String localName, 
			String qName) throws SAXException {
	}
	
	@Override
	public void characters(char[] ch, int start, int length) {
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
	
	private float getNumber(String value) {
		if(value == null) {
			return 0;
		}
		
		float result = 0;
		try {
			result = Float.parseFloat(value);
		} catch(NumberFormatException e) {
			Log.e(e);
		} catch (NullPointerException e) {
			Log.e(e);
		}
		return result;
		
	}

	private List<Image> mImages;
	private List<Label> mLabels;
	private Image mCurrentImage;
	private Label mCurrentLabel;
	private String mParentQName;
}
