//
//  CardManager.cpp
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 3/4/14.
//
//

#include "CardManager.h"
#include "VideoPokerDefine.h"

#include "Card.h"
#include "PokerHand.h"
#include "PokerHandData.h"
#include "Payout.h"


CardManager* CardManager::create(int gameType)
{
    CardManager *pRet = new CardManager();
    pRet->init(gameType);
    pRet->autorelease();
    return pRet;
}

CardManager::~CardManager()
{
    mDonCards->clear();
}

void CardManager::init(int gameType)
{
    mDonCards = new vector<Card*>(5);
    mDealCards = new vector<Card*>(5);
    mDrawCards = new vector<Card*>(5);
    mCards = new vector<Card*>(53);
    
    PokerHand::getInstance();
    
    mPokerHandData = new PokerHandData();

    mGameType = gameType;
    
    switch (gameType) {
        case JOKER_POKER:
            createCardsWithJoker();
            break;
            
        case DEUCES_WILD:
            createCardsWithDueces();
            break;
            
        case DEUCES_AND_JOKER_WILD:
            createCardsWithJokerAndDueces();
            break;
            
        default:
            createNormalCards();
            break;
    }
}

#pragma mark - create cards with game type

void CardManager::createNormalCards()
{
    mTotalCards = 52;

    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            Card *card = new Card(rank, suit);
            int index = rank + suit * 13;
            mCards->at(index) = card;
        }
    }
}

void CardManager::createCardsWithJoker()
{
    createNormalCards();
    
    mTotalCards = 53;
    Card *jokerCard = new Card(14, SUIT_JOKERS);
    mCards->at(52) = jokerCard;
}

void CardManager::createCardsWithDueces()
{
    mTotalCards = 52;
    
    int index = 0;
    // add normal cards from 3-K
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 2; rank < 13; rank++) {
            Card *card = new Card(rank, suit);
            mCards->at(index++) = card;
        }
    }
    
    // add duece cards & aces
    for (int i = 0; i < 4; i++) {
        Card *card = new Card(14, i);
        mCards->at(index++) = card;
        Card *aceCard = new Card(0, i);
        mCards->at(index++) = aceCard;
    }
}

void CardManager::createCardsWithJokerAndDueces()
{
    createCardsWithDueces();

    mTotalCards = 53;
    Card *jokerCard = new Card(14, SUIT_JOKERS);
    mCards->at(52) = jokerCard;
}

#pragma mark - Double or Nothing

void CardManager::createDonDealerCard()
{
    mRemainCards = mTotalCards;
    int x = rand() % (mRemainCards--);
    mDonCards->at(0) = mCards->at(x);
    mCards->at(x) = mCards->at(mRemainCards);
    mCards->at(mRemainCards) = mDonCards->at(0);
}

void CardManager::createDonPlayerCards(int holdPosition)
{
    for(int i = 1 ; i < 5; i++) {
        int x = rand() % (mRemainCards--);
        mDonCards->at(i) = mCards->at(x);
        mCards->at(x) = mCards->at(mRemainCards);
        mCards->at(mRemainCards) = mDonCards->at(i);
    }
    
    // calculate won chips
    Card* dealerCard = mDonCards->at(0);
    Card* playerCard = mDonCards->at(holdPosition);
    if (dealerCard->getRank() > 0 && dealerCard->getRank() < 13) {
        if (playerCard->getRank() == 0 || playerCard->getRank() == 14) {
            mWonChips *= 2;
        }
        else {
            if (dealerCard->getRank() < playerCard->getRank()) {
                mWonChips *= 2;
            }
            else if (dealerCard->getRank() > playerCard->getRank()) {
                mWonChips = 0;
            }
        }
    }
    else {
        if (playerCard->getRank() != 0 && playerCard->getRank() != 14) {
            mWonChips = 0;
        }
    }
}

int CardManager::getDonDealerCard()
{
    return mDonCards->at(0)->getCardNumber();
}

vector<int> CardManager::getDonCards()
{
    vector<int> ret = vector<int>(5);
    for (int i = 0; i < 5; i++) {
        ret[i] = mDonCards->at(i)->getCardNumber();
    }
    
    return ret;
}

#pragma mark - deal cards action

void CardManager::createDealCards(long long betChips)
{
    mBetChips = betChips;
    
    mRemainCards = mTotalCards;
    for(int i = 0 ; i < 5; i++) {
        int x = rand() % (mRemainCards--);
        mDealCards->at(i) = mCards->at(x);
        mDrawCards->at(i) = mCards->at(x);
        mCards->at(x) = mCards->at(mRemainCards);
        mCards->at(mRemainCards) = mDealCards->at(i);
    }
    
    // calculate video poker hand
    PokerHand::getInstance()->calculateHand(mDealCards, mPokerHandData);
    
    // validate hand with game type
    validateHand();
    
    // create hint bits if need
    mHintCardBits = getHintBitsOfDealCards();
}

vector<int> CardManager::getDealCards()
{
    vector<int> ret = vector<int>(5);
    for (int i = 0; i < 5; i++) {
        ret[i] = mDealCards->at(i)->getCardNumber();
    }
    
    return ret;
}

#pragma mark - draw cards action

void CardManager::createDrawCards(int heldCardBits, long long jackpot)
{
    for(int i = 0 ; i < 5; i++) {
        if ((heldCardBits & (1 << i)) == 0) {
            int x = rand() % (mRemainCards--);
            mDrawCards->at(i) = mCards->at(x);
            mCards->at(x) = mCards->at(mRemainCards);
            mCards->at(mRemainCards) = mDrawCards->at(i);
        }
    }

    // calculate video poker hand
    PokerHand::getInstance()->calculateHand(mDrawCards, mPokerHandData);
    
    // validate hand with game type
    validateHand();

    // get won values
    mWonCardBits = getWonBitsOfDrawCards();
    
    // get wonId & wonChips
    mWonHandId = mPokerHandData->getPokerHand();
    if (mWonHandId == POKER_HAND_NOTHING) {
        mWonChips = 0;
    }
    else {
        int payout = Payout::getInstance()->getMultiplier(mGameType, mWonHandId);
        // normal won
        if (payout < 10000) {
            mWonChips = payout * mBetChips;
        }
        // got jackpot
        else {
            mWonChips = jackpot;
        }
    }
}

vector<int> CardManager::getDrawCards()
{
    vector<int> ret = vector<int>(5);
    for (int i = 0; i < 5; i++) {
        ret[i] = mDrawCards->at(i)->getCardNumber();
    }
    
    return ret;
}

#pragma mark - validate video poker hand

void CardManager::validateHand()
{
    switch (mGameType) {
        case JACKS_OR_BETTER:
            validateHandOfJacksOrBetter();
            break;
            
        case JOKER_POKER:
            validateHandOfJokerPoker();
            break;
            
        case TENS_OR_BETTER:
            validateHandOfTensOrBetter();
            break;
            
        case DEUCES_WILD:
            validateHandOfDeucesWild();
            break;
            
        case ACES_AND_FACES:
            validateHandOfAcesAndFaces();
            break;
            
        case DEUCES_AND_JOKER_WILD:
            validateHandOfDuecesAndJokerWild();
            break;
            
        case ACES_AND_EIGHTS:
            validateHandOfAcesAndEights();
            break;
            
        case DOUBLE_BONUS:
            validateHandOfDoubleBonus();
            break;
            
        default:
            break;
    }
}

void CardManager::validateHandOfJacksOrBetter()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_KINGS_OR_BETTER:
            validateHand = POKER_HAND_JACKS_OR_BETTER;
            break;
            
        case POKER_HAND_TENS_OR_BETTER:
            validateHand = POKER_HAND_NOTHING;
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfJokerPoker()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_JACKS_OR_BETTER:
        case POKER_HAND_KINGS_OR_BETTER:
        case POKER_HAND_TENS_OR_BETTER:
        case POKER_HAND_TWO_PAIR:
            validateHand = POKER_HAND_NOTHING;
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfTensOrBetter()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_JACKS_OR_BETTER:
            validateHand = POKER_HAND_TENS_OR_BETTER;
            break;
            
        case POKER_HAND_KINGS_OR_BETTER:
            validateHand = POKER_HAND_TENS_OR_BETTER;
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfDeucesWild()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_JACKS_OR_BETTER:
        case POKER_HAND_KINGS_OR_BETTER:
        case POKER_HAND_TENS_OR_BETTER:
        case POKER_HAND_TWO_PAIR:
            validateHand = POKER_HAND_NOTHING;
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfAcesAndFaces()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_KINGS_OR_BETTER:
            validateHand = POKER_HAND_JACKS_OR_BETTER;
            break;
            
        case POKER_HAND_TENS_OR_BETTER:
            validateHand = POKER_HAND_NOTHING;
            break;

        case POKER_HAND_FOUR_OF_A_KIND:
            if (mPokerHandData->getKicker() < 10) {
                validateHand = POKER_HAND_FOUR_2_10;
            }
            else if (mPokerHandData->getKicker() < 13) {
                validateHand = POKER_HAND_FOUR_J_K;
            }
            else {
                validateHand = POKER_HAND_FOUR_ACES;
            }
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfDuecesAndJokerWild()
{
    validateHandOfDeucesWild();
}

void CardManager::validateHandOfAcesAndEights()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_KINGS_OR_BETTER:
            validateHand = POKER_HAND_JACKS_OR_BETTER;
            break;
            
        case POKER_HAND_TENS_OR_BETTER:
            validateHand = POKER_HAND_NOTHING;
            break;
            
        case POKER_HAND_FOUR_OF_A_KIND:
            if (mPokerHandData->getKicker() == 13 || mPokerHandData->getKicker() == 7) {
                validateHand = POKER_HAND_FOUR_ACES_OR_EIGHTS;
            }
            else if (mPokerHandData->getKicker() == 6) {
                validateHand = POKER_HAND_FOUR_SEVENS;
            }
            else {
                validateHand = POKER_HAND_FOUR_OF_A_KIND;
            }
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

void CardManager::validateHandOfDoubleBonus()
{
    int validateHand;
    switch (mPokerHandData->getPokerHand()) {
        case POKER_HAND_KINGS_OR_BETTER:
            validateHand = POKER_HAND_JACKS_OR_BETTER;
            break;
            
        case POKER_HAND_TENS_OR_BETTER:
            validateHand = POKER_HAND_NOTHING;
            break;
            
        case POKER_HAND_FOUR_OF_A_KIND:
            if (mPokerHandData->getKicker() < 4 && mPokerHandData->getKicker() > 0) {
                validateHand = POKER_HAND_FOUR_2_4;
            }
            else if (mPokerHandData->getKicker() < 13) {
                validateHand = POKER_HAND_FOUR_5_K;
            }
            else {
                validateHand = POKER_HAND_FOUR_ACES;
            }
            break;
            
        default:
            validateHand = mPokerHandData->getPokerHand();
            break;
    }
    
    mPokerHandData->setPokerHand(validateHand);
}

#pragma mark - get hint bits

int CardManager::getHintBitsOfDealCards()
{
    if (mPokerHandData->getPokerHand() == POKER_HAND_NOTHING) {
        if (mPokerHandData->getNumberJokers() > 0) {
            // get bit location of joker position
            int ret = 0;
            for (int i = 0; i < 5; i++) {
                if (mDealCards->at(i)->getRank() == 14) {
                    ret += (1 << i);
                    break;
                }
            }
            return ret;
        }
        else {
            return 0;
        }
    }
    else {
        return getHandBits(mDealCards);
    }
}

int CardManager::getWonBitsOfDrawCards()
{
    if (mPokerHandData->getPokerHand() == POKER_HAND_NOTHING) {
        return 0;
    }
    else {
        return getHandBits(mDrawCards);
    }
}

int CardManager::getHandBits(vector<Card*>* cards)
{
    int ret = 0;
    // 5 cards
    if(mPokerHandData->getPokerHand() == POKER_HAND_STRAIGHT ||
       mPokerHandData->getPokerHand() == POKER_HAND_FLUSH ||
       mPokerHandData->getPokerHand() == POKER_HAND_FULL_HOUSE ||
       mPokerHandData->getPokerHand() == POKER_HAND_STRAIGHT_FLUSH ||
       mPokerHandData->getPokerHand() == POKER_HAND_FIVE_OF_A_KIND ||
       mPokerHandData->getPokerHand() == POKER_HAND_WILD_ROYAL_FLUSH ||
       mPokerHandData->getPokerHand() == POKER_HAND_NATURAL_ROYAL_FLUSH ||
       mPokerHandData->getPokerHand() == POKER_HAND_FIVE_WILDS) {
        ret = ALL_CARD_MARKED;
    }
    
    // pair, three of a kind, four of a kind
    else if (mPokerHandData->getPokerHand() == POKER_HAND_TENS_OR_BETTER ||
             mPokerHandData->getPokerHand() == POKER_HAND_JACKS_OR_BETTER ||
             mPokerHandData->getPokerHand() == POKER_HAND_KINGS_OR_BETTER ||
             mPokerHandData->getPokerHand() == POKER_HAND_THREE_OF_A_KIND ||
             mPokerHandData->getPokerHand() == POKER_HAND_FOUR_OF_A_KIND ||
             mPokerHandData->getPokerHand() == POKER_HAND_NATURAL_FOUR_DEUCES) {
        int cardRank = mPokerHandData->getLargeGroupRank();
        if (cardRank == 13) {
            cardRank = 0;
        }
        for (int i = 0; i < 5; i++) {
            if (cards->at(i)->getRank() == cardRank) {
                ret += (1 << i);
            }
            else if (cards->at(i)->getRank() == 14) {
                ret += (1 << i);
            }
        }
    }
    // two pair
    else if (mPokerHandData->getPokerHand() == POKER_HAND_TWO_PAIR) {
        int cardRank = mPokerHandData->getLargeGroupRank();
        if (cardRank == 13) {
            cardRank = 0;
        }
        for (int i = 0; i < 5; i++) {
            if (cards->at(i)->getRank() == cardRank ||
                cards->at(i)->getRank() == mPokerHandData->getSmallGroupRank()) {
                ret += (1 << i);
            }
        }
    }
    
    return ret;
}
