//
//  AvatarMenuItem.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/11/13.
//
//

#ifndef __Dragon_Poker__AvatarMenuItem__
#define __Dragon_Poker__AvatarMenuItem__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

// define avatar callback
typedef void (CCObject::*AvatarLoadedCallback)(CCSprite*, CCObject*);
#define avatar_selector(_SELECTOR) (AvatarLoadedCallback)(&_SELECTOR)

// define delegate
class AvatarDelegate
{
public:
    virtual void selectAvatarCallback(const char* memeberID) = 0;
};


class AvatarMenuItem : public CCMenuItemSprite {
public:
    virtual ~AvatarMenuItem();
    
    static AvatarMenuItem * create(const char* memeberID,
                                   long avatarType,
                                   CCSize avatarSize,
                                   CCPoint avatarPos);
    
    bool initWithPos(const char* memeberID,
                     long avatarType,
                     CCSize avatarSize,
                     CCPoint avatarPos);
    
    void updatePosition(CCPoint avatarPos);
    
    void internalAvatarLoadedCallback(CCSprite* avatarPhoto, CCObject* sender);
    
    void setDelegate(AvatarDelegate *avatarDelegate) {delegate = avatarDelegate;};
    
private:
    void menuSelectAvatarCallback(CCObject *pSender);
    CCSprite* maskedSprites(CCSprite *textureSprite, CCSprite *maskSprite);

    AvatarDelegate*     delegate;
    CCSize              mAvatarSize;
    CCPoint             mAvatarPos;
    string              mMemberID;
    long                mAvatarType;
};

#endif /* defined(__Dragon_Poker__AvatarMenuItem__) */
