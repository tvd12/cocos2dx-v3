//
//  PurchaseTestLayer.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 1/20/15.
//
//

#include "PurchaseTestLayer.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "PurchaseHelper.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::plugin;
using namespace cocos2d::ui;

Scene* PurchaseTestLayer::scene() {
    Scene *scene = Scene::create();
    PurchaseTestLayer *layer = PurchaseTestLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool PurchaseTestLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Load plugins
    PurchaseHelper::getInstance()->loadInappPlugin();
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Back button
    auto backButton = Button::create("btn_normal.png","btn_pressed.png");
    backButton->setAnchorPoint(Vec2(1, 0));
    backButton->setTitleText("Back");
    backButton->setScale(2);
    backButton->setPosition(Vec2(origin.x + winSize.width, origin.y));
    backButton->addClickEventListener([=](Ref* sender){
        PurchaseHelper::purgePurchase();
        Director::getInstance()->replaceScene(HelloWorld::scene());
    });
    addChild(backButton);
    
    auto panel = Layout::create();
    panel->setAnchorPoint(Vec2(0.5,0.5));
    panel->setPosition(Vec2(origin.x + winSize.width/2, origin.y + winSize.height/2));
    panel->setLayoutType(LayoutType::VERTICAL);
    addChild(panel);
    
    //Google IAP button
    auto btnGoogle = Button::create("btn_normal.png","btn_pressed.png");
    btnGoogle->setTitleText("Google");
    btnGoogle->setScale(2);
    btnGoogle->addClickEventListener([=](Ref* sender){
        //Perform IAP callback
        TProductInfo pInfo;
        PurchaseHelper::PayMode mode = PurchaseHelper::PayMode::eIOS;
        pInfo["IAPId"] = "android.test.purchased";
        PurchaseHelper::getInstance()->payByMode(pInfo, mode);
        
    });
    panel->addChild(btnGoogle);
    
    
    return true;
}
