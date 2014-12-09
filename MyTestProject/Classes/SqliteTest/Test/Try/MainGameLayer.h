//
//  MainGameLayer.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#ifndef __MyTestProject__MainGameLayer__
#define __MyTestProject__MainGameLayer__

#include "cocos2d.h"

using namespace cocos2d;

class MainGameLayer : public Layer {
public:
    static Scene* createScene(int size, int character);
    static MainGameLayer* create(int size, int character);
    
    void init(int size, int character);
    
    CC_SYNTHESIZE(int, mSize, Size);
    CC_SYNTHESIZE(int, mCharacter, Character);
    CC_SYNTHESIZE(MenuItemLabel*, mPlayMenuItem, PlayMenuItem);
    
private:
    void mainGameLayerMenuItemCallback(Ref* pSender);
    Menu *mMenu;
};

#endif /* defined(__MyTestProject__MainGameLayer__) */
