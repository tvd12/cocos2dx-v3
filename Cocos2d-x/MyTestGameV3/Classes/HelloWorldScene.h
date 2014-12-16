#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ParallNodeExtras.h"
#include "EndGamePopup.h"
#include <istream>
#include <functional>

using namespace std;
using namespace cocos2d;

typedef enum Reason {
    KENDREASONWIN,
    KENDREASONLOSE
} EndReason;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    //scheduled update
    void update(float dt);
    
    virtual void onAccelerate(Acceleration* pAccelerationValue);
    
    float randomValueBetween(float low, float hight);
    
    float getTimeTick();
    void setInvisible(Node *node);
    
    void touchesBegan(const std::vector<Touch*>& touches, Event *event);
    void touchesBegan(Touch *touch, Event *event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    SpriteBatchNode* _batchNode;
    Sprite *_ship;
    
    ParallNodeExtras *_backgroundNode;
    Sprite *_spacedust1;
    Sprite *_spacedust2;
    Sprite *_planetsunrise;
    Sprite *_galaxy;
    Sprite *_spacialanomaly;
    Sprite *_spacialanomaly2;
    float _shipPointsPerSecY;
    Vector<Sprite*> *_asteroids;
    int _nextAsteroid;
    float _nexAsteroidSpawn;
    Vector<Sprite* > *_shipLasers;
    int _nextShipLaser;
    int _lives;
    double _gameOverTime;
    bool _gameOver;
    EndGamePopup *mEndGamePopup;

private:
    void endScene(EndReason endReason);
    void restartTapped(Object* obj);
    
};

#endif // __HELLOWORLD_SCENE_H__
