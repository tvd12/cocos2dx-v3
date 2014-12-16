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

package com.tvd.gameview.ext.ui.internal;

import org.eclipse.core.runtime.IAdapterFactory;
import org.eclipse.ui.views.properties.IPropertySource;

import com.tvd.gameview.ext.views.BuildingListElement;

public class TreeViewAdapterFactory implements IAdapterFactory {

	public TreeViewAdapterFactory() {
		System.out.println("construction adapter");
	}
	
	@SuppressWarnings("rawtypes")
	@Override
	public Class[] getAdapterList() {
		return new Class[] {
				IPropertySource.class
		};
	}
	
	@SuppressWarnings("rawtypes")
	@Override
	public Object getAdapter(Object o, Class type) {
		if(type == IPropertySource.class && o instanceof BuildingListElement) {
			return new TreeViewElementInfo((BuildingListElement)o);
		} else {
			return null;
		}
	}
}
