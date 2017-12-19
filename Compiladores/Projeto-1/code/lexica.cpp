#include "lexica.h"

tabela_simbolos_t tabela_simbolos;
vs reconhece_reservadas = {"RB", "TB", "WB", "BB", "YA", "EB", "OB", "MB"};

void analiseLexica(FILE *entrada){
  int i, fim_linha, numero_linha = 1, estado_atual = 0, i_lexoma, rotulo_atual;
  char linha[MAX], lexema[MAX];
  while(fgets(linha, MAX, entrada)){
    linha[strlen(linha) - 1] = ' ';
    fim_linha = strlen(linha);
    for(lexema[0] = i_lexoma = i = 0; i < fim_linha; i++){
      if(linha[i] == ' '){
        if (strlen(lexema)) {
          if (nome_estado[estado_nome[estado_atual]].final) {
            rotulo_atual = pegaRotulo(estado_atual);
            linguicona_t elemento_linguicona;
            elemento_linguicona.rotulo = rotulo_atual;
            elemento_linguicona.nome = string(lexema);
            tabela_simbolos.linguicona.push_back(elemento_linguicona);
            if (rotulo_atual == IDENTIFICADOR) {
              identificador_t id_atual;
              id_atual.nome = 

            }
          } else {
            // ERROU!
          }
        }
        i_lexoma = 0; lexema[0] = '\0';
        estado_atual = 0;
        continue;
      }
      if (automato[estado_atual][nome_term[string(linha[i])]].size() == 1) {
        lexema[i_lexoma++] = linha[i];
        estado_atual = automato[estado_atual][nome_term[string(linha[i])]][0];
        continue;
      }
      printf("Erro na linha %d, coluna %d. Caractere %c não esperado\n", numero_linha, i, linha[i]);
      i = indProxChar(linha, i, ' ');
    }
  }
}
