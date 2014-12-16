//
//  Deck.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__Deck__
#define __DragonVideoPoker__Deck__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define NUMBER_CARDS_IN_DECK            57

class Card;

class Deck : public CCObject
{
public:
    virtual bool init();
    
    CREATE_FUNC(Deck);

    CC_SYNTHESIZE(int, mHeldBit, HeldBit);
    CC_SYNTHESIZE(int, mWonBit, WonBit);
    CC_SYNTHESIZE(int, mNumberOfHeldCards, NumberOfHeldCards);
    
    vector<Card*> *getCards() {return mCards;};
    vector<Card*> *getDealCards() {return mDealCards;};
    vector<Card*> *getDrawCards() {return mDrawCards;};
    vector<Card*> *getDonCards() {return mDonCards;};

    void gotDealCardsFromServer(int *dealCards, int hintBit);
    void updateHeldBit(int cardHeld);
    void gotDrawCardsFromServer(int *drawCards, int wonBit);
    void gotDonDealerCardFromServer(int dealerCard);
    void gotDonCardsFromServer(int *donCards);

    void updateMainGameFinish();
    
private:
    vector<Card*> *mCards;
    
    vector<Card*> *mDealCards;
    vector<Card*> *mDrawCards;
    vector<Card*> *mDonCards;

};

#endif /* defined(__DragonVideoPoker__Deck__) */
