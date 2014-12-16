//
//  ServerSimulate.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/15/14.
//
//

#include "ServerSimulate.h"
#include "VideoPokerDefine.h"

#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "TdgDealCardData.h"
#include "TdgDrawCardData.h"
#include "TdgDonCardData.h"

#include "UserInfo.h"
#include "RoomInfo.h"

#include "PaytableCell.h"
#include "Paytable.h"

#include "CardManager.h"
#include "VideoPokerDefine.h"


ServerSimulate::ServerSimulate()
{
    mDirector = CCDirector::sharedDirector();
    
    mCardManager = CardManager::create(JACKS_OR_BETTER);
    mCardManager->retain();
    
//    simulateRoomVariables();
//    simulateUserInfo();
//    simulatePaytable();
}

void ServerSimulate::simulateRoomVariables()
{
    ROOMINFO()->setJackpot(3000000);
    ROOMINFO()->setChip1(50);
    ROOMINFO()->setChip2(500);
    ROOMINFO()->setChip3(5000);
    ROOMINFO()->setMaxStakes(20000);
}

void ServerSimulate::simulateUserInfo()
{
    USERINFO()->setTotalChips(300000);
    USERINFO()->setLevel(1);
}

void ServerSimulate::simulatePaytable()
{
    PaytableCell* paytableCell;
    
    paytableCell = PaytableCell::create(21, "Natural Royal Flush", -1);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(17, "Straight Flush", 50);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(9, "Four of a Kind", 25);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(8, "Full House", 9);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(7, "Flush", 6);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(6, "Straight", 4);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(5, "Three of a Kind", 3);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(4, "Two Pair", 2);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(2, "Jacks Or Better", 1);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(PAYTABLE_EMPTY, "", -1);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
    
    paytableCell = PaytableCell::create(PAYTABLE_EMPTY, "", -1);
    paytableCell->retain();
    PAYTABLE()->push_back(paytableCell);
}

void ServerSimulate::updateJackpot() {
    ROOMINFO()->setJackpot(ROOMINFO()->getJackpot() + 5000);
}

void ServerSimulate::updateLevel() {
    USERINFO()->setExperience(USERINFO()->getExperience() + 2);
    USERINFO()->setLevel(USERINFO()->getLevel() + 1);
}

void ServerSimulate::sendDealCardsRequest(long long betChips)
{
    mCardManager->createDealCards(betChips);
    
    // notify to controller
    mDirector->getScheduler()->scheduleSelector(schedule_selector(ServerSimulate::simulateSendDealCards),
                                                this,
                                                0.05f,
                                                0,
                                                0.5f,
                                                false);
}

void ServerSimulate::sendDrawCardsRequest(int heldBits)
{
    mCardManager->createDrawCards(heldBits, 10000000);
    
    // notify to controller
    mDirector->getScheduler()->scheduleSelector(schedule_selector(ServerSimulate::simulateSendDrawCards),
                                                this,
                                                0.05f,
                                                0,
                                                0.5f,
                                                false);
}

void ServerSimulate::sendDonDealerCardRequest()
{
    mCardManager->createDonDealerCard();
    
    // notify to controller
    mDirector->getScheduler()->scheduleSelector(schedule_selector(ServerSimulate::simulateSendDonDealerCard),
                                                this,
                                                0.05f,
                                                0,
                                                0.5f,
                                                false);
}

void ServerSimulate::sendDonCardsRequest(int heldPosition)
{
    mCardManager->createDonPlayerCards(heldPosition);
    
    // notify to controller
    mDirector->getScheduler()->scheduleSelector(schedule_selector(ServerSimulate::simulateSendDonCards),
                                                this,
                                                0.05f,
                                                0,
                                                0.5f,
                                                false);
}

void ServerSimulate::simulateSendDealCards()
{
    vector<int> dealCardsServer = mCardManager->getDealCards();
    vector<int>* dealCards = DEALCARDS()->getDealCards();

    CCLOG("Got 5 deal cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%d", dealCardsServer[i]);
        dealCards->at(i) = dealCardsServer[i];
    }
    
    DEALCARDS()->setHintBits(mCardManager->getHintCardBits());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DEAL_CARDS,
                                                                       DEALCARDS());
}

void ServerSimulate::simulateSendDrawCards()
{
    vector<int> drawCardsServer = mCardManager->getDrawCards();
    vector<int>* drawCards = DRAWCARDS()->getDrawCards();
    
    CCLOG("Got 5 draw cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%d", drawCardsServer[i]);
        drawCards->at(i) = drawCardsServer[i];
    }
    
    CCLOG("won Bits: %d", mCardManager->getWonCardBits());
    CCLOG("won id: %ld", mCardManager->getWonHandId());
    CCLOG("won chips: %lld", mCardManager->getWonChips());

    DRAWCARDS()->setWonBit(mCardManager->getWonCardBits());
    DRAWCARDS()->setWonHandType(mCardManager->getWonHandId());
    DRAWCARDS()->setWonValue(mCardManager->getWonChips());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DRAW_CARDS,
                                                                       DRAWCARDS());
}

void ServerSimulate::simulateSendDonDealerCard()
{
    int donDealerCard = mCardManager->getDonDealerCard();
    vector<int>* donCards = DONCARDS()->getDonCards();
    donCards->at(0) = donDealerCard;
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DON_DEALER_CARD,
                                                                       DONCARDS());
}

void ServerSimulate::simulateSendDonCards()
{
    vector<int> donCardsServer = mCardManager->getDonCards();
    vector<int>* donCards = DONCARDS()->getDonCards();
    
    CCLOG("Got 5 DON cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%d", donCardsServer[i]);
        donCards->at(i) = donCardsServer[i];
    }

    DONCARDS()->setWonChips(mCardManager->getWonChips());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DON_CARDS,
                                                                       DONCARDS());
}

