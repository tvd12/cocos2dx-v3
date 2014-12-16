//
//  GameController.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#ifndef __DragonVideoPoker__GameController__
#define __DragonVideoPoker__GameController__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GameModel;
class GameView;

class ServerSimulate;

class GameController : public CCObject
{
public:
    virtual ~GameController();
    
    GameController(GameModel *gameModel, GameView *gameView);
    
    static GameController* createWithModelAndView(GameModel *gameModel, GameView *gameView);

    // Tdg Server delegate
    // server notify cards to game controller
    void onDealCardsReceived(CCObject *object);
    void onDrawCardsReceived(CCObject *object);
    
    void onDonDealerCardReceived(CCObject *object);
    void onDonCardsReceived(CCObject *object);
    
    // server notify room variables update to game controller
    void onJackpotUpdate(CCObject *object);
    void onNumberOnlinePlayersUpdate(CCObject *object);
    void onLevelUpdate(CCObject *object);
    void onLevelExperienceUpdate(CCObject *object);

    // Notification center
    void onMainGameFinish(CCObject *object);
    void onDonGameFinish(CCObject *object);

    // Menu item callbacks
    void onCardSelectMenuItemCallback(CCNode *sender);
    void onDealMenuItemCallback(CCNode *sender);
    void onDrawMenuItemCallback(CCNode *sender);
    void onDonYesMenuItemCallback(CCNode *sender);
    void onDonNoMenuItemCallback(CCNode *sender);
    void onBetChipMenuItemCallBack(CCNode *sender);
    void onMaxBetMenuItemCallBack(CCNode *sender);
    void onCancelBetMenuItemCallBack(CCNode *sender);

    void setServerSimulate(ServerSimulate *serverSimulate)
    {mServerSimulate = serverSimulate;};
    
private:
    void prepareForANewGame();
    
    GameModel *mGameModel;
    GameView *mGameView;
  
    ServerSimulate *mServerSimulate;
    int mGamePlayState;
    int mDonHeldPosition;
};

#endif /* defined(__DragonVideoPoker__GameController__) */
