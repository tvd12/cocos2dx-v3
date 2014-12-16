//
//  GameController.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#include "GameController.h"
#include "GameControllerDefine.h"

#include "GameView.h"
#include "GameViewDefine.h"
#include "GameModel.h"

#include "UserInfo.h"
#include "Deck.h"

//#include "ServerSimulate.h"

#include "TdgServerDefine.h"
#include "TdgServer.h"
#include "TdgDealCardData.h"
#include "TdgDrawCardData.h"
#include "TdgDonCardData.h"

#include "GameParams.h"
#include "SoundManager.h"
#include "NativeHelper.h"


GameController::~GameController()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameController* GameController::createWithModelAndView(GameModel *gameModel,
                                                       GameView *gameView)
{
    GameController *gameController = new GameController(gameModel, gameView);
    gameController->autorelease();
    return gameController;
}

GameController::GameController(GameModel *gameModel, GameView *gameView)
{
    mGameModel = gameModel;
    mGameView = gameView;
    
    mGamePlayState = tdgGamePlayStateBetting;
    
    // init to notification center
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onDealCardsReceived),
                                                                  NOTIFICATION_GOT_DEAL_CARDS,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onDrawCardsReceived),
                                                                  NOTIFICATION_GOT_DRAW_CARDS,
                                                                  NULL);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onDonDealerCardReceived),
                                                                  NOTIFICATION_GOT_DON_DEALER_CARD,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onDonCardsReceived),
                                                                  NOTIFICATION_GOT_DON_CARDS,
                                                                  NULL);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onMainGameFinish),
                                                                  NOTIFICATION_MAIN_GAME_FINISH,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onDonGameFinish),
                                                                  NOTIFICATION_DON_GAME_FINISH,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onJackpotUpdate),
                                                                  NOTIFICATION_GOT_JACKPOT_UPDATE,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onLevelUpdate),
                                                                  NOTIFICATION_GOT_LEVEL_UPDATE,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameController::
                                                                                     onLevelExperienceUpdate),
                                                                  NOTIFICATION_GOT_LEVEL_EX_UPDATE,
                                                                  NULL);
}

#pragma mark - server notify cards to game controller

void GameController::onDealCardsReceived(CCObject *object)
{
    CCLOG("Got deal cards");
    // udpate game play state
    mGamePlayState = tdgGamePlayStateDealing;
    
    TdgDealCardData* dealCardData = (TdgDealCardData*)object;
    mGameModel->updateDealCards(dealCardData->getDealCards()->data(),
                                dealCardData->getHintBits());
    mGameView->updateGameViewState(tdgGameViewUpdateGotDealCards);
}

void GameController::onDrawCardsReceived(CCObject *object)
{
    CCLOG("Got draw cards");
    // udpate game play state
    mGamePlayState = tdgGamePlayStateDrawing;
    
    TdgDrawCardData* drawCardData = (TdgDrawCardData*)object;
    mGameModel->updateDrawCards(drawCardData->getDrawCards()->data(),
                                drawCardData->getWonBit(),
                                drawCardData->getWonHandType(),
                                drawCardData->getWonValue(),
                                drawCardData->getIsGotJackpot());
    mGameView->updateGameViewState(tdgGameViewUpdateGotDrawCards);
}

void GameController::onDonDealerCardReceived(CCObject *object)
{
    CCLOG("Got don dealer card");
    
    // udpate game play state
    mGamePlayState = tdgGamePlayStateDonDealing;
    
    TdgDonCardData* donCardData = (TdgDonCardData*)object;
    mGameModel->updateDonDealerCard(donCardData->getDonCards()->at(0));
    mGameView->updateGameViewState(tdgGameViewUpdateGotDonDealerCard);
}

void GameController::onDonCardsReceived(CCObject *object)
{
    CCLOG("Got don cards");

    TdgDonCardData* donCardData = (TdgDonCardData*)object;
    mGameModel->updateDonCards(donCardData->getDonCards()->data(),
                               donCardData->getWonChips());
    mGameView->updateGameViewState(tdgGameViewUpdateGotDonCards);
}

// server notify room variables update to game controller
void GameController::onJackpotUpdate(CCObject *object)
{
    mGameView->updateGameViewState(tdgGameViewUpdateJackpot);
}

void GameController::onNumberOnlinePlayersUpdate(CCObject *object)
{
    
}

void GameController::onLevelUpdate(CCObject *object)
{
    mGameModel->checkLevelUp();
    mGameView->updateGameViewState(tdgGameViewUpdateLevel);
}

void GameController::onLevelExperienceUpdate(CCObject *object)
{
    mGameView->updateGameViewState(tdgGameViewUpdateLevelExperience);
}

#pragma mark - Notification center

void GameController::onMainGameFinish(CCObject *object)
{
    // prepare for main game finish
    mGameView->updateGameViewState(tdgGameViewUpdateMainGameFinish);
    
    // player lose
    if (mGameModel->getUserInfo()->getTotalWonChips() <= 0) {
        // prepare for a new game
        prepareForANewGame();
    }
    // player won
    else {
        // remove highlight cell
        mGameView->updateGameViewState(tdgGameViewUpdateRemoveHighlightPayout);
        
        // disable DON
        if (!GPARAMS().isDonEnabled) {
            onDonNoMenuItemCallback(NULL);
        }
        // enable DON
        else {
            // show DON game
            mGameView->updateGameViewState(tdgGameViewUpdatePlayDonGame);
        }
    }
}

void GameController::onDonGameFinish(CCObject *object)
{
    // finish don game
    mGameView->updateGameViewState(tdgGameViewUpdateFinishDonGame);

    // player lose
    if (mGameModel->getUserInfo()->getTotalWonChips() <= 0) {

        // prepare for a new game
        prepareForANewGame();
    }
    
    // player won/push
    else {
        // show DON game
        mGameView->updateGameViewState(tdgGameViewUpdatePlayDonGame);
    }
}

#pragma mark - menu item callbacks

void GameController::onCardSelectMenuItemCallback(CCNode *sender)
{
    CCLOG("Tag = %d", sender->getTag());
    if (mGamePlayState == tdgGamePlayStateDealing) {
        mGameModel->updateDealCardSelected(sender->getTag());
        mGameView->updateGameViewState(tdgGameViewUpdateDealCardSelected);
    }
    else if (mGamePlayState == tdgGamePlayStateDonDealing) {
        if (sender->getTag() > 0) {
            mDonHeldPosition = sender->getTag();
            mGameModel->updateDonCardSelected(sender->getTag());
            mGameView->updateGameViewState(tdgGameViewUpdateSelectDonCard);
        }
    }
}

void GameController::onDealMenuItemCallback(CCNode *sender)
{
    if (mGamePlayState == tdgGamePlayStateBetting) {
//        mServerSimulate->sendDealCardsRequest(mGameModel->getUserInfo()->getTotalBetChips());
        SERVER().sendDealCardsRequest(mGameModel->getUserInfo()->getTotalBetChips());
        
        mGameView->updateGameViewState(tdgGameViewUpdateDealButton);
        
        // track GA
        NATIVE().sendGameEvent(kGAGameEventDeal,
                               mGameModel->getUserInfo()->getTotalBetChips());
    }
    else if (mGamePlayState == tdgGamePlayStateDonDealing) {
//        mServerSimulate->sendDonCardsRequest(mDonHeldPosition);
        SERVER().sendDonCardsRequest(mDonHeldPosition);
        mGamePlayState = tdgGamePlayStateDonFinish;
        mGameView->updateGameViewState(tdgGameViewUpdateDonDealButton);
    }
}

void GameController::onDrawMenuItemCallback(CCNode *sender)
{
//    mServerSimulate->sendDrawCardsRequest(mGameModel->getDeck()->getHeldBit());
    SERVER().sendDrawCardsRequest(mGameModel->getDeck()->getHeldBit());
    mGameView->updateGameViewState(tdgGameViewUpdateDrawButton);
}

void GameController::onDonYesMenuItemCallback(CCNode *sender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    // send to server
    SERVER().sendDonDealerCardRequest(true);
    
    mGamePlayState = tdgGamePlayStateDonStart;
//    mServerSimulate->sendDonDealerCardRequest();

    // track GA
    NATIVE().sendGameEvent(kGAGameEventDonYes);
}

void GameController::onDonNoMenuItemCallback(CCNode *sender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    // send to server
    SERVER().sendDonDealerCardRequest();
    
    // collect won chips
    mGameModel->updateCollectWonChips();
    mGameView->updateGameViewState(tdgGameViewUpdateCollectWonChips);
    
    mGameView->updateGameViewState(tdgGameViewUpdateFinishDonGame);

    // prepare for a new game
    prepareForANewGame();
    
    // track GA
    NATIVE().sendGameEvent(kGAGameEventDonYes);
}

void GameController::onBetChipMenuItemCallBack(CCNode *sender)
{
    // update to model
    if (mGameModel->updateBetChipWithType(sender->getTag())) {
        // update to view
        mGameView->updateGameViewState(tdgGameViewUpdateBetChip);
    }
    else {
        ((CCMenuItem*)sender)->setEnabled(false);
    }
    
    // track GA
    NATIVE().sendGameEvent(kGAGameEventChipTypeSmall + sender->getTag());
}

void GameController::onMaxBetMenuItemCallBack(CCNode *sender)
{
    mGameModel->updateMaxBet();
    mGameView->updateGameViewState(tdgGameViewUpdateBetMaxChip);
    
    // track GA
    NATIVE().sendGameEvent(kGAGameEventMaxBet);
}

void GameController::onCancelBetMenuItemCallBack(CCNode *sender)
{
    mGameModel->updateCancelBetChip();
    mGameView->updateGameViewState(tdgGameViewUpdateCancelBetChip);
    
    // track GA
    NATIVE().sendGameEvent(kGAGameEventCancelBet);
}

void GameController::prepareForANewGame()
{
    mGamePlayState = tdgGamePlayStateBetting;
    mGameModel->updateMainGameFinish();
    mGameView->updateGameViewState(tdgGameViewUpdatePrepareNewGame);
    
    // rebet chips
    if (mGameModel->updateRepeatLastBet()) {
        mGameView->updateGameViewState(tdgGameViewIdle);
        mGameView->updateGameViewState(tdgGameViewIdle);
        mGameView->updateGameViewState(tdgGameViewUpdateRebetChips);
    }
}

