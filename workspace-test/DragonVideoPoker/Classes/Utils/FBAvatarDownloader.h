//
//  FBAvatarDownloader.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/11/13.
//
//

#ifndef __Dragon_Poker__FBAvatarDownloader__
#define __Dragon_Poker__FBAvatarDownloader__

#include "cocos2d.h"
#include "AvatarMenuItem.h"

USING_NS_CC;

#define AUTO_DOWNLOAD_FREQUENCE             50

typedef enum AVATAR_DOWNLOAD_TYPE {
    kFBAvatarForceDownload,
    kFBAvatarAutoDownload,
    kFBAvatarNormalDownload         // Do not force download
} Avatar_Download_type;

class FBAvatarDownloader : public CCObject {
public:
    
    virtual ~FBAvatarDownloader();

    static FBAvatarDownloader * create(const char* memeberID,
                                       int downloadType,
                                       CCObject *listener,
                                       AvatarLoadedCallback selector);
    
    bool initWithPos(const char* memeberID,
                     int downloadType,
                     CCObject *listener,
                     AvatarLoadedCallback selector);

    // Update avatar downloaded callback
    void setAvatarDownloadedCallback(CCObject *listener, AvatarLoadedCallback selector)
    {
        m_pListener = listener;
        m_pfnSelector = selector;
    };
    
private:
    bool isDownloading;
    
    std::string *mMemberID;
    
    CCObject* m_pListener;
    AvatarLoadedCallback m_pfnSelector;

    void startDownloadingAvatar(bool forceDownloadFromServer);
    bool isAvatarDownloaded(const char *fileName);
    
    void onHttpRequestFBAvatarCompleted(cocos2d::CCNode *sender, void *data);
};

#endif /* defined(__Dragon_Poker__FBAvatarDownloader__) */
