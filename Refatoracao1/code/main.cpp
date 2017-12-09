#include "automato.h"
#include "determinimiza.h"

int main(void) {
  FILE *entrada;
<<<<<<< HEAD
  if (!(entrada = fopen("input/input8.txt", "r"))) {
=======
  if (!(entrada = fopen("input/input.txt", "r"))) {
>>>>>>> d9e01d05fa02a95c8f3ed659e40916666240bec9
    printf("Erro ao abrir o arquivo!");
    return 0;
  }
  mapearGramatica(entrada);
  construirAfndGramatica(entrada);
  puts("AUTOMATO CONSTRUIDO");
  imprimeAutomato(automato);
  minimiza();
  puts("AUTOMATO MINIMIZADO");
  imprimeAutomato(automato);
  determiniza();
  puts("AUTOMATO DETERMINIZADO");
  imprimeAutomato(automato);
  minimiza();
  puts("AUTOMATO MINIMIZADO E DETERMINIZADO");
  imprimeAutomato(automato);
  return 0;
}

