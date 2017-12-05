#include "automato.h"

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/input.txt", "r"))) {
    printf("Erro ao abrir o arquivo!");
    return 0;
  }
  mapearGramatica(entrada);
  construirAfndGramatica(entrada);
  imprimeAutomato(automato);
  return 0;
}

