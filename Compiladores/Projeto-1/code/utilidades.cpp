#include "utilidades.h"

char ultimo_nome[TAM_NOME] = "\0";

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

int pegaCampo(char linha[], char campo[], int i, char parada) {
  int j;
  for (j = 0; linha[i] != parada; i++)
    campo[j++] = linha[i];
  campo[j] = '\0';
  return i;
}
