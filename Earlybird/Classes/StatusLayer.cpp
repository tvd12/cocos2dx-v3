//
//  StatusLayer.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#include "StatusLayer.h"
#include "Number.h"
#include "AtlasLoader.h"
#include "GameScene.h"

StatusLayer::StatusLayer() :
mBlink(NULL),
mScoreSprite(NULL),
mGetreadySprite(NULL),
mTutorialSprite(NULL),
mWhiteSprite(NULL),
mCurrentScore(0),
mBestScore(0),
mTmpScore(0),
mIsNewRecord(false),
mOriginPoint(),
mVisibleSize()
{
    
}

bool StatusLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    // init numbers
    mBestScore = 0;
    mCurrentScore = 0;
    mIsNewRecord = false;
    Number::getInstance()->loadNumber(NUMBER_FONT, "font_0%02d", 48);
    Number::getInstance()->loadNumber(NUMBER_SCORE, "number_score_%02d");
    mVisibleSize = Director::getInstance()->getVisibleSize();
    mOriginPoint = Director::getInstance()->getVisibleOrigin();
    
    showReadyStatus();
    loadWhiteSprite();
    
    return true;
}

void StatusLayer::showReadyStatus() {
    mScoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT, 0);
    mScoreSprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                                   mOriginPoint.y + mVisibleSize.height * 5 / 6));
    this->addChild(mScoreSprite);
    
    mGetreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                    ->getSpriteFrameByName("text_ready"));
    mGetreadySprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                                      mOriginPoint.y + mVisibleSize.height * 2 / 3));
    this->addChild(mGetreadySprite);
    
    mTutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                    ->getSpriteFrameByName("tutorial"));
    mTutorialSprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                                      mOriginPoint.y + mVisibleSize.height * 1 / 2));
    this->addChild(mTutorialSprite);
}

void StatusLayer::showStartStatus() {
    mGetreadySprite->runAction(FadeOut::create(0.4f));
    mTutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int bestScore) {
    mCurrentScore = curScore;
    mBestScore = bestScore;
    if(curScore > bestScore) {
        mBestScore = curScore;
        mIsNewRecord = true;
    }
    else {
        mIsNewRecord = false;
    }
    
    removeChild(mScoreSprite);
    blinkFullScreen();
}

void StatusLayer::onGameStart() {
    showStartStatus();
}

void StatusLayer::onGamePlaying(int score) {
    removeChild(mScoreSprite);
    mScoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT, score);
    mScoreSprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                                   mOriginPoint.y + mVisibleSize.height * 5 / 6));
    this->addChild(mScoreSprite);
}

void StatusLayer::onGameEnd(int currentScore, int bestScore) {
    showOverStatus(currentScore, bestScore);
}

void StatusLayer::loadWhiteSprite() {
    
    //this white sprite is used for blinking the screen for a short while
    mWhiteSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                 ->getSpriteFrameByName("white"));
    mWhiteSprite->setScale(100);
    mWhiteSprite->setOpacity(0);
    this->addChild(mWhiteSprite, 10000);
}

void StatusLayer::blinkFullScreen() {
   
    //display a flash blink
    auto fadeOut = FadeOut::create(0.1f);
    auto fadeIn = FadeIn::create(0.1f);
    auto blinkAction = Sequence::create(fadeIn, fadeOut, NULL);
    CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
    auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
    mWhiteSprite->stopAllActions();
    mWhiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver() {
    
    // create the game over panel
    Sprite* gameoverSprite =
    Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                  ->getSpriteFrameByName("text_game_over"));
    gameoverSprite->setPosition(Point(this->mOriginPoint.x + this->mVisibleSize.width / 2,
                                      this->mOriginPoint.y + this->mVisibleSize.height * 2 / 3));
    this->addChild(gameoverSprite);
    auto gameoverFadeIn = FadeIn::create(0.5f);
    
    // Start next action
    CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
    auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
    gameoverSprite->stopAllActions();
    gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel() {
    
    // create the score panel
    Sprite* scorepanelSprite =
    Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                  ->getSpriteFrameByName("score_panel"));
    scorepanelSprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                                       mOriginPoint.y - scorepanelSprite->getContentSize().height));
    this->addChild(scorepanelSprite);
    
    // display the best score on the score panel
    auto bestScoreSprite =
    (Sprite*)Number::getInstance()->convert(NUMBER_SCORE,
                                            mBestScore,
                                            Gravity::GRAVITY_RIGHT);
    bestScoreSprite->setAnchorPoint(Vec2(1, 1));
    bestScoreSprite->setPosition(Vec2(scorepanelSprite->getContentSize().width - 28, 50));
    scorepanelSprite->addChild(bestScoreSprite);
    
    string medalsName = this->getMedalsName(mCurrentScore);
    if(medalsName != "") {
        Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                             ->getSpriteFrameByName(medalsName));
        medalsSprite->addChild(mBlink);
        medalsSprite->setPosition(54, 58);
        scorepanelSprite->addChild(medalsSprite);
    }
    
    // if the current score is higher than the best score.
    // the panel will appear a "new" tag.
    if(this->mIsNewRecord){
        Sprite* newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                             ->getSpriteFrameByName("new"));
        newTagSprite->setPosition(-16, 12);
        bestScoreSprite->addChild(newTagSprite);
    }
    
    // start next action
    auto pos = Vec2(mOriginPoint.x + mVisibleSize.width / 2,
                    mOriginPoint.y + mVisibleSize.height / 2 - 10.0f);
    auto scorePanelMoveTo = MoveTo::create(0.8f, pos);
    
    // add variable motion for the action
    auto sineIn = EaseExponentialOut::create(scorePanelMoveTo);
    auto actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::fadeInRestartBtn, this));
    
    auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
    scorepanelSprite->stopAllActions();
    SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
    scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn() {
    Node * tmpNode = Node::create();
    
    //create the restart menu;
    Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
    Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
    restartBtnActive->setPositionY(-4);
    auto  menuItem =
    MenuItemSprite::create(restartBtn,
                           restartBtnActive,
                           NULL,
                           CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
    
    auto menuPos = Vec2(mOriginPoint.x + mVisibleSize.width / 2
                        - restartBtn->getContentSize().width / 2,
                        mOriginPoint.y + mVisibleSize.height * 2 / 7 - 10.0f);
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(menuPos);
    tmpNode->addChild(menu);
    
    //create the rate button. however ,this button is not available yet = =
    Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                                    ->getSpriteFrameByName("button_score"));
    auto rateBtnPos = Vec2(mOriginPoint.x + mVisibleSize.width / 2
                           + rateBtn->getContentSize().width / 2,
                           mOriginPoint.y + mVisibleSize.height * 2 / 7 - 10.0f);
    rateBtn->setPosition(rateBtnPos);
    tmpNode->addChild(rateBtn);
    this->addChild(tmpNode);
    
    //fade in the two buttons
    auto fadeIn = FadeIn::create(0.1f);
    
    CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback, this));
    auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
    tmpNode->stopAllActions();
    tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback(){
    mTmpScore = 0;
    schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt){
    if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
        this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
    }
    mScoreSprite =
    (Sprite *)Number::getInstance()->convert(NUMBER_SCORE,
                                             mTmpScore,
                                             Gravity::GRAVITY_RIGHT);
    mScoreSprite->setAnchorPoint(Point(1, 0));
    mScoreSprite->setPosition(Vec2(mOriginPoint.x + mVisibleSize.width * 3 / 4 + 20.0f,
                                   mOriginPoint.y + mVisibleSize.height *  1 / 2));
    mScoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
    this->addChild(mScoreSprite, 1000);
    
    mTmpScore++;
    if(mTmpScore > mCurrentScore){
        unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
    }
}

void StatusLayer::setBlinkSprite() {
    mBlink = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()
                                           ->getSpriteFrameByName("blink_00"));
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.1f);
    for (int i = 0; i < 3; i++){
        string filename = StringUtils::format("blink_%02d", i);
        SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    for (int i = 2; i >= 0; i--){
        string filename = StringUtils::format("blink_%02d", i);
        SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    auto animate = Animate::create(animation);
    auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
    auto sequence = Sequence::createWithTwoActions(animate, actionDone);
    mBlink->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction() {
    if(mBlink && mBlink->getParent()) {
        Size activeSize = mBlink->getParent()->getContentSize();
        mBlink->setPosition(rand()%((int)(activeSize.width)),
                            rand()%((int)(activeSize.height)));
    }
}

string StatusLayer::getMedalsName(int score){
    this->setBlinkSprite();
    
    //display the golden silver or bronze iron
    string medalsName = "";
    if(mCurrentScore >=10 && mCurrentScore < 20){//iron medals
        medalsName = "medals_0";
    }else if(mCurrentScore >= 20 && mCurrentScore < 30){//bronze medals
        medalsName = "medals_1";
    }else if(mCurrentScore >= 30 && mCurrentScore < 50){//silver medals
        medalsName = "medals_2";
    }else if(mCurrentScore >= 50){//golden medals
        medalsName = "medals_3";
    }
    return medalsName;
}

void StatusLayer::menuRestartCallback(Ref* pSender){
    SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
    auto scene = GameScene::create();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}

StatusLayer::~StatusLayer() {
    
}