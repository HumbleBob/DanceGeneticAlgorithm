//
//  GenticAlgorithm.h
//  EvolutionaryAlgorithms
//
//  Created by Sawyer Bowman on 2/5/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __EvolutionaryAlgorithms__EvolutionaryAlgorithm
#define __EvolutionaryAlgorithms__EvolutionaryAlgorithm

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Population.h"
#include "DanceGraph.h"
#include <cstdio>
#include <ctime>
#include <sstream>

using namespace std;

//Constants for checking parameters passed in command line arguments
const string RS = "rs";
const string TS = "ts";
const string BS = "bs";
const string ONE_C = "1c";
const string UNIFORM = "uc";

class EvolutionaryAlgorithm {
    
public:
    //Initialize an empty EvolutionaryAlgorithm object
    EvolutionaryAlgorithm();
    
    //Initialize EvolutionaryAlgorithm object for Genetic
    EvolutionaryAlgorithm(int numMoves, double probConnect, int pop, string select, string cross, double probCross, double probMut, int maxGen, string alg, int printInt, int staleGen);
    
    //Initialize EvolutionaryAlgorithm object for PBIL
    EvolutionaryAlgorithm(int numMoves, double probConnect, int pop, double pos, double neg, double probMut, double mutAmt, int maxGen, string alg, int printInt, int staleGen);
    
    //The body of the algorithm goes here
    void run(int graphNum);
    
private:
    void quitEvolving(int generationsRun, bool done, DanceGraph globalBest, clock_t start, int graphNum);
    
    //Updates to Probability Vector
    void updateTowardsBest(DanceGraph best);
    void updateAwayFromWorst(DanceGraph best, DanceGraph worst);
    void mutateProbVector();
    void saveAdjacencyList(DanceGraph best, int graphNum);
    void saveSequences(DanceGraph best, int graphNum);
    
    //Shared properties between Genetic and PBIL
    int numMoves;
    double probConnection;
    int populationSize;
    double probMutation;
    int maxGenerations;
    string algorithm;
    int printInterval;
    int quitEvolve;
    Population* population;
    
    //Genetic specific properties
    string selection;
    string crossover;
    double probCrossover;
    
    //PBIL specific properties
    double posLearnRate;
    double negLearnRate;
    double mutationAmount;
    vector<double> probabilityVector;
    
};

#endif /* defined(__EvolutionaryAlgorithms__EvolutionaryAlgorithm__) */
