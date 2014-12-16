#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
















































//#ifndef __HELLOWORLD_SCENE_H__
//#define __HELLOWORLD_SCENE_H__
//
//#include <time.h>
//#include <math.h>
//#include <string>
//
//#include "cocos2d.h"
//
//using namespace std;
//using namespace cocos2d;
//
//class BonusTimer {
//public:
//    
//    BonusTimer() {
//        time_t currentTime, lastBonus;
//        time(&currentTime);
//        string lastTimeStr = UserDefault::getInstance()
//        ->getStringForKey("last_time", std::to_string(currentTime));
//        mLastTime       = (time_t)(atof(lastTimeStr.c_str()));
//        mLiveBonus      = (long long)(UserDefault::getInstance()
//                                      ->getIntegerForKey("live_bonus", 5));
//        string lastBonusStr = UserDefault::getInstance()
//        ->getStringForKey("last_bonus", std::to_string(mLastTime - 60));
//        lastBonus   = (time_t)(atof(lastBonusStr.c_str()));
//        
//        long long liveBonus = mLiveBonus;
//        
//        CCLOG("ceil what = %ld, live bonus = %lld", currentTime - mLastTime, liveBonus);
//        CCLOG("bonus hehe mLastTime = %ld, lastBonus = %ld, currentTime = %ld", mLastTime, lastBonus, currentTime);
//        
//        if(currentTime >= mLastTime) {
//            time_t offset = abs(mLastTime - lastBonus);
//            liveBonus += (long long)ceil(offset/5.0f);
//            CCLOG("ceil is: %ld", abs(mLastTime - lastBonus));
//            mLastTime = currentTime + 60;
//            UserDefault::getInstance()
//            ->setStringForKey("last_time", std::to_string(mLastTime));
//        }
//        else if(currentTime >=  mLastTime - 5 * 4) {
//            if(lastBonus >= mLastTime - 5 * 4) {
//                time_t offset = currentTime - lastBonus;
//                liveBonus += (long long)(offset / 5);
//                CCLOG("ceil is if 1: %ld", currentTime - lastBonus);
//            }
//            else {
//                time_t offset = currentTime - (mLastTime - 5 * 4);
//                liveBonus += (long long)(offset / 5 + 1);
//                CCLOG("ceil is if 2: %ld", currentTime - (mLastTime - 5 * 4));
//            }
//            
//        }
//        
//        if(liveBonus != mLiveBonus) {
//            
//            CCLOG("live bonus2 = %lld", liveBonus);
//            mLiveBonus = (liveBonus > 5) ? 5 : liveBonus;
//            
//            UserDefault::getInstance()
//            ->setIntegerForKey("live_bonus", (int)mLiveBonus);
//        }
//        
//        update();
//        
//    }
//    
//    void update() {
//        time_t currentTime;
//        time(&currentTime);
//        int liveBonus = mLiveBonus;
//        
//        if(currentTime >= mLastTime) {
//            liveBonus += 1;
//            mLastTime = currentTime + 60;;
//            UserDefault::getInstance()
//            ->setStringForKey("last_time", std::to_string(mLastTime));
//            CCLOG("bonus hehe last_time_in_update = %ld", mLastTime);
//        }
//        else if(currentTime    ==  mLastTime - 5 * 1
//                || currentTime ==  mLastTime - 5 * 2
//                || currentTime ==  mLastTime - 5 * 3
//                || currentTime ==  mLastTime - 5 * 4) {
//            liveBonus += 1;
//            UserDefault::getInstance()
//            ->setIntegerForKey("live_bonus", (int)liveBonus);
//        }
//        
//        mLiveBonus = (liveBonus > 5) ? 5 : liveBonus;
//        
//        long time = (mLastTime - currentTime);
//        
//        mHour = time / 3600;
//        mMinute = (time - mHour * 3600) / 60;
//        mSecond = time - mHour * 3600 - mMinute * 60;
//    }
//    
//    const string toString() {
//        string result = string().append(to_string(mHour))
//        .append("h").append(to_string(mMinute))
//        .append("\"").append(to_string(mSecond)).append("'");
//        
//        return result;
//    }
//    
//    void updateLiveBonus(int pLive) {
//        if(mLiveBonus <= 0) {
//            return;
//        }
//        mLiveBonus += pLive;
//        UserDefault::getInstance()
//        ->setIntegerForKey("live_bonus", (int)mLiveBonus);
//    }
//    
//    CC_SYNTHESIZE(int, mHour, Hour);
//    CC_SYNTHESIZE(int, mMinute, Minute);
//    CC_SYNTHESIZE(int, mSecond, Second);
//    CC_SYNTHESIZE(long long, mLiveBonus, LiveBonus);
//    
//protected:
//    time_t mLastTime;
//    
//};
//
//class HelloWorld : public cocos2d::Layer
//{
//public:
//    // there's no 'id' in cpp, so we recommend returning the class instance pointer
//    static cocos2d::Scene* createScene();
//
//    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//    virtual bool init();
//    
//    virtual void update(float dt);
//    
//    // a selector callback
//    void menuCloseCallback(cocos2d::Ref* pSender);
//    
//    // implement the "static create()" method manually
//    CREATE_FUNC(HelloWorld);
//    
//protected:
//    void updateTimingLabel();
//    void loginMenuItemCallback(Ref* pSender);
//    
//    Label *mTimingLabel;
//    Label *mLiveLabel;
//    BonusTimer* mBonusTimer;
//};
//
//#endif // __HELLOWORLD_SCENE_H__
