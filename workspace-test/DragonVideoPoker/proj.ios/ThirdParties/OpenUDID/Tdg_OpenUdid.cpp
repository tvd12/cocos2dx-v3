//
//  Tdg_OpenUdid.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 1/4/14.
//
//

#include "Tdg_OpenUdid.h"

#import "OpenUDID.h"

Tdg_OpenUdid::Tdg_OpenUdid()
{
    
}

const char * Tdg_OpenUdid::getOpenUdid()
{
    NSString *uuid = [OpenUDID value];
    return [uuid UTF8String];
}

