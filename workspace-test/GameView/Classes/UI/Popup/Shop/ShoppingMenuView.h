//
//  ShoppingMenuView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/6/14.
//
//

#ifndef __DragonVideoPoker__ShoppingMenuView__
#define __DragonVideoPoker__ShoppingMenuView__

#include "cocos2d.h"

using namespace cocos2d;

class ShoppingMenuView  : public CCMenu {
    
public:
    
    ShoppingMenuView();
    
    static ShoppingMenuView* create();
    
    bool init();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    
    CC_SYNTHESIZE(CCRect, mBoundingBox, BoundingBox);
};

#endif /* defined(__DragonVideoPoker__ShoppingMenuView__) */
