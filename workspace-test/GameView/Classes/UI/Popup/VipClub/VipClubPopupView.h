//
//  VipClubPopupView.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 5/22/14.
//
//

#ifndef __DragonVideoPoker__VipClubPopupView__
#define __DragonVideoPoker__VipClubPopupView__

#include "PopUpLayer.h"

class VipClubPopupView : public PopUpLayer {
public:
    
    static VipClubPopupView* create(string pBackgroundImage = "pop_common_bg.png",
                                    string pExitNormalImage = "pop_common_close_normal.png",
                                    string pExitSelectedImage = "pop_common_close_active.png");
    
    virtual bool init(string pBackgroundImage = "pop_common_bg.png",
                      string pExitNormalImage = "pop_common_close_normal.png",
                      string pExitSelectedImage = "pop_common_close_active.png");
    
protected:
    virtual void addSprites();
    virtual void addLabels();
    virtual void addProgressBars();
    
private:
    CCSprite* mPlatinumTextSprite;
    CCSprite* mPlatinumCardSprite;
    CCSprite* mMemberCardSprite;
    CCSprite* mLinesSprite;
    CCSprite* mBronzeTextSprite;
    CCSprite* mHeaderSprite;
    CCSprite* mBigPlatinumCardSprite;
    CCSprite* mDiamondTextSprite;
    CCSprite* mDiamondCardSprite;
    CCSprite* mSliverCardSprite;
    CCSprite* mSliverTextSprite;
    CCSprite* mBigBronzeCardSprite;
    CCSprite* mProgressLevelSprite;
    CCSprite* mProgressLevelBackgroundSprite;
    CCSprite* mBigGoldCardSprite;
    CCSprite* mBronzeCardSprite;
    CCSprite* mBigSliverCardSprite;
    CCSprite* mGoldTextSprite;
    CCSprite* mBigDiamondCardSprite;
    CCSprite* mGoldCardSprite;
    
    CCSprite* mCheckedSprites[5];
    
    CCLabelTTF* mNoteMorePointsLabel;
    CCLabelTTF* mNoteMultipleLabel;
    CCLabelTTF* mBronzeVipPointTextLabel;
    CCLabelTTF* mBronzeVipPointValueLabel;
    CCLabelTTF* mBronzePackagesTextLabel;
    CCLabelTTF* mBronzePackagesValueLabel;
    CCLabelTTF* mSliverVipPointTextLabel;
    CCLabelTTF* mSliverVipPointValueLabel;
    CCLabelTTF* mSliverPackagesTextLabel;
    CCLabelTTF* mSliverPackagesValueLabel;
    CCLabelTTF* mGoldVipPointTextLabel;
    CCLabelTTF* mGoldVipPointValueLabel;
    CCLabelTTF* mGoldPackagesTextLabel;
    CCLabelTTF* mGoldPackagesValueLabel;
    CCLabelTTF* mPlatinumVipPointTextLabel;
    CCLabelTTF* mPlatinumVipPointValueLabel;
    CCLabelTTF* mPlatinumPackagesTextLabel;
    CCLabelTTF* mPlatinumPackagesValueLabel;
    CCLabelTTF* mDiamondVipPointTextLabel;
    CCLabelTTF* mDiamondVipPointValueLabel;
    CCLabelTTF* mDiamondPackagesTextLabel;
    CCLabelTTF* mDiamondPackagesValueLabel;
    CCLabelTTF* mProgressTextLabel;

};

#endif /* defined(__DragonVideoPoker__VipClubPopupView__) */
