#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include"grammar.h"
#include"determinize.h"
using namespace std;

int main(void) {
  FILE *input_file;
  viii afnd; //This is our automata
  input_file = fopen("input/input7.txt", "r");
  create_automata(input_file, afnd);
  minimize_afnd(afnd, alive);
  automaton_determinize(afnd);
  remove_unreachable(afnd);
  print_file(afnd);
  fclose(input_file);
  return 0;
}
