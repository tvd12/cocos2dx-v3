//
//  EndGamePopup.h
//  MyTestGameV3
//
//  Created by Ta Van Dung on 1/23/14.
//
//

#ifndef __MyTestGameV3__EndGamePopup__
#define __MyTestGameV3__EndGamePopup__

#include "cocos2d.h"

using namespace cocos2d;

class EndGamePopup : public Layer {
public:
    EndGamePopup();
    bool init() override;
    void onExit();
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    void backCallback(Object* sender);
    bool isExitGame = false;
    
    void createCallback();
    
    CREATE_FUNC(EndGamePopup);
private:
    MenuItemImage *cancelButton;
    LabelTTF* cancelLabel;
    int count = 1;
    Sprite* pSprite;
};

#endif /* defined(__MyTestGameV3__EndGamePopup__) */
