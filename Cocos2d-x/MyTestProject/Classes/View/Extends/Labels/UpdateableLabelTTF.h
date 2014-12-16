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

typedef enum CURRENCY_TYPE {
    tdgCurrencyLong                                 = 0,
    tdgCurrencyShort                                = 1,
} CurrencyType;

USING_NS_CC;
using namespace std;

class ILabelSource;

class UpdateableLabelTTF : public Label {
public:
    static UpdateableLabelTTF* createWithSource(ILabelSource* pSource,
                                                const string& pFontName,
                                                const float& pFontSize,
                                                const float& pVelocity = 10,
                                                const int& pMinDeltaValue = 6,
                                                const int& pType = tdgCurrencyLong);
    bool init(ILabelSource* pSource,
              const string& pFontName,
              const float& pFontSize,
              const float& pVelocity = 10,
              const int& pMinDeltaValue = 6,
              const int& pType = tdgCurrencyLong);
    
    virtual void update(float dt);
    
    void updateLabelSource(ILabelSource* source);
    
    CC_SYNTHESIZE(ILabelSource*, mSource, Source);
    CC_SYNTHESIZE(long long, mCurrentValue, CurrentValue);
    
private:
    void updateView();
    const char* createLableText();
    bool mIsNeedUpdating;
    float mUpdatingVelocity;
    int mMinDeltaValue;
    int mLabelType;
};


#endif /* defined(__DragonVideoPoker__UpdateableLabelTTF__) */
