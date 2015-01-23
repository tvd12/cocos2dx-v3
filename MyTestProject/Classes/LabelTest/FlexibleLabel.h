//
//  FlexibleLabel.h
//  MyTestProject
//
//  Created by Dung Ta Van on 1/23/15.
//
//

#ifndef __MyTestProject__FlexibleLabel__
#define __MyTestProject__FlexibleLabel__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class FlexibleLabel {
    
public:
    
    FlexibleLabel();
    
    static FlexibleLabel* create(const string &str,
                                 const string &fontName,
                                 float fontSize,
                                 int visibleLength,
                                 const string &ext = "...");
    
    virtual bool init(const string &str,
                      const string &fontName,
                      float fontSize,
                      int visibleLength,
                      const string &ext);
    
    virtual void setPosition(const Vec2& position);
    
    virtual void addToParent(Node* parent, int z_order = 0, int tag = 0);
    
    virtual string getVisibleString();
    
    CC_SYNTHESIZE(string, mExt, Ext);
    CC_SYNTHESIZE(string, mString, String);
    CC_SYNTHESIZE(int, mVisibleLength, VisibleLength);
    
    CC_SYNTHESIZE_READONLY(Label*, mGraphic, Graphics);
    
};

#endif /* defined(__MyTestProject__FlexibleLabel__) */
