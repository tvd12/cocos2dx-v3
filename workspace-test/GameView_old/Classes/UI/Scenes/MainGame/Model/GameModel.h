//
//  GameModel.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#ifndef __DragonVideoPoker__GameModel__
#define __DragonVideoPoker__GameModel__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Card;
class Deck;
class ChipBetted;
class Paytable;
class UserInfo;
class RoomInfo;
class TdgDealCardData;
class TdgDrawCardData;

class GameModel : public CCObject
{
public:
    bool init();
    virtual ~GameModel(void);
    CREATE_FUNC(GameModel);

    bool updateBetChipWithType(int chipType);
    void updateCancelBetChip();
    bool updateMaxBet();
    bool updateCollectWonChips();
    bool updateRepeatLastBet();
    
    void updateMainGameFinish();
    
    void updateDealCardSelected(int cardPosition);
    void updateDealCards(int* dealCards, int hintBit);
    void updateDrawCards(int* drawCards, int wonBit, int wonHand, long long wonValue, bool isGotJackpot);
    
    void updateDonCardSelected(int cardPosition);
    void updateDonDealerCard(int dealerCard);
    void updateDonCards(int* donCards, long long wonValue);
    
    void checkLevelUp();
    
    CC_SYNTHESIZE_READONLY(ChipBetted*, mChipBetted, ChipBetted);
    CC_SYNTHESIZE_READONLY(Paytable*, mPaytable, Paytable);
    CC_SYNTHESIZE_READONLY(Deck*, mDeck, Deck);
    CC_SYNTHESIZE_READONLY(bool, mIsGotLevelUp, IsGotLevelUp);

    CC_SYNTHESIZE(UserInfo*, mUserInfo, UserInfo);
    CC_SYNTHESIZE(RoomInfo*, mRoomInfo, RoomInfo);
    
    CC_SYNTHESIZE(int, mDonResult, DonResult);

private:    
    vector<Card *> *mDealCards;
    vector<Card *> *mDrawCards;
    
    long mLastLevel;
};

#endif /* defined(__DragonVideoPoker__GameModel__) */
