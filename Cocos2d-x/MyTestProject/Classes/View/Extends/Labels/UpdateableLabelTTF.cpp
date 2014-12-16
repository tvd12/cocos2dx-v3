//
//  UpdateableLabelTTF.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 8/4/14.
//
//

#include "UpdateableLabelTTF.h"
#include "ILabelSource.h"

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
                              const int& pType)
{
    updateLabelSource(pSource);
    mIsNeedUpdating = false;
    mUpdatingVelocity = pVelocity;
    mMinDeltaValue = pMinDeltaValue;
    mLabelType = pType;
    Label::setString(createLableText());
    TTFConfig ttfConfig(pFontName.c_str(),
                        pFontSize,
                        GlyphCollection::DYNAMIC);
    Label::setTTFConfig(ttfConfig);
    
    scheduleUpdate();
    
    return true;
}

void UpdateableLabelTTF::updateLabelSource(ILabelSource* source)
{
    mSource = source;
    if (source) {
        mCurrentValue = source->getValue();
    }
    else {
        mCurrentValue = 0;
    }

    this->setString(createLableText());
    mIsNeedUpdating = false;
    mSource->setIsChanged(false);
}

void UpdateableLabelTTF::update(float dt)
{
    if(mSource != NULL && mSource->getIsChanged()) {
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
        this->setString(createLableText());
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
        
        this->setString(createLableText());
    }
    else {
        this->setString(createLableText());
        mIsNeedUpdating = false;
        mSource->setIsChanged(false);
    }
}

const char* UpdateableLabelTTF::createLableText()
{
    if (mSource) {
        if(mLabelType == tdgCurrencyLong) {
//            return CURRENCY_LONG(mCurrentValue);
        }
        else if(mLabelType == tdgCurrencyShort) {
//            return CURRENCY_SHORT(mCurrentValue);
        }
        
        return "0";
    }
    else {
        return "";
    }
}