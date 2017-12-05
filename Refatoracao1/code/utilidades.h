#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include "automato.h"

using namespace std;

extern char ultimo_nome[TAM_NOME];

//Gera um nome de estado válido (que ainda não exista)
void geraNomeValido(char nome[]);

//Função para gerar o nome do próximo estado
void novoNomeEstado(char *state);

//Dado um array, ela pega o nome do prox estado na linha.
int pegaNomeEstado(char linha[], char state[], int i);

//Dado uma linha, ela pega o nome do prox terminal da linha
int pegaNomeTerminal(char linha[], char term[], int i);

//Procura pela primeira ocorrencia de um caractere (alvo) na string
int indProxChar(char linha[], int s, char alvo);

//Função utilizada para imprimir o map dos terminais, com intuito de debug
void mostraTerminais(map<string, int> &nome_term);

//Função utilizada para imprimir o map dos estados, com intuito de debug
void mostraEstados(map<string, nterm_t> &nome_estado);

#endif
