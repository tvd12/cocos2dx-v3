//
//  UserRecord.h
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#ifndef __Earlybird__UserRecord__
#define __Earlybird__UserRecord__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class UserRecord {
public:
    
    static UserRecord* getInstance();
    
    virtual bool init();
    
    /**
     * @var key : the key that point the the data which will be sotred
     *
     * @var data: the data will be stored
     *
     * as a matter of fact, the score will be stored in local memory with XML format.
     */
    void saveTheBestScore(int score);
    
    /*
     * @var key: get the data with the key we used to stored it.
     *
     * @return the data we have been stored, with the attached key
     */
    int getTheBestScore();
    
    virtual ~UserRecord();
    
protected:
    
    int mTheBestScore;
    
private:
    UserRecord();
    UserRecord(const UserRecord &) = delete;
    void operator = (const UserRecord &) = delete;
};

#endif /* defined(__Earlybird__UserRecord__) */
