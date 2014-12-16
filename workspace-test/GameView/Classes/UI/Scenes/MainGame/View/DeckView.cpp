//
//  DeckView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "DeckView.h"
#include "Deck.h"
#include "Card.h"
#include "CardView.h"
#include "GameParams.h"


DeckView::~DeckView()
{
    mCardViews->removeAllObjects();
    mCardViews->release();
    mCardViewsOnTable->removeAllObjects();
    mCardViewsOnTable->release();
}

DeckView::DeckView()
{
    mDeck = Deck::create();
    mDeck->retain();
    mCardViews = CCArray::create();
    mCardViews->retain();
    mCardViewsOnTable = CCArray::create();
    mCardViewsOnTable->retain();
    
    // init cardViews
    vector<Card*> *cards = mDeck->getCards();
    for (vector<Card*>::iterator it = cards->begin();
         it != cards->end();
         ++it) {
        Card* card = *it;
        CardView* cardView = CardView::create(card);
        mCardViews->addObject(cardView);
    }
}

void DeckView::addDeckToLayer(CCLayer *layer, int zOrder)
{
    for (int i = 0; i < mCardViews->count(); i++) {
        CardView* cardView = (CardView*)mCardViews->objectAtIndex(i);
//        cardView->removeFromLayer();
        // add to this layer
        cardView->addToLayer(layer, zOrder);
//        cardView->hideCard();
    }
}

#pragma mark - Main game

void DeckView::showBackOfDealCards()
{
    vector<Card*> *dealCards = mDeck->getDealCards();
    mCardViewsOnTable->removeAllObjects();
    
    for (int i = 0; i < 5; i++) {
        Card* dealCard = dealCards->at(i);
        CardView* dealCardView = getCardView(dealCard);
        dealCardView->showBackCard(GPARAMS().MAIN_CARDS_POSITIONS[i]);
        mCardViewsOnTable->addObject(dealCardView);
    }
}

void DeckView::showBackOfDrawCards()
{
    // hide card on table first
    vector<Card*> *drawCards = mDeck->getDrawCards();
    int heldBit = mDeck->getHeldBit();
    
    for (int i = 0; i < 5; i++) {
        if ((heldBit & (1 << i)) == 0) {
            Card* drawCard = drawCards->at(i);
            CardView* drawCardView = getCardView(drawCard);
            drawCardView->showBackCard(GPARAMS().MAIN_CARDS_POSITIONS[i]);
            
            // update card on table
            ((CardView*)mCardViewsOnTable->objectAtIndex(i))->hideCard();
            mCardViewsOnTable->replaceObjectAtIndex(i, drawCardView);
        }
    }
}

void DeckView::showBackOfDonDealerCard()
{
    Card* dealerCard = mDeck->getDonCards()->at(0);
    CardView* dealerCardView = getCardView(dealerCard);
    dealerCardView->showBackCard(GPARAMS().MAIN_CARDS_POSITIONS[0]);
    
    mCardViewsOnTable->removeAllObjects();
    mCardViewsOnTable->addObject(dealerCardView);
}

void DeckView::showBackOfDonCards()
{
    vector<Card*> *donCards = mDeck->getDonCards();
    for (int i = 1; i < 5; i++) {
        Card* donCard = donCards->at(i);
        CardView* donCardView = getCardView(donCard);
        donCardView->showBackCard(GPARAMS().MAIN_CARDS_POSITIONS[i]);
        mCardViewsOnTable->addObject(donCardView);
    }
}

void DeckView::turnIntoAllDrawCards()
{
    vector<Card*> *drawCards = mDeck->getDrawCards();
    
    for (int i = 0; i < 5; i++) {
        Card* drawCard = drawCards->at(i);
        CardView* drawCardView = getCardView(drawCard);
        drawCardView->turnnIntoCardView(0);
    }
}

float DeckView::flipOutDealCards()
{
    float delay = 0;
    for (int i = 0; i < 5; i++) {
        ((CardView*)mCardViewsOnTable->objectAtIndex(i))->flipOutCardView(delay);
        delay += DELAY_SHOW_CARD;
    }
    
    return delay;
}

float DeckView::flipOutDrawCards()
{
    int heldBit = mDeck->getHeldBit();
    float delay = 0;

    for (int i = 0; i < 5; i++) {
        if ((heldBit & (1 << i)) == 0) {
            ((CardView*)mCardViewsOnTable->objectAtIndex(i))->flipOutCardView(delay);
            delay += DELAY_SHOW_CARD;
        }
    }
    
    return delay;
}

float DeckView::flipOutDonDealerCard()
{
    ((CardView*)mCardViewsOnTable->objectAtIndex(0))->flipOutCardView(0);
    return 0;
}

float DeckView::flipOutDonCards()
{
    float delay = 0;
    
    for (int i = 1; i < 5; i++) {
        ((CardView*)mCardViewsOnTable->objectAtIndex(i))->flipOutCardView(delay);
        delay += DELAY_SHOW_CARD;
    }
    
    return delay;
}

CardView* DeckView::getCardView(Card *card)
{
    CardView* cardView = (CardView*)mCardViews->objectAtIndex(card->getCardNumber());
    return cardView;
}

void DeckView::hideCardViewsOnTable()
{
    for (int i = 0; i < 5; i++) {
        CardView* cardView = ((CardView*)mCardViewsOnTable->objectAtIndex(i));
        cardView->hideCard();
    }
}

void DeckView::turnIntoCardViewsOnDrawPosition()
{
    int heldBit = mDeck->getHeldBit();
    
    for (int i = 0; i < 5; i++) {
        if ((heldBit & (1 << i)) == 0) {
            CardView* drawCardView = ((CardView*)mCardViewsOnTable->objectAtIndex(i));
            drawCardView->turnnIntoCardView(0);
        }
    }
}

#pragma mark - Double or Nothing

void DeckView::showDealerCardOnDon()
{
    
}

void DeckView::showPlayerCardsOnDon()
{
    
}
