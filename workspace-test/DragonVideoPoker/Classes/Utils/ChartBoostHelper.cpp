//
//  ChartBoostHelper.cpp
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 1/21/13.
//
//

#include "ChartBoostHelper.h"
#include "GameParams.h"

#ifdef CC_TARGET_OS_IPHONE
#import "Chartboost.h"
#else
#include <jni.h>
#include "jni/JniHelper.h"
#endif

using namespace cocos2d;

extern "C" {

static ChartBoostHelper *s_pHelper;

ChartBoostHelper* ChartBoostHelper::sharedHelper()
{
    if (! s_pHelper) {
        s_pHelper = new ChartBoostHelper();
    }
    
    return s_pHelper;
}

void ChartBoostHelper::showBonusInterstitial()
{
#ifdef CC_TARGET_OS_IPHONE
    [[Chartboost sharedChartboost] showInterstitial:CHARTBOOST_GOT_HOURLY_BONUS];
#else
    JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sShowChartboostHourlyBonusAds",
                                       "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	} else {
        
	}
#endif
}

}