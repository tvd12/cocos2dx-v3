//
//  SceneController.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/31/14.
//
//

#ifndef __DragonVideoPoker__SceneController__
#define __DragonVideoPoker__SceneController__

#include "cocos2d.h"
#include "SingLeton.h"
#include "NotificationPopupView.h"

USING_NS_CC;

#define SCENE_CHANGE_DELAY              0.05f
#define SCENE_INTERVAL                  0.0f

typedef enum SCENE_TYPE {
    kSceneLogin             = 0,
    kSceneLobby             = 1,
    kScenePokerGame         = 2,
    kSceneLoadingTable      = 3,
    kSceneAvatar            = 4,
    kSceneVipClub           = 5,
    
} Scene_Type;

class SceneController : public CCObject, public SingLeton<SceneController>,
public NotificationPopupDelegate
{
public:
	SceneController();
    
    void showLoginScene(float delayTime = SCENE_CHANGE_DELAY);
    void showLobbyScene(float delayTime = SCENE_CHANGE_DELAY);
    void showGameScene(float delayTime = SCENE_CHANGE_DELAY);
    void showLoadingRoomScene(float delayTime = SCENE_CHANGE_DELAY);
    
    void backToLastScene(float delayTime = SCENE_CHANGE_DELAY);
    
    virtual void button1DidPressed(NotificationPopupView* sender);
    virtual void button2DidPressed(NotificationPopupView* sender);

private:

    void showNotificationPopup(CCObject *object);
    void onGotLostServerConnectionReceive(CCObject *object);
    void onLogoutReceive(CCObject *object);
    void onCheckingInternetFailedReceive(CCObject *object);
    void onMustUpgradeNewestVersion(CCObject *object);
    void onConnectFailedToServerReceive(CCObject *object);
    void onPurchaseFailedReceive(CCObject *object);
    void onPurchaseSuccessReceive(CCObject *object);
    void onCannotInviteFriend(CCObject *object);
    
    void onVipUpgradeReceive(CCObject *object);
    void onLevelUpReceive(CCObject *object);
    void onJackpotReceive(CCObject *object);

    void _showLoginScene();
    void _showLobbyScene();
    void _showGameScene();
    void _showLoadingRoomScene();
    void _showNotificationPopup();
    
    void _showVipUpgradePopup();
    void _showLevelUpPopup();
    void _showJackpotPopup();
    
    NotificationObject* mNotificationObject;
    
    CCDirector *mDirector;
    CCScene* mCurrentScene;

    int mCurrentSceneId;
    int mLastSceneId;
};

#define SCONTROL() SceneController::getSingleton()


#endif /* defined(__DragonVideoPoker__SceneController__) */
