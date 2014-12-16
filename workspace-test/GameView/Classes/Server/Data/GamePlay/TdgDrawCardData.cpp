//
//  TdgDrawCardData.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/18/14.
//
//

#include "TdgDrawCardData.h"


bool TdgDrawCardData::init()
{
    mDrawCards = new vector<int>(5);
    mWonHandType = 0;
    mWonValue = 0;
    mWonBit = 0;
    mIsGotJackpot = false;
    
    return true;
}

void TdgDrawCardData::updateData(SFSObject* data)
{
    
}
