//
//  CardView.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "CardView.h"
#include "Card.h"
#include "GameParams.h"
#include "SoundManager.h"


CardView * CardView::create(Card* card, float pScale)
{
    CardView *pRet = new CardView();
    pRet->initWithCard(card, pScale);
    pRet->autorelease();
    return pRet;
}

bool CardView::initWithCard(Card* card, float scale)
{
    mCard = card;
    
    createFrontCard();
    createBackCard();
    
    mBackCard->setScale(scale);
    mFrontCard->setScale(scale);

    return true;
}

void CardView::createFrontCard()
{
    ccColor3B numberColor;
    
    // get color
    switch (mCard->getSuit()) {
        case SUIT_SPADES:
        case SUIT_CLUBS:
            numberColor = CARD_BLACK;
            break;
            
        case SUIT_HEARTS:
        case SUIT_DIAMONDS:
            numberColor = CARD_RED;
            break;
            
        default:
            numberColor = CARD_BLACK;
            break;
    }
    
    // create front card
    mFrontCard = CCSprite::create("cards/card_front.png");
    mFrontCard->retain();
    
    // create number
    string numberStr;
    if (mCard->getRank() == 0) {
        numberStr = "A";
    }
    else if (mCard->getRank() < 9) {
        numberStr = string(CCString::createWithFormat("%d", mCard->getRank() + 1)->getCString());
    }
    else if (mCard->getRank() == 9) {
        numberStr = "10";
    }
    else if (mCard->getRank() == 10) {
        numberStr = "J";
    }
    else if (mCard->getRank() == 11) {
        numberStr = "Q";
    }
    else if (mCard->getRank() == 12) {
        numberStr = "K";
    }
    else if (mCard->getRank() == 14) {
        if (mCard->getSuit() == SUIT_JOKERS) {
            numberStr = "JOKER";
        }
        else {
            numberStr = "2";
        }
    }
    
    // add rank label
    mNumberLabel = CCLabelTTF::create(numberStr.c_str(),
                                      DEFAULT_FONT_NAME,
                                      GPARAMS().CMM_CARD_FONT_SIZE);
    mNumberLabel->setColor(numberColor);
    mNumberLabel->setAnchorPoint(CCPoint(0.5f, 0.5f));
    mFrontCard->addChild(mNumberLabel, 1);
    
    // add small suit icon
    switch (mCard->getRank()) {
        case 10:
        case 11:
        case 12:
            createJQKCards();
            break;

        case 0:
            createAceCards();
            break;
            
        case 14:
            if (mCard->getSuit() == SUIT_JOKERS) {
                createJokerCard();
            }
            else {
                createWildCards();
            }
            break;
            
        default:
            create2To10Cards();
            break;
    }
}

void CardView::createJokerCard()
{
    mNumberLabel->setPosition(GPARAMS().CARD_JOKER_LABEL_POSITION);
    
    // joker icon
    CCSprite* jokerIcon = CCSprite::create("cards/joker.png");
    jokerIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    jokerIcon->setPosition(GPARAMS().CARD_JOKER_ICON_POSITION);
    mFrontCard->addChild(jokerIcon, 1);
}

void CardView::createWildCards()
{
    mNumberLabel->setPosition(GPARAMS().CARD_RANK_LABEL_POSITION);
    
    // add small suit icon
    CCString* smallSuitString = CCString::createWithFormat("cards/card_suit_%d_s.png",
                                                           mCard->getSuit());
    CCSprite* smallSuitIcon = CCSprite::create(smallSuitString->getCString());
    smallSuitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    smallSuitIcon->setPosition(GPARAMS().CARD_SUIT_SMALL_ICON_POSITION);
    mFrontCard->addChild(smallSuitIcon, 1);
    
    // wild icon
    CCSprite* wildIcon = CCSprite::create("cards/card_wild.png");
    wildIcon->setScale(1.2f);
    wildIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    wildIcon->setPosition(GPARAMS().CARD_WILD_ICON_POSITION);
    mFrontCard->addChild(wildIcon, 1);
}

void CardView::createJQKCards()
{
    mNumberLabel->setPosition(GPARAMS().CARD_RANK_LABEL_POSITION);
    
    // add small suit icon
    CCString* smallSuitString = CCString::createWithFormat("cards/card_suit_%d_s.png",
                                                           mCard->getSuit());
    CCSprite* smallSuitIcon = CCSprite::create(smallSuitString->getCString());
    smallSuitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    smallSuitIcon->setPosition(GPARAMS().CARD_SUIT_SMALL_ICON_POSITION);
    mFrontCard->addChild(smallSuitIcon, 1);
    
    // add JQK icon
    const char* iconFormat = NULL;
    switch (mCard->getRank()) {
        case 10:
            iconFormat = "cards/card_j_%d.png";
            break;
        case 11:
            iconFormat = "cards/card_q_%d.png";
            break;
        case 12:
            iconFormat = "cards/card_k_%d.png";
            break;
        default:
            break;
    }
    CCString* suitString = CCString::createWithFormat(iconFormat,
                                                      mCard->getSuit());
    CCSprite* suitIcon = CCSprite::create(suitString->getCString());
    suitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    suitIcon->setPosition(GPARAMS().CARD_SUIT_ICON_POSITION);
    mFrontCard->addChild(suitIcon, 1);
}

void CardView::createAceCards()
{
    mNumberLabel->setPosition(GPARAMS().CARD_RANK_LABEL_POSITION);
    
    // add small suit icon
    CCString* smallSuitString = CCString::createWithFormat("cards/card_suit_%d_s.png",
                                                           mCard->getSuit());
    CCSprite* smallSuitIcon = CCSprite::create(smallSuitString->getCString());
    smallSuitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    smallSuitIcon->setPosition(GPARAMS().CARD_SUIT_SMALL_ICON_POSITION);
    mFrontCard->addChild(smallSuitIcon, 1);
    
    // add suit icon
    CCString* suitString = CCString::createWithFormat("cards/card_ace_%d.png",
                                                      mCard->getSuit());
    CCSprite* suitIcon = CCSprite::create(suitString->getCString());
    suitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    suitIcon->setPosition(GPARAMS().CARD_SUIT_ICON_POSITION);
    mFrontCard->addChild(suitIcon, 1);
}

void CardView::create2To10Cards()
{
    mNumberLabel->setPosition(GPARAMS().CARD_RANK_LABEL_POSITION);
    
    // add small suit icon
    CCString* smallSuitString = CCString::createWithFormat("cards/card_suit_%d_s.png",
                                                           mCard->getSuit());
    CCSprite* smallSuitIcon = CCSprite::create(smallSuitString->getCString());
    smallSuitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    smallSuitIcon->setPosition(GPARAMS().CARD_SUIT_SMALL_ICON_POSITION);
    mFrontCard->addChild(smallSuitIcon, 1);
    
    // add suit icon
    CCString* suitString = CCString::createWithFormat("cards/card_suit_%d.png",
                                                           mCard->getSuit());
    CCSprite* suitIcon = CCSprite::create(suitString->getCString());
    suitIcon->setAnchorPoint(ccp(0.5f, 0.5f));
    suitIcon->setPosition(GPARAMS().CARD_SUIT_ICON_POSITION);
    mFrontCard->addChild(suitIcon, 1);
}

void CardView::createBackCard()
{
    mBackCard = CCSprite::create("cards/card_back.png");
    mBackCard->retain();
}

void CardView::addToLayer(CCLayer *layer, int zOrder)
{
    layer->addChild(mFrontCard, zOrder);
    layer->addChild(mBackCard, zOrder+1);
    mFrontCard->setVisible(false);
    mBackCard->setVisible(false);
}

void CardView::addToParent(CCNode *pParent, int zOrder) {
    pParent->addChild(mFrontCard, zOrder);
    pParent->addChild(mBackCard, zOrder+1);
    mFrontCard->setVisible(false);
    mBackCard->setVisible(false);
}

void CardView::removeFromLayer()
{
    mFrontCard->removeFromParentAndCleanup(false);
    mBackCard->removeFromParentAndCleanup(false);
}

void CardView::showBackCard(CCPoint position)
{
    mFrontCard->setPosition(position);
    mBackCard->setPosition(position);
    
    mFrontCard->setVisible(true);
    mBackCard->setVisible(true);
    mIsFlipped = false;
}

void CardView::showBackCard()
{
    mFrontCard->setVisible(true);
    mBackCard->setVisible(true);
    mIsFlipped = false;
}

void CardView::hideCard()
{
    mFrontCard->setVisible(false);
    mBackCard->setVisible(false);
}

void CardView::flipOutCardView(float delayTime)
{
    hideSpriteAnimation(mBackCard, delayTime);
    showSpriteAnimation(mFrontCard, delayTime);
    
    mIsFlipped = true;
}

void CardView::turnnIntoCardView(float delayTime)
{
    mBackCard->setVisible(true);
    mFrontCard->setVisible(false);

    mIsFlipped = false;
}

void CardView::setPosition(const CCPoint &pPosition) {
    mBackCard->setPosition(pPosition);
    mFrontCard->setPosition(pPosition);
}

void CardView::showSpriteAnimation(CCSprite* sprite, float delayTime)
{
    sprite->stopAllActions();
    CCDelayTime* delay = CCDelayTime::create(delayTime);
    
    float scaleMax = sprite->getScaleY();
    CCActionInterval *flipHideCard = CCScaleTo::create(FLIP_ONE_CARD_ANIMATION, 0.0f, scaleMax);
    CCActionInterval *flipShowCard = CCScaleTo::create(FLIP_ONE_CARD_ANIMATION, scaleMax, scaleMax);
    
    CCCallFuncN *showCard = CCCallFuncN::create(this,
                                                callfuncN_selector(CardView::showSprite));
    CCSequence *sequence = CCSequence::create(delay, flipHideCard, showCard, flipShowCard, NULL);
    sprite->runAction(sequence);
}

void CardView::hideSpriteAnimation(CCSprite* sprite, float delayTime)
{
    sprite->stopAllActions();
    CCDelayTime* delay = CCDelayTime::create(delayTime);

    float scaleMax = sprite->getScaleY();
    CCActionInterval *flipHideCard = CCScaleTo::create(FLIP_ONE_CARD_ANIMATION, 0.0f, scaleMax);
    CCActionInterval *flipShowCard = CCScaleTo::create(FLIP_ONE_CARD_ANIMATION, scaleMax, scaleMax);

    CCCallFuncN *hideCard = CCCallFuncN::create(this,
                                                callfuncN_selector(CardView::hideSprite));
    CCSequence *sequence = CCSequence::create(delay, flipHideCard, hideCard, flipShowCard, NULL);
    sprite->runAction(sequence);
}

void CardView::showSprite(CCNode* sender)
{
    SOUND().playSound(SOUND_FLIP_CARD);
    
    sender->setVisible(true);
}

void CardView::hideSprite(CCNode* sender)
{
    sender->setVisible(false);
}

