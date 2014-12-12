//
//  TableLayer.h
//  TomCuaCaOnline
//
//  Created by Ta Van Dung on 9/25/14.
//
//

#ifndef __TomCuaCaOnline__TableLayer__
#define __TomCuaCaOnline__TableLayer__

#include "cocos-ext.h"

#include "CommonLayer.h"
#include "ITableViewBuilder.h"

using namespace cocos2d::extension;

class TableLayer :
public CommonLayer,
public ITableViewBuilder,
public TableViewDelegate {
public:
    virtual void scrollViewDidScroll(ScrollView* pView) {}
    virtual void scrollViewDidZoom(ScrollView* pView) {}
    virtual void tableCellHighlight(TableView* pTable, TableViewCell* pCell);
    virtual void tableCellUnhighlight(TableView* pTable, TableViewCell* pCell);
    virtual void tableCellTouched(TableView* pTable, TableViewCell* pCell);
    virtual void tableCellWillRecycle(TableView* pTable, TableViewCell* pCell);
    
    virtual ITableCellView* createTableViewCellAt(const int &idx) = 0;
};

#endif /* defined(__TomCuaCaOnline__TableLayer__) */