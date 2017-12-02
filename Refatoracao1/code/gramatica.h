#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <stdio.h>

#define TAM_LINHA 112345
#define TAM_NOME 112

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;

struct nterm_t { int id, final; nterm_t() {}
nterm_t(int _id, int _final): id(_id), final(_final) {} };

extern map<string, int>nome_term;
extern map<string, nterm_t>nome_estado;
extern int qtd_terminais;
extern int qtd_estados;
extern int qtd_estados_novos;
extern vvvi automato;
extern vs term_nome;
extern vs estado_nome;

//Essa função recebe um arquivo de entrada e conta a quantidade de terminais e não terminais e os coloca no map.
void mapearGramatica(FILE *entrada);

//Essa função constroi a estrutura do automato a partir do arquivo de entrada
void construirAfndGramatica(FILE *entrada);

#endif
