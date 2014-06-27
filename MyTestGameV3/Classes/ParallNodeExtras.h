//
//  ParallNodeExtras.h
//  MyTestGameV3
//
//  Created by Ta Van Dung on 1/21/14.
//
//

#ifndef __MyTestGameV3__ParallNodeExtras__
#define __MyTestGameV3__ParallNodeExtras__

#include "cocos2d.h"

using namespace cocos2d;

class ParallNodeExtras : public ParallaxNode {

public:
    //Need to provide a constructor
    ParallNodeExtras();
    
    //just to avoid ugly later cast and also for safety
    static ParallNodeExtras* node();
    
    //Facility method
    void incrementOffset(Point offset, Node* node);
};

#endif /* defined(__MyTestGameV3__ParallNodeExtras__) */
