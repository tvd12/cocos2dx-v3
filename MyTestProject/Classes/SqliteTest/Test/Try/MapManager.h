//
//  MapManager.h
//  MyTestProject
//
//  Created by Dung Ta Van on 12/9/14.
//
//

#ifndef __MyTestProject__MapManager__
#define __MyTestProject__MapManager__

#include <vector>

#include "cocos2d.h"

#include "SqlObject.h"
#include "SqlRow.h"

#define TO_STRING_FUNC(fname) \
    std::string fname##Str() { \
        return std::to_string(fname()); \
    }

class MapArea : public SqlRow {
public:
    int getIndex();
    int getSize();
    int getCharacter();
    int getTime();
    int getClick();
    
    void setSize(int size);
    void setCharacter(int character);
    void setTime(int time);
    void setClick(int click);
    void setDate(const string& date);
    
    std::string getDate();
    
    TO_STRING_FUNC(getIndex);
    TO_STRING_FUNC(getSize);
    TO_STRING_FUNC(getCharacter);
    TO_STRING_FUNC(getTime);
    TO_STRING_FUNC(getClick);
};

class MapManager : public SqlObject {
public:
    static MapManager* getInstance();
    virtual SqlRow* newRow();
    
    void init();
    
    int numberOfAreas();
    
    void setMapAreasVector();
    
    std::vector<MapArea*>* areasAt(int size);
    MapArea* areaAt(int size, int index);
    MapArea* areaByCharacter(int size, int character);
    
    int numberOfCharacters(int size);
    
    void updateMapArea(MapArea* pMapArea);
    
    
protected:
    std::vector<std::vector<MapArea*> > mMapAreasVector;
    
private:
    MapManager() : SqlObject() {}
    MapManager(const MapManager&);
    void operator = (const MapManager&);
};

#endif /* defined(__MyTestProject__MapManager__) */
