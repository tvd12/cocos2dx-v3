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

package com.tdgc.cocos2dx.popup.creator.model.basic;

import com.tvd.gameview.ext.value.validate.Validator;

public class Point {

	public Point(float pX, float pY) {
		this.mX = pX;
		this.mY = pY;
	}
	
	@Override
	public String toString() {
		return mX + ", " + mY;
	}
	
	public float getX() {
		return this.mX;
	}
	
	public float getY() {
		return this.mY;
	}
	
	public void add(Point p) {
		this.mX = mX + p.getX();
		this.mY = mY + p.getY();
	}
	
	public static Point parsePoint(String str) {
		Point point = null;
		if(str != null && Validator.isValidDoubleValueString(str)) {
			String xy[] = str.split(",");
			point = new Point(Float.parseFloat(xy[0]), 
					Float.parseFloat(xy[1]));
		} else {
			System.err.println("ERROR::parsePoint " + str + " is invalid point");
		}
		
		return point;
	}
	
	private float mX, mY;
	
}
