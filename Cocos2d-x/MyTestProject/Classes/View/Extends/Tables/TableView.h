//
//  TableView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/29/14.
//
//

#ifndef __DragonVideoPoker__TableView__
#define __DragonVideoPoker__TableView__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;

//class ATableViewCell;
class ITableViewBuilder;

namespace gameview {
    namespace ext {

        class TableView :
        public cocos2d::extension::TableView,
        public extension::TableViewDataSource {
        public:
            
            static TableView* create(Size pSize,
                                     int pNumberOfRows,
                                     int pNumberOfColumns,
                                     const Point& pCellPosition,
                                     const Size& pCellSize,
                                     ITableViewBuilder *pContainerView,
                                     Node *pContainer = NULL);
            
            virtual bool init(Size pSize,
                              int pNumberOfRows,
                              int pNumberOfColumns,
                              const Point& pCellPosition,
                              const Size& pCellSize,
                              ITableViewBuilder *pContainerView,
                              Node *pContainer = NULL);
            
            virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
            virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table,
                                                                        ssize_t idx);
            
            virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
            
            void addToParent(Node *pParent, const Point &pPosition);
            
            CC_SYNTHESIZE(int, mNumberOfRows, NumberOfRows);
            CC_SYNTHESIZE(ITableViewBuilder*, mTableViewBuilder, TableViewBuilder);
            
        protected:
            
            int mNumberOfColumns;
            
            Point mCellPosition;
            Size mCellSize;
            
        private:
            void initData();
        };
    }
}

#endif /* defined(__DragonVideoPoker__TableView__) */
