//
//  PokerHand.cpp
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#include "PokerHand.h"
#include "PokerHandData.h"

#include "VideoPokerDefine.h"

#include "Card.h"
#include "CardManager.h"


static PokerHand *sInstance;
PokerHand* PokerHand::getInstance()
{
    if (!sInstance) {
        sInstance = new PokerHand();
    }
    
    return sInstance;
}

PokerHand::PokerHand()
{
}

int PokerHand::calculateHand(std::vector<Card*>* fiveCards, PokerHandData* pokerHandData)
{
    pokerHandData->prepareWith5Cards(fiveCards);

    if (!pokerHandData->getNumberJokers()) {
        calculateHandNoneJoker(pokerHandData);
    }
    else {
        calculateHandWithJokers(pokerHandData);
    }
    
    return pokerHandData->getPokerHand();
}

void PokerHand::calculateHandNoneJoker(PokerHandData* pokerHandData)
{
    // calculate hand
    pokerHandData->setPokerHand(POKER_HAND_NOTHING);
    
    // calculate Flush, straight first
    if (pokerHandData->getSameCardsInLargeGroup() == 1) {
        bool isFlush = pokerHandData->isFlushHand();
        int isStraight = pokerHandData->isStraightHand();
        if (isFlush && isStraight > -1) {
            if (isStraight == 13) {
                pokerHandData->setPokerHand(POKER_HAND_NATURAL_ROYAL_FLUSH);
            }
            else {
                pokerHandData->setPokerHand(POKER_HAND_STRAIGHT_FLUSH);
            }
        }
        else if (isFlush) {
            pokerHandData->setPokerHand(POKER_HAND_FLUSH);
        }
        else if (isStraight > -1) {
            pokerHandData->setPokerHand(POKER_HAND_STRAIGHT);
        }
    }
    else {
        if (pokerHandData->getSameCardsInLargeGroup() == 2 &&
            pokerHandData->getSameCardsInSmallGroup() == 1) {
            // Pair
            if (pokerHandData->getLargeGroupRank() > 11) {
                pokerHandData->setPokerHand(POKER_HAND_KINGS_OR_BETTER);
            }
            else if (pokerHandData->getLargeGroupRank() > 9) {
                pokerHandData->setPokerHand(POKER_HAND_JACKS_OR_BETTER);
            }
            else if (pokerHandData->getLargeGroupRank() > 8) {
                pokerHandData->setPokerHand(POKER_HAND_TENS_OR_BETTER);
            }
        }
        else if (pokerHandData->getSameCardsInLargeGroup() == 2 &&
                 pokerHandData->getSameCardsInSmallGroup() == 2) {
            pokerHandData->setPokerHand(POKER_HAND_TWO_PAIR);
        }
        else if (pokerHandData->getSameCardsInLargeGroup() == 3 &&
                 pokerHandData->getSameCardsInSmallGroup() != 2) {
            pokerHandData->setPokerHand(POKER_HAND_THREE_OF_A_KIND);
        }
        else if (pokerHandData->getSameCardsInLargeGroup() == 3 &&
                 pokerHandData->getSameCardsInSmallGroup() == 2) {
            pokerHandData->setPokerHand(POKER_HAND_FULL_HOUSE);
        }
        else if (pokerHandData->getSameCardsInLargeGroup() == 4) {
            pokerHandData->setPokerHand(POKER_HAND_FOUR_OF_A_KIND);
            pokerHandData->setKicker(pokerHandData->getLargeGroupRank());
        }
    }
}


void PokerHand::calculateHandWithJokers(PokerHandData* pokerHandData)
{
    // got 5 joker
    switch (pokerHandData->getNumberJokers()) {
        case 5:
            calculateHandWith5Jokers(pokerHandData);
            break;
            
        case 4:
            calculateHandWith4Jokers(pokerHandData);
            break;
            
        default:
            calculateHandWith1To3Jokers(pokerHandData);
            break;
    }
}

void PokerHand::calculateHandWith5Jokers(PokerHandData* pokerHandData)
{
    pokerHandData->setPokerHand(POKER_HAND_FIVE_WILDS);
}

void PokerHand::calculateHandWith4Jokers(PokerHandData* pokerHandData)
{
    // all special are wild
    if (!pokerHandData->isHaveJokerInHand()) {
        pokerHandData->setPokerHand(POKER_HAND_NATURAL_FOUR_DEUCES);
    }
    else {
        pokerHandData->createOrderedRanks();
        
        // wild royal flush
        if (pokerHandData->getOrderedRanks()[0] > 8) {
            pokerHandData->setPokerHand(POKER_HAND_WILD_ROYAL_FLUSH);
        }
        // five of a kind
        else {
            pokerHandData->setPokerHand(POKER_HAND_FIVE_OF_A_KIND);
        }
    }
}

void PokerHand::calculateHandWith1To3Jokers(PokerHandData* pokerHandData)
{
    pokerHandData->setPokerHand(POKER_HAND_NOTHING);

    if (pokerHandData->getSameCardsInLargeGroup() == 1) {
        bool isHaveSameSuit = pokerHandData->isHaveSameSuitInHand();
        int smallOrderedIndex = 5 - pokerHandData->getNumberJokers() - 1;
        // Wild royal flush or Straight flush
        if (isHaveSameSuit) {
            pokerHandData->createOrderedRanks();
            
            if (pokerHandData->getOrderedRanks()[smallOrderedIndex] > 8) {
                pokerHandData->setPokerHand(POKER_HAND_WILD_ROYAL_FLUSH);
            }
            // check it have ace?
            else {
                // have ace and large card is smaller than 6
                if (pokerHandData->getOrderedRanks()[0] == 13 &&
                    pokerHandData->getOrderedRanks()[1] < 5) {
                    pokerHandData->setPokerHand(POKER_HAND_STRAIGHT_FLUSH);
                }
                // don't have ace and distance is smaller 5
                else if (pokerHandData->getOrderedRanks()[0] != 13 &&
                         pokerHandData->getOrderedRanks()[0] - pokerHandData->getOrderedRanks()[smallOrderedIndex] < 5) {
                    pokerHandData->setPokerHand(POKER_HAND_STRAIGHT_FLUSH);
                }
                // other cases
                else {
                    // have three jokers
                    if (pokerHandData->getNumberJokers() == 3) {
                        pokerHandData->setPokerHand(POKER_HAND_FOUR_OF_A_KIND);
                    }
                    else {
                        pokerHandData->setPokerHand(POKER_HAND_FLUSH);
                    }
                }
            }
        }
        // find straight
        else {
            // have three jokers
            if (pokerHandData->getNumberJokers() == 3) {
                pokerHandData->setPokerHand(POKER_HAND_FOUR_OF_A_KIND);
            }
            else {
                pokerHandData->createOrderedRanks();
                
                // have ace and large card is smaller than 6
                if (pokerHandData->getOrderedRanks()[0] == 13 && pokerHandData->getOrderedRanks()[1] < 5) {
                    pokerHandData->setPokerHand(POKER_HAND_STRAIGHT);
                }
                // don't have ace and distance is smaller 5
                else if (pokerHandData->getOrderedRanks()[0] - pokerHandData->getOrderedRanks()[smallOrderedIndex] < 5) {
                    pokerHandData->setPokerHand(POKER_HAND_STRAIGHT);
                }
                // other cases
                else {
                    if (pokerHandData->getNumberJokers() == 2) {
                        pokerHandData->setPokerHand(POKER_HAND_THREE_OF_A_KIND);
                    }
                    // Pair
                    else if (pokerHandData->getOrderedRanks()[0] > 11) {
                        pokerHandData->setPokerHand(POKER_HAND_KINGS_OR_BETTER);
                    }
                }
            }
        }
    }
    
    // got at least a pair in normal cards
    else {
        if (pokerHandData->getSameCardsInSmallGroup() == 0) {
            pokerHandData->setPokerHand(POKER_HAND_FIVE_OF_A_KIND);
        }
        else {
            // Pair
            if (pokerHandData->getSameCardsInLargeGroup() == 2 && pokerHandData->getSameCardsInSmallGroup() == 1) {
                if (pokerHandData->getNumberJokers() == 2) {
                    pokerHandData->setPokerHand(POKER_HAND_FOUR_OF_A_KIND);
                }
                else {
                    pokerHandData->setPokerHand(POKER_HAND_THREE_OF_A_KIND);
                }
            }
            else if (pokerHandData->getSameCardsInLargeGroup() == 2 && pokerHandData->getSameCardsInSmallGroup() == 2) {
                pokerHandData->setPokerHand(POKER_HAND_FULL_HOUSE);
            }
            else if (pokerHandData->getSameCardsInLargeGroup() == 3 && pokerHandData->getSameCardsInSmallGroup() == 1) {
                pokerHandData->setPokerHand(POKER_HAND_FOUR_OF_A_KIND);
            }
        }
    }
}
