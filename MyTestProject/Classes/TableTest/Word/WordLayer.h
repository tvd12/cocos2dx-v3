//
//  WordLayer.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/11/14.
//
//

#ifndef __MyTestProject__WordLayer__
#define __MyTestProject__WordLayer__

#include "cocos2d.h"

USING_NS_CC;

class TestController : public Layer
{
public:
    TestController();
    
    static Scene* createScene();
    
    virtual bool init();
    
    bool onTouchBegan(Touch* touches, Event  *event);
    void onTouchMoved(Touch* touches, Event  *event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    CREATE_FUNC(TestController);
    
private:
    Vec2 _beginPos;
    Label *textLabel;
};

#endif /* defined(__MyTestProject__WordLayer__) */
