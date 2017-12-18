#include"determinize.h"
#include"grammar.h"

void print_dictionary(vii &states_dictionary, vpsb &names) {
  int i, j;
  //printf("SIZE = %d\n", (int)states_dictionary.size());
  for (i = 0; i < (int)states_dictionary.size(); i++) {
    printf("%s ->", names[i].first.c_str());
    for (j = 0; j < (int)states_dictionary[i].size(); j++) {
      printf(" %s", names[states_dictionary[i][j]].first.c_str());
    }
    printf("\n");
  }
}

void dictionary_initialize(int n, vii &states_dictionary) {
  int i;
  for (i = 0; i < n; i++) {
    vi aux;
    states_dictionary.push_back(aux);
    states_dictionary[i].push_back(i);
  }
}

int create_new_state(viii &afnd, int i, int j, int &states_cont, map <string, int> &map_states, vpsb &states_name, int &terms_cont, vii &states_dictionary, char last_state_generated[], int new_final, vi &alive, vs &terms_name) {
  int k, l, m, n, state_composition, find_composition_states, insert_automaton, my_state;
  do {
    new_state_inc(last_state_generated);
  } while (map_states.find(string(last_state_generated)) != map_states.end());
  map_states[string(last_state_generated)] = states_cont++;
  alive.push_back(1); //TESTE
  states_name.push_back(make_pair(last_state_generated, new_final));
  vi aux;
  my_state = states_cont - 1;
  states_dictionary.push_back(aux);
  for (k = 0; k < (int)afnd[i][j].size(); k++) {
    states_dictionary[my_state].push_back(afnd[i][j][k]);
  }
  //printf("Determinizando: Estado %s\n", states_name[i].first.c_str());
  //print_dictionary(states_dictionary, states_name);
  vii new_line(terms_cont, vi());
  afnd.push_back(new_line);
  //printf("%d\n", (int)afnd[my_state].size());
  //printf("Criando o estado %s\n", states_name[my_state].first.c_str());
  for (k = 0; k < terms_cont; k++) {
    for (l = 0; l < (int)states_dictionary[my_state].size(); l++) {
      state_composition = states_dictionary[my_state][l];
      for (m = 0; m < (int)afnd[state_composition][k].size(); m++) {
        find_composition_states = afnd[state_composition][k][m];
        //printf("indo buscar em %s\n", states_name[find_composition_states].first.c_str());
        for (n = 0; n < (int)states_dictionary[find_composition_states].size(); n++) {
          // printf("saoecuh\n");
          insert_automaton = states_dictionary[find_composition_states][n];
          if (find(afnd[my_state][k].begin(), afnd[my_state][k].end(), insert_automaton) == afnd[my_state][k].end()) {
            afnd[my_state][k].push_back(insert_automaton);
          }
        }
      }
    }
    if ((int)afnd[my_state][k].size() > 1) {
      //Tem que tratar indeterminismo
      sort(afnd[my_state][k].begin(), afnd[my_state][k].end());
      transition_determinize(afnd, my_state, k, states_cont, map_states, states_name, terms_cont, states_dictionary, last_state_generated, alive, terms_name);
    }
  }
  return my_state;
}

void transition_determinize(viii &afnd, int i, int j, int &states_cont, map <string, int> &map_states, vpsb &states_name, int &terms_cont, vii &states_dictionary, char last_state_generated[], vi &alive, vs &terms_name) {
  int k, l, equal, transition, new_final = 0;
  for (k = 0; k < (int)states_dictionary.size(); k++) {
    if (!(states_dictionary[k].size() == afnd[i][j].size())) continue;
    for (equal = 1, new_final = l = 0; equal && l < (int)afnd[i][j].size(); l++) {
      equal &= (states_dictionary[k][l] == afnd[i][j][l]);
      new_final |= states_name[afnd[i][j][l]].second;
    }
    if (equal) {
      transition = k;
      break; //Encontramos uma composição.
    }
  }
  if (!equal) {
    transition = create_new_state(afnd, i, j, states_cont, map_states, states_name, terms_cont, states_dictionary, last_state_generated, new_final, alive, terms_name);
  }
  afnd[i][j].clear();
  afnd[i][j].push_back(transition);
  printf("Determinizando estado %s\n", states_name[i].first.c_str());
  print_afnd(states_cont, terms_cont, afnd, states_name, terms_name);
  //printf("NOVO ESTADO: %s\n", states_name[afnd[i][j][0]].first.c_str());
}

void automaton_determinize(viii &afnd, int &states_cont, int &terms_cont, vpsb &states_name, vs &terms_name, vi &transition_cont, vi &alive, map<string, int> &map_states, map<string, int> &map_terms, char last_state_generated[]) {
  int limit = states_cont, i, j;
  vii states_dictionary;
  dictionary_initialize(states_cont, states_dictionary);
  //print_dictionary(states_dictionary, states_name);
  for (i = 0; i < limit; i++) {
    if (!alive[i]) continue;
    for (j = 0; j < terms_cont; j++) {
      if (!transition_cont[j]) continue;
      if ((int)afnd[i][j].size() > 1) {
        //Tem que tratar indeterminismo
        sort(afnd[i][j].begin(), afnd[i][j].end());
        transition_determinize(afnd, i, j, states_cont, map_states, states_name, terms_cont, states_dictionary, last_state_generated, alive, terms_name);
      }
    }
  }
}

void select_valids(int states_cont, int terms_cont, viii &afnd, vi &vis, int u) {
  int i, j;
  vis[u] = 1;
  for (i = 0; i < terms_cont; i++) {
    for (j = 0; j < (int)afnd[u][i].size(); j++) {
      if (afnd[u][i][j] != -1) {
        if (!vis[afnd[u][i][j]]) {
          select_valids(states_cont, terms_cont, afnd, vis, afnd[u][i][j]);
        }
      }
    }
  }
}

void remove_unreachable(int states_cont, int terms_cont, viii &afnd, vi &vis, vpsb &states_name, vs &terms_name, map<string, int> &map_states, map<string, int> &map_terms) {
  int i;
  vi seen(states_cont, 0);
  //lança a DFS no estado 0, inicial, para já ver os alcançáveis a partir de S
  select_valids(states_cont, terms_cont, afnd, seen, 0);
  for (i = 0; i < states_cont; i++) vis[i] &= seen[i];
}
