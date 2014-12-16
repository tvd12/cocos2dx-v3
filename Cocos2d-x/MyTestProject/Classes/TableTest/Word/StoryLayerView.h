//
//  StoryLayerView.h
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 12/11/14.
//
//

#ifndef __SupernaturalMemory__StoryLayerView__
#define __SupernaturalMemory__StoryLayerView__

#include "PopupLayer.h"

#include "cocos2d.h"

using namespace cocos2d;

class StoryPopupView : public PopupLayer {
public:
    static StoryPopupView* create();
    
    virtual bool init();
    
    CC_SYNTHESIZE(Label*, mTextLabel, TextLabel);

protected:
    
    virtual void addSprites();
    virtual void addMenuItems();
    virtual void addLabels();
    
private:
    void storyPopupCallback(Ref* pSender);
};

#endif /* defined(__SupernaturalMemory__StoryLayerView__) */
