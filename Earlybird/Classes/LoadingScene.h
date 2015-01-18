//
//  LoadingScene.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/17/15.
//
//

#ifndef __Earlybird__LoadingScene__
#define __Earlybird__LoadingScene__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class LoadingScene : public Scene {
    
public:
    
    LoadingScene();
    
    /**
     *  Initializes the instance of AtlasLoader.
     *
     *  @note When you are porting Cocos2d-x to a new platform, 
     *  you may need to take care of this method.
     *
     *  @return true if successed, otherwise it returns false.
     *
     */
    virtual bool init();
    
    /**
     * When this scene appear ,will call this method,
     * not this scene is create, so if you have some thing
     * want do when scen appear not init, please add to here
     */
    void onEnter() override;
    
    void onExit() override;
    
    CREATE_FUNC(LoadingScene);
    
    ~LoadingScene();
    
private:
    
    /**
     *  Called when the texture (exp. atlas.png) is loading finish,
     *  will call this function
     *  this function finish build all the SpritFrame by using AtlasLoader
     */
    void loadingCallBack(Texture2D *texture);
};

#endif /* defined(__Earlybird__LoadingScene__) */
