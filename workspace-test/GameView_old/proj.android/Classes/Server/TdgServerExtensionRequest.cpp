//
//  TdgServerExtensionRequest.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#include "TdgServerExtensionRequest.h"

TdgServerExtensionRequest::TdgServerExtensionRequest(string extensionName,
                                                     CCObject* target,
                                                     ExtensionCallback selector)
{
    mExtensionName = new string(extensionName);
    mTarget = target;
    mSelector = selector;
}

TdgServerExtensionRequest::TdgServerExtensionRequest(string extensionName,
                                                     CCObject* target,
                                                     ExtensionDataCallback selector)
{
    mExtensionName = new string(extensionName);
    mTarget = target;
    mSelectorData = selector;
}

void TdgServerExtensionRequest::invoke(void *extensionInfo)
{
    (mTarget->*mSelector)(extensionInfo);
}

void TdgServerExtensionRequest::invokeWithData(void *extensionInfo, void *data)
{
    (mTarget->*mSelectorData)(extensionInfo, data);
}
