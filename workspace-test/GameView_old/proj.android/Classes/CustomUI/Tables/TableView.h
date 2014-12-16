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
using namespace cocos2d::extension;

class TableView :
public CCTableView,
public CCTableViewDataSource {
public:
    static TableView* create(vector<CCSprite*> &pNodes,
                                     CCSize pSize,
                                     int pNumberOfRows,
                                     int pNumberOfColumns,
                                     CCNode *pContainer = NULL);
    
    virtual bool init(vector<CCSprite*> &pNodes,
                      CCSize pSize,
                      int pNumberOfRows,
                      int pNumberOfColumns,
                      CCNode *pContainer = NULL);
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void addToParent(CCNode *pParent, const CCPoint &pPosition);
    void setMenus(vector<CCMenu*> &pMenus) {mMenus = pMenus;}
    
protected:
    vector<CCMenu*> mMenus;
    vector<CCMenuItem*> mSelectedMenuItems;
    vector<CCSprite*> mSprites;
    vector<CCNode*> mNodes;
    
    int mNumberOfRows;
    int mNumberOfColumns;
    
private:
    void initData();
};

#endif /* defined(__DragonVideoPoker__TableView__) */
