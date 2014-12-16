//
//  NotificationObject.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/26/14.
//
//

#include "NotificationObject.h"

bool NotificationObject::init()
{
    
    return true;
}

NotificationObject::~NotificationObject()
{
    if (mTitle) {
        delete mTitle;
    }
    if (mMessage) {
        delete mMessage;
    }
}