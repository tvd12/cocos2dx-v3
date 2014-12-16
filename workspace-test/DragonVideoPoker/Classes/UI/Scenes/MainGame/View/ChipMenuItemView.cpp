//
//  ChipMenuItemView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/18/14.
//
//

#include "ChipMenuItemView.h"

ChipMenuItemView* ChipMenuItemView::create(CCNode *normalSprite,
                                           CCNode *selectedSprite,
                                           CCNode *disabledSprite,
                                           CCObject *target,
                                           SEL_MenuHandler selector) {
    ChipMenuItemView *pRet = new ChipMenuItemView();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
    pRet->autorelease();
    return pRet;
}

bool ChipMenuItemView::initWithNormalSprite(CCNode *normalSprite,
                                            CCNode *selectedSprite,
                                            CCNode *disabledSprite,
                                            CCObject *target,
                                            SEL_MenuHandler selector) {
    CCMenuItemSprite::initWithNormalSprite(normalSprite,
                                           selectedSprite,
                                           disabledSprite,
                                           target,
                                           selector);
    return true;
}

void ChipMenuItemView::updateLongTouch(float delta) {
    activate();
}

void ChipMenuItemView::selected() {
    CCMenuItemSprite::selected();
    schedule(schedule_selector(ChipMenuItemView::updateLongTouch),
             0.1f,
             kCCRepeatForever,
             0.5f);
}

void ChipMenuItemView::unselected() {
    CCMenuItemSprite::unselected();
    unschedule(schedule_selector(ChipMenuItemView::updateLongTouch));
    if (m_bEnabled == false) {
        m_pNormalImage->setVisible(false);
        m_pDisabledImage->setVisible(true);
    }
}