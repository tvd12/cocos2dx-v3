//
//  PaytableCell.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/14/14.
//
//

#ifndef __DragonVideoPoker__PaytableCell__
#define __DragonVideoPoker__PaytableCell__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;


class PaytableCell : public CCObject {
public:
    static PaytableCell* create(const int pHandType,
                                const string pHandName,
                                const int pHandMultiple);
    bool init(const int pHandType,
              const string pHandName,
              const int pHandMultiple);
    
    CC_SYNTHESIZE_READONLY(int, mHandType, HandType);
    CC_SYNTHESIZE_READONLY(string, mHandName, HandName);
    CC_SYNTHESIZE_READONLY(int, mHandMultiple, HandMultiple);
};

#endif /* defined(__DragonVideoPoker__PaytableCell__) */
