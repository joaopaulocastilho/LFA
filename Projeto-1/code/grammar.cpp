#include"grammar.h"

#define MAX 1123

//Procura pela primeira ocorrencia de um caractere (simbol) na string
int next_simb(char linha[], int s, char simbol) {
  int i;
  for (i = s; linha[i] != simbol; i++) {
    if (i == strlen(linha)) return -1;
  }
  return i;
}


int take_state_name(char linha[], char state[], int i) {
  int j;
  for (i = next_simb(linha, i, '<') + 1, j = 0; linha[i] != '>'; i++) state[j++] = linha[i];
  state[j] = '\0';
  return i;
}

int take_term_name(char linha[], char term[], int i) {
  int j;
  for (j = 0; linha[i] != '<' && linha[i] != '\n' && linha[i] != '|'; i++) {
    if (linha[i] != ' ') term[j++] = linha[i];
  }
  term[j] = '\0';
  return i;
}

void symbols_mape(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms) {
  int i, j, flag, id_current_state = 0;
  char linha[MAX], state[MAX], term[MAX];
  fseek(input_file, 0, SEEK_SET);
  while (fgets(linha, MAX, input_file)) {
    flag = 1;
    //passar o nome do estado (que está a esquerda) para o vetor auxiliar "state". "i" começa depois da primeira ocorrencia do caractere '<' na linha.
    i = take_state_name(linha, state, 0);
    if (map_states.find(string(state)) == map_states.end()) {
      id_current_state = states_cont;
      map_states[string(state)] = states_cont++;
      states_name.push_back(make_pair(string(state), false));
    }
    //Mapear os simbolos terminais
    //Como a gramática é regular, vamos pular o "::=" e parar no primeiro símbolo depois do '='
    i = next_simb(linha, i, '=') + 1;
    //Tem que mapear todos os símbolos terminais até o \n
    while (flag) {
      i = take_term_name(linha, term, i);
      //Verificar se o terminal já está no map, se não estiver, insere.
      if (!strcmp(term, "eps") || linha[i] != '<') {
        states_name[id_current_state].second = true;
      }
      if (strcmp(term, "eps") && map_terms.find(string(term)) == map_terms.end()) {
        map_terms[string(term)] = terms_cont++;
        terms_name.push_back(string(term));
      }
     //Quer dizer que não terá mais produções naquela regra da gramática
     if ((i = next_simb(linha, i, '|')) == -1) flag = 0;
     i++;
   }
 }
}

void create_afnd(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, viii &afnd) {
  int i, j, flag = 1;
  int id_current_state, id_current_term, transition;
  char linha[MAX], state[MAX], term[MAX];
  fseek(input_file, 0, SEEK_SET);
  while (fgets(linha, MAX, input_file)) {
    flag = 1;
    //Pegar o estado que está a esquerda do ::=
    i = take_state_name(linha, state, 0);
    id_current_state = map_states[string(state)];
    i = next_simb(linha, i, '=') + 1;
    while (flag) {
      i = take_term_name(linha, term, i);
      if (strcmp(term, "eps")) {
        id_current_term = map_terms[string(term)];
        if (linha[i] == '<') {
          //Quer dizer que tem um não-terminal depois do terminal.
          i = take_state_name(linha, state, i);
          transition = map_states[string(state)];
        } else {
          //não há um não-terminal depois do terminal
          transition = -1;
        }
        //printf("estado: %d, terminal: %d\n", id_current_state, id_current_term); //otohu
        afnd[id_current_state][id_current_term].push_back(transition);
      }
      //Quer dizer que não terá mais produções naquela regra da gramática
      if ((i = next_simb(linha, i, '|')) == -1) flag = 0;
      i++;
    }
  }
}

void print_afnd(int l, int c, viii &afnd, vpsb &states_name, vs &terms_name) {
  int i, j, k;
  int first;
  for (i = 0; i < l; i++) {
    printf("%s: ", states_name[i].first.c_str());
    for (j = 0; j < c; j++) {
      printf("[");
      for (k = 0, first = 1; k < (int)afnd[i][j].size(); k++) {
        if (first && afnd[i][j][k] != -1) first = 0;
        else if (afnd[i][j][k] != -1) printf(", ");
        printf("%s", afnd[i][j][k] == -1 ? "" : states_name[afnd[i][j][k]].first.c_str());
      }
      printf("] ");
    }
    printf("\n");
  }
}
