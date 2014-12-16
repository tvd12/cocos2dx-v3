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

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertySource;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import com.tdgc.cocos2dx.popup.creator.model.View;

public class ViewPropertySource implements IPropertySource {

	public ViewPropertySource(View view) {
		this.mView = view;
	}
	
	@Override
	public Object getEditableValue() {
		return null;
	}

	@Override
	public IPropertyDescriptor[] getPropertyDescriptors() {
		return new IPropertyDescriptor[] {
				new PropertyDescriptor(CLASS_NAME, "class name"),
				new PropertyDescriptor(SUPER, "super"),
				new PropertyDescriptor(NUMBER_OF_LABELS, "number of labels"),
				new PropertyDescriptor(NUMBER_OF_MENUITEMS, "number of menuitems"),
				new PropertyDescriptor(NUMBER_OF_MENUS, "number of menus"),
				new PropertyDescriptor(NUMBER_OF_PROGRESSBARS, "number of progressbars"),
				new PropertyDescriptor(NUMBER_OF_RESOUCES, "number of resources"),
				new PropertyDescriptor(NUMBER_OF_SPRITES, "number of sprites"),
				new PropertyDescriptor(NUMBER_OF_TABLES, "number of tables")
		};
	}

	@Override
	public Object getPropertyValue(Object id) {
		if(id.equals(CLASS_NAME)) {
			return mView.getClassName();
		} 
		else if(id.equals(SUPER)) {
			return mView.getSuper();
		}
		else if(id.equals(NUMBER_OF_LABELS)) {
			return mView.getNumberOfLabels();
		}
 		else if(id.equals(NUMBER_OF_MENUITEMS)) {
 			return mView.getNumberOfMenuItems();
 		}
 		else if(id.equals(NUMBER_OF_MENUS)) {
 			return mView.getNumberOfMenus();
 		}
 		else if(id.equals(NUMBER_OF_PROGRESSBARS)) {
 			return mView.getNumberOfProgressbar();
 		}
 		else if(id.equals(NUMBER_OF_RESOUCES)) {
 			return mView.getResource().getImages().size();
 		}
 		else if(id.equals(NUMBER_OF_SPRITES)) {
 			return mView.getNumberOfSprites();
 		}
 		else if(id.equals(NUMBER_OF_TABLES)) {
 			return mView.getNumberOfTable();
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

	
	private static final Object CLASS_NAME 			= new Object();
	private static final Object SUPER				= new Object();
	private static final Object NUMBER_OF_LABELS		= new Object();
	private static final Object NUMBER_OF_SPRITES	= new Object();
	private static final Object NUMBER_OF_MENUITEMS	= new Object();
	private static final Object NUMBER_OF_MENUS		= new Object();
	private static final Object NUMBER_OF_TABLES		= new Object();
	private static final Object NUMBER_OF_PROGRESSBARS	= new Object();
	private static final Object NUMBER_OF_RESOUCES		= new Object();
	private View mView;
	
}
