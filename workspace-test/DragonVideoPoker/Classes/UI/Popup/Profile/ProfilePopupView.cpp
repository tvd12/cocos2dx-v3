//
//  ProfilePopupView.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/15/14.
//
//

#include "ProfilePopupView.h"
#include "VisibleRect.h"
#include "TdgServer.h"
#include "UserInfo.h"
#include "BaseUserInfo.h"
#include "UserStatistics.h"
#include "CardView.h"
#include "Card.h"
#include "SoundManager.h"
#include "NativeHelper.h"

#include "VipClubPopupView.h"
#include "AvatarsPopupView.h"
#include "LobbyScene.h"


#define NEW_SPRITE(pSpriteName, pImageName, pPosition) \
pSpriteName = CCSprite::create(pImageName); \
pSpriteName->setPosition(pPosition); \
mBackgroundSprite->addChild(pSpriteName);

#define NEW_SPRITE_LEFT_ALIGN(pSpriteName, pImageName, pPosition) \
    pSpriteName = CCSprite::create(pImageName); \
    pSpriteName->setAnchorPoint(CCPoint(0.0f, 0.5f)); \
    pSpriteName->setPosition(pPosition); \
    mBackgroundSprite->addChild(pSpriteName);

#define NEW_LABEL_LEFT_ALIGN(pLabelName, pString, pPosition) \
    pLabelName = CCLabelTTF::create(pString, DEFAULT_FONT_NAME, GPARAMS().CMM_FONT_SIZE_3); \
    pLabelName->setAnchorPoint(CCPoint(0.0f, 0.5f)); \
    pLabelName->setPosition(pPosition); \
    mBackgroundSprite->addChild(pLabelName);

#define NEW_LABEL_RIGHT_ALIGN(pLabelName, pString, pPosition) \
    pLabelName = CCLabelTTF::create(pString, DEFAULT_FONT_NAME, GPARAMS().CMM_FONT_SIZE_3); \
    pLabelName->setAnchorPoint(CCPoint(1.0f, 0.5f)); \
    pLabelName->setPosition(pPosition); \
    mBackgroundSprite->addChild(pLabelName);

#define LONG_TO_STRING(longValue)      CCString::createWithFormat("%lld", longValue)->getCString()


ProfilePopupView* ProfilePopupView::create(string pBackgroundImage,
                                           string pExitNormalImage,
                                           string pExitSelectedImage) {
    // update the newest user statistics
    SERVER().updateNewestUserStatistics();
    
    ProfilePopupView* pRet = new ProfilePopupView();
    pRet->autorelease();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage);
    
    return pRet;
}

bool ProfilePopupView::init(string pBackgroundImage,
                            string pExitNormalImage,
                            string pExitSelectedImage) {
    
    PopUpLayer::init(pBackgroundImage,
                     pExitNormalImage,
                     pExitSelectedImage,
                     GPARAMS().POP_COMMON_EXIT_BUTTON_POSITION);
    setBackgroundPosition(VisibleRect::center());
    
    return true;
}

void ProfilePopupView::addMenuItems() {
    PopUpLayer::addMenuItems();
    
    //add menuItem sprite
    this->addLogoutMenuItem(mPopupMenu, GPARAMS().POP_PROFILE_LOGOUT_MENUITEM_POSITION);
    this->addAvatarMenuItem(mPopupMenu, GPARAMS().POP_PROFILE_AVARTAR_MENUITEM_POSITION);
    this->addVipClubMenuItem(mPopupMenu, GPARAMS().POP_PROFILE_VIP_CLUB_MENUITEM_POSITION);
    
    //set tag for menuitems
    this->mLogoutMenuItem->setTag(logoutTag);
    this->mAvatarMenuItem->setTag(avatarTag);
    this->mVipClubMenuItem->setTag(vipClubTag);
    if(!USERINFO()->getIsFBAccount()) {
        this->addRenameMenuItem(mPopupMenu, GPARAMS().POP_PROFILE_RENAME_MENUITEM_POSITION);
        this->mRenameMenuItem->setTag(renameTag);
    }
    
    // add user avatar menu item
    AvatarMenuItem* avatarLayer = AvatarMenuItem::create(USERINFO()->getProfileID(),
                                                         USERINFO()->getUserAvatarType(),
                                                         GPARAMS().CMM_ICON_PROFILE_SIZE,
                                                         GPARAMS().POP_PROFILE_CIRCLE_AVATAR_SPRITE_POSITION);
    mPopupMenu->addChild(avatarLayer);
    avatarLayer->setDelegate(this);
}

void ProfilePopupView::addSprites() {
    PopUpLayer::addSprites();
    
    //total 9 + 5
    //1
    NEW_SPRITE_LEFT_ALIGN(mBestHandTextSprite,
               "pop_profile_best_hand_text.png",
               GPARAMS().POP_PROFILE_BEST_HAND_SPRITE_POSITION);

    
    //2
    NEW_SPRITE_LEFT_ALIGN(mWinRatioTextSprite,
               "pop_profile_win_ratio_text.png",
               GPARAMS().POP_PROFILE_WIN_RATIO_SPRITE_POSITION);
    
    //3
    NEW_SPRITE_LEFT_ALIGN(mBiggestWinPlayedTextSprite,
               "pop_profile_biggest_win_text.png",
               GPARAMS().POP_PROFILE_BIGGEST_WIN_SPRITE_POSITION);
    
    //4
    NEW_SPRITE_LEFT_ALIGN(mHandsWonPlayedTextSprite,
               "pop_profile_hands_won_text.png",
               GPARAMS().POP_PROFILE_HANDS_WON_SPRITE_POSITION);
    
    //5
    NEW_SPRITE_LEFT_ALIGN(mHandsPlayedTextSprite,
               "pop_profile_hands_played_text.png",
               GPARAMS().POP_PROFILE_HANDS_PLAYED_SPRITE_POSITION);
    
    //other
    //6
    NEW_SPRITE(mLevelIconSprite,
               "pop_profile_level_icon.png",
               GPARAMS().POP_PROFILE_LEVEL_ICON_SPRITE_POSITION);
    
    //7
    NEW_SPRITE(mLocationIconSprite,
               "pop_profile_location_icon.png",
               GPARAMS().POP_PROFILE_LOCATION_ICON_SPRITE_POSITION);
    
    if(USERINFO()->getGender() == 0 || USERINFO()->getGender() == 1) {
        //8
        NEW_SPRITE(mGenderIconSprite,
                   (USERINFO()->getGender() == 0)
                   ? "pop_profile_male_icon.png"
                   : "pop_profile_female_icon.png",
                   GPARAMS().POP_PROFILE_GENDER_ICON_SPRITE_POSITION);
    }
    
    //9
    NEW_SPRITE(mChipIconSprite,
               "pop_profile_chip_icon.png",
               GPARAMS().POP_PROFILE_CHIP_ICON_SPRITE_POSITION);
    
    vector<CardView*> cardViews = vector<CardView*>(5);
    for(int k = 0 ; k < 5  ; k++) {
        int hand = USERSTATS()->getBestHand()->at(k);
        Card *card = new Card(hand);
        cardViews[k] = CardView::create(card, GPARAMS().POP_PROFILE_CARD_SCALE);
        cardViews[k]->retain();
        cardViews[k]->setPosition(GPARAMS().POP_PROFILE_CARDS_POSTIONS[k]);
        cardViews[k]->addToParent(mBackgroundSprite, 100);
        if (hand >= 0) {
            cardViews[k]->flipOutCardView(0.15f);
        }
        else {
            cardViews[k]->showBackCard();
        }
    }
    
    CCSprite* avatarBorder = CCSprite::create("pop_profile_avatar_profile_frame.png");
    avatarBorder->setPosition(GPARAMS().POP_PROFILE_CIRCLE_AVATAR_SPRITE_POSITION);
    mBackgroundSprite->addChild(avatarBorder);
}

void ProfilePopupView::addLabels()
{
    if(!USERINFO()->getIsFBAccount()) {
        CCScale9Sprite * editBoxSprite = CCScale9Sprite::create("pop_profile_green_editbox.png");
        editBoxSprite->setOpacity(0);
        float height = GPARAMS().POP_PROFILE_NAME_EDITBOX_HEIGHT;
        float width = GPARAMS().POP_PROFILE_NAME_EDITBOX_WIDTH;
        mNameEditBox = CCEditBox::create(CCSizeMake(width, height), editBoxSprite);
        mNameEditBox->setAnchorPoint(CCPoint(0.0f, 0.5f));
        mNameEditBox->setPosition(GPARAMS().POP_PROFILE_NICKNAME_LABEL_POSITION);
        mNameEditBox->setFont(DEFAULT_FONT_NAME, GPARAMS().CMM_FONT_SIZE_3);
        mNameEditBox->setFontColor(ccWHITE);
        mNameEditBox->setPlaceHolder(USERINFO()->getFullName());
        mNameEditBox->setPlaceholderFontColor(ccWHITE);
        mNameEditBox->setMaxLength(30);
        mNameEditBox->setReturnType(kKeyboardReturnTypeDone);
        mNameEditBox->setDelegate(this);
        mNameEditBox->setTouchPriority(kCCMenuHandlerPriority - 999);
        mBackgroundSprite->addChild(mNameEditBox);
    } else {
        NEW_LABEL_LEFT_ALIGN(mNickNameLabel,
                             USERINFO()->getFullName(),
                             GPARAMS().POP_PROFILE_NICKNAME_LABEL_POSITION);
    }
    
    NEW_LABEL_LEFT_ALIGN(mChipLabel,
                         CURRENCY_LONG(USERINFO()->getTotalChips()),
                         GPARAMS().POP_PROFILE_CHIPS_LABEL_POSITION);
    
    NEW_LABEL_LEFT_ALIGN(mLocationLabel,
                         USERINFO()->getLocation(),
                         GPARAMS().POP_PROFILE_LOCATION_LABEL_POSITION);
    
    NEW_LABEL_LEFT_ALIGN(mLocationLabel,
                         CCString::createWithFormat("%ld", USERINFO()->getLevel())->getCString(),
                         GPARAMS().POP_PROFILE_LEVEL_LABEL_POSITION);
    
    NEW_LABEL_RIGHT_ALIGN(mHandsPlayedTextLabel,
                         USERSTATS()->getHandsPlayedString(),
                         GPARAMS().POP_PROFILE_HANDS_PLAYED_LABEL_POSITION);
    
    NEW_LABEL_RIGHT_ALIGN(mHandsWonPlayedTextLabel,
                          USERSTATS()->getHandsWonString(),
                          GPARAMS().POP_PROFILE_HANDS_WON_LABEL_POSITION);
    
    NEW_LABEL_RIGHT_ALIGN(mBiggestWinPlayedTextSprite,
                          USERSTATS()->getBiggestWinString(),
                          GPARAMS().POP_PROFILE_BIGGEST_WIN_LABEL_POSITION);
    
    NEW_LABEL_RIGHT_ALIGN(mWinRatioTextLabel,
                          USERSTATS()->getHandsWonRatioString(),
                          GPARAMS().POP_PROFILE_WIN_RATIO_LABEL_POSITION);
    
}

void ProfilePopupView::profileMenuItemCallback(CCObject *pSender)
{
    SOUND().playSound(SOUND_BUTTON_CLICK);

    CCNode *sender = static_cast<CCNode*>(pSender);
    
    switch (sender->getTag()) {
        case logoutTag:
            SERVER().logout();
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventLogout);
            break;
        
        case avatarTag: {
            this->hide();
            AvatarsPopupView *avatar = AvatarsPopupView::create();
            this->getParent()->addChild(avatar, 1000);
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventAvatar);
            break;
        }
            
        case vipClubTag: {
            this->hide();
            VipClubPopupView *vipclubPopup = VipClubPopupView::create();
            this->getParent()->addChild(vipclubPopup, 1000);
            
            // track GA
            NATIVE().sendMainEvent(kGAMainEventVip);
            break;
        }
        
        case renameTag: {
            mNameEditBox->touchDownAction(NULL, NULL);
            break;
        }
    }
}

void ProfilePopupView::selectAvatarCallback(const char* memeberID) {
    SOUND().playSound(SOUND_BUTTON_CLICK);

    this->hide();
    AvatarsPopupView *avatar = AvatarsPopupView::create();
    this->getParent()->addChild(avatar, 1000);
    
    // track GA
    NATIVE().sendMainEvent(kGAMainEventAvatar);
}

void ProfilePopupView::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void ProfilePopupView::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox->getText());
    USERINFO()->setFirstName(editBox->getText());
    CCLabelTTF *fullnameLabel = static_cast<LobbyLayer*>(this->getParent())->getFullnameLabel();
    if(fullnameLabel) {
        fullnameLabel->setString(editBox->getText());
    }
    USERINFO()->updateFullName();
    SERVER().sendUpdateFirstNameRequest(string(editBox->getText()));
}

void ProfilePopupView::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void ProfilePopupView::editBoxReturn(CCEditBox* editBox)
{
    CCLog("editBox %p was returned !",editBox);
}

