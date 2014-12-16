//
//  GameView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#ifndef __DragonVideoPoker__GameView__
#define __DragonVideoPoker__GameView__

#include "cocos2d.h"
#include "GameViewDefine.h"

#ifdef CC_TARGET_OS_IPHONE
#include <queue.h>
#else
#include <queue>
#endif

#define ORDER_CARDS             100
#define ORDER_LABELS            200
#define ORDER_PAYTABLE          300
#define ORDER_HELD_SPRITE       400
#define ORDER_CHIPS             1000
#define ORDER_POPUP             2000

using namespace std;
USING_NS_CC;

class GameModel;
class ChipBettedView;
class PaytableView;
class DeckView;
class GameViewHeader;
class GameViewMiddle;
class GameViewFooter;

class GameView : public CCLayer
{
public:
    virtual ~GameView(void);
    GameView(GameModel* gameModel);
    static GameView* createWithModel(GameModel* gameModel);
    bool initWithModel(GameModel* gameModel);
    
    virtual void update(float dt);

    // update game view state
    void updateGameViewState(long state);

    // game model delegate
    
    void addMenuItems(CCObject *target);
    
    GameModel* getGameModel();

private:
    
    void addBackground();
    void addHeaderLayer();
    void addMiddleLayer();
    void addFooterLayer();

    void addBetChips();
    void addPaytable();
    void addDeck();
    
    // update game view state
    bool isGameViewStateIdle();
    void getNextGameViewState();
    void setGameViewStateToIdle();
    void updateGameViewWithState();
    
    // process game view state change
    void processBetChipState();
    void processBetMaxChipState();
    void processCancelBetChipState();
    void processRebetChipState();
    void processCollectWonChipState();
    void processMainGameFinish();
    void processRecieveUpdateJackpotState();
    void processRecieveUpdateLevelState();
    void processRecieveUpdateLevelExperienceState();
    void processPlayDonGameState();
    void processFinishDonGameState();
    
    void processDealCards();
    void processDealButton();
    void processDealCardSelected();
    void processDrawCards();
    void processDrawButton();
    void processRemoveHighlightPayout();
    
    void processDonDealerCard();
    void processDonCards();
    void processSelectDonCard();
    void processDonDealButton();

    // Post Event to Controller
    void postEventFinishMainGameToController();
    void postEventFinishDonGameToController();
    
    // process notifications
    void onSwitchHand(CCObject *object);
    
    // prepare for a new game
    void processPrepareNewGame();

    GameModel* mGameModel;
    
    // draw header of game view
    GameViewHeader* mGameViewHeader;
    
    // draw middle of game view
    GameViewMiddle* mGameViewMiddle;
    
    // draw footer of game view
    GameViewFooter* mGameViewFooter;
        
    // chip betted view
    ChipBettedView* mChipBettedView;
    
    // deck view
    DeckView* mDeckView;
    
    // paytable view
    PaytableView* mPaytableView;
    
    // game state queue
    deque<GameViewState> mStateQueue;
    GameViewState mCurrentGameViewState;
    
};

#endif /* defined(__DragonVideoPoker__GameView__) */
