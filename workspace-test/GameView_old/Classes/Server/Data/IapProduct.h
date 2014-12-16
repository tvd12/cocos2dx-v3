//
//  IapProduct.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/28/14.
//
//

#ifndef __DragonVideoPoker__IapProduct__
#define __DragonVideoPoker__IapProduct__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class IapProduct : public CCObject {
public:
    virtual bool init();
    CREATE_FUNC(IapProduct);
    void resetDefaultPriceWithType(long type);
    
    CC_SYNTHESIZE(long , mProductType, ProductType);
    CC_SYNTHESIZE(string*, mPackageName, PackageName);
    CC_SYNTHESIZE(long, mChipsAmount, ChipsAmount);
    CC_SYNTHESIZE(long, mVipPoint, VipPoint);
    CC_SYNTHESIZE(string*, mPrice, Price);
};

#endif /* defined(__DragonVideoPoker__IapProduct__) */
