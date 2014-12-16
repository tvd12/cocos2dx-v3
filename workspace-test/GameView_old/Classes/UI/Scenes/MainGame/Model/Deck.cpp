//
//  Deck.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "Deck.h"
#include "Card.h"


bool Deck::init()
{
    // init params
    mCards = new vector<Card*>();
    mDealCards = new vector<Card*>();
    mDrawCards = new vector<Card*>();
    mDonCards = new vector<Card*>(5);
    
    mHeldBit = 0;
    mNumberOfHeldCards = 0;
    
    // all cards to deck
    for (int i = 0; i < NUMBER_CARDS_IN_DECK; i++) {
        Card *card = new Card(i);
        mCards->push_back(card);
    }

    // prepare deal cards
    for (int i = 0; i < 5; i++) {
        Card *card = mCards->at(i);
        mDealCards->push_back(card);
    }
    
    return true;
}

void Deck::gotDealCardsFromServer(int *dealCards, int hintBit)
{
    // reset items
    mDealCards->clear();
    mHeldBit = hintBit;
    
    for (int i = 0; i < 5; i++) {
        int cardNumber = dealCards[i];
        Card *card = mCards->at(cardNumber);
        // add to dealcards
        mDealCards->push_back(card);
    }
}

void Deck::updateHeldBit(int cardHeld)
{
    mHeldBit = mHeldBit xor (1 << cardHeld);
}

void Deck::gotDrawCardsFromServer(int *drawCards, int wonBit)
{
    mDrawCards->clear();
    mWonBit = wonBit;

    for (int i = 0; i < 5; i++) {
        int cardNumber = drawCards[i];
        Card *card = mCards->at(cardNumber);
        // add to drawcards
        mDrawCards->push_back(card);
    }
}

void Deck::gotDonDealerCardFromServer(int dealerCard)
{
    mDonCards->at(0) = mCards->at(dealerCard);
}

void Deck::gotDonCardsFromServer(int *donCards)
{
    for (int i = 0; i < 5; i++) {
        int cardNumber = donCards[i];
        Card *card = mCards->at(cardNumber);
        // add to drawcards
        mDonCards->at(i) = card;
    }
}

void Deck::updateMainGameFinish()
{
    mHeldBit = 0;
    mWonBit = 0;
}
