//
//  PaytablePopupCellView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/19/14.
//
//

#include <string>

#include "PaytablePopupCellView.h"
#include "PaytableCell.h"
#include "GameParams.h"

using namespace std;

PaytablePopupCellView* PaytablePopupCellView::create(PaytableCell *pPaytableCell,
                                                     CCObject* pTarget,
                                                     SEL_MenuHandler pSelector) {
    PaytablePopupCellView* pRet = new PaytablePopupCellView();
    pRet->init(pPaytableCell, pTarget, pSelector);
    pRet->autorelease();
    return pRet;
}

bool PaytablePopupCellView::init(PaytableCell* pPaytableCell,
                                 CCObject* pTarget,
                                 SEL_MenuHandler pSelector) {
    this->mPaytableCell = pPaytableCell;
    createSprites();
    CCMenuItemSprite::initWithNormalSprite(mNormalSprite,
                                           mSelectedSprite,
                                           NULL,
                                           pTarget,
                                           pSelector);
    return true;
}

void PaytablePopupCellView::createSprites()
{
    mNormalSprite = CCSprite::create("paytable_text_bg.png");
    string handNameString = mPaytableCell->getHandName();
    CCLabelTTF *handName = CCLabelTTF::create(handNameString.c_str(),
                                              DEFAULT_FONT_NAME,
                                              GPARAMS().CMM_FONT_SIZE_3);
    handName->setPosition(CCPoint(mNormalSprite->getContentSize().width/2,
                                  mNormalSprite->getContentSize().height/2));
    mNormalSprite->addChild(handName, 100);
    
    mSelectedSprite = CCSprite::create("paytable_text_bg.png");
    CCSprite *activeSprite = CCSprite::create("paytable_text_bg_active.png");
    activeSprite->setPosition(CCPoint(mSelectedSprite->getContentSize().width/2,
                                      mSelectedSprite->getContentSize().height/2));
    CCLabelTTF *handNameActive = CCLabelTTF::create(handNameString.c_str(),
                                                    DEFAULT_FONT_NAME,
                                                    GPARAMS().CMM_FONT_SIZE_3);
    handNameActive->setPosition(CCPoint(mNormalSprite->getContentSize().width/2,
                                        mNormalSprite->getContentSize().height/2));
    
    if (GPARAMS().isIpadDevice) {
        handNameActive->setScale(0.9f);
        handName->setScale(0.9f);
    }
    mSelectedSprite->addChild(handNameActive);
    mSelectedSprite->addChild(activeSprite);
}

PaytablePopupCellView* PaytablePopupCellView::createEmptyMenuItem(const CCPoint &pPosition) {
    CCSprite* normalSprite = CCSprite::create("paytable_text_bg.png");
    CCLabelTTF *emptyLabel = CCLabelTTF::create("Empty",
                                              DEFAULT_FONT_NAME,
                                              GPARAMS().CMM_FONT_SIZE_3);
    emptyLabel->setPosition(CCPoint(normalSprite->getContentSize().width/2,
                                    normalSprite->getContentSize().height/2));
    emptyLabel->setColor(ccGRAY);
    
    normalSprite->addChild(emptyLabel);

    CCSprite* selectedSprite = CCSprite::create("paytable_text_bg.png");
    CCLabelTTF *emptyLabelSelected = CCLabelTTF::create("Empty",
                                                DEFAULT_FONT_NAME,
                                                GPARAMS().CMM_FONT_SIZE_3);
    emptyLabelSelected->setPosition(CCPoint(selectedSprite->getContentSize().width/2,
                                    selectedSprite->getContentSize().height/2));
    emptyLabelSelected->setColor(ccGRAY);
    
    selectedSprite->addChild(emptyLabelSelected);
    
    PaytablePopupCellView *pRet = new PaytablePopupCellView();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, NULL, NULL, NULL);
    pRet->autorelease();
    pRet->setPosition(pPosition);
    
    return pRet;
}