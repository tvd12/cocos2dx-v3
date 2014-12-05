/*
 * Board.h
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#ifndef TICTACTOE_BOARD_H_
#define TICTACTOE_BOARD_H_

#include <vector>
#include <string>

#include "TicTacToe.h"

class Transform;

using namespace std;

class Board {
public:
	static bool isSameBoard(Board* a, Board* b, bool compareRecursiveScore);
	static bool isSimilarBoard(Board* a, Board* b);

	Board();
	Board(vector<GridEntry> *values, bool turnForPlayerX);
	Board* getChildAtPosition(int x, int y);
	bool isTerminalNode();
	vector<Board*> getChildren();

	int miniMaxShortVersion(int depth, int alpha, int beta, Board& childWithMax);
	int miniMax(int depth, bool needMax, int alpha, int beta, Board& childWithMax);

	Board* findNextMove(int depth);
	int getScoreForOneLine(vector<GridEntry>* values);
	void computeScore();
	Board* transformBoard(Transform* t);

	void copy(Board* other);

	string toString();

    int getRecursiveScore() { return mRecursiveScore; }
    bool isGameOver() { return mIsGameOver; }

	~Board();
protected:
	vector<GridEntry> *mValues;
	int mScore;
	int mTurnForPlayerX;
	int mRecursiveScore;
	bool mIsGameOver;
};

#endif /* TICTACTOE_BOARD_H_ */
