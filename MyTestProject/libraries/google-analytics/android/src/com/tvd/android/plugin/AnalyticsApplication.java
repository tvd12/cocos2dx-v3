/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
 *
 * This file is part of Google analytics plugin.
 * Google analytics plugin is free library: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Google analytics plugin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Google analytics plugin.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.tvd.android.plugin;

import java.util.HashMap;
import java.util.Map;

import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.Logger;
import com.google.android.gms.analytics.Tracker;

import android.app.Application;

public class AnalyticsApplication extends Application {
	
	public AnalyticsApplication() {
		super();
	}
	
	public void setTrackerName(TrackerName pTrackerName) {
		mTrackerName = pTrackerName;
	}

	public TrackerName getTrackerName() {
		return mTrackerName;
	}
	
	public String appTrackerId() {
		return "";
	}
	
	public String globalTrackerId() {
		return "";
	}
	
	public String ecommerceTrackerId() {
		return "";
	}
	
	public String appName() {
		return getClass().getSimpleName();
	}
	
	public String appVersion() {
		return "1.0.0";
	}
	
	public long sessionTimeOut() {
		return 300;
	}
	
	public synchronized Tracker getTracker(TrackerName trackerName) 
			throws AnalyticsException {
		String trackerId = appTrackerId();
		if(trackerName == TrackerName.GLOBAL_TRACKER) {
			trackerId = globalTrackerId();
		}
		else if(trackerName == TrackerName.ECOMMERCE_TRACKER) {
			trackerId = ecommerceTrackerId();
		}
		if(trackerId == null ||
				trackerId.trim().length() == 0) {
			throw new AnalyticsException();
		}
		
		if(mTrackers.containsKey(getTrackerName())) {
			return mTrackers.get(getTrackerName());
		}
		
		GoogleAnalytics analytics = GoogleAnalytics.getInstance(this);
		analytics.getLogger().setLogLevel(Logger.LogLevel.VERBOSE);
		
		Tracker tracker = analytics.newTracker(trackerId);
		tracker.setAppName(appName());
		tracker.setAppVersion(appVersion());
		tracker.setSessionTimeout(sessionTimeOut());
		mTrackers.put(trackerName, tracker);
		
		return tracker;
	}
	
	public synchronized Tracker getTracker() throws AnalyticsException {
		return getTracker(getTrackerName());
	}
	
	public enum TrackerName {
        APP_TRACKER, // Tracker used only in this app.
        GLOBAL_TRACKER, // Tracker used by all the apps from a company. eg: roll-up tracking.
        ECOMMERCE_TRACKER, // Tracker used by all ecommerce transactions from a company.
    }
	
	protected TrackerName mTrackerName = 
			TrackerName.APP_TRACKER;
	protected Map<TrackerName, Tracker> mTrackers = 
			new HashMap<AnalyticsApplication.TrackerName, Tracker>();;
	
}
