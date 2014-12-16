//
//  NativeHelper.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 10/17/13.
//
//

#ifndef __Dragon_Poker__NativeHelper__
#define __Dragon_Poker__NativeHelper__

#include "SingLeton.h"

using namespace std;

#define GA_MAIN_CATEGORY                        "Main Category"
#define GA_GAME_CATEGORY                        "Game Category"

#define GA_SCREEN_LOGIN                         "Login Scene"
#define GA_SCREEN_LOBBY                         "Lobby Scene"
#define GA_MAIN_GAME_JACKS_OR_BETTER            "Jacks Or Better Game"
#define GA_MAIN_GAME_JOKER_POKER                "Joker Poker Game"
#define GA_MAIN_GAME_TENS_OR_BETTER             "Tens Or Better Game"
#define GA_MAIN_GAME_DEUCES_WILD                "Deuces Wild Game"
#define GA_MAIN_GAME_ACES_AND_FACES             "Aces And Faces Game"
#define GA_MAIN_GAME_DOUBLE_BONUS               "Double Bonus Game"
#define GA_MAIN_GAME_ACES_AND_EIGHTS            "Aces And Eights Game"
#define GA_MAIN_GAME_DEUCES_AND_JOKER_WILD      "Deuces And Joker Wild Game"

typedef enum {
    kGAScreenMainGameJacksOrBetter			= 0,
    kGAScreenMainGameJokerPoker             = 1,
    kGAScreenMainGameTensOrBetter			= 2,
    kGAScreenMainGameDeucesWild             = 3,
    kGAScreenMainGameAcesAndFaces			= 4,
    kGAScreenMainGameDoubleBonus			= 5,
    kGAScreenMainGameAcesAndEights			= 6,
    kGAScreenMainGameDeucesAndJokerWild     = 7,
    kGAScreenLogin                          = 8,
    kGAScreenLobby                          = 9,
} GAScreenViewType;

typedef enum {
    kGAMainEventLobbySettings       = 0,
    kGAMainEventOnGameSettings		= 1,
    kGAMainEventProfile             = 2,
    kGAMainEventBuyChips			= 3,
    kGAMainEventHourlyBonus         = 4,
    kGAMainEventAvatar				= 5,
    kGAMainEventVip					= 6,
    kGAMainEventDailyBonus          = 7,
    kGAMainEventLogout              = 8,
    kGAMainEventGuestLogin          = 9,
    kGAMainEventFbLogin             = 10,
    kGAMainEventContact             = 11,
    kGAMainEventRateUs              = 12,
    kGAMainEventShareLevelUp        = 13,
    kGAMainEventShareVipUpgrade     = 14,
    kGAMainEventShareJackpot        = 15,
    kGAMainEventFanPage             = 16,
    kGAMainEventInviteFriend        = 17,
} GAMainEvent;

typedef enum {
    kGAGameEventDeal				= 0,
    kGAGameEventCancelBet			= 2,
    kGAGameEventMaxBet              = 3,
    kGAGameEventDonYes              = 4,
    kGAGameEventDonNo               = 5,
    kGAGameEventLeftHand            = 6,
    kGAGameEventRightHand           = 7,
    kGAGameEventDonEnable           = 8,
    kGAGameEventDonDisable          = 9,
    
    kGAGameEventChipTypeSmall       = 10,
    kGAGameEventChipTypeMedium      = 11,
    kGAGameEventChipTypeBig         = 12,
} GAGameEvent;

#define EMAIL_SUBJECT               "[Video Poker JACKPOT] - Feedback"

#ifdef CC_TARGET_OS_IPHONE
#define GAME_ON_STORE_URL           "https://itunes.apple.com/app/id%s"
#else
#define GAME_ON_STORE_URL           "https://play.google.com/store/apps/details?id=%s"
#endif

class NativeHelper : public SingLeton<NativeHelper>
{
public:
	NativeHelper();
    
    void vibrate();
    
    void rateUsOnStore();
    void sendFeedback();
    void openUrl(const char *url);
    void openUpdateUrl();
    
    string getDeviceUdid();
    
	//----Google Analytic------
    void sendMainEvent(int eventType);
    void sendGameEvent(int eventType);
    void sendGameEvent(int eventType, long long eventValue);
    void sendScreenView(int screenType);
private:
    void screenMeasurement(const char* screenName);
	void eventMeasurement(const char* eventCategory,
                          const char* eventAction,
                          const char* eventLabel,
                          long long eventValue);
	void sessionManagement(bool isStart);
};

#define NATIVE() NativeHelper::getSingleton()

#endif /* defined(__Dragon_Poker__NativeHelper__) */
