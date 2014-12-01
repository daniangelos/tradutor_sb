#include "../header/tradutor.hpp"

vector<string> defines;

int traducaoIA32(vector<int> vetObjeto){
	// ** Traduzir objeto assembly hipotetico pra codigo IA32
	ofstream fpOutput;
	vector<int> opcodes;
	vector<string> codigoIA_32, temp;
	string buffer, opcode;
	int i, j;
	int enderecoAtual;
	vector<string> paraBss;
	vector<string> paraData;

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
				break;
			case SUB:
                buffer = "sub";
                temp.push_back(getAddFormat(buffer,opcodes[i+1]));
                i++;
				break;
			case MULT:
				temp.push_back(getMultFormat(opcodes[i+1]));
				i++;
				break;
			case DIV:
				temp.push_back(getDivFormat(opcodes[i+1]));
				i++;
				break;
			case JMP:
                buffer = "jmp";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				break;
			case JMPN:
                buffer = "jl";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				break;
			case JMPP:
                buffer = "jg";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				break;
			case JMPZ:
                buffer = "je";
                temp.push_back(getJmpFormat(buffer,opcodes[i+1]));
                i++;
				break;
			case COPY:
				temp = getCopyFormat(opcodes[i+1],opcodes[i+2]);
				i += 2;		// operacao que utiliza 2 operandos
				break;
			case LOAD:
				temp.push_back(getLoadFormat(opcodes[i+1]));
				i++;
				break;
			case STORE:
				temp.push_back(getStoreFormat(opcodes[i+1]));
				i++;
				break;
			case INPUT:
				temp = lerInteiro(opcodes[i+1]);
				i++;	  	// incremento pra desconsiderar o operando
				break;
			case OUTPUT:
				temp = escreverInteiro(opcodes[i+1]);
				i++;
				break;
			case C_INPUT:
				temp = lerChar(opcodes[i+1]);
				i++;
				break;
			case C_OUTPUT:
				temp = escreverChar(opcodes[i+1]);
				i++;
				break;
			case S_INPUT:
				temp = lerString(opcodes[i+1]);
				i++;
				break;
			case S_OUTPUT:
				temp = escreverString(opcodes[i+1]);
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


    //apenas para deixar o codigo ia32 mais bonitinho no final:
    codigoIA_32.push_back("");

	temp = escreverSubrotinas();
	for(j = 0; j < temp.size(); j++){
		codigoIA_32.push_back(temp[j]);
	}

	//como o criterio de parada eh o stop, nesse ponto geramos o IA32 do text, a partir daqui vamos fazer o data!!!
	//eh necesario section bss?!
	enderecoAtual = i;

	while(enderecoAtual < opcodes.size()){
        //usarei a tabela de rotulos para verificar se a variavel em questao eh space e qnt espaço alocado,
        //a tabela de rotulos eh global, usarei na bruta!!!
        //achar a variavel em questao pelo endereco dela que agente tem no endereco atual
        for(auto it = tabelaDeRotulos.begin();it != tabelaDeRotulos.end();it++){
            buffer.clear();
            //conferir se o endereco eh igual ao do endereco atual, se for eh a variavel q agente quer
            if(it->second.value == enderecoAtual){
                //variavel achada
                if(it->second.isLabel){
                    //nao sei o q fazer com isso ainda

                }
                else if(!it->second.isConst){
                    //botar no bss ja que eh spaco nao inicializado
                    buffer += "var";
                    buffer += to_string(enderecoAtual);
                    buffer += ": ";
                    buffer += "resb ";
                    buffer += to_string(it->second.spaceSIZE);
                    defines.push_back("\n%define VAR" + to_string(enderecoAtual) +
                    	 "_SIZE " + to_string(it->second.spaceSIZE));

                    paraBss.push_back(buffer);

                    //passar direto dos proximos spaces alocados como zero nos opcodes, que ja foram declarados.
                    enderecoAtual = enderecoAtual + it->second.spaceSIZE - 1;

                }
                else{
                    //so pode ser const, botar no data, porem nada impede que o modifiquem no data, pensemos depois.
                    buffer += "var";
                    buffer += to_string(enderecoAtual);
                    buffer += ": ";
                    buffer += "dw ";
                    buffer += to_string(it->second.valorDoConst);   //valor do const

                    paraData.push_back(buffer);


                }
            }

        }


        enderecoAtual++;
	}

	//usar os vector de strings de bss e data para enche-los
	//começar com o data
	codigoIA_32.push_back("");
	codigoIA_32.push_back("section .data");
	for(j=0;j<paraData.size();j++){
        codigoIA_32.push_back(paraData[j]);

	}

	//bss
	codigoIA_32.push_back("");
	codigoIA_32.push_back("section .bss");
	for(j=0;j<paraBss.size();j++){
        codigoIA_32.push_back(paraBss[j]);

	}


	fpOutput.open("outputs_ia32/assemblyIA32.s");
	for(i=0;i < defines.size();i++){
        fpOutput << defines[i];
        fpOutput << '\n';

	}
	for(i=0;i < codigoIA_32.size();i++){
        fpOutput << codigoIA_32[i];
        fpOutput << '\n';

	}

    fpOutput.close();
	return 0;
}

vector<string> lerInteiro(int op){
	vector<string> codigo;

	codigo.push_back("mov ecx, var" + to_string(op));
	codigo.push_back("call input");
	codigo.push_back("sub byte [ecx], 0x30");

	return codigo;
}

vector<string> escreverInteiro(int op){
	vector<string> codigo;

	codigo.push_back("mov ecx, var" + to_string(op));
	codigo.push_back("add byte [ecx], 0x30");
	codigo.push_back("call output");

	return codigo;
}

vector<string> lerChar(int op){
	vector<string> codigo;

	codigo.push_back("mov ecx, var" + to_string(op));
	codigo.push_back("call input");

	return codigo;
}

vector<string> escreverChar(int op){
	vector<string> codigo;

	codigo.push_back("mov ecx, var" + to_string(op));
	codigo.push_back("call output");

	return codigo;
}

vector<string> lerString(int op){
	vector<string> codigo;

	codigo.push_back("sub ah, ah");
	codigo.push_back("add ah, 0x0a");
	codigo.push_back("mov ebx, var" + to_string(op));
	codigo.push_back("mov edx, VAR" + to_string(op) + "_SIZE");
	codigo.push_back("add edx, ebx");
	codigo.push_back("inString:");
	codigo.push_back("mov ecx, ebx");
	codigo.push_back("call input");
	codigo.push_back("mov BYTE al, [ebx]");
	codigo.push_back("cmp al, ah");
	codigo.push_back("je endInString");
	codigo.push_back("inc ebx");
	codigo.push_back("cmp ebx, edx");
	codigo.push_back("jb inString");
	codigo.push_back("endInString:");

	return codigo;
}

vector<string> escreverString(int op){
	vector<string> codigo;

	codigo.push_back("sub ah, ah");
	codigo.push_back("add ah, 0x0a");
	codigo.push_back("mov ebx, var" + to_string(op));
	codigo.push_back("mov edx, VAR" + to_string(op) + "_SIZE");
	codigo.push_back("add edx, ebx");
	codigo.push_back("outString:");
	codigo.push_back("mov ecx, ebx");
	codigo.push_back("mov BYTE al, [ebx]");
	codigo.push_back("cmp al, ah");
	codigo.push_back("je endOutString");
	codigo.push_back("call output");
	codigo.push_back("inc ebx");
	codigo.push_back("cmp ebx, edx");
	codigo.push_back("jb outString");
	codigo.push_back("endOutString:");


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

string getMultFormat(int op){
    string result;

    result += "mul byte [var";
    result += to_string(op);
    result += "]";

    return result;


}

string getLoadFormat(int op){
    string result;

    result += "mov eax, ";
    result += "[var";
    result += to_string(op);
    result += "]";

    return result;


}

string getStoreFormat(int op){
    string result;

    result += "mov word [var";
    result += to_string(op);
    result += "], ";
    result += "eax";

    return result;


}

string getDivFormat(int op){
    string result;

    result += "div word [var";
    result += to_string(op);
    result += "]";

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

vector<string> escreverSubrotinas(){
	vector<string> codigo;

	//Input padrao
	codigo.push_back("input:");
	codigo.push_back("pusha");
	codigo.push_back("mov eax, 3");
	codigo.push_back("mov ebx, 0");
	codigo.push_back("mov edx, 1");
	codigo.push_back("int 0x80");
	codigo.push_back("popa");
	codigo.push_back("ret");

	//Output padrao
	codigo.push_back("output:");
	codigo.push_back("pusha");
	codigo.push_back("mov eax, 4");
	codigo.push_back("mov ebx, 1");
	codigo.push_back("mov edx, 1");
	codigo.push_back("int 0x80");
	codigo.push_back("popa");
	codigo.push_back("ret");

	return codigo;
}
