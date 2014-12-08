//
//  SqliteTestScene.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/4/14.
//
//

#ifndef __MyTestProject__SqliteTestScene__
#define __MyTestProject__SqliteTestScene__

#include "cocos2d.h"

using namespace cocos2d;

class SqliteTestScene : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SqliteTestScene);
};

#endif /* defined(__MyTestProject__SqliteTestScene__) */
