//
//  BirdSprite.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/11/15.
//
//

#ifndef __Earlybird__BirdSprite__
#define __Earlybird__BirdSprite__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

typedef enum{
    
    ACTION_STATE_IDLE,
    
    ACTION_STATE_FLY,
    
    ACTION_STATE_DIE
    
} ActionState;

class BirdSprite {
public:
    
    static BirdSprite* getInstance();
    
    virtual bool init();
    
    bool createBird();
    
    void idle();
    
    void fly();
    
    void die();
    
    void setPosition(const Vec2 &position);;
    
    void setTag(int tag);
    
    void addToParent(Node* pParent, int zOrder);
    
    void removeFromParent();
    
    CC_SYNTHESIZE(Sprite*, mGraphic, Graphic);
    
    ~BirdSprite();
    
protected:
    /**
     * This method can create a frame animation with the likey name texture.
     */
    static cocos2d::Animation *createAnimation(string fmt, int count, float fps);
    
    /**
     * Since this game has three different types of bird
     * this method is just used for choosing which type of bird by random
     */
    void createBirdByRandom();
    
private:
    
    BirdSprite();
    BirdSprite(const BirdSprite &) = delete;
    void operator = (const BirdSprite &) = delete;
    
    /**
     * This method change current status. called by fly and idle etc.
     */
    bool changeState(ActionState state);
    
    static BirdSprite* sShareBirdSprite;
    
    Action* mIdleAction;
    
    //Action* flyAction;
    
    Action* mSwingAction;
    
    ActionState mCurrentStatus;
    
    //the bird name will be created by random
    string mBirdName;
    
    //the bird name format depends on the bird name we have rendom created before
    string mBirdNameFormat;
    
    //record the first time into the game.
    unsigned int mIsFirstTime;
};

#endif /* defined(__Earlybird__BirdSprite__) */
