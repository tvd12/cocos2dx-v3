//
//  ShoppingPopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/28/14.
//  Thank PrinceJohn, http://www.cocos2d-x.org/forums/18/topics/17298
//
//

#include "ShoppingPopupView.h"
#include "ShoppingMenuItemView.h"
#include "GameParams.h"
#include "VisibleRect.h"
#include "ShoppingTableView.h"
#include "ShoppingMenuView.h"
#include "SoundManager.h"

#include "TdgServer.h"
#include "IapProduct.h"
#include "GameIAPHelper.h"

#include "WaitingLayer.h"


ShoppingPopupView::ShoppingPopupView() :
mShoppingMenuItems(new vector<CCMenuItem*>()){
    
}

ShoppingPopupView::~ShoppingPopupView()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool ShoppingPopupView::init()
{
    PopUpLayer::init("pop_common_bg.png",
                     "pop_common_close_normal.png",
                     "pop_common_close_active.png",
                     GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    setBackgroundPosition(VisibleRect::center());
    
    mWaitingLayer = NULL;
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(ShoppingPopupView::
                                                                                     onPurchaseFinished),
                                                                  NOTIFICATION_GOT_IAP_FINISHED,
                                                                  NULL);
    
    return true;
}

void ShoppingPopupView::addSprites() {
    PopUpLayer::addSprites();
    
    CCSprite* header = CCSprite::create("pop_shop_header.png");
    header->setPosition(GPARAMS().POP_COMMON_HEADER_POSITION);
    mBackgroundSprite->addChild(header);
}

void ShoppingPopupView::addMenuItems() {
    
    //call super function
    PopUpLayer::addMenuItems();
    
    vector<CCMenu*> priceListMenus = vector<CCMenu*>(3);
    
    //create shopping menu item
    for(int i = 0 ; i < IAPLIST()->size() ; i++) {
        IapProduct *product = IAPLIST()->at(i);
        
        SEL_MenuHandler selector = menu_selector(ShoppingPopupView::shoppingMenuItemCallback);
        CCMenuItem* shoppingMenuItem;
        if(i < 5) {
            // normal package
            shoppingMenuItem = ShoppingMenuItemView::create(product,
                                                            this,
                                                            selector);
        }
        else {
            //big package
            shoppingMenuItem = ShoppingMenuItemView::create(product,
                                                            this,
                                                            selector,
                                                            "pop_shop_bg_orange_normal.png",
                                                            "pop_shop_bg_orange_active.png");
        }
        shoppingMenuItem->setPosition(GPARAMS().POP_SHOP_PRODUCT_MENUITEMS_POSITIONS[i % 2]);
        mShoppingMenuItems->push_back(shoppingMenuItem);
        
        if(priceListMenus[i/2] == NULL) {
            priceListMenus[i/2] = ShoppingMenuView::create();
            priceListMenus[i/2]->setAnchorPoint(CCPointZero);
            priceListMenus[i/2]->setPosition(CCPointZero);
            priceListMenus[i/2]->setTouchPriority(kCCMenuHandlerPriority - 102);
            priceListMenus[i/2]->setContentSize(GPARAMS().POP_SHOP_TABLEVIEW_CELL_SIZE);
        }
        
        priceListMenus[i/2]->addChild(mShoppingMenuItems->at(i));
    }
    
    //create table view
    ShoppingTableView *table = ShoppingTableView::create(priceListMenus,
                                                         GPARAMS().POP_SHOP_TABLEVIEW_SIZE);
    table->setTouchPriority(kCCMenuHandlerPriority - 109);
    
    table->addToParent(mBackgroundSprite, GPARAMS().POP_SHOP_TABLEVIEW_POSITION);
    
}

bool ShoppingPopupView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    
    return PopUpLayer::ccTouchBegan(pTouch, pEvent);
    
}

void ShoppingPopupView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
   
}

void ShoppingPopupView::shoppingMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    CCMenuItem* menuItem = (CCMenuItem*)pSender;
    
    GameIAPHelper::sharedHelper()->purchaseItem(menuItem->getTag());

    // add waiting layer
    this->addWaitingLayerWithType(kWaitingLayerMustWait);
}

#pragma mark - Waiting Layer

void ShoppingPopupView::addWaitingLayerWithType(int type)
{
    // remove last waiting layer
    removeWaitingLayer(-1);
    
    // create new one
    mWaitingLayer = WaitingLayer::createWithType(type);
    this->addChild(mWaitingLayer, WAITING_POP_UP_ORDER);
}

void ShoppingPopupView::removeWaitingLayer(int type)
{
    if (mWaitingLayer != NULL) {
        if (type == -1 || type == mWaitingLayer->getWaitingType()) {
            mWaitingLayer->removeLayer();
            mWaitingLayer = NULL;
        }
    }
}

void ShoppingPopupView::onPurchaseFinished(CCObject* object)
{
    removeWaitingLayer(-1);
}


