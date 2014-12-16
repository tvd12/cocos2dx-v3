//
//  PokerHandData.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/22/14.
//
//

#ifndef __DragonVideoPoker__PokerHandData__
#define __DragonVideoPoker__PokerHandData__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Card;
class PokerHandData : public CCObject
{
public:
    PokerHandData();
    
    void prepareWith5Cards(vector<Card*>* fiveCards);
    
    bool isHaveJokerInHand();
    bool isHaveSameSuitInHand();
    bool isFlushHand();
    int isStraightHand();

    void createOrderedRanks();

    
    int getNumberJokers() { return mNumberJokers; };
    
    int getPokerHand() { return mPokerHand; };
    void setPokerHand(int pokerHand) { mPokerHand = pokerHand; };
    
    int* getRanks() { return mRanks; };
    int* getOrderedRanks() { return mOrderedRanks; };
    
    int getSameCardsInLargeGroup() { return mSameCardsInLargeGroup; };
    int getLargeGroupRank() { return mLargeGroupRank; };
    int getSameCardsInSmallGroup() { return mSameCardsInSmallGroup; };
    int getSmallGroupRank() { return mSmallGroupRank; };
        
    int getKicker() { return mKicker; };
    void setKicker(int kicker) { mKicker = kicker; };

private:
    int mRanks[15];
    int mOrderedRanks[15];
    vector<Card*>* mFiveCards;
    
    int mPokerHand;
    int mKicker;
    
    int mSameCardsInLargeGroup, mSameCardsInSmallGroup;
    int mLargeGroupRank, mSmallGroupRank;
    int mNumberJokers;
};

#endif /* defined(__DragonVideoPoker__PokerHandData__) */
