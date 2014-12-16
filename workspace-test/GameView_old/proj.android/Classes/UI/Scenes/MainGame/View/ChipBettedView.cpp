//
//  ChipBettedView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "ChipBettedView.h"
#include "Chip.h"
#include "ChipView.h"
#include "ChipBetted.h"
#include "GameParams.h"
#include "GameViewDefine.h"

ChipBettedView::~ChipBettedView()
{
    mSmallChipViews->removeAllObjects();
    mSmallChipViews->release();
    mMediumChipViews->removeAllObjects();
    mMediumChipViews->release();
    mBigChipViews->removeAllObjects();
    mBigChipViews->release();
}

ChipBettedView* ChipBettedView::create(ChipBetted* chipBetted)
{
    ChipBettedView* pRet = new ChipBettedView();
    pRet->initWithChipBetted(chipBetted);
    pRet->autorelease();
    return pRet;
}

bool ChipBettedView::initWithChipBetted(ChipBetted* chipBetted)
{
    // init small chips
    mChipBetted = chipBetted;
    
    int numberChips = mChipBetted->getSmallChips()->size();
    mSmallChipViews = CCArray::create();
    mSmallChipViews->retain();
    mMediumChipViews = CCArray::create();
    mMediumChipViews->retain();
    mBigChipViews = CCArray::create();
    mBigChipViews->retain();
    
    for (int i = 0; i < numberChips; i++) {
        ChipView *smallChipView = ChipView::create(mChipBetted->getSmallChips()->at(i));
        mSmallChipViews->addObject(smallChipView);
        
        ChipView *mediumChipView = ChipView::create(mChipBetted->getMediumChips()->at(i));
        mMediumChipViews->addObject(mediumChipView);
        
        ChipView *bigChipView = ChipView::create(mChipBetted->getBigChips()->at(i));
        mBigChipViews->addObject(bigChipView);
    }
    
    return true;
}

void ChipBettedView::addChipViewsToLayer(CCLayer *gameView, int zOrder)
{
    for (int i = 0; i < mSmallChipViews->count(); i++) {
        gameView->addChild((CCNode*)mSmallChipViews->objectAtIndex(i), zOrder);
        gameView->addChild((CCNode*)mMediumChipViews->objectAtIndex(i), zOrder+1);
        gameView->addChild((CCNode*)mBigChipViews->objectAtIndex(i), zOrder+2);
    }
}

void ChipBettedView::moveCurrentBetChip()
{
    int currentBetChipType = mChipBetted->getCurrentBetChipType();
    
    ChipView *chipView = getAvailableChipView(currentBetChipType);
    
    if (chipView != NULL) {
        CCPoint startPosition = mChipsPosition[currentBetChipType];
        CCPoint endPosition = GPARAMS().MAIN_TOTAL_BET_CHIP_BUTTON_POSITION;

        chipView->setTag(TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET);
        chipView->moveToPosition(startPosition, endPosition, 0);
    }
    
    // disable all bet buttons if touch max bet
    
}

void ChipBettedView::moveBettedChips()
{    
    float delayTime = 0;
    CCPoint endPosition = GPARAMS().MAIN_TOTAL_BET_CHIP_BUTTON_POSITION;
    
    // move big chip
    for (int i = 0; i < mChipBetted->getNumberBigChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_BIG);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET);
        CCPoint startPosition = mChipsPosition[2];
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move medium chip
    for (int i = 0; i < mChipBetted->getNumberMediumChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_MEDIUM);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET);
        CCPoint startPosition = mChipsPosition[1];
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move small chip
    for (int i = 0; i < mChipBetted->getNumberSmallChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_SMALL);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET);
        CCPoint startPosition = mChipsPosition[0];
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
}

void ChipBettedView::cancelBettedChips()
{
    float delayTime = 0;
    CCPoint startPosition = GPARAMS().MAIN_TOTAL_BET_CHIP_BUTTON_POSITION;
    CCPoint endPosition = GPARAMS().MAIN_TOTAL_CHIP_ICON_POSITION;
    
    // move big chip
    for (int i = 0; i < mChipBetted->getNumberBigChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_BIG);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move medium chip
    for (int i = 0; i < mChipBetted->getNumberMediumChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_MEDIUM);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move small chip
    for (int i = 0; i < mChipBetted->getNumberSmallChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_SMALL);
        chipView->setTag(TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
}

void ChipBettedView::rebetLastChips()
{
    moveBettedChips();
}

void ChipBettedView::collectWonChips()
{
    float delayTime = 0;
    CCPoint startPosition = GPARAMS().MAIN_TOTAL_BET_CHIP_BUTTON_POSITION;
    CCPoint endPosition = GPARAMS().MAIN_TOTAL_CHIP_ICON_POSITION;
    
    // move big chip
    for (int i = 0; i < mChipBetted->getNumberBigChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_BIG);
        chipView->setTag(TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move medium chip
    for (int i = 0; i < mChipBetted->getNumberMediumChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_MEDIUM);
        chipView->setTag(TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
    
    // move small chip
    for (int i = 0; i < mChipBetted->getNumberSmallChips(); i++) {
        ChipView *chipView = getAvailableChipView(CHIP_SMALL);
        chipView->setTag(TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP);
        chipView->moveToPosition(startPosition, endPosition, delayTime);
        delayTime += DELAY_MOVE_CHIP_DURATION;
    }
}

ChipView* ChipBettedView::getAvailableChipView(int chipType)
{
//    vector<ChipView*>* chipViews;
    CCArray* chipViews;
    switch (chipType) {
        case CHIP_SMALL:
            chipViews = mSmallChipViews;
            break;
            
        case CHIP_MEDIUM:
            chipViews = mMediumChipViews;
            break;
            
        case CHIP_BIG:
            chipViews = mBigChipViews;
            break;
            
        default:
            chipViews = mSmallChipViews;
            break;
    }
    
    ChipView* chipView = NULL;
    
    for (int i = 0; i < chipViews->count(); i++) {
        chipView = (ChipView*)chipViews->objectAtIndex(i);
        if (chipView->getTag() == 0) {
            break;
        }
    }
    
    return chipView;
}

void ChipBettedView::updateChipsPosition(CCPoint smallPosition, CCPoint mediumPosition,
                                         CCPoint bigPosition)
{
    mChipsPosition[0] = smallPosition;
    mChipsPosition[1] = mediumPosition;
    mChipsPosition[2] = bigPosition;
}
