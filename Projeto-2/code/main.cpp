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
  inputFile = fopen("input/input2.txt", "r");
  loadTransitions(inputFile, transitionsMap, first_stack);
  printTransitions(transitionsMap);
  build_map_terms(transitionsMap, map_terms, terms_name, terms_count);
  while (trash = scanf(" %s", word), strcmp(word, "#")) {
    accepted = 0;
    vi word_terms(terms_count, 0);
    vi stack_terms(terms_count, 0);
    stack<char> astack;
    calculate_word_terms(word_terms, map_terms, terms_count, word);
    for (int i = 0; i < terms_count; i++) {
      printf("%c -> %d\n", terms_name[i], word_terms[i]);
    }
    //Vamos chamar o BT
    astack.push(first_stack);
    printf("%c\n", first_stack);
    wtp[0] = first_stack;
    wtp[1] = '\0';
    backtracking(word_terms, map_terms, terms_count, word, astack, accepted, stack_terms, transitionsMap, wtp, 0, terms_name);
    printf("The word has%s been Accepted!\n", accepted ? "" : " not");
  }
  trash++;
  return 0;
}

//OBISERVAZOIS
// # = epslon
