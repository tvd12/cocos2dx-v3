//
//  FBAvatarDownloader.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/11/13.
//
//

#include "FBAvatarDownloader.h"

#include "GameParams.h"
#include "EziSocialObject.h"

#include "cocos-ext.h"

USING_NS_CC_EXT;
using namespace std;

FBAvatarDownloader::~FBAvatarDownloader()
{
    delete mMemberID;
}

FBAvatarDownloader* FBAvatarDownloader::create(const char* memeberID,
                                               int downloadType,
                                               CCObject *listener,
                                               AvatarLoadedCallback selector)
{
    // not fb account type?
    if (memeberID[0] == '_') {
        return NULL;
    }
    
    FBAvatarDownloader *pRet = new FBAvatarDownloader();
    pRet->initWithPos(memeberID,
                      downloadType,
                      listener,
                      selector);
//    pRet->autorelease();
    
    return pRet;
}

bool FBAvatarDownloader::initWithPos(const char* memeberID,
                                     int downloadType,
                                     CCObject *listener,
                                     AvatarLoadedCallback selector)
{
    mMemberID = new std::string(memeberID);
    this->setAvatarDownloadedCallback(listener, selector);
    
    // start download avater if need
    bool forceDownloadFromServer = false;
    switch (downloadType) {
        case kFBAvatarForceDownload:
            forceDownloadFromServer = true;
            break;
            
        case kFBAvatarNormalDownload:
            forceDownloadFromServer = false;
            break;
            
        case kFBAvatarAutoDownload:
            if (arc4random() % AUTO_DOWNLOAD_FREQUENCE == 1) {
                forceDownloadFromServer = true;
            }
            break;
            
        default:
            forceDownloadFromServer = false;
            break;
    }
    
    this->startDownloadingAvatar(forceDownloadFromServer);
    
    return true;
}

#pragma mark - download avatar

void FBAvatarDownloader::startDownloadingAvatar(bool forceDownloadFromServer)
{
    int imageSize = (int) GPARAMS().CMM_ICON_FB_SIZE.width;
    CCString* fileName = CCString::createWithFormat("%s_%d_%d.jpg",
                                                    mMemberID->c_str(),
                                                    imageSize,
                                                    imageSize);

    if (forceDownloadFromServer == false) // Check if local copy exist
    {
        if (isAvatarDownloaded(fileName->getCString())) {
            // send to avatar layer
            if (m_pListener != NULL) {
                // load to sprite
                std::string file = CCFileUtils::sharedFileUtils()->getWritablePath().append(fileName->getCString());
                CCSprite* avatarPhoto = EziSocialObject::sharedObject()->generateCCSprite(file.c_str());
                
                (m_pListener->*m_pfnSelector)(avatarPhoto, this);
            }

            return;
        }
    }
    
    // download from fb server
    CCString* downloadURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?width=%d&height=%d",
                                                       mMemberID->c_str(),
                                                       imageSize,
                                                       imageSize);

    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(downloadURL->getCString());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this,
                                 httpresponse_selector(FBAvatarDownloader::onHttpRequestFBAvatarCompleted));
    request->setTag(fileName->getCString());
    
    CCHttpClient::getInstance()->send(request);
    request->release();
}

bool FBAvatarDownloader::isAvatarDownloaded(const char *fileName)
{
    std::string file = CCFileUtils::sharedFileUtils()->getWritablePath().append(fileName);

    return CCFileUtils::sharedFileUtils()->isFileExist(file);    
}

void FBAvatarDownloader::onHttpRequestFBAvatarCompleted(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse* response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLOG("Load fb avatar failed!");
        return;
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed!", response->getHttpRequest()->getTag());
    }
    
    // just for testing
//    int statusCode = response->getResponseCode();
//    char statusString[64] = {};
//    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
//    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // Dump the data
    vector<char> *buffer = response->getResponseData();
    
    // Create the CCSprite from data dump...
    
    CCImage *img = new CCImage();
    img->initWithImageData(&(buffer->front()), buffer->size());
    
    // Save file for resue.
    string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    writablePath.append(response->getHttpRequest()->getTag());
    img->saveToFile(writablePath.c_str());
    
    // send to avatar layer
    CCTexture2D* texture = new CCTexture2D();
    texture->initWithImage(img);    
    
    if (m_pListener != NULL && m_pListener->m_uID > 0
        && m_pListener->retainCount() > 0 && m_pListener->retainCount() < 10) {
        CCSprite* avatarPhoto = CCSprite::createWithTexture(texture);
        (m_pListener->*m_pfnSelector)(avatarPhoto, this);
    }
    
    else {
        texture->release();
        img->release();
    }
}
