//
//  GameViewMiddle.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#include "GameViewMiddle.h"
#include "GameModel.h"
#include "GameController.h"
#include "GameViewDefine.h"

#include "GameParams.h"
#include "TextUtils.h"
#include "SoundManager.h"

#include "UserInfo.h"
#include "RoomInfo.h"
#include "ShoppingPopupView.h"
#include "UpdateableLabelTTF.h"


GameViewMiddle::~GameViewMiddle()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameViewMiddle* GameViewMiddle::create(GameModel* gameModel)
{
    GameViewMiddle *pRet = new GameViewMiddle();
    pRet->init(gameModel);
    pRet->autorelease();
    return pRet;
}

bool GameViewMiddle::init(GameModel* gameModel)
{
    if (!CCLayer::init()) {
        return false;
    }

    mUserInfo = gameModel->getUserInfo();
    mRoomInfo = gameModel->getRoomInfo();

    addSprites();
    addLabels();
    
    // init notification center
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewMiddle::
                                                                                     onBettedChipStopMoving),
                                                                  NOTIFICATION_BETTED_CHIP_STOP_MOVING,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewMiddle::
                                                                                     onBettedChipStartMoving),
                                                                  NOTIFICATION_BEETED_CHIP_START_MOVING,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewMiddle::
                                                                                     onEnableCancelBetButton),
                                                                  NOTIFICATION_ENABLE_CANCEL_BET_BUTTON,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewMiddle::
                                                                                     onDisableCancelBetButton),
                                                                  NOTIFICATION_DISABLE_CANCEL_BET_BUTTON,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewMiddle::
                                                                                     onInAppPurchaseSuccess),
                                                                  NOTIFICATION_GOT_IAP_SUCCESS,
                                                                  NULL);
    
    scheduleUpdate();
    
    return true;
}

void GameViewMiddle::onExit()
{
    CCLayer::onExit();
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void GameViewMiddle::update(float dt)
{
}

void GameViewMiddle::prepareNewGame()
{
    onEnableCancelBetButton(NULL);
    if (mTotalWonChipsLabel) {
        showBetChips();
    }
}

void GameViewMiddle::addLabels()
{
    // total chips
    mTotalChipsDisplay = mUserInfo->getTotalChips();
//    mTotalChipsLabel = CCLabelTTF::create(CURRENCY_LONG(mTotalChipsDisplay),
//                                          DEFAULT_FONT_NAME,
//                                          GPARAMS().CMM_FONT_SIZE_3);
    mTotalChipsLabel = UpdateableLabelTTF::createWithSource(mUserInfo->getUserInfoTotalChips(),
                                                            DEFAULT_FONT_NAME,
                                                            GPARAMS().CMM_FONT_SIZE_3,
                                                            NUMBER_DISPLAY_UPDATE_RATE);
    mTotalChipsLabel->setAnchorPoint(ccp(0, 0.5f));
    mTotalChipsLabel->setPosition(GPARAMS().MAIN_TOTAL_CHIPS_LABEL_POSITION);
    this->addChild(mTotalChipsLabel);

    // bet chips
    mUserInfo->setTotalBetChips(0);
    mUserInfo->setTotalWonChips(0);
    mTotalBetChipsDisplay = 0;
    mTotalWonChipsDisplay = 0;
    
    mTotalBetChipsLabel = UpdateableLabelTTF::createWithSource(mUserInfo->getUserInfoBetChips(),
                                                               DEFAULT_FONT_NAME,
                                                               GPARAMS().CMM_FONT_SIZE_3,
                                                               NUMBER_DISPLAY_UPDATE_RATE);
    mTotalBetChipsLabel->setAnchorPoint(ccp(0, 0.5f));
    mTotalBetChipsLabel->setPosition(GPARAMS().MAIN_BET_CHIPS_LABEL_POSITION);
    this->addChild(mTotalBetChipsLabel);
    
    // won chips
    mTotalWonChipsLabel = UpdateableLabelTTF::createWithSource(mUserInfo->getUserInfoTotalWonChips(),
                                                               DEFAULT_FONT_NAME,
                                                               GPARAMS().CMM_FONT_SIZE_3,
                                                               NUMBER_DISPLAY_UPDATE_RATE);
    mTotalWonChipsLabel->setAnchorPoint(ccp(0, 0.5f));
    mTotalWonChipsLabel->setPosition(GPARAMS().MAIN_WON_CHIPS_LABEL_POSITION);
    this->addChild(mTotalWonChipsLabel);
    mTotalWonChipsLabel->setVisible(false);
}

void GameViewMiddle::addSprites()
{
    CCSprite *bgChipInfo = CCSprite::create("bg_chip_statistic.png");
    bgChipInfo->setPosition(GPARAMS().MAIN_CHIP_INFO_BG_POSITION);
    addChild(bgChipInfo);
    
    CCSprite *bgTotalChips = CCSprite::create("bg_text_chips.png");
    bgTotalChips->setPosition(GPARAMS().MAIN_TOTAL_CHIP_BG_POSITION);
    addChild(bgTotalChips);
    
    mTotalChipsIcon = CCSprite::create("icon_chip.png");
    mTotalChipsIcon->setPosition(GPARAMS().MAIN_TOTAL_CHIP_ICON_POSITION);
    addChild(mTotalChipsIcon);
    
    CCSprite *bgBetChips = CCSprite::create("bg_text_bet.png");
    bgBetChips->setPosition(GPARAMS().MAIN_BET_CHIP_BG_POSITION);
    addChild(bgBetChips);

    mTotalBetChipsSprite = CCSprite::create("text_bet.png");
    mTotalBetChipsSprite->setAnchorPoint(ccp(0, 0.5f));
    mTotalBetChipsSprite->setPosition(GPARAMS().MAIN_BET_CHIPS_SPRITE_POSITION);
    this->addChild(mTotalBetChipsSprite);
    
    mTotatWonChipsSprite = CCSprite::create("text_won.png");
    mTotatWonChipsSprite->setAnchorPoint(ccp(0, 0.5f));
    mTotatWonChipsSprite->setPosition(GPARAMS().MAIN_WON_CHIPS_SPRITE_POSITION);
    this->addChild(mTotatWonChipsSprite);
    mTotatWonChipsSprite->setVisible(false);
}

void GameViewMiddle::addMenuItems(CCObject *target)
{
    CCMenu *menu = CCMenu::create();
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    // bet chip
    mTotalBetChipMenuItem = CCMenuItemImage::create("icon_chips_bet.png",
                                                    "icon_chips_bet.png",
                                                    target,
                                                    menu_selector(GameController::
                                                                  onCancelBetMenuItemCallBack));
    ((CCSprite*)mTotalBetChipMenuItem->getSelectedImage())->setColor(ccGRAY);
    mTotalBetChipMenuItem->setPosition(GPARAMS().MAIN_TOTAL_BET_CHIP_BUTTON_POSITION);
    menu->addChild(mTotalBetChipMenuItem);

    mBuyChipMenuItem = CCMenuItemImage::create("add_chips_normal.png",
                                               "add_chips_active.png",
                                               this,
                                               menu_selector(GameViewMiddle::
                                                             buyChipsItemCallback));
    mBuyChipMenuItem->setPosition(GPARAMS().MAIN_ADD_CHIP_BUTTON_POSITION);
    menu->addChild(mBuyChipMenuItem);
}

#pragma mark - menu item callback

void GameViewMiddle::buyChipsItemCallback(CCNode *sender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    ShoppingPopupView *shoppingPopup = ShoppingPopupView::create();
    this->getParent()->addChild(shoppingPopup, 1000);
}

#pragma mark - Notification Center callback

void GameViewMiddle::onBettedChipStopMoving(CCObject *object)
{
    CCNode* node = (CCNode*)object;
    
    // update total bet chip
    if (node->getTag() == TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET) {
        // start update total bet chips label
        mUserInfo->getUserInfoBetChips()->isChanged() = true;

        mTotalBetChipMenuItem->stopAllActions();
        CCScaleTo* scaleOut = CCScaleTo::create(0.1f, 1.2f);
        CCScaleTo* scaleIn = CCScaleTo::create(0.1f, 1.0f);
        CCSequence* sequence = CCSequence::create(scaleOut, scaleIn, NULL);
        mTotalBetChipMenuItem->runAction(sequence);
    }
    // update total chip
    else if (node->getTag() == TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP ||
             node->getTag() == TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP) {
        mUserInfo->getUserInfoTotalChips()->isChanged() = true;

        mTotalChipsIcon->stopAllActions();
        CCScaleTo* scaleOut = CCScaleTo::create(0.1f, 1.2f);
        CCScaleTo* scaleIn = CCScaleTo::create(0.1f, 1.0f);
        CCSequence* sequence = CCSequence::create(scaleOut, scaleIn, NULL);
        mTotalChipsIcon->runAction(sequence);
    }
}

void GameViewMiddle::onBettedChipStartMoving(CCObject *object)
{
    CCNode* node = (CCNode*)object;

    // update total bet chip
    if (node->getTag() == TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP) {
        mUserInfo->getUserInfoBetChips()->isChanged() = true;
        // user can bet again
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_ENABLE_CHIP_BUTTONS,
                                                                           NULL);
    }
    // update total chip
    else if (node->getTag() == TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET) {
        mUserInfo->getUserInfoTotalChips()->isChanged() = true;
        // disable all bet chip menu item if got max
        if (mUserInfo->getTotalBetChips() >= mRoomInfo->getMaxStakes() ||
            mUserInfo->getTotalChips() <= 0) {
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_DISABLE_CHIP_BUTTONS,
                                                                               NULL);
        }
    }
    // update won chips
    else if (node->getTag() == TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP) {
        mUserInfo->getUserInfoTotalWonChips()->isChanged() = true;
    }
}

void GameViewMiddle::onEnableCancelBetButton(CCObject *object)
{
    mTotalBetChipMenuItem->setEnabled(true);
}

void GameViewMiddle::onDisableCancelBetButton(CCObject *object)
{
    mTotalBetChipMenuItem->setEnabled(false);
}

void GameViewMiddle::onInAppPurchaseSuccess(CCObject *object)
{
    mUserInfo->getUserInfoTotalChips()->isChanged() = true;
}

#pragma mark - update label


void GameViewMiddle::showWonChips()
{
    mTotatWonChipsSprite->setVisible(true);
    mTotalWonChipsLabel->setVisible(true);
    
    mTotalBetChipsSprite->setVisible(false);
    mTotalBetChipsLabel->setVisible(false);
    
    mUserInfo->getUserInfoTotalWonChips()->isChanged() = true;
}

void GameViewMiddle::showBetChips()
{
    mTotatWonChipsSprite->setVisible(false);
    mTotalWonChipsLabel->setVisible(false);
    
    mTotalBetChipsSprite->setVisible(true);
    mTotalBetChipsLabel->setVisible(true);
    mTotalBetChipsLabel->setString("0");
    static_cast<UpdateableLabelTTF*>(mTotalBetChipsLabel)->setCurrentValue(0);
    mTotalBetChipsDisplay = 0;
}


