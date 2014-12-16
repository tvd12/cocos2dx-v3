//
//  NotificationObject.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/26/14.
//
//

#ifndef __DragonVideoPoker__NotificationObject__
#define __DragonVideoPoker__NotificationObject__

typedef enum NOTIFICATION_BUTTON_TYPE
{
    kButtonNone             = 0,
    kButtonOk               = 1,
    kButtonCancel           = 2,
    kButtonShare            = 3,
} Notification_Button_Type;

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class NotificationObject: public CCObject
{
public:
    virtual bool init();
    CREATE_FUNC(NotificationObject);
    ~NotificationObject();
    
    CC_SYNTHESIZE(string*, mTitle, Title);
    CC_SYNTHESIZE(string*, mMessage, Message);
    CC_SYNTHESIZE(long, mButton1Type, Button1Type);
    CC_SYNTHESIZE(long, mButton2Type, Button2Type);
    CC_SYNTHESIZE(long, mNotificationType, NotificationType);
};

#endif /* defined(__DragonVideoPoker__NotificationObject__) */
