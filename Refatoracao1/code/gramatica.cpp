#include "gramatica.h"
#include "utilidades.h"

void mapearGramatica(FILE *entrada) {
  char teste[TAM_LINHA];
  while (fgets(teste, TAM_LINHA, entrada)) {
    printf("%s", teste);
  }
}
