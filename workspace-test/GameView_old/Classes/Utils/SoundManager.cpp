//
//  SoundManager.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 6/5/14.
//
//

#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include "GameParams.h"

using namespace CocosDenshion;

SoundManager::SoundManager(void)
{
    // Cache sounds and music
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/BetChip.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/BetChips.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ButtonClick.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/CollectChips.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/DoubleOrNothing.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/FlipCard.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/FlyingCard.wav");
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/FlyingText.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/GotJackpot.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/GotLevelUp.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/GotVipUpgrade.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/HoldCard.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/NormalWin.mp3");
    
    // Preload music
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/_GameTheme.mp3");
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
}

unsigned int SoundManager::playSound(int type)
{
    if (!GPARAMS().isSoundOn) {
        return 0;
    }
    
    unsigned int soundID;
    switch (type) {
        case SOUND_BUTTON_CLICK:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/ButtonClick.mp3");
            break;
            
        case SOUND_GOT_BONUS:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/Bonus_Collect.mp3");
            break;
            
        case SOUND_GOT_PURCHASED:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/Purchase_Success.mp3");
            break;
            
        case SOUND_GOT_LEVEL_UP:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/GotLevelUp.mp3");
            break;
            
        case SOUND_GOT_JACKPOT:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/GotJackpot.mp3");
            break;
            
        case SOUND_GOT_VIP_UPGRADE:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/GotLevelUp.mp3");
            break;
            
        case SOUND_MISS_BIG_FISH:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/Miss_Big_Fish.mp3");
            break;
            
        case SOUND_BET_CHIP:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/BetChip.mp3");
            break;
            
        case SOUND_BET_CHIPS:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/BetChips.mp3");
            break;
            
        case SOUND_COLLECT_CHIPS:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/CollectChips.mp3");
            break;
            
        case SOUND_DON:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/DoubleOrNothing.mp3");
            break;
            
        case SOUND_FLIP_CARD:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/FlipCard.mp3");
            break;
            
        case SOUND_FLY_CARD:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/FlyingCard.wav");
            break;
            
        case SOUND_NORMAL_WIN:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/NormalWin.mp3");
            break;
            
        case SOUND_NORMAL_LOSE:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/Button_Disable.mp3");
            break;
            
        case SOUND_HOLD_CARD:
            soundID = SimpleAudioEngine::sharedEngine()->playEffect("sounds/HoldCard.wav");
            break;
            
        default:
            break;
    }
    
    return soundID;
}

void SoundManager::stopSound(unsigned int soundID)
{
    if (!GPARAMS().isSoundOn) {
        return;
    }
    
    SimpleAudioEngine::sharedEngine()->stopEffect(soundID);
}

#pragma mark - music feature

void SoundManager::playBackgroundMusic()
{
    if (!GPARAMS().isMusicOn) {
        return;
    }
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/_GameTheme.mp3", true);
    isMusicStopped = false;
}

void SoundManager::resumeBackgroundMusic()
{
    if (!GPARAMS().isMusicOn || isMusicStopped) {
        return;
    }
    
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void SoundManager::pauseBackgroundMusicIfNeed()
{
    if (!GPARAMS().isMusicOn) {
        return;
    }
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void SoundManager::forcePauseBackgroundMusic()
{
    if (GPARAMS().isMusicOn) {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}

void SoundManager::stopBackgroundMusic()
{
    if (!GPARAMS().isMusicOn) {
        return;
    }
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    isMusicStopped = true;
}

