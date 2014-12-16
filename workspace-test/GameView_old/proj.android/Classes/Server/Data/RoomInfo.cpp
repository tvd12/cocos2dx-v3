//
//  RoomInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/25/14.
//
//

#include "RoomInfo.h"

#include "TdgServerDefine.h"

#include <algorithm>
#include <boost/tokenizer.hpp>

RoomInfo::RoomInfo()
{    
    mIndex                  = 0;
    mLevelRequired          = 0;
    mMinStakes              = 0;
    mMaxStakes              = 0;
    mJackpotPercent         = 0;
    mJackpotHand            = 0;
    mJackpotReset           = 0;
    mChip1                  = 0;
    mChip2                  = 0;
    mChip3                  = 0;
    mNumberOnlinePlayers    = 0;
    mJackpot                = 0;
}

void RoomInfo::updateChipTypeValueFromString(string* chipType)
{
    boost::char_separator<char> sep("_");
    boost::tokenizer<boost::char_separator<char> > toker(string(*chipType), sep);
    vector<string> chipTypes(toker.begin(), toker.end());

    mChip1 = atol(chipTypes[0].c_str());
    mChip2 = atol(chipTypes[1].c_str());
    mChip3 = atol(chipTypes[2].c_str());
}
