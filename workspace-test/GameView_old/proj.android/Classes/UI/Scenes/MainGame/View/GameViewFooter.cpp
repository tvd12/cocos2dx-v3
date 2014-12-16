//
//  GameViewFooter.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#include "GameViewFooter.h"
#include "GameModel.h"
#include "GameParams.h"
#include "GameController.h"
#include "GameViewDefine.h"
#include "VideoPokerDefine.h"
#include "TextUtils.h"
#include "VisibleRect.h"
#include "NativeHelper.h"

#include "TdgServer.h"
#include "RoomInfo.h"
#include "UserInfo.h"

#include "ChipView.h"
#include "Chip.h"
#include "ChipMenuItemView.h"


GameViewFooter::~GameViewFooter()
{
    mHeldSprites->removeAllObjects();
    mHeldSprites->release();
    mWonBorders->removeAllObjects();
    mWonBorders->release();
    mCardSelectMenuItems->removeAllObjects();
    mCardSelectMenuItems->release();

    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameViewFooter* GameViewFooter::create(GameModel* gameModel)
{
    GameViewFooter *pRet = new GameViewFooter();
    pRet->init(gameModel);
    pRet->autorelease();
    return pRet;
}

bool GameViewFooter::init(GameModel* gameModel)
{
    // get width of screen
    mScreenWidth = VisibleRect::right().x;
    
    if (!CCLayer::init()) {
        return false;
    }
    
    mGameModel = gameModel;
    
    mHeldSprites = CCArray::create();
    mHeldSprites->retain();
    mWonBorders = CCArray::create();
    mWonBorders->retain();
    mCardSelectMenuItems = CCArray::create();
    mCardSelectMenuItems->retain();
    
    addSprites();
    
    // init notification center
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewFooter::
                                                                                     onEnableChipButtons),
                                                                  NOTIFICATION_ENABLE_CHIP_BUTTONS,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameViewFooter::
                                                                                     onDisableChipButtons),
                                                                  NOTIFICATION_DISABLE_CHIP_BUTTONS,
                                                                  NULL);
    this->setTouchEnabled(true);
    return true;
}

void GameViewFooter::onExit()
{
    CCLayer::onExit();
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void GameViewFooter::prepareNewGame()
{
    // show card back
    displayCardBacks(true);

    // show deal buttons and disable this
    showDealButton();
    disableDealButton();
    
    // enable all bet chips button
    if (mUserInfo->getTotalChips() >= ROOMINFO()->getMinStakes()) {
        onEnableChipButtons(NULL);
    }
    else {
        onDisableChipButtons(NULL);
    }
    
    // hide all held icons
    hideAllHeldIcons();
}

void GameViewFooter::displayCardBacks(bool isSetVisible, int positionMask)
{
    int opacity = 0;
    if (isSetVisible) {
        opacity = 255;
    }
    for (int i = 0; i < 5; i++) {
        if (positionMask & (1 << i)) {
            ((CCMenuItem*)mCardSelectMenuItems->objectAtIndex(i))->setOpacity(opacity);
        }
    }
}

void GameViewFooter::addSprites()
{
    CCSprite *bgFunction = CCSprite::create("bottom_ingame.png");
    bgFunction->setPosition(GPARAMS().MAIN_FUNCTION_BG_POSITION);
    addChild(bgFunction);
    
    mFunctionButtonBg = CCSprite::create("bottom2_ingame.png");
    mFunctionButtonBg->setPosition(GPARAMS().MAIN_FUNCTION_BUTTON_BG_POSITION);
    addChild(mFunctionButtonBg);
    
    // add chip bg
    mSmallChipBg = CCSprite::create("bottom_circle.png");
    mSmallChipBg->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[0]);
    addChild(mSmallChipBg);
    
    mMediumChipBg = CCSprite::create("bottom_circle.png");
    mMediumChipBg->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[1]);
    addChild(mMediumChipBg);
    
    mBigChipBg = CCSprite::create("bottom_circle.png");
    mBigChipBg->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[2]);
    addChild(mBigChipBg);
    
    mMaxBetBg = CCSprite::create("bottom_circle.png");
    mMaxBetBg->setPosition(GPARAMS().MAIN_MAX_BET_BUTTON_POSITION);
    addChild(mMaxBetBg);
    
    // add held sprites
    for (int i = 0; i < 5; i++) {
        CCSprite *heldSprite = CCSprite::create("hold.png");
        heldSprite->setPosition(GPARAMS().MAIN_HELDINGS_POSITIONS[i]);
        addChild(heldSprite, 100);
        heldSprite->setVisible(false);
        mHeldSprites->addObject(heldSprite);
        
        CCSprite *wonBorderSprite = CCSprite::create("hold_shine.png");
        wonBorderSprite->setPosition(GPARAMS().MAIN_CARDS_POSITIONS[i]);
        addChild(wonBorderSprite);
        wonBorderSprite->setVisible(false);
        mWonBorders->addObject(wonBorderSprite);
    }

    // Double 10 to 20?
    mDonLabel = CCLabelTTF::create("",
                                   DEFAULT_FONT_NAME,
                                   GPARAMS().CMM_FONT_SIZE_4);
    mDonLabel->setAnchorPoint(ccp(0, 0.5f));
    mDonLabel->setPosition(GPARAMS().MAIN_DON_LABEL_POSITION);
    this->addChild(mDonLabel);
    mDonLabel->setVisible(false);
    mDonLabel->enableShadow(CCSizeMake(0, -1), 0.5f, 1.0f);
}

void GameViewFooter::updateLabels()
{
}

void GameViewFooter::addMenuItems(CCObject *target)
{
    CCMenu *menu = CCMenu::create();
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    // add chips menu items
    int smallValue = ROOMINFO()->getChip1();
    int mediumValue = ROOMINFO()->getChip2();
    int bigValue = ROOMINFO()->getChip3();
    
    mSmallChipMenuItem = ChipMenuItemView::create(ChipView::create(Chip::create(CHIP_SMALL,
                                                                                smallValue),
                                                                   true),
                                                  ChipView::create(Chip::create(CHIP_SMALL,
                                                                                smallValue),
                                                                   true, true),
                                                  ChipView::create(Chip::create(CHIP_SMALL,
                                                                                smallValue),
                                                                   true, true),
                                                  target,
                                                  menu_selector(GameController::
                                                                onBetChipMenuItemCallBack));
    mSmallChipMenuItem->setTag(CHIP_SMALL);
    mSmallChipMenuItem->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[0]);
    menu->addChild(mSmallChipMenuItem);
    
    mMediumChipMenuItem = ChipMenuItemView::create(ChipView::create(Chip::create(CHIP_MEDIUM,
                                                                                 mediumValue),
                                                                    true),
                                                   ChipView::create(Chip::create(CHIP_MEDIUM,
                                                                                 mediumValue),
                                                                    true, true),
                                                   ChipView::create(Chip::create(CHIP_MEDIUM,
                                                                                 mediumValue),
                                                                    true, true),
                                                   target,
                                                   menu_selector(GameController::
                                                                 onBetChipMenuItemCallBack));
    mMediumChipMenuItem->setTag(CHIP_MEDIUM);
    mMediumChipMenuItem->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[1]);
    menu->addChild(mMediumChipMenuItem);
    
    mBigChipMenuItem = ChipMenuItemView::create(ChipView::create(Chip::create(CHIP_BIG,
                                                                              bigValue),
                                                                 true),
                                                ChipView::create(Chip::create(CHIP_BIG,
                                                                              bigValue),
                                                                 true, true),
                                                ChipView::create(Chip::create(CHIP_BIG,
                                                                              bigValue),
                                                                 true, true),
                                                target,
                                                menu_selector(GameController::
                                                              onBetChipMenuItemCallBack));
    mBigChipMenuItem->setTag(CHIP_BIG);
    mBigChipMenuItem->setPosition(GPARAMS().MAIN_BET_CHIP_BUTTONS_POSITIONS[2]);
    menu->addChild(mBigChipMenuItem);
    
    mMaxBetMenuItem = CCMenuItemImage::create("max_normal.png",
                                              "max_active.png",
                                              "max_normal.png",
                                              target,
                                              menu_selector(GameController::onMaxBetMenuItemCallBack));
    ((CCSprite*)mMaxBetMenuItem->getDisabledImage())->setColor(ccGRAY);
    mMaxBetMenuItem->setPosition(GPARAMS().MAIN_MAX_BET_BUTTON_POSITION);
    menu->addChild(mMaxBetMenuItem);
    
    // add deal button
    mDealMenuItem = CCMenuItemImage::create("deal_normal.png",
                                             "deal_active.png",
                                             "deal_unable.png",
                                             target,
                                             menu_selector(GameController::onDealMenuItemCallback));
    mDealMenuItem->setPosition(GPARAMS().MAIN_DEAL_BUTTON_POSITION);
    menu->addChild(mDealMenuItem);

    // add draw button
    mDrawMenuItem = CCMenuItemImage::create("draw_normal.png",
                                             "draw_active.png",
                                             "draw_unable.png",
                                             target,
                                             menu_selector(GameController::onDrawMenuItemCallback));
    mDrawMenuItem->setPosition(GPARAMS().MAIN_DEAL_BUTTON_POSITION);
    menu->addChild(mDrawMenuItem);
    mDrawMenuItem->setVisible(false);

    // add double or nothing buttons
    // Yes
    mDonYesMenuItem = CCMenuItemImage::create("button_yes_normal.png",
                                               "button_yes_active.png",
                                               NULL,
                                               target,
                                               menu_selector(GameController::onDonYesMenuItemCallback));
    mDonYesMenuItem->setPosition(GPARAMS().MAIN_DON_YES_BUTTON_POSITION);
    menu->addChild(mDonYesMenuItem);
    mDonYesMenuItem->setVisible(false);

    // No
    mDonNoMenuItem = CCMenuItemImage::create("button_no_normal.png",
                                              "button_no_active.png",
                                              NULL,
                                              target,
                                              menu_selector(GameController::onDonNoMenuItemCallback));
    mDonNoMenuItem->setPosition(GPARAMS().MAIN_DON_NO_BUTTON_POSITION);
    menu->addChild(mDonNoMenuItem);
    mDonNoMenuItem->setVisible(false);

    // add card select
    for (int i = 0; i < 5; i++) {
        CCMenuItem* cardSelectItem;
        cardSelectItem = CCMenuItemImage::create("cards/card_back.png",
                                                 "cards/card_back.png",
                                                 "cards/card_back.png",
                                                 target,
                                                 menu_selector(GameController::
                                                               onCardSelectMenuItemCallback));
        cardSelectItem->setPosition(GPARAMS().MAIN_CARDS_POSITIONS[i]);
        cardSelectItem->setTag(i);
        cardSelectItem->setOpacity(0);
        
        // testing
//        cardSelectItem->setScale(0.9f);
        CCMenu *cardSelectedMenu = CCMenu::createWithItem(cardSelectItem);
        cardSelectedMenu->setPosition(CCPointZero);
        this->addChild(cardSelectedMenu);
        
        mCardSelectMenuItems->addObject(cardSelectItem);
    }
    
    // show left or right hand?
    if (!GPARAMS().isLeftHand) {
        switchHandPosition();
    }
}

#pragma mark - Notification Center observer

void GameViewFooter::onEnableChipButtons(CCObject *object)
{
    mSmallChipMenuItem->setEnabled(true);
    mMediumChipMenuItem->setEnabled(true);
    mBigChipMenuItem->setEnabled(true);
    mMaxBetMenuItem->setEnabled(true);
}

void GameViewFooter::onDisableChipButtons(CCObject *object)
{
    mSmallChipMenuItem->setEnabled(false);
    mMediumChipMenuItem->setEnabled(false);
    mBigChipMenuItem->setEnabled(false);
    mMaxBetMenuItem->setEnabled(false);
}

#pragma mark - update game state

void GameViewFooter::disableDrawButton()
{
    mDrawMenuItem->setEnabled(false);
}

void GameViewFooter::enableDrawButton()
{
    mDrawMenuItem->setEnabled(true);
}

void GameViewFooter::showDrawButton(float dt)
{
    mDealMenuItem->setVisible(false);
    mDrawMenuItem->setVisible(true);
}

void GameViewFooter::disableDealButton()
{
    mDealMenuItem->setEnabled(false);
}

void GameViewFooter::enableDealButton()
{
    mDealMenuItem->setEnabled(true);
}

void GameViewFooter::showDealButton()
{
    mDealMenuItem->setVisible(true);
    mDrawMenuItem->setVisible(false);
}

void GameViewFooter::hideAllHeldIcons()
{
    for (int i = 0; i < 5; i++) {
        ((CCSprite*)mHeldSprites->objectAtIndex(i))->setVisible(false);
    }
}

void GameViewFooter::showHeldIcons(int heldBit, float delayTime)
{
    mHeldBit = heldBit;
    scheduleOnce(schedule_selector(GameViewFooter::showHeldIcons), delayTime);
}

void GameViewFooter::hideAllHighLightIcons()
{
    for (int i = 0; i < 5; i++) {
        ((CCSprite*)mWonBorders->objectAtIndex(i))->setVisible(false);
    }
}

void GameViewFooter::showHighLightIcons(int wonBit, float delayTime)
{
    mWonBit = wonBit;
    scheduleOnce(schedule_selector(GameViewFooter::showHighLightIcons), delayTime);
}

void GameViewFooter::showHeldIcons(float dt)
{
    for (int i = 0; i < 5; i++) {
        if (mHeldBit & (1 << i)) {
            ((CCSprite*)mHeldSprites->objectAtIndex(i))->setVisible(true);
        }
        else {
            ((CCSprite*)mHeldSprites->objectAtIndex(i))->setVisible(false);
        }
    }
}

void GameViewFooter::showHighLightIcons(float dt)
{
    for (int i = 0; i < 5; i++) {
        if (mWonBit & (1 << i)) {
            ((CCSprite*)mWonBorders->objectAtIndex(i))->setVisible(true);
        }
        else {
            ((CCSprite*)mWonBorders->objectAtIndex(i))->setVisible(false);
        }
    }
}

#pragma mark - hide/show double or nothing game

void GameViewFooter::showDonGame()
{
    // show card back
    displayCardBacks(true);
    
    // hide items
    mBigChipBg->setVisible(false);
    mMediumChipBg->setVisible(false);
    mSmallChipBg->setVisible(false);
    mMaxBetBg->setVisible(false);
    
    mSmallChipMenuItem->setVisible(false);
    mMediumChipMenuItem->setVisible(false);
    mBigChipMenuItem->setVisible(false);
    mMaxBetMenuItem->setVisible(false);
    
    mDrawMenuItem->setVisible(false);
    mDealMenuItem->setVisible(false);
    
    // show DON itmes
    mDonNoMenuItem->setVisible(true);
    mDonYesMenuItem->setVisible(true);
    
    mDonLabel->setVisible(true);
    CCString* donString = CCString::createWithFormat("Double %s to %s?",
                                                     CURRENCY_SHORT(mUserInfo->getTotalWonChips()),
                                                     CURRENCY_SHORT(mUserInfo->getTotalWonChips() * 2));
    mDonLabel->setString(donString->getCString());

    // create animation
    CCPoint labelPosition = mDonLabel->getPosition();
    if (GPARAMS().isLeftHand) {
        mDonLabel->setPosition(ccpAdd(mDonLabel->getPosition(), ccp(-GPARAMS().MAIN_DON_MOVING_DISTANCE, 0)));
    }
    else {
        mDonLabel->setPosition(ccpAdd(mDonLabel->getPosition(), ccp(GPARAMS().MAIN_DON_MOVING_DISTANCE, 0)));
    }
    CCMoveTo* moveTo = CCMoveTo::create(DON_MOVING_INTERVAL,
                                        labelPosition);
    mDonLabel->runAction(moveTo);
}

void GameViewFooter::hideDonGame()
{
    // show items
    mBigChipBg->setVisible(true);
    mMediumChipBg->setVisible(true);
    mSmallChipBg->setVisible(true);
    mMaxBetBg->setVisible(true);
    
    mSmallChipMenuItem->setVisible(true);
    mMediumChipMenuItem->setVisible(true);
    mBigChipMenuItem->setVisible(true);
    mMaxBetMenuItem->setVisible(true);
    
    mDealMenuItem->setVisible(true);

    // hide DON itmes
    mDonNoMenuItem->setVisible(false);
    mDonYesMenuItem->setVisible(false);
    mDonLabel->setVisible(false);
    
    // hide all held icons
    hideAllHeldIcons();
}

void GameViewFooter::startDonGame()
{
    // hide don buttons
    mDonNoMenuItem->setVisible(false);
    mDonYesMenuItem->setVisible(false);

    // show deal buttons
    mDealMenuItem->setVisible(true);
    mDealMenuItem->setEnabled(false);
    
    // update label
    mDonLabel->setString("Tap card to select!");
}

void GameViewFooter::dealDonGame()
{
    enableDealButton();
        
    // change text of don label
    mDonLabel->setString("Tap DEAL to play!");
}

void GameViewFooter::showResultDonGame()
{
    switch (mGameModel->getDonResult()) {
        case DON_RESULT_WON:
            mDonLabel->setString("YOU WON!");
            break;
            
        case DON_RESULT_LOSE:
            mDonLabel->setString("YOU LOSE!");
            break;
            
        case DON_RESULT_PUSH:
            mDonLabel->setString("PUSH!");
            break;
            
        default:
            break;
    }
}

#pragma mark - show right/left hand

CCPoint GameViewFooter::switchHandPoint(CCPoint leftPoint)
{
    CCPoint ret = ccp(mScreenWidth - leftPoint.x,
                      leftPoint.y);
    return ret;
}

void GameViewFooter::updateImagesForMenuItem(CCMenuItemImage* menuItem,
                                             const char* itemNameFormat,
                                             bool isHaveDisableImage)
{
    CCString* normalName = CCString::createWithFormat(itemNameFormat, "normal");
    CCString* activeName = CCString::createWithFormat(itemNameFormat, "active");
    menuItem->setNormalImage(CCSprite::create(normalName->getCString()));
    menuItem->setSelectedImage(CCSprite::create(activeName->getCString()));

    if (isHaveDisableImage) {
        CCString* unableName = CCString::createWithFormat(itemNameFormat, "unable");
        menuItem->setDisabledImage(CCSprite::create(unableName->getCString()));
    }
    
    // change position
    menuItem->setPosition(switchHandPoint(menuItem->getPosition()));
}

void GameViewFooter::switchHandPosition()
{
    // swith position
    mFunctionButtonBg->setPosition(switchHandPoint(mFunctionButtonBg->getPosition()));
    mSmallChipBg->setPosition(switchHandPoint(mSmallChipBg->getPosition()));
    mMediumChipBg->setPosition(switchHandPoint(mMediumChipBg->getPosition()));
    mBigChipBg->setPosition(switchHandPoint(mBigChipBg->getPosition()));
    mMaxBetBg->setPosition(switchHandPoint(mMaxBetBg->getPosition()));
    
    mSmallChipMenuItem->setPosition(switchHandPoint(mSmallChipMenuItem->getPosition()));
    mMediumChipMenuItem->setPosition(switchHandPoint(mMediumChipMenuItem->getPosition()));
    mBigChipMenuItem->setPosition(switchHandPoint(mBigChipMenuItem->getPosition()));
    mMaxBetMenuItem->setPosition(switchHandPoint(mMaxBetMenuItem->getPosition()));
    
    mDonLabel->setPosition(switchHandPoint(mDonLabel->getPosition()));

    if (GPARAMS().isLeftHand) {
        showLeftHandUI();
    }
    else {
        showRightHandUI();
    }
}

void GameViewFooter::showLeftHandUI()
{
    // update feature buttons
    updateImagesForMenuItem(mDealMenuItem, "deal_%s.png");
    updateImagesForMenuItem(mDrawMenuItem, "draw_%s.png");
    updateImagesForMenuItem(mDonYesMenuItem, "button_yes_%s.png", false);
    updateImagesForMenuItem(mDonNoMenuItem, "button_no_%s.png", false);
    
    // update chips buttons
    mFunctionButtonBg->setFlipX(false);
    
    // update label
    mDonLabel->setAnchorPoint(ccp(0, 0.5f));

}

void GameViewFooter::showRightHandUI()
{
    // update feature buttons
    updateImagesForMenuItem(mDealMenuItem, "deal_%s_flip.png");
    updateImagesForMenuItem(mDrawMenuItem, "draw_%s_flip.png");
    updateImagesForMenuItem(mDonYesMenuItem, "button_yes_%s_flip.png", false);
    updateImagesForMenuItem(mDonNoMenuItem, "button_no_%s_flip.png", false);
    
    // update chips buttons
    mFunctionButtonBg->setFlipX(true);

    // update label
    mDonLabel->setAnchorPoint(ccp(1.0f, 0.5f));
}

