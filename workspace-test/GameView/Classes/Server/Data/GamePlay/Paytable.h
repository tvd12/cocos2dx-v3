//
//  Paytable.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/12/14.
//
//

#ifndef __DragonVideoPoker__Paytable__
#define __DragonVideoPoker__Paytable__

#include <vector>
#include <string>

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class PaytableCell;
class Paytable : public CCObject
{
public:
	Paytable(vector<PaytableCell*> * pPaytableCells);
    static Paytable *create(vector<PaytableCell*> * pPaytableCells);
    bool updateWonHandType(const int pWonHandType);
    
    CC_SYNTHESIZE_READONLY(PaytableCell*, mWonPaytableCell, WonPaytableCell);
    CC_SYNTHESIZE_READONLY(vector<PaytableCell*> *, mPaytableCells, PaytableCells);
    
    ~Paytable();
};

#endif /* defined(__DragonVideoPoker__Paytable__) */
