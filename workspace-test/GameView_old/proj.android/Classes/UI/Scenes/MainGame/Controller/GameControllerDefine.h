//
//  GameControllerDefine.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/21/14.
//
//

#ifndef DragonVideoPoker_GameControllerDefine_h
#define DragonVideoPoker_GameControllerDefine_h

typedef enum GAME_PLAY_STATE {
    tdgGamePlayStateBetting,
    tdgGamePlayStateDealing,
    tdgGamePlayStateDrawing,
    tdgGamePlayStateDonStart,
    tdgGamePlayStateDonDealing,
    tdgGamePlayStateDonFinish,
    
    
} Game_Play_State;

#endif
