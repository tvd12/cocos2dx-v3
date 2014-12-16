//
//  Defines.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 6/4/14.
//
//#ifndef __DragonVideoPoker__Defines__
#define __DragonVideoPoker__Defines__#include <string>#include "SingLeton.h"using namespace std;class Id {
public:
    Id();
    void defineCommon();
    //void defineIpad();public:
    string jackpot_popup_background_container;
    string jackpot_popup_chips;
    string jackpot_popup_jackpot_text;
    string jackpot_popup_reward_icon;
    string jackpot_popup_shine_circle;
    string jackpot_popup_star_shine;
    string jackpot_popup_ok_ok_active;
    string jackpot_popup_ok_ok_normal;
    string jackpot_popup_share_share_active;
    string jackpot_popup_share_share_normal;
    string jackpot_popup_small_star;
    string jackpot_popup_big_star;	
	/**
	* VipUpgradePopupView image ids declare
	* by apple
	*/
	string vip_upgrade_popup_background_container;
	string vip_upgrade_popup_member_cards[5];
	string vip_upgrade_popup_reward_icon;
	string vip_upgrade_popup_shine;
	string vip_upgrade_popup_star1;
	string vip_upgrade_popup_star2;
	string vip_upgrade_popup_vip_level_ribbon;
	string vip_upgrade_popup_ok_ok_active;
	string vip_upgrade_popup_ok_ok_normal;
	string vip_upgrade_popup_share_share_active;
	string vip_upgrade_popup_share_share_normal;	
	/**
	* LevelupPopupView image ids declare
	* by apple
	*/
	string levelup_popup_background_level;
	string levelup_popup_circle_container_1;
	string levelup_popup_circle_container_2;
	string levelup_popup_ribbon;
	string levelup_popup_shine_circle;
	string levelup_popup_star1;
	string levelup_popup_star2;
	string levelup_popup_star3;
	string levelup_popup_star_shine;
	string levelup_popup_ok_ok_active;
	string levelup_popup_ok_ok_normal;
	string levelup_popup_share_share_active;
	string levelup_popup_share_share_normal;
	
	
	// LeaderboardPopupView image ids declaring
	// by apple Wed Aug 13 16:16:23 GMT+07:00 2014
	string common_background;
	string leaderboard_popup_bg_fuck;
	string leaderboard_popup_bg_number;
	string leaderboard_popup_leaderboard_banner;
	string leaderboard_popup_number_1;
	string leaderboard_popup_number_2;
	string leaderboard_popup_number_3;

	//don't modify or delete this line
};class Defines
{
public:
	Defines();
    static Id id;
};#define D Defines#endif /* defined(__DragonVideoPoker__Defines__) */
