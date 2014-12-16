//
//  ChipBetted.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__ChipBetted__
#define __DragonVideoPoker__ChipBetted__

#include "cocos2d.h"

#define MAX_CHIP_TYPE_ON_TABLE      25


USING_NS_CC;
using namespace std;

class Chip;

class ChipBetted : public CCObject
{
public:
    ~ChipBetted();
    
    void initWithValues(int smallValue, int mediumValue, int bigValue, int maxStake);
    static ChipBetted* create(int smallValue, int mediumValue, int bigValue, int maxStake);
    
    vector<Chip*>* getSmallChips() {return mSmallChips;};
    vector<Chip*>* getMediumChips() {return mMediumChips;};
    vector<Chip*>* getBigChips() {return mBigChips;};
    
    void betChipWithType(int chipType, long long totalChips);
    
    void calculateNumberChipsFromLastBettedChip();
    void calculateNumberChipsForMaxBet(long long detalBet, long long totalBetChips);
    void calculateNumberChipsForWonChip(long long wonChips);
    
    void updateMainGameFinish();

    void reset();
    
    CC_SYNTHESIZE_READONLY(int, mNumberSmallChips, NumberSmallChips);
    CC_SYNTHESIZE_READONLY(int, mNumberMediumChips, NumberMediumChips);
    CC_SYNTHESIZE_READONLY(int, mNumberBigChips, NumberBigChips);
    CC_SYNTHESIZE_READONLY(long long, mMaxStake, MaxStake);

    CC_SYNTHESIZE_READONLY(int, mCurrentBetChipType, CurrentBetChipType);
    CC_SYNTHESIZE_READONLY(int, mCurrentBetChipValue, CurrentBetChipValue);
    
    CC_SYNTHESIZE(long long, mCurrentTotalBet, CurrentTotalBet);
    CC_SYNTHESIZE_READONLY(long long, mLastTotalBet, LastTotalBet);

private:
    
    vector<Chip*>* mSmallChips;
    vector<Chip*>* mMediumChips;
    vector<Chip*>* mBigChips;
    
    int mSmallValue;
    int mMediumValue;
    int mBigValue;
};

#endif /* defined(__DragonVideoPoker__ChipBetted__) */
