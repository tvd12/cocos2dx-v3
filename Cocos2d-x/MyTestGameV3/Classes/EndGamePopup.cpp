//
//  EndGamePopup.cpp
//  MyTestGameV3
//
//  Created by Ta Van Dung on 1/23/14.
//
//

#include <thread>

#include "EndGamePopup.h"

EndGamePopup::EndGamePopup() {
    
}

bool EndGamePopup::init() {
    if(!Layer::init()) {
        return false;
    }
    auto customListener = EventListenerCustom::create("finish_game", [=] (EventCustom *event) {
        char* userData = (char*)event->getUserData();
        log("data is %s", userData);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(customListener, 1);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//    auto listener = EventListenerTouchAllAtOnce::create();
//    listener->onTouchesBegan = [](const std::vector<Touch*>& touches, Event* event) {
//        if(touches.size() > 0) {
//            log("touch size is %d", touches.size());
//        }
//    };
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    pSprite = Sprite::create("dialogBox.png");
    
    pSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    LabelTTF* pLabel = LabelTTF::create("Do you want exit game?", "Arial", 24);
    
    pLabel->setPosition(Point(pSprite->getContentSize().width/2,
                              pSprite->getContentSize().height/2));
    MenuItemImage *exitButton = MenuItemImage::create("dialogButton.png",
                                                      "dialogButton.png",
                                                      CC_CALLBACK_1(EndGamePopup::backCallback, this));
    exitButton->setTag(0);
    
    cancelButton = MenuItemImage::create("dialogButton.png",
                                                        "dialogButton.png",
                                                        CC_CALLBACK_1(EndGamePopup::backCallback, this));
    LabelTTF* exitLabel = LabelTTF::create("Exit", "Arial", 20);
    cancelLabel = LabelTTF::create("Cancel", "Arial", 20);
    
    exitButton->setPosition(Point(pSprite->getContentSize().width/4, 30));
    cancelButton->setPosition(Point(3*pSprite->getContentSize().width/4, 30));
    
    exitLabel->setPosition(Point(exitButton->getContentSize().width/2,
                                 exitButton->getContentSize().height/2));
    cancelLabel->setPosition(Point(cancelButton->getContentSize().width/2,
                                   cancelButton->getContentSize().height/2));
    
    exitButton->addChild(exitLabel);
    cancelButton->addChild(cancelLabel);
    
    pSprite->addChild(pLabel);
    
    Menu *exitMenu = Menu::create(exitButton, cancelButton, NULL);
    exitMenu->setPosition(Point::ZERO);
    
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, exitMenu);
    
    pSprite->addChild(exitMenu);
    this->addChild(pSprite);
    //this->setTouchEnabled(true);
    pSprite->setTag(1000);
    this->setTag(999);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        return this->isVisible();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void EndGamePopup::onExit() {
    Layer::onExit();
}

void EndGamePopup::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event) {
    return;
}

void EndGamePopup::createCallback() {
    auto exitLabel1 = LabelTTF::create("Exit", "Arial", 20);
    exitLabel1->setPosition(pSprite->getPosition() + Point(count, count));
    exitLabel1->setColor(Color3B::GRAY);
    count += 10;
    this->addChild(exitLabel1);
}

void EndGamePopup::backCallback(Object *sender) {
    //this->removeFromParentAndCleanup(true);
    if(static_cast<Node*>(sender)->getTag() == 0) {
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif

    }
    this->setVisible(false);
//    try {
//        std::thread abcd = std::thread(CC_CALLBACK_0(EndGamePopup::createCallback, this));
//        abcd.detach();
//        log("thread ok");
//    } catch(const std::exception& ex) {
//        log("thread error: %s", ex.what());
//    }
}
