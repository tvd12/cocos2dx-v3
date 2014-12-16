//
//  PaytableCell.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/14/14.
//
//

#include "PaytableCell.h"

PaytableCell* PaytableCell::create(const int pHandType,
                                   const string pHandName,
                                   const int pHandMultiple) {
    PaytableCell *pRet = new PaytableCell();
    pRet->init(pHandType,
               pHandName,
               pHandMultiple);
    pRet->autorelease();
    
    return pRet;
}

bool PaytableCell::init(const int pHandType,
                        const string pHandName,
                        const int pHandMultiple) {
    mHandType = pHandType;
    mHandName = pHandName;
    mHandMultiple = pHandMultiple;
    
    return true;
}