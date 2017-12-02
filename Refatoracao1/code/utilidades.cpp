#include "utilidades.h"

char ultimo_nome[TAM_NOME] = "\0";

void geraNomeValido(char nome[]){
  do{
    novoNomeEstado(nome);
  }while(nome_estado.find(string(ultimo_nome)) != nome_estado.end());
}

void novoNomeEstado(char *state) {
  if (state[0] == '\0') {
    state[0] = 'A';
    state[1] = '\0';
  }
  else if (state[0] == 'Z') {
    state[0] = 'A';
    novoNomeEstado(state + sizeof(char));
  }
  else state[0]++;
}

int indProxChar(char linha[], int s, char alvo) {
  int i;
  for (i = s; linha[i] != alvo; i++) {
    if (i == (int)strlen(linha)) return -1;
  }
  return i;
}

int pegaNomeEstado(char linha[], char state[], int i) {
  int j;
  for (i = indProxChar(linha, i, '<') + 1, j = 0; linha[i] != '>'; i++)
    state[j++] = linha[i];
  state[j] = '\0';
  return i;
}

int pegaNomeTerminal(char linha[], char term[], int i) {
  int j;
  for (j = 0; linha[i] != '<' && linha[i] != '\n' &&
         linha[i] != '|'; i++)
    if (linha[i] != ' ') term[j++] = linha[i];
  term[j] = '\0';
  return i;
}

void mostraTerminais(map<string, int> &nome_term){
  printf("A quantidade de terminais é: %d\n", (int) nome_term.size());
  for (map<string, int>::iterator it = nome_term.begin(); it != nome_term.end(); it++)
    printf("%d: %s\n", it->second, it->first.c_str());
}

void mostraEstados(map<string, nterm_t> &nome_estado){
  printf("A quantidade de estados é: %d\n", (int) nome_estado.size());
  for (map<string, nterm_t>::iterator it = nome_estado.begin(); it != nome_estado.end(); it++)
    printf("%d: %s %s é final\n", it->second.id, it->first.c_str(), it->second.final ? "" : "não");
}

void imprimeAutomato(vvvi &automato){
  int i, j, k;
}
