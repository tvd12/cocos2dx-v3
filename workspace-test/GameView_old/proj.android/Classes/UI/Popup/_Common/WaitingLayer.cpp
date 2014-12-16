//
//  WaitingLayer.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 11/29/13.
//
//

#include "WaitingLayer.h"
#include "GameParams.h"
#include "VisibleRect.h"


WaitingLayer * WaitingLayer::createWithType(int type)
{
    WaitingLayer *pRet = new WaitingLayer();
    pRet->initWithType(type);
    pRet->autorelease();
    return pRet;
}

bool WaitingLayer::initWithType(int type)
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    layerType = type;
    
    // Prevent click thru lower layers
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
                                                                            kCCMenuHandlerPriority - WAITING_POP_UP_DEEP,
                                                                            true);
    addSprites();
    
    return true;
}

void WaitingLayer::onExit()
{
    CCLayer::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool WaitingLayer::ccTouchBegan(CCTouch * touch, CCEvent * event)
{
    switch (layerType) {
        case kWaitingLayerJustShow:
            return false;
            break;
            
        case kWaitingLayerMustWait:
            return true;
            break;
            
        default:
            break;
    }

    return false;
}

void WaitingLayer::removeLayer()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    removeFromParentAndCleanup(true);
}

void WaitingLayer::addSprites()
{
    if (layerType == kWaitingLayerMustWait) {
        // add black background
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
        CCSize frameSize = pEGLView->getFrameSize();
        
        CCSprite *colorBG = CCSprite::create();
        colorBG->setTextureRect(CCRect(0, 0, frameSize.width, frameSize.height));
        colorBG->setColor(ccBLACK);
        colorBG->setOpacity(120);
        colorBG->setPosition(CCPoint(frameSize.width/2, frameSize.height/2));
        this->addChild(colorBG);
    }
    
    // add indicator
    indicator = CCSprite::create("loading_icon.png");
    indicator->setOpacity(200);
    indicator->setPosition(VisibleRect::center());
    addChild(indicator);
    
    // create rotate action
    CCRotateBy *rotate = CCRotateBy::create(1.75f, 360.0f);
    indicator->runAction(CCRepeatForever::create(rotate));
}
