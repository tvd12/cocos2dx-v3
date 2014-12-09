//
//  MapManager.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#include "MapManager.h"
#include "SqlCell.h"
#include "Sqlite3Helper.h"

using namespace std;

int MapArea::getIndex() {
    return mCells.at(0)->getIntegerValue();
}

int MapArea::getSize() {
    return mCells.at(1)->getIntegerValue();
}

int MapArea::getCharacter() {
    return mCells.at(2)->getIntegerValue();
}

int MapArea::getTime() {
    return mCells.at(3)->getIntegerValue();
}

int MapArea::getClick() {
    return mCells.at(4)->getIntegerValue();
}

string MapArea::getDate() {
    return mCells.at(5)->getTextValue();
}

void MapArea::setSize(int size) {
    mCells.at(1)->setIntegerValue(size);
}

void MapArea::setCharacter(int character) {
    mCells.at(2)->setIntegerValue(character);
}

void MapArea::setTime(int time) {
    mCells.at(3)->setIntegerValue(time);
}

void MapArea::setClick(int click) {
    mCells.at(4)->setIntegerValue(click);
}

void MapArea::setDate(const string& date) {
    mCells.at(5)->setTextValue(date);
}

//===========================================

MapManager* MapManager::getInstance() {
    static MapManager sInstance;
    
    return &sInstance;
}

void MapManager::init() {
    this->setTableName("super_memory_test");
    this->setColumnNames("id",
                        "size",
                        "character",
                        "time",
                        "click",
                        "date",
                        NULL);
    this->setColumnTypes(sqlinteger,
                        sqlinteger,
                        sqlinteger,
                        sqlinteger,
                        sqlinteger,
                        sqltext,
                        -1);
    this->setIdFieldIndexes(0, -1);
    
    Sqlite3Helper::getInstance()->createTableData(this);
    
    int id = 0;
    for(int i = 3 ; i < 9 ; i++) {
        int character = (i * i) / 2;
        if(i > 4) {
            int beforecharacter = ((i - 1) * (i - 1)) / 2 + 1;
            for(int j = beforecharacter ; j <= character ; j++) {
                Sqlite3Helper::getInstance()
                ->insertData(this, new SqlRow(new SqlCell(++id),
                                             new SqlCell(i),
                                             new SqlCell(j),
                                             new SqlCell(-1),
                                             new SqlCell(-1),
                                             new SqlCell(-1),
                                             NULL));
            }
        }
        else {
            Sqlite3Helper::getInstance()
            ->insertData(this, new SqlRow(new SqlCell(++id),
                                         new SqlCell(i),
                                         new SqlCell(character),
                                         new SqlCell(-1),
                                         new SqlCell(-1),
                                         new SqlCell(-1),
                                         NULL));
        }
    }
    Sqlite3Helper::getInstance()->fetchData(this);
    setMapAreasVector();
}

void MapManager::setMapAreasVector() {
    mMapAreasVector = vector<vector<MapArea*> >();
    for(int size = 3 ; size < 9 ; size++) {
        vector<MapArea*> mapAreas = vector<MapArea*>();
        for(int j = 0 ; j < numberOfAreas() ; j++) {
            MapArea* temp = static_cast<MapArea*>(rowAt(j));
            if(temp->getSize() == size) {
                mapAreas.push_back(temp);
            }
        }
        mMapAreasVector.push_back(mapAreas);
    }
}

SqlRow* MapManager::newRow() {
    return new MapArea();
}

MapArea* MapManager::areaAt(int size, int index) {
    return areasAt(size)->at(index);
}

MapArea* MapManager::areaByCharacter(int size, int character) {
    for(int i = 0 ; i < areasAt(size)->size() ; i++) {
        if(areasAt(size)->at(i)->getCharacter() == character) {
            return areasAt(size)->at(i);
        }
    }
    
    return NULL;
}

vector<MapArea*>* MapManager::areasAt(int size) {
    return &mMapAreasVector.at(size - 3);
}

int MapManager::numberOfAreas() {
    return numberOfRows();
}

int MapManager::numberOfCharacters(int size) {
    return areasAt(size)->size();
}

void MapManager::updateMapArea(MapArea *pMapArea) {
    Sqlite3Helper::getInstance()->updateData(this, pMapArea);
}


