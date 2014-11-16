#ifndef TRADUTOR_HPP
#define TRADUTOR_HPP

#include <iostream>
#include <vector>
#include <fstream>

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
	C_INPUT,
	C_OUTPUT,
	S_INPUT,
	S_OUTPUT,
	STOP
};

int traducaoIA32();
vector<string> lerInteiro();
vector<string> escreverInteiro();
vector<string> lerChar();
vector<string> escreverChar();
vector<string> lerString();
vector<string> escreverString();
vector<string> instStop();

#endif //TRADUTOR_HPP
