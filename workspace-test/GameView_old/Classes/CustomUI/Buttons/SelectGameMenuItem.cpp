//
//  SelectGameMenuItem.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#include "SelectGameMenuItem.h"
#include "SelectGameMenuSprite.h"

#include "TdgServer.h"
#include "UserInfo.h"
#include "RoomInfo.h"


SelectGameMenuItem* SelectGameMenuItem::createWithIndex(const int index,
                                                        CCObject* target,
                                                        SEL_MenuHandler selector) {
    SelectGameMenuItem *menuItem = new SelectGameMenuItem();
    if (menuItem && menuItem->initWithIndex(index, target, selector)) {
        menuItem->autorelease();
        return menuItem;
    }
    
    CC_SAFE_DELETE(menuItem);
    return NULL;
}

bool SelectGameMenuItem::initWithIndex(const int index,
                                       CCObject* target,
                                       SEL_MenuHandler selector)
{
    mNormalSprite = SelectGameMenuSprite::createWithIndex(index);
    mSelectedSprite = SelectGameMenuSprite::createWithIndex(index, true);
    mDisableSprite = SelectGameMenuSprite::createWithIndex(index, false, true);
    
    CCMenuItem::initWithTarget(target, selector);
    setNormalImage(mNormalSprite);
    setSelectedImage(mSelectedSprite);
    setDisabledImage(mDisableSprite);
    setTag(index);
    
    if(m_pNormalImage) {
        this->setContentSize(m_pNormalImage->getContentSize());
    }
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

    long levelRequired = SERVER().getRoomInfos()->at(index)->getLevelRequired();
    if (USERINFO()->getLevel() < levelRequired) {
        this->setEnabled(false);
    }
    
    return true;
}
