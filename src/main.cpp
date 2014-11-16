#include <iostream>
#include <string.h>
#include "../montador/header/montador.hpp"
//#include "../header/tradutor.hpp"

using namespace std;

int main(int argc, char* argv[]){

	char * input;

	if(argc != 2){
		cout << "Erro! Numero de argumentos diferente do esperado." << endl;
		return (1);
	}

	input = argv[1];
	// Usar o montador (trab1) pra gerar o objeto hipotetico e auxiliar a traducao
	gerarObjetoHipotetico(input);
	//traducaoIA32();
	
	return 0;
}
