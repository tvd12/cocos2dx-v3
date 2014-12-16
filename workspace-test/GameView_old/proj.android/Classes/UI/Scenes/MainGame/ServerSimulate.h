//
//  ServerSimulate.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/15/14.
//
//

#ifndef __DragonVideoPoker__ServerSimulate__
#define __DragonVideoPoker__ServerSimulate__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class CardManager;

class ServerSimulate : public CCObject
{
    
public:
	ServerSimulate();
    void updateJackpot();
    void updateLevel();
    
    void sendDealCardsRequest(long long betChips);
    void sendDrawCardsRequest(int heldBits);
    
    void sendDonDealerCardRequest();
    void sendDonCardsRequest(int heldPosition);

private:
    void simulateRoomVariables();
    void simulateUserInfo();
    void simulatePaytable();
    
    void simulateSendDealCards();
    void simulateSendDrawCards();
    
    void simulateSendDonDealerCard();
    void simulateSendDonCards();

    CCDirector *mDirector;
    CardManager *mCardManager;
    
};

#endif /* defined(__DragonVideoPoker__ServerSimulate__) */
