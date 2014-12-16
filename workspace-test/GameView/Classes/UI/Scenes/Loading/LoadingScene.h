//
//  LoadingScene.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/8/14.
//
//

#ifndef __DragonVideoPoker__LoadingScene__
#define __DragonVideoPoker__LoadingScene__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class LoadingLayer : public CCLayer
{
public:
    static CCScene* createScene();
    
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(LoadingLayer);
    
private:
    void addSprites();
    
    CCProgressTimer *mLoadingProgress;
    
};

#endif /* defined(__DragonVideoPoker__LoadingScene__) */
