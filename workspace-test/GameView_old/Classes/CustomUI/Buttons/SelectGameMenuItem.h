//
//  SelectGameMenuItem.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef __DragonVideoPoker__SelectGameMenuItem__
#define __DragonVideoPoker__SelectGameMenuItem__

#include <string>

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class SelectGameMenuSprite;

class SelectGameMenuItem : public CCMenuItemSprite
{
public:
    static SelectGameMenuItem * createWithIndex(const int index,
                                                CCObject* target,
                                                SEL_MenuHandler selector);
    bool initWithIndex(const int index, CCObject* target,
                       SEL_MenuHandler selector);
    
    
//    virtual void update(float dt);
    
private:

    SelectGameMenuSprite* mNormalSprite;
    SelectGameMenuSprite* mSelectedSprite;
    SelectGameMenuSprite* mDisableSprite;
};

#endif /* defined(__DragonVideoPoker__SelectGameMenuItem__) */
