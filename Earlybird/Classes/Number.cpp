//
//  Number.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#include "Number.h"
#include "AtlasLoader.h"

NumberSeries::NumberSeries() :
mNumberOfSeries(vector<SpriteFrame*>()) {
    
}

NumberSeries* NumberSeries::create() {
    NumberSeries* pRet = new NumberSeries;
    pRet->init();
    
    return pRet;
}

bool NumberSeries::init() {    
    return true;
}

void NumberSeries::loadNumber(string fmt, int base) {
    for(int i = base ; i < 10 + base ; i++) {
        string filename = StringUtils::format(fmt.c_str(), i);
        auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
        mNumberOfSeries.push_back(frame);
    }
}

SpriteFrame* NumberSeries::at(int index) {
    return mNumberOfSeries.at(index);
}

NumberSeries::~NumberSeries() {
    mNumberOfSeries.clear();
}

Number::Number() :
mNumberContainer(map<string, NumberSeries*>()){
    
}

Number* Number::getInstance() {
    static Number sInstance;
    
    return &sInstance;
}

void Number::destroyInstance() {
    
}

bool Number::init() {
    return true;
}

bool Number::loadNumber(string name, string fmt, int base) {
    auto numberSeries = NumberSeries::create();
    numberSeries->loadNumber(fmt, base);
    mNumberContainer.insert(pair<string, NumberSeries*>(name, numberSeries));
    
    return true;
}

Node* Number::convert(string name, int number, Gravity gravity) {
    auto numbers = mNumberContainer.at(name);
    if(number == 0) {
        auto numberZero = Sprite::createWithSpriteFrame(numbers->at(0));
        numberZero->setAnchorPoint(Vec2(0.5, 0));
        
        return numberZero;
    }
    
    auto numberNode = Node::create();
    float totalWidth = 0;
    while(number) {
        int temp = number % 10;
        number /= 10;
        auto sprite = Sprite::createWithSpriteFrame(numbers->at(temp));
        totalWidth += sprite->getContentSize().width;
        numberNode->addChild(sprite);
    }
    
    auto numberZero = Sprite::createWithSpriteFrame(numbers->at(0));
    numberNode->setContentSize(Size(totalWidth,
                                    numberZero->getContentSize().height));
    if(gravity == Gravity::GRAVITY_CENTER) {
        float singleWidth = totalWidth / numberNode->getChildrenCount();
        int index = numberNode->getChildrenCount() / 2;
        for(auto child : numberNode->getChildren()) {
            child->setAnchorPoint(Vec2(0.5f, 0));
            float offLength = singleWidth * index --;
            child->setPositionX(offLength);
        }
    }
    else if (gravity == Gravity::GRAVITY_RIGHT) {
        float singleWidth = totalWidth / numberNode->getChildrenCount();
        int index = numberNode->getChildrenCount();
        for(auto child : numberNode->getChildren()) {
            child->setAnchorPoint(Point(1, 0));
            float offLength = singleWidth * index --;
            child->setPositionX(offLength);
        }
    }
    else if(gravity == Gravity::GRAVITY_LEFT) {
        float singleWidth = totalWidth / numberNode->getChildrenCount();
        int index = 0;
        for(auto child : numberNode->getChildren()) {
            child->setAnchorPoint(Point::ZERO);
            float offLength = singleWidth * index ++;
            child->setPositionX(offLength);
        }
    }
    
    return numberNode;
}

Number::~Number() {
    
}