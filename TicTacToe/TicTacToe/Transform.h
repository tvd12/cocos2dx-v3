/*
 * Transform.h
 *
 *  Created on: Nov 17, 2014
 *      Author: dungtavan
 */

#ifndef SRC_TRANSFORM_H_
#define SRC_TRANSFORM_H_

#include <vector>

#include "Point.h"

using namespace std;

namespace algorithm {
    
    class Transform;
    
    typedef Point (Transform::*FnPtr)(Point);
    
#define fn_selector(_SELECTOR)	(FnPtr)(&_SELECTOR)
    
    class Transform {
    public:
        static void initStatic();
        
        Transform(FnPtr op, vector<FnPtr>& ops);
        Point rotate90Degree(Point p);
        Point mirrorX(Point p);
        Point mirrorY(Point p);
        Point actOn(Point p);
        
        static vector<Transform*> sTransforms;
        
    protected:
        int mSize;
        vector<FnPtr> mActions;
    };
    
}

#endif /* SRC_TRANSFORM_H_ */
