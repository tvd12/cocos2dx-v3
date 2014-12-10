//
//  MainGameLayer.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#include "MainGameLayer.h"
#include "MapAreaLayer.h"
#include "MapManager.h"

Scene* MainGameLayer::createScene(int size, int character) {
    Scene* ret = Scene::create();
    ret->addChild(MainGameLayer::create(size, character));
    
    return ret;
}

MainGameLayer* MainGameLayer::create(int size, int character) {
    MainGameLayer* pRet = new MainGameLayer;
    pRet->autorelease();
    pRet->init(size, character);
    
    return pRet;
}

void MainGameLayer::init(int size, int character) {
    Layer::init();
    
    this->setSize(size);
    this->setCharacter(character);
    
    mSize = size;
    mMenu = Menu::create();
    mMenu->setAnchorPoint(Point::ZERO);
    mMenu->setPosition(Point::ZERO);
    this->addChild(mMenu);
    
    Label* backLabel = Label::createWithSystemFont("Back",
                                                   "Arial",
                                                   18);
    MenuItem* backMenuItem =
    MenuItemLabel::create(backLabel,
                          CC_CALLBACK_1(MainGameLayer::mainGameLayerMenuItemCallback,this));
    backMenuItem->setPosition(30, 15);
    backMenuItem->setTag(999);
    mMenu->addChild(backMenuItem);
    
    Label* playLabel = Label::createWithSystemFont("Play: ",
                                                   "Arial",
                                                   24);
    mPlayMenuItem =
    MenuItemLabel::create(playLabel,
                          CC_CALLBACK_1(MainGameLayer::mainGameLayerMenuItemCallback, this));
    mPlayMenuItem->setTag(1000);
    mPlayMenuItem->setPosition(Vec2(140, 160));
    mMenu->addChild(mPlayMenuItem);
    
}

void MainGameLayer::mainGameLayerMenuItemCallback(cocos2d::Ref *pSender) {
    MenuItem* menuItem = static_cast<MenuItem*>(pSender);
    
    if(menuItem->getTag() == 999) {
        Director::getInstance()->replaceScene(MapAreaLayer::createScene(mSize));
    }
    else {
        int time = mCharacter * 0.75 + arc4random() % 90;
        int click = mCharacter + arc4random() % (2 * mCharacter);
        std::string str = "Play: time = " + std::to_string(time)
        + ", click = " + std::to_string(click);
        static_cast<Label*>(mPlayMenuItem->getLabel())->setString(str);
        
        MapArea* area = MapManager::getInstance()->areaByCharacter(mSize, mCharacter);
        area->setTime(time);
        area->setClick(click);
        area->setDate();
        
        MapManager::getInstance()->updateMapArea(area);
    }
}

