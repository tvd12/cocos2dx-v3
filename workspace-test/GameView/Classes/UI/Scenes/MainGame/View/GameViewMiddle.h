//
//  GameViewMiddle.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#ifndef __DragonVideoPoker__GameViewMiddle__
#define __DragonVideoPoker__GameViewMiddle__

#include "cocos2d.h"
#include "IGameViewLayout.h"

using namespace std;
USING_NS_CC;

class UserInfo;
class RoomInfo;
class GameModel;

class GameViewMiddle : public CCLayer, public IGameViewLayout
{
public:
    ~GameViewMiddle();
    virtual bool init(GameModel* gameModel);
    static GameViewMiddle* create(GameModel* gameModel);
    
    virtual void update(float dt);
    virtual void onExit();
    virtual void prepareNewGame();

    void addMenuItems(CCObject *target);
    void showWonChips();
    void showBetChips();
    
private:
    virtual void updateLabels();
    virtual void addSprites();

    void addLabels();

    // menu item callback
    void buyChipsItemCallback(CCNode *sender);
    
    // notification center
    void onBettedChipStopMoving(CCObject *object);
    void onBettedChipStartMoving(CCObject *object);
    void onEnableCancelBetButton(CCObject *object);
    void onDisableCancelBetButton(CCObject *object);
    void onInAppPurchaseSuccess(CCObject *object);

    // update label
    void updateChipsLabel(long long& displayValue,
                          long long value,
                          CCLabelTTF* chipsLabel,
                          bool& isUpdatingChips);
    
    CCSprite*  mTotalChipsIcon;
    CCSprite*  mTotalBetChipsSprite;
    CCSprite*  mTotatWonChipsSprite;

    CCLabelTTF* mTotalBetChipsLabel;
    CCLabelTTF* mTotalWonChipsLabel;
    CCLabelTTF* mTotalChipsLabel;
    
    CCMenuItemImage* mTotalBetChipMenuItem;
    CCMenuItemImage* mBuyChipMenuItem;
    
    long long mTotalBetChipsDisplay;
    long long mTotalWonChipsDisplay;
    long long mTotalChipsDisplay;
    
    bool mIsUpdatingBetChips;
    bool mIsUpdatingWonChips;
    bool mIsUpdatingTotalChips;
    
    RoomInfo* mRoomInfo;
    UserInfo* mUserInfo;

};

#endif /* defined(__DragonVideoPoker__GameViewMiddle__) */
