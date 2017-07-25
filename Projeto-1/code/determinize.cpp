#include"determinize.h"

// void print_dictionary(map<int, vi> &states_dictionary, vpsb &names) {
//   int i;
//   for (map<int,vi>::iterator it=states_dictionary.begin(); it!=states_dictionary.end(); ++it) {
//     printf("%s ->", names[it->first].first.c_str());
//     for (i = 0; i < (int)it->second.size(); i++) printf(" %s", names[states_dictionary[it->first][i]].first.c_str());
//     printf("\n");
//   }
// }

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

int create_new_state(viii &afnd, int i, int j, int &states_cont, map <string, int> &map_states, vpsb &states_name, int &terms_cont, vii &states_dictionary, char last_state_generated[], int new_final) {
  int k;
  do {
    new_state_inc(last_state_generated);
  } while (map_states.find(string(last_state_generated)) != map_states.end());
  map_states[string(last_state_generated)] = states_cont++;
  states_name.push_back(make_pair(last_state_generated, new_final));
  vi aux;
  my_state = states_cont - 1;
  states_dictionary.push_back(aux);
  for (k = 0; k < (int)afnd[i][j].size(); k++) {
    states_dictionary[my_state] = afnd[i][j][k];
  }
  vii new_line(terms_cont, vi());
  afnd.push_back(new_line);
  for (k = 0; k < terms_cont; k++) {
    


  }
}

void transition_determinize(viii &afnd, int i, int j, int &states_cont, map <string, int> &map_states, vpsb &states_name, int &terms_cont, vii &states_dictionary, char last_state_generated[]) {
  int k, l, equal, transition, new_final;
  for (k = 0; k < (int)states_dictionary.size(); k++) {
    if (!(states_dictionary[k].size() == afnd[i][j].size())) continue;
    for (equal = 1, new_final = l = 0; equal && l < afnd[i][j].size(); l++) {
      equal &= (states_dictionary[l] == afnd[i][j][l]);
      new_final |= states_name[afnd[i][j][l]].second;
    }
    if (equal) {
      transition = k;
      break; //Encontramos uma composição.
    }
  }
  if (!equal) {
    transition = create_new_state(afnd, i, j, states_cont, map_states, states_name, terms_cont, states_dictionary, last_states_generated, new_final);
  }
  afnd[i][j].clear();
  afnd[i][j].push_back(transition);
}

void automaton_determinize(viii &afnd, int &states_cont, int &terms_cont, vpsb &states_name, vs &terms_name, vi &transition_cont, vi &alive, map<string, int> &map_states, map<string, int> &map_terms, char last_state_generated[]) {
  int limit = states_cont, i, j;
  vii states_dictionary;
  dictionary_initialize(states_cont, states_dictionary);
  print_dictionary(states_dictionary, states_name);
  for (i = 0; i < limit; i++) {
    if (!alive[i]) continue;
    for (j = 0; j < terms_cont; j++) {
      if (!transition_cont[j]) continue;
      if ((int)afnd[i][j].size() > 1) {
        //Tem que tratar indeterminismo
        sort(afnd[i][j].begin(), afnd[i][j].end());
        transition_determinize(afnd, i, j, states_cont, map_states, states_name, terms_cont, states_dictionary, last_states_generated);
      }
    }
  }
}
