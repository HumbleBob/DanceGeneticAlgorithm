//
//  DanceGraph.h
//  DanceGeneticAlgorithm
//
//  Created by Sawyer Bowman on 2/20/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef DanceGeneticAlgorithm_DanceGraph_h
#define DanceGeneticAlgorithm_DanceGraph_h

#include <stdio.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include "DanceMove.h"

using namespace std;

const int K = 2;

//The constant, 2D array for the elevation of a given dance move.
const int elevation[20][2] = { {2,2},{2,1},{2,1},{1,2},{2,2},{2,2},{2,2},
    {2,2},{2,0},{1,1},{1,2},{2,2},{2,0},{0,1},{0,0},{0,1},{2,2},{2,2},{2,2},
    {2,1} };

//The constant array for the speed of a given dance move.
const int speed[20] = {1,1,1,0,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,};

//The constant, 2D array for the body parts used for a given dance move.
const int partsUsed[20][5] = { {0,0,1,1,1},{1,0,1,1,0},{0,0,0,1,1},
    {0,0,0,0,1},{1,0,1,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,1,1,0,0},
    {0,1,1,1,0},{0,1,0,0,0},{1,1,1,1,1},{0,0,1,0,0},{0,1,1,1,0},
    {0,0,1,1,0},{0,0,0,1,0},{0,0,1,1,1},{0,0,1,1,0},{0,1,1,1,1},
    {0,1,1,1,0},{1,0,1,1,1} };

//constant for number of representative sequences generated for a graph
const int numReps = 100;

class DanceGraph{
public:
    //Constructors for creating a random graph
    DanceGraph(int numMoves, double makeLinkProb);
    
    //Constructor for creating a graph given connections already exist
    DanceGraph(int numMoves, vector<bool> newConnections);
    
    double calcFitness(vector<DanceMove*> sequence);
    double calcGraphFitness();
    void setFitness(double newFit) { fitness = newFit; }
    double getFitness() { return fitness; }
    vector<bool> getConnections() { return connections; }
    vector<DanceMove*> getMoves() { return moves; }
    
    DanceGraph* breed(DanceGraph graph, string cross, double crossProb, double mutProb);
    
    void printGraphConnections();
    vector<DanceMove*> getSequence();
        
    void printMoves();
    
private:
    void initializeMoves(int numMoves);
    void initializeConnections(int numMoves, double probConnect);
    unsigned long long calcCombinations(int numMoves);
    void createGraphWithLinks(int numMoves);
    void clearAllLinks();
    
    vector<bool> crossover(vector<bool> otherConnections, string crossMethod);
    vector<bool> mutate(vector<bool> newConnections, double mutProb);
    
    //Vector representing each move, creates a graph
    vector<DanceMove*> moves;
    
    //Each index represents a possible connection in the undirected graph (1=connected) (0=unconnected)
    vector<bool> connections;
    
    double fitness;
    
};

//#include <stdio.h>
//#include <iostream>
//#include <vector>
//#include "Clause.h"
//
//using namespace std;
//
//class Individual {
//public:
//    //Constructors
//    Individual(int numVariables, vector<Clause> clauses);
//    Individual(vector<bool> newSequence, vector<Clause> clauses);
//    
//    //For fitness, get variables from clause, check if satisifed in proper location of string
//    double calcFitness(vector<Clause> clauses);
//    void setFitness(int newFit) { fitness = newFit; }
//    void printFitness() { cout << fitness << endl; }
//    double getFitness() { return fitness; }
//    
//    //Breed function
//    Individual* breed(Individual indiv, string cross, double crossProb, double mutProb, vector<Clause> clauses);
//    
//    void printSequence();
//    void printVariableSequence();
//    
//    void setRank(int newRank) { rank = newRank; }
//    int getRank() { return rank; }
//    
//    vector<bool> getSequence() { return sequence; }
//    
//    //TODO: figure out how to make individual work with PBIL
//    
//private:
//    //TODO: implement helper functions for breed
//    vector<bool> crossover(vector<bool> secondSequence, string method);
//    vector<bool> mutate(vector<bool>, double mutProb);
//    
//    //Properties of an invidual
//    vector<bool> sequence;
//    double fitness;
//    int rank;
//    
//    
//};


#endif
