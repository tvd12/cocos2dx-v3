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

import java.util.ArrayList;
import java.util.List;

import com.tdgc.cocos2dx.popup.creator.model.ItemGroup;
import com.tdgc.cocos2dx.popup.creator.model.View;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;

public class ViewUtils {
	
	public static String implementGroups(List<ItemGroup> groups) {
		StringBuilder builder = new StringBuilder();
		for(int i = groups.size() - 1 ; i >= 0 ; i--) {
			if(groups.get(i).isAddToView()) {
				builder.append(groups.get(i).implement(false))
					.append("\n");
				groups.get(i).setAddToView(false);
			}
		}
		
		return builder.toString();
	}
	
	public static String declareGroups(List<ItemGroup> groups) {
		StringBuilder builder = new StringBuilder();
		for(ItemGroup group : groups) {
			builder.append(group.declare())
				.append("\n");
		}
		
		return builder.toString();
	}
	
	public static String declarePositionGroups(List<ItemGroup> groups) {
		StringBuilder builder = new StringBuilder();
		for(ItemGroup group : groups) {
			builder.append(group.declarePosition());
		}
		
		return builder.toString();
	}
	
	public static String implementPositionGroups(List<ItemGroup> groups) {
		StringBuilder builder = new StringBuilder();
		for(ItemGroup group : groups) {
			builder.append(group.implementPosition());
		}
		
		return builder.toString();
	}
	
	public static String createElementTags(List<ItemGroup> groups, int begin) {
		StringBuilder builder = new StringBuilder();
		for(int i = 0 ; i < groups.size() ; i++) {
			int tag = (i > 0) ? (groups.size() + i + 2) : (i + 1);
			builder.append(groups.get(i).createElementTags(tag));
		}
		
		return builder.toString();
	}
	
	public static void implementObject(CommonObject obj, StringBuilder builder) {
		if(obj == null) {
			return;
		}
		
		List<List<ItemGroup>> groups = new ArrayList<List<ItemGroup>>();
		groups.add(obj.getSpriteGroups());
		groups.add(obj.getMenuGroups());
		groups.add(obj.getMenuItemGroups());
		groups.add(obj.getLabelGroups()); 
		for(int k = 0 ; k < groups.size() ; k++) {
			List<ItemGroup> group = groups.get(k);
			for(int i = group.size() - 1 ; i >= 0  ; i--) {
				if(group.get(i) == null || !group.get(i).isAddToView()) {
					continue;
				}
				builder.append(group.get(i).implement(false))
					.append("\n");
				for(int j = group.get(i).getItems().size() - 1 ; 
						 j >= 0 ; j--) {
					implementObject(group.get(i).getItems().get(j), builder);
				}
				group.get(i).setReferenceCount(1);
			}
		}
	}
	
	public static void blockOrUnlockAddingGroupToView(
			CommonObject obj, boolean isAdding) {
		if(obj == null) {
			return;
		}
		
		List<List<ItemGroup>> groups = new ArrayList<List<ItemGroup>>();
		groups.add(obj.getSpriteGroups());
		groups.add(obj.getMenuGroups());
		groups.add(obj.getMenuItemGroups());
		groups.add(obj.getLabelGroups());
		for(int k = 0 ; k < groups.size() ; k++) {
			List<ItemGroup> group = groups.get(k);
			for(int i = group.size() - 1 ; i >= 0  ; i--) {
				if(group.get(i) == null) {
					continue;
				}
				for(int j = group.get(i).getItems().size() - 1 ; 
						 j >= 0 ; j--) {
					blockOrUnlockAddingGroupToView(
							group.get(i).getItems().get(j), isAdding);
				}
				group.get(i).setAddToView(isAdding);
			}
		}
	}
	
	public static void blockAddingGroupToView(CommonObject obj) {
		blockOrUnlockAddingGroupToView(obj, false);
	}
	
	public static void unlockAddingGroupToView(CommonObject obj) {
		blockOrUnlockAddingGroupToView(obj, true);
	}
	
	public static void statisticsItemView(CommonObject obj, View view) {
		if(obj == null) {
			return;
		} 
		List<List<ItemGroup>> groups = new ArrayList<List<ItemGroup>>();
		groups.add(obj.getSpriteGroups());
		groups.add(obj.getMenuGroups());
		groups.add(obj.getMenuItemGroups());
		groups.add(obj.getLabelGroups());
		groups.add(obj.getTableGroups());
		if(obj.getCellGroups() != null) {
			groups.add(obj.getCellGroups());
		}
		for(int k = 0 ; k < groups.size() ; k++) {
			List<ItemGroup> group = groups.get(k);
			for(int i = group.size() - 1 ; i >= 0  ; i--) {
				if(group.get(i) == null) {
					continue;
				}
				for(int j = group.get(i).getItems().size() - 1 ; 
						 j >= 0 ; j--) {
					statisticsItemView(
							group.get(i).getItems().get(j),
							view);
				}
				int numberOfChilds = group.get(i).getItems().size();
				switch (group.get(i).getType()) {
				case ItemGroup.Type.LABLE:
					view.addNumberOfLabels(numberOfChilds);
					break;
				case ItemGroup.Type.MENU:
					view.addNumberOfMenus(numberOfChilds);
					break;
				case ItemGroup.Type.MENUITEM:
					view.addNumberOfMenuItems(numberOfChilds);
					break;
				case ItemGroup.Type.PROGRESSBAR:
					view.addNumberOfProgressbar(numberOfChilds);
					break;
				case ItemGroup.Type.SPRITE:
					view.addNumberOfSprites(numberOfChilds);
					break;
				case ItemGroup.Type.TABLE:
					view.addNumberOfTable(numberOfChilds);
					break;
				default:
					break;
				}
			}
		}
	}
}
