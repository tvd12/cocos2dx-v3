//
//  UpdateableLabelTTF.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 8/4/14.
//
//

#include "UpdateableLabelTTF.h"
#include "ILabelSource.h"
#include "GameParams.h"
#include "TextUtils.h"

const int UpdateableLabelTTF::CURRENCY_LONG = 1001;
const int UpdateableLabelTTF::CURRENCY_SHORT = 1002;

UpdateableLabelTTF* UpdateableLabelTTF::createWithSource(ILabelSource* pSource,
                                                         const string& pFontName,
                                                         const float& pFontSize,
                                                         const float& pVelocity,
                                                         const int& pMinDeltaValue,
                                                         const int& pType) {
    UpdateableLabelTTF* pRet = new UpdateableLabelTTF;
    pRet->init(pSource, pFontName, pFontSize, pVelocity, pMinDeltaValue, pType);
    pRet->autorelease();
    
    return pRet;
    
}
bool UpdateableLabelTTF::init(ILabelSource* pSource,
                              const string& pFontName,
                              const float& pFontSize,
                              const float& pVelocity,
                              const int& pMinDeltaValue,
                              const int& pType) {
    mSource = pSource;
    mIsNeedUpdating = false;
    mUpdatingVelocity = pVelocity;
    mMinDeltaValue = pMinDeltaValue;
    mLabelType = pType;
    mCurrentValue = pSource->getValue();
    CCLabelTTF::initWithString(createLableText().c_str(),
                               pFontName.c_str(),
                               pFontSize);
    
    scheduleUpdate();
    return true;
}

void UpdateableLabelTTF::update(float dt) {
    if(mSource->isChanged()) {
        mIsNeedUpdating = true;
        updateView();
    }
}

void UpdateableLabelTTF::updateView() {
    if (mIsNeedUpdating == false) {
        return;
    }
    
    if (mSource->getValue() > mCurrentValue) {
        // Update displayValue
        long long deltaValue = llabs(mSource->getValue() - mCurrentValue);
        if (deltaValue < 6) {
            mCurrentValue += deltaValue;
        }
        else {
            deltaValue = (deltaValue / mUpdatingVelocity);
            
            if (deltaValue <= 1) {
                mCurrentValue += deltaValue + 1;
            }
            else {
                mCurrentValue += arc4random() % deltaValue + 1;
            }
        }
        if (mCurrentValue > mSource->getValue()) {
            mCurrentValue = mSource->getValue();
        }
        
        // Update to label
        this->setString(createLableText().c_str());
    }
    else if (mSource->getValue() < mCurrentValue) {
        // Update displayValue
        long long deltaValue = llabs(mSource->getValue() - mCurrentValue);
        if (deltaValue < 6) {
            mCurrentValue -= deltaValue;
        }
        else {
            mCurrentValue = (deltaValue / mUpdatingVelocity);
            
            if (deltaValue <= 1) {
                mCurrentValue -= deltaValue + 1;
            }
            else {
                mCurrentValue -= arc4random() % deltaValue + 1;
            }
        }
        if (mCurrentValue < mSource->getValue()) {
            mCurrentValue = mSource->getValue();
        }
        
        this->setString(createLableText().c_str());
    }
    else {
        mIsNeedUpdating = false;
        mSource->isChanged() = false;
    }
}

const string UpdateableLabelTTF::createLableText() {
    if(mLabelType == CURRENCY_LONG) {
        return FormatWithCommas<const long long>(mCurrentValue);
    } else if(mLabelType == CURRENCY_SHORT) {
        return string(CURRENCY_SHORT(mCurrentValue));
    }
    return "0";
}