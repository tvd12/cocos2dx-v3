//
//  GameViewHeader.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#ifndef __DragonVideoPoker__GameViewHeader__
#define __DragonVideoPoker__GameViewHeader__

#include "cocos2d.h"
#include "GameViewDefine.h"
#include "IGameViewLayout.h"
#include "NotificationPopupView.h"

using namespace std;
USING_NS_CC;

class UserInfo;
class RoomInfo;
class GameModel;

class GameViewHeader : public CCLayer, public IGameViewLayout,
public NotificationPopupDelegate
{
public:
    virtual bool init(GameModel* gameModel);
    static GameViewHeader* create(GameModel* gameModel);
    
    virtual void update(float dt);

    virtual void prepareNewGame();

    virtual void button1DidPressed(NotificationPopupView* sender);
    virtual void button2DidPressed(NotificationPopupView* sender);

    void updateJackpot();
    void updateLevel();
    void updateLevelExperience();
    void updateJackpotLabel(long long& displayValue,
                          long long value,
                          CCLabelTTF* chipsLabel,
                          bool& isUpdatingJackpot);
    void updateLevelNumber();
    void updateLevelExperienceProgress();
    
    
    CC_SYNTHESIZE(UserInfo*, mUserInfo, UserInfo);
    CC_SYNTHESIZE(RoomInfo*, mRoomInfo, RoomInfo);
    CC_SYNTHESIZE(bool, mIsOnGame, IsOnGame);

private:
    virtual void updateLabels();
    virtual void addSprites();
    
    void addLabels();
    void addMenuItems();
    void addLevelProgress();

    void onExitItemCallback(CCNode *sender);
    void onSettingsItemCallback(CCNode *sender);

    CCSprite* mLevelNormalSprite;
    CCSprite* mJackpotSprite;
    CCSprite* mJackpotStringSprite;
    
    CCLabelTTF* mLevelLabel;
    CCLabelTTF* mJackpotLabel;
    CCLabelTTF* mJackpotHandLabel;
    CCLabelTTF* mNumberPlayersLabel;
    
    CCMenuItemImage* mExitMenuItem;
    CCMenuItemImage* mSettingsMenuItem;
    
    CCProgressTimer *mLevelProgress;
    
    bool mIsUpdatingJackpot;
    bool mIsUpdateLevel;
    bool mIsUpdateLevelExperience;
    long long mJackpotDisplay;
    long long mCurrentUserExperience;
    long mCurrentUserLevel;
};

#endif /* defined(__DragonVideoPoker__GameViewHeader__) */
