/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.tdgc.videopokerjackpot;

import com.sbstrm.appirater.Appirater;
import com.tdgc.videopokerjackpot.utils.TDGAndroidUtils;
import com.tdgc.videopokerjackpot.utils.TDGInAppHelper;
import com.ezibyte.social.EziSocialManager;
import com.google.analytics.tracking.android.EasyTracker;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.chartboost.sdk.*;
import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;

public class DragonVideoPoker extends Cocos2dxActivity{
	
	protected static final String TAG = "DragonVideoPoker";
	
	private static Context sContext = null;
	private TDGInAppHelper inAppHelper = null;
	private Chartboost cb;

    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		DragonVideoPoker.sContext = DragonVideoPoker.this;

		// init Utils
		TDGAndroidUtils.getInstance();
		
		// init IAP
		this.inAppHelper =  TDGInAppHelper.getInstance();

		// init key hash -> for Facebook
		TDGAndroidUtils.sGenerateFbKeyHash();
		
		Appirater.appLaunched(this);

		// Add chartboost
		this.addChartboost();

		// ezisocial
		EziSocialManager.setApplicationID(this.getApplicationContext().getString(R.string.app_id));
		EziSocialManager.setEnableDebugLogs(true);
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// DragonVideoPoker should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     

    public static Context getContext() {
    	return DragonVideoPoker.sContext;
    }

	@Override
	  public void onStart() {
	    super.onStart();
	    // The rest of your onStart() code.
	    // Init Google Analytics
	    EasyTracker.getInstance(this).activityStart(this);
	    
	    TDGAndroidUtils.getInstance();
	    
	    this.cb.onStart(this);

		// Send start new game event
	    TDGAndroidUtils.sEventMeasurement("Main Category", 
	    		"Start a new game", 
	    		"Android Version", 
	    		1);
	  }

	  @Override
	  public void onStop() {
	    super.onStop();
	    // The rest of your onStop() code.
        this.cb.onStop(this);
	    EasyTracker.getInstance(this).activityStop(this);  // Add this method.
	  }
	  
	 @Override
	 public void onActivityResult(int requestCode, int resultCode, Intent data) {
		 if (TDGInAppHelper.sInAppHelper.handleActivityResult(requestCode, resultCode, data)) {	
		        inAppHelper.onActivityResult(requestCode, resultCode, data);
	     } else {
	        EziSocialManager.onActivityResult(requestCode, resultCode, data);
	     }
	}
	 
	 @Override
	 protected void onResume() {
		 super.onResume();
//		 this.registerReceiver(mHandleMessageReceiver, new IntentFilter(
//					DISPLAY_MESSAGE_ACTION));
		 if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.GINGERBREAD) {
			 this.getWindow().getDecorView().setSystemUiVisibility(
                 View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                 | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                 | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                 | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                 | View.SYSTEM_UI_FLAG_FULLSCREEN
                 | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
		 }
		 
		 // facebook install ads counter
		 com.facebook.AppEventsLogger.activateApp(
				 this, 
				 this.getApplicationContext().getString(R.string.app_id));

	}
	 
	 @Override
	 public void onWindowFocusChanged(boolean hasFocus) {
	         super.onWindowFocusChanged(hasFocus);
	     if (hasFocus) {
	    	 //do nothing
			 if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.GINGERBREAD) {
				 this.getWindow().getDecorView().setSystemUiVisibility(
	                 View.SYSTEM_UI_FLAG_LAYOUT_STABLE
	                 | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
	                 | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
	                 | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
	                 | View.SYSTEM_UI_FLAG_FULLSCREEN
	                 | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
			 	}
			 }
	 }
		
	@Override
	public void onDestroy() {
//		if (mRegisterTask != null) {
//			mRegisterTask.cancel(true);
//		}
//		try {
//			unregisterReceiver(mHandleMessageReceiver);
//			GCMRegistrar.onDestroy(this);
//		} catch (Exception e) {
//			Log.e("UnRegister Receiver Error", "> " + e.getMessage());
//		}
		 super.onDestroy();
	     this.cb.onDestroy(this);
	}

    @Override
    public void onBackPressed() {

        // If an interstitial is on screen, close it. Otherwise continue as normal.
        if (this.cb.onBackPressed())
            return;
        else
            super.onBackPressed();
    }

    private void addChartboost()
    {
    	this.cb = Chartboost.sharedChartboost();
    	String appId = this.getApplicationContext().getString(R.string.chartboost_app_id);
    	String appSignature = this.getApplicationContext().getString(R.string.chartboost_app_signature);
    	this.cb.onCreate(this, appId, appSignature, this.chartBoostDelegate);

    	// Cache an interstitial at some named locations -- (Pro Tip: do this!)
    	this.cb.cacheInterstitial(this.getApplicationContext().getString(R.string.chartboost_bonus_interstitial));
   	}

    //
    // Chartboost delegate
    //
	private ChartboostDelegate chartBoostDelegate = new ChartboostDelegate() {

		/*
		 * Chartboost delegate methods
		 * 
		 * Implement the delegate methods below to finely control Chartboost's behavior in your app
		 * 
		 * Minimum recommended: shouldDisplayInterstitial()
		 */
	
		
		/* 
		 * shouldDisplayInterstitial(String location)
		 *
		 * This is used to control when an interstitial should or should not be displayed
		 * If you should not display an interstitial, return false
		 *
		 * For example: during gameplay, return false.
		 *
		 * Is fired on:
		 * - showInterstitial()
		 * - Interstitial is loaded & ready to display
		 */
		@Override
		public boolean shouldDisplayInterstitial(String location) {
			Log.i(TAG, "SHOULD DISPLAY INTERSTITIAL '"+location+ "'?");
			return true;
		}
		
		/*
		 * shouldRequestInterstitial(String location)
		 * 
		 * This is used to control when an interstitial should or should not be requested
		 * If you should not request an interstitial from the server, return false
		 *
		 * For example: user should not see interstitials for some reason, return false.
		 *
		 * Is fired on:
		 * - cacheInterstitial()
		 * - showInterstitial() if no interstitial is cached
		 * 
		 * Notes: 
		 * - We do not recommend excluding purchasers with this delegate method
		 * - Instead, use an exclusion list on your campaign so you can control it on the fly
		 */
		@Override
		public boolean shouldRequestInterstitial(String location) {
			Log.i(TAG, "SHOULD REQUEST INSTERSTITIAL '"+location+ "'?");
			return true;
		}
		
		/*
		 * didCacheInterstitial(String location)
		 * 
		 * Passes in the location name that has successfully been cached
		 * 
		 * Is fired on:
		 * - cacheInterstitial() success
		 * - All assets are loaded
		 * 
		 * Notes:
		 * - Similar to this is: cb.hasCachedInterstitial(String location) 
		 * Which will return true if a cached interstitial exists for that location
		 */
		@Override
		public void didCacheInterstitial(String location) {
			Log.i(TAG, "INTERSTITIAL '"+location+"' CACHED");
		}

		/*
		 * didDismissInterstitial(String location)
		 *
		 * This is called when an interstitial is dismissed
		 *
		 * Is fired on:
		 * - Interstitial click
		 * - Interstitial close
		 *
		 * #Pro Tip: Use the delegate method below to immediately re-cache interstitials
		 */
		@Override
		public void didDismissInterstitial(String location) {
			
			// Immediately re-caches an interstitial
			cb.cacheInterstitial(location);
			
			Log.i(TAG, "INTERSTITIAL '"+location+"' DISMISSED");
		}

		/*
		 * didCloseInterstitial(String location)
		 *
		 * This is called when an interstitial is closed
		 *
		 * Is fired on:
		 * - Interstitial close
		 */
		@Override
		public void didCloseInterstitial(String location) {
			Log.i(TAG, "INSTERSTITIAL '"+location+"' CLOSED");
		}

		/*
		 * didClickInterstitial(String location)
		 *
		 * This is called when an interstitial is clicked
		 *
		 * Is fired on:
		 * - Interstitial click
		 */
		@Override
		public void didClickInterstitial(String location) {
			Log.i(TAG, "DID CLICK INTERSTITIAL '"+location+"'");
		}

		/*
		 * didShowInterstitial(String location)
		 *
		 * This is called when an interstitial has been successfully shown
		 *
		 * Is fired on:
		 * - showInterstitial() success
		 */
		@Override
		public void didShowInterstitial(String location) {
			Log.i(TAG, "INTERSTITIAL '" + location + "' SHOWN");
		}
		@Override
		public boolean shouldDisplayLoadingViewForMoreApps() {
			return true;
		}
		@Override
		public boolean shouldRequestMoreApps() {
			return true;
		}
		@Override
		public boolean shouldDisplayMoreApps() {
			Log.i(TAG, "SHOULD DISPLAY MORE APPS?");
			return true;
		}
		@Override
		public void didCacheMoreApps() {
			Log.i(TAG, "MORE APPS CACHED");
		}
		@Override
		public void didDismissMoreApps() {
			Log.i(TAG, "MORE APPS DISMISSED");
		}
		@Override
		public void didCloseMoreApps() {
			Log.i(TAG, "MORE APPS CLOSED");
		}
		@Override
		public void didClickMoreApps() {
			Log.i(TAG, "MORE APPS CLICKED");
		}
		@Override
		public void didShowMoreApps() {
			Log.i(TAG, "MORE APPS SHOWED");
		}
		@Override
		public boolean shouldRequestInterstitialsInFirstSession() {
			return true;
		}

		@Override
		public void didFailToLoadInterstitial(String arg0,
				CBImpressionError arg1) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void didFailToLoadMoreApps(CBImpressionError arg0) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void didFailToRecordClick(String arg0, CBClickError arg1) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public boolean shouldPauseClickForConfirmation(
				CBAgeGateConfirmation arg0) {
			// TODO Auto-generated method stub
			return false;
		}

	};

}
