#include "gramatica.h"

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/input.txt", "r"))) {
    printf("Erro ao abrir o arquivo!");
    return 0;
  }
  mapearGramatica(entrada);
  construirAfndGramatica(entrada);
  return 0;
}

