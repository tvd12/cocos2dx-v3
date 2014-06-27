package com.packtpub.e4.clock.ui.internal;

import java.util.TimeZone;

public class TimeZoneDisplayNameColumn extends TimeZoneColumn {

	@Override
	public String getText(Object element) {
		if(element instanceof TimeZone) {
			return ((TimeZone)element).getDisplayName();
		} 
		return "";
	}

	@Override
	public String getTitle() {
		return "Display Name";
	}

}
