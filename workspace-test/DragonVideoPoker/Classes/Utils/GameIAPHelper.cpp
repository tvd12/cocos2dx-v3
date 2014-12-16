//
//  GameIAPHelper.cpp
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 1/18/13.
//
//

#include "GameIAPHelper.h"
#include "TdgServerDefine.h"
#include "cocos2d.h"

#ifdef CC_TARGET_OS_IPHONE
#include "GameIAPHelper_objc.h"
#else
#include <jni.h>
#include "jni/JniHelper.h"
#include <string>
#include "TdgServer.h"
#endif

USING_NS_CC;

extern "C" {

static GameIAPHelper *s_pHelper;

GameIAPHelper* GameIAPHelper::sharedHelper(void)
{
    if (! s_pHelper)
    {
        s_pHelper = new GameIAPHelper();
        
#ifdef CC_TARGET_OS_IPHONE
        // process ios native
        [GameIAPHelper_objc sharedHelper];
        
        s_pHelper->isGotPriceFromServer = false;
        
        [[GameIAPHelper_objc sharedHelper] requestProducts];
#else
        // process android native
        
#endif
    }
    
    return s_pHelper;
}

void GameIAPHelper::purchasedChips(int type)
{
    // Play sound effect
}

void GameIAPHelper::purchasedGold(int type)
{
    // Play sound effect
}

const char* GameIAPHelper::getItemPriceString(int itemType)
{
    const char* ret;
    
#ifdef CC_TARGET_OS_IPHONE
    float price;
    switch (itemType) {
        case kIAPChip1:
            price = [GameIAPHelper_objc sharedHelper].chip1Price;
            break;
            
        case kIAPChip2:
            price = [GameIAPHelper_objc sharedHelper].chip2Price;
            break;
            
        case kIAPChip3:
            price = [GameIAPHelper_objc sharedHelper].chip3Price;
            break;
            
        case kIAPChip4:
            price = [GameIAPHelper_objc sharedHelper].chip4Price;
            break;
            
        case kIAPChip5:
            price = [GameIAPHelper_objc sharedHelper].chip5Price;
            break;
            
        case kIAPChip6:
            price = [GameIAPHelper_objc sharedHelper].chip6Price;
            break;
            
        default:
            break;
    }
    
    [[GameIAPHelper_objc sharedHelper] resetFormatterCurrencyIfNeed];
    
    NSString *formattedPrice = [[GameIAPHelper_objc sharedHelper].priceFormatter
                                stringFromNumber:[NSNumber numberWithFloat:price]];
    
    ret = [formattedPrice UTF8String];
    
#else
    // process android native
    
#endif

    return ret;
}

void GameIAPHelper::purchaseItem(int itemType)
{
#ifdef CC_TARGET_OS_IPHONE
    [[GameIAPHelper_objc sharedHelper] purchaseItem:itemType];
#else
    // process android native
    JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tdgc/videopokerjackpot/utils/TDGInAppHelper", "sBuyPackage", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, (jint)itemType);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void GameIAPHelper::finishPurchasing()
{
    // inform to UI
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_IAP_FINISHED,
                                                                           NULL);
}

}

#ifndef CC_TARGET_OS_IPHONE
JNIEXPORT void JNICALL Java_com_tdgc_videopokerjackpot_utils_TDGInAppHelper_nativeCancelPurchase
(JNIEnv * env, jobject obj)
{
    GameIAPHelper::sharedHelper()->finishPurchasing();
}

JNIEXPORT void JNICALL Java_com_tdgc_videopokerjackpot_utils_TDGInAppHelper_nativeVerifyInApp
(JNIEnv * env, jobject obj, jstring packageGame, jstring productId, jstring purchaseToken)
{
	string packageStr = JniHelper::jstring2string(packageGame);
	string productIdStr = JniHelper::jstring2string(productId);
	string purchaseTokenStr = JniHelper::jstring2string(purchaseToken);
    
	CCLog("packageStr = %s", packageStr.c_str());
	CCLog("productIdStr = %s", productIdStr.c_str());
	CCLog("purchaseTokenStr = %s", purchaseTokenStr.c_str());
    
    // send to server to verify
    SERVER().sendVerifyIapAndroidData(packageStr.c_str(), productIdStr.c_str(), purchaseTokenStr.c_str());
}

#endif

