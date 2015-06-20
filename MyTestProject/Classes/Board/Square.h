/*
 * Square.h
 *
 *  Created on: Mar 28, 2015
 *      Author: dungtavan
 */

#ifndef MODEL_SQUARE_H_
#define MODEL_SQUARE_H_

#include <string>

class Square {
public:
    Square();
	Square(const std::string &str, int index);
	virtual ~Square();

	void setString(const std::string &str);
	std::string getString();

	void setStringIndex(int index);
	int getStringIndex();

protected:
	std::string mString;
	int mStringIndex;
};

#endif /* MODEL_SQUARE_H_ */
