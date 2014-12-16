//
//  PaytablePopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/19/14.
//
//

#ifndef __DragonVideoPoker__PaytablePopupView__
#define __DragonVideoPoker__PaytablePopupView__

#include <map>

#include "cocos2d.h"
#include "PopUpLayer.h"

using namespace std;
using namespace cocos2d;

class Paytable;
class PaytablePopupCellView;
class CardView;

class PaytablePopupView : public PopUpLayer {
public:
    PaytablePopupView();
    static PaytablePopupView* create(Paytable* pPaytable,
                                     const int pCurrentSelectedHand,
                                     string pBackgroundImage = "pop_common_bg.png",
                                     string pExitNormalImage = "pop_common_close_normal.png",
                                     string pExitSelectedImage = "pop_common_close_active.png"
                              );
    
    virtual bool init(Paytable* pPaytable,
                      const int pCurrentSelectedHand,
                      string pBackgroundImage,
                      string pExitNormalImage = "pop_common_close_normal.png",
                      string pExitSelectedImage = "pop_common_close_active.png"
                      );
    ~PaytablePopupView();
protected:
    virtual void addSprites();
    virtual void addMenuItems();
    virtual void addLabels();
private:
    void handMenuItemCallback(CCObject *pSender);
    void addCardSprites();
    void showExampleCards();
    void setPayoutPosition();
    
    CCSprite *mCardViewContainer;
    CCSprite *mPayoutSprite;
    
    CCLabelTTF *mHandMultipleLabel;
    
    PaytablePopupCellView *mCurrentSelectedCell;
    
    int mCurrentSelectedHand;
    
    Paytable* mPaytable;
    
    vector<PaytablePopupCellView*>* mPaytablePopupCellViews;
    
    map<const int, vector<CardView*> > mCardViewMap;
};

#endif /* defined(__DragonVideoPoker__PaytablePopupView__) */
