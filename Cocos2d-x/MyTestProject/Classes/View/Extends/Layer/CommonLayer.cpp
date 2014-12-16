//
//  CommonLayer.cpp
//  TomCuaCaOnline
//
//  Created by Ta Van Dung on 9/23/14.
//
//

#include "CommonLayer.h"

CommonLayer::CommonLayer() :
mMenu(NULL){
    
}

CommonLayer* CommonLayer::create() {
    CommonLayer *pRet = new CommonLayer();
    pRet->init();
    pRet->autorelease();
    
    return pRet;
}

bool CommonLayer::init() {
    Layer::init();
    this->addSprites();
    this->addMenus();
    this->addMenuItems();
    this->addLabels();
    this->addProgressBars();
    this->addTables();
    this->addActions();
    return true;
}

void CommonLayer::addSprites() {
    
}

void CommonLayer::addLabels() {
    
}

void CommonLayer::addProgressBars() {
    
}

void CommonLayer::addActions() {
    
}

void CommonLayer::addTables() {
    
}

void CommonLayer::addMenus() {
    mMenu = Menu::create();
    mMenu->setAnchorPoint(Point(0, 0));
    mMenu->setPosition(Point(0, 0));
    this->addChild(mMenu);
}

void CommonLayer::addMenuItems() {
    
}


bool CommonLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {
    return true;
}

void CommonLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {
    Layer::onTouchMoved(pTouch, pEvent);
    
}
void CommonLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {
    Layer::onTouchEnded(pTouch, pEvent);
}
void CommonLayer::onTouchCancelled(Touch *pTouch, Event *pEvent) {
    Layer::onTouchCancelled(pTouch, pEvent);
}