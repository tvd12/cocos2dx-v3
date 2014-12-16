//
//  PokerHand.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#ifndef __VideoPoker__PokerHand__
#define __VideoPoker__PokerHand__

#include <vector>

using namespace std;

class Card;
class PokerHandData;

class PokerHand {
    
public:
	PokerHand();
    static PokerHand * getInstance();

    int calculateHand(vector<Card*>* fiveCards, PokerHandData* pokerHandData);
    
private:
    
    void calculateHandNoneJoker(PokerHandData* pokerHandData);
    void calculateHandWithJokers(PokerHandData* pokerHandData);
    void calculateHandWith5Jokers(PokerHandData* pokerHandData);
    void calculateHandWith4Jokers(PokerHandData* pokerHandData);
    void calculateHandWith1To3Jokers(PokerHandData* pokerHandData);
};

#define POKER_HAND()            PokerHand::getInstance()

#endif /* defined(__VideoPoker__PokerHand__) */
