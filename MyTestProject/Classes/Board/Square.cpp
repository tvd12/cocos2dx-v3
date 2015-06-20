/*
 * Square.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: dungtavan
 */

#include "Square.h"

using namespace std;

Square::Square() :
mString(""),
mStringIndex(0) {
    
}

Square::Square(const std::string &str, int index) :
mString(str),
mStringIndex(index) {
}

void Square::setString(const std::string &str) {
	mString = str;
}

void Square::setStringIndex(int index) {
	mStringIndex = index;
}

string Square::getString() {
	return mString;
}

int Square::getStringIndex() {
	return mStringIndex;
}

Square::~Square() {
}

