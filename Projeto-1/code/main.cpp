#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include"grammar.h"
using namespace std;

#define MAX_LINHA 1123

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;


int main(void) {
  int i;
  int states_cont = 0; //Contador de estados. Diz quantos estados tem.
  int terms_cont = 0; //Contador de terminais.
  vpsb states_name; //vector onde a posição i corresponde ao i-ésimo não-terminal.
  vs terms_name; //vector onde a posição i corresponde ao i-ésimo terminal.
  map<string, int> map_states; //Mapeando os não terminais para um ID.
  map<string, int> map_terms; //Mapeia os terminais para saber se já está no autômato.
  FILE *input_file;
  input_file = fopen("input/input.txt", "r");
  symbols_mape(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms);
  viii afnd(states_cont, vii(terms_cont, vi())); //Declarando o AFND
  create_afnd(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, afnd);
  //printf("states_cont: %d\n terms_cont: %d\n", states_cont, terms_cont);
  print_afnd(states_cont, terms_cont, afnd, states_name, terms_name);
  fclose(input_file);
  return 0;
}
