//
//  GameScene.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#include "GameScene.h"

#include "GameModel.h"
#include "GameView.h"
#include "GameController.h"
#include "GameViewDefine.h"

//#include "ServerSimulate.h"
#include "NativeHelper.h"
#include "TdgServer.h"
#include "RoomInfo.h"
#include "GameParams.h"


GameScene::GameScene()
{
    // create server simulator
//    ServerSimulate* serverSimulate = new ServerSimulate();
    
    // create game model
    mGameModel = GameModel::create();
    mGameModel->retain();
    
    // create game view
    mGameView = GameView::createWithModel(mGameModel);
    this->addChild(mGameView);
    
    // create game controller
    mGameController = GameController::createWithModelAndView(mGameModel, mGameView);
    mGameController->retain();
//    mGameController->setServerSimulate(serverSimulate);
    mGameView->addMenuItems(mGameController);
    
    // prepare for a new game
    mGameView->updateGameViewState(tdgGameViewUpdatePrepareNewGame);
    
    // track GA
    NATIVE().sendScreenView(ROOMINFO()->getIndex() - 1);
    
    if (GPARAMS().isLeftHand) {
        NATIVE().sendGameEvent(kGAGameEventLeftHand);
    }
    else {
        NATIVE().sendGameEvent(kGAGameEventRightHand);
    }
    
    if (GPARAMS().isDonEnabled) {
        NATIVE().sendGameEvent(kGAGameEventDonEnable);
    }
    else {
        NATIVE().sendGameEvent(kGAGameEventDonDisable);
    }
}

GameScene::~GameScene()
{
    mGameModel->release();
    mGameController->release();
}
