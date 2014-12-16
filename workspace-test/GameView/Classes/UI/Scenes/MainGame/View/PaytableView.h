//
//  PaytableView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/12/14.
//
//

#ifndef __DragonVideoPoker__PaytableView__
#define __DragonVideoPoker__PaytableView__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Paytable;
class PaytableCellView;

class PaytableView  : public CCMenu {
public:
    static PaytableView* create(Paytable* pPaytable);
    bool init(Paytable* pPaytable);
    
    void highlightWonPayTableCellView(float delayTime);
    void removeHighlightCellView();
    
    CC_SYNTHESIZE_READONLY(Paytable*, mPaytable, Paytable);
    
    ~PaytableView();
    
private:
    
    CCArray* mPaytableCellViews;
};

#endif /* defined(__DragonVideoPoker__PaytableView__) */
