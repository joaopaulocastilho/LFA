#include"grammar.h"

#define MAX 1123

void grammar_treatment(char linha[], int &states_cont, vector < pair<int, string> > &states_name) {
  int i;
  char state[MAX];
  //passar o nome do estado (que está a esquerda) para o vetor auxiliar "state". "i" começa em 1 pois o primeiro caractere de uma linha na gramática é '<'
  for (i = 1; linha[i] != '>'; i++) state[i-1] = linha[i];
  state[i-1] = '\0';
  //coloca o estado no vector de estados (states_name)
  states_name.push_back(make_pair(states_cont++, string(state)));
}
