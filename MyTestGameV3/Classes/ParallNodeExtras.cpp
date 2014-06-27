//
//  ParallNodeExtras.cpp
//  MyTestGameV3
//
//  Created by Ta Van Dung on 1/21/14.
//
//

#include "ParallNodeExtras.h"

//Hack to access PointObject (which is not a public class)

ParallNodeExtras::ParallNodeExtras() {
    getCustomInstance();
}

auto ParallNodeExtras::node() -> ParallNodeExtras* {
    return new ParallNodeExtras();
}

void ParallNodeExtras::incrementOffset(Point offset, Node* node) {
    for(unsigned int i = 0 ; i < _parallaxArray->num ; i++) {
        PointObject *point = (PointObject*)_parallaxArray->arr[i];
        Node* curNode = point->getChild();
        if(curNode->isEqual(node)) {
            point->setOffset(point->getOffset() + offset);
            break;
        } else {
            
        }
        
    }
}

