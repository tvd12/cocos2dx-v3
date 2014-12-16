#include <climits>

#include "LobbyScene.h"

#include "CCScrollLayer.h"
#include "SelectGameMenuItem.h"

#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "UserInfo.h"
#include "BaseUserInfo.h"

#include "RoomInfo.h"
#include "HourlyBonusInfo.h"
#include "DailyBonusInfo.h"

#include "GameParams.h"
#include "VisibleRect.h"
#include "SceneController.h"
#include "ProfilePopupView.h"
#include "GameViewDefine.h"
#include "ChipView.h"
#include "Chip.h"
#include "SoundManager.h"
#include "NativeHelper.h"

#include "DailyBonusPopupView.h"
#include "ShoppingPopupView.h"
#include "SettingPopupView.h"
#include "NotificationObject.h"

#include "ChartBoostHelper.h"
#include "LeaderboardPopupView.h"
#include "UpdateableLabelTTF.h"

#define INDEX_OF_FIRST_MENU     0
#define BOUNCE_DURATION         0.3f

CCScene* LobbyLayer::createScene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LobbyLayer* layer = LobbyLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LobbyLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    
    // play background music
    SOUND().playBackgroundMusic();

    mIsClaimingHourlyBonus = false;
    mIsJustGotDailyBonus = false;
    mAvatarMenuItem = NULL;
    
    addSprites();
    addLevelUpSystem();
    addMenuItems();
    addLabels();
    
    createHeaderSprites();
    addScrollLayer();

    scheduleUpdate();
    schedule(schedule_selector(LobbyLayer::updateHourlyBonusLabel), 1.0f);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(LobbyLayer::
                                                                                     onClaimHourlyBonusSuccess),
                                                                  NOTIFICATION_GOT_CLAIM_HOURLY_BONUS,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(LobbyLayer::
                                                                                     onClaimDailyBonusSuccess),
                                                                  NOTIFICATION_GOT_CLAIM_DAILY_BONUS,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(LobbyLayer::
                                                                                     onInAppPurchaseSuccess),
                                                                  NOTIFICATION_GOT_IAP_SUCCESS,
                                                                  NULL);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(LobbyLayer::
                                                                                     moveChipFinish),
                                                                  NOTIFICATION_BETTED_CHIP_STOP_MOVING,
                                                                  NULL);
    
    // update avatar
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(LobbyLayer::
                                                                                     onUpdateAvatar),
                                                                  NOTIFICATION_GOT_UPDATE_AVATAR,
                                                                  NULL);
    
    // track GA
    NATIVE().sendScreenView(kGAScreenLobby);
    
    return true;
}

void LobbyLayer::onExit()
{
    CCLayer::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
   
    // stop background music
    SOUND().stopBackgroundMusic();
}

void LobbyLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();

    // show daily bonus if have
    if (DAILYBONUS()->getDaysPlay() > 0) {
        DailyBonusPopupView *daily = DailyBonusPopupView::create();
        this->addChild(daily, 1000);
        DAILYBONUS()->setDaysPlay(0);
    }
    
    // show first login popup if have
    if (SERVER().getIsJoinedGameFirstTime()) {
        NotificationObject* object = NotificationObject::create();
        object->setTitle(new string("WELCOME!"));
        CCString* message;
        if (USERINFO()->getIsFBAccount()) {
            message = CCString::createWithFormat("Your First Time! Here is %s chips to play Video Poker Jackpot!",
                                                 CURRENCY_LONG(USERINFO()->getTotalChips()));
        }
        else {
            message = CCString::createWithFormat("Your First Time! Here is %s chips to play Video Poker Jackpot! Login via facebook to get more chips!",
                                                 CURRENCY_LONG(USERINFO()->getTotalChips()));
        }
        
        object->setMessage(new string(message->getCString()));
        object->setButton1Type(kButtonOk);
        object->setButton2Type(kButtonNone);
        object->setNotificationType(kNotificationFirstJoinGame);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_FIRST_JOIN_GAME,
                                                                           object);
    }
}

void LobbyLayer::addSprites()
{
    CCSprite* background = CCSprite::create("bg_ingame.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background);
    
    CCSprite* middleBg = CCSprite::create("bg_header_ingame.png");
    middleBg->setPosition(GPARAMS().LBB_MIDDLE_BG_POSITION);
    this->addChild(middleBg, MIDDLE_ORDER);
    
    CCSprite* footerBg = CCSprite::create("bottom_bg_avatar.png");
    footerBg->setPosition(GPARAMS().LBB_FOOTER_BG_POSITION);
    this->addChild(footerBg);
    
    // add to middle bg
    CCSprite* middleChipBg = CCSprite::create("bg_text_chips.png");
    middleChipBg->setPosition(GPARAMS().LBB_MIDDLE_CHIP_BG_POSITION);
    this->addChild(middleChipBg, MIDDLE_ORDER);
    
    mMiddleChipIcon = CCSprite::create("icon_chip.png");
    mMiddleChipIcon->setPosition(GPARAMS().LBB_MIDDLE_CHIP_ICON_POSITION);
    this->addChild(mMiddleChipIcon, MIDDLE_ORDER);
    
    CCSprite* middleBonusBg = CCSprite::create("bg_text_time_bonus.png");
    middleBonusBg->setPosition(GPARAMS().LBB_MIDDLE_BONUS_BG_POSITION);
    this->addChild(middleBonusBg, MIDDLE_ORDER);
    
    // add footer bg
    CCSprite* footerAvatar = CCSprite::create("avatar_frame.png");
    footerAvatar->setPosition(GPARAMS().LBB_FOOTER_AVATAR_POSITION);
    this->addChild(footerAvatar, FOOTER_ORDER);
}

void LobbyLayer::addLevelUpSystem()
{
    CCString* levelString = CCString::createWithFormat("Level %ld", USERINFO()->getLevel());
    CCLabelTTF* levelLabel = CCLabelTTF::create(levelString->getCString(),
                                                DEFAULT_FONT_NAME,
                                                GPARAMS().CMM_FONT_SIZE_2);
    levelLabel->setPosition(GPARAMS().LBB_FOOTER_LEVEL_LABEL_POSITION);
    levelLabel->setAnchorPoint(ccp(0, 0.5f));
    this->addChild(levelLabel);
    
    CCSprite* levelBarBg = CCSprite::create("level_bar_nornal.png");
    levelBarBg->setPosition(GPARAMS().LBB_FOOTER_LEVEL_BAR_POSITION);
    this->addChild(levelBarBg);
    
    CCProgressTimer* levelProgress = CCProgressTimer::create(CCSprite::create("level_bar_active.png"));
    levelProgress->setType(kCCProgressTimerTypeBar);
    levelProgress->setMidpoint(ccp(0,0.5));
    levelProgress->setBarChangeRate(ccp(1, 0));
    levelProgress->setPosition(GPARAMS().LBB_FOOTER_LEVEL_BAR_POSITION);
    addChild(levelProgress);
    
    float percent = (float)USERINFO()->getExperience();
    percent /= (float)USERINFO()->getExperienceMax();
    percent *= 100;
    levelProgress->setPercentage(percent);
}

void LobbyLayer::addLabels()
{
    mDisplayTotalChips = USERINFO()->getTotalChips();
    mTotalChipsLabel = UpdateableLabelTTF::createWithSource(USERINFO()->getUserInfoTotalChips(),
                                                            DEFAULT_FONT_NAME,
                                                            GPARAMS().CMM_FONT_SIZE_3,
                                                            NUMBER_DISPLAY_UPDATE_RATE);
    mTotalChipsLabel->setAnchorPoint(ccp(0, 0.5f));
    mTotalChipsLabel->setPosition(GPARAMS().LBB_MIDDLE_CHIP_LABEL_POSITION);
    this->addChild(mTotalChipsLabel, FOOTER_ORDER);
    
    // add fullname
    if (GPARAMS().isIpadDevice) {
        mFullnameLabel = CCLabelTTF::create(USERINFO()->getFullName(),
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_2);
        mFullnameLabel->setAnchorPoint(ccp(0, 0.5f));
        mFullnameLabel->setPosition(GPARAMS().LBB_FOOTER_FULLNAME_POSITION);
        this->addChild(mFullnameLabel, FOOTER_ORDER);
    }
}

void LobbyLayer::addMenuItems()
{
    CCMenu* menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu, MENU_ORDER);

    // add user avatar menu item
    mAvatarMenuItem = AvatarMenuItem::create(USERINFO()->getProfileID(),
                                             USERINFO()->getUserAvatarType(),
                                             GPARAMS().CMM_ICON_LOBBY_SIZE,
                                             GPARAMS().LBB_FOOTER_AVATAR_POSITION);
    menu->addChild(mAvatarMenuItem);
    mAvatarMenuItem->setDelegate(this);

    CCMenuItemImage* buyChipMenuItem = CCMenuItemImage::create("add_chips_normal.png",
                                                               "add_chips_active.png",
                                                               this,
                                                               menu_selector(LobbyLayer::
                                                                             addChipsMenuItemCallback));
    buyChipMenuItem->setPosition(GPARAMS().LBB_MIDDLE_CHIP_BUTTON_POSITION);
    menu->addChild(buyChipMenuItem);
    
    CCMenuItemImage* bonusMenuItem = CCMenuItemImage::create("treasure_normal.png",
                                                             "treasure_active.png",
                                                             this,
                                                             menu_selector(LobbyLayer::
                                                                           bonusChipsMenuItemCallback));
    bonusMenuItem->setPosition(GPARAMS().LBB_MIDDLE_BONUS_BUTTON_POSITION);
    menu->addChild(bonusMenuItem);
    
    // add settings
    CCMenuItemImage* settingsMenuItem = CCMenuItemImage::create("setting_icon_ingame_normal.png",
                                                                "setting_icon_ingame_active.png",
                                                                this,
                                                                menu_selector(LobbyLayer::
                                                                              settingsMenuItemCallback));
    settingsMenuItem->setPosition(GPARAMS().LBB_HEADER_SETTINGS_BUTTON_POSITION);
    menu->addChild(settingsMenuItem);
    
    CCMenuItem *leaderBoardMenuItem;
    leaderBoardMenuItem = CCMenuItemImage::create("leaderboard/icon_normal.png", 
                                                  "leaderboard/icon_normal.png",
                                                  this,
                                                  menu_selector(LobbyLayer::leaderBoardMenuItemCallback));
    leaderBoardMenuItem->setPosition(GPARAMS().LBB_HEADER_LEADERBOARD_BUTTON_POSITION);
    menu->addChild(leaderBoardMenuItem);
    // add bonus menu item label
    HOURLYBONUS()->updateCurrentBonus();
    mBonusChipsLabel = CCLabelTTF::create(CURRENCY_LONG(HOURLYBONUS()->getCurrentBonus()),
                                          DEFAULT_FONT_NAME,
                                          GPARAMS().CMM_FONT_SIZE_3);
    
    mBonusChipsMenuLabel = CCMenuItemLabel::create(mBonusChipsLabel,
                                                   this,
                                                   menu_selector(LobbyLayer::
                                                                 bonusChipsMenuItemCallback));
    mBonusChipsMenuLabel->setAnchorPoint(ccp(0, 0.5f));
    mBonusChipsMenuLabel->setPosition(GPARAMS().LBB_MIDDLE_BONUS_LABEL_POSITION);
    menu->addChild(mBonusChipsMenuLabel);
}

#pragma mark - update labels

void LobbyLayer::update(float dt)
{
    // update daily bonus if have
    if (mIsJustGotDailyBonus) {
        mIsJustGotDailyBonus = false;
        USERINFO()->getUserInfoTotalChips()->isChanged() = true;

        SOUND().playSound(SOUND_COLLECT_CHIPS);
    }

}

void LobbyLayer::updateHourlyBonusLabel(float dt)
{
    // create hourly bonus effect
    if (HOURLYBONUS()->getLastClaimed() > 0) {
        createClaimHourlyBonusEffect();
        HOURLYBONUS()->setLastClaimed(0);
    }
    
    if (mIsClaimingHourlyBonus) {
        return;
    }
    
    // update current bonus
    HOURLYBONUS()->updateCurrentBonus();
    
    if (HOURLYBONUS()->getCurrentBonus() < HOURLYBONUS()->getBonusMax()) {
        mBonusChipsLabel->setColor(ccWHITE);
        mBonusChipsLabel->setString(CURRENCY_LONG(HOURLYBONUS()->getCurrentBonus()));
    }
    // animation
    else {
        mBonusChipsLabel->setColor(ccRED);
        mBonusChipsLabel->stopAllActions();
    }
}

void LobbyLayer::onClaimHourlyBonusSuccess(CCObject *object)
{
    mIsClaimingHourlyBonus = false;
}

void LobbyLayer::onClaimDailyBonusSuccess(CCObject *object)
{
    mIsJustGotDailyBonus = true;
}

void LobbyLayer::onInAppPurchaseSuccess(CCObject *object)
{
    USERINFO()->getUserInfoTotalChips()->isChanged() = true;
}

void LobbyLayer::onUpdateAvatar(CCObject *object)
{
    if (mAvatarMenuItem != NULL) {
        CCMenu* menu = (CCMenu*)mAvatarMenuItem->getParent();
        mAvatarMenuItem->removeFromParentAndCleanup(true);
        
        // add user avatar menu item
        mAvatarMenuItem = AvatarMenuItem::create(USERINFO()->getProfileID(),
                                                 USERINFO()->getUserAvatarType(),
                                                 GPARAMS().CMM_ICON_LOBBY_SIZE,
                                                 GPARAMS().LBB_FOOTER_AVATAR_POSITION);
        menu->addChild(mAvatarMenuItem);
        mAvatarMenuItem->setDelegate(this);
    }
}

#pragma mark - add to scroll view

void LobbyLayer::createHeaderSprites()
{
    int numberOfItems = NUMBER_OF_GAMES;
    int numberOfMenuItemsOnPage = GPARAMS().LBB_NUMBER_OF_MENU_ITEM_ON_SELECT_GAME;
    int numberOfPages = (int)ceilf((float)numberOfItems /
                                   (float)numberOfMenuItemsOnPage);
    
    mHeaderSprites = vector<CCSprite*>(numberOfPages);
    for(int i = 0; i < numberOfPages; i++) {
        CCSprite* headerSprite =
        CCSprite::create(CCString::createWithFormat("header_0%d.png", i + 1)->getCString());
        headerSprite->setAnchorPoint(ccp(0, 1.0f));
        headerSprite->setPosition(VisibleRect::leftTop());
        mHeaderSprites[i] = headerSprite;
        this->addChild(mHeaderSprites[i], 30 - i);
        if (i) {
            headerSprite->setOpacity(0);
        }
    }
}

void LobbyLayer::addScrollLayer()
{
    int numberOfMenuItemsOnPage = GPARAMS().LBB_NUMBER_OF_MENU_ITEM_ON_SELECT_GAME;
    int numberOfPages = (int)ceilf((float)NUMBER_OF_GAMES /
                                   (float)numberOfMenuItemsOnPage);
    
    // init page
    CCArray* scrollViewLayers = CCArray::createWithCapacity(NUMBER_OF_GAMES);
    for(int i = 0 ; i < numberOfPages ; i++) {
        scrollViewLayers->insertObject(CCLayer::create(), i);
    }
    
    CCMenu *menuOnLayer;
    
    for(int i = 0; i < NUMBER_OF_GAMES; i++) {
        int currentItemIndex = i % numberOfMenuItemsOnPage;
        int currentPage = i / numberOfMenuItemsOnPage;
        
        CCLayer *currentLayer = static_cast<CCLayer*>(scrollViewLayers->objectAtIndex(currentPage));
        if (currentItemIndex == 0) {
            menuOnLayer = CCMenu::create();
            menuOnLayer->setPosition(CCPointZero);
            currentLayer->addChild(menuOnLayer);
        }
        
        // create menu item
        SelectGameMenuItem *gameMenuItem;
        gameMenuItem = SelectGameMenuItem::createWithIndex(i,
                                                           this,
                                                           menu_selector(LobbyLayer::selectGameMenuItemCallback));
        
        gameMenuItem->setPosition(GPARAMS().LBB_GAME_LIST_POSITION[currentItemIndex]);
        // add to menuOnLayer
        menuOnLayer->addChild(gameMenuItem);
    }
    
    CCScrollLayer* scrollLayer;
    scrollLayer = CCScrollLayer::createWithLayers(scrollViewLayers,
                                                  0,
                                                  GPARAMS().LBB_SELECT_GAME_SCROLL_VIEW_BOUNDING_BOX);
    scrollLayer->setPagesIndicatorPosition(GPARAMS().LBB_PAGE_INDICATOR_ON_SELECT_GAME_POSITION);
    scrollLayer->setDelegate(this);
    
    int minimumTouchLengthToChangePage = VisibleRect::center().x * 1/4;
    scrollLayer->setMinimumTouchLengthToChangePage(minimumTouchLengthToChangePage);
    
    this->addChild(scrollLayer);
}

void LobbyLayer::scrollLayerScrolledToPageNumber(CCScrollLayer *sender,
                                                 unsigned int page)
{
    int currentScreen = page;
    int beforeScreen = sender->getBeforeScreen();
    if(currentScreen == beforeScreen) {
        return;
    }
    
    mHeaderSprites[beforeScreen]->runAction(CCFadeOut::create(BOUNCE_DURATION));
    mHeaderSprites[currentScreen]->runAction(CCFadeIn::create(BOUNCE_DURATION));
}

#pragma mark - Menu items callbacks

void LobbyLayer::selectGameMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    SelectGameMenuItem* menuItemSelected = static_cast<SelectGameMenuItem*>(pSender);
    
    // get room info
    vector<RoomInfo *>* rooms = SERVER().getRoomInfos();
    RoomInfo* roomInfo = rooms->at(menuItemSelected->getTag());
    SERVER().setCurrentRoomInfo(roomInfo);
    
    // join this room
    SERVER().joinRoom(*roomInfo->getRoomName());
    SERVER().setJoiningStatus(kJoiningGameRoom);

    // show loading scene
    SCONTROL().showLoadingRoomScene();
}

void LobbyLayer::addChipsMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    ShoppingPopupView *shoppingPopup = ShoppingPopupView::create();
    getParent()->addChild(shoppingPopup, 100);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventBuyChips);
}

void LobbyLayer::bonusChipsMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    if (SERVER().sendClaimHourlyBonus(HOURLYBONUS()->getCurrentBonus()) && !mIsClaimingHourlyBonus) {
        mIsClaimingHourlyBonus = true;
    }
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventHourlyBonus);
}

void LobbyLayer::selectAvatarCallback(const char* memeberID)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    CCLayer* profilePopup = ProfilePopupView::create();
    this->addChild(profilePopup, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventProfile);
}

void LobbyLayer::settingsMenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);
    
    PopUpLayer* settingPopup = SettingPopupView::create();
    this->getParent()->addChild(settingPopup, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventLobbySettings);
}

void LobbyLayer::leaderBoardMenuItemCallback(CCObject *pSender)
{
    LeaderboardPopupView* popup = LeaderboardPopupView::create();
    this->addChild(popup, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventLeaderboard);
}

#pragma mark - animation

void LobbyLayer::createClaimHourlyBonusEffect()
{
    USERINFO()->getUserInfoTotalChips()->isChanged() = true;
    float delayTime = 0;
    int numberChips = HOURLYBONUS()->getLastClaimed() / NUMBER_CHIPS_PER_ICON + 1;
    SOUND().playSound(SOUND_COLLECT_CHIPS);
    
    for (int i = 0; i < numberChips; i++) {
        // create chip view
        int chipType = arc4random() % 3;
        ChipView* chipView = ChipView::create(Chip::create(chipType, 0));
        this->addChild(chipView, FOOTER_ORDER);
        chipView->moveToPosition(GPARAMS().LBB_MIDDLE_BONUS_LABEL_POSITION,
                                 GPARAMS().LBB_MIDDLE_CHIP_ICON_POSITION,
                                 delayTime);
        delayTime += DELAY_MOVE_BONUS_CHIP_DURATION;
    }
    
    // show ads
    ChartBoostHelper::sharedHelper()->showBonusInterstitial();
}

void LobbyLayer::moveChipFinish(CCObject* pSender)
{
    CCNode* node = (CCNode*)pSender;
    node->removeFromParent();
    
    // scale this chip icon
    mMiddleChipIcon->stopAllActions();
    CCScaleTo* scaleOut = CCScaleTo::create(0.1f, 1.2f);
    CCScaleTo* scaleIn = CCScaleTo::create(0.1f, 1.0f);
    CCSequence* sequence = CCSequence::create(scaleOut, scaleIn, NULL);
    mMiddleChipIcon->runAction(sequence);
}

