//
//  Defines.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 6/4/14.
//
//

#ifndef __DragonVideoPoker__Defines__
#define __DragonVideoPoker__Defines__

#include <string>

#include "SingLeton.h"

using namespace std;

class Id {
public:
    Id();
    void defineCommon();
    //void defineIpad();

public:
    string defautl;
    string popup_common_exit_normal;
    string popup_common_exit_active;
    string pop_common_close_normal;
    string pop_common_close_active;
    string pop_common_bg;
    
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

	
	// LeaderboardPopupView image ids declare
	// by apple Mon Jul 28 10:51:18 GMT+07:00 2014
	string common_background;
	string leaderboard_popup_bg;
	string leaderboard_popup_bg_number;
	string leaderboard_popup_frame_avatar;
    string leaderboard_popup_frame_avatar_ipad;
	string leaderboard_popup_leaderboard_banner;
	string leaderboard_popup_number_1;
	string leaderboard_popup_number_2;
	string leaderboard_popup_number_3;
	
	// CrazyUpgradePopupView image ids declaring
	// by apple Fri Aug 15 17:07:30 GMT+07:00 2014
	string crazy_upgrade_popup_background_cz_container;
	string crazy_upgrade_popup_cz_reward_icon;
	string crazy_upgrade_popup_cz_vip_level_ribbon;
	string crazy_on_ribbon;
    
    
    // CrazyShoppingPopupView image ids declaring
	// by apple Fri Sep 19 18:03:07 GMT+07:00 2014
	string crazy_shopping_popup_czs_header;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_bg_blue_active;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_chip_icon;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_main_icon_1;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_buy_child_czs_buy_active;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_buy_child_czs_buy_normal;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_bg_blue_normal;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_chip_icon;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_main_icon_1;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_buy_child_czs_buy_active;
	string crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_buy_child_czs_buy_normal;
	string package_1;
	string crazy_shopping_popup_resource_czs_main_icon_2;
	string crazy_shopping_popup_resource_czs_main_icon_3;
	string crazy_shopping_popup_resource_czs_main_icon_4;
	string crazy_shopping_popup_resource_czs_main_icon_5;
	string crazy_shopping_popup_resource_czs_main_icon_6;
	string crazy_shopping_popup_resource_czs_orange_active;
	string crazy_shopping_popup_resource_czs_orange_normal;
    
	// CzaAvatarsPopupView image ids declaring
	// by apple Sat Sep 20 13:07:16 GMT+07:00 2014
	string cza_avatars_popup_background_cza_bg;
	string cza_avatars_popup_cza_come_back_text;
	string cza_avatars_popup_cza_header;
	string cza_avatars_popup_cza_lv_progress_bg_cza_lv_progress_bg;
	string cza_avatars_popup_cza_lv_progress_bg_progressbar_cza_lv_progress_over;
	string cza_avatars_popup_container_cell_cza_current_background_cza_current_background;
	string cza_avatars_popup_container_cell_cza_current_background_cza_facebook_icon;
	string cza_avatars_popup_container_cell_cza_current_background_cza_inframe;
	string cza_avatars_popup_container_cell_cza_current_background_cza_selected;
	string cza_avatars_popup_container_cell_cza_current_background_cza_use_background;
	string cza_avatars_popup_container_cell_cza_current_background_use_use_use_active;
	string cza_avatars_popup_container_cell_cza_current_background_use_use_use_normal;
	string cza_current_background_1;
	string cza_current_background_2;
	string cza_avatars_popup_resource_memory_game_ki_tu;
	string cza_avatars_popup_resource_memory_game_main_game_layer_exit_ex_active;
	string cza_avatars_popup_resource_memory_game_main_game_layer_exit_ex_normal;
	string cza_avatars_popup_resource_memory_game_main_game_layer_replay_rp_active;
	string cza_avatars_popup_resource_memory_game_main_game_layer_replay_rp_normal;
	string cza_avatars_popup_resource_memory_game_main_game_layer_square_default_normal;
	string cza_avatars_popup_resource_memory_game_main_game_layer_square_text_active;
	string cza_avatars_popup_resource_memory_game_main_game_layer_background_mg_bg;
	string cza_avatars_popup_resource_memory_game_main_game_layer_time_bg;
	string cza_avatars_popup_resource_memory_game_man;
	string cza_avatars_popup_resource_memory_game_meo_goi_y;
	string cza_avatars_popup_resource_memory_game_meo;
	string cza_avatars_popup_resource_memory_game_o_trong_goi_y;
	string cza_avatars_popup_resource_memory_game_o_trong;
	string cza_avatars_popup_resource_memory_game_thoat_replay;

	//don't modify or delete this line
};

class Defines
{
public:
	Defines();
    static Id id;
};

#define D Defines

#endif /* defined(__DragonVideoPoker__Defines__) */
