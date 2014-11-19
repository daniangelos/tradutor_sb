#ifndef TRADUTOR_HPP
#define TRADUTOR_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "../montador/header/montador.hpp"

extern map<string, rotulo> tabelaDeRotulos;

using namespace std;


enum{
	ADD = 1,
	SUB,
	MULT,
	DIV,
	JMP,
	JMPN,
	JMPP,
	JMPZ,
	COPY,
	LOAD,
	STORE,
	INPUT,
	OUTPUT,
	STOP,
	C_INPUT,
	C_OUTPUT,
	S_INPUT,
	S_OUTPUT
};

int traducaoIA32(vector<int> vetObjeto);
vector<string> lerInteiro(int op);
vector<string> escreverInteiro(int op);
vector<string> lerChar();
vector<string> escreverChar();
vector<string> lerString();
vector<string> escreverString();
vector<string> instStop();
string getAddFormat(string inst,int op);
string getJmpFormat(string inst,int op);
vector<string> getCopyFormat(int op1,int op2);
vector<string> escreverSubrotinas();
string getDivFormat(int op);
string getMultFormat(int op);
string getStoreFormat(int op);
string getLoadFormat(int op);

#endif //TRADUTOR_HPP
