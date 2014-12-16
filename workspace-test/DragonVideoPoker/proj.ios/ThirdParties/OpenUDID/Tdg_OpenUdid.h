//
//  Tdg_OpenUdid.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 1/4/14.
//
//

#ifndef __Dragon_Poker__Tdg_OpenUdid__
#define __Dragon_Poker__Tdg_OpenUdid__

#include "SingLeton.h"

class Tdg_OpenUdid : public SingLeton<Tdg_OpenUdid>
{
public:
	Tdg_OpenUdid();
    
    const char * getOpenUdid();    
};

#define OPEN_UDID() Tdg_OpenUdid::getSingleton().getOpenUdid()

#endif /* defined(__Dragon_Poker__Tdg_OpenUdid__) */
