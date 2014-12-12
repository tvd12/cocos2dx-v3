//
//  PopUpLayer.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#include <climits>

#include "PopUpLayer.h"

PopupLayer::PopupLayer() :
mExitNormalImage(""),
mExitSelectedImage(""),
mExitMenuItem(NULL),
mPopupMenu(NULL),
mBackgroundSprite(NULL) {
    
}

PopupLayer* PopupLayer::create(string pBackgroundImage,
                               string pExitNormalImage,
                               string pExitSelectedImage,
                               const Point &pExitPostion) {
    PopupLayer *pRet = new PopupLayer();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage, pExitPostion);
    pRet->autorelease();
    
    return pRet;
}

bool PopupLayer::init(string pBackgroundImage,
                      string pExitImageNormal,
                      string pExitImageSelected,
                      const Point &pExitPostion) {
    Layer::init();
    this->setPosition(Point::ZERO);
    this->mBackgroundImage = pBackgroundImage;
    this->mExitNormalImage = pExitImageNormal;
    this->mExitSelectedImage = pExitImageSelected;
    this->mExitPostion = pExitPostion;
    this->setBackground();
    this->addMenuItems();
    this->addSprites();
    this->addLabels();
    this->addProgressBars();
    this->addTables();
    this->initTouch();
    return true;
}

void PopupLayer::initTouch() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    mTouchListener = EventListenerTouchOneByOne::create();
    mTouchListener->setSwallowTouches(true);
    mTouchListener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
    mTouchListener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
    mTouchListener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
    mTouchListener->onTouchCancelled = CC_CALLBACK_2(PopupLayer::onTouchCancelled, this);
    
//    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    dispatcher->addEventListenerWithFixedPriority(mTouchListener, INT_MIN + 101);
}

void PopupLayer::setBackground()
{
    GLView* pEGLView = Director::getInstance()->getOpenGLView();
    Size frameSize = pEGLView->getFrameSize();
    
    Sprite *colorBG = Sprite::create();
    colorBG->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    colorBG->setColor(Color3B::BLACK);
    colorBG->setOpacity(150);
    colorBG->setPosition(Point(0, 0));
    colorBG->setScale(2.0f);
    this->addChild(colorBG);
    
    if (mBackgroundImage.size() > 0) {
        mBackgroundSprite = Sprite::create(mBackgroundImage.c_str());
        this->addChild(mBackgroundSprite);
    }
    else {
        mBackgroundSprite = Sprite::create();
        this->addChild(mBackgroundSprite);
    }
}

void PopupLayer::addSprites() {

}

void PopupLayer::addLabels() {
    
}

void PopupLayer::addProgressBars() {
    
}

void PopupLayer::addActions() {
    
}

void PopupLayer::addTables() {
    
}

void PopupLayer::addMenuItems() {
    mPopupMenu = Menu::create();
    if(mExitNormalImage.compare("") > 0) {
        if(mExitSelectedImage.compare("") <= 0) {
            mExitSelectedImage = mExitNormalImage;
        }
        mExitMenuItem = MenuItemSprite::create(Sprite::create(mExitNormalImage.c_str()),
                                                 Sprite::create(mExitSelectedImage.c_str()),
                                                 CC_CALLBACK_1(PopupLayer::exitMenuItemCallback,
                                                               this));
        mExitMenuItem->setPosition(mExitPostion);
        mPopupMenu->addChild(mExitMenuItem, 1000);
    }
    mPopupMenu->setPosition(Point::ZERO);
    mBackgroundSprite->addChild(mPopupMenu);
}

void PopupLayer::setBackgroundPosition(const Point &pPosition) {
    mBackgroundSprite->setPosition(pPosition);
}

bool PopupLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {
    if(mBackgroundSprite) {
        Point touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
        touchPoint = mBackgroundSprite->convertToNodeSpace(touchPoint);
        Rect backgroundRect= Rect(mBackgroundSprite->getOffsetPosition().x,
                                      mBackgroundSprite->getOffsetPosition().y,
                                      mBackgroundSprite->getTextureRect().size.width,
                                      mBackgroundSprite->getTextureRect().size.height);
        if(!backgroundRect.containsPoint(touchPoint)) {
            this->hide();
        }
    }
    return true;
}

void PopupLayer::show() {
    mBackgroundSprite->setScale(0.75f);
    mBackgroundSprite->setOpacity(150);
    
    ScaleTo *scaleTo = ScaleTo::create(POP_UP_SHOW_ANIMATION_DURATION, 1.0f);
    FadeIn *fadeIn = FadeIn::create(POP_UP_SHOW_ANIMATION_DURATION);
    Spawn *spawn = Spawn::create(scaleTo, fadeIn, NULL);
    CallFuncN *finishAction
    = CallFuncN::create(CC_CALLBACK_0(PopupLayer::onActionShowFinished, this));
    Sequence *sequence = Sequence::create(spawn, finishAction, NULL);
    
    mBackgroundSprite->runAction(sequence);
}

void PopupLayer::onActionShowFinished()
{
    addActions();
}

void PopupLayer::hide() {
    ScaleTo *scaleTo = ScaleTo::create(POP_UP_HIDE_ANIMATION_DURATION, 0.75f);
    FadeOut *fadeOut = FadeOut::create(POP_UP_HIDE_ANIMATION_DURATION);
    Spawn *spawn = Spawn::create(scaleTo, fadeOut, NULL);
    CallFuncN *remove =
    CallFuncN::create(CC_CALLBACK_0(PopupLayer::removeFromParent, this));
    Action *action = Sequence::create(spawn, remove, NULL);
    
    mBackgroundSprite->runAction(action);
}

void PopupLayer::onEnter()
{
    Layer::onEnter();
    show();
}

void PopupLayer::onExit() {
    Layer::onExit();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(mTouchListener);
}

void PopupLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {
    Layer::onTouchMoved(pTouch, pEvent);
    
}
void PopupLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {
    Layer::onTouchEnded(pTouch, pEvent);
}
void PopupLayer::onTouchCancelled(Touch *pTouch, Event *pEvent) {
    Layer::onTouchCancelled(pTouch, pEvent);
}

void PopupLayer::exitMenuItemCallback(Ref* pSender) {
    this->hide();
}

void PopupLayer::removeFromParent() {
    this->removeFromParentAndCleanup(true);
}
