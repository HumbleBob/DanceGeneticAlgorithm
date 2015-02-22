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
#include <vector>

using namespace std;

class DanceMove {
public:
    //Constructor for creating a dance move: TODO: add levels, speed, emotion, etc.
    DanceMove(int moveNum);
    
    vector<DanceMove*> getLinks() { return links; }
    void setLinks(vector<DanceMove*> newLinks) { links = newLinks; }
    void addToLinks(DanceMove* newLink);
    
private:
    vector<DanceMove*> links;
    int moveNumber;
};

#endif /* defined(__DanceGeneticAlgorithm__DanceMove__) */
