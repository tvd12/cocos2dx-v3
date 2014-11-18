/*
 * Point.h
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

struct Point {
	Point(): x(0), y(0) {}
	Point(int pX, int pY) : x(pX), y(pY){}
	int x, y;
};

#endif /* SRC_POINT_H_ */
