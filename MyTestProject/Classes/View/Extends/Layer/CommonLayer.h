//
//  CommonLayer.h
//  TomCuaCaOnline
//
//  Created by Ta Van Dung on 9/23/14.
//
//

#ifndef __TomCuaCaOnline__CommonLayer__
#define __TomCuaCaOnline__CommonLayer__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

#define CREATE_SCENE_FUNC(__classname__) \
public: \
    static Scene* createScene() { \
        Scene* scene = Scene::create(); \
        __classname__ *layer = __classname__::create(); \
        scene->addChild(layer); \
        return scene; \
    }

class CommonLayer : public Layer {
public:
    CommonLayer();
    static CommonLayer* create();
    virtual bool init();
    
    // Layer
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
    
    CC_SYNTHESIZE_READONLY(Menu*, mMenu, Menu);
    
protected:
    virtual void addSprites();
    virtual void addLabels();
    virtual void addMenuItems();
    virtual void addMenus();
    virtual void addProgressBars();
    virtual void addTables();
    virtual void addActions();
    
};

#endif /* defined(__TomCuaCaOnline__CommonLayer__) */