//
//  TextUtils.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/18/13.
//
//

#ifndef __Dragon_Poker__TextUtils__
#define __Dragon_Poker__TextUtils__

#include "SingLeton.h"
#include "cocos2d.h"

USING_NS_CC;

class TextUtils : public SingLeton<TextUtils>
{
public:
	TextUtils();
    
    const char * TextFitInSize(const char *text,
                               const char *fontName,
                               float fontSize,
                               CCSize size,
                               CCTextAlignment hAlignment,
                               CCVerticalTextAlignment vAlignment,
                               CCSize maxSize,
                               long maxTextLen);
    
    const char * TextFromCurrencyNumber(long long number);
    const char * TextFromFloatNumber(float number);

    const char * ShortTextFromCurrencyNumber(long long number);

    int countUTF8String(const char * text);
    const char *getFirstUtf8String(const char *text, long maxTextLen);
    
private:
    bool isTextFittedInSize(const char *text,
                            const char *fontName,
                            float fontSize,
                            CCSize size,
                            CCTextAlignment hAlignment,
                            CCVerticalTextAlignment vAlignment,
                            CCSize maxSize);
};

/// macro to get TextFitInSize
#define TEXTFIT(k, l, m, n, o, p, q, r) (TextUtils::getSingleton().TextFitInSize(k, l, m, n, o, p, q, r))

/// macro to get TextFromCurrencyNumber
#define TEXT() TextUtils::getSingleton()
#define CURRENCY_SHORT(k) (TextUtils::getSingleton().TextFromCurrencyNumber(k))

#endif /* defined(__Dragon_Poker__TextUtils__) */
