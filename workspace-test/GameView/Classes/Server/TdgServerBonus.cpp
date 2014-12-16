//
//  TdgServerBonus.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#include "TdgServerBonus.h"
#include "TdgServer.h"

#include "UserInfo.h"
#include "HourlyBonusInfo.h"
#include "DailyBonusInfo.h"


TdgServerBonus::TdgServerBonus()
{
    
}

// process hourly & daily bonus

void TdgServerBonus::processHourlyBonusData(boost::shared_ptr<ISFSObject> data)
{
    long long* totalChips = data->GetLong(EX_REQUEST_PARAM_USER_CHIPS).get();
    if (totalChips) {
        // update claimed data
        long long claimed = *totalChips - USERINFO()->getTotalChips();
        HOURLYBONUS()->setLastClaimed((long)claimed);
        CCLOG("Got claimed: %lld", claimed);
        
        USERINFO()->setTotalChips(*totalChips);
        
        // reset current bonus
        HOURLYBONUS()->setLastBonus(0);
        HOURLYBONUS()->updateLastBonusTime();
        HOURLYBONUS()->updateCurrentBonus();
        
        // report to UI
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_CLAIM_HOURLY_BONUS,
                                                                           NULL);
    }
}

void TdgServerBonus::processDailyBonusData(boost::shared_ptr<ISFSObject> data)
{
    long long* totalChips = data->GetLong(EX_REQUEST_PARAM_USER_CHIPS).get();
    if (totalChips) {
        // update claimed data
        USERINFO()->setTotalChips(*totalChips);
        
        // reset current bonus
        DAILYBONUS()->setDaysPlay(0);
        
        // report to UI
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_CLAIM_DAILY_BONUS,
                                                                           NULL);
    }
}

void TdgServerBonus::fetchingHourlyBonusData(boost::shared_ptr<ISFSObject> data)
{
    long* bonusMax = data->GetInt(EX_REQUEST_PARAM_HOURLY_BONUS_MAX).get();
    float* chipsPerSecond = data->GetFloat(EX_REQUEST_PARAM_HOURLY_CHIPS_PER_SECOND).get();

    if (bonusMax) {
        HOURLYBONUS()->setBonusMax(*bonusMax);
    }
    if (chipsPerSecond) {
        HOURLYBONUS()->setChipsPerSecond(*chipsPerSecond);
    }
    
    // get current bonus
    HOURLYBONUS()->updateCurrentBonus();
}

void TdgServerBonus::fetchingDailyBonusData(boost::shared_ptr<ISFSObject> data)
{
    long* consecutiveDays = data->GetInt(EX_REQUEST_PARAM_DAILY_CONSECUTIVE_DAYS).get();
    long* consecutiveDaysBonus = data->GetInt(EX_REQUEST_PARAM_DAILY_CONSECUTIVE_DAYS_BONUS).get();
    long* eachFriendReward = data->GetInt(EX_REQUEST_PARAM_DAILY_EACH_FRIEND_REWARD).get();
    long* friendsBonus = data->GetInt(EX_REQUEST_PARAM_DAILY_FRIENDS_BONUS).get();
    long* eachLevelReward = data->GetInt(EX_REQUEST_PARAM_DAILY_EACH_LEVEL_REWARD).get();
    long* levelReward = data->GetInt(EX_REQUEST_PARAM_DAILY_LEVEL_REWARD_BONUS).get();
    long* vipCard = data->GetInt(EX_REQUEST_PARAM_DAILY_VIP_CARD).get();
    long* vipBonus = data->GetInt(EX_REQUEST_PARAM_DAILY_VIP_REWARD_BONUS).get();

    if (consecutiveDays && consecutiveDaysBonus &&
        eachFriendReward && friendsBonus &&
        eachLevelReward && levelReward &&
        vipCard && vipBonus) {
        DAILYBONUS()->setDaysPlay(*consecutiveDays);
        DAILYBONUS()->setDaysBonus(*consecutiveDaysBonus);

        DAILYBONUS()->setBonusPerFriend(*eachFriendReward);
        DAILYBONUS()->setFriendsBonus(*friendsBonus);

        DAILYBONUS()->setBonusPerLevel(*eachLevelReward);
        DAILYBONUS()->setLevelBonus(*levelReward);

        DAILYBONUS()->setVipStatus(*vipCard);
        DAILYBONUS()->setVipBonus(*vipBonus);
        
        // update total bonus
        DAILYBONUS()->setTotalBonus(*consecutiveDaysBonus + *friendsBonus +
                                    *levelReward + *vipBonus);
    }
}
