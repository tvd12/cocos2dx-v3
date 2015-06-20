#include "HelloWorldScene.h"
//#include "TestAdsScene.h"
//#include "TestAnalyticsScene.h"
//#include "TestShareScene.h"
//#include "TestIAPScene.h"
//#include "TestIAPOnlineScene.h"
//#include "TestUserScene.h"
//#include "TestSocialScene.h"
#include "TestFacebookUserScene.h"
#include "TestFacebookShare.h"

USING_NS_CC;

std::string g_testCases[] = {
    "Test Ads",
    "Test Analytics",
    "Test Share",
    "Test Facebook User",
    "Test Facebook Share",
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    "Test IAP",
    "Test IAP Online",
    "Test User",
    "Test Social",
#endif
};

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
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
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                                      "CloseNormal.png",
                                                      "CloseSelected.png",
                                                      CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    pCloseItem->setPosition(Point(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                  origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu, 1);
    
    Point beginPos = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
    float step = 60.0f;
    int nCaseCount = sizeof(g_testCases) / sizeof(std::string);
    for (int i = 0; i < nCaseCount; ++i) {
        std::string caseName = g_testCases[i];
        MenuItemFont *pItem = MenuItemFont::create(caseName.c_str(), CC_CALLBACK_1(HelloWorld::menuCallback, this));
        pItem->setTag(i);
        pItem->setPosition(Point(beginPos.x, beginPos.y - i * step));
        pMenu->addChild(pItem);
    }
    
    return true;
}

void HelloWorld::menuCallback(Ref* pSender)
{
    MenuItemFont *pItem = (MenuItemFont*) pSender;
    Scene* newScene = NULL;
    switch (pItem->getTag()) {
        case 0:
//            newScene = TestAds::scene();
            break;
        case 1:
//            newScene = TestAnalytics::scene();
            break;
        case 2:
//            newScene = TestShare::scene();
            break;
        case 3:
            newScene = TestFacebookUser::scene();
            break;
        case 4:
            newScene = TestFacebookShare::scene();
            break;
        case 5:
//            newScene = TestIAP::scene();
            break;
        case 6:
//            newScene = TestIAPOnline::scene();
            break;
        case 7:
//            newScene = TestUser::scene();
            break;
        case 8:
//            newScene = TestSocial::scene();
            break;
        case 9:
            break;
        default:
            break;
    }
    
    if (newScene) {
        Director::getInstance()->replaceScene(newScene);
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}















































//#include "HelloWorldScene.h"
//
//USING_NS_CC;
//
//Scene* HelloWorld::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer = HelloWorld::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer);
//
//    // return the scene
//    return scene;
//}
//
//// on "init" you need to initialize your instance
//bool HelloWorld::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//    
//    mBonusTimer = new BonusTimer();
//    
//    mTimingLabel = Label::createWithTTF(string("Time: ") + mBonusTimer->toString(),
//                                      "fonts/Marker Felt.ttf",
//                                      17.0f);
//    mTimingLabel->setPosition(Point(400, 300));
//    this->addChild(mTimingLabel);
//    
//    mLiveLabel = Label::createWithTTF(StringUtils::format("Live: %lld", mBonusTimer->getLiveBonus()),
//                                    "fonts/Marker Felt.ttf",
//                                    17.0f);
//    mLiveLabel->setPosition(Point(400, 270));
//    this->addChild(mLiveLabel);
//    
//    Label *temp = Label::createWithTTF("Click me!",
//                                       "fonts/Marker Felt.ttf",
//                                       17.0f);
//    MenuItem *useBonusMenuItem =
//    MenuItemLabel::create(temp,
//                          CC_CALLBACK_1(HelloWorld::loginMenuItemCallback, this));
//    useBonusMenuItem->setPosition(Point(240, 100));
//    useBonusMenuItem->setTag(1);
//    menu->addChild(useBonusMenuItem);
//    
//    temp = Label::createWithTTF("Login via Facebook",
//                                "fonts/Marker Felt.ttf",
//                                17.0f);
//    temp->setColor(Color3B(100, 100, 50));
//    MenuItem *loginFb =
//    MenuItemLabel::create(temp,
//                          CC_CALLBACK_1(HelloWorld::loginMenuItemCallback, this));
//    loginFb->setPosition(Point(240, 50));
//    loginFb->setTag(2);
//    menu->addChild(loginFb);
//    
//    
//    CallFunc *callFunc =
//    CallFunc::create(CC_CALLBACK_0(HelloWorld::updateTimingLabel, this));
//    DelayTime *delay = DelayTime::create(1.0f);
//    mTimingLabel->runAction(RepeatForever::create(Sequence::create(delay, callFunc, NULL)));
//    
//    scheduleUpdate();
//    
//    return true;
//}
//
//
//void HelloWorld::updateTimingLabel() {
//    mBonusTimer->update();
//    mTimingLabel->setString(string("Time: ") + mBonusTimer->toString());
//}
//
//void HelloWorld::loginMenuItemCallback(Ref *pSender) {
//    MenuItem *menuItem = static_cast<MenuItem*>(pSender);
//    switch (menuItem->getTag()) {
//        case 1:
//            mBonusTimer->updateLiveBonus(- 1);
//            break;
//        case 2:
//            
//            break;
//        default:
//            break;
//    }
//    
//}
//
//void HelloWorld::update(float dt) {
//    mLiveLabel->setString(StringUtils::format("Live: %lld", mBonusTimer->getLiveBonus()));
//}
//
//
//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
