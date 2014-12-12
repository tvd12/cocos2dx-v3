//
//  ILabelSource.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 8/4/14.
//
//

#ifndef __DragonVideoPoker__ILabelSource__
#define __DragonVideoPoker__ILabelSource__

class ILabelSource {
public:
    ILabelSource();
    virtual void setValue(const long long);
    inline const long long getValue() {return mValue;}
    
    bool getIsChanged() { return mIsChanged; }
    void setIsChanged(bool isChanged) { mIsChanged = isChanged; }
    
protected:
    long long mValue;
    bool mIsChanged;
};

#endif /* defined(__DragonVideoPoker__ILabelSource__) */
