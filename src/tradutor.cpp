#include "../header/tradutor.hpp"

int traducaoIA32(vector<int> vetObjeto){
	// ** Traduzir objeto assembly hipotetico pra codigo IA32
	ofstream fpOutput;
	vector<int> opcodes;
	vector<string> codigoIA_32, temp;
	string buffer, opcode;
	int i, j;

    //comentei toda essa parte pq agente ja tinha esse vetor do trabalho passado.
	//boa!! nem precisa gerar o output do montador entao...
    opcodes = vetObjeto;

	// Inicio do .text
	codigoIA_32.push_back("section .text");
	codigoIA_32.push_back("global _start");
	codigoIA_32.push_back("_start:");

	//TODO: primeiro data ou text?
	//tanto faz! 
	//nao!! preciso saber onde comeca o text no objeto, se nao vou estar lendo dado como instrucao... nao?

	// Le vetor de opcodes ate encontrar stop
	// Gera codigo ia-32 correspondente a instrucao
	i = -1;
	//pensando:
	//add var1 -> add eax, [var1]
	do{
		i++;
		temp.clear();
		switch(opcodes[i]){
			case ADD:
                buffer = "add";
                temp.push_back(getAddFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case SUB:
                buffer = "sub";
                temp.push_back(getAddFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case MULT:
				//Jony aqui
				break;
			case DIV:
				//Jony aqui
				break;
			case JMP:
                buffer = "jmp";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case JMPN:
                buffer = "jl";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case JMPP:
                buffer = "jg";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case JMPZ:
                buffer = "je";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				//Jony aqui
				break;
			case COPY:
				//Jony aqui
				temp = getCopyFormat(opcodes[i+1],opcodes[i+2]);
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

	//como o criterio de parada eh o stop, nesse ponto geramos o IA32 do text, a partir daqui vamos fazer o data!!!
	//eh necesario section bss?!
	codigoIA_32.push_back("section .data");

	fpOutput.open("outputs_ia32/assemblyIA32.s");
	for(i=0;i < codigoIA_32.size();i++){
        fpOutput << codigoIA_32[i];
        fpOutput << '\n';

	}

    fpOutput.close();
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

string getAddFormat(string inst,int op){
    string result;

    result += inst;
    result += " eax, ";
    result += "[var";
    result += to_string(op);
    result += "]";


    return result;


}

string getJmpFormat(string inst,int op){
    string result;

    result += inst;
    result += " label";
    result += to_string(op);

    return result;


}

vector<string> getCopyFormat(int op1,int op2){
    string result;
    vector<string> vetor;

    result += "mov ebx, [var";
    result += to_string(op2);
    result += "]";
    vetor.push_back(result);

    result.clear();

    result += "mov [var";
    result += to_string(op1);
    result += "], ";
    result += "ebx";

    vetor.push_back(result);

    return vetor;


}
