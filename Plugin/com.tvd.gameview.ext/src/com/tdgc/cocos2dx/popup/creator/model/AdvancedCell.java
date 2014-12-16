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

import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.basic.AdvancedObject;

public class AdvancedCell extends AdvancedObject {

	public AdvancedCell() {
		super();
		mSuper = Config.getInstance().getDefaultSuper(mSuffix);
		
		mTemplateName = "ITableCellView";
		mTemplateFile = "cell.template";
		mIsGenerateClass = false;
	}
	
	@Override
	public String implement(boolean pInfunction) {
		return super.implement(pInfunction);
	}
	
	@Override
	public String declarePositions() {
		return super.declarePositions();
	}
	
	@Override
	public String implementPositions() {
		return super.implementPositions();
	}
	public String declareAndImplement() {
		if(mBasicObject.isGenerateClass()) {
			return "";
		}
		StringBuilder builder = new StringBuilder(declare())
			.append(implement(false));
		return builder.toString();
	}
	
	@Override
	public void update() {
		if(mBasicObject.isGenerateClass()) {
			mTemplateName = "ITableCellView full";
		}
	}
	
	@Override
	public void setAdvancedParent(AdvancedObject parent) {
		if(parent != this) {
			super.setAdvancedParent(parent);
		}
	}
	
}
