//
//  OptionLayer.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/13/15.
//
//

#ifndef __Earlybird__OptionLayer__
#define __Earlybird__OptionLayer__

#include "cocos2d.h"

using namespace cocos2d;

class OptionDelegate {
public:
    virtual void onTouch() = 0;
};

class OptionLayer : public Layer {
public:
    
    OptionLayer();
    
    virtual bool init();
    
    // override
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(OptionDelegate*, mDelegate, Delegate);
    
    CREATE_FUNC(OptionLayer);
    
    ~OptionLayer();
};

#endif /* defined(__Earlybird__OptionLayer__) */
