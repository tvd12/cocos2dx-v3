//
//  IapProduct.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/28/14.
//
//

#include "IapProduct.h"


bool IapProduct::init()
{
    mProductType = 0;
    mPackageName = NULL;
    mChipsAmount = 0;
    mVipPoint = 0;
    mPrice = NULL;
    
    return true;
}

void IapProduct::resetDefaultPriceWithType(long type)
{
    mProductType = type;
    switch (mProductType) {
        case 0:
            mPrice = new string("$1.99");
            break;
            
        case 1:
            mPrice = new string("$3.99");
            break;
            
        case 2:
            mPrice = new string("$9.99");
            break;
            
        case 3:
            mPrice = new string("$24.99");
            break;
            
        case 4:
            mPrice = new string("$49.99");
            break;
            
        case 5:
            mPrice = new string("$99.99");
            break;
            
        default:
            break;
    }
}
