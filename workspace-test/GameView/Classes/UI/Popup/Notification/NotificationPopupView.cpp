//
//  NotificationPopupView.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/26/14.
//
//

#include "NotificationPopupView.h"
#include "VisibleRect.h"
#include "GameParams.h"
#include "NotificationObject.h"
#include "SoundManager.h"


NotificationPopupView* NotificationPopupView::create(NotificationObject* object)
{
    NotificationPopupView* pRet = new NotificationPopupView();
    pRet->autorelease();
    pRet->init(object);
    return pRet;
}

bool NotificationPopupView::init(NotificationObject* object)
{
    mNotificationObject = object;
//    mNotificationObject->retain();
    
    PopUpLayer::init("common_pop_up_table.png");
    setBackgroundPosition(VisibleRect::center());
    
    // store type of this notification
    this->setTag(mNotificationObject->getNotificationType());
    mPopupMenu->setTouchPriority(kCCMenuHandlerPriority - 2000);

    // play sound if need
    if (object->getNotificationType() == kNotificationInAppPurchaseSuccessed) {
        SOUND().playSound(SOUND_GOT_PURCHASED);
    }
    
    return true;
}

void NotificationPopupView::onExit()
{
    mNotificationObject->release();
    PopUpLayer::onExit();
}

void NotificationPopupView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()
    ->getTouchDispatcher()
    ->addTargetedDelegate(this,
                          kCCMenuHandlerPriority - 2000,
                          true);
}

void NotificationPopupView::addLabels()
{
    // add title
    CCLabelTTF* title = CCLabelTTF::create(mNotificationObject->getTitle()->c_str(),
                                           DEFAULT_FONT_NAME,
                                           GPARAMS().CMM_FONT_SIZE_2);
    title->setPosition(GPARAMS().NTF_TITLE_TEXT_POSITION);
    mBackgroundSprite->addChild(title);
    
    // add message
    CCLabelTTF *message = CCLabelTTF::create(mNotificationObject->getMessage()->c_str(),
                                             DEFAULT_FONT_NAME,
                                             GPARAMS().CMM_FONT_SIZE_2,
                                             GPARAMS().NTF_MESSAGE_SIZE,
                                             kCCTextAlignmentCenter,
                                             kCCVerticalTextAlignmentCenter);
    message->setPosition(GPARAMS().NTF_MESSAGE_TEXT_POSITION);
    mBackgroundSprite->addChild(message);
}

void NotificationPopupView::addMenuItems()
{
    PopUpLayer::addMenuItems();

    // add first button
    const char* firstButtonName = getButtonFileNameByType(mNotificationObject->getButton1Type());
    CCMenuItem* firstMenuItem = CCMenuItemImage::create(CCString::createWithFormat("%s_normal.png", firstButtonName)->getCString(),
                                                        CCString::createWithFormat("%s_active.png", firstButtonName)->getCString(),
                                                        this,
                                                        menu_selector(NotificationPopupView::selectButton1MenuItemCallback));
    mPopupMenu->addChild(firstMenuItem);
    if (mNotificationObject->getButton2Type() == kButtonNone) {
        firstMenuItem->setPosition(GPARAMS().NTF_BUTTON_CENTER_POSITION);
    }
    else {
        firstMenuItem->setPosition(GPARAMS().NTF_BUTTON_LEFT_POSITION);

        const char* secondButtonName = getButtonFileNameByType(mNotificationObject->getButton2Type());
        CCMenuItem* secondMenuItem = CCMenuItemImage::create(CCString::createWithFormat("%s_normal.png", secondButtonName)->getCString(),
                                                             CCString::createWithFormat("%s_active.png", secondButtonName)->getCString(),
                                                             this,
                                                             menu_selector(NotificationPopupView::selectButton2MenuItemCallback));
        mPopupMenu->addChild(secondMenuItem);
        secondMenuItem->setPosition(GPARAMS().NTF_BUTTON_RIGHT_POSITION);
    }
}

#pragma mark - menu items callback

void NotificationPopupView::selectButton1MenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    if (mDelegate != NULL) {
        mDelegate->button1DidPressed(this);
    }
    hide();
}

void NotificationPopupView::selectButton2MenuItemCallback(CCObject* pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    if (mDelegate != NULL) {
        mDelegate->button2DidPressed(this);
    }
    hide();
}

const char* NotificationPopupView::getButtonFileNameByType(int type)
{
    const char* fileName;
    
    switch (type) {
        case kButtonNone:
            fileName = "";
            break;
            
        case kButtonOk:
            fileName = "common_ok";
            break;
            
        case kButtonCancel:
            fileName = "common_cancel";
            break;
            
        case kButtonShare:
            fileName = "common_share";
            break;
            
        default:
            fileName = "";
            break;
    }
    
    return fileName;
}
