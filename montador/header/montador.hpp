#ifndef MONTADOR_HPP
#define MONTADOR_HPP

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <list>
#include "../header/pre_parser.hpp"
#include <cassert>

using namespace std;


typedef struct rotulo
{
	int defined;
	int value;
	int valorDoConst = 0;
	list<int> use;
	bool isLabel;
	bool isVar;
	bool isConst;
	int spaceSIZE = 1;
}rotulo;

typedef struct argumento
{
	string arg;
	int linha;
}argumento;



vector<int> gerarObjetoHipotetico(char * input);

#endif //MONTADOR_HPP
