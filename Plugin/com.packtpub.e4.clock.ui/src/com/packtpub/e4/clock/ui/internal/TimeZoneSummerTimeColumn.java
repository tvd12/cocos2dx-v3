package com.packtpub.e4.clock.ui.internal;

import java.util.TimeZone;

public class TimeZoneSummerTimeColumn extends TimeZoneColumn {

	@Override
	public String getText(Object element) {
		if(element instanceof TimeZone) {
			return ((TimeZone)element).useDaylightTime() + "";
		} 
		return "";
	}

	@Override
	public String getTitle() {
		return "Summer Time";
	}

}
