//
//  Number.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/14/15.
//
//

#ifndef __Earlybird__Number__
#define __Earlybird__Number__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

typedef enum _gravity {
    GRAVITY_CENTER = 1,
    GRAVITY_LEFT,
    GRAVITY_RIGHT
} Gravity;

/**
 * The distance between two number
*/

#define NUMBER_INTERVAL 4

class NumberSeries {
public:
    
    NumberSeries();
    
    static NumberSeries* create();
    
    virtual bool init();
    
    void loadNumber(string fmt, int base = 0);
    
    SpriteFrame* at(int index);
    
    ~NumberSeries();
    
protected:
    vector<SpriteFrame*> mNumberOfSeries;
};

/**
 * @class Number
 * Used to create the number sprite from texture and image, and
 * give some useful support
 */

class Number {
public:
    Number();
    
    static Number* getInstance();
    
    static void destroyInstance();
    
    virtual bool init();
    
    /**
     * cocos2d constructor
     *
     * @var fmt The file name like 'number_score_%2d', constructor will get number_score_00
     * to number_score_09 present the number 0 to 9
     *
     * @var base If the serious file name is not start with 0, you can set base to fix it
     *
     * #return instnce of number
     */
    virtual bool loadNumber(string name, string fmt, int base = 0);
    
    /**
     * convert the integer number to Sprite present the number
     *
     * @var number The given number such as 4562
     *
     * @return the Node presenting the given number
     */
    Node* convert(string name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);
    
    
    ~Number();
    
protected:
    map<string, NumberSeries*> mNumberContainer;
};

#endif /* defined(__Earlybird__Number__) */
