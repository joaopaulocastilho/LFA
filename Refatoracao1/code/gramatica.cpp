#include "gramatica.h"
#include "utilidades.h"

map<string, int>nome_term;
map<string, nterm_t>nome_estado;
int qtd_estados = 0;
int qtd_terms = 0;
int qtd_novos_estados = 0;
vvvi automato;

void mapearLinha(char linha[]) {
  char nome_novo_estado[TAM_NOME], nome_novo_terminal[TAM_NOME];
  int acabou_linha = 0, i = pegaNomeEstado(linha, nome_novo_estado, 0);
  nome_estado[string(nome_novo_estado)] = nterm_t(qtd_estados++, 0);
  printf("%s | %d\n", nome_novo_estado, nome_estado[string(nome_novo_estado)].id);
  for(i = indProxChar(linha, i, '=') + 1; !acabou_linha; i++){
    i = pegaNomeTerminal(linha, nome_novo_terminal, i);
    if(!strcmp(nome_novo_terminal, "eps"))
       nome_estado[string(nome_novo_estado)].final = 1;
    if(linha[i] != '<' && strcmp(nome_novo_terminal, "eps")) qtd_novos_estados++;
    if(strcmp(nome_novo_terminal, "eps") &&
       nome_term.find(string(nome_novo_terminal)) == nome_term.end())
      nome_term[string(nome_novo_terminal)] = qtd_terms++;
    if((i = indProxChar(linha, i, '|')) == -1) acabou_linha = 1;
  }
}

void mapearGramatica(FILE *entrada) {
  char linha[TAM_LINHA];
  while (fgets(linha, TAM_LINHA, entrada)) {
    if (indProxChar(linha, 0, '<') != -1) mapearLinha(linha);
  }
  mostraTerminais(nome_term);
  mostraEstados(nome_estado);
}

void construirAfndGramatica(FILE *entrada){
  int i, nlinha, acabou_linha, aux_qtd_estados = qtd_estados;
  char linha[TAM_LINHA], terminal_lido[TAM_NOME], estado_lido[TAM_NOME];
  fseek(entrada, 0, SEEK_SET);
  for(nlinha = 0; nlinha < aux_qtd_estados; nlinha++){
    vvi tmp(qtd_terms);
    fgets(linha, TAM_LINHA, entrada);
    for(i = acabou_linha = 0, i = indProxChar(linha, i, '=') + 1; !acabou_linha; i++){
      i = pegaNomeTerminal(linha, terminal_lido, i);
      if(!strcmp(terminal_lido, "eps")){
        if((i = indProxChar(linha, i, '|')) == -1) acabou_linha = 1;
        continue;
      }
      if(linha[i] == '<') i = pegaNomeEstado(linha, estado_lido, i);
      else if(linha[i] == '|' || linha[i] == '\n'){
        geraNomeValido(ultimo_nome);
        strcpy(estado_lido, ultimo_nome);
        nome_estado[string(ultimo_nome)] = nterm_t(qtd_estados++, 1);
      }
      tmp[nome_term[string(terminal_lido)]].push_back(nome_estado[string(estado_lido)].id);
      if((i = indProxChar(linha, i, '|')) == -1) acabou_linha = 1;
    }
    automato.push_back(tmp);
  }
  for(i = 0; i < qtd_novos_estados; i++){
    vvi tmp(qtd_terms);
    automato.push_back(tmp);
  }
}
