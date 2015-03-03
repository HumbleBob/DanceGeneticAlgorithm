//
//  DanceMove.h
//  DanceGeneticAlgorithm
//
//  Created by Sawyer Bowman on 2/20/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __DanceGeneticAlgorithm__DanceMove__
#define __DanceGeneticAlgorithm__DanceMove__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DanceMove {
public:
    //Constructor for creating a dance move: TODO: add levels, speed, emotion, etc.
    DanceMove(int moveNum, int elev[2], int spd, int limbs[5]);
    
    vector<DanceMove*> getLinks() { return links; }
    void setLinks(vector<DanceMove*> newLinks) { links = newLinks; }
    void addToLinks(DanceMove* newLink);
    
    int getMoveNumber(){return moveNumber;};
    int getStartElevation(){return elevation[0];};
    int getEndElevation(){return elevation[1];};
    int getSpeed(){return speed;};
    int lLegUsed(){return limbsUsed[0];};
    int rLegUsed(){return limbsUsed[1];};
    int lArmUsed(){return limbsUsed[2];};
    int rArmUsed(){return limbsUsed[3];};
    int headUsed(){return limbsUsed[4];};
    
    void printMoveNum() { cout << moveNumber+1; }

    
private:
    vector<DanceMove*> links;
    int moveNumber;
    int elevation[2];
    int speed;
    int limbsUsed[5];
};

#endif /* defined(__DanceGeneticAlgorithm__DanceMove__) */
