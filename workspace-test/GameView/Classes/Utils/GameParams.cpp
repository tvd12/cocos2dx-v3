//
//  GameParams.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/10/13.
//
//

#include "GameParams.h"
#include "VisibleRect.h"

GameParams::GameParams()
{
    // setting default
    isSoundOn = true;
    isMusicOn = true;
    isDonEnabled = true;
    isLeftHand = true;
    
    getUserDefaultSettings();
}

void GameParams::getUserDefaultSettings()
{
    isSoundOn = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_SOUND_EFFECT, true);
    isMusicOn = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_MUSIC, true);
    isDonEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_DOUBLE_OR_NOTHING, true);
    isLeftHand = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_LEFT_HAND, true);
}

CCPoint GameParams::MakePoint(float x, float y)
{
    CCPoint point = CCPoint(x, VisibleRect::top().y - y);
    return point;
}

CCPoint GameParams::MakePointCommon(float x, float y)
{
    CCPoint point = CCPoint(x, 480 - y);
    return point;
}

void GameParams::initIphone4Params()
{
    // init common params
    initIphone4_5Params();
    
    // Login scene
    LOG_FB_BUTTON_POSITION                      = MakePoint(160, 330);
    LOG_GUEST_BUTTON_POSITION                   = MakePoint(160, 390);
    LOG_STATUS_LABEL_POSITION                   = MakePoint(160, 445);
    
    // Lobby scene
    LBB_PAGE_INDICATOR_ON_SELECT_GAME_POSITION  = MakePoint(160, 432);
    LBB_SELECT_GAME_SCROLL_VIEW_BOUNDING_BOX    = CCRect(15, VisibleRect::top().y - 477,
                                                         305, VisibleRect::top().y - 160);
    
    LBB_NUMBER_OF_MENU_ITEM_ON_SELECT_GAME      = 3;
    
    LBB_FOOTER_BG_POSITION                      = MakePoint(160, 448);
    LBB_FOOTER_AVATAR_POSITION                  = MakePoint(28, 450);
    LBB_FOOTER_LEVEL_BAR_POSITION               = MakePoint(160, 465);
    LBB_FOOTER_LEVEL_LABEL_POSITION             = MakePoint(269, 465);

    //Main game scene
    // Main game midle
    MAIN_CHIP_INFO_BG_POSITION                  = MakePoint(160, 240);
    MAIN_TOTAL_CHIP_BG_POSITION                 = MakePoint(82, 240);
    MAIN_TOTAL_CHIP_ICON_POSITION               = MakePoint(28, 239);
    MAIN_BET_CHIP_BG_POSITION                   = MakePoint(252, 240);
    MAIN_ADD_CHIP_BUTTON_POSITION               = MakePoint(142, 240);
    MAIN_TOTAL_BET_CHIP_BUTTON_POSITION         = MakePoint(191, 240);
    MAIN_TOTAL_CHIPS_LABEL_POSITION             = MakePoint(54, 239);
    MAIN_BET_CHIPS_LABEL_POSITION               = MakePoint(238, 239);
    MAIN_WON_CHIPS_LABEL_POSITION               = MakePoint(239, 239);
    MAIN_BET_CHIPS_SPRITE_POSITION              = MakePoint(211, 239);
    MAIN_WON_CHIPS_SPRITE_POSITION              = MakePoint(210, 239);

    // Main game footer
    MAIN_DEAL_BUTTON_POSITION                   = MakePoint(264, 444);
    MAIN_MAX_BET_BUTTON_POSITION                = MakePoint(172, 454);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[0]          = MakePoint(28, 448);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[1]          = MakePoint(76, 452);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[2]          = MakePoint(124, 452);
    MAIN_DON_YES_BUTTON_POSITION                = MakePoint(245, 447);
    MAIN_DON_NO_BUTTON_POSITION                 = MakePoint(292, 443);
    MAIN_DON_LABEL_POSITION                     = MakePoint(15, 452);
    
    MAIN_CARDS_POSITIONS[0]                     = MakePoint(40, 342);
    MAIN_CARDS_POSITIONS[1]                     = MakePoint(100, 342);
    MAIN_CARDS_POSITIONS[2]                     = MakePoint(160, 342);
    MAIN_CARDS_POSITIONS[3]                     = MakePoint(220, 342);
    MAIN_CARDS_POSITIONS[4]                     = MakePoint(280, 342);
    
    MAIN_HELDINGS_POSITIONS[0]                  = MakePoint(52 + 0*60, 322);
    MAIN_HELDINGS_POSITIONS[1]                  = MakePoint(52 + 1*60, 322);
    MAIN_HELDINGS_POSITIONS[2]                  = MakePoint(52 + 2*60, 322);
    MAIN_HELDINGS_POSITIONS[3]                  = MakePoint(52 + 3*60, 322);
    MAIN_HELDINGS_POSITIONS[4]                  = MakePoint(52 + 4*60, 322);
    
    MAIN_FUNCTION_BG_POSITION                   = MakePoint(160, 446);
    MAIN_FUNCTION_BUTTON_BG_POSITION            = MakePoint(258, 440);

    // paytable cells
    MAIN_PAYTABLE_BG_POSITION                   = MakePoint(160, 137);
    MAIN_PAYTABLE_CELL_POSITIONS[0]             = MakePoint(82, 90);
    MAIN_PAYTABLE_CELL_POSITIONS[1]             = MakePoint(82, 115);
    MAIN_PAYTABLE_CELL_POSITIONS[2]             = MakePoint(82, 140);
    MAIN_PAYTABLE_CELL_POSITIONS[3]             = MakePoint(82, 165);
    MAIN_PAYTABLE_CELL_POSITIONS[4]             = MakePoint(82, 190);
    
    MAIN_PAYTABLE_CELL_POSITIONS[5]             = MakePoint(238, 90);
    MAIN_PAYTABLE_CELL_POSITIONS[6]             = MakePoint(238, 115);
    MAIN_PAYTABLE_CELL_POSITIONS[7]             = MakePoint(238, 140);
    MAIN_PAYTABLE_CELL_POSITIONS[8]             = MakePoint(238, 165);
    MAIN_PAYTABLE_CELL_POSITIONS[9]             = MakePoint(238, 190);
    
    //
    // Loading scene
    //
    LOADING_PROGRESS_BAR_POSITION               = MakePoint(160, 420);
}

void GameParams::initIphone5Params()
{
    // init common params
    initIphone4_5Params();
    
    // init just for iphone 5
    // Login scene
    LOG_FB_BUTTON_POSITION                      = MakePoint(160, 382);
    LOG_GUEST_BUTTON_POSITION                   = MakePoint(160, 444);
    LOG_STATUS_LABEL_POSITION                   = MakePoint(160, 517);
    
    // lobby scene
    LBB_PAGE_INDICATOR_ON_SELECT_GAME_POSITION  = MakePoint(160, 516);
    LBB_SELECT_GAME_SCROLL_VIEW_BOUNDING_BOX    = CCRect(0, VisibleRect::top().y - 534,
                                                         320, 360);

    LBB_GAME_LIST_POSITION[3]                   = MakePoint(160, 460);
    LBB_NUMBER_OF_MENU_ITEM_ON_SELECT_GAME      = 4;

    LBB_FOOTER_BG_POSITION                      = MakePoint(160, 536);
    LBB_FOOTER_AVATAR_POSITION                  = MakePoint(28, 538);
    LBB_FOOTER_LEVEL_BAR_POSITION               = MakePoint(160, 552);
    LBB_FOOTER_LEVEL_LABEL_POSITION             = MakePoint(269, 552);

    // main game scene
    // Main game midle
    MAIN_CHIP_INFO_BG_POSITION                  = MakePoint(160, 240 + 39);
    MAIN_TOTAL_CHIP_BG_POSITION                 = MakePoint(82, 240 + 39);
    MAIN_TOTAL_CHIP_ICON_POSITION               = MakePoint(28, 239 + 39);
    MAIN_BET_CHIP_BG_POSITION                   = MakePoint(252, 240 + 39);
    MAIN_ADD_CHIP_BUTTON_POSITION               = MakePoint(142, 240 + 39);
    MAIN_TOTAL_BET_CHIP_BUTTON_POSITION         = MakePoint(191, 240 + 39);
    MAIN_TOTAL_CHIPS_LABEL_POSITION             = MakePoint(54, 239 + 39);
    MAIN_BET_CHIPS_LABEL_POSITION               = MakePoint(238, 239 + 39);
    MAIN_WON_CHIPS_LABEL_POSITION               = MakePoint(239, 239 + 39);
    MAIN_BET_CHIPS_SPRITE_POSITION              = MakePoint(211, 239 + 39);
    MAIN_WON_CHIPS_SPRITE_POSITION              = MakePoint(210, 239 + 39);
    
    // Main game footer
    MAIN_FUNCTION_BG_POSITION                   = MakePoint(160, 534);
    MAIN_FUNCTION_BUTTON_BG_POSITION            = MakePoint(258, 528);
    
    MAIN_DEAL_BUTTON_POSITION                   = MakePoint(264, 532);
    MAIN_MAX_BET_BUTTON_POSITION                = MakePoint(172, 542);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[0]          = MakePoint(28, 448 + 92);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[1]          = MakePoint(76, 452 + 92);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[2]          = MakePoint(124, 452 + 92);
    MAIN_DON_YES_BUTTON_POSITION                = MakePoint(245, 447 + 92);
    MAIN_DON_NO_BUTTON_POSITION                 = MakePoint(292, 443 + 92);
    MAIN_DON_LABEL_POSITION                     = MakePoint(15, 452 + 92);
    
    MAIN_CARDS_POSITIONS[0]                     = MakePoint(40 + 0*60, 416);
    MAIN_CARDS_POSITIONS[1]                     = MakePoint(40 + 1*60, 416);
    MAIN_CARDS_POSITIONS[2]                     = MakePoint(40 + 2*60, 416);
    MAIN_CARDS_POSITIONS[3]                     = MakePoint(40 + 3*60, 416);
    MAIN_CARDS_POSITIONS[4]                     = MakePoint(40 + 4*60, 416);
    
    MAIN_HELDINGS_POSITIONS[0]                  = MakePoint(52 + 0*60, 396);
    MAIN_HELDINGS_POSITIONS[1]                  = MakePoint(52 + 1*60, 396);
    MAIN_HELDINGS_POSITIONS[2]                  = MakePoint(52 + 2*60, 396);
    MAIN_HELDINGS_POSITIONS[3]                  = MakePoint(52 + 3*60, 396);
    MAIN_HELDINGS_POSITIONS[4]                  = MakePoint(52 + 4*60, 396);
    
    // paytable cells
    MAIN_PAYTABLE_BG_POSITION                   = MakePoint(160, 157);
    MAIN_PAYTABLE_CELL_POSITIONS[0]             = MakePoint(82, 92 + 0*32);
    MAIN_PAYTABLE_CELL_POSITIONS[1]             = MakePoint(82, 92 + 1*32);
    MAIN_PAYTABLE_CELL_POSITIONS[2]             = MakePoint(82, 92 + 2*32);
    MAIN_PAYTABLE_CELL_POSITIONS[3]             = MakePoint(82, 92 + 3*32);
    MAIN_PAYTABLE_CELL_POSITIONS[4]             = MakePoint(82, 92 + 4*32);
    
    MAIN_PAYTABLE_CELL_POSITIONS[5]             = MakePoint(238, 92 + 0*32);
    MAIN_PAYTABLE_CELL_POSITIONS[6]             = MakePoint(238, 92 + 1*32);
    MAIN_PAYTABLE_CELL_POSITIONS[7]             = MakePoint(238, 92 + 2*32);
    MAIN_PAYTABLE_CELL_POSITIONS[8]             = MakePoint(238, 92 + 3*32);
    MAIN_PAYTABLE_CELL_POSITIONS[9]             = MakePoint(238, 92 + 4*32);

    //
    // Loading scene
    //
    LOADING_PROGRESS_BAR_POSITION               = MakePoint(160, 460);
}

void GameParams::initIphone4_5Params()
{
    isIpadDevice = false;
    
    CMM_FONT_SIZE_0 =                       10.0f;
    CMM_FONT_SIZE_1 =                       13.0f;
    CMM_FONT_SIZE_2 =                       14.0f;
    CMM_FONT_SIZE_3 =                       15.0f;
    CMM_FONT_SIZE_4 =                       17.0f;
    CMM_FONT_SIZE_5 =                       19.0f;
    CMM_FONT_SIZE_6 =                       40.0f;
    
    CMM_CARD_FONT_SIZE =                    17.0f;

    CMM_ICON_FB_SIZE                                    = CCSizeMake(160, 160);
    CMM_ICON_LOBBY_SIZE                                 = CCSizeMake(42, 42);
    CMM_ICON_PROFILE_SIZE                               = CCSizeMake(49, 49);
    CMM_ICON_AVATAR_SIZE                                = CCSizeMake(55, 55);

    // lobby scene
    LBB_SELECT_GAME_HEADER_POSITION                     = MakePoint(160, 57);

    LBB_GAME_LIST_POSITION[0]                           = MakePoint(160, 220);
    LBB_GAME_LIST_POSITION[1]                           = MakePoint(160, 300);
    LBB_GAME_LIST_POSITION[2]                           = MakePoint(160, 380);

    LBB_HEADER_BG_POSITION                              = MakePoint(160, 57);
    LBB_HEADER_SETTINGS_BUTTON_POSITION                 = MakePoint(22, 22);
    
    LBB_MIDDLE_BG_POSITION                              = MakePoint(160, 140);
    LBB_MIDDLE_CHIP_BG_POSITION                         = MakePoint(82, 140);
    LBB_MIDDLE_CHIP_ICON_POSITION                       = MakePoint(29, 140);
    LBB_MIDDLE_CHIP_LABEL_POSITION                      = MakePoint(53, 140);
    LBB_MIDDLE_CHIP_BUTTON_POSITION                     = MakePoint(143, 140);
    LBB_MIDDLE_BONUS_BG_POSITION                        = MakePoint(262, 140);
    LBB_MIDDLE_BONUS_LABEL_POSITION                     = MakePoint(244, 140);
    LBB_MIDDLE_BONUS_BUTTON_POSITION                    = MakePoint(209, 140);

    LBB_STACKS_IN_MENU_ITEM_POSITION                    = MakePointCommon(188, 462);
    LBB_JACKPOT_SPRITE_IN_MENU_ITEM_POSITION            = MakePointCommon(208, 428);
    LBB_JACKPOT_LABEL_IN_MENU_ITEM_POSITION             = MakePointCommon(188, 441);
    LBB_LOCK_SPRITE_IN_MENU_ITEM_POSITION               = MakePointCommon(178, 443);
    LBB_LOCK_LABEL_IN_MENU_ITEM_POSITION                = MakePointCommon(189, 443);
    
    // main game scene
    MAIN_HEADER_BG_POSITION                             = MakePoint(160, 34);
    MAIN_HEADER_LEVEL_POSITION                          = MakePoint(57, 37);
    MAIN_HEADER_BOARD_POSITION                          = MakePoint(194, 30);
    
    MAIN_EXIT_BUTTON_POSITION                           = MakePoint(296, 16);
    MAIN_SETTINGS_BUTTON_POSITION                       = MakePoint(296, 49);
    
    MAIN_JACKPOT_VALUE_LABEL_POSITION                   = MakePoint(173, 37);
    MAIN_HAND_OF_JACKPOT_LABEL_POSTION                  = MakePoint(129, 20); //left
    MAIN_JACKPOT_STRING_LABEL_POSITION                  = MakePoint(129, 39); //left
    MAIN_TOTAL_USER_LABEL_POSITION                      = CCPoint(3, 2);
    MAIN_LEVEL_LABEL_POSITION                           = MakePoint(58, 20);

    MAIN_PAYTABLE_CELL_NAME_DELTA                       = 65;
    MAIN_DON_MOVING_DISTANCE                            = 200;

    
    // card view
    CARD_RANK_LABEL_POSITION                            = MakePointCommon(10,417);
    CARD_SUIT_SMALL_ICON_POSITION                       = MakePointCommon(10,430);
    CARD_SUIT_ICON_POSITION                             = MakePointCommon(27,454);
    CARD_JQK_ICON_POSITION                              = MakePointCommon(27,454);
    CARD_JQK_SUIT_ICON_POSITION                         = MakePointCommon(12,410);
    CARD_WILD_ICON_POSITION                             = MakePointCommon(27,454);
    CARD_JOKER_ICON_POSITION                            = MakePointCommon(27,454);
    CARD_JOKER_LABEL_POSITION                           = MakePointCommon(27,418);

    // Notification popup
    NTF_TITLE_TEXT_POSITION                             = MakePointCommon(148, 336);
    NTF_MESSAGE_TEXT_POSITION                           = MakePointCommon(148, 390);
    NTF_BUTTON_CENTER_POSITION                          = MakePointCommon(148, 438);
    NTF_BUTTON_LEFT_POSITION                            = MakePointCommon(88, 438);
    NTF_BUTTON_RIGHT_POSITION                           = MakePointCommon(208, 438);
    NTF_MESSAGE_SIZE                                    = CCSizeMake(240,52);

    POP_COMMON_EXIT_BUTTON_POSITION                     = MakePointCommon(148,450);
    POP_COMMON_HEADER_POSITION                          = MakePointCommon(148, 66);
    
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[0]           = MakePointCommon(82, 214 + 0*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[1]           = MakePointCommon(82, 214 + 1*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[2]           = MakePointCommon(82, 214 + 2*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[3]           = MakePointCommon(82, 214 + 3*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[4]           = MakePointCommon(82, 214 + 4*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[5]           = MakePointCommon(82, 214 + 5*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[6]           = MakePointCommon(216, 214 + 0*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[7]           = MakePointCommon(216, 214 + 1*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[8]           = MakePointCommon(216, 214 + 2*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[9]           = MakePointCommon(216, 214 + 3*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[10]          = MakePointCommon(216, 214 + 4*37);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[11]          = MakePointCommon(216, 214 + 5*37);
    
    POP_PAYTABLE_CARDS_POSTIONS[0]                      = MakePointCommon(48 + 0*50, 150);
    POP_PAYTABLE_CARDS_POSTIONS[1]                      = MakePointCommon(48 + 1*50, 150);
    POP_PAYTABLE_CARDS_POSTIONS[2]                      = MakePointCommon(48 + 2*50, 150);
    POP_PAYTABLE_CARDS_POSTIONS[3]                      = MakePointCommon(48 + 3*50, 150);
    POP_PAYTABLE_CARDS_POSTIONS[4]                      = MakePointCommon(48 + 4*50, 150);
    
    POP_PAYTABLE_CARD_VIEW_CONTAINER_POSITION           = MakePointCommon(148, 150);
    
    POP_PAYTABLE_PAYOUT_SPRITE_POSITION                 = MakePointCommon(134, 110);
    POP_PAYTABLE_PAYOUT_LABEL_POSITION                  = MakePointCommon(165, 110);
    
    POP_SETTING_SOUND_EFFECT_LABEL_POSITION             = MakePointCommon(30, 118); //left
    POP_SETTING_MUSIC_LABEL_POSITION                    = MakePointCommon(30, 118 + 1*44); //left
    POP_SETTING_LEFT_HAND_LABEL_POSITION                = MakePointCommon(30, 118 + 2*44); //left
    POP_SETTING_DOUBLE_OR_NOTHING_LABEL_POSITION        = MakePointCommon(30, 118 + 3*44); //left
    
    POP_SETTING_SOUND_EFFECT_MENUITEM_POSITION          = MakePointCommon(233, 118);
    POP_SETTING_MUSIC_MENUITEM_POSITION                 = MakePointCommon(233, 118 + 1*44);
    POP_SETTING_LEFT_HAND_MENUITEM_POSITION             = MakePointCommon(233, 118 + 2*44);
    POP_SETTING_DOUBLE_OR_NOTHING_MENUITEM_POSITION     = MakePointCommon(233, 118 + 3*44);
    
    POP_SETTING_RATE_US_MENUITEM_POSITION               = MakePointCommon(82, 305);
    POP_SETTING_FEEDBACK_MENUITEM_POSITION              = MakePointCommon(214, 305);
    POP_SETTING_LIKE_PAGE_MENUITEM_POSITION             = MakePointCommon(82, 357);;
    POP_SETTING_INVITE_FRIEND_MENUITEM_POSITION         = MakePointCommon(214, 357);;

    POP_SETTING_PRIVATE_POLICY_MENUITEM_POSITION        = MakePointCommon(78, 421);
    POP_SETTING_TERM_OF_SERVICES_MENUITEM_POSITION      = MakePointCommon(218, 421);
    
    //shopping popup
    POP_SHOP_PACKET_NAME_LABEL_POSITION                 = CCPoint(65, 480 - 380);
    POP_SHOP_CHIP_AMOUNT_LABEL_POSITION                 = CCPoint(14 + 9, 480 - 454); //left
    POP_SHOP_VIP_POINT_LABEL_POSITION                   = CCPoint(14 + 9, 480 - 466); //left
    
    POP_SHOP_PRICE_MENUITEM_POSITION                    = CCPoint(75, 480 - 472);
    
    POP_SHOP_MAIN_ICON_SPRITE_POSITION                  = CCPoint(65, 480 - 416);
    POP_SHOP_CHIP_ICON_SPRITE_POSITION                  = CCPoint(14, 480 - 454);
    POP_SHOP_STAR_ICON_SPRITE_POSITION                  = CCPoint(14, 480 - 466);
    
    POP_SHOP_PRODUCT_MENUITEMS_POSITIONS[0]             = CCPoint(13*0 + 61*1, 57.5f);
    POP_SHOP_PRODUCT_MENUITEMS_POSITIONS[1]             = CCPoint(13*1 + 61*3, 57.5f);
    
    POP_SHOP_TABLEVIEW_POSITION                         = CCPoint(19, 60 + 14); //left-down
    
    POP_SHOP_MENU_BOUNDINGBOX                           = CCRect(0, 0, 296, 390);
    
    POP_SHOP_TABLEVIEW_CELL_SIZE                        = CCSizeMake(257, 115 + 14);
    
    POP_SHOP_TABLEVIEW_SIZE                             = CCSizeMake(257, 322);
    
    //profile popup
    POP_PROFILE_AVARTAR_MENUITEM_POSITION               = MakePointCommon(79, 419);
    POP_PROFILE_VIP_CLUB_MENUITEM_POSITION              = MakePointCommon(218, 419);
    POP_PROFILE_LOGOUT_MENUITEM_POSITION                = MakePointCommon(228, 71);
    
    POP_PROFILE_CIRCLE_AVATAR_SPRITE_POSITION           = MakePointCommon(148, 77);
    
    //left
    POP_PROFILE_BEST_HAND_SPRITE_POSITION               = MakePointCommon(27, 306 - 0*(9 + 15)- 8);
    POP_PROFILE_WIN_RATIO_SPRITE_POSITION               = MakePointCommon(27, 306 - 1*(9 + 15)- 8);
    POP_PROFILE_BIGGEST_WIN_SPRITE_POSITION             = MakePointCommon(27, 306 - 2*(9 + 15)- 8);
    POP_PROFILE_HANDS_WON_SPRITE_POSITION               = MakePointCommon(27, 306 - 3*(9 + 15)- 8);
    POP_PROFILE_HANDS_PLAYED_SPRITE_POSITION            = MakePointCommon(27, 306 - 4*(9 + 15)- 8);
    
    POP_PROFILE_GENDER_ICON_SPRITE_POSITION             = MakePointCommon(28, 172 - 1*(9 + 15)- 8);
    POP_PROFILE_LOCATION_ICON_SPRITE_POSITION           = MakePointCommon(28, 172 - 0*(9 + 15)- 8);
    POP_PROFILE_LEVEL_ICON_SPRITE_POSITION              = MakePointCommon(178, 172 - 0*(9 + 15)- 8);
    POP_PROFILE_CHIP_ICON_SPRITE_POSITION               = MakePointCommon(178, 172 - 1*(9 + 15)- 8);
    
    POP_PROFILE_NICKNAME_LABEL_POSITION                 = MakePointCommon(28 + 15, 172-1*(9 + 15)- 8);
    POP_PROFILE_LOCATION_LABEL_POSITION                 = MakePointCommon(28 + 15, 172-0*(9 + 15)- 8);
    POP_PROFILE_CHIPS_LABEL_POSITION                    = MakePointCommon(178 + 15, 172-1*(9 + 15)- 8);
    POP_PROFILE_LEVEL_LABEL_POSITION                    = MakePointCommon(178 + 15, 172-0*(9 + 15)- 8);

    POP_PROFILE_WIN_RATIO_LABEL_POSITION                = MakePointCommon(269, 306 - 1*(9 + 15)- 8);
    POP_PROFILE_BIGGEST_WIN_LABEL_POSITION              = MakePointCommon(269, 306 - 2*(9 + 15)- 8);
    POP_PROFILE_HANDS_WON_LABEL_POSITION                = MakePointCommon(269, 306 - 3*(9 + 15)- 8);
    POP_PROFILE_HANDS_PLAYED_LABEL_POSITION             = MakePointCommon(269, 306 - 4*(9 + 15)- 8);
    
    POP_PROFILE_CARDS_POSTIONS[0]                       = MakePointCommon(50 + 0*(43 + 6), 349);
    POP_PROFILE_CARDS_POSTIONS[1]                       = MakePointCommon(50 + 1*(43 + 6), 349);
    POP_PROFILE_CARDS_POSTIONS[2]                       = MakePointCommon(50 + 2*(43 + 6), 349);
    POP_PROFILE_CARDS_POSTIONS[3]                       = MakePointCommon(50 + 3*(43 + 6), 349);
    POP_PROFILE_CARDS_POSTIONS[4]                       = MakePointCommon(50 + 4*(43 + 6), 349);
    
    POP_PROFILE_CARD_SCALE                              = 0.85f;
    
    //dailybonus popup
    POP_DAILYBONUS_LEVEL_SPRITE_POSITION                = MakePointCommon(81, 228);
    POP_DAILYBONUS_VIP_SPRITE_POSITION                  = MakePointCommon(213, 228);
    POP_DAILYBONUS_DAYS_SPRITE_POSITION                 = MakePointCommon(81, 138);
    POP_DAILYBONUS_FACEBOOK_FRIEND_SPRITE_POSITION		= MakePointCommon(213, 138);
    POP_DAILYBONUS_CLAIM_MENUITEM_POSITION              = MakePointCommon(147, 388);
    POP_DAILYBONUS_TOTAL_BONUS_SPRITE_POSITION			= MakePointCommon(147, 310);
    POP_DAILYBONUS_HEADER_SPRITE_POSITION               = POP_COMMON_HEADER_POSITION;
    POP_DAILYBONUS_SLIVER_CARD_SPRITE_POSITION			= MakePointCommon(186, 218);
    POP_DAILYBONUS_COMEBACK_SPRITE_POSITION             = MakePointCommon(147, 354);
    
    POP_DAILYBONUS_LEVEL_SEPARATE_SPRITE_POSITION		= MakePointCommon(106, 214);
    POP_DAILYBONUS_FACEBOOK_SEPARATE_SPRITE_POSITION	= MakePointCommon(238, 126);
    
    POP_DAILYBONUS_DAYS_LABEL_POSITION                          = MakePointCommon(108, 126);
    POP_DAILYBONUS_DAYS_CHIPS_LABEL_POSITION                    = MakePointCommon(100, 164);
    POP_DAILYBONUS_FACEBOOK_FRIEND_PART_ONE_LABEL_POSITION 		= MakePointCommon(238, 116);
    POP_DAILYBONUS_FACEBOOK_FRIEND_PART_TWO_LABEL_POSITION 		= MakePointCommon(236, 136);
    POP_DAILYBONUS_FACEBOOK_FRIEND_CHIPS_LABEL_POSITION 		= MakePointCommon(233, 164);
    POP_DAILYBONUS_LEVEL_PART_ONE_LABEL_POSITION                = MakePointCommon(106, 204);
    POP_DAILYBONUS_LEVEL_PART_TWO_LABEL_POSITION                = MakePointCommon(106, 224);
    POP_DAILYBONUS_LEVEL_CHIPS_LABEL_POSITION                   = MakePointCommon(100, 254);
    POP_DAILYBONUS_VIP_LABEL_POSITION                           = MakePointCommon(244, 215);
    POP_DAILYBONUS_VIP_CHIPS_LABEL_POSITION                     = MakePointCommon(233, 254);
    POP_DAILYBONUS_TOTAL_BONUS_TEXT_LABEL_POSITION              = MakePointCommon(78, 310);
    POP_DAILYBONUS_TOTAL_BONUS_VALUE_LABEL_POSITION             = MakePointCommon(197, 310);
    POP_DAILYBONUS_DAYS_VALUE_LABEL_POSITION                    = MakePointCommon(59, 129);
    
    POP_DAILYBONUS_DAYS_LABEL_DIMENSION                         = CCSizeMake(52.0, 36.0);
    POP_DAILYBONUS_VIP_LABEL_DIMENSION                          = CCSizeMake(52.0, 34.0);
    
    //vipclub popup
    POP_VIPCLUB_HEADER_SPRITE_POSITION                      = POP_COMMON_HEADER_POSITION;
    
    POP_VIPCLUB_BRONZE_TEXT_SPRITE_POSITION                 = MakePointCommon(87, 182 + 0*50); //left
    POP_VIPCLUB_SLIVER_TEXT_SPRITE_POSITION                 = MakePointCommon(87, 187 + 1*50); //left
    POP_VIPCLUB_GOLD_TEXT_SPRITE_POSITION                   = MakePointCommon(87, 186 + 2*50); //left
    POP_VIPCLUB_PLATINUM_TEXT_SPRITE_POSITION               = MakePointCommon(87, 186 + 3*50); //left
    POP_VIPCLUB_DIAMOND_TEXT_SPRITE_POSITION                = MakePointCommon(87, 186 + 4*50); //left
    
    POP_VIPCLUB_BRONZE_CARD_SPRITE_POSITION                 = MakePointCommon(47, 191 + 0*50);
    POP_VIPCLUB_SLIVER_CARD_SPRITE_POSITION                 = MakePointCommon(47, 196 + 1*50);
    POP_VIPCLUB_GOLD_CARD_SPRITE_POSITION                   = MakePointCommon(47, 196 + 2*50);
    POP_VIPCLUB_PLATINUM_CARD_SPRITE_POSITION               = MakePointCommon(47, 196 + 3*50);
    POP_VIPCLUB_DIAMOND_CARD_SPRITE_POSITION                = MakePointCommon(47, 196 + 4*50);
    
    POP_VIPCLUB_MEMBER_CARD_SPRITE_POSITION                 = MakePointCommon(62, 127);
    POP_VIPCLUB_BIG_BRONZE_CARD_SPRITE_POSITION             = MakePointCommon(62, 127);
    POP_VIPCLUB_BIG_GOLD_CARD_SPRITE_POSITION               = MakePointCommon(62, 127);
    POP_VIPCLUB_BIG_SLIVER_CARD_SPRITE_POSITION             = MakePointCommon(62, 127);
    POP_VIPCLUB_BIG_PLATINUM_CARD_SPRITE_POSITION			= MakePointCommon(62, 127);
    POP_VIPCLUB_BIG_DIAMOND_CARD_SPRITE_POSITION			= MakePointCommon(62, 127);
    
    POP_VIPCLUB_LINES_SPRITE_POSITION                       = MakePointCommon(148, 268);
    
    POP_VIPCLUB_PROGRESS_LEVEL_SPRITE_POSITION              = MakePointCommon(194, 113);
    POP_VIPCLUB_PROGRESS_LEVEL_BACKGROUND_SPRITE_POSITION	= MakePointCommon(194, 113);

    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[0]                = MakePointCommon(265, 182 + 0*50);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[1]                = MakePointCommon(265, 182 + 1*50);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[2]                = MakePointCommon(265, 182 + 2*50);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[3]                = MakePointCommon(265, 182 + 3*50);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[4]                = MakePointCommon(265, 182 + 4*50);
    
    POP_VIPCLUB_NOTE_MORE_POINTS_LABEL_POSITION          = MakePointCommon(111, 134);
    POP_VIPCLUB_NOTE_MULTIPLE_LABEL_POSITION             = MakePointCommon(111, 148);
    
    POP_VIPCLUB_BRONZE_VIP_POINT_TEXT_LABEL_POSITION 	= MakePointCommon(108, 200 + 0*50);
    POP_VIPCLUB_BRONZE_VIP_POINT_VALUE_LABEL_POSITION 	= MakePointCommon(132 + 3, 200 + 0*50); //left
    POP_VIPCLUB_BRONZE_PACKAGES_TEXT_LABEL_POSITION 	= MakePointCommon(212, 200 + 0*50);
    POP_VIPCLUB_BRONZE_PACKAGES_VALUE_LABEL_POSITION 	= MakePointCommon(240 + 3, 200 + 0*50);
    
    POP_VIPCLUB_SLIVER_VIP_POINT_TEXT_LABEL_POSITION 	= MakePointCommon(108, 204 + 1*50);
    POP_VIPCLUB_SLIVER_VIP_POINT_VALUE_LABEL_POSITION 	= MakePointCommon(132 + 3, 204 + 1*50); //left
    POP_VIPCLUB_SLIVER_PACKAGES_TEXT_LABEL_POSITION 	= MakePointCommon(212, 204 + 1*50);
    POP_VIPCLUB_SLIVER_PACKAGES_VALUE_LABEL_POSITION 	= MakePointCommon(240 + 3, 204 + 1*50);
    
    POP_VIPCLUB_GOLD_VIP_POINT_TEXT_LABEL_POSITION 		= MakePointCommon(108, 204 + 2*50);
    POP_VIPCLUB_GOLD_VIP_POINT_VALUE_LABEL_POSITION 	= MakePointCommon(132 + 3, 204 + 2*50); //left
    POP_VIPCLUB_GOLD_PACKAGES_TEXT_LABEL_POSITION 		= MakePointCommon(212, 204 + 2*50);
    POP_VIPCLUB_GOLD_PACKAGES_VALUE_LABEL_POSITION 		= MakePointCommon(240 + 3, 204 + 2*50);
    
    POP_VIPCLUB_PLATINUM_VIP_POINT_TEXT_LABEL_POSITION 	= MakePointCommon(108, 204 + 3*50);
    POP_VIPCLUB_PLATINUM_VIP_POINT_VALUE_LABEL_POSITION = MakePointCommon(132 + 3, 204 + 3*50); //left
    POP_VIPCLUB_PLATINUM_PACKAGES_TEXT_LABEL_POSITION 	= MakePointCommon(212, 204 + 3*50);
    POP_VIPCLUB_PLATINUM_PACKAGES_VALUE_LABEL_POSITION 	= MakePointCommon(240 + 3, 204 + 3*50);
    
    POP_VIPCLUB_DIAMOND_VIP_POINT_TEXT_LABEL_POSITION 	= MakePointCommon(108, 204 + 4*50);
    POP_VIPCLUB_DIAMOND_VIP_POINT_VALUE_LABEL_POSITION 	= MakePointCommon(132 + 3, 204 + 4*50); //left
    POP_VIPCLUB_DIAMOND_PACKAGES_TEXT_LABEL_POSITION 	= MakePointCommon(212, 204 + 4*50);
    POP_VIPCLUB_DIAMOND_PACKAGES_VALUE_LABEL_POSITION 	= MakePointCommon(240 + 3, 204 + 4*50);
    
    /**
     * mDefaultPopup position init
     * by apple
     */
	
    
    /**
     * mDefaultPopup position init
     * by apple
     */
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[0] 		= CCPoint(38 + 0*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[1] 		= CCPoint(38 + 1*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[2] 		= CCPoint(38 + 2*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[3] 		= CCPoint(38 + 0*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[4] 		= CCPoint(38 + 1*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[5] 		= CCPoint(38 + 2*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[6] 		= CCPoint(38 + 0*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[7] 		= CCPoint(38 + 1*88, 52);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[8] 		= CCPoint(38 + 2*88, 52);
	POP_AVATARS_AVATAR_1_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_2_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_3_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_4_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_5_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_6_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_7_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_8_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_9_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_FB_ICON_SPRITE_POSITION             = MakePointCommon(50, 430);
	POP_AVATARS_CONTAINER_TABLE_POSITION            = MakePointCommon(20, 403);
	POP_AVATARS_INFRAME_SPRITE_POSITION             = MakePointCommon(38, 414);
	POP_AVATARS_USE_MENUITEM_POSITION               = MakePointCommon(38, 460);
	POP_AVATARS_USE_MENU_POSITION                   = MakePointCommon(0, 0);
    
    POP_AVATARS_CONTAINER_TABLE_SIZE                = CCSizeMake(256, 302);
    POP_AVATARS_CONTAINER_TABLE_CELL_SIZE           = CCSizeMake(256, 114);
    
    POP_AVATARS_CELL_POSITION                       = CCPoint(128, 57);
    
    /**
     * JackpotPopupView position init
     * by Dung Ta Van
     */
	POP_JACKPOT_CHIPS_SPRITE_POSITION               = MakePointCommon(63, 382);
	POP_JACKPOT_JACKPOT_TEXT_SPRITE_POSITION 		= MakePointCommon(148, 290);
	POP_JACKPOT_REWARD_ICON_SPRITE_POSITION 		= MakePointCommon(148, 349);
	POP_JACKPOT_SHINE_CIRCLE_SPRITE_POSITION 		= MakePointCommon(148, 386);
	POP_JACKPOT_STAR_SHINE_SPRITE_POSITION          = MakePointCommon(148, 272);
    POP_JACKPOT_CHIPS_LABEL_POSITION                = MakePointCommon(95, 402);
    
    POP_JACKPOT_STARS_POSITIONS[0]                  = MakePointCommon(30, 332);
    POP_JACKPOT_STARS_POSITIONS[1]                  = MakePointCommon(250, 336);
    POP_JACKPOT_STARS_POSITIONS[2]                  = MakePointCommon(96, 223);
    POP_JACKPOT_STARS_POSITIONS[3]                  = MakePointCommon(188, 234);

	POP_JACKPOT_OK_MENUITEM_POSITION                = MakePointCommon(96, 438);
	POP_JACKPOT_SHARE_MENUITEM_POSITION             = MakePointCommon(198, 438);

    /**
	* VipUpgradePopupView  position init
	* by Dung Ta Van
	*/
	POP_VIP_UPGRADE_CHIPS_LABEL_POSITION            = MakePointCommon(60, 395);
	POP_VIP_UPGRADE_INAPP_LABEL_POSITION            = MakePointCommon(162, 395);
	POP_VIP_UPGRADE_MEMBER_CARD_SPRITE_POSITION     = MakePointCommon(148, 342);
	POP_VIP_UPGRADE_REWARD_ICON_SPRITE_POSITION     = MakePointCommon(38, 395);
	POP_VIP_UPGRADE_SHINE_SPRITE_POSITION           = MakePointCommon(148, 386);
	POP_VIP_UPGRADE_STAR1_SPRITE_POSITION           = MakePointCommon(205, 362);
	POP_VIP_UPGRADE_STAR2_SPRITE_POSITION           = MakePointCommon(92, 316);
	POP_VIP_UPGRADE_VIP_LEVEL_RIBBON_SPRITE_POSITION    = MakePointCommon(148, 300);

	POP_VIP_UPGRADE_OK_MENUITEM_POSITION            = MakePointCommon(96, 440);
	POP_VIP_UPGRADE_SHARE_MENUITEM_POSITION 		= MakePointCommon(198, 440);

	/**
	* LevelupPopupView  position init
	* by apple
	*/
	POP_LEVELUP_CIRCLE_CONTAINER_1_SPRITE_POSITION  = MakePointCommon(148, 314);
	POP_LEVELUP_CIRCLE_CONTAINER_2_SPRITE_POSITION  = MakePointCommon(148, 314);
	POP_LEVELUP_CONGRATULATION_LABEL_POSITION 		= MakePointCommon(148, 400);
	POP_LEVELUP_LEVEL_LABEL_POSITION                = MakePointCommon(150, 314);
	POP_LEVELUP_RIBBON_SPRITE_POSITION              = MakePointCommon(148, 365);
	POP_LEVELUP_SHINE_CIRCLE_SPRITE_POSITION 		= MakePointCommon(148, 314);
	POP_LEVELUP_STAR1_SPRITE_POSITION               = MakePointCommon(250, 245);
	POP_LEVELUP_STAR2_SPRITE_POSITION               = MakePointCommon(160, 228);
	POP_LEVELUP_STAR3_SPRITE_POSITION               = MakePointCommon(70, 270);
	POP_LEVELUP_STAR_SHINE_SPRITE_POSITION          = MakePointCommon(149, 310);

	POP_LEVELUP_OK_MENUITEM_POSITION                = MakePointCommon(96, 440);
	POP_LEVELUP_SHARE_MENUITEM_POSITION             = MakePointCommon(198, 440);

	

	// LeaderboardPopupView  position init
	// by apple Wed Aug 13 09:33:14 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_RBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);

}

void GameParams::initIpadParams()
{
    isIpadDevice = true;

    POP_COMMON_EXIT_BUTTON_POSITION                     = MakePoint(278, 968);
    POP_COMMON_HEADER_POSITION                          = MakePoint(278, 250);
    
    /**
     * mDefaultPopup position init
     * by apple
     */
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[0] 		= CCPoint(70 + 0*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[1] 		= CCPoint(70 + 1*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[2] 		= CCPoint(70 + 2*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[3] 		= CCPoint(70 + 0*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[4] 		= CCPoint(70 + 1*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[5] 		= CCPoint(70 + 2*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[6] 		= CCPoint(70 + 0*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[7] 		= CCPoint(70 + 1*169, 95);
	POP_AVATARS_AVATARS_SPRITE_POSITIONS[8] 		= CCPoint(70 + 2*169, 95);
	POP_AVATARS_AVATAR_1_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_2_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_3_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_4_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_5_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_6_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_7_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_8_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
	POP_AVATARS_AVATAR_9_SPRITE_POSITION            = POP_AVATARS_INFRAME_SPRITE_POSITION;
    
	POP_AVATARS_FB_ICON_SPRITE_POSITION             = MakePoint(96, 926);
	POP_AVATARS_CONTAINER_TABLE_POSITION            = MakePoint(20, 889);
	POP_AVATARS_INFRAME_SPRITE_POSITION             = MakePoint(70, 901);
	POP_AVATARS_USE_MENUITEM_POSITION               = MakePoint(70, 983);
	POP_AVATARS_USE_MENU_POSITION                   = MakePoint(0, 0);
    
    POP_AVATARS_CONTAINER_TABLE_SIZE                = CCSizeMake(515, 583);
    POP_AVATARS_CONTAINER_TABLE_CELL_SIZE           = CCSizeMake(515, 210);
    
    POP_AVATARS_CELL_POSITION                       = CCPoint(278, 95);
    
    //dailybonus popup
    POP_DAILYBONUS_DAYS_SPRITE_POSITION                 = MakePoint(152 + 0*254, 386 + 0*176);
    POP_DAILYBONUS_FACEBOOK_FRIEND_SPRITE_POSITION		= MakePoint(152 + 1*254, 386 + 0*176);
    POP_DAILYBONUS_LEVEL_SPRITE_POSITION                = MakePoint(152 + 0*254, 386 + 1*176);
    POP_DAILYBONUS_VIP_SPRITE_POSITION                  = MakePoint(152 + 1*254, 386 + 1*176);
    POP_DAILYBONUS_CLAIM_MENUITEM_POSITION              = MakePoint(277, 872);
    POP_DAILYBONUS_TOTAL_BONUS_SPRITE_POSITION			= MakePoint(274, 728);
    POP_DAILYBONUS_HEADER_SPRITE_POSITION               = POP_COMMON_HEADER_POSITION;
    POP_DAILYBONUS_SLIVER_CARD_SPRITE_POSITION			= MakePoint(358, 548);
    POP_DAILYBONUS_COMEBACK_SPRITE_POSITION             = MakePoint(278, 812);
    
    POP_DAILYBONUS_LEVEL_SEPARATE_SPRITE_POSITION		= MakePoint(210, 538);
    POP_DAILYBONUS_FACEBOOK_SEPARATE_SPRITE_POSITION	= MakePoint(452, 361);
    
    POP_DAILYBONUS_DAYS_CHIPS_LABEL_POSITION                    = MakePoint(197 + 0*254, 430 + 0*176);
    POP_DAILYBONUS_FACEBOOK_FRIEND_CHIPS_LABEL_POSITION 		= MakePoint(197 + 1*254, 430 + 0*176);
    POP_DAILYBONUS_LEVEL_CHIPS_LABEL_POSITION                   = MakePoint(197 + 0*254, 430 + 1*176);
    POP_DAILYBONUS_VIP_CHIPS_LABEL_POSITION                     = MakePoint(197 + 1*254, 430 + 1*176);
    
    POP_DAILYBONUS_DAYS_LABEL_POSITION                          = MakePoint(210, 360);
    POP_DAILYBONUS_FACEBOOK_FRIEND_PART_ONE_LABEL_POSITION 		= MakePoint(452, 361 - 12);
    POP_DAILYBONUS_FACEBOOK_FRIEND_PART_TWO_LABEL_POSITION 		= MakePoint(452, 361 + 12);
    POP_DAILYBONUS_LEVEL_PART_ONE_LABEL_POSITION                = MakePoint(210, 538 - 12);
    POP_DAILYBONUS_LEVEL_PART_TWO_LABEL_POSITION                = MakePoint(210, 538 + 12);
    POP_DAILYBONUS_VIP_LABEL_POSITION                           = MakePoint(462, 538);
    POP_DAILYBONUS_TOTAL_BONUS_TEXT_LABEL_POSITION              = MakePoint(147, 728);
    POP_DAILYBONUS_TOTAL_BONUS_VALUE_LABEL_POSITION             = MakePoint(403, 728);
    POP_DAILYBONUS_DAYS_VALUE_LABEL_POSITION                    = MakePoint(112, 368);
    
    POP_DAILYBONUS_DAYS_LABEL_DIMENSION                         = CCSizeMake(91, 61);
    POP_DAILYBONUS_VIP_LABEL_DIMENSION                          = CCSizeMake(91, 44);
    
    //profile popup
    POP_PROFILE_AVARTAR_MENUITEM_POSITION               = MakePoint(148, 911);
    POP_PROFILE_VIP_CLUB_MENUITEM_POSITION              = MakePoint(406, 911);
    POP_PROFILE_LOGOUT_MENUITEM_POSITION                = MakePoint(432, 264);
    
    POP_PROFILE_CIRCLE_AVATAR_SPRITE_POSITION           = MakePoint(278, 272);
    
    //left
    POP_PROFILE_BEST_HAND_SPRITE_POSITION               = MakePoint(47, 694 - 0*40);
    POP_PROFILE_WIN_RATIO_SPRITE_POSITION               = MakePoint(47, 694 - 1*40);
    POP_PROFILE_BIGGEST_WIN_SPRITE_POSITION             = MakePoint(47, 694 - 2*40);
    POP_PROFILE_HANDS_WON_SPRITE_POSITION               = MakePoint(47, 694 - 3*40);
    POP_PROFILE_HANDS_PLAYED_SPRITE_POSITION            = MakePoint(47, 694 - 4*40);
    
    POP_PROFILE_GENDER_ICON_SPRITE_POSITION             = MakePoint(72 + 0*242, 378 + 0*48);
    POP_PROFILE_LOCATION_ICON_SPRITE_POSITION           = MakePoint(72 + 0*242, 378 + 1*48);
    POP_PROFILE_LEVEL_ICON_SPRITE_POSITION              = MakePoint(72 + 1*242, 378 + 1*48);
    POP_PROFILE_CHIP_ICON_SPRITE_POSITION               = MakePoint(72 + 1*242, 378 + 0*48);
    
    POP_PROFILE_NICKNAME_LABEL_POSITION                 = MakePoint(72 + 0*242 + 23, 378 + 0*48);
    POP_PROFILE_LOCATION_LABEL_POSITION                 = MakePoint(72 + 0*242 + 23, 378 + 1*48);
    POP_PROFILE_CHIPS_LABEL_POSITION                    = MakePoint(72 + 1*242 + 23, 378 + 0*48);
    POP_PROFILE_LEVEL_LABEL_POSITION                    = MakePoint(72 + 1*242 + 23, 378 + 1*48);
    
    POP_PROFILE_WIN_RATIO_LABEL_POSITION                = MakePoint(47 + 450, 694 - 1*40);
    POP_PROFILE_BIGGEST_WIN_LABEL_POSITION              = MakePoint(47 + 450, 694 - 2*40);
    POP_PROFILE_HANDS_WON_LABEL_POSITION                = MakePoint(47 + 450, 694 - 3*40);
    POP_PROFILE_HANDS_PLAYED_LABEL_POSITION             = MakePoint(47 + 450, 694 - 4*40);
    
    POP_PROFILE_CARDS_POSTIONS[0]                       = MakePoint(90 + 0*94, 787);
    POP_PROFILE_CARDS_POSTIONS[1]                       = MakePoint(90 + 1*94, 787);
    POP_PROFILE_CARDS_POSTIONS[2]                       = MakePoint(90 + 2*94, 787);
    POP_PROFILE_CARDS_POSTIONS[3]                       = MakePoint(90 + 3*94, 787);
    POP_PROFILE_CARDS_POSTIONS[4]                       = MakePoint(90 + 4*94, 787);
    
    POP_PROFILE_CARD_SCALE                              = 0.75f;
    
    //vipclub popup
    POP_VIPCLUB_HEADER_SPRITE_POSITION                      = POP_COMMON_HEADER_POSITION;
    
    POP_VIPCLUB_BRONZE_TEXT_SPRITE_POSITION                 = MakePoint(152, 450 + 0*99); //left
    POP_VIPCLUB_SLIVER_TEXT_SPRITE_POSITION                 = MakePoint(152, 450 + 1*99); //left
    POP_VIPCLUB_GOLD_TEXT_SPRITE_POSITION                   = MakePoint(152, 450 + 2*99); //left
    POP_VIPCLUB_PLATINUM_TEXT_SPRITE_POSITION               = MakePoint(152, 450 + 3*99); //left
    POP_VIPCLUB_DIAMOND_TEXT_SPRITE_POSITION                = MakePoint(152, 450 + 4*99); //left
    
    POP_VIPCLUB_BRONZE_CARD_SPRITE_POSITION                 = MakePoint(95, 464 + 0*99);
    POP_VIPCLUB_SLIVER_CARD_SPRITE_POSITION                 = MakePoint(95, 464 + 1*99);
    POP_VIPCLUB_GOLD_CARD_SPRITE_POSITION                   = MakePoint(95, 464 + 2*99);
    POP_VIPCLUB_PLATINUM_CARD_SPRITE_POSITION               = MakePoint(95, 464 + 3*99);
    POP_VIPCLUB_DIAMOND_CARD_SPRITE_POSITION                = MakePoint(95, 464 + 4*99);
    
    POP_VIPCLUB_MEMBER_CARD_SPRITE_POSITION                 = MakePoint(114, 346);
    POP_VIPCLUB_BIG_BRONZE_CARD_SPRITE_POSITION             = MakePoint(114, 346);
    POP_VIPCLUB_BIG_GOLD_CARD_SPRITE_POSITION               = MakePoint(114, 346);
    POP_VIPCLUB_BIG_SLIVER_CARD_SPRITE_POSITION             = MakePoint(114, 346);
    POP_VIPCLUB_BIG_PLATINUM_CARD_SPRITE_POSITION			= MakePoint(114, 346);
    POP_VIPCLUB_BIG_DIAMOND_CARD_SPRITE_POSITION			= MakePoint(114, 346);
    
    POP_VIPCLUB_LINES_SPRITE_POSITION                       = MakePoint(275, 607);
    
    POP_VIPCLUB_PROGRESS_LEVEL_SPRITE_POSITION              = MakePoint(358, 322);
    POP_VIPCLUB_PROGRESS_LEVEL_BACKGROUND_SPRITE_POSITION	= MakePoint(358, 322);
    
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[0]                = MakePoint(492, 455 + 0*99);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[1]                = MakePoint(492, 455 + 1*99);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[2]                = MakePoint(492, 455 + 2*99);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[3]                = MakePoint(492, 455 + 3*99);
    POP_VIPCLUB_CHECKED_SPRITES_POSITIONS[4]                = MakePoint(492, 455 + 4*99);
    
    POP_VIPCLUB_NOTE_MORE_POINTS_LABEL_POSITION          = MakePoint(202, 362);
    POP_VIPCLUB_NOTE_MULTIPLE_LABEL_POSITION             = MakePoint(202, 386);
    
    POP_VIPCLUB_BRONZE_VIP_POINT_TEXT_LABEL_POSITION 	= MakePoint(196, 479 + 0*99);
    POP_VIPCLUB_BRONZE_VIP_POINT_VALUE_LABEL_POSITION 	= MakePoint(243 + 3, 479 + 0*99); //left
    POP_VIPCLUB_BRONZE_PACKAGES_TEXT_LABEL_POSITION 	= MakePoint(361 + 20, 479 + 0*99);
    POP_VIPCLUB_BRONZE_PACKAGES_VALUE_LABEL_POSITION 	= MakePoint(418 + 23, 479 + 0*99);
    
    POP_VIPCLUB_SLIVER_VIP_POINT_TEXT_LABEL_POSITION 	= MakePoint(196, 479 + 1*99);
    POP_VIPCLUB_SLIVER_VIP_POINT_VALUE_LABEL_POSITION 	= MakePoint(243 + 3, 479 + 1*99); //left
    POP_VIPCLUB_SLIVER_PACKAGES_TEXT_LABEL_POSITION 	= MakePoint(361 + 20, 479 + 1*99);
    POP_VIPCLUB_SLIVER_PACKAGES_VALUE_LABEL_POSITION 	= MakePoint(418 + 23, 479 + 1*99);
    
    POP_VIPCLUB_GOLD_VIP_POINT_TEXT_LABEL_POSITION 		= MakePoint(196, 479 + 2*99);
    POP_VIPCLUB_GOLD_VIP_POINT_VALUE_LABEL_POSITION 	= MakePoint(243 + 3, 479 + 2*99); //left
    POP_VIPCLUB_GOLD_PACKAGES_TEXT_LABEL_POSITION 		= MakePoint(361 + 20, 479 + 2*99);
    POP_VIPCLUB_GOLD_PACKAGES_VALUE_LABEL_POSITION 		= MakePoint(418 + 23, 479 + 2*99);
    
    POP_VIPCLUB_PLATINUM_VIP_POINT_TEXT_LABEL_POSITION 	= MakePoint(196, 479 + 3*99);
    POP_VIPCLUB_PLATINUM_VIP_POINT_VALUE_LABEL_POSITION = MakePoint(243 + 3, 479 + 3*99); //left
    POP_VIPCLUB_PLATINUM_PACKAGES_TEXT_LABEL_POSITION 	= MakePoint(361 + 20, 479 + 3*99);
    POP_VIPCLUB_PLATINUM_PACKAGES_VALUE_LABEL_POSITION 	= MakePoint(418 + 23, 479 + 3*99);
    
    POP_VIPCLUB_DIAMOND_VIP_POINT_TEXT_LABEL_POSITION 	= MakePoint(196, 479 + 4*99);
    POP_VIPCLUB_DIAMOND_VIP_POINT_VALUE_LABEL_POSITION 	= MakePoint(243 + 3, 479 + 4*99); //left
    POP_VIPCLUB_DIAMOND_PACKAGES_TEXT_LABEL_POSITION 	= MakePoint(361 + 20, 479 + 4*99);
    POP_VIPCLUB_DIAMOND_PACKAGES_VALUE_LABEL_POSITION 	= MakePoint(418 + 23, 479 + 4*99);
    
    //shopping popup
    POP_SHOP_PACKET_NAME_LABEL_POSITION                 = MakePoint(119, 831);
    POP_SHOP_CHIP_AMOUNT_LABEL_POSITION                 = MakePoint(30 + 15, 961); //left
    POP_SHOP_VIP_POINT_LABEL_POSITION                   = MakePoint(30 + 15, 988); //left
    
    POP_SHOP_PRICE_MENUITEM_POSITION                    = MakePoint(138, 1001);
    
    POP_SHOP_MAIN_ICON_SPRITE_POSITION                  = MakePoint(119, 902);
    POP_SHOP_CHIP_ICON_SPRITE_POSITION                  = MakePoint(28, 961);
    POP_SHOP_STAR_ICON_SPRITE_POSITION                  = MakePoint(28, 988);
    
    POP_SHOP_PRODUCT_MENUITEMS_POSITIONS[0]             = CCPoint(152, 112.5f);
    POP_SHOP_PRODUCT_MENUITEMS_POSITIONS[1]             = CCPoint(401, 112.5f);
    
    POP_SHOP_TABLEVIEW_POSITION                         = MakePoint(4, 889); //left-down
    
    POP_SHOP_MENU_BOUNDINGBOX                           = CCRect(0, 0, 550, 800);
    
    POP_SHOP_TABLEVIEW_CELL_SIZE                        = CCSizeMake(515, 225);
    POP_SHOP_TABLEVIEW_SIZE                             = CCSizeMake(515, 583);
    
    /**
     * LevelupPopupView  position init
     * by apple
     */
	POP_LEVELUP_CIRCLE_CONTAINER_1_SPRITE_POSITION  = MakePoint(252, 742);
	POP_LEVELUP_CIRCLE_CONTAINER_2_SPRITE_POSITION  = MakePoint(252, 742);
	POP_LEVELUP_CONGRATULATION_LABEL_POSITION 		= MakePoint(252, 883);
	POP_LEVELUP_LEVEL_LABEL_POSITION                = MakePoint(252, 742);
	POP_LEVELUP_RIBBON_SPRITE_POSITION              = MakePoint(252, 821);
	POP_LEVELUP_SHINE_CIRCLE_SPRITE_POSITION 		= MakePoint(252, 742);
	POP_LEVELUP_STAR1_SPRITE_POSITION               = MakePoint(99, 640);
	POP_LEVELUP_STAR2_SPRITE_POSITION               = MakePoint(229, 570);
	POP_LEVELUP_STAR3_SPRITE_POSITION               = MakePoint(396, 608);
	POP_LEVELUP_STAR_SHINE_SPRITE_POSITION          = MakePoint(252, 715);
    
	POP_LEVELUP_OK_MENUITEM_POSITION                = MakePoint(165, 953);
	POP_LEVELUP_SHARE_MENUITEM_POSITION             = MakePoint(334, 953);
    
    /**
     * JackpotPopupView position init
     * by Dung Ta Van
     */
	POP_JACKPOT_CHIPS_SPRITE_POSITION               = MakePoint(92, 858);
	POP_JACKPOT_JACKPOT_TEXT_SPRITE_POSITION 		= MakePoint(252, 713);
	POP_JACKPOT_REWARD_ICON_SPRITE_POSITION 		= MakePoint(252, 796);
	POP_JACKPOT_SHINE_CIRCLE_SPRITE_POSITION 		= POP_LEVELUP_SHINE_CIRCLE_SPRITE_POSITION;
	POP_JACKPOT_STAR_SHINE_SPRITE_POSITION          = MakePoint(252, 667);
    POP_JACKPOT_CHIPS_LABEL_POSITION                = MakePoint(156, 872);
    
    POP_JACKPOT_STARS_POSITIONS[0]                  = MakePoint(173, 624);
    POP_JACKPOT_STARS_POSITIONS[1]                  = MakePoint(333, 592);
    POP_JACKPOT_STARS_POSITIONS[2]                  = MakePoint(61, 765);
    POP_JACKPOT_STARS_POSITIONS[3]                  = MakePoint(425, 781);
    
	POP_JACKPOT_OK_MENUITEM_POSITION                = POP_LEVELUP_OK_MENUITEM_POSITION;
	POP_JACKPOT_SHARE_MENUITEM_POSITION             = POP_LEVELUP_SHARE_MENUITEM_POSITION;
    
    /**
     * VipUpgradePopupView  position init
     * by Dung Ta Van
     */
	POP_VIP_UPGRADE_CHIPS_LABEL_POSITION            = MakePoint(101, 881);
	POP_VIP_UPGRADE_INAPP_LABEL_POSITION            = MakePoint(289, 881);
	POP_VIP_UPGRADE_MEMBER_CARD_SPRITE_POSITION     = MakePoint(252, 784);
	POP_VIP_UPGRADE_REWARD_ICON_SPRITE_POSITION     = MakePoint(64, 881);
	POP_VIP_UPGRADE_SHINE_SPRITE_POSITION           = POP_LEVELUP_SHINE_CIRCLE_SPRITE_POSITION;
	POP_VIP_UPGRADE_STAR1_SPRITE_POSITION           = MakePoint(170, 744);
	POP_VIP_UPGRADE_STAR2_SPRITE_POSITION           = MakePoint(332, 821);
	POP_VIP_UPGRADE_VIP_LEVEL_RIBBON_SPRITE_POSITION    = MakePoint(252, 712);
    
	POP_VIP_UPGRADE_OK_MENUITEM_POSITION            = POP_LEVELUP_OK_MENUITEM_POSITION;
	POP_VIP_UPGRADE_SHARE_MENUITEM_POSITION 		= POP_LEVELUP_SHARE_MENUITEM_POSITION;
    
    // settings popup
    POP_SETTING_SOUND_EFFECT_LABEL_POSITION             = MakePoint(54, 348); //left
    POP_SETTING_MUSIC_LABEL_POSITION                    = MakePoint(54, 348 + 1*84); //left
    POP_SETTING_LEFT_HAND_LABEL_POSITION                = MakePoint(54, 348 + 2*84); //left
    POP_SETTING_DOUBLE_OR_NOTHING_LABEL_POSITION        = MakePoint(54, 348 + 3*84); //left
    
    POP_SETTING_SOUND_EFFECT_MENUITEM_POSITION          = MakePoint(434, 348);
    POP_SETTING_MUSIC_MENUITEM_POSITION                 = MakePoint(434, 348 + 1*84);
    POP_SETTING_LEFT_HAND_MENUITEM_POSITION             = MakePoint(434, 348 + 2*84);
    POP_SETTING_DOUBLE_OR_NOTHING_MENUITEM_POSITION     = MakePoint(434, 348 + 3*84);
    
    POP_SETTING_RATE_US_MENUITEM_POSITION               = MakePoint(151, 700);
    POP_SETTING_FEEDBACK_MENUITEM_POSITION              = MakePoint(404, 700);
    POP_SETTING_LIKE_PAGE_MENUITEM_POSITION             = MakePoint(151, 800);;
    POP_SETTING_INVITE_FRIEND_MENUITEM_POSITION         = MakePoint(404, 800);;
    
    POP_SETTING_PRIVATE_POLICY_MENUITEM_POSITION        = MakePoint(148, 911);
    POP_SETTING_TERM_OF_SERVICES_MENUITEM_POSITION      = MakePoint(408, 911);
    
    // Paytable
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[0]           = MakePoint(154, 524 + 0*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[1]           = MakePoint(154, 524 + 1*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[2]           = MakePoint(154, 524 + 2*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[3]           = MakePoint(154, 524 + 3*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[4]           = MakePoint(154, 524 + 4*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[5]           = MakePoint(154, 524 + 5*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[6]           = MakePoint(402, 524 + 0*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[7]           = MakePoint(402, 524 + 1*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[8]           = MakePoint(402, 524 + 2*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[9]           = MakePoint(402, 524 + 3*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[10]          = MakePoint(402, 524 + 4*70);
    POP_PAYTABLE_HAND_MENUITEMS_POSITIONS[11]          = MakePoint(402, 524 + 5*70);
    
    POP_PAYTABLE_CARDS_POSTIONS[0]                      = MakePoint(90 + 0*94, 408);
    POP_PAYTABLE_CARDS_POSTIONS[1]                      = MakePoint(90 + 1*94, 408);
    POP_PAYTABLE_CARDS_POSTIONS[2]                      = MakePoint(90 + 2*94, 408);
    POP_PAYTABLE_CARDS_POSTIONS[3]                      = MakePoint(90 + 3*94, 408);
    POP_PAYTABLE_CARDS_POSTIONS[4]                      = MakePoint(90 + 4*94, 408);
    
    POP_PAYTABLE_CARD_VIEW_CONTAINER_POSITION           = MakePoint(278, 408);
    
    POP_PAYTABLE_PAYOUT_SPRITE_POSITION                 = MakePoint(210, 331);
    POP_PAYTABLE_PAYOUT_LABEL_POSITION                  = MakePoint(273, 331);

    //
    CMM_FONT_SIZE_0                                     = 20.0f;
    CMM_FONT_SIZE_1                                     = 26.0f;
    CMM_FONT_SIZE_2                                     = 28.0f;
    CMM_FONT_SIZE_3                                     = 30.0f;
    CMM_FONT_SIZE_4                                     = 34.0f;
    CMM_FONT_SIZE_5                                     = 38.0f;
    CMM_FONT_SIZE_6                                     = 80.0f;
    
    CMM_CARD_FONT_SIZE                                  = 34.0f;
    
    
    CMM_ICON_FB_SIZE                                    = CCSizeMake(160, 160);
    CMM_ICON_LOBBY_SIZE                                 = CCSizeMake(85, 85);
    CMM_ICON_PROFILE_SIZE                               = CCSizeMake(93, 93);
    CMM_ICON_AVATAR_SIZE                                = CCSizeMake(103, 103);
    
    // Login scene
    LOG_FB_BUTTON_POSITION                              = MakePoint(384, 714);
    LOG_GUEST_BUTTON_POSITION                           = MakePoint(384, 824);
    LOG_STATUS_LABEL_POSITION                           = MakePoint(384, 944);
    
    // Lobby scene
    LBB_PAGE_INDICATOR_ON_SELECT_GAME_POSITION          = MakePoint(384, 915);
    LBB_SELECT_GAME_SCROLL_VIEW_BOUNDING_BOX            = CCRect(0, VisibleRect::top().y - 936,
                                                                 768, 560);
    
    LBB_NUMBER_OF_MENU_ITEM_ON_SELECT_GAME              = 3;
    
    LBB_FOOTER_BG_POSITION                              = MakePoint(384, 968);
    LBB_FOOTER_AVATAR_POSITION                          = MakePoint(52, 974);
    LBB_FOOTER_LEVEL_BAR_POSITION                       = MakePoint(464, 997);
    LBB_FOOTER_LEVEL_LABEL_POSITION                     = MakePoint(647, 997);
    LBB_FOOTER_FULLNAME_POSITION                        = MakePoint(111, 997);
    
    LBB_SELECT_GAME_HEADER_POSITION                     = MakePoint(384, 142);
    
    LBB_GAME_LIST_POSITION[0]                           = MakePoint(384, 475);
    LBB_GAME_LIST_POSITION[1]                           = MakePoint(384, 640);
    LBB_GAME_LIST_POSITION[2]                           = MakePoint(384, 805);
    
    LBB_HEADER_BG_POSITION                              = MakePoint(384, 142);
    LBB_HEADER_SETTINGS_BUTTON_POSITION                 = MakePoint(46, 46);
    
    LBB_MIDDLE_BG_POSITION                              = MakePoint(384, 314);
    LBB_MIDDLE_CHIP_BG_POSITION                         = MakePoint(178, 316);
    LBB_MIDDLE_CHIP_ICON_POSITION                       = MakePoint(76, 316);
    LBB_MIDDLE_CHIP_LABEL_POSITION                      = MakePoint(117, 316);
    LBB_MIDDLE_CHIP_BUTTON_POSITION                     = MakePoint(292, 316);
    LBB_MIDDLE_BONUS_BG_POSITION                        = MakePoint(632, 316);
    LBB_MIDDLE_BONUS_LABEL_POSITION                     = MakePoint(593, 316);
    LBB_MIDDLE_BONUS_BUTTON_POSITION                    = MakePoint(537, 314);
    
    LBB_STACKS_IN_MENU_ITEM_POSITION                    = MakePoint(376, 982);
    LBB_JACKPOT_SPRITE_IN_MENU_ITEM_POSITION            = MakePoint(417, 913);
    LBB_JACKPOT_LABEL_IN_MENU_ITEM_POSITION             = MakePoint(376, 941);
    LBB_LOCK_SPRITE_IN_MENU_ITEM_POSITION               = MakePoint(350, 949);
    LBB_LOCK_LABEL_IN_MENU_ITEM_POSITION                = MakePoint(376, 949);

    // main game scene
    MAIN_HEADER_BG_POSITION                             = MakePoint(384, 58);
    MAIN_HEADER_LEVEL_POSITION                          = MakePoint(112, 68);
    MAIN_HEADER_BOARD_POSITION                          = MakePoint(456, 56);
    
    MAIN_EXIT_BUTTON_POSITION                           = MakePoint(728, 27);
    MAIN_SETTINGS_BUTTON_POSITION                       = MakePoint(725, 82);
    
    MAIN_HAND_OF_JACKPOT_LABEL_POSTION                  = MakePoint(234, 46); //left
    MAIN_JACKPOT_STRING_LABEL_POSITION                  = MakePoint(525, 30); //left
    MAIN_JACKPOT_VALUE_LABEL_POSITION                   = MakePoint(525, 60); //left
    MAIN_TOTAL_USER_LABEL_POSITION                      = CCPoint(3, 2);
    MAIN_LEVEL_LABEL_POSITION                           = MakePoint(112, 39);
    
    MAIN_PAYTABLE_CELL_NAME_DELTA                       = 150;

    // Main game midle
    MAIN_CHIP_INFO_BG_POSITION                  = MakePoint(384, 512);
    MAIN_TOTAL_CHIP_BG_POSITION                 = MakePoint(172, 508);
    MAIN_TOTAL_CHIP_ICON_POSITION               = MakePoint(70, 508);
    MAIN_ADD_CHIP_BUTTON_POSITION               = MakePoint(286, 508);
    MAIN_TOTAL_CHIPS_LABEL_POSITION             = MakePoint(112, 508);
    MAIN_TOTAL_BET_CHIP_BUTTON_POSITION         = MakePoint(514, 508);
    MAIN_BET_CHIP_BG_POSITION                   = MakePoint(614, 508);
    MAIN_BET_CHIPS_LABEL_POSITION               = MakePoint(603, 508);
    MAIN_WON_CHIPS_LABEL_POSITION               = MakePoint(605, 508);
    MAIN_BET_CHIPS_SPRITE_POSITION              = MakePoint(554, 508);
    MAIN_WON_CHIPS_SPRITE_POSITION              = MakePoint(554, 508);
    
    // Main game footer
    MAIN_FUNCTION_BG_POSITION                   = MakePoint(384, 956);
    MAIN_FUNCTION_BUTTON_BG_POSITION            = MakePoint(643, 946);
    
    MAIN_DEAL_BUTTON_POSITION                   = MakePoint(653, 954);
    MAIN_MAX_BET_BUTTON_POSITION                = MakePoint(380, 974);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[0]          = MakePoint(66, 966);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[1]          = MakePoint(170, 970);
    MAIN_BET_CHIP_BUTTONS_POSITIONS[2]          = MakePoint(274, 973);
    MAIN_DON_YES_BUTTON_POSITION                = MakePoint(614, 962);
    MAIN_DON_NO_BUTTON_POSITION                 = MakePoint(710, 954);
    MAIN_DON_LABEL_POSITION                     = MakePoint(30, 966);
    MAIN_DON_MOVING_DISTANCE                    = 400;
    
    MAIN_CARDS_POSITIONS[0]                     = MakePoint(112 + 0*136, 738);
    MAIN_CARDS_POSITIONS[1]                     = MakePoint(112 + 1*136, 738);
    MAIN_CARDS_POSITIONS[2]                     = MakePoint(112 + 2*136, 738);
    MAIN_CARDS_POSITIONS[3]                     = MakePoint(112 + 3*136, 738);
    MAIN_CARDS_POSITIONS[4]                     = MakePoint(112 + 4*136, 738);
    
    MAIN_HELDINGS_POSITIONS[0]                  = MakePoint(136 + 0*136, 695);
    MAIN_HELDINGS_POSITIONS[1]                  = MakePoint(136 + 1*136, 695);
    MAIN_HELDINGS_POSITIONS[2]                  = MakePoint(136 + 2*136, 695);
    MAIN_HELDINGS_POSITIONS[3]                  = MakePoint(136 + 3*136, 695);
    MAIN_HELDINGS_POSITIONS[4]                  = MakePoint(136 + 4*136, 695);
    
    // paytable cells
    MAIN_PAYTABLE_BG_POSITION                   = MakePoint(384, 281);
    MAIN_PAYTABLE_CELL_POSITIONS[0]             = MakePoint(190, 172 + 0*57);
    MAIN_PAYTABLE_CELL_POSITIONS[1]             = MakePoint(190, 172 + 1*57);
    MAIN_PAYTABLE_CELL_POSITIONS[2]             = MakePoint(190, 172 + 2*57);
    MAIN_PAYTABLE_CELL_POSITIONS[3]             = MakePoint(190, 172 + 3*57);
    MAIN_PAYTABLE_CELL_POSITIONS[4]             = MakePoint(190, 172 + 4*57);
    
    MAIN_PAYTABLE_CELL_POSITIONS[5]             = MakePoint(570, 172 + 0*57);
    MAIN_PAYTABLE_CELL_POSITIONS[6]             = MakePoint(570, 172 + 1*57);
    MAIN_PAYTABLE_CELL_POSITIONS[7]             = MakePoint(570, 172 + 2*57);
    MAIN_PAYTABLE_CELL_POSITIONS[8]             = MakePoint(570, 172 + 3*57);
    MAIN_PAYTABLE_CELL_POSITIONS[9]             = MakePoint(570, 172 + 4*57);
    
    //
    // Loading scene
    //
    LOADING_PROGRESS_BAR_POSITION               = MakePoint(384, 882);

    // card view
    CARD_RANK_LABEL_POSITION                            = MakePoint(19,887);
    CARD_SUIT_SMALL_ICON_POSITION                       = MakePoint(19,914);
    CARD_SUIT_ICON_POSITION                             = MakePoint(60,964);
    CARD_JQK_ICON_POSITION                              = MakePoint(60,964);
    CARD_JQK_SUIT_ICON_POSITION                         = MakePoint(12,410);
    CARD_WILD_ICON_POSITION                             = MakePoint(60,964);
    CARD_JOKER_ICON_POSITION                            = MakePoint(60,964);
    CARD_JOKER_LABEL_POSITION                           = MakePoint(60,888);

    // Notification popup
    NTF_TITLE_TEXT_POSITION                             = MakePoint(252, 782);
    NTF_MESSAGE_TEXT_POSITION                           = MakePoint(252, 872);
    NTF_BUTTON_CENTER_POSITION                          = MakePoint(252, 955);
    NTF_BUTTON_LEFT_POSITION                            = MakePoint(139, 955);
    NTF_BUTTON_RIGHT_POSITION                           = MakePoint(363, 955);
    NTF_MESSAGE_SIZE                                    = CCSizeMake(407, 85);


	

	// LeaderboardPopupView position initializing(ipadhd)
	// by apple Wed Aug 13 16:22:33 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(ipadhd)
	// by apple Wed Aug 13 16:22:34 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(ipadhd)
	// by apple Wed Aug 13 16:22:36 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(ipadhd)
	// by apple Wed Aug 13 16:22:38 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(ipadhd)
	// by apple Wed Aug 13 16:22:40 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	//don't modify or delete this line(ipadhd)
    
    

	// LeaderboardPopupView position initializing(iphone)
	// by apple Wed Aug 13 16:22:21 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(iphone)
	// by apple Wed Aug 13 16:22:27 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	

	// LeaderboardPopupView position initializing(iphone)
	// by apple Wed Aug 13 16:22:30 GMT+07:00 2014
	POP_LEADERBOARD_BG_NUMBER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_BG_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_LEADERBOARD_BANNER_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_1_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_2_SPRITE_POSITION 		= MakePointCommon(0, 0);
	POP_LEADERBOARD_NUMBER_3_SPRITE_POSITION 		= MakePointCommon(0, 0);

	//don't modify or delete this line(iphone)
    
}

void GameParams::initParams() {
    
}
