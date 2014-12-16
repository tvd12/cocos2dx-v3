//
//  ILabelSource.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 8/4/14.
//
//

#include "ILabelSource.h"

ILabelSource::ILabelSource() :
mValue(0),
mIsChanged(false){
    
}
void ILabelSource::updateValue(const long long &pValue) {
    mValue = pValue;
}
