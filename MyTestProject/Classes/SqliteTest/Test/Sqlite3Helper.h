//
//  Sqlite3Helper.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/5/14.
//
//

#ifndef __MyTestProject__Sqlite3Helper__
#define __MyTestProject__Sqlite3Helper__

#include <string>
#include <vector>
#include <fstream>

#include "sqlite3.h"

using namespace std;

class SqlObject;
class SqlRow;

class Sqlite3Helper {
public:
    
    static Sqlite3Helper* getInstance();
    
    void openConnection(const string& dbFilePath = "save.db3");
    
    void closeConnection();
    
    bool executeUpdate(const string& query);
    
    bool insertData(SqlObject* sqlObj, SqlRow* sqlRow);
    bool updateData(SqlObject* sqlObj, SqlRow* sqlRow);
    bool deleteData(SqlObject* sqlObj, SqlRow* sqlRow);
    SqlObject* createTableData(SqlObject* sqlObj);
    SqlObject* fetchData(SqlObject* sqlObj);
    
    void setConnected(bool isConnected);
    
    bool isConnected();
    
    sqlite3* getSqlite3();
    
    ~Sqlite3Helper();
    
protected:
    bool mIsConnected;
    sqlite3 *mSqlite3;
private:
    Sqlite3Helper();
    Sqlite3Helper(const Sqlite3Helper&);
    void operator = (const Sqlite3Helper&);
};

#endif /* defined(__MyTestProject__Sqlite3Helper__) */
