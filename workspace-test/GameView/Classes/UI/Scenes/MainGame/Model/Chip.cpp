//
//  Chip.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#include "Chip.h"

Chip::Chip(int type, int value)
{
    mType = type;
    mValue = value;
}

Chip * Chip::create(int type, int value)
{
    Chip *pRet = new Chip(type, value);
    return pRet;
}
