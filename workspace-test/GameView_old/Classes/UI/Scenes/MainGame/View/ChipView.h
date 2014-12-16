//
//  ChipView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__ChipView__
#define __DragonVideoPoker__ChipView__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

static ccColor3B CHIP_NUMBER_COLOR = {204, 0, 0};

#define CHIP_MOVE_DURATION      0.25f

class Chip;

class ChipView : public CCSprite
{
public:
    static ChipView * create(Chip* chip, bool isNumberAttached = false, bool isGrayed = false);
    
    bool initWithChip(Chip* chip, bool isNumberAttached, bool isGrayed);
    void moveToPosition(CCPoint startPoint, CCPoint endPoint, float delayTime);
    
private:
    void stoppedAnimatingChip(CCNode * node);
    void startAnimatingChip(CCNode * node);

    Chip *mChip;
    CCLabelTTF *mAmountLabel;
};

#endif /* defined(__DragonVideoPoker__ChipView__) */
