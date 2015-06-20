/*
 * Board.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: dungtavan
 */

#include "Board.h"
#include "Square.h"
#include "StringUtil.h"
#include "tounicupper.h"

using namespace std;
using namespace cocos2d;

Board::Board() :
mRow(3),
mColumn(3),
mSelectedIndex(-1),
mVisibleString(""),
mHiddenString(""),
mSquares(vector<Square*>()),
mSelectedIndexes(vector<int>()),
mCorrectIndexes(vector<int>())
{

}


void Board::prepare() {
    init();
    
    int size = mRow * mColumn;
    int matrixSize = size;
    int numberArr[size];
    bool statusArr[size];
    vector<string> squareStrings = vector<string>(size);
    for(int i = 0 ; i < size ; i++) {
        numberArr[i] = i;
        statusArr[i] = true;
        squareStrings[i] = "";
    }
    std::u16string u16VisibleStr, u16RequiredStr;
    StringUtils::UTF8ToUTF16(mVisibleString, u16VisibleStr);
    StringUtils::UTF8ToUTF16(mRequiredString, u16RequiredStr);
    
    unsigned long length = u16VisibleStr.length();
    CCLOG("vi = %s, re = %s, lenth = %ld", mVisibleString.c_str(), mRequiredString.c_str(), length);
    int invalidCharCount = 0;
    for(int i = 0, t = 0; t < length ; i++, t++) {
        if(!tvd::StringUtil::isValidCharacter(u16VisibleStr.at(t))) {
            invalidCharCount ++;
            i --;
            continue;
        }
        int number = 0;
        if(size == 0) {
            for(int z = 0 ; z < squareStrings.size() ; z++) {
                if(squareStrings[z].length() == 0) {
                    number = z;
                    break;
                }
            }
        }
        else {
            int index = arc4random() % (size);
            number = numberArr[index];
        }
        squareStrings[number] = tvd::StringUtil::unicodeToUTF8(u16RequiredStr.at(i));
        mSquares[number]->setString(squareStrings[number]);
        mSquares[number]->setStringIndex(i + invalidCharCount);
        statusArr[number] = false;
        
        CCLOG("%d", number);
        
        int currentRow 	= number / mColumn;
        int begin 		= currentRow * mColumn;
        int last		= (currentRow + 1) * mColumn;
        
        //check square
        //1.1
        if(number - 1 >= begin
	        		&& number + mColumn < mRow * mColumn
	        		&& squareStrings[number + mColumn].length() > 0
	        		&& squareStrings[number + mColumn - 1].length() > 0) {
            statusArr[number - 1] = false;
        }
        //1.2
        else if(number - 1 >= begin
                && number + mColumn < mRow * mColumn
                && squareStrings[number - 1].length() > 0
                && squareStrings[number + mColumn].length() > 0) {
            statusArr[number - 1 + mColumn] = false;
        }
        //1.3
        else if(number - 1 >= begin
                && number + mColumn < mRow * mColumn
                && squareStrings[number - 1].length() > 0
                && squareStrings[number + mColumn - 1].length() > 0) {
            statusArr[number + mColumn] = false;
        }
        //2.1
        else if(number - 1 >= begin
                && number - mColumn > 0
                && squareStrings[number - 1].length() > 0
                && squareStrings[number - mColumn - 1].length() > 0) {
            statusArr[number - mColumn] = false;
        }
        //2.2
        else if(number - 1 >= begin
                && number - mColumn > 0
                && squareStrings[number - 1].length() > 0
                && squareStrings[number - mColumn].length() > 0) {
            statusArr[number - mColumn - 1] = false;
        }
        //2.3
        else if(number - 1 >= begin
                && number - mColumn > 0
                && squareStrings[number - mColumn].length() > 0
                && squareStrings[number - mColumn - 1].length() > 0) {
            statusArr[number - 1] = false;
        }
        //3.1
        else if(number + 1 < last
                && number - mColumn > 0
                && squareStrings[number - mColumn].length() > 0
                && squareStrings[number - mColumn + 1].length() > 0) {
            statusArr[number + 1] = false;
        }
        //3.2
        else if(number + 1 < last
                && number - mColumn > 0
                && squareStrings[number - mColumn].length() > 0
                && squareStrings[number + 1].length() > 0) {
            statusArr[number - mColumn + 1] = false;
        }
        //3.3
        else if(number + 1 < last
                && number - mColumn > 0
                && squareStrings[number - mColumn + 1].length() > 0
                && squareStrings[number + 1].length() > 0) {
            statusArr[number - mColumn] = false;
        }
        //4.1
        else if(number + 1 < last
                && number + mColumn < mRow * mColumn
                && squareStrings[number + 1].length() > 0
                && squareStrings[number + mColumn + 1].length() > 0) {
            statusArr[number + mColumn - 1] = false;
        }
        //4.2
        else if(number + 1 < last
                && number + mColumn < mRow * mColumn
                && squareStrings[number + 1].length() > 0
                && squareStrings[number + mColumn].length() > 0) {
            statusArr[number + mColumn + 1] = false;
        }
        //4.3
        else if(number + 1 < last
                && number + mColumn < mRow * mColumn
                && squareStrings[number + mColumn].length() > 0
                && squareStrings[number + mColumn + 1].length() > 0) {
            statusArr[number + 1] = false;
        }
        
        //check row
        //* A A * *
        if(number - 1 >= begin //&& !statusArr[number - 1]
           && squareStrings[number - 1].length() != 0) {
            if(number - 2 >= begin) {
                statusArr[number - 2] = false;
            }
            if(number + 1 < last) {
                statusArr[number + 1] = false;
            }
        }
        //* * A A *
        else if(number + 1 < last //&& !statusArr[number + 1]
                && squareStrings[number + 1].length() != 0) {
            if(number + 2 < last) {
                statusArr[number + 2] = false;
            }
            if(number - 1 >= begin) {
                statusArr[number - 1] = false;
            }
        }
        //* A * A *
        else if(number - 2 >= begin //&& !statusArr[number - 2]
                && squareStrings[number - 2].length() != 0) {
            statusArr[number - 1] = false;
        }
        else if(number + 2 < last //&& !statusArr[number + 2]
                && squareStrings[number + 2].length() != 0) {
            statusArr[number + 1] = false;
        }
        
        //check column
        if(number - mColumn >= 0 //&& !statusArr[number - mColumn]
           && squareStrings[number - mColumn].length() != 0) {
            if(number - 2*mColumn >= 0) {
                statusArr[number - 2*mColumn] = false;
            }
            if(number + mColumn < matrixSize) {
                statusArr[number + mColumn] = false;
            }
        }
        
        else if(number + mColumn < matrixSize //&& !statusArr[number + mColumn]
                && squareStrings[number + mColumn].length() != 0) {
            if(number + 2*mColumn < matrixSize) {
                statusArr[number + 2*mColumn] = false;
            }
            if(number - mColumn >= 0) {
                statusArr[number - mColumn] = false;
            }
        }
        else if(number - 2*mColumn >= 0 //&& !statusArr[number - 2*mColumn]
                && squareStrings[number - 2*mColumn].length() != 0) {
            statusArr[number - 1*mColumn] = false;
        }
        else if(number + 2*mColumn < matrixSize //&& !statusArr[number + 2*mColumn]
                && squareStrings[number + 2*mColumn].length() != 0) {
            statusArr[number + 1*mColumn] = false;
        }
        
        int k = 0;
        int lostSize = 0;
        for(int j = 0 ; j < matrixSize ; j++) {
            if(statusArr[j]) {
                numberArr[k++] = j;
            } else {
                lostSize++;
            }
        }
        size = matrixSize - lostSize;
    }
    
    unsigned long strLength = u16RequiredStr.length();
//    string str = (strLength < 10) ? " 0%d" : " %d";
//    str = D::string.main_game_layer_character + str;
//    mStringLengthLabel->setString(StringUtils::format(str.c_str(), strLength));
    
    CCLOG("================ Done! ==================");
}


void Board::init() {
    int size = mRow * mColumn;
    int squareDatasSize = (int)mSquares.size();
    for(int i = squareDatasSize ; i < size ; i++) {
        mSquares.push_back(new Square());
    }
    for(int i = 0 ; i < size ; i++) {
        if(!mSquares[i]) {
            mSquares[i] = new Square();
        } else {
            mSquares[i]->setString("");
            mSquares[i]->setStringIndex(-1);
        }
    }
    
    int validChars = 0, length = 0;
    std::u16string u16str;
    StringUtils::UTF8ToUTF16(mHiddenString, u16str);
    for(int index = 0; index < u16str.length() ; index++) {
        char16_t ch = u16str.at(index);
        string str = tvd::StringUtil::unicodeToUTF8(ch);
        //        CCLOG("str = %s", str.c_str());
        length += str.length();
        if(ch != ' ') {
            validChars ++;
            if(validChars == mNumberOfCharacter) {
                break;
            }
        }
    }
    mVisibleString = tvd::StringUtil::adjustString(string(mHiddenString.c_str(), length));
    setRequiredString(mVisibleString);
    
}

void Board::setRequiredString(const string &pVisibleString) {
    string upperString = "";
    mRequiredString = "";
    locale loc;
    
    std::u16string utf16str;
    StringUtils::UTF8ToUTF16(pVisibleString, utf16str);
    //upper visible string
    for(int i = 0 ; i < utf16str.length() ; i++) {
        upperString += tvd::StringUtil::unicodeToUTF8(toupperUnic(utf16str[i]));
    }
    mVisibleString = upperString;
    
    for(int i = 0 ; i < utf16str.length() ; i++) {
        if(tvd::StringUtil::isValidCharacter(utf16str[i])) {
            mRequiredString += tvd::StringUtil::unicodeToUTF8(toupperUnic(utf16str[i]));
        }
    }
    
    CCLOG("required string is %s", mRequiredString.c_str());
}

Board::~Board() {
}
