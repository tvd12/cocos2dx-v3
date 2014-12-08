/*
 * SqlField.h
 *
 *  Created on: Dec 5, 2014
 *      Author: dungtavan
 */

#ifndef SQL_SQLCELL_H_
#define SQL_SQLCELL_H_

#include <string>

#include "cocos2d.h"
#include "SqlType.h"

using namespace std;

class SqlCell {

public:
	SqlCell();
    SqlCell(const string &textValue);
    SqlCell(int intValue);
    SqlCell(float realValue);

	virtual SqlCell* clone();

	virtual string toString();

	CC_SYNTHESIZE(string, mTextValue, TextValue);
	CC_SYNTHESIZE(int, mIntegerValue, IntegerValue);
	CC_SYNTHESIZE(float, mRealValue, RealValue);

	virtual ~SqlCell();
};

#endif /* SQL_SQLCELL_H_ */
