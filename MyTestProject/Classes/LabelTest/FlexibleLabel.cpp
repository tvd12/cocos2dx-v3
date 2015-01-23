//
//  FlexibleLabel.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 1/23/15.
//
//

#include "FlexibleLabel.h"

FlexibleLabel::FlexibleLabel() :
mGraphic(NULL) {
    
}

FlexibleLabel* FlexibleLabel::create(const string &str,
                                     const string &fontName,
                                     float fontSize,
                                     int visibleLength,
                                     const string &ext) {
    FlexibleLabel* pRet = new FlexibleLabel;
    pRet->init(str, fontName, fontSize, visibleLength, ext);
    
    return pRet;
}

bool FlexibleLabel::init(const string &str,
                         const string &fontName,
                         float fontSize,
                         int visibleLength,
                         const string &ext) {
    mExt = ext;
    mVisibleLength = visibleLength;
    setString(str);
    setExt(ext);
    setVisibleLength(visibleLength);
    
    mGraphic = Label::createWithTTF(getVisibleString(),
                                    fontName,
                                    fontSize);
    
    return true;
}

void FlexibleLabel::addToParent(cocos2d::Node *parent, int zorder, int tag) {
    parent->addChild(getGraphics(), zorder, tag);
}

void FlexibleLabel::setPosition(const cocos2d::Vec2 &position) {
    getGraphics()->setPosition(position);
}

string FlexibleLabel::getVisibleString() {
    
    if(getString().length() <= getVisibleLength()) {
        return getString();
    }
    
    string newstr = string(getString(), 0, getVisibleLength())
    .append(getExt());
    
    return newstr;
}