//
//  ChipBetted.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "ChipBetted.h"
#include "Chip.h"

ChipBetted::~ChipBetted()
{
    // delete small chips
    vector<Chip*>::iterator it;
    for (it = mSmallChips->begin(); it != mSmallChips->end(); ++it) {
        delete *it;
    }
    mSmallChips->clear();
    delete mSmallChips;
    
    // delete medium chips
    for (it = mMediumChips->begin(); it != mMediumChips->end(); ++it) {
        delete *it;
    }
    mMediumChips->clear();
    delete mMediumChips;
    
    // delete big chips
    for (it = mBigChips->begin(); it != mBigChips->end(); ++it) {
        delete *it;
    }
    mBigChips->clear();
    delete mBigChips;
}

void ChipBetted::initWithValues(int smallValue, int mediumValue, int bigValue, int maxStake)
{
    mSmallChips = new vector<Chip*>();
    mMediumChips = new vector<Chip*>();
    mBigChips = new vector<Chip*>();
    
    mSmallValue = smallValue;
    mMediumValue = mediumValue;
    mBigValue = bigValue;
    mMaxStake = maxStake;
    
    mCurrentBetChipValue = 0;
    
    for (int i = 0; i < MAX_CHIP_TYPE_ON_TABLE; i++) {
        Chip *smallChip = Chip::create(CHIP_SMALL, smallValue);
        mSmallChips->push_back(smallChip);
        Chip *mediumChip = Chip::create(CHIP_MEDIUM, mediumValue);
        mMediumChips->push_back(mediumChip);
        Chip *bigChip = Chip::create(CHIP_BIG, bigValue);
        mBigChips->push_back(bigChip);
    }
}

ChipBetted* ChipBetted::create(int smallValue, int mediumValue, int bigValue, int maxStake)
{
    ChipBetted *pRet = new ChipBetted();
    pRet->initWithValues(smallValue, mediumValue, bigValue, maxStake);
    pRet->autorelease();
    return pRet;
}

void ChipBetted::betChipWithType(int chipType, long long totalChips)
{
    mCurrentBetChipType = chipType;

    switch (chipType) {
        case CHIP_SMALL:
            mCurrentBetChipValue = mSmallValue;
            break;
            
        case CHIP_MEDIUM:
            mCurrentBetChipValue = mMediumValue;
            break;
            
        case CHIP_BIG:
            mCurrentBetChipValue = mBigValue;
            break;
            
        default:
            break;
    }
    
    // canot more than total chips
    if (mCurrentBetChipValue > totalChips) {
        mCurrentBetChipValue = totalChips;
    }
    
    // canot more than max stake
    if (mCurrentTotalBet + mCurrentBetChipValue > mMaxStake) {
        mCurrentBetChipValue = mMaxStake - mCurrentTotalBet;
    }

    mCurrentTotalBet += mCurrentBetChipValue;
}

void ChipBetted::calculateNumberChipsFromLastBettedChip()
{
    mLastTotalBet = mCurrentTotalBet;
    
    int minChips = 10000;
    
    for (int chip3 = mLastTotalBet / mBigValue; chip3 >= 0; chip3--) {
        for (int chip2 = (mLastTotalBet - chip3 * mBigValue) / mMediumValue; chip2 >= 0; chip2--) {
            for (int chip1 = (mLastTotalBet - chip3 * mBigValue - chip2 * mMediumValue) / mSmallValue;
                 chip1 >= 0;
                 chip1--) {
                if (chip1 + chip2 + chip3 < minChips) {
                    if (chip3 * mBigValue + chip2 * mMediumValue + chip1 * mSmallValue ==
                        mLastTotalBet) {
                        minChips = chip1 + chip2 + chip3;
                        mNumberBigChips = chip3;
                        mNumberMediumChips = chip2;
                        mNumberSmallChips = chip1;
                    }
                }
            }
        }
    }
}

void ChipBetted::calculateNumberChipsForWonChip(long long wonChips)
{
    int minChips = 10000;
    
    if (wonChips / mBigValue > MAX_CHIP_TYPE_ON_TABLE) {
        mNumberBigChips = MAX_CHIP_TYPE_ON_TABLE;
        mNumberMediumChips = 0;
        mNumberSmallChips = 0;
        return;
    }
    
    for (int chip3 = wonChips / mBigValue; chip3 >= 0; chip3--) {
        for (int chip2 = (wonChips - chip3 * mBigValue) / mMediumValue; chip2 >= 0; chip2--) {
            for (int chip1 = (wonChips - chip3 * mBigValue - chip2 * mMediumValue) / mSmallValue;
                 chip1 >= 0;
                 chip1--) {
                if (chip1 + chip2 + chip3 < minChips) {
                    if (chip3 * mBigValue + chip2 * mMediumValue + chip1 * mSmallValue == wonChips) {
                        minChips = chip1 + chip2 + chip3;
                        mNumberBigChips = chip3;
                        mNumberMediumChips = chip2;
                        mNumberSmallChips = chip1;
                    }
                }
            }
        }
    }
    
    mNumberBigChips = mNumberBigChips > MAX_CHIP_TYPE_ON_TABLE ?
    MAX_CHIP_TYPE_ON_TABLE : mNumberBigChips;
    mNumberMediumChips = mNumberMediumChips > MAX_CHIP_TYPE_ON_TABLE ?
    MAX_CHIP_TYPE_ON_TABLE : mNumberMediumChips;
    mNumberSmallChips = mNumberSmallChips > MAX_CHIP_TYPE_ON_TABLE ?
    MAX_CHIP_TYPE_ON_TABLE : mNumberSmallChips;
}

void ChipBetted::calculateNumberChipsForMaxBet(long long detalBet,
                                               long long totalBetChips)
{
    long long deltaMax = detalBet;

    // calculate number of big chip
    mNumberBigChips = deltaMax / mBigValue;

    // calculate number of medium chip
    deltaMax = deltaMax - mNumberBigChips * mBigValue;
    mNumberMediumChips = deltaMax / mMediumValue;
    
    // calculate number of small chip
    deltaMax = deltaMax - mNumberMediumChips * mMediumValue;
    mNumberSmallChips = ceilf((float)deltaMax / (float)mSmallValue);
    
    mCurrentTotalBet = totalBetChips;
}

void ChipBetted::reset()
{
    mCurrentTotalBet = 0;
    mLastTotalBet = 0;
}

void ChipBetted::updateMainGameFinish()
{
    mLastTotalBet = mCurrentTotalBet;
    mCurrentTotalBet = 0;
}
