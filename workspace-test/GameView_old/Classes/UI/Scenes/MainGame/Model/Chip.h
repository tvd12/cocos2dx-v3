//
//  Chip.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/10/14.
//
//

#ifndef __DragonVideoPoker__Chip__
#define __DragonVideoPoker__Chip__

typedef enum CHIP_TYPE {
    CHIP_SMALL              = 0,
    CHIP_MEDIUM             = 1,
    CHIP_BIG                = 2,
} ChipType;


class Chip {
    
public:
	Chip(int type, int value);
    static Chip *create(int type, int value);
    
    int getType() { return mType;}
    int getValue() { return mValue;}
    
private:
	int mType, mValue;
};


#endif /* defined(__DragonVideoPoker__Chip__) */
