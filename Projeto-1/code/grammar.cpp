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

void grammar_treatment(char linha[], int &states_cont, vector < pair<int, string> > &states_name) {
  int i, j, flag = 1, qtty_term = 0;
  char state[MAX], term[MAX], n_term[MAX];
  map<string, int> terms;
  //passar o nome do estado (que está a esquerda) para o vetor auxiliar "state". "i" começa depois da primeira ocorrencia do caractere '<' na linha.
  for (i = next_simb(linha, 0, '<') + 1, j = 0; linha[i] != '>'; i++) state[j++] = linha[i];
  state[j] = '\0';
  //printf("%s\n", state); //DEBUG
  //coloca o estado no vector de estados (states_name)
  states_name.push_back(make_pair(states_cont++, string(state)));
  //Como a gramática é regular, vamos pular o "::=" e parar no primeiro símbolo depois do '='
  i = next_simb(linha, i, '=') + 1;
  //Tem que mapear todos os símbolos terminais até o \n
  while (flag) {
    for (j = 0; linha[i] != '<' && linha[i] != '\n' && linha[i] != '|'; i++) {
      if (linha[i] != ' ') term[j++] = linha[i];
    }
    term[j] = '\0';
    //Verificar se o terminal já está no map, se não estiver, insere.
    if (terms.find(string(term)) == terms.end()) {
      terms[string(term)] = qtty_term++;
    }
    //Se linha[i] == '<' quer dizer que tem um não terminal depois do terminal.
    if (linha[i] == '<') {
      //Pegando o não terminal daquela produção.
      for (i += 1, j = 0; linha[i] != '>'; i++) {
        n_term[j++] = linha[i];
      }
      n_term[j] = '\0';
    }
    //Quer dizer que não terá mais produções naquela regra da gramática
    if ((i = next_simb(linha, i, '|')) == -1) flag = 0;
    i++;
    //printf("Terminal: %s\n", term); //DEBUG
    //printf("Nao terminal: %s\n", n_term); //DEBUG
  }
}
