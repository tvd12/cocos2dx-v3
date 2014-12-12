//
//  TableLayer.cpp
//  TomCuaCaOnline
//
//  Created by Ta Van Dung on 9/25/14.
//
//

#include "TableLayer.h"
#include "ITableCellView.h"

void TableLayer::tableCellTouched(TableView *pTableView, TableViewCell *pCell) {
    CCLOG("cell touched at index: %zi", pCell->getIdx());
    static_cast<ITableCellView*>(pCell)->processWhenTouched();
}

void TableLayer::tableCellHighlight(TableView* pTableView, TableViewCell* pCell){
    CCLOG("cell highlight at index: %zi", pCell->getIdx());
    static_cast<ITableCellView*>(pCell)->processWhenHighlight();
}

void TableLayer::tableCellUnhighlight(TableView* pTable, TableViewCell* pCell) {
    CCLOG("cell unhighlight at index: %zi", pCell->getIdx());
    static_cast<ITableCellView*>(pCell)->processWhenUnhighlight();
}

void TableLayer::tableCellWillRecycle(TableView *pTable, TableViewCell *pCell) {
    CCLOG("cell will recycle at index: %zi", pCell->getIdx());
    static_cast<ITableCellView*>(pCell)->processWhenWillRecycle();
}