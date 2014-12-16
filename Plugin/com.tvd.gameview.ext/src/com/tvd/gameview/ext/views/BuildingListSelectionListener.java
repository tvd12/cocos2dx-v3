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

import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.StructuredViewer;
import org.eclipse.jface.viewers.Viewer;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.IWorkbenchPart;

public class BuildingListSelectionListener implements ISelectionListener {
	
	public BuildingListSelectionListener(Viewer viewer, IWorkbenchPart part) {
		this.mViewer = viewer;
		this.mPart = part;
	}
	
	@Override
	public void selectionChanged(IWorkbenchPart part, ISelection sel) {
//		System.out.println("BuildingListSelectionListener::selectionChanged::sel instanceof = " + sel.getClass().getName());
		if(part != this.mPart && sel instanceof IStructuredSelection) {
			Object selected = ((IStructuredSelection)sel).getFirstElement();
			Object current = ((IStructuredSelection)mViewer.getSelection())
					.getFirstElement();
//			System.out.println("BuildingListSelectionListener::selectionChanged::selected instanceof = " + ((selected != null)?selected.getClass().getName():"null"));
			if(selected != current && selected instanceof BuildingListElement) {
				mViewer.setSelection(sel);
				if(mViewer instanceof StructuredViewer) {
					((StructuredViewer)mViewer).reveal(selected);
				}
			}
		}
	}
	
	private Viewer mViewer;
	private IWorkbenchPart mPart;
	
}
