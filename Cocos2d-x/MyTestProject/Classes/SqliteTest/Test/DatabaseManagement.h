#ifndef __DATABASE_MANAGEMENT__
#define __DATABASE_MANAGEMENT__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "sqlite3.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "sqlite3.h"
#endif
using namespace std;
using namespace cocos2d;
class DatabaseManagement {
public:
    static DatabaseManagement* getInstance();
	sqlite3* openData(string path);
	bool insertRow(sqlite3* db, string table, vector<string> field, vector<string> values);
	bool deleteRow(sqlite3*db, string table, string fieldName, string value);
	bool runQuery(sqlite3*db, string query);
	vector<vector<string> > readDataTable(sqlite3* db, string tableName);
	virtual ~DatabaseManagement();
    
private:
    DatabaseManagement();
    DatabaseManagement(const DatabaseManagement&);
    void operator = (const DatabaseManagement&);
};
#endif