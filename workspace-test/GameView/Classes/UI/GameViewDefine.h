//
//  GameViewDefine.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/15/14.
//
//

#ifndef DragonVideoPoker_GameViewDefine_h
#define DragonVideoPoker_GameViewDefine_h

#define NUMBER_DISPLAY_UPDATE_RATE                  4
#define JACKPOT_DISPLAY_UPDATE_RATE                 20

#define DELAY_POST_FINISH_MAIN_GAME_EVENT           2.0f
#define DELAY_POST_FINISH_DON_GAME_EVENT            2.0f

#define NOTIFICATION_BETTED_CHIP_STOP_MOVING        "BETTED_CHIP_STOP_MOVING"
#define NOTIFICATION_BEETED_CHIP_START_MOVING       "BETTED_CHIP_START_MOVING"

#define NOTIFICATION_DISABLE_CHIP_BUTTONS           "DISABLE_CHIP_BUTTONS"
#define NOTIFICATION_ENABLE_CHIP_BUTTONS            "ENABLE_CHIP_BUTTONS"

#define NOTIFICATION_DISABLE_CANCEL_BET_BUTTON      "DISABLE_CANCEL_BET_BUTTON"
#define NOTIFICATION_ENABLE_CANCEL_BET_BUTTON       "ENABLE_CANCEL_BET_BUTTON"

#define NOTIFICATION_MAIN_GAME_FINISH               "MAIN_GAME_FINISH"
#define NOTIFICATION_DON_GAME_FINISH                "DON_GAME_FINISH"

#define NOTIFICATION_SWITCH_HAND                    "SWITCH_HAND"

#define NOTIFICATION_CANNOT_INVITE_FRIEND           "CANNOT_INVITE_FRIEND"


#define TAG_CHIP_NOT_MOVING                         0
#define TAG_CHIP_MOVING_FROM_BUTTONS_TO_TOTAL_BET   1
#define TAG_CHIP_MOVING_FROM_BET_TO_TOTAL_CHIP      2
#define TAG_CHIP_MOVING_FROM_WON_TO_TOTAL_CHIP      3


#define DON_MOVING_INTERVAL                         0.2f


typedef enum GAME_VIEW_STATE {
    tdgGameViewIdle                                 = 0,
    
    tdgGameViewUpdateBetChip                        = 1,
    tdgGameViewUpdateCancelBetChip                  = 2,
    tdgGameViewUpdateBetMaxChip                     = 3,
    tdgGameViewUpdateCollectWonChips                = 4,
    tdgGameViewUpdateRebetChips                     = 5,
    tdgGameViewUpdateMainGameFinish                 = 6,
    tdgGameViewUpdatePlayDonGame                    = 7,
    tdgGameViewUpdateFinishDonGame                  = 8,
    
    tdgGameViewUpdateJackpot                        = 20,
    tdgGameViewUpdateLevel                          = 21,
    tdgGameViewUpdateLevelExperience                = 22,
    
    tdgGameViewUpdateDealButton                     = 30,
    tdgGameViewUpdateGotDealCards                   = 31,
    tdgGameViewUpdateDealCardSelected               = 32,
    tdgGameViewUpdateDrawButton                     = 33,
    tdgGameViewUpdateGotDrawCards                   = 34,
    tdgGameViewUpdateRemoveHighlightPayout          = 35,
    
    tdgGameViewUpdateGotDonDealerCard               = 40,
    tdgGameViewUpdateSelectDonCard                  = 41,
    tdgGameViewUpdateGotDonCards                    = 42,
    tdgGameViewUpdateDonDealButton                  = 43,

    tdgGameViewUpdatePrepareNewGame                 = 1000,
    
} Game_View_State;

typedef struct gameViewState {
    long state;                     // state to draw UI
    bool isQuickAction;             // is need to draw quickly
} GameViewState;

#endif
