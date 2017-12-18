#ifndef _LEXICA_H_
#define _LEXICA_H_

#include "automato.h"

typedef struct{
  String linguicona;
}tabela_simbolos;

#define MAX 1123

void analiseLexica(FILE *entrada);

#endif
