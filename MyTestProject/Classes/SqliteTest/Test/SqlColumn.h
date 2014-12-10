/*
 * SqlColumn.h
 *
 *  Created on: Dec 6, 2014
 *      Author: dungtavan
 */

#ifndef SQL_SQLCOLUMN_H_
#define SQL_SQLCOLUMN_H_

#include <vector>
#include <string>

#include "cocos2d.h"
#include "SqlType.h"


using namespace std;

class SqlCell;

class SqlColumn {
public:

	SqlColumn();

	SqlColumn(const string& name, SqlType type);

	virtual SqlCell* newCellAt(int index);
	virtual SqlCell* newCell();

	virtual void addCell(SqlCell* sqlCell);
	virtual void addCells(const vector<SqlCell*>& mSqlCells);

	virtual vector<SqlCell*>* cells();
	virtual SqlCell* cellAt(int index);
    
    virtual void removeCellAt(int index);

	virtual void setType(int pType);
    virtual string getTypeString();

	virtual int numberOfCells();

    virtual void clear();
	virtual SqlColumn* clone();

	virtual string toString();

	CC_SYNTHESIZE(string, mName, Name);
	CC_SYNTHESIZE(SqlType, mType, Type);
    CC_SYNTHESIZE(int, mIndex, Index);

	virtual ~SqlColumn();

protected:
	vector<SqlCell*> mCells;
};

#endif /* SQL_SQLCOLUMN_H_ */
