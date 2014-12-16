//
//  PaytableView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/12/14.
//
//

#include "PaytableView.h"
#include "PaytableCellView.h"
#include "Paytable.h"
#include "GameParams.h"

PaytableView::~PaytableView()
{
    mPaytableCellViews->removeAllObjects();
    mPaytableCellViews->release();
}

PaytableView* PaytableView::create(Paytable* pPaytable)
{
    PaytableView* pRet = new PaytableView();
    pRet->init(pPaytable);
    pRet->autorelease();
    
    return pRet;
}

bool PaytableView::init(Paytable* pPaytable)
{
    CCMenu::init();
    this->setAnchorPoint(CCPointZero);
    this->setPosition(CCPointZero);

    mPaytable = pPaytable;
    int numberCells = pPaytable->getPaytableCells()->size() - 1;
    mPaytableCellViews = CCArray::create();
    mPaytableCellViews->retain();
    
    for(int i = 0; i < numberCells; i++) {
        PaytableCellView *paytableCellView;
        paytableCellView =
        PaytableCellView::create(pPaytable->getPaytableCells()->at(i+1),
                                GPARAMS().MAIN_PAYTABLE_CELL_POSITIONS[i]);
        this->addChild(paytableCellView);
        mPaytableCellViews->addObject(paytableCellView);
    }
        
    return true;
}

void PaytableView::highlightWonPayTableCellView(float delayTime)
{
    if (mPaytable->getWonPaytableCell() == NULL) {
        return;
    }
    
    for(int i = 0; i < mPaytableCellViews->count(); i++) {
        PaytableCellView* paytableCellView = (PaytableCellView*)mPaytableCellViews->objectAtIndex(i);
        if(paytableCellView->getPaytableCell() == mPaytable->getWonPaytableCell()) {
            paytableCellView->highlight(delayTime);
            return;
        }
    }
}

void PaytableView::removeHighlightCellView()
{
    if (mPaytable->getWonPaytableCell() == NULL) {
        return;
    }
    
    for(int i = 0; i < mPaytableCellViews->count(); i++) {
        PaytableCellView* paytableCellView = (PaytableCellView*)mPaytableCellViews->objectAtIndex(i);
        if(paytableCellView->getPaytableCell() == mPaytable->getWonPaytableCell()) {
            paytableCellView->removeHighlight();
            return;
        }
    }
}

