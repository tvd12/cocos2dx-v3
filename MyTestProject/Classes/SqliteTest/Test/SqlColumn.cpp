/*
 * SqlColumn.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: dungtavan
 */

#include "SqlColumn.h"
#include "SqlCell.h"

SqlColumn::SqlColumn() :
mName(""),
mType(sqltext),
mIndex(0),
mCells(vector<SqlCell*>()) {

}

SqlCell* SqlColumn::newCellAt(int index) {
	SqlCell* cell = new SqlCell();
	mCells.insert(mCells.begin() + index, cell);

	return cell;
}

SqlCell* SqlColumn::newCell() {
	SqlCell* cell = new SqlCell();
	mCells.push_back(cell);

	return cell;
}

void SqlColumn::addCell(SqlCell* cell) {
	mCells.push_back(cell);
}

void SqlColumn::addCells(const vector<SqlCell*>& cells) {
	mCells.insert(mCells.end(), cells.begin(), cells.end());
}

vector<SqlCell*>* SqlColumn::cells() {
	return &mCells;
}

SqlCell* SqlColumn::cellAt(int index) {
	return mCells.at(index);
}

void SqlColumn::removeCellAt(int index) {
    mCells.erase(mCells.begin() + index);
}

void SqlColumn::setType(int pType) {
	if(pType == -1) {
		return;
	}

    if(pType == 1) {
        mType = sqltext;
    }
    else if(pType == 2) {
        mType = sqlinteger;
    }
    else if(pType == 3) {
        mType = sqlreal;
    }
}

string SqlColumn::getTypeString() {
    if(getType() == sqltext) {
        return "TEXT";
    }
    else if(getType() == sqlinteger) {
        return "INT";
    }
    else if(getType() == sqlreal) {
        return "REAL";
    }
    
    return "NULL";
}

string SqlColumn::toString() {
	string builder = string("column: ")
			.append(getName())
			.append("; data type = ")
			.append(std::to_string(getType()))
			.append("; data size =")
			.append(std::to_string(mCells.size()))
			.append("\ndata: \n");
	for(int i = 0 ; i < mCells.size() ; i++) {
		if(getType() == sqltext) {
			builder.append(mCells.at(i)->getTextValue());
		}
		else if(getType() == sqlinteger) {
			builder.append(std::to_string(mCells.at(i)
					->getIntegerValue()));
		}
		else if(getType() == sqlreal) {
			builder.append(std::to_string(mCells.at(i)
								->getRealValue()));
		}
		builder.append(", ");
	}
	return builder;
}

int SqlColumn::numberOfCells() {
	return mCells.size();
}

SqlColumn* SqlColumn::clone() {
	SqlColumn* column = new SqlColumn();
	column->setName(this->getName());
	column->setType(this->getType());

	for(int i = 0 ; i < numberOfCells() ; i++) {
		column->addCell(this->cellAt(i)->clone());
	}

	return column;
}

void SqlColumn::clear() {
    mCells.clear();
}

SqlColumn::~SqlColumn() {
    mCells.clear();
}
