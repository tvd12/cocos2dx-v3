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

import com.tdgc.cocos2dx.popup.creator.global.Config;

public class Property extends Parameter {
	
	public Property() {
		super();
	}
	
	public Property(Parameter pParameter) {
		super();
		this.mName = pParameter.mName;
		this.mType = pParameter.mType;
		this.mKind = pParameter.mKind;
	}
	
	@Override
	public String toString() {
		if(mType == null || mName == null) {
			return "";
		}
		String result = Config.getInstance().getDefaultNormalPrefix();

		if(mKind.equals(Kind.POINTER)
				|| mKind.equals(Kind.CONSTANT_POINTER)) {
			result = mType + "* " + result + mName;
		}
		else {
			result = mType + " " + result + mName;
		}
		
		return result + ";";
	}
	
	@Override
	public String getName() {
		return Config.getInstance().getDefaultNormalPrefix() 
				+ this.mName;
	}
}
