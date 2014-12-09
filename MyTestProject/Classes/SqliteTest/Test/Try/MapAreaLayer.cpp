//
//  MapAreaLayer.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#include "MapAreaLayer.h"
#include "MapManager.h"
#include "SqliteTestScene.h"
#include "MainGameLayer.h"

Scene* MapAreaLayer::createScene(int size) {
    Scene* scene = Scene::create();
    scene->addChild(MapAreaLayer::create(size));
    
    return scene;
}

MapAreaLayer* MapAreaLayer::create(int size) {
    MapAreaLayer* pRet = new MapAreaLayer;
    pRet->autorelease();
    pRet->init(size);
    
    return pRet;
}

void MapAreaLayer::init(int size) {
    Layer::init();
    mSize = size;
    mMenu = Menu::create();
    mMenu->setAnchorPoint(Point::ZERO);
    mMenu->setPosition(Point::ZERO);
    this->addChild(mMenu);
    
    int length = MapManager::getInstance()->numberOfCharacters(mSize);
    for(int i = 0 ; i < length; i++) {
        createMenuItemAt(i);
    }
    
    Label* backLabel = Label::createWithSystemFont("Back",
                                                   "Arial",
                                                   18);
    MenuItem* backMenuItem =
    MenuItemLabel::create(backLabel,
                          CC_CALLBACK_1(MapAreaLayer::mapAreaMenuItemCallback,this));
    backMenuItem->setPosition(30, 15);
    backMenuItem->setTag(999);
    mMenu->addChild(backMenuItem);
}

void MapAreaLayer::createMenuItemAt(int index) {
    MenuItem* squareMenuItem =
    MenuItemImage::create("square.png",
                          "square.png",
                          CC_CALLBACK_1(MapAreaLayer::mapAreaMenuItemCallback, this));
    squareMenuItem->setPosition(Vec2((30 + 60) * (index % 3 + 1) + 60 * (index % 3),
                                     25 + (15 + 60) * (index / 3 + 1) + 60 * (index / 3)));
    mMenu->addChild(squareMenuItem);
    
    for(int i = 0 ; i < 3 ; i++) {
        float x = 34 + 23 * i + 3;
        Sprite* starSprite = Sprite::create("starb.png");
        starSprite->setPosition(Vec2(x, 5));
        squareMenuItem->addChild(starSprite);
    }
    
    MapArea* area = MapManager::getInstance()->areaAt(mSize, index);
    string numchar = area->getCharacterStr();
    Label* charLabel =
    Label::createWithSystemFont(numchar + "\nCharacter",
                                "Arial",
                                17);
    charLabel->setAlignment(TextHAlignment::CENTER);
    charLabel->setPosition(Vec2(60, 35));
    charLabel->setColor(Color3B(10, 11, 255));
    squareMenuItem->addChild(charLabel);
    
    Label* dotsLabel =
    Label::createWithSystemFont("..............",
                                "Arial",
                                16);
    dotsLabel->setAlignment(TextHAlignment::CENTER);
    dotsLabel->setPosition(Vec2(60, 70));
    dotsLabel->setColor(Color3B(10, 11, 255));
    squareMenuItem->addChild(dotsLabel);
    
    int time = area->getTime();
    int click = area->getClick();
    
    string inforStr = "Play now!";
    if(time > 3 && click >= area->getCharacter()) {
        inforStr = area->getTimeStr() + "s & "
        + area->getCharacterStr() + " click";
    }
    
    Label* infoLabel =
    Label::createWithSystemFont(inforStr,
                                "Arial",
                                15);
    infoLabel->setAlignment(TextHAlignment::CENTER);
    infoLabel->setPosition(Vec2(60, 80));
    infoLabel->setColor(Color3B(10, 11, 255));
    squareMenuItem->addChild(infoLabel);
    squareMenuItem->setTag(area->getCharacter());
}

void MapAreaLayer::mapAreaMenuItemCallback(cocos2d::Ref *pSender) {
    MenuItem* menuItem = static_cast<MenuItem*>(pSender);
    if(menuItem->getTag() == 999) {
        Director::getInstance()->replaceScene(SqliteTestScene::scene());
    }
    else {
        Director::getInstance()->replaceScene(MainGameLayer::createScene(mSize,
                                                                         menuItem->getTag()));
    }
}