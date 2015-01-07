//
//  WordLayer.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/11/14.
//
//

#include "WordLayer.h"

#include "cocos-ext.h"

#define LINE_SPACE          40

static Vec2 s_tCurPos = Vec2::ZERO;

TestController::TestController() :
_beginPos(Vec2::ZERO) {
}

Scene* TestController::createScene() {
    Scene* scene = Scene::create();
    TestController* la = new TestController;
    la->autorelease();
    la->init();
    
    scene->addChild(la);
    
    return scene;
}

bool TestController::init() {
    Layer::init();
    
    Sprite *hello = Sprite::create("HelloWorld.png");
    hello->setPosition(Vec2(240, 160));
    this->addChild(hello);
    
    std::string text = std::string() +
                                   "Police have said they plan" +
                                   "to dismantle the camp of colorful" +
                                   "tents and art installations Thursday" +
                                   "morning, urging protesters to leave" +
                                   "peacefully."+ "On Thursday morning," +
                                   "bailiffs read out the court injunction," +
                                   "telling demonstrators to pack up and" +
                                   "leave on their own accord. They then"
                                   "began dismantling and removing barricades"
                                   "at the far western end of the protest area." +
                                   "The bailiffs carried off metal and plastic" +
                                   "barriers that had been lashed together, as" +
                                   "well as broken umbrellas -- wilted versions" +
                                   "of the protest movement's symbol.";
    
    textLabel = Label::createWithTTF(text,
                                    "fonts/Skranji-Regular.ttf",
                                    24);
    textLabel->setAnchorPoint(Vec2(0, 1));
    textLabel->setPosition(Vec2(0, 300));
    textLabel->setDimensions(300, 500);
    textLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
//    textLabel->enableOutline(Color4B(52, 26, 7, 255), 1);
    textLabel->enableShadow(Color4B(52, 26, 7, 255), Size(-0.5f, -0.5f));
//    this->addChild(textLabel);


    CCLOG("content size = (%f, %f)", textLabel->getContentSize().width,
          textLabel->getContentSize().height);
    
    auto clipper = ClippingNode::create();
    clipper->setTag( 98 );
    clipper->setContentSize(  Size(300, 300) );
    clipper->setAnchorPoint(  Vec2(0.5, 0.5) );
    clipper->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
//    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);
    
    auto stencil = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(clipper->getContentSize().width, 0);
    rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = Vec2(0, clipper->getContentSize().height);
    
    Color4F white(1, 1, 1, 1);
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);
    
//    auto content = Sprite::create();
//    content->setContentSize(Size(300, 300));
//    content->setTag( 97 );
//    content->setAnchorPoint(  Vec2(0.5, 0.5) );
//    content->setPosition(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2);
    clipper->addChild(textLabel);
//    content->addChild(textLabel);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TestController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TestController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TestController::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    rapidjson::Document json;
    std::string stdstr = std::string("{ \"hello\" : \"world\" }").c_str();
    char str[2048];
    sprintf(str, "%s", stdstr.c_str());
    
    json.Parse<0>(str);
    
    const char key[] = "hello";
    CCLOG("json value = %s", json[key].GetString());
    
    return true;
}


bool TestController::onTouchBegan(Touch* touch, Event  *event)
{
    _beginPos = touch->getLocation();
    return true;
}

void TestController::onTouchMoved(Touch* touch, Event  *event)
{
    auto touchLocation = touch->getLocation();
    
    float nMoveY =  _beginPos.y - touchLocation.y;
    textLabel->setPosition(Vec2(textLabel->getPositionX(),
                           textLabel->getPositionY() - nMoveY));
    
    _beginPos = touchLocation;
//    s_tCurPos   = nextPos;
}

void TestController::onTouchEnded(Touch *touch, Event *unused_event) {
    if(textLabel->getPositionY() < 300) {
        textLabel->runAction(Sequence::create(MoveTo::create(0.15, Vec2(0, 300)), NULL));
    }
    else if(textLabel->getPositionY() > 500) {
        textLabel->runAction(Sequence::create(MoveTo::create(0.15, Vec2(0, 500)), NULL));
    }
}