/*
 * Board.h
 *
 *  Created on: Mar 28, 2015
 *      Author: dungtavan
 */

#ifndef MODEL_BOARD_H_
#define MODEL_BOARD_H_

#include <string>
#include <vector>

class Square;

class Board {
public:
	Board();

	void prepare();
    void init();
    
    void setRequiredString(const std::string &pVisibleString);

	virtual ~Board();

protected:
	int mRow;
	int mColumn;
    int mSelectedIndex;
    int mNumberOfCharacter;
    
    std::string mHiddenString;
    std::string mVisibleString;
    std::string mRequiredString;

    std::vector<int> mSelectedIndexes;
    std::vector<int> mCorrectIndexes;
	std::vector<Square*> mSquares;
};

#endif /* MODEL_BOARD_H_ */
