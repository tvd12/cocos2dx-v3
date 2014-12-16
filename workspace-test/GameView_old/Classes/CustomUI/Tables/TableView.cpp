//
//  TableView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/29/14.
//
//

#include "TableView.h"

#include "GameParams.h"

TableView* TableView::create(vector<CCSprite*> &pNodes,
                             CCSize pSize,
                             int pNumberOfRows,
                             int pNumberOfColumns,
                             CCNode *pContainer) {
    TableView *pRet = new class TableView();
    pRet->autorelease();
    pRet->init(pNodes, pSize, pNumberOfRows, pNumberOfColumns, pContainer);
    pRet->_updateCellPositions();
    pRet->_updateContentSize();
    
    return pRet;
}

bool TableView::init(vector<CCSprite*> &pNodes,
                     CCSize pSize,
                     int pNumberOfRows,
                     int pNumberOfColumns,
                     CCNode *pContainer) {
    
    mSprites = pNodes;
    mNumberOfRows = pNumberOfRows;
    mNumberOfColumns = pNumberOfColumns;
    
    initData();
    
    CCTableView::initWithViewSize(pSize, pContainer);
    CCTableView::setDataSource(this);
    CCTableView::setDirection(kCCScrollViewDirectionVertical);
    CCTableView::setVerticalFillOrder(kCCTableViewFillTopDown);
    CCTableView::setAnchorPoint(CCPointZero);
    
    return true;
}

void TableView::tableCellTouched(CCTableView *ptable, CCTableViewCell *pCell) {
    CCLOG("cell touched at index: %i", pCell->getIdx());
}

CCSize TableView::tableCellSizeForIndex(CCTableView *pTable, unsigned int pIdx) {
    return mNodes[pIdx]->getContentSize();
}

CCTableViewCell* TableView::tableCellAtIndex(CCTableView *pTable, unsigned int pIdx) {
    CCTableViewCell *cell = pTable->dequeueCell();
    if(!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        cell->addChild(mNodes[pIdx]);
    }
    
    return cell;
}

unsigned int TableView::numberOfCellsInTableView(CCTableView *pTable) {
    return mNumberOfRows;
}

void TableView::addToParent(CCNode *pParent, const CCPoint &pPosition) {
    CCTableView::setPosition(pPosition);
    pParent->addChild(this);
    this->reloadData();
}

void TableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    
    CCTableView::ccTouchMoved(pTouch, pEvent);
    
//    for(int i = 0 ; i < mMenus.size() ; i++) {
//        for(int k = 0 ; k < mMenus[i]->getChildren()->count() ; k++) {
//            CCMenuItem *selectedMenuItem =
//            static_cast<CCMenuItem*>(mMenus[i]->getChildren()->objectAtIndex(k));
//            if(selectedMenuItem->isSelected()) {
//                selectedMenuItem->unselected();
//                selectedMenuItem->setEnabled(false);
//                
//                mSelectedMenuItems.push_back(selectedMenuItem);
//            }
//        }
//    }
}

void TableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
    CCTableView::ccTouchEnded(pTouch, pEvent);
    
//    for(int i = 0 ; i < mSelectedMenuItems.size() ; i++) {
//        if(mSelectedMenuItems[i] != NULL && !mSelectedMenuItems[i]->isEnabled()) {
//            mSelectedMenuItems[i]->setEnabled(true);
//        }
//    }
}

void TableView::initData() {
    mNodes = vector<CCNode*>(mNumberOfRows);
    for(int i = 0 ; i < mNodes.size() ; i++) {
        mNodes[i] = CCSprite::create();
        for(int k = 0 ; k < mNumberOfColumns ; k++) {
            mNodes[i]->addChild(mSprites[i*mNumberOfRows + k]);
            mNodes[i]->setPosition(GPARAMS().POP_AVATARS_CELL_POSITION);
            mNodes[i]->setContentSize(GPARAMS().POP_AVATARS_CONTAINER_TABLE_CELL_SIZE);
        }
    }
}