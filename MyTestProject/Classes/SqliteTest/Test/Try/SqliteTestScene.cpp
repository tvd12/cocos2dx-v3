//
//  SqliteTestScene.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/4/14.
//
//

#include <vector>

#include "SqliteTestScene.h"
#include "sqlite3.h"
#include "Sqlite3Helper.h"

#include "SqlRow.h"
#include "SqlColumn.h"
#include "SqlCell.h"
#include "SqlType.h"
#include "SqlObject.h"
#include "MapManager.h"
#include "MapAreaLayer.h"

using namespace std;
using namespace cocos2d;

Scene* SqliteTestScene::scene()
{
    Scene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        SqliteTestScene *layer = SqliteTestScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SqliteTestScene::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
//        std::string path = FileUtils::getInstance()->getWritablePath() + "save.db3";
        Sqlite3Helper::getInstance()->openConnection();
        Menu* menu = Menu::create();
        menu->setAnchorPoint(Point::ZERO);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
        
        for(int i = 3 ; i < 9 ; i++) {
            Label* sizeLabel =
            Label::createWithSystemFont(StringUtils::format("%d x %d", i, i),
                                        "Arial",
                                        24);
            MenuItem *sizeMenuItem =
            MenuItemLabel::create(sizeLabel,
                                  CC_CALLBACK_1(SqliteTestScene::mapSizeMenuItemCallback, this));
            sizeMenuItem->setPosition(Vec2(240, i * 24 + 24));
            sizeMenuItem->setTag(i);
            menu->addChild(sizeMenuItem);
        }
        
        bRet = true;
        
        
    } while (0);
    
    return bRet;
}

void SqliteTestScene::mapSizeMenuItemCallback(cocos2d::Ref *pSender) {
    MenuItem* menuItem = static_cast<MenuItem*>(pSender);
    int size = menuItem->getTag();
    
    Director::getInstance()->replaceScene(MapAreaLayer::createScene(size));
}

void SqliteTestScene::menuCloseCallback(Ref* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}

