//
//  LoginScene.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#include "LoginScene.h"
#include "GameParams.h"
#include "SceneController.h"
#include "EziHelper.h"
#include "SoundManager.h"
#include "NativeHelper.h"

#include "TdgServerDefine.h"
#include "TdgServer.h"
#include "TdgServerConfig.h"

#include "VisibleRect.h"

#include "PaytableCellView.h"
#include "PaytableCell.h"

#include "NotificationObject.h"
#include "NotificationPopupView.h"

//#include "LevelupPopupView.h"
//#include "JackpotPopupView.h"
//#include "VipUpgradePopupView.h"


CCScene* LoginLayer::createScene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoginLayer* layer = LoginLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool LoginLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    
    if (SERVER_CONFIG().getStatusConfigLoading() != kConfigLoadedSuccess) {
        SERVER_CONFIG().updateConfigFromServer();
        mIsEnableLoginButtonsWhenGotConfigs = false;
    }
    else {
        mIsEnableLoginButtonsWhenGotConfigs = true;
    }
    SERVER().setLoginStatus(kUserLoggingInIDLE);
    CCSprite* background = CCSprite::create("splash.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background);
    addMenuItems();
    addLabels();
    scheduleUpdate();
    //jackpot popup demo
//    JackpotPopupView *jackpot = JackpotPopupView::create();
//    this->addChild(jackpot, 1000);
    
    //vip upgrade popup demo
    //level up demo

    // track GA
    NATIVE().sendScreenView(kGAScreenLogin);
    return true;
}

void LoginLayer::addMenuItems()
{
    mFacebookItem = CCMenuItemImage::create("login_facebook_normal.png",
                                            "login_facebook_active.png",
                                            "login_facebook_normal.png",
                                            this,
                                            menu_selector(LoginLayer::facebookMenuItemCallback));
    ((CCSprite*)mFacebookItem->getDisabledImage())->setColor(ccGRAY);
    mFacebookItem->setPosition(GPARAMS().LOG_FB_BUTTON_POSITION);
    
    
    mGuestItem = CCMenuItemImage::create("later_normal.png",
                                         "later_active.png",
                                         "later_normal.png",
                                         this,
                                         menu_selector(LoginLayer::guestMenuItemCallback));
    ((CCSprite*)mGuestItem->getDisabledImage())->setColor(ccGRAY);
    mGuestItem->setPosition(GPARAMS().LOG_GUEST_BUTTON_POSITION);

    CCMenu* pMenu = CCMenu::create(mFacebookItem, mGuestItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    // disable all buttons for waiting loading
    if (!mIsEnableLoginButtonsWhenGotConfigs) {
        disableAllLoginButtons();
    }
}

void LoginLayer::addLabels()
{
    mStatusLabel = CCLabelTTF::create("",
                                      DEFAULT_FONT_NAME,
                                      GPARAMS().CMM_FONT_SIZE_2);
    mStatusLabel->setPosition(GPARAMS().LOG_STATUS_LABEL_POSITION);
    this->addChild(mStatusLabel);
}

void LoginLayer::guestMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    SERVER().setLoginType(kGuestLogin);
    SERVER().connectToServer();
    disableAllLoginButtons();
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventGuestLogin);
    
    //Test popup
//    VipUpgradePopupView *vipUpgrade = VipUpgradePopupView::create(string("123,456"),
//                                                                  string("x1.25"),
//                                                                  1);
//    this->addChild(vipUpgrade, 1000);
//
//    JackpotPopupView *jackpot = JackpotPopupView::create(string("123"),
//                                                         123);
//    this->addChild(jackpot, 1000);
//
//    LevelupPopupView *levelup = LevelupPopupView::create(string(CURRENCY_LONG(99)));
//    this->addChild(levelup, 1000);
}

void LoginLayer::facebookMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    SERVER().setLoginStatus(kUserLoggingInFacebook);
    SERVER().setLoginType(kFacebookLogin);
    EZI().loginViaFacebook();
    disableAllLoginButtons();
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventFbLogin);
}

void LoginLayer::disableAllLoginButtons()
{
    mFacebookItem->setEnabled(false);
    mGuestItem->setEnabled(false);
}

void LoginLayer::enableAllLoginButtons()
{
    mFacebookItem->setEnabled(true);
    mGuestItem->setEnabled(true);
}

void LoginLayer::update(float dt)
{
    // update buttons status
    updateButtonsStatus();
    
    // show lobby scene if must
    if (SERVER().getIsGotUserInfo()) {
        SERVER().setIsGotUserInfo(false);

        SCONTROL().showLobbyScene();
    }
}

void LoginLayer::updateButtonsStatus()
{
    if (SERVER_CONFIG().getStatusConfigLoading() != kConfigLoadedSuccess) {
        mStatusLabel->setString("Checking Internet...");
    }
    else {
        if (!mIsEnableLoginButtonsWhenGotConfigs) {
            mStatusLabel->setString("");
            enableAllLoginButtons();
            mIsEnableLoginButtonsWhenGotConfigs = true;
        }
    }
    
    if (SERVER().getLoginStatus() != kUserLoggingInIDLE &&
        SERVER().getLoginStatus() != kUserJoinedLobbyRoom) {
        mStatusLabel->setString("Mixing the drinks...");
    }
}


