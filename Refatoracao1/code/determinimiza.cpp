#include "determinimiza.h"

int dfs(int u) {
  int i, j;
  if (valido[u] != -1) return valido[u];
  valido[u] = 0;
  for (i = 0; i < (int)automato[u].size(); i++)
    for (j = 0; j < (int)automato[u][i].size(); j++)
      valido[u] |= dfs(automato[u][i][j]);
  return valido[u] = valido[u] || nome_estado[string(estado_nome[u])].final;
}

void minimiza() {
  int i;
  valido.resize(qtd_estados, -1);
  valido[0] = dfs(0);
  for (i = 0; i < (int)valido.size(); i++)
    printf("%d ", valido[i]);
  printf("\n");
}
