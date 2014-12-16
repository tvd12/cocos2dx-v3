//
//  NotificationPopupView.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/26/14.
//
//

#ifndef __DragonVideoPoker__NotificationPopupView__
#define __DragonVideoPoker__NotificationPopupView__

#include "cocos2d.h"
#include "PopUpLayer.h"
#include "GameParams.h"

#define NOTIFICATION_POPUP_ORDER        2000

using namespace std;

class NotificationObject;
class NotificationPopupView;

class NotificationPopupDelegate
{
public:
    virtual void button1DidPressed(NotificationPopupView* sender) {}
    virtual void button2DidPressed(NotificationPopupView* sender) {}
};


class NotificationPopupView : public PopUpLayer {
public:
    static NotificationPopupView* create(NotificationObject* object);
    bool init(NotificationObject* object);
    
    CC_SYNTHESIZE(NotificationPopupDelegate*, mDelegate, Delegate);

    virtual void addLabels();
    virtual void addMenuItems();

    virtual void onExit();
    virtual void registerWithTouchDispatcher(void);

private:
    void selectButton1MenuItemCallback(CCObject* pSender);
    void selectButton2MenuItemCallback(CCObject* pSender);

    const char* getButtonFileNameByType(int type);
    
    NotificationObject* mNotificationObject;
};


#endif /* defined(__DragonVideoPoker__NotificationPopupView__) */
