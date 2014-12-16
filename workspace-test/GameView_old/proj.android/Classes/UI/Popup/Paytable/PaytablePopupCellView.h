//
//  PaytablePopupCellView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/19/14.
//
//

#ifndef __DragonVideoPoker__PaytablePopupCellView__
#define __DragonVideoPoker__PaytablePopupCellView__

#include "cocos2d.h"

using namespace cocos2d;

class PaytableCell;
class PaytablePopupCellView : public CCMenuItemSprite {
public:
    static PaytablePopupCellView* create(PaytableCell* pPaytableCell,
                                         CCObject* target,
                                         SEL_MenuHandler selector);
    static PaytablePopupCellView* createEmptyMenuItem(const CCPoint &pPosition);
    
    bool init(PaytableCell* pPaytableCell,
              CCObject* target,
              SEL_MenuHandler selector);
    CC_SYNTHESIZE_READONLY(PaytableCell*, mPaytableCell, PaytableCell);
private:
    void createSprites();
    CCSprite *mNormalSprite;
    CCSprite *mSelectedSprite;
};


#endif /* defined(__DragonVideoPoker__PaytablePopupCellView__) */
