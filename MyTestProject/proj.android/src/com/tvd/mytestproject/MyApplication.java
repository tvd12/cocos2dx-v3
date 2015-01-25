package com.tvd.mytestproject;

import com.tvd.android.plugin.AnalyticsApplication;

public class MyApplication extends AnalyticsApplication {

	@Override
	public String appTrackerId() {
		return "UA-36352887-9";
	}
	
	@Override
	public String appName() {
		return "My Test Project";
	}
	
	@Override
	public String appVersion() {
		return "1.0.0";
	}
	
}
