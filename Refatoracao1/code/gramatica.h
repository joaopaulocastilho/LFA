#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <map>
#include <vector>
#include <utility>

using namespace std;

#define TAM_LINHA 112345

//Essa função recebe um arquivo de entrada e conta a quantidade de terminais e não terminais e os coloca no map.
void mapearGramatica(FILE *entrada);

#endif
