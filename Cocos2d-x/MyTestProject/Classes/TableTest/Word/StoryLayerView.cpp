//
//  StoryLayerView.cpp
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 12/11/14.
//
//

#include "StoryLayerView.h"

StoryPopupView* StoryPopupView::create() {
    StoryPopupView* pRet = new StoryPopupView;
    pRet->autorelease();
    pRet->init();
    
    return pRet;
}

bool StoryPopupView::init() {
    PopupLayer::init("HelloWorld.png");
    
    getBackgroundSprite()->setPosition(Director::getInstance()->getVisibleSize()/2);
    
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
    
    Label* textLabel = Label::createWithTTF(text,
                                     "fonts/VNF-Oswald_Regular.ttf",
                                     24);
    textLabel->setAnchorPoint(Vec2(0, 1));
    textLabel->setPosition(Vec2(0, 300));
    textLabel->setDimensions(300, 500);
    textLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    //    this->addChild(textLabel);
    
    
    CCLOG("content size = (%f, %f)", textLabel->getContentSize().width,
          textLabel->getContentSize().height);
    
    auto clipper = ClippingNode::create();
    clipper->setTag( 98 );
    clipper->setContentSize(  Size(300, 300) );
    clipper->setAnchorPoint(  Vec2(0.5, 0.5) );
    clipper->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    //    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    mBackgroundSprite->addChild(clipper);
//    mBackgroundSprite->setPosition(240, 160);
    
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
    
    return true;
}

void StoryPopupView::addSprites() {
    PopupLayer::addSprites();
}

void StoryPopupView::addMenuItems() {
    PopupLayer::addMenuItems();
}

void StoryPopupView::addLabels() {
    PopupLayer::addLabels();
    
//    mTextLabel = Label::createWithTTF(D::string.story_popup_story_text,
//                                     DEFAULT_STORY_FONT_FILE,
//                                     26);
//    mTextLabel->setAnchorPoint(Vec2(0, 1));
//    mTextLabel->setColor(Color3B(0, 0, 0));
//    mTextLabel->setPosition(GPARAMS()->POPUP_STORY_TEXT_POSITION);
//    mTextLabel->setDimensions(GPARAMS()->POPUP_STORY_TEXT_DIMENSION.width,
//                              GPARAMS()->POPUP_STORY_TEXT_DIMENSION.height);
//    mTextLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
//
//    auto clipper = ClippingNode::create();
//    clipper->setContentSize(GPARAMS()->POPUP_STORY_VISIBLE_SIZE);
//    clipper->setAnchorPoint( Vec2(0.5, 0.5) );
//    clipper->setPosition(mBackgroundSprite->getContentSize()/2);
//    mBackgroundSprite->addChild(clipper);
//    
//    auto stencil = DrawNode::create();
//    Vec2 rectangle[4];
//    rectangle[0] = Vec2(0, 0);
//    rectangle[1] = Vec2(clipper->getContentSize().width, 0);
//    rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
//    rectangle[3] = Vec2(0, clipper->getContentSize().height);
//    
//    Color4F white(1, 1, 1, 1);
//    stencil->drawPolygon(rectangle, 4, white, 1, white);
//    clipper->setStencil(stencil);
//    clipper->addChild(mTextLabel);
}

void StoryPopupView::storyPopupCallback(cocos2d::Ref *pSender) {
//    MenuItem* menuItem = static_cast<MenuItem*>(pSender);
}