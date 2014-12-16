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

package com.tvd.gameview.ext.views;

import org.eclipse.jface.resource.FontRegistry;
import org.eclipse.jface.resource.ImageRegistry;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.viewers.IFontProvider;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.jface.viewers.DelegatingStyledCellLabelProvider.IStyledLabelProvider;
import org.eclipse.jface.viewers.StyledString;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;

public class BuildingListLabelProvider extends LabelProvider
		implements IStyledLabelProvider, IFontProvider {
	
	public BuildingListLabelProvider(ImageRegistry mImageRegistry, 
			FontRegistry mFontRegistry) {
		this.mImageRegistry = mImageRegistry;
		this.mFontRegistry = mFontRegistry;
	}
	
	@Override
	public String getText(Object element) {
		if(element instanceof BuildingListElement) {
			return element.toString();
		}
		else {
			return "Unknown type: " + element.getClass();
		}
	}
	
	public Image getImage(Object element) {
		if(element instanceof BuildingListElement) {
			return mImageRegistry.get("iconURL");
		} else {
			return super.getImage(element);
		}
	}

	@Override
	public StyledString getStyledText(Object element) {
		String text = getText(element);
		StyledString ss = new StyledString(text);
		if(element instanceof BuildingListElement) {
			ss.append(" (" + element.toString() + ")",
					StyledString.DECORATIONS_STYLER);
		}
		return ss;
	}

	@Override
	public Font getFont(Object element) {
		Font italic = mFontRegistry.getItalic(
				JFaceResources.DEFAULT_FONT);
		return italic;
	}
	
	private final ImageRegistry mImageRegistry;
	private final FontRegistry mFontRegistry;
	
}
