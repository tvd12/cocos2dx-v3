//
//  Defines.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 6/4/14.
//
//

#include "Defines.h"

Defines::Defines()
{
    //id.defineCommon();
}

Id Defines::id;

Id::Id() {
    defineCommon();
}

void Id::defineCommon() {
    defautl = "";
    pop_common_close_active = "pop_common_close_active.png";
    pop_common_close_normal = "pop_common_close_normal.png";
    pop_common_bg                               = "pop_common_bg.png";
    popup_common_exit_active                    = "pop_common_close_active.png";
    popup_common_exit_normal                    = "pop_common_close_normal.png";
    
    jackpot_popup_background_container          = "jackpot_popup/background/container.png";
	jackpot_popup_chips                         = "jackpot_popup/sprites/chips.png";
	jackpot_popup_jackpot_text                  = "jackpot_popup/sprites/jackpot_text.png";
	jackpot_popup_reward_icon                   = "jackpot_popup/sprites/reward_icon.png";
	jackpot_popup_shine_circle                  = "jackpot_popup/sprites/shine_circle.png";
	jackpot_popup_star_shine                    = "jackpot_popup/sprites/star_shine.png";
    jackpot_popup_ok_ok_active                  = "common_ok_active.png";
    jackpot_popup_ok_ok_normal                  = "common_ok_normal.png";
    jackpot_popup_share_share_active            = "common_share_active.png";
    jackpot_popup_share_share_normal            = "common_share_normal.png";
    jackpot_popup_small_star                    = "common_pop_star_small.png";
    jackpot_popup_big_star                      = "common_pop_star_big.png";

	
	/**
	* VipUpgradePopupView image ids init
	* by apple
	*/
	vip_upgrade_popup_background_container		= "vip_upgrade_popup/background/container.png";
	vip_upgrade_popup_member_cards[0]           = "common_vip_card_sprite_0_big.png";
    vip_upgrade_popup_member_cards[1]           = "common_vip_card_sprite_1_big.png";
    vip_upgrade_popup_member_cards[2]           = "common_vip_card_sprite_2_big.png";
    vip_upgrade_popup_member_cards[3]           = "common_vip_card_sprite_3_big.png";
    vip_upgrade_popup_member_cards[4]           = "common_vip_card_sprite_4_big.png";
    vip_upgrade_popup_member_cards[5]           = "common_vip_card_sprite_5_big.png";
	vip_upgrade_popup_reward_icon               = "vip_upgrade_popup/sprites/reward_icon.png";
	vip_upgrade_popup_shine                     = "jackpot_popup/sprites/shine_circle.png";
	vip_upgrade_popup_star1                     = "common_pop_star_big.png";
	vip_upgrade_popup_star2                     = "common_pop_star_big.png";
	vip_upgrade_popup_vip_level_ribbon          = "vip_upgrade_popup/sprites/vip_level_ribbon.png";
	vip_upgrade_popup_ok_ok_active              = "common_ok_active.png";
	vip_upgrade_popup_ok_ok_normal              = "common_ok_normal.png";
	vip_upgrade_popup_share_share_active		= "common_share_active.png";
	vip_upgrade_popup_share_share_normal		= "common_share_normal.png";

	
	/**
	* LevelupPopupView image ids init
	* by apple
	*/
	levelup_popup_background_level		= "levelup_popup/background/level.png";
	levelup_popup_circle_container_1		= "levelup_popup/sprites/circle_container_1.png";
	levelup_popup_circle_container_2		= "levelup_popup/sprites/circle_container_2.png";
	levelup_popup_ribbon		= "levelup_popup/sprites/ribbon.png";
	levelup_popup_shine_circle		= "levelup_popup/sprites/shine_circle.png";
	levelup_popup_star1		= "levelup_popup/sprites/star1.png";
	levelup_popup_star2		= "levelup_popup/sprites/star2.png";
	levelup_popup_star3		= "levelup_popup/sprites/star3.png";
	levelup_popup_star_shine		= "levelup_popup/sprites/star_shine.png";
	levelup_popup_ok_ok_active		= "common_ok_active.png";
	levelup_popup_ok_ok_normal		= "common_ok_normal.png";
	levelup_popup_share_share_active		= "common_share_active.png";
	levelup_popup_share_share_normal		= "common_share_normal.png";

	
	// LeaderboardPopupView image ids init
	// by apple Mon Jul 28 10:51:18 GMT+07:00 2014
	common_background		= "pop_common_bg.png";
	leaderboard_popup_bg		= "leaderboard_popup/sprites/bg.png";
	leaderboard_popup_bg_number		= "leaderboard_popup/sprites/bg_number.png";
	leaderboard_popup_frame_avatar		= "avatar_inframe_40.png";
    leaderboard_popup_frame_avatar_ipad      = "avatar_inframe_73.png";
	leaderboard_popup_leaderboard_banner		= "leaderboard_popup/sprites/leaderboard_banner.png";
	leaderboard_popup_number_1		= "leaderboard_popup/sprites/number_1.png";
	leaderboard_popup_number_2		= "leaderboard_popup/sprites/number_2.png";
	leaderboard_popup_number_3		= "leaderboard_popup/sprites/number_3.png";

	// CrazyUpgradePopupView image ids initializing
	// by apple Fri Aug 15 17:07:30 GMT+07:00 2014
	crazy_upgrade_popup_background_cz_container		= "crazy_upgrade_popup/background/cz_container.png";
	crazy_upgrade_popup_cz_reward_icon		= "crazy_upgrade_popup/sprites/cz_reward_icon.png";
	crazy_upgrade_popup_cz_vip_level_ribbon		= "crazy_upgrade_popup/sprites/cz_vip_level_ribbon.png";
	crazy_on_ribbon		= "crazy_upgrade_popup/sprites/cz_reward_icon.png";
    
    
    // CrazyShoppingPopupView image ids initializing
	// by apple Fri Sep 19 18:03:07 GMT+07:00 2014
	crazy_shopping_popup_czs_header			= "crazy_shopping_popup/sprites/czs_header.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_bg_blue_active			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_active/czs_bg_blue_active.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_chip_icon			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_active/sprites/czs_chip_icon.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_czs_main_icon_1			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_active/sprites/czs_main_icon_1.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_buy_child_czs_buy_active			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_active/menus/buy/menuitems/child/sprites/czs_buy_active.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_active_buy_child_czs_buy_normal			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_active/menus/buy/menuitems/child/sprites/czs_buy_normal.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_bg_blue_normal			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_normal/czs_bg_blue_normal.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_chip_icon			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_normal/sprites/czs_chip_icon.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_czs_main_icon_1			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_normal/sprites/czs_main_icon_1.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_buy_child_czs_buy_active			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_normal/menus/buy/menuitems/child/sprites/czs_buy_active.png";
	crazy_shopping_popup_shopping_cell_shopping_bg_package_blue_normal_buy_child_czs_buy_normal			= "crazy_shopping_popup/tables/shopping/cell/menus/shopping_bg/menuitems/package/sprites/blue_normal/menus/buy/menuitems/child/sprites/czs_buy_normal.png";
	crazy_shopping_popup_resource_czs_main_icon_2			= "crazy_shopping_popup/resource/czs_main_icon_2.png";
	crazy_shopping_popup_resource_czs_main_icon_3			= "crazy_shopping_popup/resource/czs_main_icon_3.png";
	crazy_shopping_popup_resource_czs_main_icon_4			= "crazy_shopping_popup/resource/czs_main_icon_4.png";
	crazy_shopping_popup_resource_czs_main_icon_5			= "crazy_shopping_popup/resource/czs_main_icon_5.png";
	crazy_shopping_popup_resource_czs_main_icon_6			= "crazy_shopping_popup/resource/czs_main_icon_6.png";
	crazy_shopping_popup_resource_czs_orange_active			= "crazy_shopping_popup/resource/czs_orange_active.png";
	crazy_shopping_popup_resource_czs_orange_normal			= "crazy_shopping_popup/resource/czs_orange_normal.png";
	
	// CzaAvatarsPopupView image ids initializing
	// by apple Sat Sep 20 13:07:16 GMT+07:00 2014
	cza_avatars_popup_background_cza_bg			= "cza_avatars_popup/background/cza_bg.png";
	cza_avatars_popup_cza_come_back_text			= "cza_avatars_popup/sprites/cza_come_back_text.png";
	cza_avatars_popup_cza_header			= "cza_avatars_popup/sprites/cza_header.png";
	cza_avatars_popup_cza_lv_progress_bg_cza_lv_progress_bg			= "cza_avatars_popup/sprites/cza_lv_progress_bg/cza_lv_progress_bg.png";
	cza_avatars_popup_cza_lv_progress_bg_progressbar_cza_lv_progress_over			= "cza_avatars_popup/sprites/cza_lv_progress_bg/progressbar/cza_lv_progress_over.png";
	cza_avatars_popup_container_cell_cza_current_background_cza_current_background			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/cza_current_background.png";
	cza_avatars_popup_container_cell_cza_current_background_cza_facebook_icon			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/sprites/cza_facebook_icon.png";
	cza_avatars_popup_container_cell_cza_current_background_cza_inframe			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/sprites/cza_inframe.png";
	cza_avatars_popup_container_cell_cza_current_background_cza_selected			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/sprites/cza_selected.png";
	cza_avatars_popup_container_cell_cza_current_background_cza_use_background			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/sprites/cza_use_background.png";
	cza_avatars_popup_container_cell_cza_current_background_use_use_use_active			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/menus/use/menuitems/use/sprites/use_active.png";
	cza_avatars_popup_container_cell_cza_current_background_use_use_use_normal			= "cza_avatars_popup/tables/container/cell/sprites/cza_current_background/menus/use/menuitems/use/sprites/use_normal.png";
	cza_avatars_popup_resource_memory_game_ki_tu			= "cza_avatars_popup/resource/memory_game/ki tu.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_exit_ex_active			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/exit/sprites/ex_active.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_exit_ex_normal			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/exit/sprites/ex_normal.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_replay_rp_active			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/replay/sprites/rp_active.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_replay_rp_normal			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/replay/sprites/rp_normal.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_square_default_normal			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/square/sprites/default_normal.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_square_text_active			= "cza_avatars_popup/resource/memory_game/main_game_layer/menuitems/square/sprites/text_active.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_background_mg_bg			= "cza_avatars_popup/resource/memory_game/main_game_layer/sprites/background/mg_bg.png";
	cza_avatars_popup_resource_memory_game_main_game_layer_time_bg			= "cza_avatars_popup/resource/memory_game/main_game_layer/sprites/time_bg.png";
	cza_avatars_popup_resource_memory_game_man			= "cza_avatars_popup/resource/memory_game/man.png";
	cza_avatars_popup_resource_memory_game_meo_goi_y			= "cza_avatars_popup/resource/memory_game/meo goi y.png";
	cza_avatars_popup_resource_memory_game_meo			= "cza_avatars_popup/resource/memory_game/meo.png";
	cza_avatars_popup_resource_memory_game_o_trong_goi_y			= "cza_avatars_popup/resource/memory_game/o trong goi y.png";
	cza_avatars_popup_resource_memory_game_o_trong			= "cza_avatars_popup/resource/memory_game/o trong.png";
	cza_avatars_popup_resource_memory_game_thoat_replay			= "cza_avatars_popup/resource/memory_game/thoat-replay.png";

	//don't modify or delete this line
}
