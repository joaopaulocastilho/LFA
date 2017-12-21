#include "automato.h"
#include "determinimiza.h"
#include "lexica.h"
#include "sintatica.h"

int main(void) {
  FILE *entrada;
  if (!(entrada = fopen("input/grammar.txt", "r"))) {
    printf("Erro ao abrir o arquivo da gramatica!");
    return 0;
  }
  mapearGramatica(entrada);
  construirAfndGramatica(entrada);
  //puts("AUTOMATO CONSTRUIDO");
  //imprimeAutomato(automato);
  minimiza();
  //puts("AUTOMATO MINIMIZADO");
  //imprimeAutomato(automato);
  determiniza();
  //puts("AUTOMATO DETERMINIZADO");
  //imprimeAutomato(automato);
  minimiza();
  //puts("AUTOMATO MINIMIZADO E DETERMINIZADO");
  //imprimeAutomato(automato);
  //puts("COLOCANDO OS TOKENS NA BRINCADEIRA");
  mapearTokens(entrada);
  //imprimeAutomato(automato);
  //puts("DETERMINIZANDO COM TOKENS");
  determiniza();
  //imprimeAutomato(automato);
  //puts("MINIMIZAÇÃO FINAL");
  minimiza();
  //imprimeAutomato(automato);
  imprimeArquivo();
  if (!(entrada = fopen("input/code.txt", "r"))) {
    printf("Erro ao abrir o arquivo do codigo!");
    return 0;
  }
  analiseLexica(entrada);
  //imprimeTabelaSimbolos();
  imprimeArquivoTabelaSimbolos();
  if (reconheceuLexica) {
    printf("Reconheceu na Lexica\n");
    analiseSintatica();
  }
  return 0;
}

