//
//  LoadingScene.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/17/15.
//
//

#include "LoadingScene.h"
#include "AtlasLoader.h"
#include "WelcomeLayer.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

LoadingScene::LoadingScene() {
    
}

bool LoadingScene::init() {
    return Scene::init();
}

void LoadingScene::onEnter() {
    Scene::onEnter();
    
    // add backround to current scene
    Sprite *background = Sprite::create("splash.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + visibleSize.height / 2));
    this->addChild(background);
    
    // start ansyc method load the atlas.png
    Director::getInstance()
    ->getTextureCache()
    ->addImageAsync("atlas.png",
                    CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::onExit() {
    Scene::onExit();
}

void LoadingScene::loadingCallBack(cocos2d::Texture2D *texture) {
    AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
    
    // After loading the texture , preload all the sound
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
    
    // After load all the things, change the scene to new one
    auto scene = WelcomeLayer::createScene();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}

LoadingScene::~LoadingScene() {
    
}