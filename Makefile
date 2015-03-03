CC=g++

CFLAGS=-c -Wall

all:	choreolution

choreolution:	main.o EvolutionaryAlgorithm.o Population.o DanceGraph.o DanceMove.o
	$(CC) main.o EvolutionaryAlgorithm.o Population.o DanceGraph.o DanceMove.o -o choreolution

main.o:	main.cpp EvolutionaryAlgorithm.h DanceGraph.h
	$(CC) $(CFLAGS) main.cpp

EvolutionaryAlgorithm.o:	EvolutionaryAlgorithm.cpp EvolutionaryAlgorithm.h Population.h DanceGraph.h
	$(CC) $(CFLAGS) EvolutionaryAlgorithm.cpp

Population.o:	Population.cpp Population.h DanceGraph.h
	$(CC) $(CFLAGS) Population.cpp

DanceGraph.o:	DanceGraph.cpp DanceGraph.h DanceMove.h
	$(CC) $(CFLAGS) DanceGraph.cpp

DanceMove.o:	DanceMove.cpp DanceMove.h
	$(CC) $(CFLAGS) DanceMove.cpp

clean:
	rm *o choreolution