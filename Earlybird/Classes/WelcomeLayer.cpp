//
//  WelcomeLayer.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#include "WelcomeLayer.h"
#include "AtlasLoader.h"
#include "BirdSprite.h"
#include "GameScene.h"

WelcomeLayer::WelcomeLayer() {
    
}

Scene* WelcomeLayer::createScene() {
    WelcomeLayer* layer = WelcomeLayer::create();
    
    Scene* s = Scene::create();
    s->addChild(layer);
    
    return s;
}

bool WelcomeLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    int hour = lt->tm_hour;
    
    // create the background image according to the current time
    Sprite* background = NULL;
    if(hour >= 6 && hour <= 17) {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                   ->getSpriteFrameByName("bg_day"));
    }
    else {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                   ->getSpriteFrameByName("bg_night"));
    }
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(0, 0));
    this->addChild(background);
    
    // add the word game-title to the current scene
    Sprite *title  = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                   ->getSpriteFrameByName("title"));
    title->setPosition(Vec2(origin.x + visibleSize.width/2,
                             (visibleSize.height * 5) / 7));
    this->addChild(title);
    
    // add the start-menu to the current scene
    Sprite *startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                        ->getSpriteFrameByName("button_play"));
    Sprite *activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                              ->getSpriteFrameByName("button_play"));
    activeStartButton->setPositionY(5);
    
    auto menuItem  =
    MenuItemSprite::create(startButton,
                           activeStartButton,
                           NULL,
                           CC_CALLBACK_1(WelcomeLayer::welcomeLayerMenuItemCallback, this));
    menuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 ,
                                origin.y + visibleSize.height * 2 / 5));
    
    auto menu = Menu::create(menuItem,NULL);
    menu->setPosition(Point(origin.x, origin.y));
    this->addChild(menu, 1);
    
    // create a bird and set the position in the center of the screen
    mBird = BirdSprite::getInstance();
    mBird->createBird();
    mBird->setTag(birdspriteTag);
    mBird->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height * 3 / 5 - 10));
    mBird->idle();
    mBird->addToParent(this, 3);
    
    // add the lands
    for(int i = 0 ; i < 2 ; i++) {
        mLands[i] = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                  ->getSpriteFrameByName("land"));
        mLands[i]->setAnchorPoint(Vec2(0, 0));
        mLands[i]->setPosition(Vec2(0, 0));
        this->addChild(mLands[i]);
    }
    mLands[1]->setPosition(Vec2(mLands[0]->getContentSize().width - 2.0f, 0.0f));
    
    this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);
    
    // add the copyright-text to the current scene
    Sprite* copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                      ->getSpriteFrameByName("brand_copyright"));
    copyright->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/6));
    this->addChild(copyright, 10);
    
    return true;
}

void WelcomeLayer::scrollLand(float dt) {
    mLands[0]->setPositionX(mLands[0]->getPositionX() - 2.0f);
    mLands[1]->setPositionX(mLands[0]->getPositionX()
                            + mLands[0]->getContentSize().width - 2.0f);
    if(mLands[1]->getPositionX() == 0) {
        mLands[0]->setPositionX(0);
    }
}

void WelcomeLayer::welcomeLayerMenuItemCallback(cocos2d::Ref *pSender) {
    SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
    removeChildByTag(birdspriteTag);
    
    auto scene = GameScene::create();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}

WelcomeLayer::~WelcomeLayer() {
}