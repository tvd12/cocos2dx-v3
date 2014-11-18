/*
 * Transform.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#include "Transform.h"

vector<Transform*> Transform::sTransforms = vector<Transform*>();

Transform::Transform(FnPtr op, vector<FnPtr>& ops) :
mSize(3),
mActions(vector<FnPtr>()){
	if(op != NULL) {
		mActions.push_back(op);
	}
	mActions.insert(mActions.end(), ops.begin(), ops.end());
}

Point Transform::rotate90Degree(Point p) {
	//012 -> x->y, y->size-x
	//012
	return Point(mSize - p.y -1, p.x);
}

Point Transform::mirrorX(Point p) {
	//012 -> 210
	return Point(mSize - p.x -1, p.y);
}

Point Transform::mirrorY(Point p) {
	return Point(p.x, mSize - p.y -1);
}

Point Transform::actOn(Point p) {
	for(int i = 0 ; i < mActions.size() ; i++) {
		if(mActions[i] != NULL) {
			p = ((*this).*mActions[i])(p);
		}
	}

	return p;
}

void Transform::initStatic() {
	for(int i = 0 ; i < 4 ; i++) {
		vector<FnPtr> ops = vector<FnPtr>(i, fn_selector(Transform::rotate90Degree));
		sTransforms.push_back(new Transform(NULL, ops));
		sTransforms.push_back(new Transform(fn_selector(Transform::mirrorX), ops));
		sTransforms.push_back(new Transform(fn_selector(Transform::mirrorY), ops));
	}
}
