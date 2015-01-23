//
//  LabelTest.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 1/23/15.
//
//

#include "LabelTest.h"
#include "FlexibleLabel.h"

bool LabelTest::init() {
    CommonLayer::init();
    
    FlexibleLabel* flabel = FlexibleLabel::create("12345678",
                                                  "fonts/Skranji-Bold.ttf",
                                                  17,
                                                  8);
    
    flabel->setPosition(Vec2(240, 160));
    
    flabel->addToParent(this);
    
    return true;
}