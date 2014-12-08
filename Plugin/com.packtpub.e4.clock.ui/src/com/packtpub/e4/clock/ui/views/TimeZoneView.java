package com.packtpub.e4.clock.ui.views;

import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TimeZone;

import org.eclipse.jface.dialogs.IDialogSettings;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CTabFolder;
import org.eclipse.swt.custom.CTabItem;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Group;
import org.eclipse.ui.internal.UIPlugin;
import org.eclipse.ui.part.ViewPart;

import com.packtpub.e4.clock.ui.Activator;
import com.packtpub.e4.clock.ui.ClockWidget;
import com.packtpub.e4.clock.ui.internal.TimeZoneComparator;

public class TimeZoneView extends ViewPart {
	
	private String lastTabSelected;

	public TimeZoneView() {
		
	}

	@Override
	public void createPartControl(Composite parent) {
		Map<String, Set<TimeZone>> timeZones =
				TimeZoneComparator.getTimeZones();
		CTabFolder tabs = new CTabFolder(parent, SWT.BOTTOM);
		Iterator<Entry<String, Set<TimeZone>>> regionIterator = 
				timeZones.entrySet().iterator();
		while(regionIterator.hasNext()) {
			Entry<String, Set<TimeZone>> region = 
					regionIterator.next();
			CTabItem item = new CTabItem(tabs, SWT.NONE);
			item.setText(region.getKey());
			Composite clocks = new Composite(tabs, SWT.NONE);
			clocks.setLayout(new RowLayout());
			item.setControl(clocks);
			
			RGB rgb = new RGB(128, 128, 128);
			TimeZone td = TimeZone.getDefault();
			Iterator<TimeZone> timezoneIterator = 
					region.getValue().iterator();
			while(timezoneIterator.hasNext()) {
				TimeZone tz = timezoneIterator.next();
//				ClockWidget clock = new ClockWidget(clocks, SWT.SHADOW_ETCHED_IN);
				Group group = new Group(clocks, SWT.SHADOW_ETCHED_IN);
				group.setText(tz.getID().split("/")[1]);
				ClockWidget clock = new ClockWidget(group, SWT.NONE, rgb);
				clock.setOffset(tz.getOffset(System.currentTimeMillis()) -
					       td.getOffset(System.currentTimeMillis()) / 3600000);
			}
		}
		tabs.setSelection(0);
//		tabs.addSelectionListener(new SelectionAdapter() {
//			@Override
//			public void widgetSelected(SelectionEvent e) {
//				if(e.item instanceof CTabItem) {
//					lastTabSelected = ((CTabItem)e.item).getText();
//				}
//			}
//		});

//		@SuppressWarnings("restriction")
		final IDialogSettings settings = 
			Activator.getDefault().getDialogSettings();
		lastTabSelected = settings.get("lastTabSelected");
		tabs.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				if(e.item instanceof CTabItem) {
					lastTabSelected = ((CTabItem)e.item).getText();
					settings.put("lastTabSelected", lastTabSelected);
				}
			}
		});
		
		if(lastTabSelected == null) {
			tabs.setSelection(0);
		} else {
			CTabItem[] items = tabs.getItems();
			for(CTabItem item : items) {
				if(lastTabSelected.equals(item.getText())) {
					tabs.setSelection(item);
					break;
				}
			}
		}
		
	}
	
//	@Override
//	public void saveState(IMemento memento) {
//		super.saveState(memento);
//		memento.putString("lastTabSelected", lastTabSelected);
//	}
//	
//	@Override
//	public void init(IViewSite site, IMemento memento) 
//			throws PartInitException {
//		super.init(site, memento);
//		if(memento != null) {
//			lastTabSelected = memento.getString("lastTabSelected");
//		}
//	}
	
	@Override
	public void setFocus() {

	}

}
