#include <cstdio>
#include <string>
#include <string.h>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include "recognize.h"

using namespace std;

#define MAX 1123

int main(void){
  //Variables
  char word[MAX], first_stack, wtp[MAX];
  int terms_count = 0, trash, accepted;
  map<pc,vs> transitionsMap;
  map<char, int> map_terms;
  vc terms_name;
  FILE *inputFile;
  inputFile = fopen("input/input1.txt", "r");
  loadTransitions(inputFile, transitionsMap, first_stack);
  printTransitions(transitionsMap);
  build_map_terms(transitionsMap, map_terms, terms_name, terms_count);
  printf("\nInforme a palavra de entrada (# para sair): ");
  while (trash = scanf(" %s", word), strcmp(word, "#")) {
    accepted = 0;
    vi word_terms(terms_count, 0);
    vi stack_terms(terms_count, 0);
    stack<char> astack;
    calculate_word_terms(word_terms, map_terms, terms_count, word);
    printf("Contador de terminais da palavra:\n");
    for (int i = 0; i < terms_count; i++) {
      printf("%c -> %d\n", terms_name[i], word_terms[i]);
    }
    printf("---------------------------------------------\n");
    //Vamos chamar o BT
    astack.push(first_stack);
    wtp[0] = first_stack;
    wtp[1] = '\0';
    printf("Iniciando o reconhecimento da palavra %s\n", word);
    backtracking(word_terms, map_terms, terms_count, word, astack, accepted, stack_terms, transitionsMap, wtp, 0, terms_name, 0);
    printf("A PALAVRA INSERIDA%s FOI RECONHECIDA!\n", accepted ? "" : " NAO");
    printf("\nInforme a palavra de entrada (# para sair): ");
  }
  trash++;
  return 0;
}

//OBISERVAZOIS
// # = epslon
