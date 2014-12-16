package com.tdgc.videopokerjackpot.utils;

/* Copyright (c) 2012 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use context file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import com.android.util.IabHelper;
import com.android.util.IabResult;
import com.android.util.Inventory;
import com.android.util.Purchase;
import com.android.util.SkuDetails;
import com.tdgc.dragonvideopoker.DragonVideoPoker;
import com.tdgc.videopokerjackpot.constants.Constants;
import com.tdgc.videopokerjackpot.inapp.models.PokerSku;

public class TDGInAppHelper {

    // Does the user have an active subscription to the infinite gas plan?
    boolean mSubscribedToInfiniteGas = false;

    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;
    
    private static Context context = null;
    public static IabHelper sInAppHelper = null;
    private static TDGInAppHelper instance = null;
    
    private static String sDeveloperPayload = "tvd";
    private static List<PokerSku> pokerSkus;
    private static boolean isCompleteLoadPrices = false;

    private native void nativeUpdateIsGotPrice(boolean isGotPrice);
    private native void nativeCancelPurchase();
    private native void nativeVerifyInApp(String packageName, String productId, String purchaseToken);

	static {
    	TDGInAppHelper.context = DragonVideoPoker.getContext();
    	TDGInAppHelper.prepareProducts();
    }
    
    private TDGInAppHelper() {
    	isCompleteLoadPrices = false;
    }
    
    public static TDGInAppHelper getInstance() {
    	if(TDGInAppHelper.instance == null) {
    		synchronized (TDGInAppHelper.class) {
				if(TDGInAppHelper.instance == null) {
					TDGInAppHelper.instance = new TDGInAppHelper();
				}
			}
    	}
    	
    	return TDGInAppHelper.instance;
    }

    public static void prepareProducts() {
        // load game data
        loadData();

        // Create the helper, passing it our context and the public key 
        // to verify signatures with
        Log.d(Constants.LOG_TAG, "Creating IAB helper.");
//        sInAppHelper = new IabHelper(context, Constants.BASE64_ENCODE_PUBLIC_KEY);
        sInAppHelper = new IabHelper(TDGInAppHelper.context, Constants.BASE64_ENCODE_PUBLIC_KEY);

        // enable debug logging (for a production application, you should set context to false).
        sInAppHelper.enableDebugLogging(true);

        // Start setup. This is asynchronous and the specified listener
        // will be called once setup completes.
        Log.d(Constants.LOG_TAG, "Starting setup.");
        sInAppHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            public void onIabSetupFinished(IabResult result) {
                Log.d(Constants.LOG_TAG, "Setup finished.");
                if (!result.isSuccess()) {
                    // Oh noes, there was a problem.
                    return;
                }
                // Have we been disposed of in the meantime? If so, quit.
                if (sInAppHelper == null) return;

                // IAB is fully set up. Now, let's get an inventory of stuff we own.
                Log.d(Constants.LOG_TAG, "Setup successful. Querying inventory.");
                ArrayList<String> moreSkus = new ArrayList<String>();
                moreSkus.addAll(Arrays.asList(Constants.TDGC_POKER_SKUS));
                sInAppHelper.queryInventoryAsync(true, moreSkus, mGotInventoryListener);
            }
        });
    }

    // Listener that's called when we finish querying the items and subscriptions we own
    private static IabHelper.QueryInventoryFinishedListener mGotInventoryListener = 
    		new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(Constants.LOG_TAG, "Query inventory finished.");

            // Have we been disposed of in the meantime? If so, quit.
            if (sInAppHelper == null) return;

            // Is it a failure?
            if (result.isFailure()) {
                //complain("Failed to query inventory: " + result);
                return;
            }

            Log.d(Constants.LOG_TAG, "Query inventory was successful.");

            /*
             * Check for items we own. Notice that for each purchase, we check
             * the developer payload to see if it's correct! See
             * verifyDeveloperPayload().
             */
            // get prices
            for(int i = 0 ; i < Constants.TDGC_POKER_SKUS.length ; i++) {
            	SkuDetails skuDetails = inventory.getSkuDetails(Constants.TDGC_POKER_SKUS[i]);
            	if(skuDetails != null) {
                    Log.d(Constants.LOG_TAG, Constants.TDGC_POKER_SKUS[i] + " Price: " + skuDetails.getPrice());
            	}
            }

            // consume 
            for(int i = 0 ; i < Constants.TDGC_POKER_SKUS.length ; i++) {
            	Purchase chipPurchase = inventory.getPurchase(Constants.TDGC_POKER_SKUS[i]);
            	if(chipPurchase != null) {
            		sInAppHelper.consumeAsync(inventory.getPurchase(Constants.TDGC_POKER_SKUS[i]), 
                    		mConsumeFinishedListener);
            	}
            }

            Log.d(Constants.LOG_TAG, "Initial inventory query finished; enabling main UI.");
        }
    };

    // User clicked the "Buy Gas" button
    private static void sOnBuyButtonClicked(int index) {
        Log.d(Constants.LOG_TAG, "Buy gold button clicked.");

        sDeveloperPayload = new Date().toString();

        sInAppHelper.launchPurchaseFlow((Activity)context, Constants.TDGC_POKER_SKUS[index], 
        		RC_REQUEST, mPurchaseFinishedListener, sDeveloperPayload);
    }

    public static void sBuyPackage(int index) {
        sDeveloperPayload = new Date().toString();

        sInAppHelper.launchPurchaseFlow((Activity)context, Constants.TDGC_POKER_SKUS[index], 
        		RC_REQUEST, mPurchaseFinishedListener, sDeveloperPayload);
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(Constants.LOG_TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
        if (sInAppHelper == null) {
        	return;
        } else {
        }
    }

    /** Verifies the developer payload of a purchase. */
    private static boolean verifyDeveloperPayload(Purchase p) {
        /*
         * verify that the developer payload of the purchase is correct. It will be
         * the same one that you sent when initiating the purchase.
         *
         * WARNING: Locally generating a random string when starting a purchase and
         * verifying it here might seem like a good approach, but context will fail in the
         * case where the user purchases an item on one device and then uses your app on
         * a different device, because on the other device you will not have access to the
         * random string you originally generated.
         *
         * So a good developer payload has these characteristics:
         *
         * 1. If two different users purchase an item, the payload is different between them,
         *    so that one user's purchase can't be replayed to another user.
         *
         * 2. The payload must be such that you can verify it even when the app wasn't the
         *    one who initiated the purchase flow (so that items purchased by the user on
         *    one device work on other devices owned by the user).
         *
         * Using your own server to store and verify developer payloads across app
         * installations is recommended.
         */
    	String payload = p.getDeveloperPayload();
        return (payload.equals(sDeveloperPayload));
    }

    // Callback for when a purchase is finished
    private static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = 
    		new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            Log.d(Constants.LOG_TAG, "Purchase finished: " + result + ", purchase: " + purchase);
            
            // if we were disposed of in the meantime, quit.
            if (sInAppHelper == null) return;

            if (result.isFailure() || purchase == null) {
            	// update to game
    			TDGInAppHelper.getInstance().nativeCancelPurchase();
                return;
            }

            // purchase success
            Log.d(Constants.LOG_TAG, "Purchase getPackageName: " + purchase.getPackageName() +
            		", getSku: " + purchase.getSku() + ", getToken: " + purchase.getToken());
            TDGInAppHelper.getInstance().nativeVerifyInApp(
            		purchase.getPackageName(), 
            		purchase.getSku(),
            		purchase.getToken());

            Log.d(Constants.LOG_TAG, "Purchase successful.");

            for(int i = 0 ; i < Constants.TDGC_POKER_SKUS.length ; i++) {
            	if (purchase.getSku().equals(Constants.TDGC_POKER_SKUS[i])) {
            		sInAppHelper.consumeAsync(purchase, mConsumeFinishedListener);
            	}
            }
        }
    };

    // Called when consumption is complete
    private static IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = 
    		new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d(Constants.LOG_TAG, "Consumption finished. Purchase: " 
            		+ purchase + ", result: " + result);

            // if we were disposed of in the meantime, quit.
            if (sInAppHelper == null) return;

            // We know context is the "gas" sku because it's the only one we consume,
            // so we don't check which sku was consumed. If you have more than one
            // sku, you probably should check...
            if (result.isSuccess()) {
                // successfully consumed, so we apply the effects of the item in our
                // game world's logic, which in our case means filling the gas tank a bit
                Log.d(Constants.LOG_TAG, "Consumption successful. Provisioning.");
                saveData();
            }
            else {
                complain("Error while consuming: " + result);
            }
            Log.d(Constants.LOG_TAG, "End consumption flow.");
        }
    };

    // We're being destroyed. It's important to dispose of the helper here!
    public void onDestroy() {
        // very important:
        Log.d(Constants.LOG_TAG, "Destroying helper.");
        if (sInAppHelper != null) {
            sInAppHelper.dispose();
            sInAppHelper = null;
        }
    }

    static void complain(String message) {
        Log.e(Constants.LOG_TAG, "**** TrivialDrive Error: " + message);
        alert("Error: " + message);
    }

    public static void alert(String message) {
        AlertDialog.Builder bld = new AlertDialog.Builder(context);
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        Log.d(Constants.LOG_TAG, "Showing alert dialog: " + message);
        bld.create().show();
    }

    static void saveData() {

    }

    static void loadData() {
    }
    
    public static void sSendTransacIdToServer(List<NameValuePair> params) {
    	HttpClient client = new DefaultHttpClient();
    	HttpPost post = new HttpPost(URI_SERVER_VERIFY);
    	try {
	    	post.setEntity(new UrlEncodedFormEntity(params));
	    	HttpResponse response = client.execute(post);
	    	InputStream content = response.getEntity().getContent();
	    	BufferedReader reader = new BufferedReader(new InputStreamReader(content));
		    StringBuffer buffer = new StringBuffer();
		    for (String line = reader.readLine(); line != null; line = reader.readLine()) {
		    	buffer.append(line);
		    }
		    if(buffer.toString().equals("")) {
	    		alert("verify failed");
	    	}
		    System.out.println(buffer.toString());
    	} catch(UnsupportedEncodingException e) {
    		Log.e(Constants.LOG_TAG, e.toString());
    	} catch (ClientProtocolException e) {
    		Log.e(Constants.LOG_TAG, e.toString());
		} catch (IOException e) {
			Log.e(Constants.LOG_TAG, e.toString());
		} catch(NullPointerException e) {
			alert("verify failed");
			Log.e(Constants.LOG_TAG, e.toString());
		}
    }
        
    private static Handler handler = new Handler() {
		@Override
		public void handleMessage(final Message msg) {
			//progressDialog.dismiss();
			isCompleteLoadPrices = true;
			
			// inform to client
//			TDGInAppHelper.getInstance().nativeUpdateIsGotPrice(true);
			//alert(pokerSkus.toString());
		}
	};
    
    public static void toastComplain(String str) {
    	Toast.makeText(context, str, Toast.LENGTH_LONG).show();
    }
    
    public static IabHelper getIabHelper() {
    	return sInAppHelper;
    }
    
    protected static final String URI_SERVER_VERIFY = "http://192.168.1.102:8080/IAppBilling/InAppServlet";
}
