all: programa


programa: montador.o pre_parser.o
	g++ montador.o pre_parser.o -g -std=c++11 -o montador

montador.o: src/montador.cpp header/montador.hpp
	g++ src/montador.cpp -g -std=c++11 -c

pre_parser.o: src/pre_parser.cpp header/pre_parser.hpp
	g++ src/pre_parser.cpp -g -std=c++11 -c


pre:
	@./montador -p inputs/input outputs/output

macro:
	@./montador -m inputs/input outputs/output

obj:
	@./montador -o inputs/input outputs/output

clear:
	rm *.o
