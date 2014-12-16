 //
//  PaytableCellView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/14/14.
//
//

#include <string>

#include "PaytableCellView.h"
#include "PaytableCell.h"
#include "GameParams.h"
#include "PaytablePopupView.h"
#include "GameView.h"
#include "GameModel.h"
#include "PaytableView.h"
#include "VideoPokerDefine.h"
#include "SoundManager.h"


using namespace std;

PaytableCellView* PaytableCellView::create(PaytableCell* pPaytableCell,
                                           const CCPoint pPosition) {
    PaytableCellView *pRet = new PaytableCellView();
    pRet->init(pPaytableCell, pPosition);
    pRet->autorelease();
    return pRet;
}

/**
 * @function init: init 2 menu item (difference color only)
 */

bool PaytableCellView::init(PaytableCell* pPaytableCell, const CCPoint pPosition)
{
    mPaytableCell = pPaytableCell;

    CCMenuItemImage::initWithNormalImage("text_box_normal.png",
                                         "text_box_normal.png",
                                         NULL,
                                         this,
                                         menu_selector(PaytableCellView::selectHandMenuCallback));
    this->setPosition(pPosition);
    this->setTag(mPaytableCell->getHandType());

    if (mPaytableCell->getHandType() != PAYTABLE_EMPTY) {
        addSprites();
        removeHighlight();
    }
    
    return true;
}

void PaytableCellView::addSprites()
{
    int yCenter = this->getContentSize().height / 2;
    int xCenter = this->getContentSize().width / 2;
    float xDelta = GPARAMS().MAIN_PAYTABLE_CELL_NAME_DELTA;
    
    // create highlight
    mHighlightSprite = CCSprite::create("text_box_active.png");
    mHighlightSprite->setPosition(CCPoint(xCenter, yCenter));
    this->addChild(mHighlightSprite);

    // add labels
    //create hand name and left alignment
    mHandNameLabel = CCLabelTTF::create(mPaytableCell->getHandName().c_str(),
                                        DEFAULT_FONT_NAME,
                                        GPARAMS().CMM_FONT_SIZE_1);

    //add hand name to highlight background
    this->addChild(mHandNameLabel);
    mHandNameLabel->setAnchorPoint(CCPoint(0, 0.5f));
    mHandNameLabel->setPosition(CCPoint(xCenter - xDelta,
                                        yCenter));

    //create hand multiple string
    const char* handMultiple =
    CCString::createWithFormat("x%d", mPaytableCell->getHandMultiple())->getCString();
    
    //create hand multiple
    mHandMultipleLabel = CCLabelTTF::create(handMultiple,
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_1);
    this->addChild(mHandMultipleLabel);
    mHandMultipleLabel->setAnchorPoint(CCPoint(1, 0.5f));
    mHandMultipleLabel->setPosition(CCPoint(xCenter + xDelta,
                                            yCenter));
}

void PaytableCellView::highlight(float delayTime)
{
    // create animation
    mHighlightSprite->setVisible(true);
    CCDelayTime* delay = CCDelayTime::create(delayTime);
    CCFadeOut *fadeOut = CCFadeOut::create(0.1f);
    CCFadeIn *fadeIn = CCFadeIn::create(0.1f);
    CCSequence *sequenceHighlight = CCSequence::create(fadeOut, fadeIn, NULL);
    CCRepeat *repeat = CCRepeat::create(sequenceHighlight, 5);
    CCSequence* sequence = CCSequence::create(delay, repeat, NULL);
    mHighlightSprite->runAction(sequence);
    
    // update color to label
    mHandNameLabel->setColor(ccWHITE);
    mHandMultipleLabel->setColor(ccWHITE);
}

void PaytableCellView::removeHighlight() {
    mHighlightSprite->setVisible(false);
    mHandNameLabel->setColor(ccGRAY);
    mHandMultipleLabel->setColor(ccGRAY);
}

void PaytableCellView::selectHandMenuCallback(CCObject *pSender)
{
    CCNode *sender = static_cast<CCNode*>(pSender);
    if(sender->getTag() == PAYTABLE_EMPTY) {
        return;
    }
    
    SOUND().playSound(SOUND_BUTTON_CLICK);
    
    PaytableView *paytableView = static_cast<PaytableView*>(this->getParent());
    PaytablePopupView* paytablePopup =
    PaytablePopupView::create(paytableView->getPaytable(), sender->getTag());
    paytableView->getParent()->getParent()->addChild(paytablePopup);
}
