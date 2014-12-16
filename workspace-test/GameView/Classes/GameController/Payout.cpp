//
//  Payout.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/21/14.
//
//

#include "Payout.h"

static Payout *sInstance;
Payout * Payout::getInstance()
{
    if (!sInstance) {
        sInstance = new Payout();
    }
    
    return sInstance;
}

Payout::Payout()
{
    
}

int Payout::getMultiplier(int gameType, int handId)
{
    return 2;
}
