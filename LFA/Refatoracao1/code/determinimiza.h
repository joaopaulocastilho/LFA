#ifndef _DETERMINIMIZA_H_
#define _DETERMINIMIZA_H_

#include "automato.h"
#include <algorithm>

using namespace std;

//Minimiza o autômato
void minimiza();

//Determiniza o autômato
void determiniza();

//Checa se uma dada composicao ja foi mapeada na tabela de composicoes
int composicaoExiste(vvi &tabela_composicoes, int i, int j);

//Gera um novo estado para tratar um indeterminismo
int geraEstado(vvi &tabela_composicoes, int i, int j);

#endif
