//
//  IGameViewLayout.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 4/17/14.
//
//

#ifndef DragonVideoPoker_IGameViewLayout_h
#define DragonVideoPoker_IGameViewLayout_h

class IGameViewLayout {
public:
    virtual void prepareNewGame() {};
    
private:
    virtual void updateLabels() = 0;
    virtual void addSprites() = 0;
};

#endif
