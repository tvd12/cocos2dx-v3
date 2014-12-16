//
//  TextUtils.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 9/18/13.
//
//

#include "TextUtils.h"
#include "support/ccUTF8.h"

static const char utf8_skip_data[256] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
    5, 5, 5, 6, 6, 1, 1
};

static const char *const g_utf8_skip = utf8_skip_data;

#define cc_utf8_next_char(p) (char *)((p) + g_utf8_skip[*(unsigned char *)(p)])

TextUtils::TextUtils()
{
    
}

const char * TextUtils::TextFitInSize(const char *text,
                                      const char *fontName,
                                      float fontSize,
                                      CCSize size,
                                      CCTextAlignment hAlignment,
                                      CCVerticalTextAlignment vAlignment,
                                      CCSize maxSize,
                                      long maxTextLen)
{
    // it fitted -> got it!!!
    if (isTextFittedInSize(text, fontName, fontSize, size, hAlignment, vAlignment, maxSize)) {
        return text;
    }
    
    // modify text
    // get the first chars with ...
    CCString *str;
    long len = maxTextLen - 3;
    while (true) {
        str = CCString::create(getFirstUtf8String(text, len));
        CCLOG("text = %s", str->getCString());
        
        if (isTextFittedInSize(str->getCString(), fontName,
                               fontSize, size,
                               hAlignment, vAlignment, maxSize)) {
            return str->getCString();
        }
        else {
            len--;
        }
    }
    
    return "";
}

const char *TextUtils::getFirstUtf8String(const char *text, long maxTextLen)
{
    std::string str = std::string(text);
    const char *str_i = text;                       // string iterator
    const char *end   = text + strlen(text) + 1;    // end iterator
    
    std::string shortText; // result
    
    int strCnt = 0; // utf char counter
    
    do
    {
        str_i = cc_utf8_next_char(str_i);
        strCnt++;
        
        if (strCnt == maxTextLen) // my maximum nickname len
        {
            shortText = str.substr(0, (strlen(text) - strlen(str_i))) + "..."; // addd dots after cut
            break;
        }
    } while (str_i < end);
    
    if (shortText.empty()) // if no cut use the org nickname
    {
        return text;
    }
    
    return shortText.c_str();
}

bool TextUtils::isTextFittedInSize(const char *text,
                                   const char *fontName,
                                   float fontSize,
                                   CCSize size,
                                   CCTextAlignment hAlignment,
                                   CCVerticalTextAlignment vAlignment,
                                   CCSize maxSize)
{
    bool ret = false;
    CCTexture2D *tex = new CCTexture2D();
    tex->initWithString(text, fontName, fontSize, size, hAlignment, vAlignment);
    float texHeight = tex->getContentSize().height;
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    float scaleY = pEGLView->getScaleY();
    float contentScale = CC_CONTENT_SCALE_FACTOR();
    if (texHeight / scaleY * contentScale <= maxSize.height / contentScale) {
        ret = true;
    }
    
    tex->release();
    return ret;
}

int TextUtils::countUTF8String(const char * text)
{
    int count = 0;
    
    std::string str = std::string(text);
    const char *str_i = text;                       // string iterator
    const char *end   = text + strlen(text) + 1;    // end iterator
    
    do
    {
        str_i = cc_utf8_next_char(str_i);
        count++;
        
    } while (str_i < end);
    
    return count;
}

#pragma mark - currency text

const char * TextUtils::TextFromCurrencyNumber(long long number)
{
    std::string currencyFormat;
    float currency = number;
    CCString *currencyText;
    
    // hang don vi
    if (number < 1000) {
        currencyText = CCString::createWithFormat("%lld", number);
        return currencyText->getCString();
    }
    // hang nghin (K)
    else if (number < 1000000) {
        currency = currency / 1000.0f;
        if (currency < 10.0f) {
            currencyFormat = "%0.3fK";
        }
        else if (currency < 100.0f) {
            currencyFormat = "%0.2fK";
        }
        else if (currency < 1000.0f) {
            currencyFormat = "%0.1fK";
        }
    }
    // hang trieu (M)
    else if (number < 1000000000) {
        currency = currency / 1000000.0f;
        if (currency < 10.0f) {
            currencyFormat = "%0.3fM";
        }
        else if (currency < 100.0f) {
            currencyFormat = "%0.2fM";
        }
        else if (currency < 1000.0f) {
            currencyFormat = "%0.1fM";
        }
    }
    // hang ty (B)
    else if (number < 1000000000000) {
        currency = currency / 1000000000.0f;
        if (currency < 10.0f) {
            currencyFormat = "%0.3fB";
        }
        else if (currency < 100.0f) {
            currencyFormat = "%0.2fB";
        }
        else if (currency < 1000.0f) {
            currencyFormat = "%0.1fB";
        }
    }
    // hang nghin ty (T)
    else if (number < 1000000000000000) {
        currency = currency / 1000000000000.0f;
        if (currency < 10.0f) {
            currencyFormat = "%0.3fT";
        }
        else if (currency < 100.0f) {
            currencyFormat = "%0.2fT";
        }
        else if (currency < 1000.0f) {
            currencyFormat = "%0.1fT";
        }
    }
    
    currencyText = CCString::createWithFormat(currencyFormat.c_str(), currency);
    
    // remove Zero value if need
    std::string str = std::string(currencyText->getCString());
    if (str.find('.')) {
        int index = str.length() - 2;
        while (true) {
            if (str[index] == '0' || str[index] == '.') {
                bool zeroRemoved = false;
                if (str[index] == '.') {
                    zeroRemoved = true;
                }
                str.replace(index, 1, "");
                index--;
                
                if (zeroRemoved) {
                    break;
                }
            }
            else {
                break;
            }
        }
        currencyText = CCString::create(str);
    }
    
    return currencyText->getCString();
}

const char * TextUtils::TextFromFloatNumber(float number)
{
    CCString *text = CCString::createWithFormat("%0.2f", number);
    
    // remove Zero value if need
    std::string str = std::string(text->getCString());
    if (str.find('.')) {
        int index = str.length() - 1;
        while (true) {
            if (str[index] == '0' || str[index] == '.') {
                bool zeroRemoved = false;
                if (str[index] == '.') {
                    zeroRemoved = true;
                }
                str.replace(index, 1, "");
                index--;
                
                if (zeroRemoved) {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    
    text = CCString::create(str);
    return text->getCString();
}

const char * TextUtils::ShortTextFromCurrencyNumber(long long number)
{
    std::string currencyFormat;
    int currency = number;
    CCString *currencyText;
    
    // hang don vi
    if (number < 1000) {
        currencyText = CCString::createWithFormat("%lld", number);
        return currencyText->getCString();
    }
    // hang nghin (K)
    else if (number < 1000000) {
        currency = currency / 1000;
        currencyFormat = "%dK";
    }
    // hang trieu (M)
    else if (number < 1000000000) {
        currency = currency / 1000000;
        currencyFormat = "%dM";
    }
    // hang ty (B)
    else if (number < 1000000000000) {
        currency = currency / 1000000000;
        currencyFormat = "%dB";
    }
    // hang nghin ty (T)
    else if (number < 1000000000000000) {
        currency = currency / 1000000000000;
        currencyFormat = "%dT";
    }
    
    currencyText = CCString::createWithFormat(currencyFormat.c_str(), currency);
    
    return currencyText->getCString();
}

