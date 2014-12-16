//
//  DailyBonusPopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/20/14.
//
//

#include "DailyBonusPopupView.h"
#include "VisibleRect.h"
#include "TdgServer.h"
#include "DailyBonusInfo.h"
#include "UserInfo.h"
#include "SoundManager.h"
#include "NativeHelper.h"
#include "GameViewDefine.h"
#include "EziHelper.h"

#include "TdgServer.h"
#include "NotificationObject.h"

#include "VipClubPopupView.h"


DailyBonusPopupView* DailyBonusPopupView::create(string pBackgroundImage,
                                           string pExitNormalImage,
                                           string pExitSelectedImage) {
    DailyBonusPopupView* pRet = new DailyBonusPopupView();
    pRet->autorelease();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage);
    
    return pRet;
}

bool DailyBonusPopupView::init(string pBackgroundImage,
                            string pExitNormalImage,
                            string pExitSelectedImage) {
    PopUpLayer::init(pBackgroundImage,
                     pExitNormalImage,
                     pExitSelectedImage,
                     GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    setBackgroundPosition(VisibleRect::center());
    
    return true;
}

void DailyBonusPopupView::addSprites() {
    
    PopUpLayer::addSprites();
    
    mLevelSeparateSprite = CCSprite::create("pop_dailybonus_facebook_separate_line.png");
    mLevelSeparateSprite->setPosition(GPARAMS().POP_DAILYBONUS_LEVEL_SEPARATE_SPRITE_POSITION);
    mBackgroundSprite->addChild(mLevelSeparateSprite, 99);
    
    mLevelSprite = CCSprite::create("pop_dailybonus_level_bg.png");
    mLevelSprite->setPosition(GPARAMS().POP_DAILYBONUS_LEVEL_SPRITE_POSITION);
    mBackgroundSprite->addChild(mLevelSprite);
    
    mFacebookSeparateSprite = CCSprite::create("pop_dailybonus_facebook_separate_line.png");
    mFacebookSeparateSprite->setPosition(GPARAMS().POP_DAILYBONUS_FACEBOOK_SEPARATE_SPRITE_POSITION);
    mBackgroundSprite->addChild(mFacebookSeparateSprite, 99);
    
    mDaysSprite = CCSprite::create("pop_dailybonus_days_bg.png");
    mDaysSprite->setPosition(GPARAMS().POP_DAILYBONUS_DAYS_SPRITE_POSITION);
    mBackgroundSprite->addChild(mDaysSprite);
    
    mTotalBonusSprite = CCSprite::create("pop_dailybonus_total_bonus_bg.png");
    mTotalBonusSprite->setPosition(GPARAMS().POP_DAILYBONUS_TOTAL_BONUS_SPRITE_POSITION);
    mBackgroundSprite->addChild(mTotalBonusSprite);
    
    mHeaderSprite = CCSprite::create("pop_dailybonus_header_bg.png");
    mHeaderSprite->setPosition(GPARAMS().POP_DAILYBONUS_HEADER_SPRITE_POSITION);
    mBackgroundSprite->addChild(mHeaderSprite);
    
    mComebackSprite = CCSprite::create("pop_dailybonus_comeback_text.png");
    mComebackSprite->setPosition(GPARAMS().POP_DAILYBONUS_COMEBACK_SPRITE_POSITION);
    mBackgroundSprite->addChild(mComebackSprite);
    
    // add vip card
    CCString *imageName = CCString::createWithFormat("common_vip_card_sprite_%ld.png",
                                                     DAILYBONUS()->getVipStatus());
    mSliverCardSprite = CCSprite::create(imageName->getCString());
    mSliverCardSprite->setPosition(GPARAMS().POP_DAILYBONUS_SLIVER_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mSliverCardSprite, 99);
  
}

void DailyBonusPopupView::addMenuItems()
{
    PopUpLayer::addMenuItems();
    this->addClaimMenuItem(mPopupMenu, GPARAMS().POP_DAILYBONUS_CLAIM_MENUITEM_POSITION);
    this->addFriendMenuItem(mPopupMenu, GPARAMS().POP_DAILYBONUS_FACEBOOK_FRIEND_SPRITE_POSITION);
    this->addVipMenuItem(mPopupMenu, GPARAMS().POP_DAILYBONUS_VIP_SPRITE_POSITION);
}

void DailyBonusPopupView::addLabels() {
    PopUpLayer::addLabels();
    
    CCString* chipsPerFriend =
    CCString::createWithFormat("%s chips", CURRENCY_LONG(DAILYBONUS()->getBonusPerFriend()));
    
    CCString* chipsPerLevel =
    CCString::createWithFormat("%s chips", CURRENCY_LONG(DAILYBONUS()->getBonusPerLevel()));

    //update
    mDaysLabel = CCLabelTTF::create("Consecutive Days Return",
                                    DEFAULT_FONT_NAME,
                                    GPARAMS().CMM_FONT_SIZE_0,
                                    GPARAMS().POP_DAILYBONUS_DAYS_LABEL_DIMENSION,
                                    kCCTextAlignmentCenter);
    mDaysLabel->setPosition(GPARAMS().POP_DAILYBONUS_DAYS_LABEL_POSITION);
    mBackgroundSprite->addChild(mDaysLabel);
    mDaysLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mDaysChipsLabel = CCLabelTTF::create(CURRENCY_LONG(DAILYBONUS()->getDaysBonus()),
                                         DEFAULT_FONT_NAME,
                                         GPARAMS().CMM_FONT_SIZE_2);
    mDaysChipsLabel->setAnchorPoint(CCPoint(1, 0.5));
    mDaysChipsLabel->setPosition(GPARAMS().POP_DAILYBONUS_DAYS_CHIPS_LABEL_POSITION);
    mBackgroundSprite->addChild(mDaysChipsLabel);
    mDaysChipsLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mFacebookFriendPartOneLabel = CCLabelTTF::create(chipsPerFriend->getCString(),
                                                     DEFAULT_FONT_NAME,
                                                     GPARAMS().CMM_FONT_SIZE_0);
    mFacebookFriendPartOneLabel->setPosition(GPARAMS().POP_DAILYBONUS_FACEBOOK_FRIEND_PART_ONE_LABEL_POSITION);
    mBackgroundSprite->addChild(mFacebookFriendPartOneLabel, 99);
    mFacebookFriendPartOneLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mFacebookFriendPartTwoLabel = CCLabelTTF::create("facebook friend",
                                                     DEFAULT_FONT_NAME,
                                                     GPARAMS().CMM_FONT_SIZE_0);
    mFacebookFriendPartTwoLabel->setPosition(GPARAMS().POP_DAILYBONUS_FACEBOOK_FRIEND_PART_TWO_LABEL_POSITION);
    mBackgroundSprite->addChild(mFacebookFriendPartTwoLabel, 99);
    mFacebookFriendPartTwoLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mFacebookFriendChipsLabel = CCLabelTTF::create(CURRENCY_LONG(DAILYBONUS()->getFriendsBonus()),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_2);
    mFacebookFriendChipsLabel->setAnchorPoint(CCPoint(1, 0.5f));
    mFacebookFriendChipsLabel->setPosition(GPARAMS().POP_DAILYBONUS_FACEBOOK_FRIEND_CHIPS_LABEL_POSITION);
    mBackgroundSprite->addChild(mFacebookFriendChipsLabel, 99);
    mFacebookFriendChipsLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mLevelPartOneLabel = CCLabelTTF::create(chipsPerLevel->getCString(),
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_0);
    mLevelPartOneLabel->setPosition(GPARAMS().POP_DAILYBONUS_LEVEL_PART_ONE_LABEL_POSITION);
    mBackgroundSprite->addChild(mLevelPartOneLabel);
    mLevelPartOneLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mLevelPartTwoLabel = CCLabelTTF::create("level",
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_0);
    mLevelPartTwoLabel->setPosition(GPARAMS().POP_DAILYBONUS_LEVEL_PART_TWO_LABEL_POSITION);
    mBackgroundSprite->addChild(mLevelPartTwoLabel);
    mLevelPartTwoLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mLevelChipsLabel = CCLabelTTF::create(CURRENCY_LONG(DAILYBONUS()->getLevelBonus()),
                                          DEFAULT_FONT_NAME,
                                          GPARAMS().CMM_FONT_SIZE_2);
    mLevelChipsLabel->setAnchorPoint(CCPoint(1, 0.5f));
    mLevelChipsLabel->setPosition(GPARAMS().POP_DAILYBONUS_LEVEL_CHIPS_LABEL_POSITION);
    mBackgroundSprite->addChild(mLevelChipsLabel);
    mLevelChipsLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mVipLabel = CCLabelTTF::create(DAILYBONUS()->getVipTypeText().c_str(),
                                   DEFAULT_FONT_NAME,
                                   GPARAMS().CMM_FONT_SIZE_0,
                                   GPARAMS().POP_DAILYBONUS_VIP_LABEL_DIMENSION,
                                   kCCTextAlignmentCenter);
    mVipLabel->setPosition(GPARAMS().POP_DAILYBONUS_VIP_LABEL_POSITION);
    mBackgroundSprite->addChild(mVipLabel, 99);
    mVipLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mVipChipsLabel = CCLabelTTF::create(CURRENCY_LONG(DAILYBONUS()->getVipBonus()), 
                                        DEFAULT_FONT_NAME, 
                                        GPARAMS().CMM_FONT_SIZE_2);
    mVipChipsLabel->setAnchorPoint(CCPoint(1, 0.5f));
    mVipChipsLabel->setPosition(GPARAMS().POP_DAILYBONUS_VIP_CHIPS_LABEL_POSITION);
    mBackgroundSprite->addChild(mVipChipsLabel, 99);
    mVipChipsLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mTotalBonusTextLabel = CCLabelTTF::create("TOTAL BONUS", 
                                              DEFAULT_FONT_NAME, 
                                              GPARAMS().CMM_FONT_SIZE_4);
    mTotalBonusTextLabel->setPosition(GPARAMS().POP_DAILYBONUS_TOTAL_BONUS_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mTotalBonusTextLabel);
    mTotalBonusTextLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    mTotalBonusValueLabel = CCLabelTTF::create(CURRENCY_LONG(DAILYBONUS()->getTotalBonus()), 
                                               DEFAULT_FONT_NAME, 
                                               GPARAMS().CMM_FONT_SIZE_4);
    mTotalBonusValueLabel->setAnchorPoint(CCPoint(1, 0.5f));
    mTotalBonusValueLabel->setPosition(GPARAMS().POP_DAILYBONUS_TOTAL_BONUS_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mTotalBonusValueLabel);
    mTotalBonusValueLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
    
    CCString* dayPlaysString;
    if (DAILYBONUS()->getDaysPlay() < 7) {
        dayPlaysString = CCString::createWithFormat("%ld", DAILYBONUS()->getDaysPlay());
    }
    else {
        dayPlaysString = CCString::createWithFormat("6+");
    }
    
    mDaysValueLabel = CCLabelTTF::create(dayPlaysString->getCString(),
                                         DEFAULT_FONT_NAME,
                                         GPARAMS().CMM_FONT_SIZE_5);
    mDaysValueLabel->setColor(ccc3(50, 50, 50));
    mDaysValueLabel->setPosition(GPARAMS().POP_DAILYBONUS_DAYS_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mDaysValueLabel);
    mDaysValueLabel->cocos2d::CCNode::setSkewY(10.0f);

}

void DailyBonusPopupView::dailyBonusMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    SERVER().sendClaimDailyBonus();
    this->hide();
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventDailyBonus);
}

void DailyBonusPopupView::friendMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

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
}

void DailyBonusPopupView::vipMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    VipClubPopupView *vipclubPopup = VipClubPopupView::create();
    this->getParent()->addChild(vipclubPopup, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventVip);
}
