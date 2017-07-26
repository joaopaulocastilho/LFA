#include <cstdio>
#include <string>
#include <string.h>
#include <utility>
#include <vector>
#include <map>

using namespace std;

#define MAX 1123

typedef pair<char,string> pcs;
typedef vector<string> vs;

void printTransitions(map<pcs,vs> &transitionsMap){
  int i;
  for(map<pcs,vs>::const_iterator it = transitionsMap.begin(); it != transitionsMap.end(); ++it){
    printf("(%c,%s) -> ", it->first.first, (it->first.second).c_str());
    for(i = 0; i < (int)it->second.size(); i++){
      if(i) printf(",");
      printf("(%s)  ", it->second[i].c_str());
    }
    printf("\n");
  }
}

// Search for the first encounter with the received symbol.
int nextSymb(char line[], int pos,char symbol){
  int i;
  for (i = pos; line[i] != symbol; i++) {
    if (i == (int)strlen(line)) return -1;
  }
  return i;
}

void loadTransitions(FILE *inputFile, map<pcs,vs> &transitionsMap){
  char line[MAX];
  char tape, stack[MAX], transition[MAX];
  int j, index;
  fseek(inputFile, 0, SEEK_SET);
  while (fgets(line, MAX, inputFile)) {
    index = nextSymb(line, 0, '<');
    tape = line[++index];
    for(index = nextSymb(line, index, '<')+1, j = 0; line[index] != '>'; index++, j++) stack[j] = line[index];
    stack[j] = '\0';

    vs aux;
    while((index = nextSymb(line, index, '<')) != -1){
      for(index++, j = 0; line[index] != '>'; index++, j++) transition[j] = line[index];
      transition[j] = '\0';
      aux.push_back(string(transition));
    }
    transitionsMap[make_pair(tape, string(stack))] = aux;
  }
}

int main(void){
  //Variables
  map<pcs,vs> transitionsMap;

  FILE *inputFile;
  inputFile = fopen("input/input1.txt", "r");
  loadTransitions(inputFile, transitionsMap);
  printTransitions(transitionsMap);
  return 0;
}

//OBISERVAZOIS
// # = epslon
