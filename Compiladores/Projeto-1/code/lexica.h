#ifndef _LEXICA_H_
#define _LEXICA_H_

#include "automato.h"

#define MAX 1123
#define PALAVRA_CHAVE 1
#define SIMBOLO 2
#define OPERADOR 3
#define OPERADOR_RELACIONAL 4
#define IDENTIFICADOR 5
#define NUMERO 6

typedef struct {
  int rotulo;
  string nome;
  int linha;
  int estado_reconhecedor;
  int novo_reconhecedor;
} linguicona_t;

typedef struct {
  vector<linguicona_t>linguicona;
  map<string, int>identificadores;
} tabela_simbolos_t;

extern tabela_simbolos_t tabela_simbolos;
extern int reconheceuLexica;

void analiseLexica(FILE *entrada);

void imprimeTabelaSimbolos(void);

void imprimeArquivoTabelaSimbolos(void);

string transcreveRotulo(int rotulo);

#endif
