//
//  LobbyScene.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef __DragonVideoPoker__LobbyScene__
#define __DragonVideoPoker__LobbyScene__

#define MIDDLE_ORDER            50
#define MENU_ORDER              200
#define FOOTER_ORDER            300


#include "cocos2d.h"
#include "CCScrollLayer.h"
#include "AvatarMenuItem.h"

#define NUMBER_CHIPS_PER_ICON                   100
#define DELAY_MOVE_BONUS_CHIP_DURATION          0.02


using namespace std;
using namespace cocos2d;

class LobbyLayer : public CCLayer, CCScrollLayerDelegate, public AvatarDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* createScene();
    
    virtual void scrollLayerScrollingStarted(CCScrollLayer* sender) {}
    virtual void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);

    virtual void selectAvatarCallback(const char* memeberID);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onExit();
    virtual void update(float dt);
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(LobbyLayer);
    
private:
    void selectGameMenuItemCallback(CCObject* pSender);
    void settingsMenuItemCallback(CCObject* pSender);
    void addChipsMenuItemCallback(CCObject* pSender);
    void bonusChipsMenuItemCallback(CCObject* pSender);
    void addSprites();
    void addLevelUpSystem();
    void addMenuItems();
    void addLabels();
    
    void addScrollLayer();
    void createHeaderSprites();
    
    // update labels
    void updateTotalChipsLabel();
    void updateHourlyBonusLabel(float dt);
    void onClaimHourlyBonusSuccess(CCObject *object);
    void onClaimDailyBonusSuccess(CCObject *object);
    void onInAppPurchaseSuccess(CCObject *object);
    void onUpdateAvatar(CCObject *object);

    void createClaimHourlyBonusEffect();
    void moveChipFinish(CCObject* pSender);
    
    vector<CCSprite*> mHeaderSprites;
    
    CCSprite* mMiddleChipIcon;
    
    long long mDisplayTotalChips;
    CCLabelTTF* mTotalChipsLabel;
    CCLabelTTF* mBonusChipsLabel;
    
    bool mIsClaimingHourlyBonus;
    bool mIsJustGotDailyBonus;
    bool mIsNeedUpdateTotalChips;
    
    AvatarMenuItem* mAvatarMenuItem;
    CCMenuItemLabel* mBonusChipsMenuLabel;
};


#endif /* defined(__DragonVideoPoker__LobbyScene__) */
