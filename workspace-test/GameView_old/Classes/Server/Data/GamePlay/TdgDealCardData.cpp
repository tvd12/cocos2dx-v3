//
//  TdgDealCardData.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/18/14.
//
//

#include "TdgDealCardData.h"

bool TdgDealCardData::init()
{
    mDealCards = new vector<int>(5);
    mHintBits = 0;
    return true;
}

void TdgDealCardData::updateData(SFSObject* data)
{
    
}
