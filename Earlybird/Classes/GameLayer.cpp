//
//  GameLayer.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/13/15.
//
//

#include "GameLayer.h"
#include "BirdSprite.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "UserRecord.h"
#include "StatusLayer.h"

using namespace CocosDenshion;

GameLayer::GameLayer() :
mBird(NULL),
mGroundNode(NULL),
mPips(vector<Node*>()),
mLandSpites(),
mShiftLand(NULL),
mScore(0),
mWorld(NULL),
mDelegate(NULL),
mGameStatus(GAME_STATUS_READY) {

}

bool GameLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    //get the origin point of the X-Y axis, and the visible size of the screen
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    mGameStatus = GAME_STATUS_READY;
    mScore = 0;
    
    // Add the bird
    mBird = BirdSprite::getInstance();
    mBird->createBird();
    
    PhysicsBody *body = PhysicsBody::create();
    body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
    body->setDynamic(true);
    body->setLinearDamping(0.0f);
    body->setGravityEnable(false);
    body->setContactTestBitmask(true);
    
    mBird->getGraphic()->setPhysicsBody(body);
    mBird->setPosition(Vec2(origin.x + visibleSize.width * 1 / 3 - 5,
                            origin.y + visibleSize.height / 2 + 5));
    mBird->idle();
    mBird->addToParent(this, 0);
    
    // Add the ground
    mGroundNode = Node::create();
    float landHeight = BackgroundLayer::getLandHeight();
    auto groundBody = PhysicsBody::create();
    groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
    groundBody->setDynamic(false);
    groundBody->setLinearDamping(0.0f);
    groundBody->setContactTestBitmask(true);
    
    mGroundNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    mGroundNode->setPhysicsBody(groundBody);
    mGroundNode->setPosition(Vec2(144, landHeight / 2));
    this->addChild(mGroundNode);
    
    //init lands
    for(int i = 0 ; i < 2 ; i++) {
        mLandSpites[i] = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                       ->getSpriteFrameByName("land"));
        mLandSpites[i]->setAnchorPoint(Vec2(0, 0));
        mLandSpites[i]->setPosition(Vec2(0, 0));
        this->addChild(mLandSpites[i], 30);
    }
    mLandSpites[1]->setPosition(Vec2(mLandSpites[0]->getContentSize().width - 2.0f, 0));
    
    mShiftLand = schedule_selector(GameLayer::scrollLand);
    this->schedule(mShiftLand, 0.01f);
    
    this->scheduleUpdate();
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

bool GameLayer::onContactBegin(const cocos2d::PhysicsContact &contact) {
    this->gameOver();
    
    return true;
}

void GameLayer::scrollLand(float dt) {
    mLandSpites[0]->setPositionX(mLandSpites[0]->getPositionX() - 2.0f);
    mLandSpites[1]->setPositionX(mLandSpites[0]->getPositionX()
                                 + mLandSpites[0]->getContentSize().width - 2.0f);
    if(mLandSpites[1]->getPositionX() == 0) {
        mLandSpites[0]->setPositionX(0);
    }
    
    // move the pips
    for(auto singlePip : mPips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < - PIP_WIDTH) {
            singlePip->setTag(PIP_NEW);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(getRandomHeight());
        }
    }
}

void GameLayer::onTouch() {
    if(mGameStatus == GAME_STATUS_OVER) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
    if(mGameStatus == GAME_STATUS_READY) {
        getDelegate()->onGameStart();
        mBird->fly();
        mGameStatus = GAME_STATUS_START;
        createPips();
    }
    else if(mGameStatus == GAME_STATUS_START) {
        mBird->getGraphic()->getPhysicsBody()->setVelocity(Vect(0, 260));
    }
}

void GameLayer::rotateBird() {
    float verticalSpeed = mBird->getGraphic()->getPhysicsBody()->getVelocity().y;
    mBird->getGraphic()->setRotation(min(max(-30, -(verticalSpeed * 0.2 + 60)), 30));
}

void GameLayer::update(float delta) {
    if(mGameStatus == GAME_STATUS_START) {
        rotateBird();
        checkHit();
    }
}

void GameLayer::createPips() {
    // create the pips
    for(int i = 0 ; i < PIP_COUNT ; i++) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite* pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                      ->getSpriteFrameByName("pipe_up"));
        Sprite* pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                        ->getSpriteFrameByName("pipe_down"));
        Node* singlePip = Node::create();
        
        //bind to pair
        pipDown->setPosition(Vec2(0, PIP_HEIGHT + PIP_DISTANCE));
        singlePip->addChild(pipDown, 0, DOWN_PIP);
        singlePip->addChild(pipUp, 0, UP_PIP);
        singlePip->setPosition(Vec2(visibleSize.width + i * PIP_INTERVAL + WAIT_DISTANCE,
                                    getRandomHeight()));
        
        auto body = PhysicsBody::create();
        auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),
                                                    PHYSICSSHAPE_MATERIAL_DEFAULT,
                                                    Point(0, PIP_HEIGHT + PIP_DISTANCE));
        body->addShape(shapeBoxDown);
        body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
        body->setDynamic(false);
        body->setContactTestBitmask(true);
        singlePip->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        singlePip->setPhysicsBody(body);
        singlePip->setTag(PIP_NEW);
        
        this->addChild(singlePip);
        
        mPips.push_back(singlePip);
    }
}

int GameLayer::getRandomHeight() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return rand() % (int)(2 * PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}


void GameLayer::checkHit() {
    for(auto pip : mPips) {
        if(pip->getTag() == PIP_NEW) {
            if(pip->getPositionX() < mBird->getGraphic()->getPositionX()) {
                SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
                mScore ++;
                getDelegate()->onGamePlaying(mScore);
                pip->setTag(PIP_PASS);
            }
        }
    }
}

void GameLayer::gameOver() {
    if(mGameStatus == GAME_STATUS_OVER) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
    
    // get the best score
    int bestScore = UserRecord::getInstance()->getTheBestScore();
    
    // update score
    if(mScore > bestScore) {
        UserRecord::getInstance()->saveTheBestScore(mScore);
    }
    
    getDelegate()->onGameEnd(mScore, bestScore);
    unschedule(mShiftLand);
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
    
    mBird->die();
    mBird->getGraphic()->setRotation(-90);
    birdSpriteFadeOut();
    mGameStatus = GAME_STATUS_OVER;
}

void GameLayer::birdSpriteFadeOut() {
    FadeOut *fadeOut = FadeOut::create(1.5);
    CallFuncN* done = CallFuncN::create(CC_CALLBACK_0(GameLayer::birdSpriteRemove, this));
    Sequence* sequence = Sequence::createWithTwoActions(fadeOut, done);
    mBird->getGraphic()->stopAllActions();
    mBird->getGraphic()->runAction(sequence);
}

void GameLayer::birdSpriteRemove() {
    mBird->getGraphic()->setRotation(0);
    mBird->removeFromParent();
}

void GameLayer::setPhyWorld(cocos2d::PhysicsWorld *world) {
    mWorld = world;
}

GameLayer::~GameLayer() {
    
    mPips.clear();
}