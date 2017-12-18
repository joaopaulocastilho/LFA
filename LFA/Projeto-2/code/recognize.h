#ifndef RECOGNIZE_H
#define RECOGNIZE_H

#include <cstdio>
#include <string>
#include <string.h>
#include <utility>
#include <vector>
#include <map>
#include <stack>
using namespace std;

#define MAX 1123

typedef pair<char,char> pc;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<char> vc;

void loadTransitions(FILE *inputFile, map<pc,vs> &transitionsMap, char &first_stack);

void printTransitions(map<pc,vs> &transitionsMap);

void build_map_terms(map<pc, vs> &transitionsMap, map<char, int> &map_terms, vc &terms_name, int &terms_count);

void calculate_word_terms(vi &word_terms, map<char, int> &map_terms, int &terms_count, char word[]);

void backtracking(vi &word_terms, map<char, int> &map_terms, int &terms_count, char word[], stack<char> astack, int &accepted, vi stack_terms, map<pc, vs> &transitionsMap, char wtp[], int word_remove, vc &terms_name, int level);


#endif
