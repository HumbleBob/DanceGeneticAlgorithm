//
//  Population.cpp
//  EvolutionaryAlgorithms
//
//  Created by Sawyer Bowman on 2/7/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "Population.h"

/**
 *Constructor creating a new population of random graphs
 */

Population::Population(int numGraphs, int numMoves, double prob) {
    for (int i = 0; i < numGraphs; i++){
        DanceGraph* newGraph = new DanceGraph(numMoves, prob);
        graphs.push_back(*newGraph);
    }
}

/**
 *Alternate constructor for the PBIL problem
 */

Population::Population(int numGraphs, int numMoves, vector<double> probVec){
    for (int i = 0; i < numGraphs; i++){
        DanceGraph newGraph = createGraphFromProbVec(probVec);
        graphs.push_back(newGraph);
    }
}

/**
 *This method takes in the selection method passed as a command line parameter
 *and decides which selection to do.
 */

void Population::selection(string select){
    if (select == "rs"){
        rankSelect();
    }
    else if (select == "ts"){
        tournamentSelect();
    }
    else if (select == "bs"){
        boltzmannSelect();
    }
}

/**
 *This method ranks the graphs in the population and then selects
 *them for breeding with a particular probability.
 */

void Population::rankSelect(){
    //Sort the graphs by fitness
    sort(graphs.begin(), graphs.end(), sortByFitness);
    
    //empty breeding pool
    breedingPool.clear();
    
    //Calculate sum of series for probability calculation later
    double seriesSum = (graphs.size() * (graphs.size()+1))/2;
    
    //While breeding pool not full, add new graph
    while (breedingPool.size() != graphs.size()){
        
        //Used to select a new graph
        double randomProb = (double)rand()/RAND_MAX;
        double count = 0;
        
        //Sum up the probabilities while iterating
        for (int i = 0; i < graphs.size(); i++){
            count += (i+1)/seriesSum;
            if (count > randomProb){
                breedingPool.push_back(graphs[i]);
                //restart the for loop and continue until breedingPool is full
                break;
            }
        }
    }
}

/**
 *While there are individuals remaining, this method takes M graphs
 *and places them into a tournament. Then, the k best graphs are
 *chosen from this tournament and added to the breeding pool.
 */

void Population::tournamentSelect(){
    vector<DanceGraph> graphPool = graphs;
    
    //empty breeding pool
    breedingPool.clear();
    
    //need to draw M from vector, select k from M, place k in pool
    while (breedingPool.size() != graphs.size()){
        vector<DanceGraph> tournamentParticipants;
        
        //Fill the tournament with candidates until M is reached
        int drawCount = 0;
        while (drawCount < M){
            int randIndex = rand() % graphs.size();
            tournamentParticipants.push_back(graphs[randIndex]);
            drawCount++;
        }
       
        //Find the best k graphs, place them in the breeding pool
        int poolCount = 0;
        while (poolCount < k && breedingPool.size() != graphs.size()){
            DanceGraph champion = *max_element(tournamentParticipants.begin(), tournamentParticipants.end(), maxByFitness);
            breedingPool.push_back(champion);
            poolCount++;
        }
    }
}

/**
 *A very similar method to rankSelect, but uses e^fitness instead of rank
 *to calculate probability of being selected.
 */

void Population::boltzmannSelect(){
    //Sort the graphs by fitness
    sort(graphs.begin(), graphs.end(), sortByFitness);
    
    //empty breeding pool
    breedingPool.clear();
    
    //Calculate sum of series for probability calculation later
    double seriesSum = 0;
    for (int i = 0; i < graphs.size(); i++){
        seriesSum += pow(e, graphs[i].getFitness());
    }
    
    //While breeding pool not full, add new individual
    while (breedingPool.size() != graphs.size()){
        
        //Used to select a new individual
        double randomProb = (double)rand()/RAND_MAX;
        double count = 0;
        
        //Sum up the probabilities while iterating
        for (int i = 0; i < graphs.size(); i++){
            count += pow(e,graphs[i].getFitness())/seriesSum;
            if (count > randomProb){
                breedingPool.push_back(graphs[i]);
                //restart the for loop and continue until breedingPool is full
                break;
            }
        }
    }
}

/**
 *This method chooses two random graphs from the breeding pool, and creates
 *a new graph to replace them in the next generation. It calls upon crossover
 *and mutation to potentially change the gene sequence of the offspring.
 */

void Population::breed(string crossover, double probCrossover, double probMutation){
    vector<DanceGraph> newGeneration;
    
    //fill up newGeneration until it reaches the set population size
    while(newGeneration.size() != graphs.size()){
        //get two random graphs
        DanceGraph graph1 = getRandomGraph();
        DanceGraph graph2 = getRandomGraph();
        
        //breed the 2 graphs together to create 1 child
        DanceGraph* child = graph1.breed(graph2, crossover, probCrossover, probMutation);
        newGeneration.push_back(*child);
    }
    
    graphs = newGeneration;
}

/**
 *This method is responsible for getting an graph from the population
 *and returning it.
 */

DanceGraph Population::getRandomGraph(){
    int randomIndex = rand() % breedingPool.size();
    return breedingPool[randomIndex];
}

/**
 *This method returns the best graph in the individuals vector.
 */

DanceGraph Population::getBestGraph(){
    return *max_element(graphs.begin(), graphs.end(), maxByFitness);
}

/**
 *This method returns the worst graph in the individuals vector
 */

DanceGraph Population::getWorstGraph(){
    return *min_element(graphs.begin(), graphs.end(), maxByFitness);
}

/**
 *This method replaces the population with a new set of individuals made in 
 *concordance with the probability vector.
 */

void Population::updatePopulation(int numIndiv, vector<double> probVec){
    vector<DanceGraph> newPopulation;
    for (int i = 0; i < numIndiv; i++){
        newPopulation.push_back(createGraphFromProbVec(probVec));
    }
    graphs = newPopulation;
}

/**
 *This method actually creates the individual from the probability vector.
 */

DanceGraph Population::createGraphFromProbVec(vector<double> probVec){
    vector<bool> newSequence;
    for (double prob : probVec){
        double newProb = (double)rand()/RAND_MAX;
        if (prob > newProb){
            newSequence.push_back(true);
        }
        else {
            newSequence.push_back(false);
        }
    }
    DanceGraph* newGraph = new DanceGraph(20, .1);
    return *newGraph;
}

