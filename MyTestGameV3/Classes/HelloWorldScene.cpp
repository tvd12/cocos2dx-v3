#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    _batchNode = SpriteBatchNode::create("Sprites.pvr.ccz");
    this->addChild(_batchNode);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprites.plist");
    
    Size winSize = Director::getInstance()->getWinSize();
    _ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    _ship->setPosition(Point(winSize.width * 0.1, winSize.height * 0.5));
    
    _batchNode->addChild(_ship, 1);
    
    //Create the ParallaxNode
    _backgroundNode = ParallNodeExtras::node();
    this->addChild(_backgroundNode, -1);
    
    //Create the sprites will be added to the ParallaxNode
    _spacedust1 = Sprite::create("bg_front_spacedust.png");
    _spacedust2 = Sprite::create("bg_front_spacedust.png");
    
    _planetsunrise = Sprite::create("bg_planetsunrise.png");
    _galaxy = Sprite::create("bg_galaxy.png");
    _spacialanomaly = Sprite::create("bg_spacialanomaly.png");
    _spacialanomaly2 = Sprite::create("bg_spacialanomaly2.png");
    
    //Determine relative movement speeds for space dust and background
    Point dustSpeed = Point(0.1, 0.1);
    Point bgSpeed = Point(0.05, 0.05);
    
    //Add children to ParallaxNode
    _backgroundNode->addChild(_spacedust1, 0, dustSpeed, Point(0, winSize.height/2));
    _backgroundNode->addChild(_spacedust2, 0, dustSpeed, Point(_spacedust1->getContentSize().width,
                                                               winSize.height/2));
    _backgroundNode->addChild(_galaxy, -1, bgSpeed, Point(0, winSize.height*0.7));
    _backgroundNode->addChild(_planetsunrise, -1, bgSpeed, Point(600, winSize.height*0));
    _backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, Point(900, winSize.height*0.3));
    _backgroundNode->addChild(_spacialanomaly2, -1, dustSpeed, Point(1500, winSize.height*0.9));
    this->scheduleUpdate();
    
    this->addChild(ParticleSystemQuad::create("Stars1.plist"));
    this->addChild(ParticleSystemQuad::create("Stars2.plist"));
    this->addChild(ParticleSystemQuad::create("Stars3.plist"));
    
    this->setAccelerometerEnabled(true);
    
#define KNUMASTEROIDS 15
    _asteroids = new Vector<Sprite*>();
    for(int i = 0 ; i < KNUMASTEROIDS ; i++) {
        Sprite *asteroid = Sprite::createWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false);
        _batchNode->addChild(asteroid);
        _asteroids->pushBack(asteroid);
    }
#define KNUMBERLASERS 5
    _shipLasers = new Vector<Sprite*>();
    for(int i = 0 ; i < KNUMBERLASERS ; i++) {
        Sprite* shipLaser = Sprite::createWithSpriteFrameName("laserbeam_blue.png");
        shipLaser->setVisible(false);
        _batchNode->addChild(shipLaser);
        _shipLasers->pushBack(shipLaser);
    }
    //this->setTouchEnabled(true);
    _lives = 3;
    double curTime = getTimeTick();
    _gameOverTime = curTime + 30000;
    SimpleAudioEngine::getInstance()->playBackgroundMusic("PokerTheme.mp3", true);
    SimpleAudioEngine::getInstance()->preloadEffect("explosion_large.caf");
    SimpleAudioEngine::getInstance()->preloadEffect("laser_ship.caf");
    SimpleAudioEngine::getInstance()->preloadEffect("shake.caf");
    SimpleAudioEngine::getInstance()->preloadEffect("powerup.caf");
    
    mEndGamePopup = EndGamePopup::create();
    mEndGamePopup->setVisible(false);
    this->addChild(mEndGamePopup);
    
//    auto listener = EventListenerTouchAllAtOnce::create();
//    
//    listener->onTouchesBegan  = [=](const std::vector<Touch*>& touches, Event* event) {
//        if((static_cast<EndGamePopup*>(event->getCurrentTarget())) != mEndGamePopup) {
//            HelloWorld::touchesBegan(touches, event);
//        } else {
//            log("end game popup");
//        }
//    };
//    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->setTag(998);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        HelloWorld::touchesBegan(touch, event);
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), mEndGamePopup);
    return true;
}

void HelloWorld::onAccelerate(Acceleration *pAcceleration) {
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.6
#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
#define KMAXDIFFX 0.2
    double rollingX;
    
    //Cocos2DX inverts X and Y accelerometer depending on device orientation
    //in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAcceleration->x = pAcceleration->y;
    rollingX = (pAcceleration->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAcceleration->x - rollingX;
    Size winSize = Director::getInstance()->getWinSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

void HelloWorld::update(float dt) {
    Point backgroundScrollVert = Point(-1000, 0);
    _backgroundNode->setPosition(_backgroundNode->getPosition() + (backgroundScrollVert * dt));
    
    auto *spaceDusts = new Vector<Sprite*>();
    spaceDusts->pushBack(_spacedust1);
    spaceDusts->pushBack(_spacedust2);
    for(int i = 0 ; i < spaceDusts->size() ; i++) {
        Sprite *spaceDust = spaceDusts->at(i);
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
        float size = spaceDust->getContentSize().width;
        if(xPosition < -size/2) {
            _backgroundNode->incrementOffset(Point(spaceDust->getContentSize().width*2, 0),
                                             spaceDust);
        }
    }
    
    delete spaceDusts;
    
    auto *backGrounds = new Vector<Sprite*>();
    backGrounds->pushBack(_galaxy);
    backGrounds->pushBack(_planetsunrise);
    backGrounds->pushBack(_spacialanomaly);
    backGrounds->pushBack(_spacialanomaly2);
    for(int i = 0 ; i < backGrounds->size() ; i++) {
        Sprite* background = backGrounds->at(i);
        float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
        float size = background->getContentSize().width;
        if(xPosition < -size) {
            _backgroundNode->incrementOffset(Point(2000, 0), background);
        }
    }
    
    delete backGrounds;
    
    Size winSize = Director::getInstance()->getWinSize();
    float maxY = winSize.height - _ship->getContentSize().height/2;
    float minY = _ship->getContentSize().height/2;
    
    float diff = (_shipPointsPerSecY * dt);
    float newY = _ship->getPosition().y + diff;
    newY = MIN(MAX(newY, minY), maxY);
    _ship->setPosition(Point(_ship->getPosition().x, newY));
    
    float curTimeMillis = getTimeTick();
    if(curTimeMillis > _nexAsteroidSpawn) {
        float randMillisecs = randomValueBetween(0.20, 1.0) * 1000;
        _nexAsteroidSpawn = randMillisecs + curTimeMillis;
        
        float randY = randomValueBetween(0.0, winSize.height);
        float randDuration = randomValueBetween(2.0, 10.0);
        
        Sprite *asteroid = _asteroids->at(_nextAsteroid);
        _nextAsteroid++;
        
        if(_nextAsteroid >= _asteroids->size()) {
            _nextAsteroid = 0;
        }
        
        asteroid->stopAllActions();
        asteroid->setPosition(Point(winSize.width + asteroid->getContentSize().width/2, randY));
        asteroid->setVisible(true);
        int widthTemp = -winSize.width - asteroid->getContentSize().width;
        std::function<void(Node*)> setInvisibleFunc = nullptr;
        setInvisibleFunc = [this, &setInvisibleFunc](Node* node) -> void {
            setInvisible(node);
        };
        asteroid->runAction(Sequence::create(MoveBy::create(randDuration, Point(widthTemp, 0)),
                                             CallFuncN::create(setInvisibleFunc), NULL));
        for(int i = 0 ; i < _asteroids->size() ; i++) {
            auto *tAsteroid = _asteroids->at(i);
            if(!(tAsteroid->isVisible())) {
                continue;
            }
            for(int k = 0 ; k < _shipLasers->size() ; k++) {
                auto *tShipLaser = _shipLasers->at(k);
                if(!tShipLaser->isVisible()) {
                    continue;
                }
                if(tShipLaser->getBoundingBox().intersectsRect(tAsteroid->getBoundingBox())) {
                    SimpleAudioEngine::getInstance()->playEffect("explosion_large.caf");
                    tShipLaser->setVisible(false);
                    tAsteroid->setVisible(false);
                    continue;
                }
            }
            if(_ship->getBoundingBox().intersectsRect(tAsteroid->getBoundingBox())) {
                SimpleAudioEngine::getInstance()->playEffect("shake.caf");
                tAsteroid->setVisible(false);
                _ship->runAction(Blink::create(1.0, 9));
                _lives--;
            }
        }
    }
    if(_lives <= 0) {
        _ship->stopAllActions();
        _ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    } else if(curTimeMillis >= _gameOverTime) {
        this->endScene(KENDREASONWIN);
    }
}

void HelloWorld::touchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event) {
    SimpleAudioEngine::getInstance()->playEffect("laser_ship.caf");
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *shipLaser = (Sprite*)_shipLasers->at(_nextShipLaser++);
    if(_nextShipLaser >= _shipLasers->size()) {
        _nextShipLaser = 0;
    }
    shipLaser->setPosition(_ship->getPosition() + Point(shipLaser->getContentSize().width/2, 0));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
//    std::function<void(Node*)> setInvisibleFunc = nullptr;
//    setInvisibleFunc = [this, &setInvisibleFunc](Node* node) -> void {
//        setInvisible(node);
//    };
    shipLaser->runAction(CCSequence::create(MoveBy::create(0.5, Point(winSize.width, 0)),
                                            CallFuncN::create(CC_CALLBACK_0(HelloWorld::setInvisible, this, shipLaser)), NULL));
    
}

void HelloWorld::touchesBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    std::vector<Touch *> touches = std::vector<Touch*>();
    touches.push_back(touch);
    this->touchesBegan(touches, event);
}

void HelloWorld::restartTapped(Object* obj) {
    auto target = static_cast<Node*>(obj);
    target->setVisible(false);
    log("label tag = %d", target->getTag());
    SimpleAudioEngine::getInstance()->playEffect("powerup.caf");
    Director::getInstance()->replaceScene(TransitionZoomFlipX::create(0.5, this->createScene()));
    //reschedule
    this->scheduleUpdate();
}

void HelloWorld::endScene(EndReason endReason) {
    if(_gameOver) {
        return;
    }
    _gameOver = true;
    
    Size winSize = Director::getInstance()->getWinSize();
    char message[10] = "You Win";
    if(endReason == KENDREASONLOSE) {
        strcpy(message, "You Lose");
    }
    LabelBMFont *label;
    label = LabelBMFont::create(message, "Arial.fnt");
    label->setScale(0.1);
    label->setPosition(Point(winSize.width/2, winSize.height*0.6));
    this->addChild(label);
    
    LabelBMFont * restartLabel;
    strcpy(message, "Restart");
    restartLabel = LabelBMFont::create(message, "Arial.fnt");
    ccMenuCallback restCallbackFunc =  [this, &restCallbackFunc](Object* obj) -> void {
        restartTapped(obj);
    };
    restartLabel->setTag(1001);
    
    MenuItemLabel *restartItem = MenuItemLabel::create(restartLabel, restCallbackFunc);
    restartItem->setScale(0.1);
    restartItem->setPosition(Point(winSize.width/2, winSize.height*0.4));
    restartItem->setVisible(true);
    
    Menu *menu = Menu::create(restartItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        return menu->isVisible();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, menu);

    
    //clear label and menu
    restartItem->runAction(ScaleTo::create(0.5, 1.0));
    label->runAction(ScaleTo::create(0.5, 1.0));
    
    //terminer update callback
    this->unscheduleUpdate();
    
}

float HelloWorld::randomValueBetween(float low, float high) {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

float HelloWorld::getTimeTick() {
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float)millisecs;
}

void HelloWorld::setInvisible(Node *node) {
    node->setVisible(false);
    if(node == this) {
        log("==");
    }
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    EventCustom event("finish_game");
    event.setUserData((void*)"I am Dung Ta Van");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    mEndGamePopup->setVisible(true);
    if(mEndGamePopup->isExitGame) {
        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}
