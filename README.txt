 ______     ______     ______     _____        __    __     ______    
/\  == \   /\  ___\   /\  __ \   /\  __-.     /\ "-./  \   /\  ___\   
\ \  __<   \ \  __\   \ \  __ \  \ \ \/\ \    \ \ \-./\ \  \ \  __\   
 \ \_\ \_\  \ \_____\  \ \_\ \_\  \ \____-     \ \_\ \ \_\  \ \_____\ 
  \/_/ /_/   \/_____/   \/_/\/_/   \/____/      \/_/  \/_/   \/_____/ 

Project Name:	Evolutionary Algorithms: Lab 2
Created by: 	Sawyer Bowman '15, David Needell '15, Phoebe Bumsted ’17, Robert Choi ’17, John Truskowski ’17, Simon Moushabeck ’15
Email:			Sawyer:	sbowman@bowdoin.edu
			David:	dneedell@bowdoin.edu
			Phoebe:	pbumsted@bowdoin.edu
			Robert:	rchoi@bowdoin.edu
			John:	jtruskow@bowdoin.edu
			Simon:	smoushab@bowdoin.edu

Date Created: 	February 6, 2015
Last Modified: 	March 2, 2015 
Version:		1.0
Language: 		C++

---------------------------------------------------------------------

DESCRIPTION:
This program uses the evolutionary genetic algorithm to evolve a population of dance graphs. We have 20 pre-set moves, and the program creates random graphs of dance moves with a particular probability of making an edge. These graphs are then evaluated by a series of random representative sequences.

HOW TO RUN:
The user must pass the following parameters as command line arguments.
Number Dance Moves (int)	ex. 20
Probability Connect (double)	ex. .05
Population (int)		ex. 100
Selection (string)		ex. rs
Crossover (string)		ex. 1c
Probability Crossover (double)	ex. .7
Probability Mutation (double)	ex. .01
Generations (int)		ex. 500
Algorithm (string)		ex. g
OPTIONAL disInterval (int)	ex. 100
OPTIONAL staleGen (int)		ex. 100
