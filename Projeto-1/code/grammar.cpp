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


void mape_token(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, char linha[], int &states_qtty) {
  int i;
  char linha_tmp[2];
  linha_tmp[1] = '\0';
  for (i = 0; linha[i] != '\n'; i++) {
    linha_tmp[0] = linha[i];
    if (map_terms.find(string(linha_tmp)) == map_terms.end()) {
      map_terms[string(linha_tmp)] = terms_cont++;
      terms_name.push_back(string(linha_tmp));
    }
  }
  states_qtty += strlen(linha) - 1;
}

void mape_grammar(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, char linha[]) {
  int i, j, flag, id_current_state = 0;
  char state[MAX], term[MAX];
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
  flag = 1;
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

void symbols_mape(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, int &states_qtty) {
  int i, j, id_current_state = 0;
  char linha[MAX];
  fseek(input_file, 0, SEEK_SET);
  while (fgets(linha, MAX, input_file)) {
    if (next_simb(linha, 0, '<') == -1) mape_token(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, linha, states_qtty);
    else mape_grammar(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, linha);
  }
  states_qtty += states_cont;
}

void new_state_inc(char *state) {
  if (state[0] == '\0') {
    state[0] = 'A';
    state[1] = '\0';
  }
  else if (state[0] == 'Z') {
    state[0] = 'A';
    new_state_inc(state + sizeof(char));
  }
  else state[0]++;
}

void tokens_mape(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, viii &afnd, char last_state_generated[], char linha[]) {
  int i, id_current_terminal, id_last_state;
  char linha_tmp[2];
  linha_tmp[1] = '\0';
  last_state_generated[0] = '\0';
  do {
    for (i = 0; linha[i] != '\n'; i++) {
      linha_tmp[0] = linha[i];
      id_current_terminal = map_terms[string(linha_tmp)];
      do {
        new_state_inc(last_state_generated);
      } while (!(map_states.find(string(last_state_generated)) == map_states.end()));
      id_last_state = (i ? states_cont : 0);
      map_states[string(last_state_generated)] = states_cont++;
      states_name.push_back(make_pair(last_state_generated, linha[i+1] == '\n' ? true : false));
      afnd[id_last_state][id_current_terminal].push_back(map_states[string(last_state_generated)]);
    }
  } while(fgets(linha, MAX, input_file));
}

void create_afnd(FILE *input_file, int &states_cont, vpsb &states_name, map<string, int> &map_states, int &terms_cont, vs &terms_name, map<string, int> &map_terms, viii &afnd, char last_state_generated[]) {
  int i, j, flag = 1;
  int id_current_state, id_current_term, transition;
  char linha[MAX], state[MAX], term[MAX];
  fseek(input_file, 0, SEEK_SET);
  while (fgets(linha, MAX, input_file)) {
    if (next_simb(linha, 0, '<') == -1) {
      tokens_mape(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, afnd, last_state_generated, linha);
      return;
    }
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
  for (i = 0; i < (int)terms_name.size(); i++) {
    printf("%s ", (terms_name[i] == "") ? "eps" : terms_name[i].c_str());
  }
  printf("\n");
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
