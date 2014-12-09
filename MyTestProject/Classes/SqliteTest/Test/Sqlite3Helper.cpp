//
//  Sqlite3Helper.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/5/14.
//
//

#include "Sqlite3Helper.h"
#include "cocos2d.h"
#include "SqlObject.h"

#include "SqlRow.h"
#include "SqlColumn.h"
#include "SqlCell.h"
#include "SqlType.h"

using namespace cocos2d;

Sqlite3Helper::Sqlite3Helper() :
mSqlite3(NULL){
    
}

Sqlite3Helper* Sqlite3Helper::getInstance() {
    static Sqlite3Helper sInstance;
    
    return &sInstance;
}

void Sqlite3Helper::openConnection(const string& dbFilePath) {
    sqlite3* pDB = NULL;
    string sqlstr;
    int result;
    
    string dbPath = FileUtils::getInstance()->getWritablePath() + dbFilePath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (!FileUtils::getInstance()->isFileExist(dbPath.c_str())) {
        Data data = FileUtils::getInstance()
        ->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(dbFilePath.c_str()));
        unsigned char* readData = data.getBytes();
        FILE* file = fopen(dbPath.c_str(), "wb");
        fwrite(readData, data.getSize(), 1, file);
        fclose(file);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Data data = FileUtils::getInstance()
    ->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(dbFilePath.c_str()));
    unsigned char* readData = data.getBytes();
    if (!FileUtils::getInstance()->isFileExist(dbPath)){
        std::ofstream outfile(dbPath.c_str(), std::ofstream::out);
        outfile.write((char *)&readData[0], data.getSize());
        outfile.close();
    }
#endif
    result = sqlite3_open_v2(dbPath.c_str(), &pDB, SQLITE_OPEN_READWRITE, NULL);
    if (result != SQLITE_OK)
    {
        CCLOG("cannot open connection!");
    }
    mSqlite3 = pDB;
}

bool Sqlite3Helper::executeUpdate(const string& query) {
    sqlite3_stmt *statement;
    int result;
    if (sqlite3_prepare(mSqlite3, query.c_str(), -1, &statement, 0) == SQLITE_OK)
    {
        int res = sqlite3_step(statement);
        result = res;
        sqlite3_finalize(statement);
        CCLOG("ok running query");
        return true;
    }
    CCLOG("erorr running query");
    return false;
}

SqlObject* Sqlite3Helper::fetchData(SqlObject* sqlObj) {
    sqlite3_stmt *statement;
    CCLOG("query = %s", sqlObj->toSelectQuery().c_str());
    int result = sqlite3_prepare_v2(mSqlite3,
                                    sqlObj->toSelectQuery().c_str(),
                                    -1,
                                    &statement,
                                    NULL);
    if (result == SQLITE_OK)
    {
        int columnCount = sqlite3_column_count(statement);
        int res = 0;
        
        while (1)
        {
            res = sqlite3_step(statement);
            
            if (res == SQLITE_ROW)
            {
                SqlRow *sqlRow = sqlObj->newRow();
                for (int i = 0; i < columnCount; i++)
                {
                    SqlType columnType = sqlObj->columnAt(i)->getType();
                    SqlCell* cell = new SqlCell();
                    if(columnType == sqltext) {
                        string s = (char*)sqlite3_column_text(statement, i);
                        cell->setTextValue(s);
                    }
                    else if(columnType == sqlinteger) {
                        cell->setIntegerValue(sqlite3_column_int(statement, i));
                    }
                    else if(columnType == sqlreal) {
                        cell->setRealValue(sqlite3_column_double(statement, i));
                    }
                    sqlRow->addCell(cell);
                }
                sqlObj->addRow(sqlRow);
                
            }
            
            if (res == SQLITE_DONE || res == SQLITE_ERROR)
            {
                if(res == SQLITE_DONE) {
                    CCLOG("ok select query");
                }
                else if (res == SQLITE_ERROR) {
                    CCLOG("error select query");
                }
                break;
            }
        }
        CCLOG("finish select query");
    }
    //sqlite3_close(db);
    return sqlObj;
}

SqlObject* Sqlite3Helper::createTableData(SqlObject *sqlObj) {
    string createtablequery = sqlObj->toCreateTableQuery();
    CCLOG("createablequery = %s", createtablequery.c_str());
    
    if(executeUpdate(createtablequery)) {
        return sqlObj;
    }
    else {
        CC_SAFE_DELETE(sqlObj);
    }
    
    return sqlObj;
}

bool Sqlite3Helper::insertData(SqlObject *sqlObj, SqlRow *sqlRow) {
    string insertquery = sqlObj->toInsertQuery(sqlRow);
    CCLOG("insertquery = %s", insertquery.c_str());
    
    if(!executeUpdate(insertquery)) {
        CC_SAFE_DELETE(sqlRow);
        return false;
    }
    
    return true;
}

bool Sqlite3Helper::updateData(SqlObject *sqlObj, SqlRow *sqlRow) {
    string updatequery = sqlObj->toUpdateQuery(sqlRow);
    CCLOG("updatequery = %s", updatequery.c_str());
    
    if(!executeUpdate(updatequery)) {
        CC_SAFE_DELETE(sqlRow);
        return false;
    }
    
    return true;
}

bool Sqlite3Helper::deleteData(SqlObject *sqlObj, SqlRow *sqlRow) {
    string deletequery = sqlObj->toDeleteQuery(sqlRow);
    CCLOG("deleteQuery = %s", deletequery.c_str());
    
    if(executeUpdate(deletequery)) {
        sqlObj->removeRow(sqlRow);
        return true;
    }
    
    return false;
}

void Sqlite3Helper::closeConnection() {
    sqlite3_close(mSqlite3);
}

void Sqlite3Helper::setConnected(bool isConnected) {
    this->mIsConnected = isConnected;
}

bool Sqlite3Helper::isConnected() {
    return this->mIsConnected;
}

sqlite3* Sqlite3Helper::getSqlite3() {
    return mSqlite3;
}

Sqlite3Helper::~Sqlite3Helper() {
    closeConnection();
}
