/*
 * SqlRow.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: dungtavan
 */

#include "SqlRow.h"
#include "SqlCell.h"

SqlRow::SqlRow() :
mCells(vector<SqlCell*>()) {

}

SqlRow::SqlRow(SqlCell* cell, ...) {
    va_list vl;
    SqlCell* c = cell;
    
    va_start(vl, cell);
    do {
        mCells.push_back(c);
        c = va_arg(vl, SqlCell*);
    } while(c != NULL);
    
    va_end(vl);
}

void SqlRow::addCell(SqlCell* cell) {
	mCells.push_back(cell);
}

void SqlRow::addCell(SqlCell *cell, int index) {
    if(mCells.size() > index) {
        mCells[index] = cell;
    }
    else {
        mCells.insert(mCells.begin() + index, cell);
    }
}

void SqlRow::addCells(const vector<SqlCell*>& cells) {
    for(int i = 0 ;i < cells.size() ; i++) {
        addCell(cells.at(i));
    }
}

void SqlRow::addCells(SqlCell *cell, ...) {
    va_list vl;
    SqlCell* c = cell;
    
    va_start(vl, cell);
    do {
        mCells.push_back(c);
        c = va_arg(vl, SqlCell*);
    } while(c != NULL);
    
    va_end(vl);
}

vector<SqlCell*>* SqlRow::cells() {
	return &mCells;
}

SqlCell* SqlRow::cellAt(int index) {
	return mCells.at(index);
}

string SqlRow::toString() {
	string builder = string("row")
			.append("; data size =")
			.append(std::to_string(mCells.size()))
			.append("\ndata: \n");
	for(int i = 0 ; i < mCells.size() ; i++) {
		builder.append(mCells.at(i)->toString());
		builder.append(", ");
	}
	return builder;
}

int SqlRow::numberOfCells() {
	return mCells.size();
}

SqlRow::~SqlRow() {
    for(int i = 0 ; i < mCells.size() ; i++) {
        if(mCells.at(i)) {
            delete mCells.at(i);
            mCells.at(i) = 0;
        }
    }
    mCells.clear();
}
