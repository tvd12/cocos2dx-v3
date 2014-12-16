//
//  TdgServerExtensionRequest.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#ifndef __DragonVideoPoker__TdgServerExtensionRequest__
#define __DragonVideoPoker__TdgServerExtensionRequest__

#include "SmartFox.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

// define extension callback
typedef void (CCObject::*ExtensionCallback)(void*);
#define extension_selector(_SELECTOR) (ExtensionCallback)(&_SELECTOR)

typedef void (CCObject::*ExtensionDataCallback)(void*, void*);
#define extension_selector_D(_SELECTOR) (ExtensionDataCallback)(&_SELECTOR)

class TdgServerExtensionRequest : public CCObject
{
public:
    TdgServerExtensionRequest(string extensionName,
                              CCObject* target,
                              ExtensionCallback selector);
    void invoke(void *extensionInfo);
    
    TdgServerExtensionRequest(string extensionName,
                              CCObject* target,
                              ExtensionDataCallback selector);
    void invokeWithData(void *extensionInfo, void *data);
    
    string *getExtensionName() {return mExtensionName;};
    
private:
    string *mExtensionName;
    CCObject* mTarget;
    ExtensionCallback mSelector;
    ExtensionDataCallback mSelectorData;
};

#endif /* defined(__DragonVideoPoker__TdgServerExtensionRequest__) */
