//
//  ChipBettedView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__ChipBettedView__
#define __DragonVideoPoker__ChipBettedView__

#include "cocos2d.h"

#define DELAY_MOVE_CHIP_DURATION        0.02


USING_NS_CC;
using namespace std;

class ChipBetted;
class ChipView;

class ChipBettedView : public CCObject
{
public:
    ~ChipBettedView();
    
    static ChipBettedView * create(ChipBetted* chipBetted);
    bool initWithChipBetted(ChipBetted* chipBetted);
    
    void addChipViewsToLayer(CCLayer *gameView, int zOrder);
    
    void moveCurrentBetChip();
    void moveBettedChips();
    void cancelBettedChips();
    void collectWonChips();
    void rebetLastChips();
    
    void updateChipsPosition(CCPoint smallPosition, CCPoint mediumPosition, CCPoint bigPosition);
    
private:
    ChipView* getAvailableChipView(int chipType);
    void moveChipWithType();
    
    ChipBetted* mChipBetted;

    CCArray* mSmallChipViews;
    CCArray* mMediumChipViews;
    CCArray* mBigChipViews;
    
    CCPoint mChipsPosition[3];
};

#endif /* defined(__DragonVideoPoker__ChipBettedView__) */
