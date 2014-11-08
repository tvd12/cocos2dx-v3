package com.packtpub.e4.clock.ui.internal;

import java.util.TimeZone;

public class TimeZoneOffsetColumn extends TimeZoneColumn {

	@Override
	public String getText(Object element) {
		if(element instanceof TimeZone) {
			return ((TimeZone)element).getOffset(System.currentTimeMillis())
					/3600000 + "h";
		} 
		return "";
	}

	@Override
	public String getTitle() {
		return "Offset";
	}

}
