//
//  ShoppingTableView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/6/14.
//
//

#include "ShoppingTableView.h"

ShoppingTableView* ShoppingTableView::create(vector<CCMenu*> &pMenus, CCSize pSize, CCNode *pContainer) {
    ShoppingTableView *pRet = new class ShoppingTableView();
    pRet->autorelease();
    pRet->init(pMenus, pSize, pContainer);
    pRet->_updateCellPositions();
    pRet->_updateContentSize();
    
    return pRet;
}

bool ShoppingTableView::init(vector<CCMenu*> &pMenus, CCSize pSize, CCNode *pContainer) {
    
    mMenus = pMenus;
    
    CCTableView::initWithViewSize(pSize, pContainer);
    CCTableView::setDataSource(this);
    CCTableView::setDirection(kCCScrollViewDirectionVertical);
    CCTableView::setVerticalFillOrder(kCCTableViewFillTopDown);
    CCTableView::setAnchorPoint(CCPointZero);
    
    return true;
}

void ShoppingTableView::tableCellTouched(CCTableView *ptable, CCTableViewCell *pCell) {
    CCLOG("cell touched at index: %i", pCell->getIdx());
}

CCSize ShoppingTableView::tableCellSizeForIndex(CCTableView *pTable, unsigned int pIdx) {
    return mMenus[pIdx]->getContentSize();
}

CCTableViewCell* ShoppingTableView::tableCellAtIndex(CCTableView *pTable, unsigned int pIdx) {
    CCTableViewCell *cell = pTable->dequeueCell();
    if(!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        cell->addChild(mMenus[pIdx]);
    }
    
    return cell;
}

unsigned int ShoppingTableView::numberOfCellsInTableView(CCTableView *pTable) {
    return mMenus.size();
}

void ShoppingTableView::addToParent(CCNode *pParent, const CCPoint &pPosition) {
    CCTableView::setPosition(pPosition);
    pParent->addChild(this);
    this->reloadData();
}

void ShoppingTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    
    CCTableView::ccTouchMoved(pTouch, pEvent);
    
    for(int i = 0 ; i < mMenus.size() ; i++) {
        for(int k = 0 ; k < mMenus[i]->getChildren()->count() ; k++) {
            CCMenuItem *selectedMenuItem =
            static_cast<CCMenuItem*>(mMenus[i]->getChildren()->objectAtIndex(k));
            if(selectedMenuItem->isSelected()) {
                selectedMenuItem->unselected();
                selectedMenuItem->setEnabled(false);
                
                mSelectedMenuItems.push_back(selectedMenuItem);
            }
        }
    }
}

void ShoppingTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
    CCTableView::ccTouchEnded(pTouch, pEvent);
    
    for(int i = 0 ; i < mSelectedMenuItems.size() ; i++) {
        if(mSelectedMenuItems[i] != NULL && !mSelectedMenuItems[i]->isEnabled()) {
            mSelectedMenuItems[i]->setEnabled(true);
        }
    }
}