//
//  TdgServerConfig.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#include "TdgServerConfig.h"
#include "TdgServerDefine.h"
#include "NotificationObject.h"
#include "TdgServer.h"

#include "cocos-ext.h"
#include <algorithm>
#include <boost/tokenizer.hpp>

USING_NS_CC_EXT;

TdgServerConfig::TdgServerConfig()
{
    mIp = NULL;
    mPort = 0;
    mZone = NULL;
    mConfigData = NULL;
    
    mIsDebugable = true;
    mIsJustLaunchedGame = true;
    
    mIsUsingCachedConfig = false;
    
    mStatusConfigLoading = kConfigIdle;
    mAutoLoginStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(AUTO_LOGIN_KEY,
                                                                            kAutoLoginNone);
    CCLog("CONFIG_URL = %s", CONFIG_URL);

}

void TdgServerConfig::updateConfigFromServer()
{
    setStatusConfigLoading(kConfigLoading);
    
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(CONFIG_URL);
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this,
                                 httpresponse_selector(TdgServerConfig::
                                                       onHttpRequestConfigCompleted));
    request->setTag(CONFIG_TAG);
    
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void TdgServerConfig::reloadConfigFromServerIfNeed()
{
    if (mIsUsingCachedConfig) {
        if (mConfigData != NULL) {
            delete mConfigData;
        }
        mConfigData = new std::string("");
        cacheServerConfig();
        updateConfigFromServer();
    }
}

void TdgServerConfig::updateAutoLoginStatus(int status)
{
    mAutoLoginStatus = status;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(AUTO_LOGIN_KEY, status);
}

void TdgServerConfig::cacheServerConfig()
{
    CCUserDefault::sharedUserDefault()->setStringForKey(CACHE_CONFIG_KEY, *mConfigData);
    CCUserDefault::sharedUserDefault()->flush();
}

void TdgServerConfig::onHttpRequestConfigCompleted(CCNode *sender, void *data)
{
    CCHttpResponse* response = (CCHttpResponse*)data;
    if (!response) {
        CCLOG("Load config failed!");
        SERVER_CONFIG().setStatusConfigLoading(kConfigLoadedFail);
        SERVER_CONFIG().informCheckingInternetConnection();
        //        SERVER_CONFIG().tryLoginServerWithCachedConfig();
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        CCLog("%s completed!", response->getHttpRequest()->getTag());
    }
    
    if (!response->isSucceed()) {
        CCLog("Load config response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        SERVER_CONFIG().setStatusConfigLoading(kConfigLoadedFail);
        SERVER_CONFIG().informCheckingInternetConnection();
        //        SERVER_CONFIG().tryLoginServerWithCachedConfig();
        return;
    }
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    mConfigData = new std::string(&(buffer->front()), buffer->size());
    
    SERVER_CONFIG().fetchServerConfigData();
}

void TdgServerConfig::tryLoginServerWithCachedConfig()
{
    std::string cacheConfig;
    cacheConfig = CCUserDefault::sharedUserDefault()->getStringForKey(CACHE_CONFIG_KEY,
                                                                      CACHE_CONFIG_NO_VALUE);
    if (cacheConfig.compare(CACHE_CONFIG_NO_VALUE) == 0) {
        // no cache available
        SERVER_CONFIG().setStatusConfigLoading(kConfigLoadedFail);
    }
    else {
        CCLOG("Load cached config!!!");
        // load cached data
        if (mConfigData != NULL) {
            delete mConfigData;
        }
        mConfigData = new std::string(cacheConfig);
        if (mConfigData->length() > 0) {
            mIsUsingCachedConfig = true;
            SERVER_CONFIG().fetchServerConfigData();
        }
    }
}

void TdgServerConfig::fetchServerConfigData()
{
    // tokenize this info
    boost::char_separator<char> sep("#");
    boost::tokenizer<boost::char_separator<char> > toker(*mConfigData, sep);
    std::vector<std::string> words(toker.begin(), toker.end());
    
    // get smart fox configure
    if (words.size() < 4) {
        return;
    }
    
    mIp = new std::string(words[0]);
    mPort = atoi(words[1].c_str());
    mZone = new std::string(words[2]);
    
    CCLOG("IP = %s", mIp->c_str());
    
    if (words[3].compare("true") == 0) {
        mIsDebugable = true;
    }
    else {
        mIsDebugable = false;
    }
    // get newest version info at index 4 & 5
    if (words.size() > 5) {
        bool isGameMustUpdate = false;
        if (words[5].compare("true") == 0) {
            isGameMustUpdate = true;
        }
        if (isGameMustUpdate) {
            // show inform message
            if (words[4].compare(SERVER().getGameVersion()->c_str()) != 0) {
                SERVER_CONFIG().setStatusConfigLoading(kConfigMustUpgradeGame);

                NotificationObject* object = NotificationObject::create();
                object->setTitle(new string("Update is available"));
                object->setMessage(new string("Good news! A new version of the game is available. Press Ok to download!"));
                object->setButton1Type(kButtonOk);
                object->setButton2Type(kButtonNone);
                object->setNotificationType(kNotificationMustUpdateNewestVersion);

                CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_MUST_UPDATE_NEWEST_VERSION,
                                                                                   object);
                return;
            }
        }
    }
    
    // Load config successful!!!
    SERVER_CONFIG().setStatusConfigLoading(kConfigLoadedSuccess);
}

void TdgServerConfig::informCheckingInternetConnection()
{
    NotificationObject* object = NotificationObject::create();
    object->setTitle(new string("Internet connection failed"));
    object->setMessage(new string("Please check your internet connection! Press Ok to retry!"));
    object->setButton1Type(kButtonOk);
    object->setButton2Type(kButtonNone);
    object->setNotificationType(kNotificationCheckingInternetFailed);

    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_CHECKING_INTERNET_FAILED,
                                                                       object);
}


