//
//  PaytablePopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/19/14.
//
//

#include "PaytablePopupView.h"
#include "GameParams.h"
#include "VisibleRect.h"
#include "Paytable.h"
#include "PaytablePopupCellView.h"
#include "CardView.h"
#include "PaytableCell.h"
#include "Card.h"
#include "VideoPokerDefine.h"
#include "SoundManager.h"


enum Hand {
    NATURAL_ROYAL_FLUSH_INDEX   = 21,
    STRAIGHT_FLUSH_INDEX        = 17,
    FOUR_OF_A_KIND_INDEX        = 9,
    FULL_HOUSE_INDEX            = 8,
    FLUSH_INDEX                 = 7,
    STRAIGHT_INDEX              = 6,
    THREE_OF_A_KIND_INDEX       = 5,
    TWO_PAIR_INDEX              = 4,
    JACKS_OR_BETTER_INDEX       = 2
};

PaytablePopupView::PaytablePopupView() :
PopUpLayer(),
mCurrentSelectedHand(0){
    
};

PaytablePopupView::~PaytablePopupView() {
    mPaytablePopupCellViews->clear();
    delete mPaytablePopupCellViews;
}

PaytablePopupView* PaytablePopupView::create(Paytable* pPaytable,
                                             const int pCurrentSelectedHand,
                                             string pBackgroundImage,
                                             string pExitNormalImage,
                                             string pExitSelectedImage
                                             ) {
    PaytablePopupView *pRet = new PaytablePopupView();
    pRet->autorelease();
    pRet->init(pPaytable,
               pCurrentSelectedHand,
               pBackgroundImage,
               pExitNormalImage,
               pExitSelectedImage);
    return pRet;
}

bool PaytablePopupView::init(Paytable* pPaytable,
                             const int pCurrentSelectedHand,
                             string pBackgroundImage,
                             string pExitNormalImage,
                             string pExitSelectedImage
                             ) {
    this->mCurrentSelectedHand = pCurrentSelectedHand;
    this->mPaytable = pPaytable;
    
    CCPoint exitPostion = CCPoint(GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    PopUpLayer::init(pBackgroundImage, pExitNormalImage, pExitSelectedImage, exitPostion);
    setBackgroundPosition(VisibleRect::center());
    
    this->setPayoutPosition();
    
    return true;
}

void PaytablePopupView::addSprites() {
    PopUpLayer::addSprites();
    
    CCSprite *headerSprite = CCSprite::create("paytable_banner.png");
    headerSprite->setPosition(GPARAMS().POP_COMMON_HEADER_POSITION);
    mBackgroundSprite->addChild(headerSprite);
    
    mCardViewContainer = CCSprite::create("paytable_poker_bg.png");
    mCardViewContainer->setPosition(GPARAMS().POP_PAYTABLE_CARD_VIEW_CONTAINER_POSITION);
    mBackgroundSprite->addChild(mCardViewContainer);
    
    mPayoutSprite = CCSprite::create("text_payout.png");
    mBackgroundSprite->addChild(mPayoutSprite);
    
    this->addCardSprites();
    
}

void PaytablePopupView::addMenuItems() {
    PopUpLayer::addMenuItems();
    int size = mPaytable->getPaytableCells()->size();
    vector<PaytableCell*> *paytableCells = mPaytable->getPaytableCells();
    mPaytablePopupCellViews = new vector<PaytablePopupCellView*>();
    
    for(int i = 0 ; i < size && paytableCells->at(i)->getHandType() != PAYTABLE_EMPTY ; i++) {
        PaytablePopupCellView* paytablePopupCellView =
        PaytablePopupCellView::create(paytableCells->at(i),
                                      this,
                                      menu_selector(PaytablePopupView::handMenuItemCallback));
        CCPoint position = GPARAMS().POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[i];
        paytablePopupCellView->setPosition(position);
        paytablePopupCellView->setTag(paytableCells->at(i)->getHandType());
        mPopupMenu->addChild(paytablePopupCellView);
        mPaytablePopupCellViews->push_back(paytablePopupCellView);
    }
    for(int i = mPaytablePopupCellViews->size() ; i < 12 ; i++) {
        CCPoint position = GPARAMS().POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[i];
        CCMenuItem *emptySprite = PaytablePopupCellView::createEmptyMenuItem(position);
        mPopupMenu->addChild(emptySprite);
    }
}

void PaytablePopupView::addCardSprites() {
    int cardValues[][5] = {
        {9, 9 + 1*13, -1, -1, -1}, //tens or better 1
        {10, 13*3 + 10, -1, -1, -1}, //jacks or better 2
        {12, 12 + 1*13, -1, -1, -1}, //kings or better 3
        {13*2, 13*3, 13*1 + 2, 2, -1}, //two pair 4
        {4, 13*1 + 4, 13*2 + 4, -1, -1}, //three of a kind 5
        {2, 13*1 + 3, 13*2 + 4, 5, 13*3 + 6}, //straight 6
        {3, 12, 8, 6, 9}, //flush 7
        {8, 1*13 + 8, 2*13 + 8, 2, 1*13 + 2},   //full house 8
        {6, 13*1 + 6, 13*2 + 6, 13*3 + 6, -1},  //four of a kind 9
        {6, 6 + 1*13, 6 + 2*13, 6 + 3*13, -1}, //four sevens 10
        {4, 4 + 1*13, 4 + 2*13, 4 + 3*13, -1}, //four 5-10 11
        {1, 1 + 1*13, 1 + 2*13, 1 + 3*13, -1}, //four 2-4 12
        {9, 9 + 1*13, 9 + 2*13, 9 + 3*13, -1}, //four 2-10 13
        {10, 10 + 1*13, 10 + 2*13, 10 + 3*13, -1}, //four j-k 14
        {0, 13, 26, 39, -1}, //four aces 15
        {7, 7 + 1*13, 7 + 2*13, 7 + 3*13, -1}, //four aces or eights 16
        {2, 3, 4, 5, 6},    //straight flush 17
        {6, 6 + 1*13, 6 + 2 *13, 6 + 3*13, 52}, //five of a kind 18
        {9 + 3*13, 10 + 3*13, 11 + 3*13, 12 + 3*13, 52}, //wild royal flush 19
        {53, 54, 55, 56, -1}, //natural four deuces 20
        {48, 49, 50, 51, 13*3}, //natural royal flush 20
        {53, 54, 55, 56, 52}, //five wilds 21
    };
    int size = mPaytable->getPaytableCells()->size();
    mCardViewMap = map<const int, vector<CardView*> >();
    
    //temporary
    for(int i = 0  ; i < size ; i++) {
        const int handType = mPaytable->getPaytableCells()->at(i)->getHandType();
        vector<CardView*> cardViews = vector<CardView*>(5);
        for(int k = 0 ; k < 5 && handType != PAYTABLE_EMPTY ; k++) {
            int value = cardValues[handType - 1][k];
            Card *card = new Card((value >= 0) ? value : 10);
            cardViews[k] = CardView::create(card, GPARAMS().POP_PROFILE_CARD_SCALE);
            cardViews[k]->retain();
            cardViews[k]->setPosition(GPARAMS().POP_PAYTABLE_CARDS_POSTIONS[k]);
            cardViews[k]->addToParent(mBackgroundSprite, 100);
            cardViews[k]->hideCard();
            cardViews[k]->setTag(value);
        }
        mCardViewMap.insert(pair<const int, vector<CardView*> >(handType, cardViews));
    }
    showExampleCards();
}

void PaytablePopupView::addLabels() {
    mHandMultipleLabel = CCLabelTTF::create("X1",
                                            DEFAULT_FONT_NAME,
                                            GPARAMS().CMM_FONT_SIZE_4);
    mBackgroundSprite->addChild(mHandMultipleLabel);
}

void PaytablePopupView::setPayoutPosition() {
    CCString *multiple =
    CCString::createWithFormat("X%d", mCurrentSelectedCell->getPaytableCell()->getHandMultiple());
    if(mCurrentSelectedCell->getPaytableCell()->getHandMultiple() == JACKPOT_MULTIPLE) {
        multiple = CCString::create("JACKPOT");
    }
    mHandMultipleLabel->setString(multiple->getCString());

    mPayoutSprite->setPosition(GPARAMS().POP_PAYTABLE_PAYOUT_SPRITE_POSITION);
    mPayoutSprite->setAnchorPoint(CCPoint(0.5f, 0.0f));

    mHandMultipleLabel->setAnchorPoint(CCPoint(0, 0.0f));
    mHandMultipleLabel->setPosition(GPARAMS().POP_PAYTABLE_PAYOUT_LABEL_POSITION);
}

void PaytablePopupView::showExampleCards() {
    for(int i = 0 ; i < mCardViewMap[mCurrentSelectedHand].size() ; i++) {
        if(mCardViewMap[mCurrentSelectedHand].at(i)->getTag() == -1) {
            mCardViewMap[mCurrentSelectedHand].at(i)->showBackCard();
        }
        else  {
            mCardViewMap[mCurrentSelectedHand].at(i)->flipOutCardView(0);
        }
    }
    
    vector<PaytableCell*> *paytableCells = mPaytable->getPaytableCells();
    
    for(int i = 0 ; i < paytableCells->size() ; i++) {
        if(paytableCells->at(i)->getHandType() == mCurrentSelectedHand) {
            mPaytablePopupCellViews->at(i)->selected();
            mCurrentSelectedCell = mPaytablePopupCellViews->at(i);
            break;
        }
    }
}

void PaytablePopupView::handMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    CCNode *item = static_cast<CCNode*>(pSender);
    mCurrentSelectedCell->unselected();
    for(int i = 0 ; i < mCardViewMap[mCurrentSelectedHand].size() ; i++) {
        mCardViewMap[mCurrentSelectedHand].at(i)->hideCard();
    }
    mCurrentSelectedHand = item->getTag();
    showExampleCards();
    setPayoutPosition();
}

