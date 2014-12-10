/*
 * SqlObject.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: dungtavan
 */

#include "SqlObject.h"
#include "SqlColumn.h"
#include "SqlRow.h"
#include "SqlCell.h"

SqlObject::SqlObject() :
mTableName(""),
mIdFieldNames(vector<string>()),
mColumns(vector<SqlColumn*>()),
mRows(vector<SqlRow*>()) {

}

SqlObject::SqlObject(const string& tableName) :
mTableName(tableName),
mIdFieldNames(vector<string>()),
mColumns(vector<SqlColumn*>()),
mRows(vector<SqlRow*>()) {

}

void SqlObject::setColumnNames(const char* columnName, ...) {
	int i = 0;
	va_list vl;
	const char* str = columnName;

	va_start(vl, columnName);
	do {
		if(!columnAt(i)) {
			newColumn();
		}
		columnAt(i++)->setName(str);
		str = va_arg(vl, const char*);
	} while(str != NULL);

	va_end(vl);
}

void SqlObject::setColumnTypes(int columnType, ...) {
	int i = 0;
	va_list vl;
	int type = columnType;

	va_start(vl, columnType);
	do {
		if(!columnAt(i)) {
			newColumn();
		}
		columnAt(i++)->setType(type);
		type = va_arg(vl, int);
	} while(type != -1);

	va_end(vl);
}

void SqlObject::setIdFieldNames(const char *idName, ...) {
    va_list vl;
    const char* str = idName;
    
    va_start(vl, idName);
    do {
        mIdFieldNames.push_back(str);
        str = va_arg(vl, const char*);
    } while(str != NULL);
    
    va_end(vl);
}

void SqlObject::setIdFieldIndexes(int index, ...) {
    va_list vl;
    int id = index;
    
    va_start(vl, index);
    do {
        mIdFieldIndexes.push_back(id);
        id = va_arg(vl, int);
    } while(id != -1);
    
    va_end(vl);
}

SqlColumn* SqlObject::newColumn() {
	SqlColumn* column = new SqlColumn();
    addColumn(column);

	return column;
}

SqlRow* SqlObject::newRow() {
    return new SqlRow();
}

void SqlObject::addColumn(SqlColumn* column) {
    column->setIndex(numberOfColumns());
	mColumns.push_back(column);
    
    int indexOfColumn = mColumns.size() - 1;
    for(int i = 0 ; i < column->numberOfCells() ; i++) {
        if(numberOfRows() == i) {
            addRow(newRow());
        }
        rowAt(i)->addCell(column->cellAt(i), indexOfColumn);
    }
}

void SqlObject::addColumns(const vector<SqlColumn*>& columns) {
    for(int i = 0 ; i < columns.size() ; i++) {
        addColumn(columns.at(i));
    }
}

vector<SqlColumn*>* SqlObject::columns() {
	return &mColumns;
}

SqlColumn* SqlObject::columnAt(int index) {
	if(mColumns.size() > index) {
		return mColumns.at(index);
	}

	return NULL;
}

SqlColumn* SqlObject::columnByName(const string &name) {
    for(int i = 0 ; i < numberOfColumns() ; i++) {
        if(columnAt(i)->getName().compare(name) == 0) {
            return columnAt(i);
        }
    }
    
    return NULL;
}

string SqlObject::toSelectQuery() {
	string builder = string();
	builder.append("SELECT ");
	for(int i = 0 ; i < mColumns.size() ; i ++) {
		builder.append(mColumns.at(i)->getName());
		if(i < mColumns.size() - 1) {
			builder.append(", ");
		}
	}
	builder.append(" FROM ")
			.append(getTableName());

	return builder;
}

SqlRow* SqlObject::rowAt(int index) {
    if(mRows.size() > index) {
        return mRows.at(index);
    }
    
    return NULL;
}

void SqlObject::addRow(SqlRow *row) {
    for(int i = 0 ; i < row->numberOfCells() ; i++) {
        this->columnAt(i)->addCell(row->cellAt(i));
    }
    
    mRows.push_back(row);
}

void SqlObject::removeRow(SqlRow *row) {
    CCLOG("size before: %d", numberOfRows());
    for(int i = 0 ; i < numberOfRows() ; i++) {
        bool isEquals = true;
        for(int j = 0 ; j < mIdFieldIndexes.size() ; j++) {
            int idindex = mIdFieldIndexes.at(j);
            string value1 = getCellValueStr(columnAt(idindex),
                                            mRows.at(i)->cellAt(idindex));
            string value2 = getCellValueStr(columnAt(idindex),
                                            row->cellAt(idindex));
            
            CCLOG("value1 = %s, value2 = %s", value1.c_str(), value2.c_str());
            if(value1.compare(value2) != 0) {
                isEquals = false;
                break;
            }
            if(isEquals) {
                for(int k = 0 ; k < numberOfColumns() ; k++) {
                    mColumns.at(k)->removeCellAt(i);
                }
                if(mRows.at(i) != row) {
                    CC_SAFE_DELETE(mRows.at(i));
                }
                mRows.erase(mRows.begin() + i);
                break;
            }
        }
    }
    CCLOG("size after: %d", numberOfRows());
    CC_SAFE_DELETE(row);
}

int SqlObject::numberOfColumns() {
	return mColumns.size();
}

int SqlObject::numberOfRows() {
	return mColumns.at(0)->numberOfCells();
}

SqlObject* SqlObject::clone() {
	SqlObject *obj = new SqlObject();
	obj->setTableName(this->getTableName());
	obj->setIdFieldNames(this->getIdFieldNames());

	for(int i = 0 ; i < numberOfColumns() ; i++) {
		obj->addColumn(columnAt(i)->clone());
	}

	return obj;
}

string SqlObject::getCellValueStr(SqlColumn* column, SqlCell *cell) {
    string value = "";
    if(column->getType() == sqltext) {
        value = "'" + cell->getTextValue() + "'";
    }
    else if(column->getType() == sqlinteger) {
        value = std::to_string(cell->getIntegerValue());
    }
    else if(column->getType() == sqlreal) {
        value = std::to_string(cell->getRealValue());
    }

    return value;
}

string SqlObject::toCreateTableQuery() {
    string builder = string();
    builder.append("CREATE TABLE IF NOT EXISTS " + getTableName())
    .append("(\n");
    
    for(int i = 0 ; i < numberOfColumns() ; i++) {
        builder.append("\t")
        .append(columnAt(i)->getName())
        .append("\t")
        .append(columnAt(i)->getTypeString());
        if(i < numberOfColumns() - 1) {
            builder.append(",\n");
        }
        
    }
    if(mIdFieldIndexes.size() > 0) {
        string keysbuilder = string(",\n\tPRIMARY KEY(");
        for(int i = 0 ; i < mIdFieldIndexes.size() ; i++) {
            int idindex = mIdFieldIndexes.at(i);
            keysbuilder.append(columnAt(idindex)->getName());
            if(i < mIdFieldIndexes.size() - 1) {
                keysbuilder.append(", ");
            }
        }
        keysbuilder.append(")\n");
        builder.append(keysbuilder);
    }
    
    builder.append("\n);");
    
    return builder;
}

string SqlObject::toInsertQuery(SqlRow *row) {
    string builder = string();
    string valueBuilder = string(" VALUES (");
    builder.append("INSERT INTO " + getTableName() + "(");
    for(int i = 0 ; i < numberOfColumns() ; i++) {
        builder.append(columnAt(i)->getName());
        
        string value = getCellValueStr(columnAt(i), row->cellAt(i));
        valueBuilder.append(value);
        if(i < numberOfColumns() - 1) {
            builder.append(", ");
            valueBuilder.append(", ");
        }
    }
    builder.append(")");
    valueBuilder.append(")");
    
    return builder.append(valueBuilder);
}

string SqlObject::toUpdateQuery(SqlRow *row) {
    string builder = string();
    builder.append("UPDATE " + getTableName())
    .append(" SET ");
    for(int i = 0 ; i < numberOfColumns() ; i++) {
        builder.append(columnAt(i)->getName() + " = ");
        builder.append(getCellValueStr(columnAt(i), row->cellAt(i)));
        if(i < numberOfColumns() - 1) {
            builder.append(", ");
        }
    }
    builder.append(" WHERE ");
    
    for(int i = 0 ; i < mIdFieldIndexes.size() ; i++) {
        int idindex = mIdFieldIndexes.at(i);
        builder.append(columnAt(idindex)->getName())
        .append(" = ")
        .append(getCellValueStr(columnAt(idindex), row->cellAt(idindex)));
        if(i < mIdFieldIndexes.size() - 1) {
            builder.append(" AND ");
        }
    }
    
    return builder;
}

string SqlObject::toDeleteQuery(SqlRow *row) {
    string builder = string();
    builder.append("DELETE FROM " + getTableName())
    .append(" WHERE ");
    for(int i = 0 ; i < mIdFieldIndexes.size() ; i++) {
        int idindex = mIdFieldIndexes.at(i);
        builder.append(columnAt(idindex)->getName())
        .append(" = ")
        .append(getCellValueStr(columnAt(idindex), row->cellAt(idindex)));
        if(i < mIdFieldIndexes.size() - 1) {
            builder.append(" AND ");
        }
    }
    
    return builder;
}

string SqlObject::toString() {
	string builder = string();
	builder.append("table: ")
			.append(getTableName())
			.append("; number of rows: ")
			.append(std::to_string(numberOfRows()))
			.append("\ninfo\n");
	for(int i = 0 ; i < numberOfRows() ; i++) {
        for(int j = 0 ; j < rowAt(i)->numberOfCells() ; j++) {
            builder.append("\t")
				.append(getCellValueStr(columnAt(j), rowAt(i)->cellAt(j)));
        }
        builder.append("\n");
	}

	return builder;
}

void SqlObject::clearData() {
    for(int i = 0 ; i < numberOfRows() ; i++) {
        CC_SAFE_DELETE(mRows.at(i));
    }
    mRows.clear();
    for(int i = 0 ; i < numberOfColumns() ; i++) {
        columnAt(i)->clear();
    }
    
}

SqlObject::~SqlObject() {
	for(int i = 0 ; i < mColumns.size() ; i++) {
		if(mColumns.at(i)) {
			delete mColumns.at(i);
			mColumns.at(i) = 0;
		}
	}
	mColumns.clear();
}


