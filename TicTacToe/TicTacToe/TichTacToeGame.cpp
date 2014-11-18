/*
 * TichTacToeGame.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#include <vector>
#include <iostream>

#include "TichTacToeGame.h"

#include "TicTacToe.h"
#include "Board.h"

using namespace std;

TichTacToeGame::TichTacToeGame() :
mCurrent(NULL),
mInit(NULL){
	vector<GridEntry> *values = new vector<GridEntry>(9, empty);
	mInit = new Board(values, true);
	mCurrent = mInit;
}

void TichTacToeGame::computerMakeMove(int depth) {
	Board* next = mCurrent->findNextMove(depth);
	if(next != NULL) {
        delete mCurrent;
		mCurrent = next;
	}
}

void TichTacToeGame::getNextMoveFromUser() {
	if(mCurrent->isTerminalNode()) {
		return;
	}

	do {
		cout << "\nCurrent Node is\n" << mCurrent->toString() << "\nPlease type in x:[0-2]: ";
		int x = 0, y = 0;
		cin >> x;
		cout << "Please type in y:[0-2]: ";
		cin >> y;
		cout << "x = " << x << ", y = " << y << "\n";
		mCurrent = mCurrent->getChildAtPosition(x, y);
		cout << mCurrent->toString();

	} while(0);
}

Board* TichTacToeGame::getInitNode() {
	return mInit;
}

TichTacToeGame::~TichTacToeGame() {
	if(mCurrent) {
		delete mCurrent;
		mCurrent = NULL;
	}
	if(mInit) {
		delete mInit;
		mInit = NULL;
	}
}
