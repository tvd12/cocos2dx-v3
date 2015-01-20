//
//  PurchaseTestLayer.h
//  MyTestProject
//
//  Created by Dung Ta Van on 1/20/15.
//
//

#ifndef __MyTestProject__PurchaseTestLayer__
#define __MyTestProject__PurchaseTestLayer__

#include "cocos2d.h"
#include "ui/UIButton.h"

class PurchaseTestLayer : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(PurchaseTestLayer);
};

#endif /* defined(__MyTestProject__PurchaseTestLayer__) */
