//
//  DanceMove.cpp
//  DanceGeneticAlgorithm
//
//  Created by Sawyer Bowman on 2/20/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "DanceMove.h"

DanceMove::DanceMove(int moveNum, int elev[2], int spd, int limbs[5]){
    moveNumber = moveNum;
    elevation[0] = elev[0];
    elevation[1] = elev[1];
    speed = spd;
    for(int i = 0; i < 5; i++){
        limbsUsed[i] = limbs[i];
    }
}

void DanceMove::addToLinks(DanceMove* newLink){
    links.push_back(newLink);
}

