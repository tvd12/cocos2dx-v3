//
//  ChipView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "ChipView.h"
#include "GameViewDefine.h"

#include "Chip.h"
#include "TextUtils.h"
#include "GameParams.h"


ChipView * ChipView::create(Chip* chip, bool isNumberAttached, bool isGrayed)
{
    ChipView *pRet = new ChipView();
    pRet->initWithChip(chip, isNumberAttached, isGrayed);
    pRet->autorelease();
    return pRet;
}

bool ChipView::initWithChip(Chip* chip, bool isNumberAttached, bool isGrayed)
{
    mChip = chip;
    string fileName;
    
    switch (chip->getType()) {
        case CHIP_SMALL:
            fileName = "icon_chip_red.png";
            break;
            
        case CHIP_MEDIUM:
            fileName = "icon_chip_blue.png";
            break;
            
        case CHIP_BIG:
            fileName = "icon_chip_green.png";
            break;
            
        default:
            fileName = "icon_chip_red.png";
            break;
    }
    
    // create chip sprite
    this->initWithFile(fileName.c_str());

    // create amount number
    if (isNumberAttached) {
        const char* valueString = CURRENCY_SHORT(chip->getValue());
        float fontSize = GPARAMS().CMM_FONT_SIZE_1;
        if (strlen(valueString) > 3) {
            fontSize = GPARAMS().CMM_FONT_SIZE_0;
        }
        else if (strlen(valueString) > 2) {
            fontSize = GPARAMS().CMM_FONT_SIZE_0 * 1.15f;
        }
        mAmountLabel = CCLabelTTF::create(valueString,
                                          DEFAULT_FONT_NAME,
                                          fontSize);
        mAmountLabel->setPosition(ccp(this->getContentSize().width / 2,
                                      this->getContentSize().height / 2));
//        mAmountLabel->enableShadow(CCSizeMake(0.0, -1.0), 0.5f, 1.0f);
        
        this->addChild(mAmountLabel);
    }
    else {
        mAmountLabel = NULL;
    }
    
    this->setTag(0);
    
    // gray if need
    if (isGrayed) {
        this->setColor(ccGRAY);
        
        if (mAmountLabel != NULL) {
            mAmountLabel->setColor(ccGRAY);
        }
    }
    
    this->setVisible(false);

    return true;
}

void ChipView::moveToPosition(CCPoint startPoint, CCPoint endPoint, float delayTime)
{
    this->stopAllActions();
    this->setScale(1.0);
    this->setPosition(startPoint);
    
    CCDelayTime *delay = CCDelayTime::create(delayTime);
    CCActionInterval *moveTo;
    
    if (this->getTag() == TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET) {
        moveTo = CCMoveTo::create(CHIP_MOVE_DURATION, endPoint);
    }
    else {
        //CCBezierTo
        CCPoint centerPoint = ccpAdd(startPoint, endPoint);
        centerPoint.x = centerPoint.x / 2 - 50;
        centerPoint.y = centerPoint.y / 2 + 50;
        
        ccBezierConfig bezier;
        bezier.endPosition = endPoint;
        bezier.controlPoint_1 = centerPoint;
        bezier.controlPoint_2 = centerPoint;
        moveTo = CCBezierTo::create(CHIP_MOVE_DURATION, bezier);
    }
    
    CCScaleTo *scaleTo = CCScaleTo::create(CHIP_MOVE_DURATION, 0.3f);
    
    CCCallFuncN *stopMoving = CCCallFuncN::create(this,
                                                  callfuncN_selector(ChipView::stoppedAnimatingChip));
    CCCallFuncN *startMoving = CCCallFuncN::create(this,
                                                   callfuncN_selector(ChipView::startAnimatingChip));
    CCSpawn* spawnMove = CCSpawn::create(moveTo, scaleTo, NULL);
    CCSequence* sequenceMove = CCSequence::create(delay, startMoving, spawnMove, stopMoving, NULL);
    
    this->runAction(sequenceMove);
}

void ChipView::stoppedAnimatingChip(CCNode * node)
{
    node->setVisible(false);

    // fire event to GameViewMiddle
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_BETTED_CHIP_STOP_MOVING,
                                                                       node);
    node->setTag(TAG_CHIP_NOT_MOVING);
}

void ChipView::startAnimatingChip(CCNode * node)
{
    node->setVisible(true);

    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_BEETED_CHIP_START_MOVING,
                                                                       node);
}



