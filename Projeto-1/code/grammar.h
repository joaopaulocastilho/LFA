#ifndef GRAMMAR_H
#define GRAMMAR_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include<set>
#include"generate_state.h"
using namespace std;

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

//Função que recebe um arquivo e mapeia todos os símbolos de uma gramática.
void symbols_mape(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, int &states_qtty, vi &transition_cont, int &lim);

//Função que lê a gramática e completa o AFND
void create_afnd(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, viii &afnd, char last_state_generated[]);

//Imprimir o AFND
void print_afnd(int l, int c, viii &afnd, vpsb &states_name, vs &terms_name);

void print_file(int l, int c, viii &afnd, vpsb &states_name, vs &terms_name, vi &transition_cont, vi &alive);

void minimize_afnd(int states_cont, int terms_cont, viii &afnd, vi &vis, vi &transition_cont, vpsb &states_name, vs &terms_name, map<string, int> &map_states, map<string, int> &map_terms, int &lim);

#endif
