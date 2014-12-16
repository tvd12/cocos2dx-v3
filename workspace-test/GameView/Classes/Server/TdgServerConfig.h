//
//  TdgServerConfig.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#ifndef __DragonVideoPoker__TdgServerConfig__
#define __DragonVideoPoker__TdgServerConfig__

#include "cocos2d.h"

#include "SingLeton.h"

USING_NS_CC;
using namespace std;

// iOS config
#ifdef CC_TARGET_OS_IPHONE
#ifdef COCOS2D_DEBUG
#define CONFIG_URL          "http://twindragonsgames.com/inapp/dragonvideopoker-KHd889ds/config-dev.txt"
#else
#define CONFIG_URL          "http://twindragonsgames.com/inapp/dragonvideopoker-KHd889ds/config.txt"
#endif

// android config
#else
#define CONFIG_URL          "http://twindragonsgames.com/inapp/dragonvideopoker-KHd889ds/config-android.txt"
#endif

#define CONFIG_TAG              "SFS_CONFIG"

#define AUTO_LOGIN_KEY          "AutoLoginStatus"
#define CACHE_CONFIG_KEY        "SfsConfigCached"
#define CACHE_CONFIG_NO_VALUE   "NoCached"

typedef enum LOAD_CONFIG_STATUS {
    kConfigIdle,
    kConfigLoading,
    kConfigLoadedFail,
    kConfigLoadedSuccess,
    kConfigMustUpgradeGame,
} Load_Config_Status;

typedef enum AUTO_LOGIN_STATUS {
    kAutoLoginNone,
    kAutoLoginGuest,
    kAutoLoginFacebook,
} Auto_login_Status;

class TdgServerConfig : public SingLeton<TdgServerConfig>, public CCObject
{
public:
    TdgServerConfig();
    
    void updateConfigFromServer();
    void reloadConfigFromServerIfNeed();
    void updateAutoLoginStatus(int status);
    void cacheServerConfig();
    
    CC_SYNTHESIZE(string *, mIp, Ip);
    CC_SYNTHESIZE(long, mPort, Port);
    CC_SYNTHESIZE(string *, mZone, Zone);
    CC_SYNTHESIZE(bool, mIsDebugable, IsDebugable);
    
    CC_SYNTHESIZE(int, mStatusConfigLoading, StatusConfigLoading);
    CC_SYNTHESIZE(int, mAutoLoginStatus, AutoLoginStatus);
    CC_SYNTHESIZE(bool, mIsJustLaunchedGame, IsJustLaunchedGame);
    
private:
    string *mConfigData;
    bool mIsUsingCachedConfig;
    
    void onHttpRequestConfigCompleted(CCNode *sender, void *data);
    void tryLoginServerWithCachedConfig();
    void fetchServerConfigData();
    void informCheckingInternetConnection();
    
};

#define SERVER_CONFIG() TdgServerConfig::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerConfig__) */
