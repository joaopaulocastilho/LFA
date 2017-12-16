#include "automato.h"

map<string, int>nome_term;
map<string, nterm_t>nome_estado;
int qtd_estados = 0;
int qtd_terms = 0;
int qtd_novos_estados = 0;
vvvi automato;
vs term_nome;
vs estado_nome;
vi valido;
vi tem_transicao;
int posicao_tokens = -1;

void mapearLinha(char linha[]) {
  char nome_novo_estado[TAM_NOME], nome_novo_terminal[TAM_NOME];
  int acabou_linha = 0, i = pegaNomeEstado(linha, nome_novo_estado, 0);
  nome_estado[string(nome_novo_estado)] = nterm_t(qtd_estados++, 0);
  estado_nome.push_back(string(nome_novo_estado));
  printf("%s | %d\n", nome_novo_estado, nome_estado[string(nome_novo_estado)].id);
  for(i = indProxChar(linha, i, '=') + 1; !acabou_linha; i++){
    i = pegaNomeTerminal(linha, nome_novo_terminal, i);
    if(!strcmp(nome_novo_terminal, "eps"))
       nome_estado[string(nome_novo_estado)].final = 1;
    if(linha[i] != '<' && strcmp(nome_novo_terminal, "eps")) qtd_novos_estados++;
    if(strcmp(nome_novo_terminal, "eps") &&
       nome_term.find(string(nome_novo_terminal)) == nome_term.end()){
      nome_term[string(nome_novo_terminal)] = qtd_terms++;
      term_nome.push_back(string(nome_novo_terminal));
    }
    if((i = indProxChar(linha, i, '|')) == -1) acabou_linha = 1;
  }
}

void mapearGramatica(FILE *entrada) {
  char linha[TAM_LINHA];
  while (fgets(linha, TAM_LINHA, entrada)) {
    if (indProxChar(linha, 0, '<') != -1) mapearLinha(linha);
    else { posicao_tokens = ftell(entrada) - strlen(linha); break; }
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
        do{
          novoNomeEstado(ultimo_nome);
        } while(nome_estado.find(string(ultimo_nome)) != nome_estado.end());
        strcpy(estado_lido, ultimo_nome);
        nome_estado[string(ultimo_nome)] = nterm_t(qtd_estados++, 1);
        estado_nome.push_back(string(ultimo_nome));
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
  valido.resize(qtd_estados, 1);
  tem_transicao.resize(qtd_terms, 1);
}

//Funções de impressão

void imprimeAutomato(vvvi &automato){
  int i, j, k;
  for(i = 0; i < (int)term_nome.size(); i++)
    if(tem_transicao[i]) printf("   %s|",  term_nome[i] == "" ? "eps" : term_nome[i].c_str());
  printf("\n");
  for(i = 0; i < (int)estado_nome.size(); i++){
    if(valido[i] != 1) continue;
    printf("%s%s:", nome_estado[estado_nome[i]].final ? "*" : " ", estado_nome[i].c_str());
    for(j = 0; j < (int)automato[i].size(); j++){
      if(!tem_transicao[j]) continue;
      printf("[");
      for(k = 0; k < (int)automato[i][j].size(); k++){
        if(k) printf(" ");
        printf("%s", estado_nome[automato[i][j][k]].c_str());
      }
      printf("]");
    }
    printf("\n");
  }
}

void imprimeArquivo(void) {
  int i, j, k;
  FILE *saida;
  saida = fopen("output/output.csv", "w");
  fwrite(",", sizeof(char), 1, saida);
  for(i = 0; i < (int)term_nome.size(); i++)
    if(tem_transicao[i])
      fprintf(saida, "%s,",  term_nome[i] == "" ? "eps" : term_nome[i].c_str());
  fprintf(saida, "\n");
  for(i = 0; i < (int)estado_nome.size(); i++){
    if(valido[i] != 1) continue;
    fprintf(saida, "%s%s,", nome_estado[estado_nome[i]].final ? "*" : " ", estado_nome[i].c_str());
    for(j = 0; j < (int)automato[i].size(); j++){
      if(!tem_transicao[j]) continue;
      //fprintf(saida, "[");
      for(k = 0; k < (int)automato[i][j].size(); k++){
        //if(k) fprintf(saida, " ");
        fprintf(saida, "%s", estado_nome[automato[i][j][k]].c_str());
      }
      fprintf(saida, ",");
    }
    fprintf(saida, "\n");
  }
}

void mostraTerminais(map<string, int> &nome_term){
  printf("A quantidade de terminais é: %d\n", (int) nome_term.size());
  for (map<string, int>::iterator it = nome_term.begin(); it != nome_term.end(); it++)
    printf("%d: %s\n", it->second, it->first.c_str());
}

void mostraEstados(map<string, nterm_t> &nome_estado){
  printf("A quantidade de estados é: %d\n", (int) nome_estado.size());
  for (map<string, nterm_t>::iterator it = nome_estado.begin(); it != nome_estado.end(); it++)
    printf("%d: %s %s é final\n", it->second.id, it->first.c_str(), it->second.final ? "" : "não");
}

void mapearTokens(FILE *entrada) {
  int estado_atual, terminal_atual, i, j;
  char linha[TAM_LINHA];
  vvi aux;
  if (posicao_tokens == -1) return;
  if (qtd_estados == 0) {
    nome_estado["S"] = nterm_t(qtd_estados++, 0);
    estado_nome.push_back("S");
    automato.push_back(aux);
    valido.resize(qtd_estados, 1);
  }
  fseek(entrada, posicao_tokens, SEEK_SET);
  while (fgets(linha, TAM_LINHA, entrada)) {
    estado_atual = 0;
    for (i = 0; linha[i] != '\n'; i++) {
      string terminal_lido(1, linha[i]);
      if (nome_term.find(terminal_lido) == nome_term.end()) {
        nome_term[terminal_lido] = qtd_terms++;
        term_nome.push_back(terminal_lido);
        for (j = 0; j < (int)automato.size(); j++) automato[j].resize(qtd_terms);
        tem_transicao.resize(qtd_terms, 1);
      }
      if (estado_atual != 0) {
        do{
          novoNomeEstado(ultimo_nome);
        } while(nome_estado.find(string(ultimo_nome)) != nome_estado.end());
        nome_estado[string(ultimo_nome)] = nterm_t(qtd_estados++, 0);
        estado_nome.push_back(string(ultimo_nome));
        valido.resize(qtd_estados, 1);
        automato.push_back(aux);
        automato[estado_atual].resize(qtd_terms);
      }
      terminal_atual = nome_term[terminal_lido];
      automato[estado_atual][terminal_atual].push_back(qtd_estados);
      estado_atual = qtd_estados;
    }
    do{
      novoNomeEstado(ultimo_nome);
    } while(nome_estado.find(string(ultimo_nome)) != nome_estado.end());
    nome_estado[string(ultimo_nome)] = nterm_t(qtd_estados++, 1);
    estado_nome.push_back(string(ultimo_nome));
    valido.resize(qtd_estados, 1);
    automato.push_back(aux);
    automato[estado_atual].resize(qtd_terms);
    //printf("%s", linha);
  }
}
