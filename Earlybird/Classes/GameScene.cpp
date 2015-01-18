//
//  GameScene.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "StatusLayer.h"
#include "GameLayer.h"

GameScene::GameScene() {
}

bool GameScene::init() {
    
    if(!Scene::initWithPhysics()) {
        return false;
    }
    
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    getPhysicsWorld()->setGravity(Vect(0, -900));
    
    // add the background
    auto backgroundLayer = BackgroundLayer::create();
    if(backgroundLayer) {
        this->addChild(backgroundLayer);
    }
    
    auto statusLayer = StatusLayer::create();
    
    // Add the main game layer
    auto gameLayer = GameLayer::create();
    if(gameLayer) {
        gameLayer->setPhyWorld(getPhysicsWorld());
        gameLayer->setDelegate(statusLayer);
        this->addChild(gameLayer);
    }
    
    // Add the game status layer to show the score and game status
    if(statusLayer) {
        this->addChild(statusLayer);
    }
    
    // Add operation layer to control the game
    auto optionLayer = OptionLayer::create();
    if(optionLayer) {
        optionLayer->setDelegate(gameLayer);
        this->addChild(optionLayer);
    }
    
    return true;
}

void GameScene::restart() {
    removeAllChildren();
    init();
}

GameScene::~GameScene() {
    
}