//
//  ProfilePopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/15/14.
//
//

#ifndef __DragonVideoPoker__ProfilePopupView__
#define __DragonVideoPoker__ProfilePopupView__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopUpLayer.h"
#include "GameParams.h"
#include "AvatarMenuItem.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class ProfilePopupView :
public PopUpLayer,
public AvatarDelegate,
public CCEditBoxDelegate {
    
public:
    static ProfilePopupView* create(string pBackgroundImage = "pop_profile_bg.png",
                                    string pExitNormalImage = "pop_common_close_normal.png",
                                    string pExitSelectedImage = "pop_common_close_active.png");
    
    virtual bool init(string pBackgroundImage = "pop_profile_bg.png",
                      string pExitNormalImage = "pop_common_close_normal.png",
                      string pExitSelectedImage = "pop_common_close_active.png");
    
    virtual void selectAvatarCallback(const char* memeberID);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
    CREATE_MENUITEM_SPRITE(LogoutMenuItem,
                           "pop_profile_log_out_button_normal.png",
                           "pop_profile_log_out_button_active.png",
                           ProfilePopupView::profileMenuItemCallback);
    CREATE_MENUITEM_SPRITE(RenameMenuItem,
                           "pop_profile_edit_button_normal.png",
                           "pop_profile_edit_button_active.png",
                           ProfilePopupView::profileMenuItemCallback);
    
    CREATE_MENUITEM_SPRITE(AvatarMenuItem,
                           "pop_profile_avatar_button_normal.png",
                           "pop_profile_avatar_button_active.png",
                           ProfilePopupView::profileMenuItemCallback);

    CREATE_MENUITEM_SPRITE(VipClubMenuItem,
                           "pop_profile_vip_club_button_normal.png",
                           "pop_profile_vip_club_button_active.png",
                           ProfilePopupView::profileMenuItemCallback);
    
protected:
    virtual void addSprites();
    virtual void addMenuItems();
    virtual void addLabels();

private:
    enum MenuItemTag {
        logoutTag          = 1000,
        avatarTag          = 1001,
        vipClubTag         = 1002,
        renameTag          = 1003,
    };
    void profileMenuItemCallback(CCObject *pSender);
    
    CCSprite* mGenderIconSprite;
    CCSprite* mChipIconSprite;
    CCSprite* mLocationIconSprite;
    CCSprite* mLevelIconSprite;
    
    CCSprite* mHandsPlayedTextSprite;
    CCSprite* mHandsWonPlayedTextSprite;
    CCSprite* mBiggestWinPlayedTextSprite;
    CCSprite* mWinRatioTextSprite;
    CCSprite* mBestHandTextSprite;
    
    CCLabelTTF* mNickNameLabel;
    CCLabelTTF* mChipLabel;
    CCLabelTTF* mLocationLabel;
    CCLabelTTF* mLevelLabel;
    
    CCLabelTTF* mHandsPlayedTextLabel;
    CCLabelTTF* mHandsWonPlayedTextLabel;
    CCLabelTTF* mBiggestWinPlayedTextLabel;
    CCLabelTTF* mWinRatioTextLabel;
    
    CCEditBox *mNameEditBox;
};

#endif /* defined(__DragonVideoPoker__ProfilePopupView__) */
