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
        automato[i][j].erase(automato[i][j].begin() + k);
      }
      tem_transicao[j] |= !automato[i][j].empty();
    }
  }
}

void minimiza() {
  int i;
  for(i = 0; i < (int) valido.size(); i++) valido[i] = -1;
  valido[0] = dfs(0);
  limpaAutomato();
  for (i = 0; i < (int)valido.size(); i++)
    printf("%d ", valido[i]);
  printf("\n");
}
