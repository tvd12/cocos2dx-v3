package com.packtpub.e4.clock.ui.views;

import java.net.URL;
import java.util.TimeZone;

import org.eclipse.jface.action.MenuManager;
import org.eclipse.jface.resource.FontRegistry;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.ImageRegistry;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.ResourceManager;
import org.eclipse.jface.viewers.DelegatingStyledCellLabelProvider;
import org.eclipse.jface.viewers.DoubleClickEvent;
import org.eclipse.jface.viewers.IDoubleClickListener;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.TreeViewer;
import org.eclipse.jface.viewers.Viewer;
import org.eclipse.jface.viewers.ViewerFilter;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.part.ViewPart;

import com.packtpub.e4.clock.ui.internal.TimeZoneComparator;
import com.packtpub.e4.clock.ui.internal.TimeZoneDialog;
import com.packtpub.e4.clock.ui.internal.TimeZoneSelectionListener;
import com.packtpub.e4.clock.ui.internal.TimeZoneViewerComparator;
import com.packtpub.e4.clock.ui.internal.TimeZoneViewerFilter;

public class TimeZoneTreeView extends ViewPart {

	private ISelectionListener selectionListener;
	
	public TimeZoneTreeView() {
	}

	@Override
	public void createPartControl(Composite parent) {
		ResourceManager rm = JFaceResources.getResources();
		LocalResourceManager lrm = new LocalResourceManager(rm, parent);
		
		ImageRegistry ir = new ImageRegistry(lrm);
		URL sample = this.getClass().getResource("/icons/sample.gif");
		ir.put("sample", ImageDescriptor.createFromURL(sample));
		FontRegistry fr = JFaceResources.getFontRegistry();
		
		treeViewer = new TreeViewer(parent,
				SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
//		treeViewer.setLabelProvider(new TimeZoneLabelProvider());
//		treeViewer.setLabelProvider(new TimeZoneLabelProvider(ir));
//		treeViewer.setLabelProvider(new DelegatingStyledCellLabelProvider(
//				new TimeZoneLabelProvider(ir)));
		treeViewer.setData("REVERSE", Boolean.TRUE);
		treeViewer.setComparator(new TimeZoneViewerComparator());
		treeViewer.setLabelProvider(new DelegatingStyledCellLabelProvider(
				new TimeZoneLabelProvider(ir, fr)));
		treeViewer.setContentProvider(new TimeZoneContentProvider());
		treeViewer.setInput(new Object[] {TimeZoneComparator.getTimeZones()});
		treeViewer.setFilters(new ViewerFilter[] {
			new TimeZoneViewerFilter("GMT")	
		});
		treeViewer.setExpandPreCheckFilters(true);
		treeViewer.addDoubleClickListener(new IDoubleClickListener() {
			
			@Override
			public void doubleClick(DoubleClickEvent event) {
				Viewer viewer = event.getViewer();
				Shell shell = viewer.getControl().getShell();
//				MessageDialog.openInformation(shell, "Double click", 
//						"Double click detected");
				ISelection sel = viewer.getSelection();
				Object selectedValue;
				if(!(sel instanceof IStructuredSelection) || sel.isEmpty()) {
					selectedValue = null;
				} else {
					selectedValue = ((IStructuredSelection)sel).getFirstElement();
					
					if(selectedValue instanceof TimeZone) {
						TimeZone timeZone = (TimeZone)selectedValue;
//						MessageDialog.openInformation(shell, timeZone.getID(), 
//								timeZone.toString());
						new TimeZoneDialog(shell, timeZone).open();
					}
				}
			}
		});
//		System.out.println("Adapter is " + Platform.getAdapterManager().
//			      getAdapter(TimeZone.getDefault(),IPropertySource.class));
		this.getSite().setSelectionProvider(treeViewer);
		selectionListener = new TimeZoneSelectionListener(
				treeViewer, getSite().getPart());
		this.getSite().getWorkbenchWindow().getSelectionService()
			.addSelectionListener(selectionListener);
	}

	@Override
	public void setFocus() {
		treeViewer.getControl().setFocus();
	}
	
	@Override
	public void dispose() {
		if(selectionListener != null) {
			this.getSite().getWorkbenchWindow().getSelectionService()
				.removeSelectionListener(selectionListener);
			selectionListener = null;
		}
		super.dispose();
	}
	
	private void hookContextMenu(Viewer viewer) {
		MenuManager manager = new MenuManager("#PopupMenu");
		Menu menu = manager.createContextMenu(viewer.getControl());
		viewer.getControl().setMenu(menu);
		this.getSite().registerContextMenu(manager, viewer);
	}
	
	private TreeViewer treeViewer;

}
