#ifndef GRAMMAR_H
#define GRAMMAR_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include<set>
#include"utilities.h"
using namespace std;

#define MAX_STATE 1123

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

//------------------------------------Declaração das variáveis------------------------------------//
int lim = 0, states_cont, terms_cont, states_qtty;
vpsb states_name; //vector onde a posição i corresponde ao i-ésimo não-terminal.
vs terms_name; //vector onde a posição i corresponde ao i-ésimo terminal.
map<string, int> map_states; //Mapeando os não terminais para um ID.
map<string, int> map_terms; //Mapeia os terminais para saber se já está no autômato.
char last_state_generated[MAX_STATE];
vi transition_cont; //Vector em quantos estados diferentes cada terminal aparece.
vi alive;
//--------------------------------Fim da declaração das variáveis---------------------------------//

//Função que recebe um arquivo e mapeia todos os símbolos de uma gramática. Ela é responsável por fazer o mapeamento de toda a entrada, tanto da gramática quanto dos tokens. Devolve o automato construído.
void create_automata(FILE *input_file, viii &afnd);

//Imprimir o AFND
void print_afnd(int l, int c, viii &afnd);

void print_file(int l, int c, viii &afnd);

void minimize_afnd(viii &afnd);

#endif
