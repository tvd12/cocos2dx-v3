//
//  SelectGameMenuSprite.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#include "SelectGameMenuSprite.h"
#include "GameParams.h"
#include "GameViewDefine.h"
#include "RoomInfo.h"
#include "TdgServer.h"

#include "VideoPokerDefine.h"
#include "TextUtils.h"
#include "UpdateableLabelTTF.h"


SelectGameMenuSprite* SelectGameMenuSprite::createWithIndex(const int index,
                                                            bool isSelected,
                                                            bool isDisabled)
{
    SelectGameMenuSprite *sprite = new SelectGameMenuSprite();
    if (sprite->initWithIndex(index, isSelected, isDisabled)); {
        sprite->autorelease();
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    return NULL;
}

bool SelectGameMenuSprite::initWithIndex(const int index,
                                         bool isSelected,
                                         bool isDisabled)
{
    mGameType = index;
    
    CCString* fileName;
    if (isDisabled) {
        fileName = CCString::createWithFormat("game_type_%d_disable.png", index);
    }
    else {
        if (isSelected) {
            fileName = CCString::createWithFormat("game_type_%d_selected.png", index);
        }
        else {
            fileName = CCString::createWithFormat("game_type_%d.png", index);
        }
    }
    
//    CCLOG("this is file %s", fileName->getCString());
    CCSprite::initWithFile(fileName->getCString());
    
    // get room info from server
    vector<RoomInfo *>* rooms = SERVER().getRoomInfos();
    mRoomInfo = rooms->at(index);
    
    if (isDisabled) {
        mJackpotLabel = NULL;
        addLockedItems();
    }
    else {
        addRoomInfoItems();
        scheduleUpdate();
    }
    
    return true;
}

void SelectGameMenuSprite::grayItems()
{
    mJackpotLabel->setColor(ccGRAY);
}

void SelectGameMenuSprite::addRoomInfoItems()
{
    // add jackpot sprite
    CCSprite* jackpotSprite = CCSprite::create("jackpot_ingame.png");
    jackpotSprite->setPosition(GPARAMS().LBB_JACKPOT_SPRITE_IN_MENU_ITEM_POSITION);
    this->addChild(jackpotSprite);
    
    // add jackpot label
    mJackpotLabel = UpdateableLabelTTF::createWithSource(mRoomInfo->getRoomInfoJackpot(),
                                                         DEFAULT_FONT_NAME,
                                                         GPARAMS().CMM_FONT_SIZE_2,
                                                         JACKPOT_DISPLAY_UPDATE_RATE);
    mJackpotLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mJackpotLabel->setPosition(GPARAMS().LBB_JACKPOT_LABEL_IN_MENU_ITEM_POSITION);
    this->addChild(mJackpotLabel);
    
    // add stakes
    CCString* stakesString = CCString::createWithFormat("Stakes: %s - %s",
                                                        CURRENCY_SHORT(mRoomInfo->getMinStakes()),
                                                        CURRENCY_SHORT(mRoomInfo->getMaxStakes()));
    CCLabelTTF* stakesLabel = CCLabelTTF::create(stakesString->getCString(),
                                                 DEFAULT_FONT_NAME,
                                                 GPARAMS().CMM_FONT_SIZE_1*0.8f);
    stakesLabel->setAnchorPoint(CCPoint(0, 0.5f));
    stakesLabel->setPosition(GPARAMS().LBB_STACKS_IN_MENU_ITEM_POSITION);
    this->addChild(stakesLabel);
}

void SelectGameMenuSprite::addLockedItems()
{
    CCSprite* lockSprite = CCSprite::create("lock.png");
    lockSprite->setPosition(GPARAMS().LBB_LOCK_SPRITE_IN_MENU_ITEM_POSITION);
    this->addChild(lockSprite);
    
    CCString* lockString = CCString::createWithFormat("Unlock level %ld",
                                                      mRoomInfo->getLevelRequired());
    CCLabelTTF* lockLabel = CCLabelTTF::create(lockString->getCString(),
                                               DEFAULT_FONT_NAME,
                                               GPARAMS().CMM_FONT_SIZE_2);
    lockLabel->setAnchorPoint(ccp(0, 0.5f));
    lockLabel->setPosition(GPARAMS().LBB_LOCK_LABEL_IN_MENU_ITEM_POSITION);
    this->addChild(lockLabel);
}

#pragma mark - update jackpot value

void SelectGameMenuSprite::update(float dt)
{
    CCSprite::update(dt);
}

