//
//  OptionLayer.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/13/15.
//
//

#include "OptionLayer.h"

OptionLayer::OptionLayer() :
mDelegate(NULL) {
    
}


bool OptionLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = std::bind(&OptionLayer::onTouchesBegan, this,
                                         std::placeholders::_1,
                                         std::placeholders::_2);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void OptionLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event) {
    mDelegate->onTouch();
}


OptionLayer::~OptionLayer() {
    
}