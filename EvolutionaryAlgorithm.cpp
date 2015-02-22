//
//  EvolutionaryAlgorithm.cpp
//  EvolutionaryAlgorithms
//
//  Created by Sawyer Bowman on 2/5/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "EvolutionaryAlgorithm.h"

/**
 *Constructor initializing a EvolutionaryAlgorithm object with Genetic properties.
 */

EvolutionaryAlgorithm::EvolutionaryAlgorithm(string name, int pop, string select, string cross, double probCross, double probMut, int maxGen, string alg, int printInt, int staleGen) {
    fileName = name;
    populationSize = pop;
    selection = select;
    crossover = cross;
    probCrossover = probCross;
    probMutation = probMut;
    maxGenerations = maxGen;
    algorithm = alg;
    printInterval = printInt;
    quitEvolve = staleGen;
    
    population = new Population(populationSize);
}

/**
 *Constructor initializing a EvolutionaryAlgorithm object with PBIL properties.
 */

EvolutionaryAlgorithm::EvolutionaryAlgorithm(string name, int pop, double pos, double neg, double probMut, double mutAmt, int maxGen, string alg, int printInt, int staleGen) {
    fileName = name;
    populationSize = pop;
    posLearnRate = pos;
    negLearnRate = neg;
    probMutation = probMut;
    mutationAmount = mutAmt;
    maxGenerations = maxGen;
    algorithm = alg;
    printInterval = printInt;
    quitEvolve = staleGen;
    
    population = new Population(populationSize, probabilityVector);
}

/**
 *The main body of the program. This is responsible for calling fitness for
 *each individual of the population, performing selection, breeding, and
 *repeating the generational cycle until the max fitness (best satisfiability)
 *is found.
 */

void EvolutionaryAlgorithm::run(){
    //start the clock
    clock_t start = clock();
    
    DanceGraph globalBest = population->getBestGraph();
    int genSinceBest = 0;
    
    //while generation < maxGenerations
    int generation = 0;
    while (generation < maxGenerations){
        
        quitEvolving(genSinceBest, false, globalBest, start);
        
        //Run the Genetic Algorithm
        if (algorithm == "g"){
            population->selection(selection);
            population->breed(crossover, probCrossover, probMutation);
        }
        
        //Run the PBIL Algorithm
        else {
            DanceGraph newBest = population->getBestGraph();
            DanceGraph newWorst = population->getWorstGraph();
            updateTowardsBest(newBest);
            updateAwayFromWorst(newBest, newWorst);
            mutateProbVector();
            population->updatePopulation(populationSize, probabilityVector);
        }
        
        //Update the global best if necessary
        DanceGraph best = population->getBestGraph();
        if (best.getFitness() > globalBest.getFitness()){
            globalBest = best;
            genSinceBest = 0;
        }
        
        //Print out the best of the generation (with interval)
        if (generation % printInterval == 0){
            cout << "o " << best.getFitness() << endl;
        }
        isSolved(globalBest, start);
        generation++;
        genSinceBest++;
    }
    quitEvolving(genSinceBest, true, globalBest, start);
}

/**
 *This method checks to see if a given solution is optimal. If it is,
 *the evolution stops, and the solution is printed out.
 */

void EvolutionaryAlgorithm::isSolved(DanceGraph best, clock_t start){
    if (best.getFitness()){
        cout << "c Generation's best solution = " << best.getFitness() << endl;
        cout << "c Program terminated in x seconds" << endl;
        cout << "c Program terminated in " << (clock() - start)/(double)CLOCKS_PER_SEC << " seconds" << endl;
        cout << "s PROBLEM SOLVED" << endl;
        exit(1);
    }
}

/**
 *If the user specifies a number of generations run since a new best has
 *been seen to terminate, then quit the program.
 */

void EvolutionaryAlgorithm::quitEvolving(int generationsRun, bool done, DanceGraph globalBest, clock_t start){
    if (quitEvolve <= generationsRun || done){
        if (done){
            cout << "c Ran though all generations and didn't satisfy all clauses" << endl;
        }
        else {
            cout << "c Terminated program after " << generationsRun << " generations since best solution encountered" << endl;
        }
        cout << "c Best solution found = " << globalBest.getFitness() << endl;
        cout << "c Program terminated in " << (clock() - start)/(double)CLOCKS_PER_SEC << " seconds" << endl;
        exit(1);
    }
}

/**
 *This method updates the probability vector towards the best candidate solution
 */

void EvolutionaryAlgorithm::updateTowardsBest(DanceGraph best) {
//    for (int i = 0; i < probabilityVector.size(); i++){
//        probabilityVector[i] = probabilityVector[i]*(1.0-posLearnRate)+best.getSequence()[i]*posLearnRate;
//    }
}

/**
 *This method updates the probability vector away from the worst candidate solution
 */

void EvolutionaryAlgorithm::updateAwayFromWorst(DanceGraph best, DanceGraph worst){
    for (int i = 0; i < probabilityVector.size(); i++){
//        if (best.getSequence()[i] != worst.getSequence()[i]){
//            probabilityVector[i] = probabilityVector[i]*(1.0-negLearnRate)+best.getSequence()[i]*negLearnRate;
//        }
    }
}

/**
 *This method mutates the probability vector
 */

void EvolutionaryAlgorithm::mutateProbVector(){
    for (int i = 0; i < probabilityVector.size(); i++){
        if ((double)rand()/RAND_MAX < probMutation){
            int mutDirection;
            if (rand() % 2 == 1){
                mutDirection = 1;
            }
            else {
                mutDirection = 0;
            }
            probabilityVector[i] = probabilityVector[i]*(1.0-mutationAmount)+mutDirection*(mutationAmount);
        }
    }
}


