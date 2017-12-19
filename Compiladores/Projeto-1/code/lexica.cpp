#include "lexica.h"

tabela_simbolos_t tabela_simbolos;
vs reconhece_reservadas = {"RB", "TB", "WB", "BB", "YA", "EB", "OB", "MB"};

int pegaRotulo(int estado_atual) {
  int i;
  for (i = 0; i < (int)reconhece_reservadas.size(); i++)
    if (reconhece_reservadas[i] == estado_nome[estado_atual]) return PALAVRA_CHAVE;
  if (estado_nome[estado_atual] == "simb") return SIMBOLO;
  if (estado_nome[estado_atual] == "op") return OPERADOR;
  if (estado_nome[estado_atual] == "oprel" || estado_nome[estado_atual] == "poprel")
    return OPERADOR_RELACIONAL;
  if (estado_nome[estado_atual] == "num") return NUMERO;
  return IDENTIFICADOR;
}


void colocaTabelaSimbolos(int estado_atual, char lexema[], int numero_linha) {
  int rotulo_atual = pegaRotulo(estado_atual);
  linguicona_t elemento_linguicona;
  elemento_linguicona.rotulo = rotulo_atual;
  elemento_linguicona.nome = string(lexema);
  elemento_linguicona.linha = numero_linha;
  tabela_simbolos.linguicona.push_back(elemento_linguicona);
  if (rotulo_atual == IDENTIFICADOR)
    tabela_simbolos.identificadores[string(lexema)] = 0;
}

void analiseLexica(FILE *entrada){
  int i, fim_linha, numero_linha, estado_atual = 0, i_lexema;
  char linha[MAX], lexema[MAX];
  for (numero_linha = 1; fgets(linha, MAX, entrada); numero_linha++){
    linha[strlen(linha) - 1] = ' ';
    fim_linha = strlen(linha);
    for(lexema[0] = i_lexema = i = 0; i < fim_linha; i++){
      if(linha[i] == ' '){
        if (strlen(lexema)) {
          if (nome_estado[estado_nome[estado_atual]].final)
            colocaTabelaSimbolos(estado_atual, lexema, numero_linha);
          else if (automato[estado_atual][nome_term[""]].size() == 1) {
            estado_atual = automato[estado_atual][nome_term[""]][0];
            if (nome_estado[estado_nome[estado_atual]].final)
              colocaTabelaSimbolos(estado_atual, lexema, numero_linha);
          } else printf("Token não reconhecido na linha %d: \"%s\"\n", numero_linha, lexema);
        }
        i_lexema = 0; lexema[0] = '\0';
        estado_atual = 0;
        continue;
      }
      if (nome_term.find(string(1, linha[i])) != nome_term.end() &&
          automato[estado_atual][nome_term[string(1, linha[i])]].size() == 1) {
        lexema[i_lexema++] = linha[i];
        if (linha[i + 1] == ' ') lexema[i_lexema] = '\0';
        estado_atual = automato[estado_atual][nome_term[string(1, linha[i])]][0];
        continue;
      }
      printf("Erro na linha %d, coluna %d. Caractere \"%c\" não esperado\n", numero_linha, i, linha[i]);
      i = indProxChar(linha, i, ' ');
      estado_atual = 0;
    }
  }
}

string transcreveRotulo(int rotulo) {
  switch (rotulo) {
  case PALAVRA_CHAVE: return"PALAVRA_CHAVE";
  case SIMBOLO: return"SIMBOLO";
  case OPERADOR: return "OPERADOR";
  case OPERADOR_RELACIONAL: return "OPERADOR_RELACIONAL";
  case IDENTIFICADOR: return "IDENTIFICADOR";
  case NUMERO: return "NUMERO";
  }
  return "OLA";
}


void imprimeTabelaSimbolos(void) {
  int i;
  for (i = 0; i < (int)tabela_simbolos.linguicona.size(); i++)
    printf("%s | %s | %d\n", transcreveRotulo(tabela_simbolos.linguicona[i].rotulo).c_str(),
           tabela_simbolos.linguicona[i].nome.c_str(), tabela_simbolos.linguicona[i].linha);
  printf("\nIdentificadores\n");
  for (map<string, int>::iterator it=tabela_simbolos.identificadores.begin();
       it != tabela_simbolos.identificadores.end(); ++it) {
    printf("%s | %d\n", it->first.c_str(), it->second);
  }
}
