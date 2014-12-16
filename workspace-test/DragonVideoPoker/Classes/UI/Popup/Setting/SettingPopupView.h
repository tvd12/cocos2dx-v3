//
//  SettingPopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/25/14.
//
//

#ifndef __DragonVideoPoker__SettingPopupView__
#define __DragonVideoPoker__SettingPopupView__

#include  <string>

#include "cocos2d.h"
#include "PopUpLayer.h"
#include "GameParams.h"

#define TERMS_OF_USE_URL        "http://twindragonsgames.com/games/TermsOfUse.html"
#define PRIVACY_POLICY_URL      "http://twindragonsgames.com/games/PrivacyPolicy.html"

using namespace std;
using namespace cocos2d;

#define CREATE_MENUITEMTOGGLE(pMenuItemName, pTag, isOn) \
protected: \
    CCMenuItemToggle* m##pMenuItemName; \
private: \
    void add##pMenuItemName(const CCPoint &pPosition) {\
        CCMenuItem* onMenuItem = \
        CCMenuItemSprite::create(CCSprite::create("pop_setting_menuitem_sprite_on.png"), \
                        CCSprite::create("pop_setting_menuitem_sprite_on.png")); \
        CCMenuItem* offMenuItem = \
        CCMenuItemSprite::create(CCSprite::create("pop_setting_menuitem_sprite_off.png"), \
                            CCSprite::create("pop_setting_menuitem_sprite_off.png")); \
        m##pMenuItemName = CCMenuItemToggle::createWithTarget(this, \
            menu_selector(SettingPopupView::settingMenuItemCallback), \
            offMenuItem, onMenuItem, NULL); \
        m##pMenuItemName->setPosition(pPosition); \
        m##pMenuItemName->setTag(pTag); \
        m##pMenuItemName->setSelectedIndex((int)isOn); \
        this->mPopupMenu->addChild(m##pMenuItemName); \
    }


class SettingPopupView : public PopUpLayer {

public:

    static SettingPopupView* create(string pBackgroundImage = "pop_common_bg.png",
                                   string pExitNormalImage = "pop_common_close_normal.png",
                                   string pExitSelectedImage = "pop_common_close_active.png");
    
    virtual bool init(string pBackgroundImage = "pop_common_bg.png",
                      string pExitNormalImage = "pop_common_close_normal.png",
                      string pExitSelectedImage = "pop_common_close_active.png");
    
    CREATE_MENUITEMTOGGLE(SoundEffectMenuItem, soundEffectTag, GPARAMS().isSoundOn);
    CREATE_MENUITEMTOGGLE(MusicMenuItem, musicTag, GPARAMS().isMusicOn);
    CREATE_MENUITEMTOGGLE(LeftHandMenuItem, leftHandTag, GPARAMS().isLeftHand);
    CREATE_MENUITEMTOGGLE(DoubleOrNothingMenuItem, doubleOrNothingTag, GPARAMS().isDonEnabled);
    CREATE_MENUITEMTOGGLE(DoubleSpeedGameMenuItem, doubleSpeedGameTag, GPARAMS().isDoubleSpeedGameEnabled);
    
    CREATE_MENUITEM_SPRITE(RateUsMenuItem,
                           "pop_setting_rate_us_button_normal.png",
                           "pop_setting_rate_us_button_active.png",
                           SettingPopupView::settingMenuItemCallback);
    CREATE_MENUITEM_SPRITE(FeedbackMenuItem,
                           "pop_setting_feedback_button_normal.png",
                           "pop_setting_feedback_button_active.png",
                           SettingPopupView::settingMenuItemCallback);
    CREATE_MENUITEM_SPRITE(PrivatePolicyMenuItem,
                           "pop_setting_private_button_normal.png",
                           "pop_setting_private_button_active.png",
                           SettingPopupView::settingMenuItemCallback);
    CREATE_MENUITEM_SPRITE(TermOfServicesMenuItem,
                           "pop_setting_term_button_normal.png",
                           "pop_setting_term_button_active.png",
                           SettingPopupView::settingMenuItemCallback);
//    CREATE_MENUITEM_SPRITE(LikePageMenuItem,
//                           "pop_setting_like_button_normal.png",
//                           "pop_setting_like_button_active.png",
//                           SettingPopupView::settingMenuItemCallback);
//    CREATE_MENUITEM_SPRITE(InviteFriendMenuItem,
//                           "pop_setting_invite_button_normal.png",
//                           "pop_setting_invite_button_active.png",
//                           SettingPopupView::settingMenuItemCallback);

    
protected:
    virtual void addSprites();
    virtual void addMenuItems();
    virtual void addLabels();

private:
    
    enum MenuItemTag {
        soundEffectTag          = 1000,
        musicTag                = 1001,
        leftHandTag             = 1002,
        doubleOrNothingTag      = 1003,
        rateUsTag               = 1004,
        feedbackTag             = 1005,
        inviteFriendTag         = 1006,
        likePageTag             = 1007,
        privatePolicyTag        = 1008,
        termOfServicesTag       = 1009,
        doubleSpeedGameTag      = 1010,
    };
    
    void settingMenuItemCallback(CCObject *pSender);
    
    CCSprite* mHeader;
    
    CCLabelTTF* mSoundEffectLabel;
    CCLabelTTF* mMusicLabel;
    CCLabelTTF* mLeftHandLabel;
    CCLabelTTF* mDoubleOrNothingLabel;
    CCLabelTTF* mDoubleSpeedGameLabel;
};



#endif /* defined(__DragonVideoPoker__SettingPopupView__) */
