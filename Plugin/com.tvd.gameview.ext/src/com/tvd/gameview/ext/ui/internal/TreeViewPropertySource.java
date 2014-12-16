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

import java.util.Arrays;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertySource;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import com.tdgc.cocos2dx.popup.creator.model.View;
import com.tvd.gameview.ext.views.BuildingListElement;

class TreeViewElementInfo implements IPropertySource {

	public TreeViewElementInfo(BuildingListElement element) {
		this.mElement = element;
	}
	
	@Override
	public Object getEditableValue() {
		return null;
	}

	@Override
	public IPropertyDescriptor[] getPropertyDescriptors() {
		return new IPropertyDescriptor[] {
				new PropertyDescriptor(TREEVIEW_ELEMENT_INFO, "Tree view element info")
		};
	}

	@Override
	public Object getPropertyValue(Object id) {
		if(id.equals(TREEVIEW_ELEMENT_INFO)) {
			return new TreeViewPropertySource(mElement);
		}
		return null;
	}

	@Override
	public boolean isPropertySet(Object id) {
		return false;
	}

	@Override
	public void resetPropertyValue(Object id) {
		
	}

	@Override
	public void setPropertyValue(Object id, Object value) {
		
	}
	
	public static final Object TREEVIEW_ELEMENT_INFO = new Object();
	private BuildingListElement mElement;
}

class TreeViewPropertySource implements IPropertySource {

	public TreeViewPropertySource(BuildingListElement element) {
		this.mElement = element;
	}
	
	@Override
	public Object getEditableValue() {
		return null;
	}

	@Override
	public IPropertyDescriptor[] getPropertyDescriptors() {
		IPropertyDescriptor propertyDescriptor[] = new IPropertyDescriptor[] {
				new PropertyDescriptor(NAME, "name"),
				new PropertyDescriptor(DEVICE, "device"),
				new PropertyDescriptor(FILEPATH, "file path"),
				new PropertyDescriptor(PROJECT, "project"),
				new PropertyDescriptor(PARENT, "parent"),
				new PropertyDescriptor(VIEW, "view")
			};
		if(mElement.getParent() != null) {
			if(mElement.getParent().getParent() == null) {
				return propertyDescriptor;
			} else {
				return Arrays.copyOf(propertyDescriptor, 
						propertyDescriptor.length - 1);
			}
		}
		
		return Arrays.copyOf(propertyDescriptor, 
				propertyDescriptor.length - 2);
	}

	@Override
	public Object getPropertyValue(Object id) {
		if(id.equals(NAME)) {
			return mElement.getName();
		}
		else if(id.equals(PARENT)) {
			return mElement.getParent();
		}
		else if(id.equals(DEVICE)) {
			return mElement.getDevice();
		}
		else if(id.equals(FILEPATH)) {
			return mElement.getFilePath();
		}  
		else if(id.equals(PROJECT)) {
			return mElement.getProject();
		}
		
		View view = mElement.getViewForRootElement();
		if(view != null) {
			return new ViewPropertySource(view);
		}
		return null;
	}

	@Override
	public boolean isPropertySet(Object id) {
		return false;
	}

	@Override
	public void resetPropertyValue(Object id) {
		
	}

	@Override
	public void setPropertyValue(Object id, Object value) {
		
	}
	
	public static final Object INFO 	= new Object();
	public static final Object NAME 	= new Object();
	public static final Object PARENT	= new Object();
	public static final Object DEVICE	= new Object();
	public static final Object FILEPATH	= new Object();
	public static final Object PROJECT	= new Object();
	public static final Object VIEW		= new Object();
	private BuildingListElement mElement;
}
