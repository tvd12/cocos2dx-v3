//
//  Card.cpp
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#include "Card.h"

Card::Card(int rank, int suit) {
    mRank = rank;
    mSuit = suit;
}

Card::Card(int cardNumber) {
    switch (cardNumber) {
        case 52:
            mRank = 14;
            mSuit = SUIT_JOKERS;
            break;
            
        case 53:
            mRank = 14;
            mSuit = 0;
            break;
            
        case 54:
            mRank = 14;
            mSuit = 1;
            break;
            
        case 55:
            mRank = 14;
            mSuit = 2;
            break;
            
        case 56:
            mRank = 14;
            mSuit = 3;
            break;
            
        case -1:
            mRank = 0;
            mSuit = 0;
            break;
            
        default:
            mRank = cardNumber % 13;
            mSuit = cardNumber / 13;
            break;
    }
}

int Card::getCardNumber() {
    int cardNumber = 0;
    
    if (mRank == 14) {
        switch (mSuit) {
            case SUIT_JOKERS:
                cardNumber = 52;
                break;
                
            case 0:
                cardNumber = 53;
                break;
                
            case 1:
                cardNumber = 54;
                break;
                
            case 2:
                cardNumber = 55;
                break;
                
            case 3:
                cardNumber = 56;
                break;
                
            default:
                break;
        }
    }
    else {
        cardNumber = mRank + mSuit * 13;
    }
    
    return cardNumber;
}
