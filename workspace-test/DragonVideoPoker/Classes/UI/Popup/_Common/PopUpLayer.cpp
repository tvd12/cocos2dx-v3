//
//  PopUpLayer.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#include "PopUpLayer.h"
#include "SoundManager.h"


PopUpLayer::PopUpLayer() :
mExitNormalImage(""),
mExitSelectedImage(""),
mExitMenuItem(NULL),
mPopupMenu(NULL),
mBackgroundSprite(NULL) {
    
}

PopUpLayer* PopUpLayer::create(string pBackgroundImage,
                               string pExitNormalImage,
                               string pExitSelectedImage,
                               const CCPoint &pExitPostion) {
    PopUpLayer *pRet = new PopUpLayer();
    pRet->init(pBackgroundImage, pExitNormalImage, pExitSelectedImage, pExitPostion);
    pRet->autorelease();
    
    return pRet;
}

bool PopUpLayer::init(string pBackgroundImage,
                      string pExitImageNormal,
                      string pExitImageSelected,
                      const CCPoint &pExitPostion) {
    CCLayer::init();
    this->setPosition(CCPointZero);
    this->mBackgroundImage = pBackgroundImage;
    this->mExitNormalImage = pExitImageNormal;
    this->mExitSelectedImage = pExitImageSelected;
    this->mExitPostion = pExitPostion;
    this->setBackground();
    this->addSprites();
    this->addMenus();
    this->addMenuItems();
    this->addLabels();
    this->addProgressBars();
    this->addTables();
    this->setTouchEnabled(true);
    return true;
}

void PopUpLayer::setBackground() {
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCSize frameSize = pEGLView->getFrameSize();
    
    CCSprite *colorBG = CCSprite::create();
    colorBG->setTextureRect(CCRect(0, 0, frameSize.width, frameSize.height));
    colorBG->setColor(ccBLACK);
    colorBG->setOpacity(150);
    colorBG->setPosition(CCPoint(0, 0));
    colorBG->setScale(2.0f);
    this->addChild(colorBG);
    
    mBackgroundSprite = CCSprite::create(mBackgroundImage.c_str());
    this->addChild(mBackgroundSprite);
}

void PopUpLayer::addSprites() {

}

void PopUpLayer::addLabels() {
    
}

void PopUpLayer::addProgressBars() {
    
}

void PopUpLayer::addActions() {
    
}

void PopUpLayer::addTables() {
    
}

void PopUpLayer::addMenus() {
    
}

void PopUpLayer::addMenuItems() {
    mPopupMenu = CCMenu::create();
    if(mExitNormalImage.compare("") > 0) {
        if(mExitSelectedImage.compare("") <= 0) {
            mExitSelectedImage = mExitNormalImage;
        }
        mExitMenuItem = CCMenuItemSprite::create(CCSprite::create(mExitNormalImage.c_str()),
                                                 CCSprite::create(mExitSelectedImage.c_str()),
                                                 this,
                                                 menu_selector(PopUpLayer::exitMenuItemCallback));
        mExitMenuItem->setPosition(mExitPostion);
        mPopupMenu->addChild(mExitMenuItem);
    }
    mPopupMenu->setTouchPriority(kCCMenuHandlerPriority - 102);
    mPopupMenu->setPosition(CCPointZero);
    mBackgroundSprite->addChild(mPopupMenu);
}

void PopUpLayer::setBackgroundPosition(const CCPoint &pPosition) {
    mBackgroundSprite->setPosition(pPosition);
}

void PopUpLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()
    ->getTouchDispatcher()
    ->addTargetedDelegate(this,
                          kCCMenuHandlerPriority - 101,
                          true);
}

bool PopUpLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if(mExitMenuItem) {
        CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        touchPoint = mBackgroundSprite->convertToNodeSpace(touchPoint);
        CCRect backgroundRect= CCRect(mBackgroundSprite->getOffsetPosition().x,
                                      mBackgroundSprite->getOffsetPosition().y,
                                      mBackgroundSprite->getTextureRect().size.width,
                                      mBackgroundSprite->getTextureRect().size.height);
        if(!backgroundRect.containsPoint(touchPoint)) {
            this->hide();
        }
    }
    return true;
}

void PopUpLayer::show() {
    mBackgroundSprite->setScale(0.75f);
    mBackgroundSprite->setOpacity(150);
    
    CCScaleTo *scaleTo = CCScaleTo::create(POP_UP_SHOW_ANIMATION_DURATION, 1.0f);
    CCFadeIn *fadeIn = CCFadeIn::create(POP_UP_SHOW_ANIMATION_DURATION);
    CCSpawn *spawn = CCSpawn::create(scaleTo, fadeIn, NULL);
    CCCallFuncN *finishAction = CCCallFuncN::create(this, callfuncN_selector(PopUpLayer::onActionShowFinished));
    CCSequence *sequence = CCSequence::create(spawn, finishAction, NULL);
    
    mBackgroundSprite->runAction(sequence);
}

void PopUpLayer::onActionShowFinished()
{
    addActions();
}

void PopUpLayer::hide() {
    CCScaleTo *scaleTo = CCScaleTo::create(POP_UP_HIDE_ANIMATION_DURATION, 0.75f);
    CCFadeOut *fadeOut = CCFadeOut::create(POP_UP_HIDE_ANIMATION_DURATION);
    CCSpawn *spawn = CCSpawn::create(scaleTo, fadeOut, NULL);
    CCCallFuncN *remove =
    CCCallFuncN::create(this,
                        callfuncN_selector(PopUpLayer::removeFromParent));
    CCAction *action = CCSequence::create(spawn, remove, NULL);
    
    mBackgroundSprite->runAction(action);
}

void PopUpLayer::onEnter()
{
    CCLayer::onEnter();
    show();
}

void PopUpLayer::onExit() {
    CCLayer::onExit();
}

void PopUpLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchMoved(pTouch, pEvent);
    
}
void PopUpLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch, pEvent);
}
void PopUpLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchCancelled(pTouch, pEvent);
}

void PopUpLayer::exitMenuItemCallback(CCObject* pSender) {
    SOUND().playSound(SOUND_BUTTON_CLICK);
    this->hide();
}

void PopUpLayer::removeFromParent() {
    this->removeFromParentAndCleanup(true);
}
