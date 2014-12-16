//
//  Paytable.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/12/14.
//
//

#include "Paytable.h"
#include "PayTableCell.h"

Paytable::Paytable(vector<PaytableCell*> *pPaytableCells)
: mPaytableCells(pPaytableCells) {
    
}

Paytable* Paytable::create(vector<PaytableCell*> *pPaytableCells) {
    Paytable* pRet = new Paytable(pPaytableCells);
    
    return pRet;
}

bool Paytable::updateWonHandType(const int pWonHand) {
    mWonPaytableCell = NULL;
    for(int i = 0 ; i < mPaytableCells->size() ; i++) {
        if(mPaytableCells->at(i)->getHandType() == pWonHand) {
            mWonPaytableCell = mPaytableCells->at(i);
            return true;
        }
    }
    return false;
}

Paytable::~Paytable() {
    for(int i = 0 ; i < mPaytableCells->size() ; i++) {
        delete mPaytableCells->at(i);
    }
    mPaytableCells->clear();
    delete mPaytableCells;
}
