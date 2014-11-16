all: TRADUTOR clear

TRADUTOR: main.o montador.o pre_parser.o tradutor.o
	g++ main.o montador.o pre_parser.o tradutor.o -o tradutor

main.o: src/main.cpp
	g++ -ansi  src/main.cpp -std=c++11 -g -c

montador.o: montador/src/montador.cpp montador/header/montador.hpp
	g++ -ansi  montador/src/montador.cpp -std=c++11 -g -c

pre_parser.o: montador/src/pre_parser.cpp montador/header/pre_parser.hpp
	g++ -ansi  montador/src/pre_parser.cpp -std=c++11 -g -c

tradutor.o: src/tradutor.cpp header/tradutor.hpp
	g++ -ansi src/tradutor.cpp -std=c++11 -g -c

clear:
	rm *.o
