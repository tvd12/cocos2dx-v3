//
//  ShoppingMenuItemView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/28/14.
//
//

#ifndef __DragonVideoPoker__ShoppingMenuItemView__
#define __DragonVideoPoker__ShoppingMenuItemView__

#include <string>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class IapProduct;

class ShoppingMenuItemView :  public CCMenuItemSprite {
    
public:
    
    static ShoppingMenuItemView* create(IapProduct *pProduct,
                                        CCObject* pTarget,
                                        SEL_MenuHandler pSelector,
                                        const string &pNormalImage = "pop_shop_bg_blue_normal.png",
                                        const string &pSelectedImage = "pop_shop_bg_blue_active.png");
    bool init(IapProduct *pProduct,
              CCObject* pTarget,
              SEL_MenuHandler pSelector,
              const string &pNormalImage = "pop_shop_bg_blue_normal.png",
              const string &pSelectedImage = "pop_shop_bg_blue_active.png");
    
    CC_SYNTHESIZE_READONLY(IapProduct*, mIapProduct, IapProduct);
    
private:
    
    void createNormalSprite();
    void createSelectedSprite();
    
    void addLabels(CCNode* pParent);
    void addSprites(CCNode* pParent);
    void addMenu(CCNode* pParent);
    
    CCSprite *mNormalSprite;
    CCSprite *mSelectedSprite;
    
    SEL_MenuHandler mSelector;
    CCObject* mTarget;
    
    string mNormalImage;
    string mSelectedImage;
    
};

#endif /* defined(__DragonVideoPoker__ShoppingMenuItemView__) */
