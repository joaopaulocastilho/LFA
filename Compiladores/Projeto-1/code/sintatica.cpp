#include "sintatica.h"

int qtd_simbolos = 0;
map <string, int> simbolo_reconhecedor;
vector <reducao_t>tabela_reducoes;
vvav tabela_parsing;
vp pilha_reconhecimento;

void mapeiaSimbolosGLC(void) {
  int i, id_simbolo;
  char linha[TAM_LINHA], nome_simbolo[TAM_SIMB];
  FILE *simbolos;
  if (!(simbolos = fopen("./goldparser/simbolos.txt", "r"))) {
    printf("Erro ao abrir o arquivo dos simbolos!");
    return;
  }
  while (fgets(linha, TAM_LINHA, simbolos)) {
    //printf("%s", linha);
    i = indProxChar(linha, 0, '"');
    i = pegaCampo(linha, nome_simbolo, i + 1, '"');
    id_simbolo = atoi(nome_simbolo);
    i = indProxChar(linha, i + 1, '"');
    i = pegaCampo(linha, nome_simbolo, i + 1, '"');
    simbolo_reconhecedor[string(nome_simbolo)] = id_simbolo;
    qtd_simbolos++;
  }
  fclose(simbolos);
}

void constroiTabelaReducoes(void) {
  int i;
  char linha[TAM_LINHA], nome_reducao[TAM_REDUCAO];
  reducao_t nova_reducao;
  FILE *reducao;
  if (!(reducao = fopen("./goldparser/reducoes.txt", "r"))) {
    printf("Erro ao abrir o arquivo de Reducoes!");
    return;
  }
  while (fgets(linha, TAM_LINHA, reducao)) {
    //printf("%s", linha);
    i = indProxChar(linha, 0, '"');
    i = indProxChar(linha, i + 1, '"');
    i = indProxChar(linha, i + 1, '"');
    i = pegaCampo(linha, nome_reducao, i + 1, '"');
    nova_reducao.empilha = atoi(nome_reducao);
    i = indProxChar(linha, i + 1, '"');
    i = pegaCampo(linha, nome_reducao, i + 1, '"');
    nova_reducao.reduz = atoi(nome_reducao);
    nova_reducao.reduz = nova_reducao.reduz << 1;
    tabela_reducoes.push_back(nova_reducao);
  }
  fclose(reducao);
}

void constroiTabelaParsing(void) {
  int i, j, qtd_acoes, ind_simb, acao, valor;
  char linha[TAM_LINHA], nome_qtd_acoes[TAM_QTD_ACOES], nome_simbolo[TAM_SIMB],
    nome_acao[TAM_SIMB], nome_valor[TAM_SIMB];
  FILE *parsing;
  if (!(parsing = fopen("./goldparser/LALR.txt", "r"))) {
    printf("Erro ao abrir o arquivo da Tabela de Parsing!");
    return;
  }
  while (fgets(linha, TAM_LINHA, parsing)) {
    vav linha_tabela_parsing(qtd_simbolos, acao_valor_t(-1, -1));
    i = indProxChar(linha, 0, '"');
    i = indProxChar(linha, i + 1, '"');
    i = indProxChar(linha, i + 1, '"');
    i = pegaCampo(linha, nome_qtd_acoes, i + 1, '"');
    qtd_acoes = atoi(nome_qtd_acoes);
    for (j = 0; j < qtd_acoes; j++) {
      if (!fgets(linha, TAM_LINHA, parsing)) printf("Não leu!\n");
      i = indProxChar(linha, 0, '"');
      i = pegaCampo(linha, nome_simbolo, i + 1, '"');
      ind_simb = atoi(nome_simbolo);
      i = indProxChar(linha, i + 1, '"');
      i = pegaCampo(linha, nome_acao, i + 1, '"');
      acao = atoi(nome_acao);
      i = indProxChar(linha, i + 1, '"');
      i = pegaCampo(linha, nome_valor, i + 1, '"');
      valor = atoi(nome_valor);
      linha_tabela_parsing[ind_simb] = acao_valor_t(acao, valor);
      //printf("%d: %d, %d\n", ind_simb, acao, valor);
    }
    tabela_parsing.push_back(linha_tabela_parsing);
    if (!fgets(linha, TAM_LINHA, parsing)) printf("Não leu!\n");;
  }
  fclose(parsing);
}

void imprimeTabelaParsing(void) {
  int i, j;
  for (i = 0; i < (int)tabela_parsing.size(); i++) {
    printf("%d: ", i);
    for (j = 0; j < (int)tabela_parsing[i].size(); j++) {
      if (tabela_parsing[i][j].valor != -1)
        printf("%d: %d %d | ", j, tabela_parsing[i][j].acao, tabela_parsing[i][j].valor);
    }
    printf("\n");
  }
}

void carregaFita(void) {
  int i;
  linguicona_t eof;
  for (i = 0; i < (int)tabela_simbolos.linguicona.size(); i++)
    if (tabela_simbolos.linguicona[i].rotulo == IDENTIFICADOR)
      tabela_simbolos.linguicona[i].novo_reconhecedor =
        simbolo_reconhecedor["id"];
    else if (tabela_simbolos.linguicona[i].rotulo == NUMERO)
      tabela_simbolos.linguicona[i].novo_reconhecedor =
        simbolo_reconhecedor["num"];
    else tabela_simbolos.linguicona[i].novo_reconhecedor =
           simbolo_reconhecedor[tabela_simbolos.linguicona[i].nome];
  eof.novo_reconhecedor = 0;
  tabela_simbolos.linguicona.push_back(eof);
}

void imprimeFita(void) {
  int i;
  for (i = 0; i < (int)tabela_simbolos.linguicona.size(); i++)
    printf("%d ", tabela_simbolos.linguicona[i].novo_reconhecedor);
  printf("\n");
}

void analiseSintatica(void) {
  int reconhece = 0;
  mapeiaSimbolosGLC();
  constroiTabelaReducoes();
  constroiTabelaParsing();
  carregaFita();
  //imprimeTabelaParsing();
  //imprimeFita();
  pilha_reconhecimento.push_back(pilha_t(0, ESTADO_PILHA));
  reconhece = reconhecimentoSintatico();
  printf("%s\n", reconhece ? "RECONHECEU!!!!!!" : "Nao foi dessa vez, campeao");
}

int reconhecimentoSintatico(){
  int i, simbolo_atual, estado_atual, valor_atual, ponteiro_fita = 0;
  while(1){
    //Estado no topo da pilha
    //printf("Topo da Pilha: %d %d\n", pilha_reconhecimento[topo(pilha_reconhecimento)].id,
    //     pilha_reconhecimento[topo(pilha_reconhecimento)].tipo);
    if(pilha_reconhecimento[topo(pilha_reconhecimento)].tipo == ESTADO_PILHA){
      estado_atual = pilha_reconhecimento[topo(pilha_reconhecimento)].id;
      simbolo_atual = tabela_simbolos.linguicona[ponteiro_fita].novo_reconhecedor;
      //printf("%d\n", simbolo_atual);
    }
    //Simbolo no topo da pilha
    else{
      simbolo_atual = pilha_reconhecimento[topo(pilha_reconhecimento)].id;
      estado_atual = pilha_reconhecimento[topo(pilha_reconhecimento)-1].id;
    }
    valor_atual = tabela_parsing[estado_atual][simbolo_atual].valor;
    //Verificações da tabela de parsing
    if(tabela_parsing[estado_atual][simbolo_atual].acao == EMPILHAMENTO){
      pilha_reconhecimento.push_back(pilha_t(simbolo_atual, SIMBOLO_PILHA));
      pilha_reconhecimento.push_back(pilha_t(valor_atual, ESTADO_PILHA));
      if(topo(pilha_reconhecimento) != 0) ponteiro_fita++;
    }
    else if(tabela_parsing[estado_atual][simbolo_atual].acao == REDUCAO){
      for(i = 0; i < tabela_reducoes[valor_atual].reduz; i++) pop(pilha_reconhecimento);
      pilha_reconhecimento.push_back(pilha_t(tabela_reducoes[valor_atual].empilha, SIMBOLO_PILHA));
    }
    else if(tabela_parsing[estado_atual][simbolo_atual].acao == SALTO){
      pilha_reconhecimento.push_back(pilha_t(valor_atual, ESTADO_PILHA));
    }
    else if(tabela_parsing[estado_atual][simbolo_atual].acao == ACEITO) return 1;
    else return 0;
  }
}
