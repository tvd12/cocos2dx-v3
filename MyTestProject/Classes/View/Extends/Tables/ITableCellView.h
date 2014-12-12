//
//  ITableCellView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 8/1/14.
//
//

#ifndef __DragonVideoPoker__ITableCellView__
#define __DragonVideoPoker__ITableCellView__

#include "cocos-ext.h"

using namespace cocos2d::extension;

class ITableCellView : public TableViewCell {
public:
    ITableCellView(const int &idx = 0) : TableViewCell() {
    }
    virtual bool init(const int &idx = 0) {
        mIndex = idx;
        this->addSprites();
        this->addLabels();
        this->addMenus();
        this->addMenuItems();
        
        return true;
    }
    virtual void update(const int &idx) {
        updateSprites(idx);
        updateLabels(idx);
        updateMenuItems(idx);
    }
    
    /**
     * @method process
     * This method will be called when user touch in cell
     */
    virtual void processWhenTouched() {}
    virtual void processWhenHighlight() {}
    virtual void processWhenUnhighlight() {}
    virtual void processWhenWillRecycle() {}
    
    inline const int getIndex() { return mIndex; }
    
protected:
    virtual void addSprites() {}
    virtual void addLabels() {}
    virtual void addMenuItems() {}
    virtual void addMenus() {}
    
    virtual void updateSprites(const int &idx) {}
    virtual void updateLabels(const int &idx) {}
    virtual void updateMenuItems(const int &idx) {}
    
    int mIndex;
};
#endif /* defined(__DragonVideoPoker__ITableCellView__) */
