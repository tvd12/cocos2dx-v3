#include "DatabaseManagement.h"
#include <fstream>

DatabaseManagement::DatabaseManagement()
{
}

DatabaseManagement* DatabaseManagement::getInstance() {
    static DatabaseManagement sInstance;
    
    return &sInstance;
}

sqlite3* DatabaseManagement::openData(string path)
{
	sqlite3* pDB = NULL;
	string sqlstr;
	int result;

	string dbPath = FileUtils::getInstance()->getWritablePath() + path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if (!FileUtils::getInstance()->isFileExist(dbPath.c_str())) {
		Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path.c_str()));
		unsigned char* readData = data.getBytes();
		FILE* file = fopen(dbPath.c_str(), "wb");
		fwrite(readData, data.getSize(), 1, file);
		fclose(file);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path.c_str()));
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
		return NULL;
	}
	return pDB;
}

bool DatabaseManagement::insertRow(sqlite3* db, string table, vector<string> field, vector<string> values)
{
	//student stud = getStudent();
	string querryStr ="";
	querryStr.append("insert into ").append(table).append("(");
	for (vector<string>::iterator i = field.begin(); i != field.end(); ++i)
	{
		querryStr.append(*i);
		if (i + 1 != field.end())
		{
			querryStr.append(",");
		}
	}
	querryStr.append(") values(");
	for (vector<string>::iterator i = values.begin(); i != values.end(); ++i)
	{
		querryStr.append(*i);
		if (i + 1 != values.end())
		{
			querryStr.append(",");
		}
	}
	querryStr.append(")");

	sqlite3_stmt *statement;

	int result = sqlite3_prepare_v2(db, querryStr.c_str(), -1, &statement, NULL);
	if (result == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
        CCLOG("ok insert query");
		return true;
	}
    CCLOG("error insert query");
	return false;
}

bool DatabaseManagement::deleteRow(sqlite3*db, string table, string fieldName, string value)
{
	string query = "delete from " + table + " where " + fieldName + " = " + value;
	sqlite3_stmt *statement;
	int result;
	if (sqlite3_prepare(db, query.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return true;
	}
	return false;
}

bool DatabaseManagement::runQuery(sqlite3*db, string query)
{
	sqlite3_stmt *statement;
	int result;
	if (sqlite3_prepare(db, query.c_str(), -1, &statement, 0) == SQLITE_OK)
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

vector<vector<string> > DatabaseManagement::readDataTable(sqlite3* db, string tableName)
{
	vector<vector<string> > table;
	sqlite3_stmt *statement;
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM " + tableName).c_str(), -1, &statement, NULL);
	if (result == SQLITE_OK)
	{
		int columnCount = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				vector<string> column;
				for (int i = 0; i < columnCount; i++)
				{
					string s = (char*)sqlite3_column_text(statement, i);
					column.push_back(s);
				}
				table.push_back(column);
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				break;
			}
		}
        CCLOG("ok select query");
	}
	//sqlite3_close(db);
	return table;
}

DatabaseManagement::~DatabaseManagement()
{
    
}
