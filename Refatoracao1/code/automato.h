#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <vector>
#include <map>
#include <string.h>
#include <string>
#include <utility>
#include <stdio.h>
#include "utilidades.h"

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;

struct nterm_t { int id, final; nterm_t() {}
nterm_t(int _id, int _final): id(_id), final(_final) {} };

extern map<string, int>nome_term;
extern map<string, nterm_t>nome_estado;
extern int qtd_terms;
extern int qtd_estados;
extern int qtd_estados_novos;
extern vvvi automato;
extern vs term_nome;
extern vs estado_nome;
extern vi valido;
extern vi tem_transicao;

//Essa função recebe um arquivo de entrada e conta a quantidade de terminais e não terminais e os coloca no map.
void mapearGramatica(FILE *entrada);

//Essa função constroi a estrutura do automato a partir do arquivo de entrada
void construirAfndGramatica(FILE *entrada);

//Função utilizada para imprimir o autôtomato na linha de comando
void imprimeAutomato(vvvi &automato);

//Função utilizada para imprimir o map dos terminais, com intuito de debug
void mostraTerminais(map<string, int> &nome_term);

//Função utilizada para imprimir o map dos estados, com intuito de debug
void mostraEstados(map<string, nterm_t> &nome_estado);

//Recebe um arquivo e mapeia os tokens
void mapearTokens(FILE *entrada);

//Imprime o Autômato no csv
void imprimeArquivo(void);

#endif
