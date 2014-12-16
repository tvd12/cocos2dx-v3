//
//  ChartBoostHelper.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 1/21/13.
//
//

#ifndef __VideoPoker__ChartBoostHelper__
#define __VideoPoker__ChartBoostHelper__

#include <cocos2d.h>

class  ChartBoostHelper : public cocos2d::CCNode {
    
public:
    static ChartBoostHelper* sharedHelper();
    void showBonusInterstitial();
};

#endif /* defined(__VideoPoker__ChartBoostHelper__) */
