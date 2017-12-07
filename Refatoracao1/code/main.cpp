#include "automato.h"
#include "determinimiza.h"

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/input7.txt", "r"))) {
    printf("Erro ao abrir o arquivo!");
    return 0;
  }
  mapearGramatica(entrada);
  construirAfndGramatica(entrada);
  imprimeAutomato(automato);
  minimiza();
  imprimeAutomato(automato);
  return 0;
}

