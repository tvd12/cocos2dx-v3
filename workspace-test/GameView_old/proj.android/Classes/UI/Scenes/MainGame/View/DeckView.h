//
//  DeckView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__DeckView__
#define __DragonVideoPoker__DeckView__

#define DELAY_SHOW_CARD         0.1f

#include "SingLeton.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Deck;
class CardView;
class Card;

class DeckView : public SingLeton<DeckView>
{
public:
    DeckView();
    ~DeckView();
    
    Deck* getDeck() {return mDeck;};
    
    void addDeckToLayer(CCLayer *layer, int zOrder);
    
    void showBackOfDealCards();
    void showBackOfDrawCards();
    void showBackOfDonDealerCard();
    void showBackOfDonCards();
    
    float flipOutDealCards();
    float flipOutDrawCards();
    float flipOutDonDealerCard();
    float flipOutDonCards();
    void turnIntoAllDrawCards();

    void showDealerCardOnDon();
    void showPlayerCardsOnDon();

    void turnIntoCardViewsOnDrawPosition();
    void hideCardViewsOnTable();
    
private:
    CardView* getCardView(Card *card);
    
    Deck *mDeck;
    
    CCArray *mCardViews;
    CCArray *mCardViewsOnTable;
};

#define DECK_VIEW() DeckView::getSingleton()

#endif /* defined(__DragonVideoPoker__DeckView__) */
