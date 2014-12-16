//
//  PaytableCellView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/14/14.
//
//

/***
 elements:
 
 */

#ifndef __DragonVideoPoker__PaytableCellView__
#define __DragonVideoPoker__PaytableCellView__

#include "cocos2d.h"

using namespace cocos2d;

class PaytableCell;

class PaytableCellView : public CCMenuItemImage {
public:
    static PaytableCellView* create(PaytableCell *pPaytableCell, const CCPoint pPosition);
    bool init(PaytableCell *pPaytableCell, const CCPoint pPosition);
    void highlight(float delayTime);
    void removeHighlight();

    CC_SYNTHESIZE_READONLY(PaytableCell*, mPaytableCell, PaytableCell);
    
private:
    //click to show pay table details
    void selectHandMenuCallback(CCObject *pSender);
    
    void addSprites();
    
    CCLabelTTF *mHandNameLabel;
    CCLabelTTF *mHandMultipleLabel;
    CCSprite *mHighlightSprite;
};

#endif /* defined(__DragonVideoPoker__PaytableCellView__) */
