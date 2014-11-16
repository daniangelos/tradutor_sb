#include "../header/tradutor.hpp"

int traducaoIA32(){
	// ** Traduzir objeto assembly hipotetico pra codigo IA32
	ifstream fpInput;
	ofstream fpOutput;
	vector<int> opcodes;
	vector<string> codigoIA_32, temp;
	string buffer, opcode;
	int i, j;

	fpInput.open("./outputs/objHipotetico.o");
	if(!fpInput.is_open()){
		cout << "Arquivo objeto hipotetico nao encontrado." << endl;
		return 1;
	}

	// Pega os opcodes do objeto e passa para um vetor de inteiros
	getline(fpInput, buffer); 
	for (i = 0; i < buffer.size(); ++i)
	{
		if(buffer[i] != ' '){
			opcode += buffer[i];
		}
		else{
			opcodes.push_back(stoi(opcode));
			opcode.clear();
		}
	}

	// Inicio do .text
	codigoIA_32.push_back("section .text");
	codigoIA_32.push_back("global _start");
	codigoIA_32.push_back("_start:");

	//TODO: primeiro data ou text? 
	
	// Le vetor de opcodes ate encontrar stop
	// Gera codigo ia-32 correspondente a instrucao
	i = -1;
	do{
		i++;
		switch(opcodes[i]){
			case ADD:
				//Jony aqui
				break;
			case SUB:
				//Jony aqui
				break;
			case MULT:
				//Jony aqui
				break;
			case DIV:
				//Jony aqui
				break;
			case JMP:
				//Jony aqui
				break;
			case JMPN:
				//Jony aqui
				break;
			case JMPP:
				//Jony aqui
				break;
			case JMPZ:
				//Jony aqui
				break;
			case COPY:
				//Jony aqui
				i += 2;		// operacao que utiliza 2 operandos
				break;
			case LOAD:
				//Jony aqui
				break;
			case STORE:
				//Jony aqui
				break;
			case INPUT:
				temp = lerInteiro();
				i++;	  	// incremento pra desconsiderar o operando
				break;
			case OUTPUT:
				temp = escreverInteiro();
				i++;
				break;
			case C_INPUT:
				temp = lerChar();
				i++;
				break;
			case C_OUTPUT:
				temp = escreverChar();
				i++;
				break;
			case S_INPUT:
				temp = lerString();
				i++;
				break;
			case S_OUTPUT:
				temp = escreverString();
				i++;
				break;
			case STOP:
				temp = instStop(); 
				break;
		}
		// Insere no codigo a instrucao processada
		for(j = 0; j < temp.size(); j++){
			codigoIA_32.push_back(temp[j]);
		}
	} while(opcodes[i] != STOP && i < opcodes.size() - 1);

	return 0;
}

vector<string> lerInteiro(){
	vector<string> codigo;

	return codigo;
}

vector<string> escreverInteiro(){
	vector<string> codigo;

	return codigo;
}

vector<string> lerChar(){
	vector<string> codigo;

	return codigo;
}

vector<string> escreverChar(){
	vector<string> codigo;

	return codigo;
}

vector<string> lerString(){
	vector<string> codigo;

	return codigo;
}

vector<string> escreverString(){
	vector<string> codigo;

	return codigo;
}

vector<string> instStop(){
	vector<string> codigo;

	//Retorna o codigo que encerra um programa em IA-32
	codigo.push_back("mov eax, 1");
	codigo.push_back("mov ebx, 0");
	codigo.push_back("int 80h");

	return codigo;
}
