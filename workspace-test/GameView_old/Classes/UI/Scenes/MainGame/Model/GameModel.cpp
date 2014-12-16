//
//  GameModel.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#include "GameModel.h"
#include "ChipBetted.h"
#include "Paytable.h"
#include "Deck.h"
#include "DeckView.h"

#include "TdgServer.h"
#include "UserInfo.h"
#include "RoomInfo.h"
#include "VideoPokerDefine.h"


GameModel::~GameModel(void)
{
    mChipBetted->release();
}

bool GameModel::init()
{
    // get user info and room info from server data
    mUserInfo = USERINFO();
    mRoomInfo = ROOMINFO();
    
    mUserInfo->setTotalBetChips(0);
    mUserInfo->setTotalWonChips(0);
    
    mIsGotLevelUp = false;
    mLastLevel = mUserInfo->getLevel();
    
    // init chip better model
    int smallValue = mRoomInfo->getChip1();
    int mediumValue = mRoomInfo->getChip2();
    int bigValue = mRoomInfo->getChip3();
    int maxStake = mRoomInfo->getMaxStakes();
    
    mChipBetted = ChipBetted::create(smallValue, mediumValue, bigValue, maxStake);
    mChipBetted->retain();
    
    // init paytable
    mPaytable = Paytable::create(PAYTABLE());
    
    // init deck
    mDeck = DeckView::getSingleton().getDeck();
    
    return true;
}

void GameModel::checkLevelUp()
{
    if (mLastLevel < mUserInfo->getLevel()) {
        mIsGotLevelUp = true;
    }
    else {
        mIsGotLevelUp = false;
    }
    
    mLastLevel = mUserInfo->getLevel();
}

#pragma mark - process bet chip

bool GameModel::updateBetChipWithType(int chipType)
{
    if (mUserInfo->getTotalBetChips() < mRoomInfo->getMaxStakes() &&
        mUserInfo->getTotalChips() > 0) {
        mChipBetted->betChipWithType(chipType, mUserInfo->getTotalChips());
        mUserInfo->setTotalBetChips(mChipBetted->getCurrentTotalBet());
        mUserInfo->setTotalChips(mUserInfo->getTotalChips() - mChipBetted->getCurrentBetChipValue());
        return true;
    }
    
    return false;
}

void GameModel::updateCancelBetChip()
{
    // update chip betted
    mChipBetted->calculateNumberChipsFromLastBettedChip();
    mChipBetted->setCurrentTotalBet(0);
    
    // update user info
    mUserInfo->setTotalBetChips(0);
    mUserInfo->setTotalChips(mUserInfo->getTotalChips() + mChipBetted->getLastTotalBet());
}

bool GameModel::updateMaxBet()
{
    if (mUserInfo->getTotalBetChips() < mRoomInfo->getMaxStakes()) {
        // update total chips
        long long deltaChips = mRoomInfo->getMaxStakes() - mUserInfo->getTotalBetChips();
        // not enought max bet
        if (deltaChips > mUserInfo->getTotalChips()) {
            deltaChips = mUserInfo->getTotalChips();
            mUserInfo->setTotalChips(0);
            mUserInfo->setTotalBetChips(mUserInfo->getTotalBetChips() + deltaChips);
        }
        // enough max bet
        else {
            mUserInfo->setTotalChips(mUserInfo->getTotalChips() - deltaChips);
            mUserInfo->setTotalBetChips(mRoomInfo->getMaxStakes());
        }
        
        mChipBetted->calculateNumberChipsForMaxBet(deltaChips, mUserInfo->getTotalBetChips());

        return true;
    }
    
    return false;
}

bool GameModel::updateCollectWonChips()
{
    if (mUserInfo->getTotalWonChips() > 0) {
        // calculate number chips
        mChipBetted->calculateNumberChipsForWonChip(mUserInfo->getTotalWonChips());
        // update total chips
        mUserInfo->setTotalChips(mUserInfo->getTotalChips() + mUserInfo->getTotalWonChips());
        mUserInfo->setTotalWonChips(0);
        return true;
    }
    else {
        return false;
    }
}

bool GameModel::updateRepeatLastBet()
{
    if (mChipBetted->getLastTotalBet() > 0 &&
        mChipBetted->getLastTotalBet() <= mUserInfo->getTotalChips()) {
        mChipBetted->setCurrentTotalBet(mChipBetted->getLastTotalBet());
        mChipBetted->calculateNumberChipsFromLastBettedChip();
        
        // update to user info
        mUserInfo->setTotalBetChips(mChipBetted->getLastTotalBet());
        mUserInfo->setTotalChips(mUserInfo->getTotalChips() - mUserInfo->getTotalBetChips());

        return true;
    }
    
    return false;
}

void GameModel::updateMainGameFinish()
{
    mUserInfo->setTotalBetChips(0);
    mDeck->updateMainGameFinish();
    mChipBetted->updateMainGameFinish();
}

#pragma mark - process server callback data

void GameModel::updateDealCards(int* dealCards, int hintBit)
{
    mDeck->gotDealCardsFromServer(dealCards, hintBit);
}

void GameModel::updateDealCardSelected(int cardPosition)
{
    mDeck->updateHeldBit(cardPosition);
}

void GameModel::updateDrawCards(int* drawCards, int wonBit, int wonHand, long long wonValue, bool isGotJackpot)
{
    // update to deck
    mDeck->gotDrawCardsFromServer(drawCards, wonBit);
    
    // update to paytable
    mPaytable->updateWonHandType(wonHand);
    
    // update to user info
    mUserInfo->setTotalWonChips(wonValue);
    mUserInfo->setIsGotJackpot(isGotJackpot);
}

void GameModel::updateDonCardSelected(int cardPosition)
{
    mDeck->setHeldBit(0);
    mDeck->updateHeldBit(cardPosition);
}

void GameModel::updateDonDealerCard(int dealerCard)
{
    mDeck->gotDonDealerCardFromServer(dealerCard);
}

void GameModel::updateDonCards(int* donCards, long long wonValue)
{
    mDeck->gotDonCardsFromServer(donCards);
    
    // update don result
    if (mUserInfo->getTotalWonChips() == wonValue) {
        mDonResult = DON_RESULT_PUSH;
    }
    else if (wonValue == 0) {
        mDonResult = DON_RESULT_LOSE;
    }
    else {
        mDonResult = DON_RESULT_WON;
    }
    
    mUserInfo->setTotalWonChips(wonValue);
}

