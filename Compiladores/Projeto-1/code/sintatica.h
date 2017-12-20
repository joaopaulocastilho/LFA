#ifndef _SINTATICA_H_
#define _SINTATICA_H_

#include <stdlib.h>
#include "automato.h"
#include "lexica.h"
#include "utilidades.h"

#define TAM_SIMB 112
#define TAM_REDUCAO 112
#define TAM_QTD_ACOES 112
#define EMPILHAMENTO 1
#define REDUCAO 2
#define SALTO 3
#define ACEITO 4
#define ESTADO_PILHA 0
#define SIMBOLO_PILHA 1

#define topo(x) (x.size()-1)
#define pop(x) (x.erase(x.begin() + x.size()-1))

typedef struct { int empilha, reduz; }reducao_t;

struct acao_valor_t { int acao, valor; acao_valor_t() {}
acao_valor_t(int _acao, int _valor): acao(_acao), valor(_valor) {} };

struct pilha_t { int id, tipo; pilha_t() {}
pilha_t(int _id, int _tipo): id(_id), tipo(_tipo) {} };

typedef vector<acao_valor_t>vav;
typedef vector<vav> vvav;
typedef vector<pilha_t> vp;

void analiseSintatica(void);

int reconhecimentoSintatico(void);

#endif
