//
//  MapManager.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#include <ctime>

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

bool MapArea::hasPassed() {
    return getTime() > 0
    && getClick() >= getCharacter();
}

int MapArea::getStars() {
    int times[] = {30, 60, 70, 80, 90, 100};
    int numberOfStar = 0, standard = getSize() * getSize() * 2 * 0.75;
    if(this->getTime() < 0.75 * getCharacter()) {
        numberOfStar = 0;
    }
    else if(this->getTime() <= standard) {
        numberOfStar = 3;
    }
    else if(this->getTime() <= standard + 15) {
        numberOfStar = 2;
    }
    
    else if(this->getTime() <= times[getSize() - 3]) {
        numberOfStar = 1;
    }
    
    return numberOfStar;
}

void MapArea::setDate(const string& date) {
    if(date.length() == 0) {
        std::time_t tp = std::time(NULL);   // current time, an integer
        // counting seconds since epoch
        std::tm * ts = std::localtime(&tp); // parsed into human conventions
        string d = string()
        .append(std::to_string(ts->tm_mday))
        .append("/")
        .append(std::to_string(ts->tm_mon + 1))
        .append("/")
        .append(std::to_string(1900 + ts->tm_year));
        mCells.at(5)->setTextValue(d);
    }
    else {
        mCells.at(5)->setTextValue(date);
    }
}

string MapArea::toString() {
    string builder = string()
    .append("\nindex: " + std::to_string(getIndex()))
    .append("\nsize: " + std::to_string(getSize()))
    .append("\ncharacter: " + std::to_string(getCharacter()))
    .append("\ntime: " + std::to_string(getTime()))
    .append("\nclick: " + std::to_string(getClick()))
    .append("\ndate: " + getDate())
    .append("\nhasPassed: " + std::to_string(hasPassed()));
    
    return builder;
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

MapArea* MapManager::beforeArea(int size, int character) {
    MapArea* area = areaByCharacter(size, character - 1);
    if(!area && size > 3) {
        area = areasAt(size - 1)->at(areasAt(size - 1)->size() - 1);
    }
    
    return area;
}

bool MapManager::playable(int size, int character) {
    MapArea* before = beforeArea(size, character);
    if(size == 3 ||
       before->hasPassed()) {
        return true;
    }
    
    return false;
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


