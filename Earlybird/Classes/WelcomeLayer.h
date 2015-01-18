//
//  WelcomeLayer.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#ifndef __Earlybird__WelcomeLayer__
#define __Earlybird__WelcomeLayer__

#include <ctime>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

class BirdSprite;

class WelcomeLayer : public Layer {
public:
    
    WelcomeLayer();
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(WelcomeLayer);
    
    virtual ~WelcomeLayer();
    
private:
    
    enum menuitemtag {
        birdspriteTag = 1,
        startmenuitemTag = 2,
    };
    
    void welcomeLayerMenuItemCallback(Ref* pSender);
    
    /**
     * This method is make the land have a scroll animation
     */
    void scrollLand(float dt);
    
    Sprite* mLands[2];
    
    BirdSprite* mBird;
};

#endif /* defined(__Earlybird__WelcomeLayer__) */
