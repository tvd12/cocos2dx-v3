//
//  Card.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#ifndef __VideoPoker__Card__
#define __VideoPoker__Card__

typedef enum CARD_SUIT {
    SUIT_SPADES             = 0,    // Bich
    SUIT_HEARTS             = 1,    // Co
    SUIT_CLUBS              = 2,    // Tep
    SUIT_DIAMONDS           = 3,    // Ro
    SUIT_JOKERS             = 4,
} CardSuit;


class Card {
    
public:
	Card(int rank, int suit);
	Card(int cardNumber);
    
    int getRank() { return mRank;}
    int getSuit() { return mSuit;}
    int getCardNumber();
    
private:
	int mRank, mSuit;
};

#endif /* defined(__VideoPoker__Card__) */
