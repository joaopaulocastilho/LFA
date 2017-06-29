#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include"grammar.h"
using namespace std;

#define MAX_LINHA 1123

typedef pair<int, string> pis; //pis é um pair de int com string
typedef vector<pis> vpis; //vpis é um vector de pair de int com string

int main(void) {
  char linha[MAX_LINHA];
  int states_cont = 0; //Contador de estados. Diz quantos estados tem para saber qual o id do próximo estado. Inicialmente é 0 (Óbvio).
  vpis states_name; //vector onde first() é o id do estado e second() é o nome do estado. Exemplo: estado com id 0 é o estado S.
  FILE *input_file;
  input_file = fopen("input/input.txt", "r");
  while (fgets(linha, MAX_LINHA, input_file)) {
    //Vamos ler e tratar uma gramatica
    grammar_treatment(linha, states_cont, states_name);
  }
  fclose(input_file);
  return 0;
}
