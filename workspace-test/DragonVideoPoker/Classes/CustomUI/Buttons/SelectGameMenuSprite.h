//
//  SelectGameMenuSprite.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#ifndef __DragonVideoPoker__SelectGameMenuSprite__
#define __DragonVideoPoker__SelectGameMenuSprite__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class RoomInfo;

class SelectGameMenuSprite : public CCSprite
{
public:
    static SelectGameMenuSprite * createWithIndex(const int index,
                                                  bool isSelected = false,
                                                  bool isDisabled = false);
    bool initWithIndex(const int index,
                       bool isSelected = false,
                       bool isDisabled = false);
    
    CC_SYNTHESIZE_READONLY(RoomInfo*, mRoomInfo, RoomInfo);
    
    virtual void update(float dt);

private:
    void addRoomInfoItems();
    void addLockedItems();
    void grayItems();
    
    int mGameType;
    
    CCLabelTTF * mJackpotLabel;
    CCLabelTTF * mStakesLabel;
};


#endif /* defined(__DragonVideoPoker__SelectGameMenuSprite__) */
