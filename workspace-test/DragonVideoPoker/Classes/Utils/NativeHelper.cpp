//
//  NativeHelper.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 10/17/13.
//
//

#include "NativeHelper.h"
#include "GameParams.h"
#include "TdgServer.h"
#include "UserInfo.h"

#ifdef CC_TARGET_OS_IPHONE
#include "Native_objc.h"
#include "GAHelper_objc.h"
#include "Tdg_OpenUdid.h"

#else
#include <jni.h>
#include "jni/JniHelper.h"
#include <string>

using namespace std;

#endif

extern "C" {

NativeHelper::NativeHelper()
{
    // get game version & OS version
#ifdef CC_TARGET_OS_IPHONE
    // get game version
    NSString *gameVersion = [NSString stringWithFormat:@"%@",
                             [[[NSBundle mainBundle] infoDictionary]
                              objectForKey:@"CFBundleVersion"]];
    SERVER().setGameVersion(new string([gameVersion UTF8String]));
    
    // get os version
    NSString *osVer = [[UIDevice currentDevice] systemVersion];
    SERVER().setOsVersion(new string(CCString::createWithFormat("iOS %s",
                                                                [osVer UTF8String])->getCString()));
#else
    // get game version
    JniMethodInfo t;
    string gameVersion = "Unknown";
	if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sGetGameVersion",
                                       "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		gameVersion = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
    }
    SERVER().setGameVersion(new string(gameVersion));

    // get os version
    string osVersion = "Unknown";
    JniMethodInfo t2;
    if (JniHelper::getStaticMethodInfo(t2,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sGetOsVersion",
                                       "()Ljava/lang/String;")) {
		jstring str = (jstring)t2.env->CallStaticObjectMethod(t2.classID, t2.methodID);
		t2.env->DeleteLocalRef(t2.classID);
        osVersion = string("Android ");
        osVersion.append(JniHelper::jstring2string(str));
		t2.env->DeleteLocalRef(str);
	}
    SERVER().setOsVersion(new string(osVersion));
#endif
    
    // get udid
    SERVER().setDeviceUdid(new string(getDeviceUdid()));
}

void NativeHelper::vibrate()
{
}

void NativeHelper::rateUsOnStore()
{
#ifdef CC_TARGET_OS_IPHONE
    [[Native_objc sharedObject] rateUsOnStore];
#else
    JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sGoRateApp", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	} else {
        
	}
#endif
}

void NativeHelper::sendFeedback()
{
#ifdef CC_TARGET_OS_IPHONE
    [[Native_objc sharedObject] sendFeedback:EMAIL_SUBJECT andUserId:USERINFO()->getProfileID()];
#else
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sSendGameFeedback",
                                       "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring subject = t.env->NewStringUTF(EMAIL_SUBJECT);
		jstring userId = t.env->NewStringUTF(USERINFO()->getProfileID());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, subject, userId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(subject);
	} else {
        
	}
#endif
}

void NativeHelper::openUrl(const char *url)
{
#ifdef CC_TARGET_OS_IPHONE
    [[Native_objc sharedObject] openUrl:url];
#else
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
			"sOpenUrl", "(Ljava/lang/String;)V")) {
		jstring urlStr = t.env->NewStringUTF(url);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, urlStr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlStr);
	} else {

	}
#endif
}

void NativeHelper::openUpdateUrl()
{
    CCString *gameOnStore;
    gameOnStore = CCString::createWithFormat(GAME_ON_STORE_URL, PRODUCT_ID);
    NATIVE().openUrl(gameOnStore->getCString());
}

void NativeHelper::sendMainEvent(int eventType)
{
    const char* eventName;
    
    switch (eventType) {
        case kGAMainEventLobbySettings:
        	eventName = "Lobby Settings";
            break;
            
        case kGAMainEventOnGameSettings:
        	eventName = "OnGame Settings";
            break;
            
        case kGAMainEventProfile:
        	eventName = "Profile";
            break;
            
        case kGAMainEventBuyChips:
        	eventName = "Buy Chips";
            break;
            
        case kGAMainEventHourlyBonus:
        	eventName = "Hourly Bonus";
            break;
            
        case kGAMainEventAvatar:
        	eventName = "Avatar";
            break;
            
        case kGAMainEventVip:
        	eventName = "Vip";
            break;
            
        case kGAMainEventDailyBonus:
        	eventName = "Daily Bonus";
            break;
            
        case kGAMainEventLogout:
        	eventName = "Logout";
            break;
            
        case kGAMainEventGuestLogin:
        	eventName = "Guest Login";
            break;
            
        case kGAMainEventFbLogin:
        	eventName = "Fb Login";
            break;
            
        case kGAMainEventShareJackpot:
        	eventName = "Share Jackpot";
            break;
            
        case kGAMainEventShareLevelUp:
        	eventName = "Share Level Up";
            break;
            
        case kGAMainEventShareVipUpgrade:
        	eventName = "Share Vip Upgrade";
            break;
            
        case kGAMainEventFanPage:
        	eventName = "Fan Page";
            break;
            
        case kGAMainEventInviteFriend:
        	eventName = "Invite Friend";
            break;
            
        case kGAMainEventDoubleSpeedGameOn:
        	eventName = "Double Speed Game On";
            break;
            
        case kGAMainEventDoubleSpeedGameOff:
        	eventName = "Double Speed Game Off";
            break;
            
        case kGAMainEventLeaderboard:
        	eventName = "Leaderboard";
            break;
            
        default:
        	eventName = "UNKNOWN EVENT";
            break;
    }

#ifdef CC_TARGET_OS_IPHONE
    [[GAHelper_objc sharedHelper] sendGameEvent:eventName
                                      withValue:1
                                   withCatagory:GA_MAIN_CATEGORY];
#else
    eventMeasurement(GA_MAIN_CATEGORY, "Button Pressed", eventName, 1);
#endif
}

void NativeHelper::sendGameEvent(int eventType)
{
    NATIVE().sendGameEvent(eventType, 1);
}

void NativeHelper::sendGameEvent(int eventType, long long eventValue)
{
    const char* eventName;
    switch (eventType) {
        case kGAGameEventDeal:
        	eventName = "Deal";
            break;
            
        case kGAGameEventCancelBet:
        	eventName = "Cancel Bet";
            break;
            
        case kGAGameEventMaxBet:
        	eventName = "Max Bet";
            break;
            
        case kGAGameEventDonYes:
        	eventName = "Don Yes";
            break;
            
        case kGAGameEventDonNo:
        	eventName = "Don No";
            break;
            
        case kGAGameEventLeftHand:
        	eventName = "Left Hand";
            break;
            
        case kGAGameEventRightHand:
        	eventName = "Right Hand";
            break;
            
        case kGAGameEventDonEnable:
        	eventName = "Don Enable";
            break;
            
        case kGAGameEventDonDisable:
        	eventName = "Don Disable";
            break;
            
        case kGAGameEventChipTypeSmall:
        	eventName = "Chip Type Small";
            break;
            
        case kGAGameEventChipTypeMedium:
        	eventName = "Chip Type Medium";
            break;
            
        case kGAGameEventChipTypeBig:
        	eventName = "Chip Type Big";
            break;
            
        default:
        	eventName = "UNKNOWN EVENT";
            break;
    }

#ifdef CC_TARGET_OS_IPHONE
    [[GAHelper_objc sharedHelper] sendGameEvent:eventName
                                      withValue:eventValue
                                   withCatagory:GA_GAME_CATEGORY];
#else
    eventMeasurement(GA_GAME_CATEGORY, "Button Pressed", eventName, eventValue);
#endif
}

void NativeHelper::sendScreenView(int screenType)
{
    const char* screenName;
    switch (screenType) {
        case kGAScreenLogin:
            screenName = GA_SCREEN_LOGIN;
            break;
            
        case kGAScreenLobby:
            screenName = GA_SCREEN_LOBBY;
            break;
            
        case kGAScreenMainGameJacksOrBetter:
            screenName = GA_MAIN_GAME_JACKS_OR_BETTER;
            break;
            
        case kGAScreenMainGameJokerPoker:
            screenName = GA_MAIN_GAME_JOKER_POKER;
            break;
            
        case kGAScreenMainGameTensOrBetter:
            screenName = GA_MAIN_GAME_TENS_OR_BETTER;
            break;
            
        case kGAScreenMainGameDeucesWild:
            screenName = GA_MAIN_GAME_DEUCES_WILD;
            break;
            
        case kGAScreenMainGameAcesAndFaces:
            screenName = GA_MAIN_GAME_ACES_AND_FACES;
            break;
            
        case kGAScreenMainGameDoubleBonus:
            screenName = GA_MAIN_GAME_DOUBLE_BONUS;
            break;
            
        case kGAScreenMainGameAcesAndEights:
            screenName = GA_MAIN_GAME_ACES_AND_EIGHTS;
            break;
            
        case kGAScreenMainGameDeucesAndJokerWild:
            screenName = GA_MAIN_GAME_DEUCES_AND_JOKER_WILD;
            break;
            
        default:
            screenName = "UNKNOWN SCENE";
            break;
    }

#ifdef CC_TARGET_OS_IPHONE
    [[GAHelper_objc sharedHelper] sendScreenView:screenName];
#else
    screenMeasurement(screenName);
#endif
}

string NativeHelper::getDeviceUdid()
{
    string ret;
#ifdef CC_TARGET_OS_IPHONE
    ret = string(OPEN_UDID());
    
#else
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sGetOpenUDID",
                                       "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		ret = string(JniHelper::jstring2string(str).c_str());
		t.env->DeleteLocalRef(str);
	} else {
		ret = string("Unknown Android");
	}
#endif
    
    return ret;
}

void NativeHelper::screenMeasurement(const char* _screenName) {
#ifdef CC_TARGET_OS_IPHONE
#else
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sScreenMeasurement",
                                       "(Ljava/lang/String;)V")) {
        jstring screenName = t.env->NewStringUTF(_screenName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, screenName);
        t.env->DeleteLocalRef(t.classID);
    } else {
            
    }
#endif
}
    
void NativeHelper::eventMeasurement(const char* _eventCategory,
                                    const char* _eventAction,
                                    const char* _eventLabel,
                                    long long _eventValue) {
#ifdef CC_TARGET_OS_IPHONE
#else
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sEventMeasurement",
                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V")) {
        jstring eventCategory = t.env->NewStringUTF(_eventCategory);
        jstring eventAction = t.env->NewStringUTF(_eventAction);
        jstring eventLabel = t.env->NewStringUTF(_eventLabel);
        jlong   eventValue = (jlong)_eventValue;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, eventCategory,
                                        eventAction, eventLabel, eventValue);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(eventCategory);
        t.env->DeleteLocalRef(eventLabel);
    } else {
            
    }
#endif
}
    
void NativeHelper::sessionManagement(bool isStart) {
#ifdef CC_TARGET_OS_IPHONE
#else
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "sSessionManagement",
                                       "(B)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, (jboolean)isStart);
        t.env->DeleteLocalRef(t.classID);
    } else {
            
    }
#endif
}
}
