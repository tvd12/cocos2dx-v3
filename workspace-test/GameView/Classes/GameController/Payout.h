//
//  Payout.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/21/14.
//
//

#ifndef __DragonVideoPoker__Payout__
#define __DragonVideoPoker__Payout__

#include "cocos2d.h"
#include <map>

using namespace std;

class Payout {
public:
	Payout();
    static Payout * getInstance();
    
    int getMultiplier(int gameType, int handId);
    
};

#endif /* defined(__DragonVideoPoker__Payout__) */
