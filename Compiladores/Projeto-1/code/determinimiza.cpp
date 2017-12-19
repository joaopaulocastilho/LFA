#include "determinimiza.h"

int dfs(int u) {
  int i, j;
  //if (valido[u] != -1) return valido[u];
  valido[u] = 0;
  if(nome_estado[string(estado_nome[u])].final) valido[u] = 1;
  for (i = 0; i < (int)automato[u].size(); i++)
    for (j = 0; j < (int)automato[u][i].size(); j++)
      if(valido[automato[u][i][j]] == -1) valido[u] |= dfs(automato[u][i][j]);
      else valido[u] |= valido[automato[u][i][j]];
  return valido[u] = valido[u] || nome_estado[string(estado_nome[u])].final;
}

void limpaAutomato(){
  int i, j, k;
  for(i = 0; i < (int) tem_transicao.size(); i++) tem_transicao[i] = 0;
  for(i = 0; i < (int) automato.size(); i++){
    if(valido[i] != 1) continue;
    for(j = 0; j < (int) automato[i].size(); j++){
      for(k = 0; k < (int) automato[i][j].size(); k++){
        if(valido[automato[i][j][k]] == 1) continue;
        automato[i][j].erase(automato[i][j].begin() + k--);
      }
      tem_transicao[j] |= !automato[i][j].empty();
    }
  }
}

void minimiza() {
  int i;
  if (!qtd_estados) return;
  for(i = 0; i < (int) valido.size(); i++) valido[i] = -1;
  valido[0] = dfs(0);
  limpaAutomato();
  //  for (i = 0; i < (int)valido.size(); i++)
  // printf("%d ", valido[i]);
  //printf("\n");
}

void determiniza(){
  int i, j, k;
  vvi tabela_composicoes(qtd_estados);
  for(i = 0; i < qtd_estados; i++) tabela_composicoes[i].push_back(i);
  for(i = 0; i < qtd_estados; i++){
    if(valido[i] != 1) continue;
    for(j = 0; j < qtd_terms; j++){
      if(automato[i][j].size() < 2) continue;
      sort(automato[i][j].begin(), automato[i][j].end());
      if((k = composicaoExiste(tabela_composicoes, i, j)) == -1){
        k = geraEstado(tabela_composicoes, i, j);
        // printf("%s %s %s\n", estado_nome[k].c_str(), estado_nome[i].c_str(), term_nome[j].c_str());
      }
      automato[i][j].clear();
      automato[i][j].push_back(k);
    }
  }
  //  for(i = 0; i < 
}

int composicaoExiste(vvi &tabela_composicoes, int i, int j){
  int encontrado, k, l;
  for(encontrado = k = 0; k < (int)tabela_composicoes.size(); k++){
    if(tabela_composicoes[k].size() != automato[i][j].size()) continue;
    for(encontrado = 1, l = 0; l < (int)tabela_composicoes[k].size(); l++)
      encontrado &= tabela_composicoes[k][l] == automato[i][j][l];
    if(encontrado) break;
  }
  return encontrado ? k : -1;
}

int geraEstado(vvi &tabela_composicoes, int i, int j){
  int k, l, m, n, novo_final = 0, estado_atual, composicao_atual, adada;
  vvi novo_estado(qtd_terms);
  vi nova_composicao;
  for(k = 0; k < (int)automato[i][j].size(); k++){
    nova_composicao.push_back(automato[i][j][k]);
    novo_final |= nome_estado[estado_nome[automato[i][j][k]]].final;
  }
  tabela_composicoes.push_back(nova_composicao);
  do{
    novoNomeEstado(ultimo_nome);
  } while(nome_estado.find(string(ultimo_nome)) != nome_estado.end());
  estado_nome.push_back(string(ultimo_nome));
  nome_estado[string(ultimo_nome)] = nterm_t(qtd_estados, novo_final);
  estado_atual = qtd_estados++;
  valido.push_back(1);
  automato.push_back(novo_estado);
  for(k = 0; k < qtd_terms; k++){
    for(l = 0; l < (int)tabela_composicoes[estado_atual].size(); l++){
      composicao_atual = tabela_composicoes[estado_atual][l];
      for(m = 0; m < (int)automato[composicao_atual][k].size(); m++){
        adada = automato[composicao_atual][k][m];
        for(n = 0; n < (int)tabela_composicoes[adada].size(); n++){
          if(find(automato[estado_atual][k].begin(), automato[estado_atual][k].end(),
                  tabela_composicoes[adada][n]) == automato[estado_atual][k].end())
            automato[estado_atual][k].push_back(tabela_composicoes[adada][n]);
        }
      }
    }
    if(automato[estado_atual][k].size() > 1){
      sort(automato[estado_atual][k].begin(), automato[estado_atual][k].end());
      if(composicaoExiste(tabela_composicoes, estado_atual, k) == -1)
        geraEstado(tabela_composicoes, estado_atual, k);
    }
  }
  return estado_atual;
}
