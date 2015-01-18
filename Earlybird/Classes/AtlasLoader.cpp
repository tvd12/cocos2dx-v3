//
//  AtlasLoader.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#include "AtlasLoader.h"

AtlasLoader* AtlasLoader::getInstance() {
    static AtlasLoader sInstance;
    
    return &sInstance;
}

void AtlasLoader::destroyInstance() {
   
}

AtlasLoader::AtlasLoader() {
    
}

bool AtlasLoader::init() {
    
    return true;
}

void AtlasLoader::loadAtlas(string filename) {
    auto textureAtlas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
    this->loadAtlas(filename, textureAtlas);
}

void AtlasLoader::loadAtlas(string filename, Texture2D* texture) {
    
    //get string content of file with name: filename
    string data = FileUtils::getInstance()->getStringFromFile(filename);
    
    unsigned pos;
    Atlas atlas;
    
    //find first of end line
    pos = data.find_first_of("\n");
    
    //get line content
    string line = data.substr(0, pos);
    
    //remove top line
    data = data.substr(pos + 1);
    
    //while has data
    while(line.length() > 0) {
        
        //parse data from line
        sscanf(line.c_str(),
               "%s %d %d %f %f %f %f",
               atlas.name,
               &atlas.width, &atlas.height,
               &atlas.start.x, &atlas.start.y,
               &atlas.end.x, &atlas.end.y);
        
        atlas.start.x = 1024*atlas.start.x;
        atlas.start.y = 1024*atlas.start.y;
        atlas.end.x = 1024*atlas.end.x;
        atlas.end.y = 1024*atlas.end.y;
        
        //next line
        pos = data.find_first_of("\n");
        line = data.substr(0, pos);
        data = data.substr(pos + 1);
        
        // use the data to create a sprite frame
        // fix 1px edge bug
        if(atlas.name == string("land")) {
            atlas.start.x += 1;
        }
        
        Rect rect = Rect(atlas.start.x, atlas.start.y,
                         atlas.width, atlas.height);
        auto frame = SpriteFrame::createWithTexture(texture, rect);
        this->mSpriteFrames.insert(string(atlas.name), frame);
    }
}

SpriteFrame* AtlasLoader::getSpriteFrameByName(string name) {
    return this->mSpriteFrames.at(name);
}



