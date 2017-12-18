#include "lexica.h"

vs reconhece_reservadas = {"RB", "TB", "WB", "BB", "YA", "EB", "OB", "MB"};

void analiseLexica(FILE *entrada){
  int i, fim_linha, numero_linha = 1, estado_atual = 0;
  char linha[MAX];

  while(fgets(linha, MAX, entrada)){
    linha[strlen(linha) - 1] = ' ';
    fim_linha = strlen(linha);
    for(i = 0; i < fim_linha; i++){
      if(linha[i] == ' '){ estado_atual = 0; puts(""); continue; }
      else printf("%c", linha[i]);
    }
  }
}
