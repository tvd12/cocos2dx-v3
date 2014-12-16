//
//  LoadingScene.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/8/14.
//
//

#include "LoadingScene.h"
#include "VisibleRect.h"
#include "GameParams.h"
#include "TdgServer.h"
#include "UserInfo.h"
#include "SceneController.h"


CCScene* LoadingLayer::createScene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoadingLayer* layer = LoadingLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LoadingLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }

    addSprites();
    
    scheduleUpdate();
    
    return true;
}

void LoadingLayer::update(float dt)
{
    float percent = mLoadingProgress->getPercentage();
    int frequence = 3;
    if (percent > 60) {
        frequence = 2;
    }
    
    percent += arc4random() % frequence;
    mLoadingProgress->setPercentage(percent);
    
    if (SERVER().getJoiningStatus() == kJoinedGameRoom) {
        unscheduleUpdate();
        SCONTROL().showGameScene(SCENE_CHANGE_DELAY * 3);
    }
    else if (SERVER().getJoiningStatus() == kJoinedLobbyRoom) {
        unscheduleUpdate();
        SCONTROL().showLobbyScene(SCENE_CHANGE_DELAY * 3);
    }
    else if (SERVER().getJoiningStatus() == kJoinGameRoomFailed) {
        unscheduleUpdate();
        SCONTROL().showLobbyScene();
    }
    else if (SERVER().getJoiningStatus() == kJoinLobbyRoomFailed) {
        unscheduleUpdate();
        SCONTROL().showGameScene();
    }
}

void LoadingLayer::addSprites()
{
    CCSprite* background = CCSprite::create("splash.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background);
    
    CCSprite* loadingBg = CCSprite::create("level_bar_nornal.png");
    loadingBg->setPosition(GPARAMS().LOADING_PROGRESS_BAR_POSITION);
    this->addChild(loadingBg);
    
    mLoadingProgress = CCProgressTimer::create(CCSprite::create("level_bar_active.png"));
    mLoadingProgress->setType(kCCProgressTimerTypeBar);
    mLoadingProgress->setMidpoint(ccp(0,0.5));
    mLoadingProgress->setBarChangeRate(ccp(1, 0));
    mLoadingProgress->setPosition(GPARAMS().LOADING_PROGRESS_BAR_POSITION);
    mLoadingProgress->setPercentage(0);
    addChild(mLoadingProgress);
}
