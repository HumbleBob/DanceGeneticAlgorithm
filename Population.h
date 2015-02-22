//
//  Population.h
//  EvolutionaryAlgorithms
//
//  Created by Sawyer Bowman on 2/7/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __EvolutionaryAlgorithms__Population__
#define __EvolutionaryAlgorithms__Population__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "DanceGraph.h"

using namespace std;

const int M = 2;
const int k = 1;
const double e = exp(1.0);
const double PROB = .25;

//Sorts ascending by fitness (lowest to highest)
static bool sortByFitness(DanceGraph firstGraph, DanceGraph secondGraph) { return firstGraph.getFitness() < secondGraph.getFitness(); }
static bool maxByFitness(DanceGraph firstGraph, DanceGraph secondGraph) { return firstGraph.getFitness() < secondGraph.getFitness(); }

class Population {
public:
    Population(int numGraphs);
    Population(int numGraphs, vector<double> probVec);

    void selection(string select);
    
    void breed(string crossover, double probCrossover, double probMutation);
    
    vector<DanceGraph> getGraphs() { return graphs; }
    vector<DanceGraph> getBreedingPool() { return breedingPool; }
    DanceGraph getBestGraph();
    DanceGraph getWorstGraph();
    
    void updatePopulation(int numIndiv, vector<double> probVec);
    
    void printBreedingPoolSize() { cout << breedingPool.size() << endl; }
    
private:
    //helper functions for select()
    void tournamentSelect();
    void rankSelect();
    void boltzmannSelect();
    
    DanceGraph getRandomGraph();
    
    DanceGraph createGraphFromProbVec(vector<double> probVec);
    
    //Vector of graphs representing a population
    vector<DanceGraph> graphs;
    
    //Vector of graphs selected via a selection method for the breeding pool
    vector<DanceGraph> breedingPool;
    
};

#endif /* defined(__EvolutionaryAlgorithms__Population__) */
