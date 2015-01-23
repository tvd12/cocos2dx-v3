//
//  LabelTest.h
//  MyTestProject
//
//  Created by Dung Ta Van on 1/23/15.
//
//

#ifndef __MyTestProject__LabelTest__
#define __MyTestProject__LabelTest__

#include "CommonLayer.h"

class LabelTest : public CommonLayer {
public:
    
    virtual bool init();
    
    CREATE_FUNC(LabelTest);
    CREATE_SCENE_FUNC(LabelTest);
};

#endif /* defined(__MyTestProject__LabelTest__) */
