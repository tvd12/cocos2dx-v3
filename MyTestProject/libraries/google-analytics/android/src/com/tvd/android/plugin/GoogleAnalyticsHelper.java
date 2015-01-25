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

import com.google.android.gms.analytics.HitBuilders;
import com.google.android.gms.analytics.Tracker;
import com.tvd.android.plugin.AnalyticsApplication;
import com.tvd.android.plugin.AnalyticsException;

public class GoogleAnalyticsHelper {

	public static void sSendScreenView(String screenView) {
		try {
			Tracker tracker = sApplication.getTracker();
			tracker.setScreenName(screenView);
			tracker.send(new HitBuilders.AppViewBuilder().build());
		} catch (AnalyticsException e) {
			e.printStackTrace();
		}
	}
	
	public static void sSendEvent(String category, 
			String action, String label, long value) {
		try {
			Tracker tracker = sApplication.getTracker();
			tracker.send(new HitBuilders.EventBuilder()
				.setCategory(category)
				.setAction(action)
				.setLabel(label)
				.setValue(value)
				.build());
		} catch (AnalyticsException e) {
			e.printStackTrace();
		}
	}
	
	public static void sStartSession(String screenView) {
		try {
			Tracker tracker = sApplication.getTracker();
			tracker.setScreenName(screenView);
			tracker.send(new HitBuilders.AppViewBuilder()
				.setNewSession()
				.build());
		} catch(AnalyticsException e) {
			e.printStackTrace();
		}
	}
	
	public static void sEndSession(String screenView) {
	}
	
	public static void sSendUserTimings(long loadTime,
			String category, long interval,
			String name, String label) {
		try {
			Tracker tracker = sApplication.getTracker();
			
			//Build and send timing
			tracker.send(new HitBuilders.TimingBuilder()
				.setCategory(category)
				.setValue(interval)
				.setVariable(name)
				.setLabel(label)
				.build());
		} catch(AnalyticsException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * An example method called when a user signs in to an authentication system.
	 *
	 * @param User user represents a generic User object returned by an 
	 * authentication system on sign in.
	 */
	public static void sSignInWithUser(String userId,
			String category, String label, long value) {
		try {
			// Be careful when creating new trackers 
			// -- it is possible to create multiple trackers for the
			// same tracking Id.
			Tracker tracker = sApplication.getTracker();
			
			// You only need to set User ID on a tracker once. 
			// By setting it on the tracker, the ID will be
			// sent with all subsequent hits.
			tracker.set("&uid", userId);
			
			// This hit will be sent with the User ID value and be visible 
			// in User-ID-enabled views (profiles).
			tracker.send(new HitBuilders.EventBuilder()
				.setCategory(category)
				.setLabel(label)
				.setAction("user_sign_in")
				.setValue(value)
				.build());
			
		} catch(AnalyticsException e) {
			e.printStackTrace();
		}
	}
	
	public static AnalyticsApplication sApplication;
}
