//
//  WaitingLayer.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 11/29/13.
//
//

#ifndef __Dragon_Poker__WaitingLayer__
#define __Dragon_Poker__WaitingLayer__

typedef enum WAITING_LAYER_TYPE {
    kWaitingLayerMustWait,
    kWaitingLayerJustShow,
} WaitingLayerType;

#define WAITING_POP_UP_DEEP                 300
#define WAITING_POP_UP_ORDER                400

#include "cocos2d.h"

USING_NS_CC;

class WaitingLayer : public CCLayer
{
    
public:
    virtual void onExit();
    
    bool initWithType(int type);
    static WaitingLayer * createWithType(int type);
    
    bool ccTouchBegan(CCTouch * touch, CCEvent * event);
    
    void removeLayer();
    int getWaitingType() {return layerType;};
    
private:
    void addSprites();
    
    int layerType;
    CCSprite *indicator;
};


#endif /* defined(__Dragon_Poker__WaitingLayer__) */
