#ifndef GRAMMAR_H
#define GRAMMAR_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
using namespace std;

//Ainda não tá bem definido o que faz, mas a princípio recebe uma linha de uma gramática e trata ela.
void grammar_treatment(char linha[], int &states_cont, vector< pair<int, string> > &states_name);

#endif
