/*
 * Board.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#include <iostream>
#include <climits>
#include <cmath>

#include "Board.h"
#include "Point.h"
#include "Transform.h"

#define DELETE_PTR(ptr) \
if(ptr) { \
    delete ptr; \
    ptr = 0; \
}

Board::Board() :
mValues(NULL),
mScore(0),
mTurnForPlayerX(false),
mRecursiveScore(0),
mIsGameOver(false){

}

Board::Board(vector<GridEntry> *value, bool turnForPlayerX) :
mValues(value),
mScore(0),
mTurnForPlayerX(turnForPlayerX),
mRecursiveScore(0),
mIsGameOver(false){
	computeScore();
}

void Board::copy(Board* other) {
    if(mValues) {
        mValues->clear();
        mValues->insert(mValues->begin(),
                        other->mValues->begin(),
                        other->mValues->end());
    }
    else {
        this->mValues 		= new vector<GridEntry>(other->mValues->begin(),
			other->mValues->end());
    }
	this->mTurnForPlayerX 	= other->mTurnForPlayerX;
	this->mRecursiveScore	= other->mRecursiveScore;
	this->mIsGameOver		= other->mIsGameOver;
	this->mScore			= other->mScore;
}

//void Board::copy(Board &other) {
//        if(mValues) {
//            mValues->clear();
//            mValues->insert(mValues->begin(),
//                            other.mValues->begin(),
//                            other.mValues->end());
//        }
//        else {
//    this->mValues 		= new vector<GridEntry>(other.mValues->begin(),
//                                                other.mValues->end());
//        }
//    this->mTurnForPlayerX 	= other.mTurnForPlayerX;
//    this->mRecursiveScore	= other.mRecursiveScore;
//    this->mIsGameOver		= other.mIsGameOver;
//    this->mScore			= other.mScore;
//}

Board* Board::getChildAtPosition(int x, int y) {
	int i = x + y*3;
	vector<GridEntry> *newValues = new vector<GridEntry>(mValues->begin(), mValues->end());
	if(mValues->at(i) != empty) {
		char ch[200];
		string one = (mValues->at(i) == playerX) ? "PlayerX" : "PlayerY";
		sprintf(ch, "invalid index [%d, %d] is taken by %s",x, y, one.c_str());
		std::cout << string(ch);
        DELETE_PTR(mValues);
        DELETE_PTR(newValues);
		return NULL;
	}
	else {
        DELETE_PTR(mValues);
		newValues->at(i) = mTurnForPlayerX ? playerX : playerO;
		return new Board(newValues, !mTurnForPlayerX);
	}
    
}

bool Board::isTerminalNode() {
	if(mIsGameOver) {
		return true;
	}
	//if all entries are set, then it is a leaf node
	for(int i = 0 ; i < mValues->size() ; i++) {
		if(mValues->at(i) == empty) {
			return false;
		}
	}

	return true;
}

vector<Board*> Board::getChildren() {
	vector<Board*> boards = vector<Board*>();
	for(int i = 0 ; i < mValues->size() ; i++) {
		if(mValues->at(i) == empty) {
			vector<GridEntry> *newValues =
					new vector<GridEntry>(mValues->begin(), mValues->end());
			newValues->at(i) = mTurnForPlayerX ? playerX : playerO;
			boards.push_back(new Board(newValues, !mTurnForPlayerX));
		}
	}

	return boards;
}

//http://en.wikipedia.org/wiki/Alpha-beta_pruning
int Board::miniMaxShortVersion(int depth, int alpha, int beta, Board& childWithMax) {
	if(depth == 0 || isTerminalNode()) {
		//When it is turn for PlayO, we need to find the minimum score.
		mRecursiveScore = mScore;
		return mTurnForPlayerX ? mScore : -mScore;
	}
	vector<Board*> childrens = getChildren();
	for(int i = 0 ; i < childrens.size() ; i++) {
		Board dummy = Board();
		int score = - (childrens[i]->miniMaxShortVersion(depth - 1, -beta, -alpha, dummy));
		
        if(alpha < score) {
			alpha = score;
			childWithMax.copy(childrens[i]);
			if(alpha >= beta) {
//				cout << "alpha = " << alpha << " beta " << beta << "\n";
				break;
			}
		}
//		if(childrens[i]) {
//			delete childrens[i];
//			childrens[i] = NULL;
//		}
	}
    for(int i = 0 ; i < childrens.size() ; i++) {
        DELETE_PTR(childrens[i]);
    }
	childrens.clear();

	mRecursiveScore = alpha;
	return alpha;
}

//http://www.ocf.berkeley.edu/~yosenl/extras/alphabeta/alphabeta.html
int Board::miniMax(int depth, bool needMax, int alpha, int beta, Board& childWithMax) {
	//System.Diagnostics.Debug.Assert(m_TurnForPlayerX == needMax);
	if (depth == 0 || isTerminalNode()) {
		mRecursiveScore = mScore;
		return mScore;
	}
	vector<Board*> childrens = getChildren();
	for(int i = 0 ; i < childrens.size() ; i++) {
		Board dummy = Board();
		int score = childrens[i]->miniMax(depth - 1, !needMax, alpha, beta, dummy);

		if (!needMax) {
			if (beta > score) {
				beta = score;
				childWithMax.copy(childrens[i]);
				if (alpha >= beta) {
					break;
				}

			}
		}
		else {
			if (alpha < score) {
				alpha = score;
				childWithMax.copy(childrens[i]);
				if (alpha >= beta) {
					break;
				}
			}
		}
    }
    for(int i = 0 ; i < childrens.size() ; i++) {
        DELETE_PTR(childrens[i]);
    }
    childrens.clear();

	mRecursiveScore = needMax ? alpha : beta;
	return mRecursiveScore;
}

Board* Board::findNextMove(int depth) {
	Board* ret 	= NULL;
	Board* ret1 = NULL;
    Board r1, r2;
	miniMaxShortVersion(depth, INT_MIN + 1, INT_MAX - 1, r2);
	miniMax(depth, mTurnForPlayerX, INT_MIN + 1, INT_MAX - 1, r1);
	if(r2.mValues != NULL) {
        ret1 = new Board();
        ret1->copy(&r2);
	}
	if(r1.mValues != NULL) {
		ret = new Board();
        ret->copy(&r1);
	}

	//compare the two versions of MiniMax give the same results
	if(!isSameBoard(ret, ret1, true)) {
		cout << "ret " << ret->toString() << "\n!= ret1 " << ret1->toString()
				<< "\ncurrent << " << this->toString();
        cout << "\nTwo MinMax functions don't match.\n";
	}
    DELETE_PTR(ret1);

	return ret;
}

int Board::getScoreForOneLine(vector<GridEntry>* values) {
	int countX = 0, countO = 0;
	for(int i = 0 ; i < values->size() ; i++) {
		if(values->at(i) == playerX) {
			countX ++;
		}
		else if(values->at(i) == playerO) {
			countO ++;
		}
	}
	if(countO == 3 || countX == 3) {
		mIsGameOver = true;
	}

	//The player who has turn should have more advantage.
	//What we should have done
	int advantage = 1;
	if(countO == 0) {
		if(mTurnForPlayerX) {
			advantage = 3;
		}
		return (int)pow(10, countX) * advantage;
	}
	else if(countX == 0) {
		if(!mTurnForPlayerX) {
			advantage = 3;
		}
		return -(int)pow(10, countO) * advantage;
	}

	return 0;
}

void Board::computeScore() {
	int ret = 0;
	int lines[8][3] = { { 0, 1, 2 },
	                  { 3, 4, 5 },
	                  { 6, 7, 8 },
	                  { 0, 3, 6 },
	                  { 1, 4, 7 },
	                  { 2, 5, 8 },
	                  { 0, 4, 8 },
	                  { 2, 4, 6 }
	                };
	for(int i = 0 ; i < 8 ; i++) {
		vector<GridEntry> *values = new vector<GridEntry>();
		values->push_back(mValues->at(lines[i][0]));
		values->push_back(mValues->at(lines[i][1]));
		values->push_back(mValues->at(lines[i][2]));
		ret += getScoreForOneLine(values);
        
        values->clear();
        delete values;
        values = NULL;
	}

	mScore = ret;
}

Board* Board::transformBoard(Transform* t) {
	vector<GridEntry> *values = new vector<GridEntry>(9, empty);
	for(int i = 0 ; i < 9 ; i++) {
		Point p(i % 3, i / 3);
		p = t->actOn(p);
		int j = p.x + p.y * 3;
		values->at(j) = this->mValues->at(i);
	}

	return new Board(values, mTurnForPlayerX);
}

bool Board::isSameBoard(Board* a, Board* b, bool compareRecursiveScore) {
	if(a == b) {
		return true;
	}
	if(a == NULL || b == NULL) {
		return false;
	}
	for(int i = 0 ; i < a->mValues->size() ; i++) {
		if(a->mValues->at(i) != b->mValues->at(i)) {
			return false;
		}
	}
	if(a->mScore != b->mScore) {
		return false;
	}
	if(compareRecursiveScore && abs(a->mRecursiveScore)
		!= abs(b->mRecursiveScore)) {
		return false;
	}

	return true;
}

bool Board::isSimilarBoard(Board* a, Board* b) {
	if(isSameBoard(a, b, false)) {
		return true;
	}
	for(int i = 0 ; i < Transform::sTransforms.size() ; i++) {
		Board *newB = b->transformBoard(Transform::sTransforms[i]);
		if(isSameBoard(a, newB, false)) {
            DELETE_PTR(newB);
			return true;
		}
        DELETE_PTR(newB);
	}
	return false;
}

string Board::toString() {
    string sb = string();
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < 3 ; j++) {
            GridEntry v = mValues->at(i * 3 + j);
            string c = " - ";
            if(v == playerX) {
                c = " X ";
            }
            else if(v == playerO) {
                c = " O ";
            }
            sb.append(c);
        }
        sb.append("\n");
    }
    char ch[200];
    string turnX = (mTurnForPlayerX) ? "true" : "false";
    sprintf(ch, "score = %d, ret = %d, %s", mScore, mRecursiveScore, turnX.c_str());
    sb.append(string(ch));
    
    return sb;
}

Board::~Board() {
    DELETE_PTR(mValues);
}
