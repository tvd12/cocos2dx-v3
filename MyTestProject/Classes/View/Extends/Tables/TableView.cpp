//
//  TableView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/29/14.
//
//

#include "TableView.h"

#include "ITableViewBuilder.h"
#include "ITableCellView.h"

using namespace gameview::ext;

gameview::ext::TableView* gameview::ext::TableView::create(Size pSize,
                             int pNumberOfRows,
                             int pNumberOfColumns,
                             const Point& pCellPosition,
                             const Size& pCellSize,
                             ITableViewBuilder *pTableViewBuilder,
                             Node *pContainer) {
    gameview::ext::TableView *pRet = new gameview::ext::TableView();
    pRet->autorelease();
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

bool gameview::ext::TableView::init(Size pSize,
                     int pNumberOfRows,
                     int pNumberOfColumns,
                     const Point& pCellPosition,
                     const Size& pCellSize,
                     ITableViewBuilder *pTableViewBuilder,
                     Node *pContainer) {
    mTableViewBuilder = pTableViewBuilder;
    mNumberOfRows = pNumberOfRows;
    mNumberOfColumns = pNumberOfColumns;
    mCellPosition = pCellPosition;
    mCellSize = pCellSize;
    
    initData();
    
    extension::TableView::initWithViewSize(pSize, pContainer);
    extension::TableView::setDataSource(this);
    extension::TableView::setDirection(ScrollView::Direction::VERTICAL);
    extension::TableView::setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    extension::TableView::setAnchorPoint(Point::ZERO);
    
    return true;
}

Size gameview::ext::TableView::tableCellSizeForIndex(TableView *pTable, ssize_t pIdx) {
    return mCellSize;
}

cocos2d::extension::TableViewCell* gameview::ext::TableView::tableCellAtIndex(cocos2d::extension::TableView *pTable,
                                                                              ssize_t pIdx)
{
    TableViewCell *cell = pTable->dequeueCell();
    
    if((!cell)) {
        cell = mTableViewBuilder->createTableViewCellAt(pIdx);
        cell->setPosition(mCellPosition);
        cell->setContentSize(mCellSize);
    }
    static_cast<ITableCellView*>(cell)->update(pIdx);

    return cell;
}

ssize_t gameview::ext::TableView::numberOfCellsInTableView(cocos2d::extension::TableView *pTable) {
    return mNumberOfRows;
}

void gameview::ext::TableView::addToParent(Node *pParent, const Point &pPosition) {
    TableView::setPosition(pPosition);
    pParent->addChild(this);
    this->reloadData();
}

void gameview::ext::TableView::initData() {

}