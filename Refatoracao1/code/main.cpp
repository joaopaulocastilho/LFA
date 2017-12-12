#include "automato.h"
#include "determinimiza.h"

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/input9.txt", "r"))) {
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
  mapearTokens(entrada);
  imprimeAutomato(automato);
  return 0;
}

