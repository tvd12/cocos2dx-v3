//
//  PopUpLayer.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef __DragonVideoPoker__PopUpLayer__
#define __DragonVideoPoker__PopUpLayer__

#define POP_UP_SHOW_ANIMATION_DURATION              0.10f
#define POP_UP_HIDE_ANIMATION_DURATION              0.10f

#include <string>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class PopUpLayer : public CCLayer {
public:
    PopUpLayer();
    static PopUpLayer* create(string pBackgroundImage,
                              string pExitNormalImage = "",
                              string pExitSelectedImage = "",
                              const CCPoint &pExitPostion = CCPointZero);
    virtual bool init(string pBackgroundImage,
                      string pExitNormalImage = "",
                      string pExitSelectedImage = "",
                      const CCPoint &pExitPostion = CCPointZero);
    virtual void onEnter();
    virtual void onExit();
    virtual void registerWithTouchDispatcher(void);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void setBackgroundPosition(const CCPoint &pPosition);
    
    CC_SYNTHESIZE_READONLY(CCMenu*, mPopupMenu, PopupMenu);
    CC_SYNTHESIZE_READONLY(CCSprite*, mBackgroundSprite, BackgroundSprite);
    
protected:
    virtual void addSprites();
    virtual void addLabels();
    virtual void addMenuItems();
    virtual void addProgressBars();
    virtual void addActions();
    virtual void onActionShowFinished();

    void show();
    void hide();

private:
    void removeFromParent();
    void exitMenuItemCallback(CCObject* pSender);
    void setBackground();

    string mBackgroundImage;
    string mExitNormalImage;
    string mExitSelectedImage;
    
    CCMenuItem* mExitMenuItem;
    
    CCPoint mExitPostion;
};



#endif /* defined(__DragonVideoPoker__PopUpLayer__) */
