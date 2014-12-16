/**
 * 
*/
package com.tdgc.videopokerjackpot.utils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Calendar;

import org.openudid.OpenUDID_manager;

import com.chartboost.sdk.Chartboost;
import com.google.analytics.tracking.android.EasyTracker;
import com.google.analytics.tracking.android.Fields;
import com.google.analytics.tracking.android.GoogleAnalytics;
import com.google.analytics.tracking.android.MapBuilder;
import com.google.analytics.tracking.android.Tracker;
//import com.google.analytics.tracking.android.EasyTracker;
//import com.google.analytics.tracking.android.Fields;
//import com.google.analytics.tracking.android.GoogleAnalytics;
//import com.google.analytics.tracking.android.MapBuilder;
//import com.google.analytics.tracking.android.Tracker;
import com.tdgc.videopokerjackpot.DragonVideoPoker;
import com.tdgc.videopokerjackpot.R;
import com.tdgc.videopokerjackpot.constants.Constants;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Vibrator;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.Log;

public class TDGAndroidUtils {
	
	private static TDGAndroidUtils instance = null;
	
	private static Context context;
	
	private static String udid;
	
    private String mRegId;
    
	public String getRegId() {
		return mRegId;
	}

	public void setRegId(String regId) {
		this.mRegId = regId;
	}

	static {
		TDGAndroidUtils.context = DragonVideoPoker.getContext();
		TDGAndroidUtils.sInitUDID();
	}
	
	private TDGAndroidUtils() {
		
	}
	
	public static TDGAndroidUtils getInstance() {
		if(TDGAndroidUtils.instance == null) {
			TDGAndroidUtils.instance = new TDGAndroidUtils();
		}
		
		return TDGAndroidUtils.instance;
	}
	
	public static String sGenerateFbKeyHash() {
		String keyHash = null;
		try {
            PackageInfo info = context.getPackageManager().getPackageInfo(
                    "com.tdgc.videopokerjackpot", 
                    PackageManager.GET_SIGNATURES);
            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                keyHash = Base64.encodeToString(md.digest(), Base64.DEFAULT);
                Log.d("KeyHash: ", keyHash);
                }
        } catch (NameNotFoundException e) {
        	Log.d(Constants.LOG_TAG, e.toString());
        }
        catch (NoSuchAlgorithmException e) {
        	Log.d(Constants.LOG_TAG, e.toString());
        }
		return keyHash;
	}
	
	public static String sGetPhoneId() {
		TelephonyManager telephonyManager = 
				(TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
		
		return telephonyManager.getDeviceId();
	}
	
	protected static String md5(String s) {
	    MessageDigest md = null;
	    StringBuffer result = new StringBuffer();
		try {
			md = MessageDigest.getInstance("MD5");
			md.update(s.getBytes());
		    byte digest[] = md.digest();
		    for (int i = 0; i < digest.length; i++) {
		    	result.append(Integer.toString((digest[i] & 0xff) + 0x100, 16).substring(1));
		    }
		} catch (NoSuchAlgorithmException e) {
			Log.e(Constants.LOG_TAG, e.toString());
			return s;
		}
	    return (result.toString());
	}
	
	public static void sInitUDID() {
		String openUDID = TDGAndroidUtils.sGetPhoneId();
		OpenUDID_manager.sync(context);
		if((openUDID == null || openUDID.equals("")) && 
				OpenUDID_manager.isInitialized()) {
			openUDID = OpenUDID_manager.getOpenUDID();
		}
		TDGAndroidUtils.udid = TDGAndroidUtils.md5(openUDID);
		Log.e(Constants.LOG_TAG, TDGAndroidUtils.udid.toString());
	}
	
	public static String sGetOpenUDID() {
		return TDGAndroidUtils.udid;
	}
	
	public static void sVibrate() {
		Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
		vibrator.vibrate(100);
	}
	
	public static String sGetPushId() {
		return TDGAndroidUtils.getInstance().getRegId();
	}
	
	public static void sCallApplicationToSendMail() {
		final Intent emailIntent = new Intent(Intent.ACTION_SEND); 
		emailIntent.setType("text/plain"); 
		emailIntent.putExtra(Intent.EXTRA_EMAIL, Constants.TWIN_DRAGONS_MAILS); 
		emailIntent.putExtra(Intent.EXTRA_SUBJECT, "my subject"); 
		emailIntent.putExtra(Intent.EXTRA_TEXT, "body text"); 
		context.startActivity(Intent.createChooser(emailIntent, 
				context.getString(R.string.send_mail_title)));
	}
	
	public static String sGetGameVersion()
	{
    	String app_ver;
        try {
			app_ver = context.getPackageManager().getPackageInfo(
					context.getPackageName(), 0).versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			app_ver = "unknown";
		}
        
        return app_ver;
	}

	public static String sGetOsVersion()
	{
        return Build.VERSION.RELEASE;
	}

	public static String sGetModel()
	{
        return Build.MODEL;
	}

	public static void sGoRateApp()
	{
		Intent i = new Intent(Intent.ACTION_VIEW);
		i.setData(Uri.parse("market://details?id=" + context.getPackageName()));
		context.startActivity(i);
	}

    public static void sOpenUrl(String url) 
    { 
        Intent i = new Intent(Intent.ACTION_VIEW);  
        i.setData(Uri.parse(url));
        context.startActivity(i);
    }

    public static void sSendGameFeedback(final String subject, final String userId) 
    {
    	String app_ver;
        try {
			app_ver = context.getPackageManager().getPackageInfo(
					context.getPackageName(), 0).versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			app_ver = "unknown";
		}
        
    	StringBuffer buf = new StringBuffer();
    	buf.append("\n\n--------------------------------\nHere's my info:");
        buf.append("\n- User Id:         " + userId);
    	buf.append("\n- MODEL:           " + Build.MODEL);
        buf.append("\n- Android version: " + Build.VERSION.RELEASE);
        buf.append("\n- Game version:    " + app_ver);
        buf.append("\n\nWebsite: http://twindragonsgames.com \nFacebook: http://www.facebook.com/twindragonsgames\n\n");
        
        Intent i = new Intent(Intent.ACTION_SEND);
        i.setType("message/rfc822");
        i.putExtra(Intent.EXTRA_EMAIL, new String[] {"contact@twindragonsgames.com"});
        i.putExtra(Intent.EXTRA_SUBJECT, subject);
        i.putExtra(Intent.EXTRA_TEXT, buf.toString());
        context.startActivity(Intent.createChooser(i, "Select application"));  
    }

	/**
	 * google analytics
	 * @return 
	 */
	public static void sScreenMeasurement(String screenName) {
		// May return null if EasyTracker has not yet been initialized with a property
		// ID.
		Tracker easyTracker = EasyTracker.getInstance(context);

		// This screen name value will remain set on the tracker and sent with
		// hits until it is set to a new value or to null.
		easyTracker.set(Fields.SCREEN_NAME, screenName);

		easyTracker.send(MapBuilder
		    .createAppView()
		    .build()
		);
	}
	
	public static void sEventMeasurement(String eventCategory, String eventAction,
			String eventLabel, long eventValue) {
		// May return null if a EasyTracker has not yet been initialized with a
		  // property ID.
		  EasyTracker easyTracker = EasyTracker.getInstance(context);

		  // MapBuilder.createEvent().build() returns a Map of event fields and values
		  // that are set and sent with the hit.
		  easyTracker.send(MapBuilder
		      .createEvent(eventCategory,     // Event category (required)
		                   eventAction,  // Event action (required)
		                   eventLabel,   // Event label
		                   eventValue)            // Event value
		      .build()
		  );
	}
	
	public static void sSessionManagement(boolean isStart) {
		// May return null if a tracker has not yet been initialized.
		Tracker tracker = GoogleAnalytics.getInstance(context).getDefaultTracker();

		// Start a new session. The next hit from this tracker will be the first in
		// a new session.
		tracker.set(Fields.SESSION_CONTROL, (isStart)?"start":"end");
	}
	
	public static void sCreateHourlyBonusLocalNotification() {
////		public static void sCreateHourlyBonusLocalNotification(long timeToBonus) {
//	    NotificationManager notificationManager = 
//	    		(NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
//	    	 
////	    Notification notification = new Notification(R.drawable.icon, "Some Text", System.currentTimeMillis());
////	    notification.flags = Notification.FLAG_AUTO_CANCEL | Notification.DEFAULT_LIGHTS | Notification.DEFAULT_SOUND;
//	    Notification notification = new Notification.Builder(context)
//	    .setContentTitle("Your free Chips are ready!")
//	    .setContentText("Collect them now!")
////	    .setSmallIcon(R.drawable.icon)
//	    .build();
//	    
//	    //10 is a random number I chose to act as the id for this notification
////	    notificationManager.notify(10, notification);
		showLocalNotification("Your free Chips are ready! Collect them now!", 4, 1000);
	}
	
    public static void showLocalNotification(String message, int interval, int tag) {
        Log.v("TDGAndroidUtils", "showLocalNotification");
        // cancel this old
        cancelLocalNotification(tag);
        
        PendingIntent sender = getPendingIntent(message, tag);

        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(System.currentTimeMillis());
        calendar.add(Calendar.SECOND, interval);

        AlarmManager am = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        am.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), sender);
    }

    public static void cancelLocalNotification(int tag) {
        Log.v("TDGAndroidUtils", "cancelLocalNotification");
        PendingIntent sender = getPendingIntent(null, tag);
        if (sender != null) {
        	AlarmManager am = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        	am.cancel(sender);
        }
    }

    private static PendingIntent getPendingIntent(String message, int tag) {
        Intent i = new Intent(context.getApplicationContext(), LocalNotificationReceiver.class);
        i.putExtra("notification_id", tag);
        i.putExtra("message", message);
        PendingIntent sender = PendingIntent.getBroadcast(
        		context.getApplicationContext(), 
        		tag,
        		i, 
        		PendingIntent.FLAG_UPDATE_CURRENT);
        return sender;
    }

    public static void sShowChartboostHourlyBonusAds() 
    {
    	((Activity) context).runOnUiThread(new Runnable() {
            public void run() {
            	final Handler handler = new Handler();
            	handler.postDelayed(new Runnable() {
            	  @Override
            	  public void run() {
            	    //Do something after 100ms
            		  Chartboost.sharedChartboost().showInterstitial(context.getApplicationContext().getString(R.string.chartboost_bonus_interstitial));
            	  }
            	}, 100); 
            }
        });
    }
    
}
