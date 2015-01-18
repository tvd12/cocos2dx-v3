//
//  GameLayer.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/13/15.
//
//

#ifndef __Earlybird__GameLayer__
#define __Earlybird__GameLayer__

#include "cocos2d.h"
#include "OptionLayer.h"

using namespace std;
using namespace cocos2d;

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

const int UP_PIP = 21;

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/**
 * The radius of the bird
 */
const int BIRD_RADIUS = 15;

/**
 * The height of the pips
 */
const int PIP_HEIGHT = 320;

/**
 * The width of the pips
 */
const int PIP_WIDTH = 52;

/**
 * Pip shift speed
 */
const float PIP_SHIFT_SPEED = 80.0f;

/**
 * The distance between the down pip and up pip
 */
const int PIP_DISTANCE = 100;

/**
 * The distance between the pips vertical
 */
const int PIP_INTERVAL = 180;

/**
 * The number of pip pairs display in the screen in the same time
 */
const int PIP_COUNT = 2;

/**
 * The distance that the pip will display in the screen, for player to ready
 */
const int WAIT_DISTANCE = 100;

/**
 * Define the game status
 * GAME_STATUS_READY game is not start, just ready for payer to start.
 * GAME_STATUS_START the game is started, and payer is paying this game.
 * GAME_STATUS_OVER the player is lose this game, the game is over.
 */
typedef enum _game_status {
    GAME_STATUS_READY = 1,
    GAME_STATUS_START,
    GAME_STATUS_OVER
} GameStatus;

class BirdSprite;
class StatusDelegate;

class GameLayer : public Layer , public OptionDelegate {
public:
    GameLayer();
    
    ~GameLayer();
    
    bool virtual init();
    
    CREATE_FUNC(GameLayer);
    
    /**
     * According to current game status, give the order to delegate.
     */
    CC_SYNTHESIZE(StatusDelegate*, mDelegate, Delegate);
    
    /**
     * @Override
     * To see @OptionDelegate::onTouch
     * User have touched the screen
     * This game, user just need only this method to control game
     */
    void onTouch();
    
    /**
     * This layer need physical engine work
     */
    void setPhyWorld(PhysicsWorld* world);
    
    void update(float delta);
    
private:
    /**
     * Set the rotate for the bird,let it looks like the head is very heavy.
     */
    void rotateBird();
    
    /**
     * create new pips and make it move from left to right then remove from parent
     */
    void createPips();
    
    /**
     * get a random number that can set the pip height
     */
    int getRandomHeight();
    
    /**
     * Check the if the bird have hit anything
     */
    void checkHit();
    
    /**
     * Since the only global bird can not be addChilded to two layers
     * we must delete it from one layer,and then add it to another layer
     * Here we use the fadeout animation to delete it from the gamelayer, so when the player
     * press the restart button, the bird can be added successfully
     */
    void birdSpriteFadeOut();
    
    /*
     * After running the fadeout animation, delete the bird from current layer
     */
    void birdSpriteRemove();
    
    void scrollLand(float dt);
    
    bool onContactBegin(const PhysicsContact& contact);
    
    void gameOver();
    
    PhysicsWorld *mWorld;
    
    GameStatus mGameStatus;
    
    int mScore;
    
    BirdSprite *mBird;
    
    Node *mGroundNode;
    
    vector<Node*> mPips;
    
    Sprite *mLandSpites[2];
    
    SEL_SCHEDULE mShiftLand;
};

#endif /* defined(__Earlybird__GameLayer__) */
