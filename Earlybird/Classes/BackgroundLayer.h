//
//  BackgroundLayer.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#ifndef __Earlybird__BackgroundLayer__
#define __Earlybird__BackgroundLayer__

#include <ctime>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class BackgroundLayer : public Layer {
public:
    BackgroundLayer();
    
    virtual bool init();
    
    static float getLandHeight();
    
    CREATE_FUNC(BackgroundLayer);
    
    ~BackgroundLayer();
};

#endif /* defined(__Earlybird__BackgroundLayer__) */
