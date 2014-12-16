//
//  GameViewHeader.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#include "GameViewHeader.h"
#include "GameModel.h"

#include "GameParams.h"
#include "TextUtils.h"
#include "SoundManager.h"
#include "NativeHelper.h"

#include "UserInfo.h"
#include "RoomInfo.h"
#include "PopUpLayer.h"
#include "SettingPopupView.h"
#include "NotificationObject.h"

#include "SceneController.h"
#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "UpdateableLabelTTF.h"


GameViewHeader* GameViewHeader::create(GameModel* gameModel)
{
    GameViewHeader *pRet = new GameViewHeader();
    pRet->init(gameModel);
    pRet->autorelease();
    return pRet;
}

bool GameViewHeader::init(GameModel* gameModel)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setUserInfo(gameModel->getUserInfo());
    setRoomInfo(gameModel->getRoomInfo());

    addSprites();
    addLabels();
    addMenuItems();
    addLevelProgress();
    
    scheduleUpdate();
    
    mJackpotDisplay = mRoomInfo->getJackpot();
    
    mIsUpdatingJackpot = false;
    mIsUpdateLevel = false;
    mIsUpdateLevelExperience = false;

    mCurrentUserExperience = mUserInfo->getExperience();
    mCurrentUserLevel = mUserInfo->getLevel();
    
    return true;
}

void GameViewHeader::prepareNewGame()
{
    mIsOnGame = false;
}

void GameViewHeader::update(float dt)
{
    updateLabels();
}

void GameViewHeader::addLabels()
{
    // jackpot value
    mJackpotLabel = UpdateableLabelTTF::createWithSource(mRoomInfo->getRoomInfoJackpot(),
                                               DEFAULT_FONT_NAME,
                                               GPARAMS().CMM_FONT_SIZE_3,
                                               JACKPOT_DISPLAY_UPDATE_RATE);
    mJackpotLabel->setAnchorPoint(ccp(0, 0.5f));
    mJackpotLabel->setPosition(GPARAMS().MAIN_JACKPOT_VALUE_LABEL_POSITION);
    this->addChild(mJackpotLabel);
    
    //level
    CCString *levelString = CCString::createWithFormat("Level %ld", mUserInfo->getLevel());
    mLevelLabel = CCLabelTTF::create(levelString->getCString(),
                                     DEFAULT_FONT_NAME,
                                     GPARAMS().CMM_FONT_SIZE_2);
    mLevelLabel->setPosition(GPARAMS().MAIN_LEVEL_LABEL_POSITION);
    this->addChild(mLevelLabel);
    
    //jackpot name
    mJackpotHandLabel = CCLabelTTF::create(mRoomInfo->getJackpotName()->c_str(),
                                           DEFAULT_FONT_NAME,
                                           GPARAMS().CMM_FONT_SIZE_3);
    mJackpotHandLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mJackpotHandLabel->setPosition(GPARAMS().MAIN_HAND_OF_JACKPOT_LABEL_POSTION);
    this->addChild(mJackpotHandLabel);
}

void GameViewHeader::addSprites()
{
    CCSprite *bgHeader = CCSprite::create("header_ingame.png");
    bgHeader->setPosition(GPARAMS().MAIN_HEADER_BG_POSITION);
    addChild(bgHeader);
    
    CCSprite *bgHeaderLevel = CCSprite::create("level.png");
    bgHeaderLevel->setPosition(GPARAMS().MAIN_HEADER_LEVEL_POSITION);
    addChild(bgHeaderLevel);
    
    CCSprite *bgHeaderBoard = CCSprite::create("table_title.png");
    bgHeaderBoard->setPosition(GPARAMS().MAIN_HEADER_BOARD_POSITION);
    addChild(bgHeaderBoard);
    
    mJackpotStringSprite = CCSprite::create("text_jackpot.png");
    mJackpotStringSprite->setAnchorPoint(CCPoint(0, 0.5f));
    mJackpotStringSprite->setPosition(GPARAMS().MAIN_JACKPOT_STRING_LABEL_POSITION);
    this->addChild(mJackpotStringSprite);
}

void GameViewHeader::addMenuItems()
{
    CCMenu *menu = CCMenu::create();
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    // exit item
    CCMenuItemImage* exitItem;
    exitItem = CCMenuItemImage::create("exit_normal.png",
                                       "exit_active.png",
                                       this,
                                       menu_selector(GameViewHeader::onExitItemCallback));
    exitItem->setPosition(GPARAMS().MAIN_EXIT_BUTTON_POSITION);
    menu->addChild(exitItem);
    
    // settings item
    CCMenuItemImage* settingsItem;
    settingsItem = CCMenuItemImage::create("setting_normal.png",
                                           "setting_active.png",
                                           this,
                                           menu_selector(GameViewHeader::onSettingsItemCallback));
    settingsItem->setPosition(GPARAMS().MAIN_SETTINGS_BUTTON_POSITION);
    menu->addChild(settingsItem);
}

void GameViewHeader::addLevelProgress()
{
    mLevelNormalSprite = CCSprite::create("level_normal.png");
    mLevelNormalSprite->setPosition(GPARAMS().MAIN_LEVEL_LABEL_POSITION);
    this->addChild(mLevelNormalSprite);
    
    mLevelProgress = CCProgressTimer::create(CCSprite::create("level_active.png"));
    mLevelProgress->setPosition(GPARAMS().MAIN_LEVEL_LABEL_POSITION);
    mLevelProgress->setReverseProgress(true);
    mLevelProgress->setType(kCCProgressTimerTypeRadial);
    
    float percentage =
    ((0.574f)*100.0f*mUserInfo->getExperience())/mUserInfo->getExperienceMax() + 21.5f;
    mLevelProgress->setPercentage(percentage);

    this->addChild(mLevelProgress);
}

void GameViewHeader::updateLabels()
{
    if(mIsUpdatingJackpot) {
        updateJackpotLabel(mJackpotDisplay,
                           mRoomInfo->getJackpot(),
                           mJackpotLabel,
                           mIsUpdatingJackpot);
    }
    if(mIsUpdateLevel) {
        updateLevelNumber();
    }
    if (mIsUpdateLevelExperience) {
        updateLevelExperienceProgress();
    }
}

void GameViewHeader::updateJackpot()
{
    mIsUpdatingJackpot = true;
}

void GameViewHeader::updateLevel()
{
    mIsUpdateLevel = true;
}

void GameViewHeader::updateLevelExperience()
{
    mIsUpdateLevelExperience = true;
}

void GameViewHeader::updateLevelNumber()
{
    if(mUserInfo->getLevel() > mCurrentUserLevel) {
        CCString *levelString = CCString::createWithFormat("Level %ld", mUserInfo->getLevel());
        mLevelLabel->setString(levelString->getCString());
        mCurrentUserLevel = mUserInfo->getLevel();
        
        // update experience max
        mUserInfo->setExperienceMax(SERVER().getLevelMaxs()->at(mUserInfo->getLevel() - 1));
        
        // show level up popup
    }
    
    mIsUpdateLevel = false;
}

void GameViewHeader::updateLevelExperienceProgress()
{
    // update percentage
    mLevelProgress->stopAllActions();
    float percentage =
    ((0.574f)*100.0f*mUserInfo->getExperience()) / mUserInfo->getExperienceMax() + 21.5f;
    CCProgressFromTo *progressAction = CCProgressFromTo::create(0.15f,
                                                                mLevelProgress->getPercentage(),
                                                                percentage);
    mLevelProgress->runAction(progressAction);

    mIsUpdateLevelExperience = false;
}

void GameViewHeader::updateJackpotLabel(long long& displayValue,
                                        long long value,
                                        CCLabelTTF* chipsLabel,
                                        bool& isUpdatingJackpot)
{
}

#pragma mark - menu item callbacks

void GameViewHeader::onExitItemCallback(CCNode *sender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);
    
    if (!mIsOnGame) {
        button1DidPressed(NULL);
    }
    else {
        NotificationObject* object = NotificationObject::create();
        object->setTitle(new string("Exit game"));
        object->setMessage(new string("Your bet chips will be lost. Do you want to quit?"));
        object->setButton1Type(kButtonOk);
        object->setButton2Type(kButtonCancel);
        object->setNotificationType(kNotificationConfirmQuitGame);
        object->retain();
        
        NotificationPopupView* view = NotificationPopupView::create(object);
        view->setDelegate(this);
        this->getParent()->addChild(view, NOTIFICATION_POPUP_ORDER);
    }
}

void GameViewHeader::onSettingsItemCallback(CCNode *sender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);
    
    PopUpLayer* settingPopup = SettingPopupView::create();
    this->getParent()->addChild(settingPopup, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventOnGameSettings);
}

#pragma mark - confirm delegate
// ok -> quit game
void GameViewHeader::button1DidPressed(NotificationPopupView* sender)
{
    // back to lobby
    SERVER().joinRoom(GAME_LOBBY_NAME);
    SERVER().setJoiningStatus(kJoiningLobbyRoom);
    
    // show loading scene
    SCONTROL().showLoadingRoomScene();
}
// cancel -> do nothing
void GameViewHeader::button2DidPressed(NotificationPopupView* sender)
{
    
}


