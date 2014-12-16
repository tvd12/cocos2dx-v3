//
//  CardView.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__CardView__
#define __DragonVideoPoker__CardView__

#define FLIP_ONE_CARD_ANIMATION                 0.1f

#include "cocos2d.h"

USING_NS_CC;

static ccColor3B CARD_RED           = {204, 0, 0};
static ccColor3B CARD_BLACK         = {26, 26, 26};

class Card;

class CardView : public CCObject
{
public:    
    static CardView * create(Card* card, float pScale = 1.0f);
    bool initWithCard(Card* card, float scale);
    
    void addToLayer(CCLayer *layer, int zOrder);
    void addToParent(CCNode *pParent, int zOrder);
    void removeFromLayer();
    
    void showBackCard(CCPoint position);
    void showBackCard();
    void hideCard();
    
    void flipOutCardView(float delayTime);
    void turnnIntoCardView(float delayTime);
    
    bool isCardFlipped(){return mIsFlipped;};
    void setPosition(const CCPoint &pPosition);
    
    CC_SYNTHESIZE(Card*, mCard, Card);
    CC_SYNTHESIZE(int, mTag, Tag);
    
private:
    void createFrontCard();
    void createBackCard();
    void createJokerCard();
    void createWildCards();
    void createJQKCards();
    void createAceCards();
    void create2To10Cards();
    
    void showSpriteAnimation(CCSprite* sprite, float delayTime);
    void hideSpriteAnimation(CCSprite* sprite, float delayTime);
    void showSprite(CCNode* sender);
    void hideSprite(CCNode* sender);
    
    CCLabelTTF *mNumberLabel;
    CCSprite *mBackCard;
    CCSprite *mFrontCard;
    
    bool mIsFlipped;
};

#endif /* defined(__DragonVideoPoker__CardView__) */
