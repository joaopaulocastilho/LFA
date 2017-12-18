#include"recognize.h"

void printTransitions(map<pc,vs> &transitionsMap){
  int i;
  for(map<pc,vs>::const_iterator it = transitionsMap.begin(); it != transitionsMap.end(); ++it){
    printf("(%c,%c) -> ", it->first.first, it->first.second);
    for(i = 0; i < (int)it->second.size(); i++){
      if(i) printf(",");
      printf("(%s)", it->second[i].c_str());
    }
    printf("\n");
  }
}

// Search for the first encounter with the received symbol.
int nextSymb(char line[], int pos,char symbol){
  int i;
  for (i = pos; line[i] != symbol; i++) {
    if (i == (int)strlen(line)) return -1;
  }
  return i;
}

void loadTransitions(FILE *inputFile, map<pc,vs> &transitionsMap, char &first_stack){
  char line[MAX];
  char tape, stack, transition[MAX];
  int j, index, first = 1;
  fseek(inputFile, 0, SEEK_SET);
  while (fgets(line, MAX, inputFile)) {
    index = nextSymb(line, 0, '<');
    tape = line[++index];
    index = nextSymb(line, index, '<');
    stack = line[++index];
    if (first) {
      first_stack = stack;
      first = 0;
    }
    vs aux;
    while((index = nextSymb(line, index, '<')) != -1){
      for(index++, j = 0; line[index] != '>'; index++, j++) transition[j] = line[index];
      transition[j] = '\0';
      aux.push_back(string(transition));
    }
    transitionsMap[make_pair(tape, stack)] = aux;
  }
}

void build_map_terms(map<pc, vs> &transitionsMap, map<char, int> &map_terms, vc &terms_name, int &terms_count) {
  for(map<pc,vs>::const_iterator it = transitionsMap.begin(); it != transitionsMap.end(); ++it) {
    if (map_terms.find(it->first.first) == map_terms.end()) {
      map_terms[it->first.first] = terms_count++;
      terms_name.push_back(it->first.first);
    }
  }
}

void calculate_word_terms(vi &word_terms, map<char, int> &map_terms, int &terms_count, char word[]) {
  int i;
  for (i = 0; i < (int)strlen(word); i++) {
    word_terms[map_terms[word[i]]]++;
  }
}

void backtracking(vi &word_terms, map<char, int> &map_terms, int &terms_count, char word[], stack<char> astack, int &accepted, vi stack_terms, map<pc, vs> &transitionsMap, char wtp[], int word_remove, vc &terms_name, int level) {
  char word_local[MAX], aux;
  int i, j, k, flag;
  strcpy(word_local, word);
  if (accepted) return;
  astack.pop();
  for (i = (int)strlen(wtp) - 1; i >= 0; i--) {
    astack.push(wtp[i]);
  }
  if (word_remove) {
    for (i = 0; i < (int)strlen(word_local); i++) {
      word_local[i] = word_local[i+1];
    }
  }
  if (astack.empty() && strlen(word_local) > 0) return;
  if (astack.empty() && strlen(word_local) == 0) {
    accepted = 1;
    return;
  }
  printf("Nivel da arvore de recursao: %d\n", level);
  printf("Empilhando: %s\n", wtp);
  printf("Topo da pilha: %c\n", astack.top());
  printf("Fita de entrada: %s\n", word_local);
  printf("-------------------------------------------\n");
  for(map<pc,vs>::const_iterator it = transitionsMap.begin(); it != transitionsMap.end(); ++it) {
    if (it->first.second == astack.top() && (it->first.first == word_local[0] || it->first.first == '#')) {
      for (i = 0; i < (int)it->second.size(); i++) {
        vi stack_mod(terms_count, 0);
        string::iterator its;
        string saux = it->second[i];
        for (k = 0, its = saux.begin(); its != saux.end(); ++its) {
          aux = *its;
          if (map_terms.find(aux) != map_terms.end() && aux != '#') {
            stack_mod[map_terms[aux]]++;
          }
            wtp[k++] = aux;
        }
        wtp[k] = '\0';
        if (!strcmp(wtp, "#")) wtp[0] = '\0';
        for (flag = 1, j = 0; j < terms_count; j++) {
          stack_mod[j] += stack_terms[j];
          flag &= stack_mod[j] <= word_terms[j];
        }
        if (!flag) continue;
        backtracking(word_terms, map_terms, terms_count, word_local, astack, accepted, stack_mod, transitionsMap, wtp, it->first.first == '#' ? 0 : 1, terms_name, level + 1);
        //  printf("%s\n", (it->second[i]).c_str());
      }
      break;
    }
  }
}
