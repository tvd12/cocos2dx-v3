//
//  GameScene.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#ifndef __DragonVideoPoker__GameScene__
#define __DragonVideoPoker__GameScene__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameModel;
class GameView;
class GameController;

class GameScene : public CCScene
{
public:
    GameScene();
    ~GameScene();
    
    CREATE_FUNC(GameScene);
    
private:
    GameModel* mGameModel;
    GameView* mGameView;
    GameController* mGameController;
};


#endif /* defined(__DragonVideoPoker__GameScene__) */
