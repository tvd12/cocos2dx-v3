//
//  SceneController.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/31/14.
//
//

#include "SceneController.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "LoadingScene.h"
#include "GameScene.h"

#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "TdgServerConfig.h"

#include "NotificationObject.h"
#include "VipUpgradePopupView.h"

#include "GameParams.h"
#include "VipInfo.h"
#include "UserInfo.h"
#include "NativeHelper.h"
#include "GameViewDefine.h"


SceneController::SceneController()
{
    mDirector = CCDirector::sharedDirector();

    // init scene controller
    mCurrentScene = LoginLayer::createScene();
    mDirector->runWithScene(mCurrentScene);
    
    // message popup notifications
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onGotLostServerConnectionReceive),
                                                                  NOTIFICATION_GOT_LOST_SERVER_CONNECTION,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onCheckingInternetFailedReceive),
                                                                  NOTIFICATION_GOT_CHECKING_INTERNET_FAILED,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onConnectFailedToServerReceive),
                                                                  NOTIFICATION_GOT_CONNECT_FAILED_TO_SERVER,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onMustUpgradeNewestVersion),
                                                                  NOTIFICATION_GOT_MUST_UPDATE_NEWEST_VERSION,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onPurchaseFailedReceive),
                                                                  NOTIFICATION_GOT_IAP_FAILED,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onPurchaseSuccessReceive),
                                                                  NOTIFICATION_GOT_IAP_SUCCESS,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onCannotInviteFriend),
                                                                  NOTIFICATION_CANNOT_INVITE_FRIEND,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onGotFirstJoinGame),
                                                                  NOTIFICATION_GOT_FIRST_JOIN_GAME,
                                                                  NULL);
    
    // popup view notifications
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onVipUpgradeReceive),
                                                                  NOTIFICATION_GOT_VIP_UPGRADE,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onLevelUpReceive),
                                                                  NOTIFICATION_GOT_LEVEL_UP,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onJackpotReceive),
                                                                  NOTIFICATION_GOT_JACKPOT,
                                                                  NULL);

    // others
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SceneController::
                                                                                     onLogoutReceive),
                                                                  NOTIFICATION_GOT_LOGOUT,
                                                                  NULL);
}

void SceneController::showLoginScene(float delayTime)
{
    mCurrentSceneId = kSceneLogin;
    mLastSceneId = kSceneLogin;
    
    // update server status
    SERVER().setLoginType(kUserLogOut);
    
    // reset in-app purchase
//    INAPP().reset();
    
    // update user status
//    USER_INFO()->setPlayerType(kDPPlayerTypeZombie);
    
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showLoginScene),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                delayTime,
                                                false);
}

void SceneController::showLobbyScene(float delayTime)
{
    mCurrentSceneId = kSceneLobby;
    mLastSceneId = kSceneLogin;
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showLobbyScene),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                delayTime,
                                                false);
}

void SceneController::showGameScene(float delayTime)
{
    mCurrentSceneId = kScenePokerGame;
    mLastSceneId = kSceneLobby;
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showGameScene),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                delayTime,
                                                false);
}

void SceneController::showLoadingRoomScene(float delayTime)
{
    mCurrentSceneId = kSceneLoadingTable;
    mLastSceneId = kSceneLobby;
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showLoadingRoomScene),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                delayTime,
                                                false);
}

void SceneController::backToLastScene(float delayTime)
{
    switch (mLastSceneId) {
        case kSceneLogin:
            SCONTROL().showLoginScene(delayTime);
            break;
            
        case kSceneLobby:
            SCONTROL().showLoginScene(delayTime);
            break;
            
        default:
            SCONTROL().showLoginScene(delayTime);
            break;
    }
}

#pragma mark - change scene here

void SceneController::_showLoginScene()
{
    mCurrentScene = LoginLayer::createScene();
    mDirector->replaceScene(mCurrentScene);
}

void SceneController::_showLobbyScene()
{
    mCurrentScene = LobbyLayer::createScene();
    mDirector->replaceScene(mCurrentScene);
}

void SceneController::_showGameScene()
{
    mCurrentScene = GameScene::create();
    mDirector->replaceScene(mCurrentScene);
}

void SceneController::_showLoadingRoomScene()
{
    mCurrentScene = LoadingLayer::createScene();
    mDirector->replaceScene(mCurrentScene);
}

#pragma mark - Notification center

void SceneController::_showNotificationPopup()
{
    NotificationPopupView* view = NotificationPopupView::create(mNotificationObject);
    view->setDelegate(this);
    mCurrentScene->addChild(view, NOTIFICATION_POPUP_ORDER);
}

void SceneController::button1DidPressed(NotificationPopupView* sender)
{
    switch (sender->getTag()) {
        case kNotificationDisconnected:
        case kNotificationConnectionLost:
            SCONTROL().showLoginScene();
            break;
            
        case kNotificationCheckingInternetFailed:
            SERVER_CONFIG().updateConfigFromServer();
            break;
            
        case kNotificationConnectFailedToServer:
            SCONTROL().showLoginScene();
            break;
            
        case kNotificationMustUpdateNewestVersion:
            SCONTROL().showLoginScene();
            NATIVE().openUpdateUrl();
            break;
            
        default:
            break;
    }
}

void SceneController::button2DidPressed(NotificationPopupView* sender)
{
    
}

#pragma mark - Got Notification Popup

void SceneController::onLogoutReceive(CCObject *object)
{
    SCONTROL().showLoginScene();
}

void SceneController::onGotLostServerConnectionReceive(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onCheckingInternetFailedReceive(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onMustUpgradeNewestVersion(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onConnectFailedToServerReceive(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onPurchaseFailedReceive(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onCannotInviteFriend(CCObject *object)
{
    showNotificationPopup(object);
}


void SceneController::onPurchaseSuccessReceive(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::onGotFirstJoinGame(CCObject *object)
{
    showNotificationPopup(object);
}

void SceneController::showNotificationPopup(CCObject *object)
{
    // get notification object
    mNotificationObject = (NotificationObject*)object;
    mNotificationObject->retain();
    
    // show this notification
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showNotificationPopup),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                SCENE_CHANGE_DELAY,
                                                false);
}

#pragma mark - Got Popup View

void SceneController::onVipUpgradeReceive(CCObject *object)
{
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showVipUpgradePopup),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                SCENE_CHANGE_DELAY,
                                                false);
}

void SceneController::onLevelUpReceive(CCObject *object)
{
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showLevelUpPopup),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                SCENE_CHANGE_DELAY,
                                                false);
}

void SceneController::onJackpotReceive(CCObject *object)
{
    mDirector->getScheduler()->scheduleSelector(schedule_selector(SceneController::_showJackpotPopup),
                                                SceneController::getSingletonPtr(),
                                                SCENE_INTERVAL,
                                                0,
                                                SCENE_CHANGE_DELAY,
                                                false);
}

void SceneController::_showVipUpgradePopup()
{
    // bonus string
    long upgradeBonus = VIPINFOLIST()->at(USERINFO()->getVipType())->getUpgradeBonus();
    CCString* bonusString = CCString::createWithFormat("%s chips", CURRENCY_LONG(upgradeBonus));
    
    // multiplies string
    const char* multiplyText = VIPINFOLIST()->at(USERINFO()->getVipType())->getMultiplyText();
    CCString* multiplyString = CCString::createWithFormat("%s In-App Purchase", multiplyText);

    VipUpgradePopupView *vipUpgrade = VipUpgradePopupView::create(string(bonusString->getCString()),
                                                                  string(multiplyString->getCString()),
                                                                  USERINFO()->getVipType());
    mDirector->getRunningScene()->addChild(vipUpgrade, 1000);
}

void SceneController::_showLevelUpPopup()
{
    
}

void SceneController::_showJackpotPopup()
{
    
}

