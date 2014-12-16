//
//  TdgServerVip.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/22/14.
//
//

#include "TdgServerVip.h"
#include "TdgServer.h"
#include "VipInfo.h"


TdgServerVip::TdgServerVip()
{
    
}

void TdgServerVip::fetchingVipInfo(boost::shared_ptr<ISFSArray> vipInfoList)
{
    CCLOG("fetchingVipInfo with size = %ld!!!", vipInfoList->Size());

    long totalVipPoint = 0;
    for (int i = 0; i < vipInfoList->Size(); i++) {
        ISFSObject* vipInfoObject = vipInfoList->GetSFSObject(i).get();
        long* vipType = vipInfoObject->GetInt(EX_REQUEST_PARAM_VIP_CARD_TYPE).get();
        long* vipPointMax = vipInfoObject->GetInt(EX_REQUEST_PARAM_VIP_POINT_MAX).get();
        long* vipMultiply = vipInfoObject->GetInt(EX_REQUEST_PARAM_VIP_MULTIPLY).get();
        long* vipUpgradeBonus = vipInfoObject->GetInt(EX_REQUEST_PARAM_VIP_UPGRADE_BONUS).get();
        
        if (vipType != NULL && vipPointMax != NULL && vipMultiply != NULL &&
            vipUpgradeBonus != NULL) {
            CCLOG("vipType = %ld", *vipType);
            CCLOG("vipPointMax = %ld", *vipPointMax);
            CCLOG("vipMultiply = %ld", *vipMultiply);
            CCLOG("vipUpgradeBonus = %ld", *vipUpgradeBonus);
            totalVipPoint += *vipPointMax;
            
            VipInfo* vipInfo = VipInfo::create();
            vipInfo->updateInfo(*vipType, *vipMultiply, *vipPointMax, *vipUpgradeBonus);
            vipInfo->setTotalPointToLevel(totalVipPoint);
            VIPINFOLIST()->push_back(vipInfo);
            if (i > 0) {
                VipInfo* vipInfo2 = VIPINFOLIST()->at(i - 1);
                vipInfo2->setPointToLevelUp(*vipPointMax);
            }
        }
    }
    
    for (int i = 0; i < 6; i++) {
        VipInfo* vipInfo = VIPINFOLIST()->at(i);
        CCLOG("----- %s Info -----", vipInfo->getVipCardText());
        CCLOG("Progress Text = %s", vipInfo->getProgressText());
        CCLOG("Text 1 = %s", vipInfo->getDescriptionText1());
        CCLOG("Text 2 = %s", vipInfo->getDescriptionText2());
        CCLOG("Point required = %s", vipInfo->getVipPointRequireText());
    }
}
