//
//  GameViewFooter.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/16/14.
//
//

#ifndef __DragonVideoPoker__GameViewFooter__
#define __DragonVideoPoker__GameViewFooter__

#include "cocos2d.h"
#include "IGameViewLayout.h"

#define CARD_SIMULATOR_TAG      100

using namespace std;
USING_NS_CC;

class UserInfo;
class GameModel;

class GameViewFooter : public CCLayer, public IGameViewLayout
{
public:
    virtual bool init(GameModel* gameModel);
    static GameViewFooter* create(GameModel* gameModel);

    virtual void onExit();
    virtual void prepareNewGame();
    
    ~GameViewFooter();
    
    void addMenuItems(CCObject *target);
    
    void disableDealButton();
    void enableDealButton();
    void showDealButton();
    void disableDrawButton();
    void enableDrawButton();
    void showDrawButton(float dt);
    
    void displayCardBacks(bool isSetVisible, int positionMask = 31);
    
    void hideAllHeldIcons();
    void showHeldIcons(int heldBit, float delayTime);
    void hideAllHighLightIcons();
    void showHighLightIcons(int wonBit, float delayTime);
    
    // double or nothing
    void showDonGame();
    void hideDonGame();
    void startDonGame();
    void dealDonGame();
    void showResultDonGame();
    
    // switch hand
    void switchHandPosition();
    
    CC_SYNTHESIZE(UserInfo*, mUserInfo, UserInfo);
    
    CC_SYNTHESIZE(CCSprite*, mSmallChipBg, SmallChipBg);
    CC_SYNTHESIZE(CCSprite*, mMediumChipBg, MediumChipBg);
    CC_SYNTHESIZE(CCSprite*, mBigChipBg, BigChipBg);

private:
    virtual void addSprites();
    virtual void updateLabels();

    void onEnableChipButtons(CCObject *object);
    void onDisableChipButtons(CCObject *object);

    void showHeldIcons(float dt);
    void showHighLightIcons(float dt);

    void showLeftHandUI();
    void showRightHandUI();
    
    CCPoint switchHandPoint(CCPoint leftPoint);
    void updateImagesForMenuItem(CCMenuItemImage* menuItem, const char* itemNameFormat, bool isHaveDisableImage = true);

    GameModel* mGameModel;
    
    CCSprite* mFunctionButtonBg;
    CCSprite* mMaxBetBg;
    
    CCMenuItemSprite* mSmallChipMenuItem;
    CCMenuItemSprite* mMediumChipMenuItem;
    CCMenuItemSprite* mBigChipMenuItem;
    CCMenuItemImage* mMaxBetMenuItem;
    
    CCMenuItemImage* mDealMenuItem;
    CCMenuItemImage* mDrawMenuItem;
    CCMenuItemImage* mDonYesMenuItem;
    CCMenuItemImage* mDonNoMenuItem;

    CCLabelTTF* mDonLabel;
    
    CCArray* mHeldSprites;
    CCArray* mWonBorders;
    CCArray* mCardSelectMenuItems;

    float mScreenWidth;
    int mHeldBit, mWonBit;
};

#endif /* defined(__DragonVideoPoker__GameViewFooter__) */
