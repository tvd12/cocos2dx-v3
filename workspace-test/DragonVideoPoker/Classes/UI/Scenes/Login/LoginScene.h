//
//  LoginScene.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef __DragonVideoPoker__LoginScene__
#define __DragonVideoPoker__LoginScene__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class LoginLayer : public CCLayer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(LoginLayer);
    
private:
    void addMenuItems();
    void addLabels();
    
    void guestMenuItemCallback(CCObject* pSender);
    void facebookMenuItemCallback(CCObject* pSender);
    
    void disableAllLoginButtons();
    void enableAllLoginButtons();
    
    void updateButtonsStatus();
    
    CCMenuItemImage* mFacebookItem;
//    CCMenuItemSprite *mCancelLoginItem;
    CCMenuItemImage* mGuestItem;
    CCLabelTTF* mStatusLabel;
    
    bool mIsEnableLoginButtonsWhenGotConfigs;
    
};

#endif /* defined(__DragonVideoPoker__LoginScene__) */
