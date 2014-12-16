//
//  VideoPokerDefine.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/21/14.
//
//

#ifndef DragonVideoPoker_VideoPokerDefine_h
#define DragonVideoPoker_VideoPokerDefine_h

//define game

typedef enum VIDEO_POKER_GAME_TYPE {
    JACKS_OR_BETTER                         = 0,
    JOKER_POKER                             = 1,
    TENS_OR_BETTER                          = 2,
    DEUCES_WILD                             = 3,
    ACES_AND_FACES                          = 4,
    DOUBLE_BONUS                            = 5,
    ACES_AND_EIGHTS                         = 6,
    DEUCES_AND_JOKER_WILD                   = 7,
} VideoPokerGameType;

#define PAYTABLE_EMPTY                      100

#define JACKPOT_MULTIPLE                    10000

typedef enum POKER_HAND {
    //nothing = 0
    POKER_HAND_NOTHING                      = 0,
    
    //ten or better = 1
    POKER_HAND_TENS_OR_BETTER               = 1,
    
    //jack or better = 2
    POKER_HAND_JACKS_OR_BETTER              = 2,
    
    //kings or better = 3
    POKER_HAND_KINGS_OR_BETTER              = 3,
    
    //two pair = 4
    POKER_HAND_TWO_PAIR                     = 4,
    
    //three of a kind = 5
    POKER_HAND_THREE_OF_A_KIND              = 5,
    
    //straight = 6
    POKER_HAND_STRAIGHT                     = 6,
    
    //flush 7
    POKER_HAND_FLUSH                        = 7,
    
    //full house 8
    POKER_HAND_FULL_HOUSE                   = 8,
    //four of a kind 9
    POKER_HAND_FOUR_OF_A_KIND               = 9,
    //four sevens 10
    POKER_HAND_FOUR_SEVENS                  = 10,
    //four 5-k 11
    POKER_HAND_FOUR_5_K                     = 11,
    //four 2-4 12
    POKER_HAND_FOUR_2_4                     = 12,
    //four 2-10 13
    POKER_HAND_FOUR_2_10                    = 13,
    //four j-k 14
    POKER_HAND_FOUR_J_K                     = 14,
    //four aces 15
    POKER_HAND_FOUR_ACES                    = 15,
    //four aces or eights = 16
    POKER_HAND_FOUR_ACES_OR_EIGHTS          = 16,
    //straight flush 17
    POKER_HAND_STRAIGHT_FLUSH               = 17,
    //five of a kind 18
    POKER_HAND_FIVE_OF_A_KIND               = 18,
    //wild royal flush 19
    POKER_HAND_WILD_ROYAL_FLUSH             = 19,
    //natural four deuces 20
    POKER_HAND_NATURAL_FOUR_DEUCES          = 20,
    //royal flush 21
    POKER_HAND_NATURAL_ROYAL_FLUSH          = 21,
    //five wilds 22
    POKER_HAND_FIVE_WILDS                   = 22,
    
} PokerHandValue;

typedef enum DON_RESULT {
    DON_RESULT_WON                          = 0,
    DON_RESULT_LOSE                         = 1,
    DON_RESULT_PUSH                         = 2,
} DonResultValue;

#endif
