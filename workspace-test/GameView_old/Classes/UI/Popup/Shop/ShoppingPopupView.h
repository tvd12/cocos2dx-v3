//
//  ShoppingPopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/28/14.
//
//

#ifndef __DragonVideoPoker__ShoppingPopupView__
#define __DragonVideoPoker__ShoppingPopupView__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopUpLayer.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class ShoppingMenuItemView;
class ProductPriceList;
class WaitingLayer;

class ShoppingPopupView : public PopUpLayer
{
public:
    ShoppingPopupView();
        
    virtual bool init();
    
    CREATE_FUNC(ShoppingPopupView);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    CC_SYNTHESIZE_READONLY(vector<CCMenuItem*>*, mShoppingMenuItems, ShoppingMenuItems);
    
    ~ShoppingPopupView();

protected:
    virtual void addSprites();
    virtual void addMenuItems();

private:
    void shoppingMenuItemCallback(CCObject *pSender);
    
    void addWaitingLayerWithType(int type);
    void removeWaitingLayer(int type);
    
    void onPurchaseFinished(CCObject* object);
    
    WaitingLayer* mWaitingLayer;

};

#endif /* defined(__DragonVideoPoker__ShoppingPopupView__) */
