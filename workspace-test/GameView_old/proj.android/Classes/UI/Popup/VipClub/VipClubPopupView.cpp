//
//  VipClubPopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/22/14.
//
//

#include "VipClubPopupView.h"
#include "GameParams.h"
#include "VisibleRect.h"
#include "TdgServer.h"
#include "VipInfo.h"
#include "UserInfo.h"

VipClubPopupView* VipClubPopupView::create(string pBackgroundImage,
                                           string pExitNormalImage,
                                           string pExitSelectedImage) {
    VipClubPopupView* pRet = new VipClubPopupView();
    pRet->autorelease();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage);
    
    return pRet;
}

bool VipClubPopupView::init(string pBackgroundImage,
                            string pExitNormalImage,
                            string pExitSelectedImage) {
    PopUpLayer::init(pBackgroundImage,
                     pExitNormalImage,
                     pExitSelectedImage,
                     GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    setBackgroundPosition(VisibleRect::center());
    
    return true;
}

void VipClubPopupView::addSprites()
{
    // add text sprites
    mPlatinumTextSprite = CCSprite::create("pop_vipclub_platinum_text_sprite.png");
    mPlatinumTextSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mPlatinumTextSprite->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_TEXT_SPRITE_POSITION);
    mBackgroundSprite->addChild(mPlatinumTextSprite);
    
    mBronzeTextSprite = CCSprite::create("pop_vipclub_bronze_text_sprite.png");
    mBronzeTextSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mBronzeTextSprite->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_TEXT_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBronzeTextSprite);
    
    mDiamondTextSprite = CCSprite::create("pop_vipclub_diamond_text_sprite.png");
    mDiamondTextSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mDiamondTextSprite->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_TEXT_SPRITE_POSITION);
    mBackgroundSprite->addChild(mDiamondTextSprite);
    
    mSliverTextSprite = CCSprite::create("pop_vipclub_sliver_text_sprite.png");
    mSliverTextSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mSliverTextSprite->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_TEXT_SPRITE_POSITION);
    mBackgroundSprite->addChild(mSliverTextSprite);
    
    mGoldTextSprite = CCSprite::create("pop_vipclub_gold_text_sprite.png");
    mGoldTextSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mGoldTextSprite->setPosition(GPARAMS().POP_VIPCLUB_GOLD_TEXT_SPRITE_POSITION);
    mBackgroundSprite->addChild(mGoldTextSprite);
    
    // add small cards
    mBronzeCardSprite = CCSprite::create("common_vip_card_sprite_1.png");
    mBronzeCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBronzeCardSprite);
    
    mSliverCardSprite = CCSprite::create("common_vip_card_sprite_2.png");
    mSliverCardSprite->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mSliverCardSprite);
    
    mGoldCardSprite = CCSprite::create("common_vip_card_sprite_3.png");
    mGoldCardSprite->setPosition(GPARAMS().POP_VIPCLUB_GOLD_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mGoldCardSprite);
    
    mPlatinumCardSprite = CCSprite::create("common_vip_card_sprite_4.png");
    mPlatinumCardSprite->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mPlatinumCardSprite);
    
    mDiamondCardSprite = CCSprite::create("common_vip_card_sprite_5.png");
    mDiamondCardSprite->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mDiamondCardSprite);
    
    // add big cards sprite
    mMemberCardSprite = CCSprite::create("common_vip_card_sprite_0_big.png");
    mMemberCardSprite->setPosition(GPARAMS().POP_VIPCLUB_MEMBER_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mMemberCardSprite);
    
    mBigBronzeCardSprite = CCSprite::create("common_vip_card_sprite_1_big.png");
    mBigBronzeCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BIG_BRONZE_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBigBronzeCardSprite);
    
    mBigSliverCardSprite = CCSprite::create("common_vip_card_sprite_2_big.png");
    mBigSliverCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BIG_SLIVER_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBigSliverCardSprite);
    
    mBigGoldCardSprite = CCSprite::create("common_vip_card_sprite_3_big.png");
    mBigGoldCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BIG_GOLD_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBigGoldCardSprite);
    
    mBigPlatinumCardSprite = CCSprite::create("common_vip_card_sprite_4_big.png");
    mBigPlatinumCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BIG_PLATINUM_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBigPlatinumCardSprite);
    
    mBigDiamondCardSprite = CCSprite::create("common_vip_card_sprite_5_big.png");
    mBigDiamondCardSprite->setPosition(GPARAMS().POP_VIPCLUB_BIG_DIAMOND_CARD_SPRITE_POSITION);
    mBackgroundSprite->addChild(mBigDiamondCardSprite);
    
    // add others
    mLinesSprite = CCSprite::create("pop_vipclub_lines_sprite.png");
    mLinesSprite->setPosition(GPARAMS().POP_VIPCLUB_LINES_SPRITE_POSITION);
    mBackgroundSprite->addChild(mLinesSprite, 999);
    
    mHeaderSprite = CCSprite::create("pop_vipclub_header_sprite.png");
    mHeaderSprite->setPosition(GPARAMS().POP_VIPCLUB_HEADER_SPRITE_POSITION);
    mBackgroundSprite->addChild(mHeaderSprite);
    
    mProgressLevelSprite = CCSprite::create("pop_vipclub_progress_level_sprite.png");
    
    mProgressLevelBackgroundSprite = CCSprite::create("pop_vipclub_progress_level_background_sprite.png");
    mProgressLevelBackgroundSprite->setPosition(GPARAMS().POP_VIPCLUB_PROGRESS_LEVEL_BACKGROUND_SPRITE_POSITION);
    mBackgroundSprite->addChild(mProgressLevelBackgroundSprite);
    
    //set visible for current big card
    CCSprite *bigCards[5] = {
        mBigBronzeCardSprite, mBigSliverCardSprite,
        mBigGoldCardSprite, mBigPlatinumCardSprite, mBigDiamondCardSprite
    };
    for(int i = 0 ; i < 5 ; i++) {
        mCheckedSprites[i] = CCSprite::create("pop_vipclub_checked_sprite.png");
        mCheckedSprites[i]->setPosition(GPARAMS().POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[i]);
        mCheckedSprites[i]->setVisible(false);
        mBackgroundSprite->addChild(mCheckedSprites[i]);
        bigCards[i]->setVisible(false);
    }
    if(USERINFO()->getVipType() > 0 && USERINFO()->getVipType() < 5) {
        mCheckedSprites[USERINFO()->getVipType() - 1]->setVisible(true);
        bigCards[USERINFO()->getVipType() - 1]->setVisible(true);
    }
    else if(USERINFO()->getVipType() >= 5) {
        mCheckedSprites[4]->setVisible(true);
        bigCards[4]->setVisible(true);
    }
    
    else {
        mProgressLevelBackgroundSprite->setVisible(false);
    }

}

void VipClubPopupView::addLabels() {
    mNoteMorePointsLabel = CCLabelTTF::create(VIPINFOLIST()->at(USERINFO()->getVipType())->getDescriptionText1(),
                                              DEFAULT_FONT_NAME,
                                              GPARAMS().CMM_FONT_SIZE_0);
    mNoteMorePointsLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mNoteMorePointsLabel->setPosition(GPARAMS().POP_VIPCLUB_NOTE_MORE_POINTS_LABEL_POSITION);
    mBackgroundSprite->addChild(mNoteMorePointsLabel);
    
    mNoteMultipleLabel = CCLabelTTF::create(VIPINFOLIST()->at(USERINFO()->getVipType())->getDescriptionText2(),
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_0);
    mNoteMultipleLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mNoteMultipleLabel->setPosition(GPARAMS().POP_VIPCLUB_NOTE_MULTIPLE_LABEL_POSITION);
    mBackgroundSprite->addChild(mNoteMultipleLabel);
    
    mBronzeVipPointTextLabel = CCLabelTTF::create("Vip point",
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_1);
    mBronzeVipPointTextLabel->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_VIP_POINT_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mBronzeVipPointTextLabel);
    
    mBronzeVipPointValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPBronze)->getVipPointRequireText(),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mBronzeVipPointValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mBronzeVipPointValueLabel->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_VIP_POINT_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mBronzeVipPointValueLabel);
    
    mBronzePackagesTextLabel = CCLabelTTF::create("Packages",
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_1);
    mBronzePackagesTextLabel->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_PACKAGES_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mBronzePackagesTextLabel);
    
    mBronzePackagesValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPBronze)->getMultiplyText(),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mBronzePackagesValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mBronzePackagesValueLabel->setPosition(GPARAMS().POP_VIPCLUB_BRONZE_PACKAGES_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mBronzePackagesValueLabel);
    
    mSliverVipPointTextLabel = CCLabelTTF::create("Vip point",
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_1);
    mSliverVipPointTextLabel->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_VIP_POINT_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mSliverVipPointTextLabel);
    
    mSliverVipPointValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPSilver)->getVipPointRequireText(),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mSliverVipPointValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mSliverVipPointValueLabel->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_VIP_POINT_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mSliverVipPointValueLabel);
    
    mSliverPackagesTextLabel = CCLabelTTF::create("Packages",
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_1);
    mSliverPackagesTextLabel->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_PACKAGES_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mSliverPackagesTextLabel);
    
    mSliverPackagesValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPSilver)->getMultiplyText(),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mSliverPackagesValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mSliverPackagesValueLabel->setPosition(GPARAMS().POP_VIPCLUB_SLIVER_PACKAGES_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mSliverPackagesValueLabel);
    
    mGoldVipPointTextLabel = CCLabelTTF::create("Vip point",
                                                DEFAULT_FONT_NAME,
                                                GPARAMS().CMM_FONT_SIZE_1);
    mGoldVipPointTextLabel->setPosition(GPARAMS().POP_VIPCLUB_GOLD_VIP_POINT_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mGoldVipPointTextLabel);
    
    mGoldVipPointValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPGold)->getVipPointRequireText(),
                                                 DEFAULT_FONT_NAME,
                                                 GPARAMS().CMM_FONT_SIZE_1);
    mGoldVipPointValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mGoldVipPointValueLabel->setPosition(GPARAMS().POP_VIPCLUB_GOLD_VIP_POINT_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mGoldVipPointValueLabel);
    
    mGoldPackagesTextLabel = CCLabelTTF::create("Packages",
                                                DEFAULT_FONT_NAME,
                                                GPARAMS().CMM_FONT_SIZE_1);
    mGoldPackagesTextLabel->setPosition(GPARAMS().POP_VIPCLUB_GOLD_PACKAGES_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mGoldPackagesTextLabel);
    
    mGoldPackagesValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPGold)->getMultiplyText(),
                                                 DEFAULT_FONT_NAME,
                                                 GPARAMS().CMM_FONT_SIZE_1);
    mGoldPackagesValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mGoldPackagesValueLabel->setPosition(GPARAMS().POP_VIPCLUB_GOLD_PACKAGES_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mGoldPackagesValueLabel);
    
    mPlatinumVipPointTextLabel = CCLabelTTF::create("Vip point",
                                                    DEFAULT_FONT_NAME,
                                                    GPARAMS().CMM_FONT_SIZE_1);
    mPlatinumVipPointTextLabel->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_VIP_POINT_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mPlatinumVipPointTextLabel);
    
    mPlatinumVipPointValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPPlatinum)->getVipPointRequireText(),
                                                     DEFAULT_FONT_NAME,
                                                     GPARAMS().CMM_FONT_SIZE_1);
    mPlatinumVipPointValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mPlatinumVipPointValueLabel->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_VIP_POINT_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mPlatinumVipPointValueLabel);
    
    mPlatinumPackagesTextLabel = CCLabelTTF::create("Packages",
                                                    DEFAULT_FONT_NAME, 
                                                    GPARAMS().CMM_FONT_SIZE_1);
    mPlatinumPackagesTextLabel->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_PACKAGES_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mPlatinumPackagesTextLabel);
    
    mPlatinumPackagesValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPPlatinum)->getMultiplyText(),
                                                     DEFAULT_FONT_NAME, 
                                                     GPARAMS().CMM_FONT_SIZE_1);
    mPlatinumPackagesValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mPlatinumPackagesValueLabel->setPosition(GPARAMS().POP_VIPCLUB_PLATINUM_PACKAGES_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mPlatinumPackagesValueLabel);
    
    mDiamondVipPointTextLabel = CCLabelTTF::create("Vip point", 
                                                   DEFAULT_FONT_NAME, 
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mDiamondVipPointTextLabel->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_VIP_POINT_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mDiamondVipPointTextLabel);
    
    mDiamondVipPointValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPDiamond)->getVipPointRequireText(),
                                                    DEFAULT_FONT_NAME, 
                                                    GPARAMS().CMM_FONT_SIZE_1);
    mDiamondVipPointValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mDiamondVipPointValueLabel->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_VIP_POINT_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mDiamondVipPointValueLabel);
    
    mDiamondPackagesTextLabel = CCLabelTTF::create("Packages", 
                                                   DEFAULT_FONT_NAME, 
                                                   GPARAMS().CMM_FONT_SIZE_1);
    mDiamondPackagesTextLabel->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_PACKAGES_TEXT_LABEL_POSITION);
    mBackgroundSprite->addChild(mDiamondPackagesTextLabel);
    
    mDiamondPackagesValueLabel = CCLabelTTF::create(VIPINFOLIST()->at(kVIPDiamond)->getMultiplyText(),
                                                    DEFAULT_FONT_NAME, 
                                                    GPARAMS().CMM_FONT_SIZE_1);
    mDiamondPackagesValueLabel->setAnchorPoint(CCPoint(0.0, 0.5));
    mDiamondPackagesValueLabel->setPosition(GPARAMS().POP_VIPCLUB_DIAMOND_PACKAGES_VALUE_LABEL_POSITION);
    mBackgroundSprite->addChild(mDiamondPackagesValueLabel);
    
    mProgressTextLabel = CCLabelTTF::create(VIPINFOLIST()->at(USERINFO()->getVipType())->getProgressText(),
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_2);
    mProgressTextLabel->setPosition(CCPoint(mProgressLevelBackgroundSprite->getContentSize().width/2,
                                            mProgressLevelBackgroundSprite->getContentSize().height/2));
    mProgressLevelBackgroundSprite->addChild(mProgressTextLabel, 100);
    
    if(USERINFO()->getVipType() <= 0) {
        mNoteMorePointsLabel->setPosition(CCPoint(GPARAMS().POP_VIPCLUB_NOTE_MORE_POINTS_LABEL_POSITION.x,
                                                  GPARAMS().POP_VIPCLUB_PROGRESS_LEVEL_BACKGROUND_SPRITE_POSITION.y));
    }
    
    
}

void VipClubPopupView::addProgressBars() {
    PopUpLayer::addProgressBars();
    if(USERINFO()->getVipType() <= 0) {
        return;
    }
    CCProgressTimer* levelProgressBar = CCProgressTimer::create(mProgressLevelSprite);
    levelProgressBar->setType(kCCProgressTimerTypeBar);
    levelProgressBar->setAnchorPoint(CCPointZero);
    levelProgressBar->setMidpoint(CCPointZero);
    levelProgressBar->setBarChangeRate(CCPoint(1, 0));
    
    float percent;
    if(USERINFO()->getVipType() < 5) {
        percent = VIPINFOLIST()->at(USERINFO()->getVipType())->getProgressPercent();
    }
    else {
        percent = 100.0f;
    }
    levelProgressBar->setPercentage(percent);
    mProgressLevelBackgroundSprite->addChild(levelProgressBar, 99);
}