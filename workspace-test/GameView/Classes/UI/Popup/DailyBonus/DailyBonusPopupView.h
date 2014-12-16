//
//  DailyBonusPopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/20/14.
//
//

#ifndef __DragonVideoPoker__DailyBonusPopupView__
#define __DragonVideoPoker__DailyBonusPopupView__

#include <string>

#include "PopUpLayer.h"
#include "GameParams.h"

using namespace std;

class DailyBonusInfo;

class DailyBonusPopupView : public PopUpLayer {
public:
    
    static DailyBonusPopupView* create(string pBackgroundImage = "pop_common_bg.png",
                                    string pExitNormalImage = "pop_common_close_normal.png",
                                    string pExitSelectedImage = "pop_common_close_active.png");
    
    virtual bool init(string pBackgroundImage = "pop_common_bg.png",
                      string pExitNormalImage = "pop_common_close_normal.png",
                      string pExitSelectedImage = "pop_common_close_active.png");
    
    CREATE_MENUITEM_SPRITE(ClaimMenuItem,
                           "pop_dailybonus_claim_menuitem_normal.png",
                           "pop_dailybonus_claim_menuitem_active.png",
                           DailyBonusPopupView::dailyBonusMenuItemCallback);
    CREATE_MENUITEM_SPRITE(FriendMenuItem,
                           "pop_dailybonus_facebook_friend_bg.png",
                           "pop_dailybonus_facebook_friend_bg.png",
                           DailyBonusPopupView::friendMenuItemCallback);
    CREATE_MENUITEM_SPRITE(VipMenuItem,
                           "pop_dailybonus_vip_bg.png",
                           "pop_dailybonus_vip_bg.png",
                           DailyBonusPopupView::vipMenuItemCallback);
    
    
protected:
    virtual void addSprites();
    virtual void addMenuItems();
    virtual void addLabels();
    
private:
    
    void dailyBonusMenuItemCallback(CCObject *pSender);
    void friendMenuItemCallback(CCObject *pSender);
    void vipMenuItemCallback(CCObject *pSender);
    
    CCSprite* mHeader;
    
    CCLabelTTF* mSoundEffectLabel;
    CCLabelTTF* mMusicLabel;
    CCLabelTTF* mLeftHandLabel;
    CCLabelTTF* mDoubleOrNothingLabel;
    
    DailyBonusInfo* mDailyBonusInfo;
    
    CCSprite* mLevelSeparateSprite;
    CCSprite* mLevelSprite;
    CCSprite* mVipSprite;
    CCSprite* mFacebookSeparateSprite;
    CCSprite* mDaysSprite;
    CCSprite* mFacebookFriendSprite;
    CCSprite* mTotalBonusSprite;
    CCSprite* mHeaderSprite;
    CCSprite* mSliverCardSprite;
    CCSprite* mComebackSprite;
    
    CCLabelTTF* mDaysLabel;
    CCLabelTTF* mDaysChipsLabel;
    CCLabelTTF* mFacebookFriendPartOneLabel;
    CCLabelTTF* mFacebookFriendPartTwoLabel;
    CCLabelTTF* mFacebookFriendChipsLabel;
    CCLabelTTF* mLevelPartOneLabel;
    CCLabelTTF* mLevelPartTwoLabel;
    CCLabelTTF* mLevelChipsLabel;
    CCLabelTTF* mVipLabel;
    CCLabelTTF* mVipChipsLabel;
    CCLabelTTF* mTotalBonusTextLabel;
    CCLabelTTF* mTotalBonusValueLabel;
    CCLabelTTF* mDaysValueLabel;
};

#endif /* defined(__DragonVideoPoker__DailyBonusPopupView__) */
