//
//  GameView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#include "GameView.h"
#include "GameModel.h"
#include "GameController.h"

#include "VisibleRect.h"
#include "GameParams.h"
#include "SoundManager.h"

#include "ChipBettedView.h"
#include "PaytableView.h"
#include "DeckView.h"

#include "GameViewFooter.h"
#include "GameViewMiddle.h"
#include "GameViewHeader.h"

#include "TdgServer.h"
#include "RoomInfo.h"
#include "UserInfo.h"

#include "Deck.h"

#include "JackpotPopupView.h"
#include "LevelupPopupView.h"

#include "cocos-ext.h"

GameView::~GameView(void)
{
    mChipBettedView->release();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameView* GameView::createWithModel(GameModel *gameModel)
{
    GameView* gameView = new GameView(gameModel);
    gameView->initWithModel(gameModel);
    gameView->autorelease();
    
    return gameView;
}

GameView::GameView(GameModel *gameModel)
{
}

bool GameView::initWithModel(GameModel* gameModel)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    // save game model
    mGameModel = gameModel;
    
    addBackground();
    addHeaderLayer();
    addMiddleLayer();
    addFooterLayer();
    
    addBetChips();
    addPaytable();
    addDeck();
    
    setGameViewStateToIdle();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameView::
                                                                                     onSwitchHand),
                                                                  NOTIFICATION_SWITCH_HAND,
                                                                  NULL);

    scheduleUpdate();

    return true;
}

void GameView::addBackground()
{
    CCSprite *bg = CCSprite::create("bg.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    CCSprite *bgPaytable = CCSprite::create("bg_pay_table.png");
    bgPaytable->setPosition(GPARAMS().MAIN_PAYTABLE_BG_POSITION);
    addChild(bgPaytable);
}

void GameView::addHeaderLayer()
{
    mGameViewHeader = GameViewHeader::create(mGameModel);
    addChild(mGameViewHeader);
}

void GameView::addMiddleLayer()
{
    mGameViewMiddle = GameViewMiddle::create(mGameModel);
    addChild(mGameViewMiddle);
}

void GameView::addFooterLayer()
{
    mGameViewFooter = GameViewFooter::create(mGameModel);
    this->addChild(mGameViewFooter, ORDER_HELD_SPRITE);
    mGameViewFooter->setUserInfo(mGameModel->getUserInfo());
}

void GameView::addBetChips()
{
    mChipBettedView = ChipBettedView::create(mGameModel->getChipBetted());
    mChipBettedView->retain();
    mChipBettedView->addChipViewsToLayer(this, ORDER_CHIPS);
}

void GameView::addPaytable()
{
    mPaytableView = PaytableView::create(mGameModel->getPaytable());
    this->addChild(mPaytableView, ORDER_PAYTABLE);
}

void GameView::addDeck()
{
    mDeckView = DeckView::getSingletonPtr();
    mDeckView->addDeckToLayer(this, ORDER_CARDS);
}

void GameView::addMenuItems(CCObject *target)
{
    mGameViewMiddle->addMenuItems(target);
    mGameViewFooter->addMenuItems(target);
    
    // update position for chipBettedView
    mChipBettedView->updateChipsPosition(mGameViewFooter->getSmallChipBg()->getPosition(),
                                         mGameViewFooter->getMediumChipBg()->getPosition(),
                                         mGameViewFooter->getBigChipBg()->getPosition());
}

#pragma mark - update game view state

void GameView::update(float dt)
{
    // update game view state
    updateGameViewWithState();
}

void GameView::updateGameViewState(long state)
{
    GameViewState newState;
    newState.state = state;
    newState.isQuickAction = false;
//    if (GPARAMS().getIsGameDidEnterBackground()) {
//        newState.isQuickAction = true;
//    }
//    else {
//        newState.isQuickAction = false;
//    }
    
    mStateQueue.push_back(newState);
}

bool GameView::isGameViewStateIdle()
{
    
}

void GameView::getNextGameViewState()
{
    if (mStateQueue.empty()) {
        mCurrentGameViewState.state = tdgGameViewIdle;
    }
    else {
        mCurrentGameViewState = mStateQueue.front();
        mStateQueue.pop_front();
    }
}

void GameView::setGameViewStateToIdle()
{
    mCurrentGameViewState.state = tdgGameViewIdle;
    mCurrentGameViewState.isQuickAction = false;
}

void GameView::updateGameViewWithState()
{
    if (mCurrentGameViewState.state == tdgGameViewIdle) {
        getNextGameViewState();
        if (mCurrentGameViewState.state == tdgGameViewIdle) {
            return;
        }
    }
    else {
        return;
    }
    
    // process update state here
    switch (mCurrentGameViewState.state) {
        case tdgGameViewUpdatePrepareNewGame:
            processPrepareNewGame();
            break;
            
        case tdgGameViewUpdateBetChip:
            processBetChipState();
            break;
            
        case tdgGameViewUpdateCancelBetChip:
            processCancelBetChipState();
            break;
            
        case tdgGameViewUpdateBetMaxChip:
            processBetMaxChipState();
            break;
            
        case tdgGameViewUpdateCollectWonChips:
            processCollectWonChipState();
            break;
            
        case tdgGameViewUpdateRebetChips:
            processRebetChipState();
            break;
            
        case tdgGameViewUpdateMainGameFinish:
            processMainGameFinish();
            break;
            
        case tdgGameViewUpdatePlayDonGame:
            processPlayDonGameState();
            break;
            
        case tdgGameViewUpdateFinishDonGame:
            processFinishDonGameState();
            break;
            
        case tdgGameViewUpdateJackpot:
            processRecieveUpdateJackpotState();
            break;
        
        case tdgGameViewUpdateLevel:
            processRecieveUpdateLevelState();
            break;
            
        case tdgGameViewUpdateLevelExperience:
            processRecieveUpdateLevelExperienceState();
            break;
            
        case tdgGameViewUpdateDealButton:
            processDealButton();
            break;
            
        case tdgGameViewUpdateGotDealCards:
            processDealCards();
            break;
            
        case tdgGameViewUpdateDrawButton:
            processDrawButton();
            break;
            
        case tdgGameViewUpdateGotDrawCards:
            processDrawCards();
            break;
            
        case tdgGameViewUpdateDealCardSelected:
            processDealCardSelected();
            break;
            
        case tdgGameViewUpdateGotDonDealerCard:
            processDonDealerCard();
            break;
            
        case tdgGameViewUpdateSelectDonCard:
            processSelectDonCard();
            break;
            
        case tdgGameViewUpdateGotDonCards:
            processDonCards();
            break;
            
        case tdgGameViewUpdateDonDealButton:
            processDonDealButton();
            break;
            
        case tdgGameViewUpdateRemoveHighlightPayout:
            processRemoveHighlightPayout();
            break;
            
            
        default:
            break;
    }
}

#pragma mark - process game view state change

void GameView::processPrepareNewGame()
{
    CCLOG("processPrepareNewGame");
//    mDeckView->showPrepareCards();
    mGameViewFooter->prepareNewGame();
    mGameViewHeader->prepareNewGame();
    mGameViewMiddle->prepareNewGame();
    
    setGameViewStateToIdle();
}

void GameView::processBetChipState()
{
    SOUND().playSound(SOUND_BET_CHIP);
    
    mChipBettedView->moveCurrentBetChip();
    mGameViewFooter->enableDealButton();
    setGameViewStateToIdle();
}

void GameView::processBetMaxChipState()
{
    SOUND().playSound(SOUND_BET_CHIPS);

    mChipBettedView->moveBettedChips();
    mGameViewFooter->enableDealButton();
    setGameViewStateToIdle();
}

void GameView::processCancelBetChipState()
{
    SOUND().playSound(SOUND_BET_CHIPS);
    
    mChipBettedView->cancelBettedChips();
    mGameViewFooter->disableDealButton();
    setGameViewStateToIdle();
}

void GameView::processRebetChipState()
{
    SOUND().playSound(SOUND_BET_CHIPS);

    mChipBettedView->rebetLastChips();
    mGameViewFooter->enableDealButton();
    setGameViewStateToIdle();
}

void GameView::processCollectWonChipState()
{
    SOUND().playSound(SOUND_COLLECT_CHIPS);

    mChipBettedView->collectWonChips();
    setGameViewStateToIdle();
}

void GameView::processMainGameFinish()
{
    // turn into all draw cards
//    mDeckView->turnIntoAllDrawCards();
    
    // hide all card on table
    mDeckView->hideCardViewsOnTable();
    
    // hide all hightlight icons
    mGameViewFooter->hideAllHighLightIcons();
    
    setGameViewStateToIdle();
}

void GameView::processRecieveUpdateJackpotState() {
    mGameViewHeader->updateJackpot();
    setGameViewStateToIdle();
}

void GameView::processRecieveUpdateLevelState()
{
    // show levelup if have
    if (mGameModel->getIsGotLevelUp()) {
        LevelupPopupView *levelup = LevelupPopupView::create(string(CURRENCY_LONG(mGameModel->getUserInfo()->getLevel())));
        this->addChild(levelup, 1000);
    }
    
    mGameViewHeader->updateLevel();
    setGameViewStateToIdle();
}

void GameView::processRecieveUpdateLevelExperienceState()
{
    mGameViewHeader->updateLevelExperience();
    setGameViewStateToIdle();
}

void GameView::processPlayDonGameState()
{
    mGameViewFooter->showDonGame();
    setGameViewStateToIdle();
}

void GameView::processFinishDonGameState()
{
    // hide all card on table
    mDeckView->hideCardViewsOnTable();

    mGameViewFooter->hideDonGame();
    
    setGameViewStateToIdle();
}

void GameView::processDealButton()
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    // disable all bet chip buttons
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_DISABLE_CHIP_BUTTONS,
                                                                       NULL);
    
    // disable cancel bet chip buttons
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_DISABLE_CANCEL_BET_BUTTON,
                                                                       NULL);

    // disable deal button
    mGameViewFooter->disableDealButton();
    
    setGameViewStateToIdle();
}

void GameView::processDealCards()
{
    // hide card back
    mGameViewFooter->displayCardBacks(false);
    
    // show deal cards
    mDeckView->showBackOfDealCards();
    float delayTime = mDeckView->flipOutDealCards();
    
    // show auto held cards
    mGameViewFooter->showHeldIcons(mDeckView->getDeck()->getHeldBit(), delayTime);

    // show draw button
    mGameViewFooter->scheduleOnce(schedule_selector(GameViewFooter::showDrawButton), delayTime*1.1f);
    mGameViewFooter->enableDrawButton();
    
    // update header flags
    mGameViewHeader->setIsOnGame(true);
    
    setGameViewStateToIdle();
}

void GameView::processDrawButton()
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    // turn into draw cards
    mDeckView->turnIntoCardViewsOnDrawPosition();
    
    // hide held icons
    mGameViewFooter->hideAllHeldIcons();
    
    // disable draw button
    mGameViewFooter->disableDrawButton();
    
    setGameViewStateToIdle();
}

void GameView::processDrawCards()
{
    // play won sound
    float delayWonGame = DELAY_POST_FINISH_MAIN_GAME_EVENT;

    if (mDeckView->getDeck()->getWonBit()) {
        // got jackpot!!!
        if (mGameModel->getUserInfo()->getIsGotJackpot()) {
            long long jackpotValue =mGameModel->getUserInfo()->getTotalWonChips();
            CCString* jackpotString = CCString::createWithFormat("%s chips", CURRENCY_LONG(jackpotValue));
            JackpotPopupView *jackpot = JackpotPopupView::create(string(jackpotString->getCString()),
                                                                 jackpotValue);
            this->addChild(jackpot, ORDER_POPUP);
        }
        
        // normal won
        else {
            SOUND().playSound(SOUND_NORMAL_WIN);
        }

        if (!GPARAMS().isDoubleSpeedGameEnabled) {
            delayWonGame *= 2;
        }
    }
    
    // update Deck
    mDeckView->showBackOfDrawCards();
    float delayTime = mDeckView->flipOutDrawCards();
    
    // update won cards
    mGameViewFooter->showHighLightIcons(mDeckView->getDeck()->getWonBit(), delayTime);
    
    // update paytable
    mPaytableView->highlightWonPayTableCellView(delayTime);
    
    // update won label
    mGameViewMiddle->showWonChips();
    
    setGameViewStateToIdle();
    
    // post finish main game event to controller
    
    scheduleOnce(schedule_selector(GameView::postEventFinishMainGameToController),
                 delayWonGame);
}

void GameView::processDonDealerCard()
{
    mGameViewFooter->displayCardBacks(false, 1);
    
    // update Deck
    mDeckView->showBackOfDonDealerCard();
    mDeckView->flipOutDonDealerCard();

    // update button
    mGameViewFooter->startDonGame();
    
    setGameViewStateToIdle();
}

void GameView::processDonCards()
{
    mGameViewFooter->displayCardBacks(false, 2+4+8+16);

    // update Deck
    mDeckView->showBackOfDonCards();
    float delay = mDeckView->flipOutDonCards();

    // update result of DON
    mGameViewFooter->scheduleOnce(schedule_selector(GameViewFooter::showResultDonGame),
                                  delay);

//    mGameViewFooter->showResultDonGame();
    // update won label
    mGameViewMiddle->scheduleOnce(schedule_selector(GameViewMiddle::showWonChips),
                                  delay);
//    mGameViewMiddle->showWonChips();
    
    // post finish DON game event to controller
    float delayFinishDonGame = DELAY_POST_FINISH_DON_GAME_EVENT;
    if (!GPARAMS().isDoubleSpeedGameEnabled) {
        delayFinishDonGame *= 1.5f;
    }
    scheduleOnce(schedule_selector(GameView::postEventFinishDonGameToController),
                 delayFinishDonGame);

    setGameViewStateToIdle();
}

void GameView::processSelectDonCard()
{
    mGameViewFooter->dealDonGame();
    mGameViewFooter->showHeldIcons(mDeckView->getDeck()->getHeldBit(), 0);

    setGameViewStateToIdle();
}

void GameView::processDonDealButton()
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    // disable this buttons
    mGameViewFooter->disableDealButton();
    setGameViewStateToIdle();
}

GameModel* GameView::getGameModel() {
    return mGameModel;
}

void GameView::processDealCardSelected()
{
    SOUND().playSound(SOUND_HOLD_CARD);
    
    mGameViewFooter->showHeldIcons(mDeckView->getDeck()->getHeldBit(), 0);
    setGameViewStateToIdle();
}

void GameView::processRemoveHighlightPayout()
{
    mPaytableView->removeHighlightCellView();
    setGameViewStateToIdle();
}

#pragma mark - Post Event to Controller

void GameView::postEventFinishMainGameToController()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_MAIN_GAME_FINISH,
                                                                       NULL);
}

void GameView::postEventFinishDonGameToController()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_DON_GAME_FINISH,
                                                                       NULL);
}

#pragma mark - Process Notifications

void GameView::onSwitchHand(CCObject *object)
{
    mGameViewFooter->switchHandPosition();
    
    // update position for chipBettedView
    mChipBettedView->updateChipsPosition(mGameViewFooter->getSmallChipBg()->getPosition(),
                                         mGameViewFooter->getMediumChipBg()->getPosition(),
                                         mGameViewFooter->getBigChipBg()->getPosition());
}

