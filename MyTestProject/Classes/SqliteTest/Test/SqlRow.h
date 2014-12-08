/*
 * SqlRow.h
 *
 *  Created on: Dec 8, 2014
 *      Author: dungtavan
 */

#ifndef SQL_SQLROW_H_
#define SQL_SQLROW_H_

#include <vector>
#include "cocos2d.h"

using namespace std;

class SqlCell;

class SqlRow {
public:
	SqlRow();
    SqlRow(SqlCell* cell, ...);

	virtual void addCell(SqlCell* sqlCell);
    virtual void addCell(SqlCell* sqlCell, int index);
	virtual void addCells(const vector<SqlCell*>& mSqlCells);
    virtual void addCells(SqlCell* cell, ...);

	virtual vector<SqlCell*>* cells();
	virtual SqlCell* cellAt(int index);

	virtual int numberOfCells();

	virtual string toString();
    
    virtual ~SqlRow();
protected:
	vector<SqlCell*> mCells;
};

#endif /* SQL_SQLROW_H_ */
