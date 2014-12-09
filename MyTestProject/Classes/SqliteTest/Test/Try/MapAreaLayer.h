//
//  MapAreaLayer.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#ifndef __MyTestProject__MapAreaLayer__
#define __MyTestProject__MapAreaLayer__

#include "cocos2d.h"

using namespace cocos2d;

class MapArea;

class MapAreaLayer : public Layer {
public:
    static Scene* createScene(int size);
    static MapAreaLayer* create(int size);
    
    void init(int size);
    
    void createMenuItemAt(int index);
    
    CC_SYNTHESIZE(int, mSize, Size);
    
private:
    
    void mapAreaMenuItemCallback(Ref* pSender);
    
    Menu *mMenu;
};

#endif /* defined(__MyTestProject__MapAreaLayer__) */
