/*
 * SqlField.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: dungtavan
 */

#include "SqlCell.h"

SqlCell::SqlCell() :
mTextValue(""),
mIntegerValue(0),
mRealValue(0.0f) {

}

SqlCell::SqlCell(const string &textValue) :
mTextValue(textValue),
mIntegerValue(0),
mRealValue(0.0f) {
    
}

SqlCell::SqlCell(int intValue) :
mTextValue(""),
mIntegerValue(intValue),
mRealValue(0.0f) {
    
}

SqlCell::SqlCell(float realValue) :
mTextValue(""),
mIntegerValue(0),
mRealValue(realValue) {
    
}

SqlCell* SqlCell::clone() {
	SqlCell* cell = new SqlCell();
	cell->setTextValue(this->getTextValue());
	cell->setIntegerValue(this->getIntegerValue());
	cell->setRealValue(this->getRealValue());

	return cell;
}

string SqlCell::toString() {
	string builder = string();
	builder.append("cell: ")
			.append("text(" + getTextValue() + "), ")
			.append("int(" + std::to_string(getIntegerValue()) + "), ")
			.append("real(" + std::to_string(getRealValue()) + ")");

	return builder;
}

SqlCell::~SqlCell() {

}
