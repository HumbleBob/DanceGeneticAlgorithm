//
//  DanceGraph.cpp
//  DanceGeneticAlgorithm
//
//  Created by Sawyer Bowman on 2/20/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "DanceGraph.h"

/**
 *Constructor to create a graph of randomly connected dance moves. First
 *create a list of move. Then, for each dance move, modify its links so
 *that it has a chance of connecting with other nodes.
 */

DanceGraph::DanceGraph(int numMoves, double makeLinkProb){
    //create a vector of dance moves
    initializeMoves();
    
    //initialize a vector of connections (undirected)
    initializeConnections(numMoves, makeLinkProb);
    
    //make an object representation of graph based on vector
    createGraphWithLinks(numMoves);
    
    //set the fitness
    fitness = calcFitness();
}

/**
 *Constructor to create a graph of moves with connections already set.
 */

DanceGraph::DanceGraph(int numMoves) {
    createGraphWithLinks(numMoves);
}

/**
 *A method to initialize the moves
 */

void DanceGraph::initializeMoves(){
    for (int i = 0; i < 20; i++){
        int elev[2] = {elevation[i][0],elevation[i][1]};
        int newSpeed = speed[i];
        int bodyParts[5] = {partsUsed[i][0],partsUsed[i][1],partsUsed[i][2],
            partsUsed[i][3],partsUsed[i][4]};
        //add the moves to the vector of moves.
        moves.push_back(new DanceMove(i,elev,newSpeed,bodyParts));
    }
}

/**
 *A method to initialize the connections between dance moves
 *with a certain probability
 */

void DanceGraph::initializeConnections(int numMoves, double probConnect){
    unsigned long long combinations = calcCombinations(numMoves);
    for (unsigned long long i = 0; i < combinations; i++){
        //create new link with probability
        double randomProb = (double)rand()/RAND_MAX;
        if (probConnect > randomProb){
            connections.push_back(true);
        }
        else {
            connections.push_back(false);
        }
    }
}

/**
 *Find the number of combinations
 */

unsigned long long DanceGraph::calcCombinations(int numMoves){
    //allow for repetition (a node can link to itself)
    unsigned long long n = numMoves+1;
    if (K > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 0; d < K; d++) {
        r *= n--;
        r /= (d+1);
    }
    return r;
}

/**
 *Create an actual graph based on the vector of connections
 */

void DanceGraph::createGraphWithLinks(int numMoves){
    //clear links for each dance move
    clearAllLinks();
    //count keep track of individual links (ex numMoves for 1st dance move, numMoves-1 for 2nd dance move, etc)
    int count = numMoves;
    //moveNum represents the first dance move, offset represents the second dance move
    int moveNum = 0;
    for (int i = 0; i < connections.size(); i+=count){
        for (int offset = 0; offset < count; offset++){
            //if there is a link at moveNum, offset, create representation in each dance move's links
            if (connections[i+offset]){
                moves[moveNum]->addToLinks(moves[offset]);
                moves[offset]->addToLinks(moves[moveNum]);
            }
        }
        moveNum++;
        count--;
    }
}

/**
 *Clear links for each Dance Move (after breeding (crossover and mutation take place)
 *the graph will have to be rebuilt. Thus, the links need to start from scratch.
 */

void DanceGraph::clearAllLinks(){
    vector<DanceMove*> clearLinks;
    for (DanceMove* move : moves){
        move->setLinks(clearLinks);
    }
}

/**
 *First generate representative sequences of dance moves. Then calculate the fitness
 *of each individual sequence. Average the fitness of each representative, and that
 *is the fitness of the graph individual.
 */

double DanceGraph::calcFitness(){
    
    int sequenceScore = 0;
    int moveCount[20];
    
    //First off, count the multiplicites of each dance move in the sequence.
    for(int i = 0; i < moves.size(); i++){
        for(int j = 0; j < moves.size(); j++){
            if(moves.at(j)->getMoveNumber() == i){
                moveCount[i]++;
            }
        }
    }
    
    //Create a rule based on the repetition of a single move.
    for(int i = 0; i < moves.size(); i++){
        //Dock points if there is a move that is repeated more than 4 times.
        if(moveCount[i] > 4){
            sequenceScore = sequenceScore - 3;
        }
        else if(moveCount[i] == 4){
            sequenceScore = sequenceScore - 1;
        }
        else if(moveCount[i] == 3 || moveCount[i] == 2){
            sequenceScore = sequenceScore + 1;
        }
    }
    
    int abruptCount = 0;
    
    //Count number of "abrupt" Changes in the sequence.
    for(int i = 0; i < moves.size() - 1; i++){
        if(moves.at(i)->getEndElevation() - moves.at(i+1)->getStartElevation()
           == 2 || moves.at(i)->getEndElevation() -
           moves.at(i+1)->getStartElevation() == -2 || moves.at(i)->getSpeed() -
           moves.at(i+1)->getSpeed() == -2){
            abruptCount++;
        }
    }
    
    //Score the sequenceScore based on number of abrupt changes.
    if(abruptCount > 3){
        sequenceScore--;
    }
    else if(abruptCount == 3 || abruptCount == 2){
        sequenceScore = sequenceScore + 2;
    }
    
    //Dock points if the same move is repeated more than two times in a row.
    for(int i = 0; i < moves.size() - 2; i++){
        if(moves.at(i)->getMoveNumber() == moves.at(i+1)->getMoveNumber() &&
           moves.at(i+1)->getMoveNumber() == moves.at(i+2)->getMoveNumber()){
            sequenceScore = sequenceScore - 3;
        }
    }
    
    //Award points for an overall cycle.
    if(moves.at(0)->getMoveNumber() == moves.at(moves.size()-1)->getMoveNumber()){
        sequenceScore++;
    }
    
    //Now we look at individual transitions between two moves:
    for(int i = 0; i < moves.size() - 1; i++){
        
        //If the elevation of two sequential moves are of distance 2 away dock points.
        if(moves.at(i)->getEndElevation() - moves.at(i+1)->getStartElevation()
           == 2 || moves.at(i)->getEndElevation() - moves.at(i+1)->getStartElevation()
           == -2){
            sequenceScore--;
        }
        
        //At least one body used part in common.
        if((moves.at(i)->headUsed() == 1 && moves.at(i+1)->headUsed() == 1) ||
           (moves.at(i)->rArmUsed() == 1 && moves.at(i+1)->rArmUsed() == 1) ||
           (moves.at(i)->lArmUsed() == 1 && moves.at(i+1)->lArmUsed() == 1) ||
           (moves.at(i)->rLegUsed() == 1 && moves.at(i+1)->rLegUsed() == 1) ||
           (moves.at(i)->lLegUsed() == 1 && moves.at(i+1)->lLegUsed() == 1)){
            sequenceScore++;
        }
        
        //Similar speed to the previous move.
        if(moves.at(i)->getSpeed() == moves.at(i+1)->getSpeed()){
            sequenceScore++;
        }
    
    }
    return sequenceScore;
}

/**
 *This method breeds two graphs together (the connections vector). It performs the crossover method,
 *given by a command line argument, with a certain probability. If crossover occurs,
 *a new connections sequence is generated. Otherwise, the child sequence remains the same as the
 *first graph's connections (the one calling the method). Then, mutate is called, which has
 *a chance of mutating each connection of a certain probability. A new graph is then
 *created and returned.
 */

DanceGraph* DanceGraph::breed(DanceGraph graph, string cross, double crossProb, double mutProb){
    vector<bool> newConnections;
    
    double crossoverProb = (double)rand()/RAND_MAX;
    if (crossProb > crossoverProb){
        newConnections = crossover(graph.connections, cross);
    }
    else {
        newConnections = connections;
    }
    
    newConnections = mutate(newConnections, mutProb);
    
    return new DanceGraph(20);
}

/**
 *
 */

void DanceGraph::printGraphConnections(){
    
}

/**
 *This method strictly performs the crossover portion of breeding. It creates
 *one new connections sequence, either by crossing on a single point or by randomly
 *selecting genes from each parent connections sequence.
 */

vector<bool> DanceGraph::crossover(vector<bool> secondConnections, string crossMethod){
    vector<bool> newConnections;
    if (crossMethod == "1c"){
        int index = rand() % connections.size();
        newConnections.insert(newConnections.end(), connections.begin(), connections.begin()+index);
        newConnections.insert(newConnections.end(), secondConnections.begin()+index, secondConnections.end());
    }
    else {
        int count = 0;
        while (newConnections.size() != connections.size()){
            int randomBit = rand() % 2;
            if (randomBit == 0){
                newConnections.push_back(connections[count]);
                count++;
            }
            else {
                newConnections.push_back(secondConnections[count]);
                count++;
            }
        }
    }
    return newConnections;
}

/**
 *This method strictly performs the mutation portion of the breeding. With some
 *probability, a connection in the child graph sequence will be flipped (ex. true to false).
 */

vector<bool> DanceGraph::mutate(vector<bool> newConnections, double mutProb){
    for (int i = 0; i < newConnections.size(); i++){
        double randomProb = (double)rand()/RAND_MAX;
        if (mutProb > randomProb){
            if (newConnections[i]){
                newConnections[i] = false;
            }
            else {
                newConnections[i] = true;
            }
        }
    }
    return newConnections;
}

void DanceGraph::printMoves(){
    
    for(int i = 0; i < moves.size(); i++){
        
        cout << "Elevation: " << moves.at(i)->getStartElevation() << " to "
        << moves.at(i)->getEndElevation() << endl;
        
    }
}
