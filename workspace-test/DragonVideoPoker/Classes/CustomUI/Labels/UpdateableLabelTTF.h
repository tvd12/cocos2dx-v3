//
//  UpdateableLabelTTF.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 8/4/14.
//
//

#ifndef __DragonVideoPoker__UpdateableLabelTTF__
#define __DragonVideoPoker__UpdateableLabelTTF__

#include <string>

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ILabelSource;

class UpdateableLabelTTF : public CCLabelTTF {
public:
    static UpdateableLabelTTF* createWithSource(ILabelSource* pSource,
                                                const string& pFontName,
                                                const float& pFontSize,
                                                const float& pVelocity = 10,
                                                const int& pMinDeltaValue = 6,
                                                const int& pType = CURRENCY_LONG);
    bool init(ILabelSource* pSource,
              const string& pFontName,
              const float& pFontSize,
              const float& pVelocity = 10,
              const int& pMinDeltaValue = 6,
              const int& pType = CURRENCY_LONG);
    
    virtual void update(float dt);
    
    CC_SYNTHESIZE(ILabelSource*, mSource, Source);
    CC_SYNTHESIZE(long long, mCurrentValue, CurrentValue);
    
    static const int CURRENCY_LONG;
    static const int CURRENCY_SHORT;
    
private:
    void updateView();
    const string createLableText();
    bool mIsNeedUpdating;
    float mUpdatingVelocity;
    int mMinDeltaValue;
    int mLabelType;
};


#endif /* defined(__DragonVideoPoker__UpdateableLabelTTF__) */
