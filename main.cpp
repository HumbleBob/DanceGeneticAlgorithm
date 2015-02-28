//
//  main.cpp
//  EvolutionaryAlgorithms
//
//  Created by Sawyer Bowman on 2/5/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include <iostream>
#include "EvolutionaryAlgorithm.h"
#include "DanceGraph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    srand( time( NULL ) );
    
    DanceGraph* test = new DanceGraph(20, .1);
    
    
//    //Make sure number of command line arguments is correct (print if not)
//
//    if (argc < 9){
//        cout << "You've entered an incorrect number of arguments to the program!" << endl;
//        cout << "For the Genetic Algorithm, please input the following parameters:" << endl;
//        cout << "   file name       = the name of the file containing the problem (string)" << endl;
//        cout << "   individuals     = number of individuals in population (int)" << endl;
//        cout << "   selection       = type of selection of breeding pool (string):" << endl;
//        cout << "                     ts   = tournament selection" << endl;
//        cout << "                     rs   = rank based selection" << endl;
//        cout << "                     bs   = Boltzmann selection" << endl;
//        cout << "    crossover      = crossover method (string):" << endl;
//        cout << "                     1c   = 1-point crossover" << endl;
//        cout << "                     uc   = uniform crossover" << endl;
//        cout << "    pC             = crossover probability (double)" << endl;
//        cout << "    pM             = mutation probability (double)" << endl;
//        cout << "    generations    = max number of generations to run (int)" << endl;
//        cout << "    algorithm      = type of algorithm to run (string)" << endl;
//        cout << "                     g     = Genetic Algorithm" << endl;
//        cout << "                     p     = Population Based Incremental Learning (PBIL)" << endl;
//        cout << "    OPTIONAL disInterval   = show best interval (int)" << endl;
//        cout << "    OPTIONAL staleGen      = decide to stop evolving if no positive change in x generations (int)" << endl;
//        
//        cout << "" << endl;
//        
//        cout << "For the Population Based Incremental Learning (PBIL) Algorithm, please input the following parameters:" << endl;
//        cout << "   file name               = the name of the file containing the problem (string)" << endl;
//        cout << "   individuals             = number of individuals in population (int)" << endl;
//        cout << "   positive learning rate  = for the best-individual update (double):" << endl;
//        cout << "   negative learning rate  = for the worst-individual update (double):" << endl;
//        cout << "   pM                      = mutation probability (double)" << endl;
//        cout << "   mA                      = mutation amount (double)" << endl;
//        cout << "   generations             = max number of generations to run (int)" << endl;
//        cout << "   algorithm               = type of algorithm to run (string)" << endl;
//        cout << "                               g     = Genetic Algorithm" << endl;
//        cout << "                               p     = Population Based Incremental Learning (PBIL)" << endl;
//        cout << "   OPTIONAL disInterval    = show best interval (int)" << endl;
//        cout << "   OPTIONAL staleGen       = decide to stop evolving if no positive change in x generations (int)" << endl;
//        exit(1);
//    }
//    
//    //If correct number of command line arguments, convert to proper type
//    
//    else {
//        
//        //These variables before the if statement represent shared values between Genetic and PBIL
//        
//        string alg = argv[8];
//        string name = argv[1];
//        int pop = stoi(argv[2]);
//        int maxGen = stoi(argv[7]);
//        int printInt = 1;
//        int staleGen = maxGen;
//        if (argc == 10 || argc == 11){
//            printInt = stoi(argv[9]);
//        }
//        if (argc == 11){
//            staleGen = stoi(argv[10]);
//        }
//        
//        //These variables represent different values between Genetic and PBIL
//        
//        string select = "";
//        string cross = "";
//        double pos = 0;
//        double neg = 0;
//        
//        double pCross = 0;
//        double pMut = 0;
//        double mutAmt = 0;
//        
//        /*
//         *Some parameters are not shared between Genetic and PBIL implementations
//         *so it is necessary to divide them up and create separate objects.
//         */
//        if (alg == "g"){
//            if (argv[3] == TS || argv[3] == RS || argv[3] == BS){
//                select = argv[3];
//            }
//            else {
//                cout << "Invalid second argument specifying selection type.  Please use:" << endl;
//                cout << "   ts  = tournament selection" << endl;
//                cout << "   rs   = rank based selection" << endl;
//                cout << "   bs   = Boltzmann selection" << endl;
//                exit(1);
//            }
//            if (argv[4] == ONE_C || argv[4] == UNIFORM){
//                cross = argv[4];
//            }
//            else {
//                cout << "Invalid fourth argument specifying crossover type.  Please use:" << endl;
//                cout << "   1c  = 1-point crossover" << endl;
//                cout << "   uc  = uniform crossover" << endl;
//                exit(1);
//            }
//            pCross = stod(argv[5]);
//            pMut = stod(argv[6]);
//            
//            //Create a Genetic object (with the appropriate parameters)
//            EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(name, pop, select, cross, pCross, pMut, maxGen, alg, printInt, staleGen);
//            
//            //TODO:implement run method
//            ea.run();
//        }
//        else {
//            pos = stod(argv[3]);
//            neg = stod(argv[4]);
//            pMut = stod(argv[5]);
//            mutAmt = stod(argv[6]);
//            
//            //Create a PBIL object (with the appropriate parameters)
//            EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(name, pop, pos, neg, pMut, mutAmt, maxGen, alg, printInt, staleGen);
//            
//            //TODO:implement run method
//            ea.run();
//            
//        }
//        
//        cout << "done!" << endl;
//        
//    }
    
    return 0;
}
