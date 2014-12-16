//
//  TableView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/29/14.
//
//

#include "TableView.h"

#include "GameParams.h"
#include "ITableViewBuilder.h"
#include "ITableCellView.h"

TableView* TableView::create(CCSize pSize,
                             int pNumberOfRows,
                             int pNumberOfColumns,
                             const CCPoint& pCellPosition,
                             const CCSize& pCellSize,
                             ITableViewBuilder *pTableViewBuilder,
                             CCNode *pContainer) {
    TableView *pRet = new class TableView();
    pRet->autorelease();
    vector<CCSprite*> nodes = vector<CCSprite*>();
    pRet->init(pSize,
               pNumberOfRows,
               pNumberOfColumns,
               pCellPosition,
               pCellSize,
               pTableViewBuilder,
               pContainer);
    pRet->_updateCellPositions();
    pRet->_updateContentSize();
    
    return pRet;
}

bool TableView::init(CCSize pSize,
                     int pNumberOfRows,
                     int pNumberOfColumns,
                     const CCPoint& pCellPosition,
                     const CCSize& pCellSize,
                     ITableViewBuilder *pTableViewBuilder,
                     CCNode *pContainer) {
    mTableViewBuilder = pTableViewBuilder;
    mNumberOfRows = pNumberOfRows;
    mNumberOfColumns = pNumberOfColumns;
    mCellPosition = pCellPosition;
    mCellSize = pCellSize;
    
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
    return mCellSize;
}

CCTableViewCell* TableView::tableCellAtIndex(CCTableView *pTable, unsigned int pIdx)
{
    CCTableViewCell *cell = pTable->dequeueCell();
    
    if((!cell)) {
        cell = mTableViewBuilder->createTableViewCellAt(pIdx);
        cell->setPosition(mCellPosition);
        cell->setContentSize(mCellSize);
    }
    static_cast<ITableCellView*>(cell)->update(pIdx);

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
}

void TableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCTableView::ccTouchEnded(pTouch, pEvent);
}

void TableView::initData() {

}