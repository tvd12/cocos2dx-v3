//
//  ILabelSource.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 8/4/14.
//
//

#ifndef __DragonVideoPoker__ILabelSource__
#define __DragonVideoPoker__ILabelSource__

#include <iostream>

using namespace std;

class ILabelSource {
public:
    ILabelSource();
    virtual void updateValue(const long long &);
    inline const long long getValue() {return mValue;}
    bool &isChanged() { return mIsChanged; }
protected:
    long long mValue;
    bool mIsChanged;
};

#endif /* defined(__DragonVideoPoker__ILabelSource__) */
