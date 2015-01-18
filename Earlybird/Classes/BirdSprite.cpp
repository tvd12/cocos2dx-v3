//
//  BirdSprite.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/11/15.
//
//

#include "BirdSprite.h"
#include "AtlasLoader.h"


BirdSprite::BirdSprite() :
mGraphic(NULL) {
    
}

BirdSprite::~BirdSprite() {
    CC_SAFE_RELEASE(mGraphic);
    CC_SAFE_RELEASE(mIdleAction);
    CC_SAFE_RELEASE(mSwingAction);
}

BirdSprite* BirdSprite::getInstance() {
    static BirdSprite sInstance;
    
    return &sInstance;
}

bool BirdSprite::init() {
    mIsFirstTime = 3;
    
    return true;
}

bool BirdSprite::createBird() {
    createBirdByRandom();
    
    mGraphic = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                             ->getSpriteFrameByName(mBirdName));
    mGraphic->retain();
    
    // init idle status
    //create the bird animation
    Animation* animation = createAnimation(mBirdNameFormat,
                                           3,
                                           10);
    Animate* animate = Animate::create(animation);
    mIdleAction = RepeatForever::create(animate);
    mIdleAction->retain();
    
    //create the swing action
    ActionInterval *up = MoveBy::create(0.4f, Vec2(0, 8));
    ActionInterval *upBack = up->reverse();
    mSwingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
    mSwingAction->retain();
    
    return true;
}

void BirdSprite::idle() {
    if(changeState(ACTION_STATE_IDLE)) {
        mGraphic->runAction(mIdleAction);
        mGraphic->runAction(mSwingAction);
    }
}

void BirdSprite::fly() {
    if(changeState(ACTION_STATE_FLY)) {
        mGraphic->stopAction(mSwingAction);
        mGraphic->getPhysicsBody()->setGravityEnable(true);
    }
}

void BirdSprite::die() {
    if(changeState(ACTION_STATE_DIE)) {
        mGraphic->stopAllActions();
    }
}

Animation* BirdSprite::createAnimation(string fmt, int count, float fps) {
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(1 / fps);
    
    for(int i = 0 ; i < count ; i++) {
        string filename = StringUtils::format(fmt.c_str(), i);
        SpriteFrame* frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    
    return animation;
}

bool BirdSprite::changeState(ActionState state) {
    mCurrentStatus = state;
    
    return true;
}

void BirdSprite::createBirdByRandom() {
    if(mIsFirstTime & 1) {
        mIsFirstTime &= 2;
    }
    else if(mIsFirstTime & 2){
        mIsFirstTime &= 1;
        return ;
    }
    
    srand((unsigned)time(NULL));
    int type = ((int)rand())% 3;
    switch (type)
    {
        case 0:
            mBirdName = "bird0_0";
            mBirdNameFormat = "bird0_%d";
            break;
        case 1:
            mBirdName = "bird1_0";
            mBirdNameFormat = "bird1_%d";
            break;
        case 2:
            mBirdName = "bird2_0";
            mBirdNameFormat = "bird2_%d";
            break;
        default:
            mBirdName = "bird2_0";
            mBirdNameFormat = "bird2_%d";
            break;
    }
}

void BirdSprite::addToParent(Node *pParent, int zOrder) {
    pParent->addChild(mGraphic, zOrder);
}

void BirdSprite::removeFromParent() {
    mGraphic->removeFromParent();
}

void BirdSprite::setTag(int tag) {
    mGraphic->setTag(tag);
}

void BirdSprite::setPosition(const cocos2d::Vec2 &position) {
    mGraphic->setPosition(position);
}