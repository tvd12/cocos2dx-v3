//
//  main.cpp
//  TicTacToe
//
//  Created by Dung Ta Van on 11/18/14.
//  Copyright (c) 2009 Dong Xiang. All rights reserved.
//

#include <vector>
#include <iostream>
#include <string>
#include <queue>

#include "Point.h"
#include "Board.h"
#include "TicTacToe.h"
#include "TichTacToeGame.h"
#include "Transform.h"

#define DELETE_PTR(ptr) \
if(ptr) { \
    delete ptr; \
    ptr = 0; \
}

using namespace std;
using namespace algorithm;

int main(int argc, const char * argv[]) {
    
    Transform::initStatic();
    TichTacToeGame *game = new TichTacToeGame;
    cout << "Winning positions for playerO:\n";
    vector<Board*> history = vector<Board*>();
    queue<Board*> q = queue<Board*>();
    q.push(game->getInitNode());

    int total = 0;
    while(q.size() > 0) {
        Board *b = q.front();
        q.pop();
        Board* next = b->findNextMove(9);
        if(abs(b->getRecursiveScore()) >= 200 && next != NULL) {
            Board* x = NULL;
            for(int i = 0 ; i < history.size() ; i++) {
                if(Board::isSimilarBoard(history[i], b)) {
                    x = history[i];
                    break;
                }
            }
            
            if(b->getRecursiveScore() < 0
               && !next->isGameOver()
               && x == NULL) {
                string winer = b->getRecursiveScore() < 0 ? "PlayerO" : "PlayerX";
                history.push_back(b);
                cout << "["<< total <<"] Winner is " << winer << ":\n"
                << b->toString() << ", next move is:\n" << next->toString();
                total ++;
            }
            else {
                DELETE_PTR(b);
            }
        }
        else {
            vector<Board*> childrens = b->getChildren();
            for(int i = 0 ; i < childrens.size() ; i++) {
                q.push(childrens[i]);
            }
            DELETE_PTR(b);
        }
        
        DELETE_PTR(next);
        
    }
    
    for(int i = 0 ; i < history.size() ; i++) {
        DELETE_PTR(history[i]);
    }
    
    history.clear();
    
    for(int i = 0 ; i < q.size() ; i++) {
        DELETE_PTR(q.front());
        q.pop();
    }
    
    bool stop = false;
    while(!stop) {
        bool userFirst = false;
        game = new TichTacToeGame;
        cout << "\nUser play against computer, Do you place the first step?[y/n]: ";
        string str = "";
        cin >> str;
        if(str.find("y") == 0) {
            userFirst = true;
        }
        
        int depth = 8;
        cout << "Please select level:[1..8]. 1 is easiet, 8 is hardest: ";
        cin >> depth;
        string firster = userFirst ? "User" : "Computer";
        cout << firster << " play first, level = " << depth;
        while(!game->getCurrent()->isTerminalNode()) {
            if(userFirst) {
                game->getNextMoveFromUser();
                game->computerMakeMove(depth);
            }
            else {
                game->computerMakeMove(depth);
                game->getNextMoveFromUser();
            }
        }
        cout << "The final result is \n" << game->getCurrent()->toString();
        if(game->getCurrent()->getRecursiveScore() < -200) {
            cout << "PlayerO has won.\n";
        }
        else if(game->getCurrent()->getRecursiveScore() > 200) {
            cout << "PlayerX has won.\n";
        }
        cout << "Try again?[y/n]: ";
        cin >> str;
        if(!(str.find("y") == 0)) {
            stop = true	;
        }
    }
    
    cout << "bye";
    return 0;
}

