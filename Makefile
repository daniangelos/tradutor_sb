all: TRADUTOR

TRADUTOR: tradutor.o
	g++ tradutor.o -o tradutor

tradutor.o: src/tradutor.cpp
	g++ -ansi -Wall src/tradutor.cpp -std=c++11 -g -c
	
clear:
	rm *.o
