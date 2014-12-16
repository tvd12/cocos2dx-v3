//
//  ShoppingMenuItemView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/28/14.
//
//

#include "ShoppingMenuItemView.h"
#include "IapProduct.h"
#include "GameParams.h"

#define LONG_TO_STRING(longValue)      CCString::createWithFormat("%ld", longValue)->getCString()
#define IMAGE_NAME_FOR(longValue) \
    CCString::createWithFormat("pop_shop_main_icon_%ld.png", longValue)->getCString()

ShoppingMenuItemView* ShoppingMenuItemView::create(IapProduct *pProduct,
                                                   CCObject* pTarget,
                                                   SEL_MenuHandler pSelector,
                                                   const string &pNormalImage,
                                                   const string &pSelectedImage) {
    ShoppingMenuItemView *pRet = new ShoppingMenuItemView();
    pRet->autorelease();
    pRet->init(pProduct,
               pTarget,
               pSelector,
               pNormalImage,
               pSelectedImage);

    return pRet;
    
}

bool ShoppingMenuItemView::init(IapProduct *pProduct,
                                CCObject* pTarget,
                                SEL_MenuHandler pSelector,
                                const string &pNormalImage,
                                const string &pSelectedImage) {
    //set variable
    this->mNormalImage = pNormalImage;
    this->mSelectedImage = pSelectedImage;
    this->mIapProduct = pProduct;
    this->mSelector = pSelector;
    this->mTarget = pTarget;
    
    //add components
    this->createNormalSprite();
    this->createSelectedSprite();
    
    //call super's function
    CCMenuItemSprite::initWithNormalSprite(mNormalSprite,
                                           mSelectedSprite,
                                           NULL,
                                           pTarget,
                                           pSelector);
    this->setTag(mIapProduct->getProductType());
    return true;
}

void ShoppingMenuItemView::addLabels(CCNode *pParent) {
    //add packet name label to parent sprite
    CCLabelTTF *packetNameLabel = CCLabelTTF::create(mIapProduct->getPackageName()->c_str(),
                                                     DEFAULT_FONT_NAME,
                                                     GPARAMS().CMM_FONT_SIZE_3);
    packetNameLabel->setPosition(GPARAMS().POP_SHOP_PACKET_NAME_LABEL_POSITION);
    pParent->addChild(packetNameLabel);
    packetNameLabel->enableShadow(CCSizeMake(0.1, -2.0), 0.5f, 2.0f);

    //add packet name label to parent sprite
    float fontSizeEdited = 1.2f;
    if (GPARAMS().isIpadDevice) {
        fontSizeEdited = 1.1f;
    }
    
    CCLabelTTF *chipAmountLabel = CCLabelTTF::create(CURRENCY_LONG(mIapProduct->getChipsAmount()),
                                                     DEFAULT_FONT_NAME,
                                                     GPARAMS().CMM_FONT_SIZE_0*fontSizeEdited);
    chipAmountLabel->setAnchorPoint(CCPoint(0.0f, 0.5f));
    chipAmountLabel->setPosition(GPARAMS().POP_SHOP_CHIP_AMOUNT_LABEL_POSITION);
    pParent->addChild(chipAmountLabel, 1000);
    
    //add packet name label to parent sprite
    CCLabelTTF *vipPointLabel = CCLabelTTF::create(CURRENCY_LONG(mIapProduct->getVipPoint()),
                                                   DEFAULT_FONT_NAME,
                                                   GPARAMS().CMM_FONT_SIZE_0*fontSizeEdited);
    vipPointLabel->setAnchorPoint(CCPoint(0.0f, 0.5f));
    vipPointLabel->setPosition(GPARAMS().POP_SHOP_VIP_POINT_LABEL_POSITION);
    pParent->addChild(vipPointLabel, 1000);
}

void ShoppingMenuItemView::addSprites(CCNode *pParent) {
    //packet chips icon
    CCSprite *mainIconSprite = CCSprite::create(IMAGE_NAME_FOR(mIapProduct->getProductType() + 1));
    mainIconSprite->setPosition(GPARAMS().POP_SHOP_MAIN_ICON_SPRITE_POSITION);
    pParent->addChild(mainIconSprite);
    
    //chip icon
    CCSprite *chipIconSprite = CCSprite::create("pop_shop_chip_icon.png");
    chipIconSprite->setPosition(GPARAMS().POP_SHOP_CHIP_ICON_SPRITE_POSITION);
    pParent->addChild(chipIconSprite);
    
    //star icon
    CCSprite *starIconSprite = CCSprite::create("pop_shop_star_icon.png");
    starIconSprite->setPosition(GPARAMS().POP_SHOP_STAR_ICON_SPRITE_POSITION);
    pParent->addChild(starIconSprite);
}

void ShoppingMenuItemView::addMenu(CCNode *pParent) {
    //normal price sprite
    CCSprite* normalPriceSprite = CCSprite::create("pop_shop_price_button_normal.png");
    CCLabelTTF* normalPriceLabel = CCLabelTTF::create(mIapProduct->getPrice()->c_str(),
                                                  DEFAULT_FONT_NAME,
                                                  GPARAMS().CMM_FONT_SIZE_0*1.2);
    normalPriceLabel->setPosition(CCPoint(normalPriceSprite->getContentSize().width/2,
                                       normalPriceSprite->getContentSize().height/2));
    normalPriceSprite->addChild(normalPriceLabel);

    //selected price sprite
    CCSprite* selectedPriceSprite = CCSprite::create("pop_shop_price_button_active.png");
    CCLabelTTF* selectedPriceLabel = CCLabelTTF::create(mIapProduct->getPrice()->c_str(),
                                                 DEFAULT_FONT_NAME,
                                                 GPARAMS().CMM_FONT_SIZE_0*1.2);
    selectedPriceLabel->setPosition(CCPoint(selectedPriceSprite->getContentSize().width/2,
                                            selectedPriceSprite->getContentSize().height/2));
    selectedPriceSprite->addChild(selectedPriceLabel);
    
    //create menu item
    CCMenuItem *priceMenuItem = CCMenuItemSprite::create(normalPriceSprite,
                                            selectedPriceSprite,
                                            this->mTarget,
                                            mSelector);
    priceMenuItem->setAnchorPoint(CCPointZero);
    priceMenuItem->setPosition(GPARAMS().POP_SHOP_PRICE_MENUITEM_POSITION);
    priceMenuItem->setTag(mIapProduct->getProductType());

    //create menu
    CCMenu *priceMenu = CCMenu::createWithItem(priceMenuItem);
    priceMenu->setPosition(CCPointZero);
    priceMenu->setTouchPriority(kCCMenuHandlerPriority - 103);
    
    pParent->addChild(priceMenu);
    
}


void ShoppingMenuItemView::createNormalSprite() {
    mNormalSprite = CCSprite::create(mNormalImage.c_str());
    
    //add label
    addLabels(mNormalSprite);
    
    //add sprite
    addSprites(mNormalSprite);
    
    //add menu
    addMenu(mNormalSprite);
}

void ShoppingMenuItemView::createSelectedSprite() {
    mSelectedSprite = CCSprite::create(mSelectedImage.c_str());
    
    //add label
    addLabels(mSelectedSprite);
    
    //add sprite
    addSprites(mSelectedSprite);
    
    //add menu
    addMenu(mSelectedSprite);
}