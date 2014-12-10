/*
 * TichTacToeGame.h
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#ifndef TICTACTOE_TICHTACTOEGAME_H_
#define TICTACTOE_TICHTACTOEGAME_H_

namespace algorithm {

class Board;

class TichTacToeGame {
public:
	TichTacToeGame();

	void computerMakeMove(int depth);
	void getNextMoveFromUser();
    void getNextMoveFromUser(int x, int y);

	Board* getInitNode();

	inline Board* getCurrent() { return mCurrent; }

	~TichTacToeGame();
protected:
	Board* mCurrent;
	Board* mInit;
};
}

#endif /* TICTACTOE_TICHTACTOEGAME_H_ */
