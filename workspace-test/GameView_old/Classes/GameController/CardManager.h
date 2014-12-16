//
//  CardManager.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#ifndef __VideoPoker__CardManager__
#define __VideoPoker__CardManager__

#define ALL_CARD_MARKED             16 + 8 + 4 + 2 + 1

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Card;
class PokerHandData;

class CardManager : public CCObject
{    
public:
	~CardManager();
    static CardManager* create(int gameType);
    void init(int gameType);

    void createDealCards(long long betChips);
    void createDrawCards(int heldCardBits, long long jackpot); //update
    
    // deal return
    vector<int> getDealCards();
    int getHintCardBits() { return mHintCardBits;};

    // draw return
    vector<int> getDrawCards();
    long long getWonChips() { return mWonChips;};
    long getWonHandId() { return mWonHandId;};
    int getWonCardBits() { return mWonCardBits;};

    // Double or Nothing
    void createDonDealerCard();
    void createDonPlayerCards(int holdPosition); //update
    int getDonDealerCard();
    vector<int> getDonCards();
    
private:
    void createNormalCards();
    void createCardsWithJoker();
    void createCardsWithDueces();
    void createCardsWithJokerAndDueces();

    void validateHand();
    void validateHandOfJacksOrBetter();
    void validateHandOfJokerPoker();
    void validateHandOfTensOrBetter();
    void validateHandOfDeucesWild();
    void validateHandOfAcesAndFaces();
    void validateHandOfDuecesAndJokerWild();
    void validateHandOfAcesAndEights();
    void validateHandOfDoubleBonus();
    
    // get hint bits
    int getHintBitsOfDealCards();
    int getWonBitsOfDrawCards();

    int getHandBits(vector<Card*>* cards);
    
private:
    
    PokerHandData* mPokerHandData;

    vector<Card*>* mCards;
    vector<Card*>* mDealCards;
    vector<Card*>* mDrawCards;
    vector<Card*>* mDonCards;
    
    int mTotalCards;
    int mRemainCards;
    int mGameType;
    
    long long mBetChips;
    long long mWonChips;
    long mWonHandId;
    int mDealHandId;
    
    int mNumberHeldCards;
    int mHeldCardBits;
    int mWonCardBits;
    int mHintCardBits;
};


#endif /* defined(__VideoPoker__CardManager__) */
