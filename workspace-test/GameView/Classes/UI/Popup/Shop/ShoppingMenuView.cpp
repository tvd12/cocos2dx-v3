//
//  ShoppingMenuView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/6/14.
//
//

#include "ShoppingMenuView.h"
#include "GameParams.h"

ShoppingMenuView::ShoppingMenuView() :
mBoundingBox(GPARAMS().POP_SHOP_MENU_BOUNDINGBOX){
    
}

ShoppingMenuView* ShoppingMenuView::create() {
    ShoppingMenuView *pRet = new ShoppingMenuView();
    pRet->init();
    pRet->autorelease();
    
    return pRet;
}

bool ShoppingMenuView::init() {
    return CCMenu::init();
}

bool ShoppingMenuView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint touchPoint = pTouch->getLocationInView();
    
    if(touchPoint.y > mBoundingBox.getMaxY() || touchPoint.y < mBoundingBox.getMinY()) {
        return false;
    }
    
    return CCMenu::ccTouchBegan(pTouch, pEvent);
}