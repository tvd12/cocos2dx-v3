//
//  SettingPopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/25/14.
//
//

#include "SettingPopupView.h"
#include "PopUpLayer.h"
#include "VisibleRect.h"
#include "GameViewDefine.h"
#include "SoundManager.h"
#include "NativeHelper.h"
#include "EziHelper.h"

#include "TdgServer.h"
#include "NotificationObject.h"


SettingPopupView* SettingPopupView::create(string pBackgroundImage,
                                           string pExitNormalImage,
                                           string pExitSelectedImage) {
    SettingPopupView* pRet = new SettingPopupView();
    pRet->autorelease();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage);
    
    return pRet;
}

bool SettingPopupView::init(string pBackgroundImage,
                            string pExitNormalImage,
                            string pExitSelectedImage) {
    PopUpLayer::init(pBackgroundImage,
                     pExitNormalImage,
                     pExitSelectedImage,
                     GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    setBackgroundPosition(VisibleRect::center());
    
    return true;
}

void SettingPopupView::addMenuItems() {
    
    PopUpLayer::addMenuItems();
    
    //add toggle menu item
    this->addSoundEffectMenuItem(GPARAMS().POP_SETTING_SOUND_EFFECT_MENUITEM_POSITION);
    this->addMusicMenuItem(GPARAMS().POP_SETTING_MUSIC_MENUITEM_POSITION);
    this->addLeftHandMenuItem(GPARAMS().POP_SETTING_LEFT_HAND_MENUITEM_POSITION);
    this->addDoubleOrNothingMenuItem(GPARAMS().POP_SETTING_DOUBLE_OR_NOTHING_MENUITEM_POSITION);
    this->addDoubleSpeedGameMenuItem(GPARAMS().POP_SETTING_DOUBLE_SPEED_PLAY_MENUITEM_POSITION);
    
    //add menu item sprite
    this->addRateUsMenuItem(mPopupMenu, GPARAMS().POP_SETTING_RATE_US_MENUITEM_POSITION);
    this->addFeedbackMenuItem(mPopupMenu, GPARAMS().POP_SETTING_FEEDBACK_MENUITEM_POSITION);
    this->addPrivatePolicyMenuItem(mPopupMenu, GPARAMS().POP_SETTING_PRIVATE_POLICY_MENUITEM_POSITION);
    this->addTermOfServicesMenuItem(mPopupMenu, GPARAMS().POP_SETTING_TERM_OF_SERVICES_MENUITEM_POSITION);
//    this->addInviteFriendMenuItem(mPopupMenu, GPARAMS().POP_SETTING_INVITE_FRIEND_MENUITEM_POSITION);
//    this->addLikePageMenuItem(mPopupMenu, GPARAMS().POP_SETTING_LIKE_PAGE_MENUITEM_POSITION);
    
    //set tag for menu item
    this->mRateUsMenuItem->setTag(rateUsTag);
    this->mFeedbackMenuItem->setTag(feedbackTag);
    this->mPrivatePolicyMenuItem->setTag(privatePolicyTag);
    this->mTermOfServicesMenuItem->setTag(termOfServicesTag);
//    this->mInviteFriendMenuItem->setTag(inviteFriendTag);
//    this->mLikePageMenuItem->setTag(likePageTag);
}

void SettingPopupView::addSprites() {
    mHeader = CCSprite::create("pop_setting_header.png");
    mHeader->setPosition(GPARAMS().POP_COMMON_HEADER_POSITION);
    mBackgroundSprite->addChild(mHeader);
}

void SettingPopupView::addLabels() {
    //add sound effect label
    mSoundEffectLabel = CCLabelTTF::create("Sound Effect",
                                           DEFAULT_FONT_NAME,
                                           GPARAMS().CMM_FONT_SIZE_4);
    mSoundEffectLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mSoundEffectLabel->setPosition(GPARAMS().POP_SETTING_SOUND_EFFECT_LABEL_POSITION);
    mBackgroundSprite->addChild(mSoundEffectLabel);
    
    //add music label
    mMusicLabel = CCLabelTTF::create("Music",
                                     DEFAULT_FONT_NAME,
                                     GPARAMS().CMM_FONT_SIZE_4);
    mMusicLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mMusicLabel->setPosition(GPARAMS().POP_SETTING_MUSIC_LABEL_POSITION);
    mBackgroundSprite->addChild(mMusicLabel);
    
    //add left hand label
    mLeftHandLabel = CCLabelTTF::create("Left hand",
                                        DEFAULT_FONT_NAME,
                                        GPARAMS().CMM_FONT_SIZE_4);
    mLeftHandLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mLeftHandLabel->setPosition(GPARAMS().POP_SETTING_LEFT_HAND_LABEL_POSITION);
    mBackgroundSprite->addChild(mLeftHandLabel);
    
    //add double or nothing label
    mDoubleOrNothingLabel = CCLabelTTF::create("Double or Nothing",
                                               DEFAULT_FONT_NAME,
                                               GPARAMS().CMM_FONT_SIZE_4);
    mDoubleOrNothingLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mDoubleOrNothingLabel->setPosition(GPARAMS().POP_SETTING_DOUBLE_OR_NOTHING_LABEL_POSITION);
    mBackgroundSprite->addChild(mDoubleOrNothingLabel);
    
    //add double or nothing label
    mDoubleSpeedGameLabel = CCLabelTTF::create("Double Speed Game",
                                               DEFAULT_FONT_NAME,
                                               GPARAMS().CMM_FONT_SIZE_4);
    mDoubleSpeedGameLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mDoubleSpeedGameLabel->setPosition(GPARAMS().POP_SETTING_DOUBLE_SPEED_PLAY_LABEL_POSITION);
    mBackgroundSprite->addChild(mDoubleSpeedGameLabel);
}

void SettingPopupView::settingMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    CCMenuItem* menuItem = static_cast<CCMenuItem*>(pSender);
    CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menuItem);
    
    switch (menuItem->getTag()) {
        case soundEffectTag:
            GPARAMS().isSoundOn = (bool)menuItemToggle->getSelectedIndex();
            CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_SOUND_EFFECT,
                                                              GPARAMS().isSoundOn);
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        case musicTag:
            if (menuItemToggle->getSelectedIndex()) {
                GPARAMS().isMusicOn = (bool)menuItemToggle->getSelectedIndex();
                SOUND().playBackgroundMusic();
            }
            else {
                SOUND().pauseBackgroundMusicIfNeed();
                GPARAMS().isMusicOn = (bool)menuItemToggle->getSelectedIndex();
            }
            
            CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_MUSIC,
                                                              GPARAMS().isMusicOn);
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        case leftHandTag:
            GPARAMS().isLeftHand = (bool)menuItemToggle->getSelectedIndex();
            CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_LEFT_HAND,
                                                              GPARAMS().isLeftHand);
            CCUserDefault::sharedUserDefault()->flush();
            
            // Notify to view UI
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_SWITCH_HAND);
            
            // track GA
            if (GPARAMS().isLeftHand) {
                NATIVE().sendMainEvent(kGAGameEventLeftHand);
            }
            else {
                NATIVE().sendMainEvent(kGAGameEventRightHand);
            }
            break;
            
        case doubleOrNothingTag:
            GPARAMS().isDonEnabled = (bool)menuItemToggle->getSelectedIndex();
            CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_DOUBLE_OR_NOTHING,
                                                              GPARAMS().isDonEnabled);
            CCUserDefault::sharedUserDefault()->flush();
            
            // track GA
            if (GPARAMS().isDonEnabled) {
                NATIVE().sendMainEvent(kGAGameEventDonEnable);
            }
            else {
                NATIVE().sendMainEvent(kGAGameEventDonDisable);
            }
            break;
            
        case doubleSpeedGameTag:
            GPARAMS().isDoubleSpeedGameEnabled = (bool)menuItemToggle->getSelectedIndex();
            CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_DOUBLE_SPEED_GAME,
                                                              GPARAMS().isDoubleSpeedGameEnabled);
            CCUserDefault::sharedUserDefault()->flush();
            
            // track GA
            if (GPARAMS().isDoubleSpeedGameEnabled) {
                NATIVE().sendMainEvent(kGAMainEventDoubleSpeedGameOn);
            }
            else {
                NATIVE().sendMainEvent(kGAMainEventDoubleSpeedGameOff);
            }
            break;
            
        case rateUsTag:
            NATIVE().rateUsOnStore();
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventRateUs);
            break;
            
        case feedbackTag:
            NATIVE().sendFeedback();
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventContact);
            break;
            
        case privatePolicyTag:
            NATIVE().openUrl(PRIVACY_POLICY_URL);
            break;
            
        case termOfServicesTag:
            NATIVE().openUrl(TERMS_OF_USE_URL);
            break;
            
        case likePageTag:
            EZI().openFacebookPage();
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventFanPage);
            break;
            
        case inviteFriendTag:
            if (SERVER().getLoginType() == kGuestLogin) {
                NotificationObject* object = NotificationObject::create();
                object->setTitle(new string("Cannot Invite Friend"));
                object->setMessage(new string("You must login via Facebook to invite friend!"));
                object->setButton1Type(kButtonOk);
                object->setButton2Type(kButtonNone);
                object->setNotificationType(0);
                
                CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_CANNOT_INVITE_FRIEND,
                                                                                   object);
            }
            else {
                EZI().inviteFriends();
            }
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventInviteFriend);
            break;
            
        default:
            break;
    }
}
