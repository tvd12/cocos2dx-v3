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
        
        std::string sql;
//        
        SqlObject *obj = new SqlObject("super_memory_test");
        obj->setColumnNames("id",
                            "size",
                            "character",
                            "time",
                            "click",
                            "date",
                            NULL);
        obj->setColumnTypes(sqlinteger,
                            sqlinteger,
                            sqlinteger,
                            sqlinteger,
                            sqlinteger,
                            sqltext,
                            -1);
        obj->setIdFieldIndexes(0, -1);
        
        Sqlite3Helper::getInstance()->createTableData(obj);
        
        int id = 0;
        for(int i = 3 ; i < 9 ; i++) {
            int character = (i * i) / 2;
            if(i > 4) {
                int beforecharacter = ((i - 1) * (i - 1)) / 2 + 1;
                for(int j = beforecharacter ; j <= character ; j++) {
                    Sqlite3Helper::getInstance()
                    ->insertData(obj, new SqlRow(new SqlCell(++id),
                                                 new SqlCell(i),
                                                 new SqlCell(j),
                                                 new SqlCell(-1),
                                                 new SqlCell(-1),
                                                 new SqlCell(-1),
                                                 NULL));
                }
            }
            else {
                Sqlite3Helper::getInstance()
                ->insertData(obj, new SqlRow(new SqlCell(++id),
                                             new SqlCell(i),
                                             new SqlCell(character),
                                             new SqlCell(-1),
                                             new SqlCell(-1),
                                             new SqlCell(-1),
                                             NULL));
            }
        }
//
        
        SqlRow* uRow = new SqlRow(new SqlCell(1),
                                  new SqlCell(3),
                                  new SqlCell(4),
                                  new SqlCell(60),
                                  new SqlCell(60),
                                  new SqlCell("1234"));
        
        Sqlite3Helper::getInstance()->updateData(obj, uRow);
//        Sqlite3Helper::getInstance()->deleteData(obj, uRow);
        obj->clearData();
        Sqlite3Helper::getInstance()->fetchData(obj);
        
        CCLOG("obj: %s", obj->toString().c_str());
        
        Label *liu = Label::createWithSystemFont(obj->toString().c_str(),
                                                 "Arial",
                                                 15);
        liu->setPosition(Vec2(200, 200));
        addChild(liu, 1);
 
        //CCDictionary *dictionary=CCDictionary::createWithContentsOfFile("test.xml");
        //const char *chinese=((CCString *)dictionary->objectForKey("japanese"))->m_sString.c_str();
        //CCLabelTTF *ccc=CCLabelTTF::create(chinese,"Arial",24);
        //ccc->setPosition(ccp(300,300));
        ///addChild(ccc,1);
        ///const char *path=CCFileUtils::sharedFileUtils()->getResourceDirectory();
        ///cocos2d::log("%s",path);
        
        bRet = true;
        
        
    } while (0);
    
    return bRet;
}

void SqliteTestScene::menuCloseCallback(Ref* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}

