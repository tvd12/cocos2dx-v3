//
//  GameScene.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#ifndef __Earlybird__GameScene__
#define __Earlybird__GameScene__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public Scene{
public:
    GameScene();
    
    bool virtual init();
    
    void restart();
    
    CREATE_FUNC(GameScene);
    
    ~GameScene();
};

#endif /* defined(__Earlybird__GameScene__) */
