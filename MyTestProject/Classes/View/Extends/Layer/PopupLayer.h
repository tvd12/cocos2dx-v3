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

class PopupLayer : public Layer {
public:
    PopupLayer();
    static PopupLayer* create(string pBackgroundImage,
                              string pExitNormalImage = "",
                              string pExitSelectedImage = "",
                              const Point &pExitPostion = Point::ZERO);
    virtual bool init(string pBackgroundImage,
                      string pExitNormalImage = "",
                      string pExitSelectedImage = "",
                      const Point &pExitPostion = Point::ZERO);
    virtual void onEnter();
    virtual void onExit();
    
    // CCLayer
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
    
    void setBackgroundPosition(const Point &pPosition);
    
    CC_SYNTHESIZE_READONLY(Menu*, mPopupMenu, PopupMenu);
    CC_SYNTHESIZE_READONLY(Sprite*, mBackgroundSprite, BackgroundSprite);
    
protected:
    virtual void initTouch();
    virtual void addSprites();
    virtual void addLabels();
    virtual void addTables();
    virtual void addMenuItems();
    virtual void addProgressBars();
    virtual void addActions();
    virtual void onActionShowFinished();

    void show();
    void hide();

protected:
    void removeFromParent();
    void exitMenuItemCallback(Ref* pSender);
    void setBackground();

    string mBackgroundImage;
    string mExitNormalImage;
    string mExitSelectedImage;
    
    MenuItem* mExitMenuItem;
    
    Point mExitPostion;
    
    EventListenerTouchOneByOne *mTouchListener;
};



#endif /* defined(__DragonVideoPoker__PopUpLayer__) */
