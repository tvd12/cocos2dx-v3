//
//  SoundManager.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 6/5/14.
//
//
#include "SingLeton.h"
#include "cocos2d.h"

#ifndef __DragonVideoPoker__SoundManager__
#define __DragonVideoPoker__SoundManager__

typedef enum SOUND_TYPE {
    SOUND_BUTTON_CLICK              = 10,
    SOUND_GOT_BONUS                 = 12,
    SOUND_GOT_PURCHASED             = 13,
    SOUND_GOT_LEVEL_UP              = 14,
    SOUND_GOT_JACKPOT               = 15,
    SOUND_GOT_VIP_UPGRADE           = 16,
    SOUND_MISS_BIG_FISH             = 17,
    
    SOUND_BET_CHIP                  = 20,
    SOUND_BET_CHIPS                 = 21,
    SOUND_COLLECT_CHIPS             = 22,
    SOUND_DON                       = 23,
    SOUND_FLIP_CARD                 = 24,
    SOUND_FLY_CARD                  = 25,
    SOUND_NORMAL_WIN                = 26,
    SOUND_NORMAL_LOSE               = 27,
    SOUND_HOLD_CARD                 = 28,
    
} SoundType;


USING_NS_CC;

class SoundManager : public SingLeton<SoundManager>
{
public:
	SoundManager();
    
    
    unsigned int playSound(int type);
    void stopSound(unsigned int soundID);
    
    void playBackgroundMusic();
    void resumeBackgroundMusic();
    void pauseBackgroundMusicIfNeed();
    void forcePauseBackgroundMusic();
    void stopBackgroundMusic();
    
private:
    bool isMusicStopped;
    
};

#define SOUND() SoundManager::getSingleton()

#endif /* defined(__DragonVideoPoker__SoundManager__) */
