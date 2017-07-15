#ifndef GRAMMAR_H
#define GRAMMAR_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
using namespace std;

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

//Função que recebe um arquivo e mapeia todos os símbolos de uma gramática.
void symbols_mape(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms);

//Função que lê a gramática e completa o AFND
void create_afnd(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, viii &afnd);

//Imprimir o AFND
void print_afnd(int l, int c, viii &afnd, vpsb &states_name, vs &terms_name);

//Ainda não tá bem definido o que faz, mas a princípio recebe uma linha de uma gramática e trata ela.
// void grammar_treatment(char linha[], int &states_cont, int &symbols_cont, vector< pair<int, string> > &states_name, viii &afnd, map<string, int> &terms);

#endif
