#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;

#define TAM_LINHA 112345
#define TAM_NOME 112

extern char ultimo_nome[TAM_NOME];

//Função para gerar o nome do próximo estado
void novoNomeEstado(char *state);

//Dado um array, ela pega o nome do prox estado na linha.
int pegaNomeEstado(char linha[], char state[], int i);

//Dado uma linha, ela pega o nome do prox terminal da linha
int pegaNomeTerminal(char linha[], char term[], int i);

//Procura pela primeira ocorrencia de um caractere (alvo) na string
int indProxChar(char linha[], int s, char alvo);

#endif
