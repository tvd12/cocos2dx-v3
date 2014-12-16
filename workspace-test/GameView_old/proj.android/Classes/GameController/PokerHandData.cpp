//
//  PokerHandData.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/22/14.
//
//

#include "PokerHandData.h"
#include "Card.h"


PokerHandData::PokerHandData()
{
}

void PokerHandData::prepareWith5Cards(vector<Card*>* fiveCards)
{
    mFiveCards = fiveCards;
    
    // init ranks
    for (int i = 0; i < 15; i++) {
        mRanks[i] = 0;
        mOrderedRanks[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        mRanks[mFiveCards->at(i)->getRank()]++;
    }
    mRanks[13] = mRanks[0];
    mNumberJokers = mRanks[14];
    
    // calculate hand ranks
    mSameCardsInLargeGroup = 0;
    mSameCardsInSmallGroup = 0;
    mLargeGroupRank = 0;
    mSmallGroupRank = 0;
    for (int i = 13; i >= 1; i--) {
        if (mRanks[i] > mSameCardsInLargeGroup) {
            if (mSameCardsInLargeGroup > 0) {
                //if mSameCardsInLargeGroup was not the default value
                mSameCardsInSmallGroup = mSameCardsInLargeGroup;
                mSmallGroupRank = mLargeGroupRank;
            }
            
            mSameCardsInLargeGroup = mRanks[i];
            mLargeGroupRank = i;
        }
        else if (mRanks[i] > mSameCardsInSmallGroup) {
            mSameCardsInSmallGroup = mRanks[i];
            mSmallGroupRank = i;
        }
    }
}

bool PokerHandData::isHaveJokerInHand()
{
    for (int i = 0; i < 4; i++) {
        if (mFiveCards->at(i)->getSuit() == SUIT_JOKERS)
            return true;
    }
    return false;
}

bool PokerHandData::isHaveSameSuitInHand()
{
    int suit = -1;
    for (int i = 0; i < 5; i++) {
        if (mFiveCards->at(i)->getRank() < 14) {
            if (suit == -1) {
                suit = mFiveCards->at(i)->getSuit();
            }
            else if (mFiveCards->at(i)->getSuit() != suit) {
                return false;
            }
        }
    }
    
    return true;
}

bool PokerHandData::isFlushHand()
{
    for (int i = 0; i < 4; i++) {
        if (mFiveCards->at(i)->getSuit() != mFiveCards->at(i+1)->getSuit())
            return false;
    }
    
    return true;
}

int PokerHandData::isStraightHand()
{
    int topStraightValue = -1;
    for (int x = 0; x < 10; x++) {
        if (mRanks[x] == 1 && mRanks[x+1] == 1 && mRanks[x+2] == 1 &&
            mRanks[x+3] == 1 && mRanks[x+4] == 1) {
            // 4 above bottom value
            topStraightValue = x+4;
            break;
        }
    }
    
    return topStraightValue;
}

void PokerHandData::createOrderedRanks()
{
    int index = 0;
    //if ace, run this before because ace is highest card
    if (mRanks[0] == 1) {
        mOrderedRanks[index++] = 13;
    }
    
    for (int x = 12; x >= 1; x--) {
        if (mRanks[x]) {
            mOrderedRanks[index++] = x;
        }
    }
}


