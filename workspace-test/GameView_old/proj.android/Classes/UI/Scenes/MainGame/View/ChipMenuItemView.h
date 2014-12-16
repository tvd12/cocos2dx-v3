//
//  ChipMenuItemView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/18/14.
//
//

#ifndef __DragonVideoPoker__ChipMenuItemView__
#define __DragonVideoPoker__ChipMenuItemView__

#include "cocos2d.h"

using namespace cocos2d;

class ChipMenuItemView : public CCMenuItemSprite {
public:
    static ChipMenuItemView* create(CCNode *normalSprite,
                                    CCNode *selectedSprite,
                                    CCNode *disabledSprite,
                                    CCObject *target,
                                    SEL_MenuHandler selector);
    bool initWithNormalSprite(CCNode* normalSprite,
                              CCNode* selectedSprite,
                              CCNode* disabledSprite,
                              CCObject* target,
                              SEL_MenuHandler selector);
    virtual void selected();
    virtual void unselected();
    
    void updateLongTouch(float delta);
    
};

#endif /* defined(__DragonVideoPoker__ChipMenuItemView__) */
