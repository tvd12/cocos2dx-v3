/*
 * SqlObject.h
 *
 *  Created on: Dec 6, 2014
 *      Author: dungtavan
 */

#ifndef SQL_SQLOBJECT_H_
#define SQL_SQLOBJECT_H_

#include <string>
#include <vector>

#include "cocos2d.h"
#include "SqlType.h"

using namespace std;

class SqlColumn;

class SqlCell;

class SqlRow;

class SqlObject {

public:

	SqlObject();
	SqlObject(const string& tableName);

	virtual void setColumnNames(const char* columnName, ...);
	virtual void setColumnTypes(int columnType, ...);
    virtual void setIdFieldNames(const char* idName, ...);
    virtual void setIdFieldIndexes(int index, ...);

	virtual SqlColumn* newColumn();

	virtual void addColumn(SqlColumn* column);
	virtual void addColumns(const vector<SqlColumn*>& columns);

	virtual vector<SqlColumn*>* columns();
	virtual SqlColumn* columnAt(int index);
    virtual SqlColumn* columnByName(const string& name);
    
    virtual void addRow(SqlRow* row);
    virtual void removeRow(SqlRow* row);

    virtual string toCreateTableQuery();
	virtual string toSelectQuery();
    virtual string toInsertQuery(SqlRow* row);
    virtual string toUpdateQuery(SqlRow* row);
    virtual string toDeleteQuery(SqlRow* row);
    
    virtual string getCellValueStr(SqlColumn* column, SqlCell *cell);

	virtual int numberOfColumns();

	virtual int numberOfRows();

	virtual SqlRow* rowAt(int index);

	virtual SqlObject* clone();

	virtual string toString();
    
    virtual void clearData();

	CC_SYNTHESIZE(string, mTableName, TableName);
	CC_SYNTHESIZE(vector<string>, mIdFieldNames, IdFieldNames);
    CC_SYNTHESIZE(vector<int>, mIdFieldIndexes, IdFieldIndexes);

	~SqlObject();

protected:
	vector<SqlColumn*> mColumns;
    vector<SqlRow*> mRows;

};

#endif /* SQL_SQLOBJECT_H_ */
