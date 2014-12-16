//
//  TdgServerDefine.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef DragonVideoPoker_TdgServerDefine_h
#define DragonVideoPoker_TdgServerDefine_h


#define GAME_LANGUAGE                           0   // 0 - En; 1 - Vi

#ifdef CC_TARGET_OS_IPHONE
#define DISTRIBUTOR_ID                          2       // TDG
#else
#define DISTRIBUTOR_ID                          1000   // TDG
#endif

#define GAME_LOBBY_NAME                         "VPKLobby"

#define FACEBOOK_PASSWORD                       "Xl5EZW9WaSYmS2VyUG8="
#define GUESS_PASSWORD                          "Xl5EZW9WaSYmS2VyUG9HdWVzdA=="
#define PASSWORD_TAIL                           "WkdGeVpUOD0="

#define BASE_EVENT                              boost::shared_ptr<BaseEvent>
#define PTR_ELD                                 boost::shared_ptr<EventListenerDelegate>
#define ELD                                     EventListenerDelegate

#define NUMBER_OF_GAMES                         8

// Notification define
#define NOTIFICATION_GOT_DEAL_CARDS                 "GOT_DEAL_CARDS"
#define NOTIFICATION_GOT_DRAW_CARDS                 "GOT_DRAW_CARDS"

#define NOTIFICATION_GOT_DON_DEALER_CARD            "GOT_DON_DEALER_CARD"
#define NOTIFICATION_GOT_DON_CARDS                  "GOT_DON_CARDS"

#define NOTIFICATION_GOT_JACKPOT_UPDATE             "GOT_JACKPOT_UPDATE"
#define NOTIFICATION_GOT_LEVEL_UPDATE               "GOT_LEVEL_UPDATE"
#define NOTIFICATION_GOT_LEVEL_EX_UPDATE            "GOT_LEVEL_EX_UPDATE"

#define NOTIFICATION_GOT_CLAIM_HOURLY_BONUS         "GOT_CLAIM_HOURLY_BONUS"
#define NOTIFICATION_GOT_CLAIM_DAILY_BONUS          "GOT_CLAIM_DAILY_BONUS"

#define NOTIFICATION_GOT_LOST_SERVER_CONNECTION     "GOT_LOST_SERVER_CONNECTION"
#define NOTIFICATION_GOT_LOGOUT                     "GOT_LOGOUT"
#define NOTIFICATION_GOT_CHECKING_INTERNET_FAILED   "GOT_CHECKING_INTERNET_FAILED"
#define NOTIFICATION_GOT_MUST_UPDATE_NEWEST_VERSION "GOT_MUST_UPDATE_NEWEST_VERSION"
#define NOTIFICATION_GOT_IAP_SUCCESS                "GOT_IAP_SUCCESS"
#define NOTIFICATION_GOT_IAP_FAILED                 "GOT_IAP_FAILED"
#define NOTIFICATION_GOT_IAP_FINISHED               "GOT_IAP_FINISHED"
#define NOTIFICATION_GOT_CONNECT_FAILED_TO_SERVER   "GOT_CONNECT_FAILED_TO_SERVER"
#define NOTIFICATION_GOT_FIRST_JOIN_GAME            "GOT_FIRST_JOIN_GAME"

#define NOTIFICATION_GOT_VIP_UPGRADE                "GOT_VIP_UPGRADE"
#define NOTIFICATION_GOT_LEVEL_UP                   "GOT_LEVEL_UP"
#define NOTIFICATION_GOT_JACKPOT                    "GOT_JACKPOT"

#define NOTIFICATION_GOT_UPDATE_AVATAR              "GOT_UPDATE_AVATAR"

#define NOTIFICATION_GET_LEADERBOARD_FINISHED       "GOT_LEADERBOARD_FINISHED"


#define encodeParam(__X__) (__X__ * 5807 + 43201)
#define decodeParam(__X__) (((__X__ - 43201) % 5807) == 0 ? ((__X__ - 43201) / 5807) : 0)

typedef enum NOTIFICATION_POPUP_TYPE {
    kNotificationCommon,
    kNotificationDisconnected,
    kNotificationConnectionLost,
    kNotificationInAppPurchaseFailed,
    kNotificationInAppPurchaseSuccessed,
    kNotificationCheckingInternetFailed,
    kNotificationMustUpdateNewestVersion,
    kNotificationNewVersionAvailable,
    kNotificationConnectFailedToServer,
    kNotificationConfirmQuitGame,
    kNotificationFirstJoinGame,
} Notification_Popup_Type;

typedef enum USER_LOGIN_STATUS {
    kUserLoggingInIDLE,
    kUserLoggingInFacebook,
    kUserConnectingServer,
    kUserLoggingInServer,
    kUserJoiningLobbyRoom,
    kUserJoinedLobbyRoom,
} User_Login_Status;

typedef enum USER_JOINING_STATUS {
    kJoiningLobbyRoom,
    kJoiningGameRoom,
    kJoinedLobbyRoom,
    kJoinedGameRoom,
    kJoinLobbyRoomFailed,
    kJoinGameRoomFailed,
} User_Joining_Status;

typedef enum USER_LOGIN_TYPE {
    kUserLogOut,
    kUserLoginFail,
    kGuestLogin,
    kFacebookLogin,
    kGuestLoggedin,
    kFacebookLoggedin,
} User_Login_Type;

typedef enum PLAYER_TYPE {
    kPlayerTypeZombie,                // not connected -> logout
    kPlayerTypeUser,                  // just in lobby
    kPlayerTypeSpectator,             // in table
    kPlayerTypePlayer,                // in table
} Player_Type;

typedef enum IAP_ITEM {
    kIAPChip1 = 0,
    kIAPChip2 = 1,
    kIAPChip3 = 2,
    kIAPChip4 = 3,
    kIAPChip5 = 4,
    kIAPChip6 = 5,
    kIAPGold1 = 6,
    kIAPGold2 = 7,
    kIAPGold3 = 8,
    kIAPGold4 = 9,
    kIAPGold5 = 10,
    kIAPGold6 = 11,
} IAP_Item;

//
// command define
//
#define EX_REQUEST_COMMAND_SEND_USER_INFO                   "inf"
#define EX_REQUEST_COMMAND_CLAIM_DAILY_BONUS                "dbc"
#define EX_REQUEST_COMMAND_CLAIM_HOURLY_BONUS               "hbc"
#define EX_REQUEST_COMMAND_DEAL_CARDS                       "dec"
#define EX_REQUEST_COMMAND_DRAW_CARDS                       "drc"
#define EX_REQUEST_COMMAND_DON_DEALER_CARD                  "dnc"
#define EX_REQUEST_COMMAND_DON_CARDS                        "sco"
#define EX_REQUEST_COMMAND_PAYTABLE                         "ptc"
#define EX_REQUEST_COMMAND_IN_APP_LIST                      "lcc"
#define EX_REQUEST_COMMAND_IN_APP_VERIFY_RESULT             "iap"
#define EX_REQUEST_COMMAND_UPDATE_AVATAR                    "cac"

//
// params define
//
#define EX_REQUEST_PARAM_USER_INFO                          "uif"
#define EX_REQUEST_PARAM_ROOM_STATIC                        "vs"
#define EX_REQUEST_PARAM_PURCHASE_LIST                      "pl"
#define EX_REQUEST_PARAM_VIP_CARD_LIST                      "vl"
#define EX_REQUEST_PARAM_LEVEL_LIST                         "ll"
#define EX_REQUEST_PARAM_HOURLY_BONUS                       "hli"
#define EX_REQUEST_PARAM_DAILY_BONUS                        "dli"

// user info
#define EX_REQUEST_PARAM_USER_PROFILE_ID                    "pid"
#define EX_REQUEST_PARAM_USER_FIRST_NAME                    "$#f"
#define EX_REQUEST_PARAM_USER_LAST_NAME                     "$#l"
#define EX_REQUEST_PARAM_USER_EMAIL                         "ema"
#define EX_REQUEST_PARAM_USER_SEX                           "$sex"
#define EX_REQUEST_PARAM_USER_FRIENDS                       "fli"
#define EX_REQUEST_PARAM_USER_HOMETOWN                      "hlo"
#define EX_REQUEST_PARAM_USER_LOCATION                      "clo"   // Present location

#define EX_REQUEST_PARAM_USER_GOLD                          "gnu"

#define EX_REQUEST_PARAM_USER_USERID                        "sid"

#define EX_REQUEST_PARAM_USER_DEVICE_TOKEN                  "dvt"

#define EX_REQUEST_PARAM_USER_IS_ONLINE                     "iol"
#define EX_REQUEST_PARAM_USER_FIRST_JOIN_GAME               "ifc"

#define EX_REQUEST_PARAM_USER_LOCATION_DISPLAY              "loc"   // location showed in game


#define EX_REQUEST_PARAM_USER_INTERFACE_LANGUAGE            "ila"
#define EX_REQUEST_PARAM_USER_LEVEL                         "$lid"
#define EX_REQUEST_PARAM_USER_EXPERIENCE                    "uex"
#define EX_REQUEST_PARAM_USER_AVATAR                        "$aid"
#define EX_REQUEST_PARAM_USER_CHIPS                         "cnu"
#define EX_REQUEST_PARAM_USER_VIP_POINT                     "pvk"   // vip point of user

// user statistics
#define EX_REQUEST_PARAM_USER_HANDS_PLAYED                  "hpl"
#define EX_REQUEST_PARAM_USER_HANDS_WON                     "hsw"
#define EX_REQUEST_PARAM_USER_BIGGEST_WIN                   "bgw"
#define EX_REQUEST_PARAM_USER_BEST_HAND                     "bsh"


// vip club
#define EX_REQUEST_PARAM_VIP_CHIPS_REWARD                   "cbn"

#define EX_REQUEST_PARAM_VIP_CARD_TYPE                      "pvc"
#define EX_REQUEST_PARAM_VIP_MULTIPLY                       "pvn" // tinh theo 100%
#define EX_REQUEST_PARAM_VIP_POINT_MAX                      "pvm"
#define EX_REQUEST_PARAM_VIP_UPGRADE_BONUS                  "vpb"

// game info
#define ROOM_PARAM_GAME_1_STATIC                            "vs1"
#define ROOM_PARAM_GAME_2_STATIC                            "vs2"
#define ROOM_PARAM_GAME_3_STATIC                            "vs3"
#define ROOM_PARAM_GAME_4_STATIC                            "vs4"
#define ROOM_PARAM_GAME_5_STATIC                            "vs5"
#define ROOM_PARAM_GAME_6_STATIC                            "vs6"
#define ROOM_PARAM_GAME_7_STATIC                            "vs7"
#define ROOM_PARAM_GAME_8_STATIC                            "vs8"

#define ROOM_PARAM_ROOM_NAME                                "gna"
#define ROOM_PARAM_JACKPOT_HAND                             "jha"
#define ROOM_PARAM_JACKPOT_RESET                            "jre"
#define ROOM_PARAM_JACKPOT_PERCENT                          "jbc"
#define ROOM_PARAM_MIN_STAKES                               "smi"
#define ROOM_PARAM_MAX_STAKES                               "sma"
#define ROOM_PARAM_LEVEL_REQUIRED                           "lre"
#define ROOM_PARAM_BET_CHIP_TYPE                            "cun"

#define ROOM_PARAM_GAME_1_DYNAMIC                           "vd1"
#define ROOM_PARAM_GAME_2_DYNAMIC                           "vd2"
#define ROOM_PARAM_GAME_3_DYNAMIC                           "vd3"
#define ROOM_PARAM_GAME_4_DYNAMIC                           "vd4"
#define ROOM_PARAM_GAME_5_DYNAMIC                           "vd5"
#define ROOM_PARAM_GAME_6_DYNAMIC                           "vd6"
#define ROOM_PARAM_GAME_7_DYNAMIC                           "vd7"
#define ROOM_PARAM_GAME_8_DYNAMIC                           "vd8"

#define ROOM_PARAM_CURRENT_GAME_DYNAMIC                     "vd"

#define ROOM_PARAM_JACKPOT                                  "jpt"
#define ROOM_PARAM_NUMBER_PLAYERS_ONLINE                    "npo"

// common info from lobby
#define ROOM_PARAM_LEVEL_MAX_EXPERIENCE                     "lme"

// game play params
#define EX_REQUEST_PARAM_BET_CHIPS                          "bmn"
#define EX_REQUEST_PARAM_DEAL_CARDS                         "dec"
#define EX_REQUEST_PARAM_HOLD_CARD_BITS                     "hoc"
#define EX_REQUEST_PARAM_DRAW_CARDS                         "drc"
#define EX_REQUEST_PARAM_RESULT_HAND_ID                     "rsk"
#define EX_REQUEST_PARAM_WON_CHIPS                          "rsm"
#define EX_REQUEST_PARAM_HINT_BITS                          "hin"
#define EX_REQUEST_PARAM_DON_ACCEPTED                       "dng"
#define EX_REQUEST_PARAM_DON_DEALER_CARD                    "dca"
#define EX_REQUEST_PARAM_DON_PLAYER_CARDS                   "dnc"
#define EX_REQUEST_PARAM_DON_SELECT_CARD                    "scp"

// device info
#define EX_REQUEST_PARAM_GAME_VERSION_PARAM                 "gvs"
#define EX_REQUEST_PARAM_OS_VERSION_PARAM                   "ovs"
#define EX_REQUEST_PARAM_GAME_TYPE_PARAM                    "gtp"

// in-app purchase
#define EX_REQUEST_PARAM_IAP_VERIFY_DATA                    "rck" //RECEIPT_KEY
#define EX_REQUEST_PARAM_IAP_PRODUCT_TYPE                   "pid"
#define EX_REQUEST_PARAM_IAP_PACKAGE_NAME                   "pna"
#define EX_REQUEST_PARAM_IAP_CHIPS_AMOUNT                   "cam"
#define EX_REQUEST_PARAM_IAP_VIP_POINT                      "pvp"
#define EX_REQUEST_PARAM_IAP_ANDROID_PACKAGE_ID             "gpi"
#define EX_REQUEST_PARAM_IAP_ANDROID_PRODUCT_ID             "sid"
#define EX_REQUEST_PARAM_IAP_ANDROID_TOKEN                  "gpt"
//#define EX_REQUEST_PARAM_IAP_RECEIPT_KEY                    "rck"

// common notification result
#define EX_REQUEST_PARAM_RESULT_STATUS                      "stk"
#define EX_REQUEST_PARAM_RESULT_STATUS_CONTENT              "stc"

// paytable info
#define EX_REQUEST_PARAM_PAYTABLE_ARRAY                     "ptk"
#define EX_REQUEST_PARAM_PAYTABLE_HAND_ID                   "hid"
#define EX_REQUEST_PARAM_PAYTABLE_HAND_NAME                 "hna"
#define EX_REQUEST_PARAM_PAYTABLE_HAND_MULTIPLY             "hmu"

// hourly bonus
#define EX_REQUEST_PARAM_HOURLY_BONUS_MAX                   "hbm"
#define EX_REQUEST_PARAM_HOURLY_CHIPS_PER_SECOND            "hbs"
#define EX_REQUEST_PARAM_HOURLY_BONUS_CURRENT               "hlb"

// daily bonus
#define EX_REQUEST_PARAM_DAILY_CONSECUTIVE_DAYS             "cds"
#define EX_REQUEST_PARAM_DAILY_CONSECUTIVE_DAYS_BONUS       "cdb"
#define EX_REQUEST_PARAM_DAILY_EACH_FRIEND_REWARD           "efr"
#define EX_REQUEST_PARAM_DAILY_FRIENDS_BONUS                "frb"
#define EX_REQUEST_PARAM_DAILY_EACH_LEVEL_REWARD            "elr"
#define EX_REQUEST_PARAM_DAILY_LEVEL_REWARD_BONUS           "lrb"
#define EX_REQUEST_PARAM_DAILY_VIP_CARD                     "pvc"
#define EX_REQUEST_PARAM_DAILY_VIP_REWARD_BONUS             "vrb"

//leaderboard
#define EX_REQUEST_PARAM_USER_CHIP_RANK                     "ucr"
#define EX_REQUEST_LEADER_BOARD_KEY                         "lbo"
#define EX_REQUEST_LEADER_BOARD_FIRSTNAME                   "$#f"
#define EX_REQUEST_LEADER_BOARD_LASTNAME                    "$#l"
#define EX_REQUEST_LEADER_BOARD_CHIPS                       "cnu"
#define EX_REQUEST_LEADER_BOARD_PROFILE_ID                  "pid"
#define EX_REQUEST_LEADER_BOARD_AVATAR_ID                   "$aid"
#define EX_REQUEST_GET_LEADER_BOARD                         "lbc"

//update name
#define EX_REQUEST_NAME_UPDATE                              "nuc"
#define EX_REQUEST_NAME_UPDATE_FIRSTNAME                    "$#f"
#define EX_REQUEST_NAME_STATUS_KEY                          "stk"

#endif
