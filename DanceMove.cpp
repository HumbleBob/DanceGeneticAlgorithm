//
//  DanceMove.cpp
//  DanceGeneticAlgorithm
//
//  Created by Sawyer Bowman on 2/20/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "DanceMove.h"

DanceMove::DanceMove(int moveNum){
    moveNumber = moveNum;
}

void DanceMove::addToLinks(DanceMove* newLink){
    links.push_back(newLink);
}

