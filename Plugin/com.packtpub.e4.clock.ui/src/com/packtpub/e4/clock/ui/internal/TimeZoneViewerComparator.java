package com.packtpub.e4.clock.ui.internal;

import java.util.TimeZone;

import org.eclipse.jface.viewers.Viewer;
import org.eclipse.jface.viewers.ViewerComparator;

public class TimeZoneViewerComparator extends ViewerComparator {

	@Override
	public int compare(Viewer viewer, Object o1, Object o2) {
		int compare = 0;
		if(o1 instanceof TimeZone && o2 instanceof TimeZone) {
			compare = ((TimeZone)o2).getOffset(System.currentTimeMillis())
				- ((TimeZone)o1).getOffset(System.currentTimeMillis());
		} else {
			compare = o1.toString().compareTo(o2.toString());
		}
//		return compare;
		boolean reverse = Boolean.parseBoolean(
				String.valueOf(viewer.getData("REVERSE")));
		return reverse ? -compare : compare;
	}
	
}
