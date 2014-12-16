/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
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
package com.tvd.gameview.ext.model;

public class ViewModel {
	
	public ViewModel(String name, boolean isDone) {
		this.mName = name;
		this.mIsDone = isDone;
	}
	
	public String getName() {
		String result = mName;
		if(mName.contains("/")) {
			result = mName.substring(mName.lastIndexOf('/') + 1);
		}
		return result;
	}
	
	public String getRealName() {
		return mName;
	}
	
	public boolean isDone() {
		return mIsDone;
	}
	
	@Override
	public String toString() {
		String str = mName;
		if(mIsDone) {
			str += ":done";
		}
		
		return str;
	}

	private String mName;
	private boolean mIsDone;
}
