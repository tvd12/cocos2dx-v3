//
//  StatusLayer.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#ifndef __Earlybird__StatusLayer__
#define __Earlybird__StatusLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <cstdlib>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

#define NUMBER_SCORE    "number_score"
#define NUMBER_FONT     "font"

#define CURRENT_SCORE_SPRITE_TAG    10001

class StatusDelegate {
public:
    /**
     * When the game start, this method will be called
     */
    virtual void onGameStart(void) = 0;
    
    /**
     * During paying, after the score changed, this method will be called
     */
    virtual void onGamePlaying(int score) = 0;
    
    /**
     * When game is over, this method will be called
     */
    virtual void onGameEnd(int currentScore, int bestScore) = 0;
};

class StatusLayer : public Layer, public StatusDelegate {
public:
    StatusLayer();
    
    virtual bool init();
    
    virtual void onGameStart();
    
    virtual void onGamePlaying(int score);
    
    virtual void onGameEnd(int currentScore, int bestScore);
    
    CREATE_FUNC(StatusLayer);
    
    ~StatusLayer();
    
private:
    void showReadyStatus();
    
    void showStartStatus();
    
    void showOverStatus(int curScore, int bestScore);
    
    void loadWhiteSprite();
    
    void blinkFullScreen();
    
    void fadeInGameOver();
    
    void jumpToScorePanel();
    
    void fadeInRestartBtn();
    
    void refreshScoreCallback();
    
    void refreshScoreExecutor(float dt);
    
    string getMedalsName(int score);
    
    void setBlinkSprite();
    
    void blinkAction();
    
    void menuRestartCallback(Ref *sender);
    
    Sprite* mScoreSprite;
    
    Sprite* mGetreadySprite;
    
    Sprite* mTutorialSprite;
    
    Sprite* mWhiteSprite;
    
    int mCurrentScore;
    
    int mBestScore;
    
    int mTmpScore;
    
    bool mIsNewRecord;
    
    Point mOriginPoint;
    
    Size mVisibleSize;
    
    Sprite* mBlink;
};

#endif /* defined(__Earlybird__StatusLayer__) */
