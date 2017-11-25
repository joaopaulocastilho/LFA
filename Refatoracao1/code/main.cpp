#include <stdio.h>
#include "gramatica.h"

map<string, int>nome_term;
map<string, int>nome_estado;
int qtd_terminais;
int qtd_estados;

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/input.txt", "r"))) {
    printf("Erro ao abrir o arquivo!");
    return 0;
  }
  mapearGramatica(entrada);
  return 0;
}

