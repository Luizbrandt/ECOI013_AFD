#include <iostream>         //Fun��es 'cin()' e 'cout()'.
#include <queue>            //Template de fila FIFO - First In, First Out (Primeiro que entra, primeiro que sai).
#include <vector>           //Template de vetor de tamanho din�mico ao longo da execu��o.
#include <bits/stdc++.h>    //Header file que contpem todas as bibliotecas padr�o do C++;
#include <fstream>          //Fun��es de manipula��o de arquivo.
#include <stdlib.h>         //
#include <map>              //Template de mapas do c++ (chave : valor).
#include <locale.h>         //Fun��o 'setlocale()'.
using namespace std;


/*  Tipo abstrato de dados que cont�m as informa��es do AFD.
    Atributos:  1 - n�mero de estados
                2 - n�mero de s�mbolos da linguagem
                3 - matriz de transi��o do AFD
                4 - estado inicial
                5 - n�mero de estados finais
                6 - vetor que cont�m os estados finais
                7 - n�mero de testes a serem realizados
                8 - vetor de testes contendo as palavras a serem testadas
                9 - mapa contendo o alfabeto, no padr�o letra e posi��o.

    Legenda: o coment�rio ao final de cada linha da estrutura de dados
    indica o n�mero do atributo que a linha de comando representa.
*/

struct Entrada{
	int num_estados;                //1
	int num_simbolos;               //2
	vector<vector<int> > Matriz;    //3
	int estado_inicial;             //4
	int num_estados_finais;         //5
	vector<int> estados_finais;     //6
	int num_testes;                 //7
	vector<string> testes;          //8
	map<char,int> alfabeto;         //9
};


void AFD(Entrada* dados){
	for(int i = 0; i < dados->num_testes; i++){
		cout<<"Testando palavra "<<dados->testes[i]<<':'<<endl;
		string palavra = dados->testes[i];
		cout<<'1';
		int e = dados->estado_inicial;
		for(int i = 0; i< palavra.size();i++){
			int LIN = e-1;
			int COL = dados->alfabeto.find(palavra[i])->second;
			e = dados->Matriz[LIN][COL];
			cout<<" -> "<<e;
		}
		cout<<endl;
		//Este token vai ajudar a verificar se a palavra pertence a linguagem
		bool token = false;
		for(int k = 0; k < dados->num_estados_finais;k++)
			if(e == dados->estados_finais[k]){
				token = true;
			}
		if(token)
			cout<<"A palavra "<< palavra<<" pertence a linguagem"<<endl<<endl;
		else
			cout<<"A palavra "<< palavra<<" -NAO- pertence a linguagem"<<endl<<endl;
	}

}


/*Esta fun��o l� os dados de um arquivo txt e faz o parser para
o processamento do algoritmo de acordo com a estrutura de dados constru�da*/
void imprimeDados(Entrada* dados){
	cout<<"N�mero de estados = "<< dados->num_estados<<'.'<<endl;
	cout<<"N�mero de s�mbolos do alfabeto= "<< dados->num_simbolos<<'.'<<endl;
	cout<<"Estados: "<<endl;
	for(int i = 0; i< dados->num_estados;i++){
		for(int j = 0; j < dados->num_simbolos;j++)
			cout<<dados->Matriz[i][j]<<' ';
		cout<<endl;
	}
	cout<<"Estado inicial = "<< dados->estado_inicial<<endl;
	cout<<"N�mero de estados_finais = "<< dados->num_estados_finais<<endl;
	cout<<"Estados finais: ";
	for(int k = 0; k < dados->num_estados_finais;k++)
		cout<<dados->estados_finais[k]<<' ';
	cout<<endl;
	cout<<"N�mero de testes = "<< dados->num_testes<<endl;
	cout<<"Testes: ";
	for(int l = 0; l < dados->num_testes;l++)
		cout<<dados->testes[l]<<' ';
	cout<<endl;
	cout<<"Alfabeto: ";
	for(int m = 0; m < dados->num_simbolos;m++)
		cout<<dados->alfabeto.find(char(m+97))->first<<", ";
	cout<<endl<<endl;
}

bool parser(string nome_do_arquivo, Entrada* dados){
	//Arquivo de entrada.
	fstream arquivo;
	//String para leitura da linha.
    string palavra;
    //Abertura do arquivo de entrada.
    arquivo.open(nome_do_arquivo.c_str());

  	//La�o condicional: se o arquivo for aberto corretamente, executa o c�digo dentro do escopo do la�o.
  	if(arquivo.is_open()){
        //Direciona a sa�da de dados da linha do arquivo de entrada para a strind 'palavra'.
	    arquivo >> palavra;
			dados->num_estados = atoi(palavra.c_str());
	    arquivo >> palavra;
			dados->num_simbolos = atoi(palavra.c_str());
		for(int i = 0; i < dados->num_estados;i++){
			vector<int> transicao;
			string num;
	    	for(int j = 0;j<dados->num_simbolos;j++){
	    		arquivo >> num;
	    		int num2 = atoi(num.c_str());
	    		transicao.push_back(num2);
	    	}
	    	dados->Matriz.push_back(transicao);
	    }

		arquivo >> palavra;
	    	dados->estado_inicial = atoi(palavra.c_str());
		arquivo >> palavra;
			dados->num_estados_finais = atoi(palavra.c_str());

		for(int i = 0; i < dados->num_estados_finais;i++){
			arquivo >> palavra;
			dados->estados_finais.push_back(atoi(palavra.c_str()));
		}

		arquivo >> palavra;
		dados->num_testes = atoi(palavra.c_str());

		for(int i = 0; i < dados->num_testes;i++){
			arquivo >> palavra;
			dados->testes.push_back(palavra);
		}

		arquivo.close();

		//Criando o alfabeto
		for(int i = 0; i < dados->num_simbolos; i++){
			dados->alfabeto.insert(pair<char,int>(char(i+97),i));
		}
	    return true;
	}else
		return false;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Portuguese");

	Entrada* dados = new Entrada;

	/* Realiza a leitura de dados do arquivo ou
	Finaliza o programa se o arquivo n�o for aberto*/
	if(!parser(argv[1],dados)){
		cout<<"Erro ao abrir o arquivo "<< argv[1]<<endl;
		cout<<"Programa finalizado!"<<endl;
		return 0;
	}

	imprimeDados(dados);
	AFD(dados);

	return 0;
}

/*
Dificuldades encontradas e material consultado;
N�o foram encontradas nenhuma dificuldade no material consultado

Avalia��o sobre o trabalho. Neste ponto voc�s devem dar notas de 1(ruim) a 10
(muito bom) sobre os temas:
Minha nota � 7, pois o trabalho permitiu uma implementa��o geral de um AFD e um APD.
A penalidade de 3 pontos se d� pelo fato de n�o ser permitida a realiza��o do algoritmo em outras
linguagens de programa��o que n�o sejam C/C++ .


o Dificuldade de implementa��o:
N�o foram encontradas dificuldades na implementa��o do algoritmo de AFD.

 import�ncia para a disciplina; dos testes
realizados; avalia��o da dupla sobre o trabalho realizado.
Os testes realizados permitiram uma aplica��o pr�tica sobre o tema te�rico, possibilitando a difus�o
do conhecimento na pr�tica, o que auxilia na consolida��o da compreesn�o do tema.
*/
