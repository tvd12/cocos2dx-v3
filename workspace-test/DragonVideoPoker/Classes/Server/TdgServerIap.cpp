//
//  TdgServerIap.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/3/14.
//
//

#include "TdgServerIap.h"
#include "IapProduct.h"
#include "TdgServer.h"
#include "NotificationObject.h"
#include "UserInfo.h"

#include <algorithm>
#include <boost/tokenizer.hpp>


TdgServerIap::TdgServerIap()
{
    
}

void TdgServerIap::fetchingInAppPurchaseList(boost::shared_ptr<ISFSArray> iapList)
{
    for (int i = 0; i < iapList->Size(); i++) {
        ISFSObject* iapObject = iapList->GetSFSObject(i).get();
        long* productType = iapObject->GetInt(EX_REQUEST_PARAM_IAP_PRODUCT_TYPE).get();
        string* packageName = iapObject->GetUtfString(EX_REQUEST_PARAM_IAP_PACKAGE_NAME).get();
        long* chipsAmount = iapObject->GetInt(EX_REQUEST_PARAM_IAP_CHIPS_AMOUNT).get();
        long* vipPoint = iapObject->GetInt(EX_REQUEST_PARAM_IAP_VIP_POINT).get();

        if (productType != NULL && packageName != NULL &&
            chipsAmount != NULL && vipPoint != NULL) {
            // update this list
            IapProduct* iapProduct = IAPLIST()->at(i);
            iapProduct->setProductType(*productType);
            iapProduct->setPackageName(new string(*packageName));
            iapProduct->setChipsAmount(*chipsAmount);
            iapProduct->setVipPoint(*vipPoint);
        }
    }
}

void TdgServerIap::processVerifyIapResult(boost::shared_ptr<ISFSObject> iapResultData)
{
    // finish purchasing
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_IAP_FINISHED,
                                                                       NULL);

    // get iap result
    long* status = iapResultData->GetInt(EX_REQUEST_PARAM_RESULT_STATUS).get();
    if (status != NULL) {
        // purchase successed
        if (*status == 0) {
            // update chips, vip
            long long* totalChips = iapResultData->GetLong(EX_REQUEST_PARAM_USER_CHIPS).get();
            long* vipType = iapResultData->GetInt(EX_REQUEST_PARAM_VIP_CARD_TYPE).get();
            long* vipPoint = iapResultData->GetInt(EX_REQUEST_PARAM_USER_VIP_POINT).get();
            
            if (totalChips) {
                USERINFO()->setTotalChips(*totalChips);
                string* message = iapResultData->GetUtfString(EX_REQUEST_PARAM_RESULT_STATUS_CONTENT).get();
                NotificationObject* object = SERVER_IAP().getNotificationMessage(message);
                object->setNotificationType(kNotificationInAppPurchaseSuccessed);
                CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_IAP_SUCCESS,
                                                                                   object);
            }
            if (vipPoint && vipType) {
                if (*vipType > USERINFO()->getVipType()) {
                    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_VIP_UPGRADE,
                                                                                       NULL);
                }
                USERINFO()->setVipPoint(*vipPoint);
                USERINFO()->setVipType(*vipType);
            }
        }
        
        // purchase failed
        else {
            // display message
            string* message = iapResultData->GetUtfString(EX_REQUEST_PARAM_RESULT_STATUS_CONTENT).get();
            NotificationObject* object = SERVER_IAP().getNotificationMessage(message);
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_IAP_FAILED,
                                                                               object);
        }
    }
}

NotificationObject* TdgServerIap::getNotificationMessage(string* message)
{
    boost::char_separator<char> sep("_");
    boost::tokenizer<boost::char_separator<char> > toker(*message, sep);
    vector<string> words(toker.begin(), toker.end());
    
    NotificationObject* object = NotificationObject::create();
    object->setTitle(new string(words[0]));
    object->setMessage(new string(words[1]));
    object->setButton1Type(kButtonOk);
    object->setButton2Type(kButtonNone);
    return object;
}

