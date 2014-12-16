//
//  TdgDonCardData.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/12/14.
//
//

#include "TdgDonCardData.h"

bool TdgDonCardData::init()
{
    mDonCards = new vector<int>(5);
    mHoldPosition = 0;
    mWonChips = 0;
    
    return true;
}

void TdgDonCardData::updateData(SFSObject* data)
{
    
}
