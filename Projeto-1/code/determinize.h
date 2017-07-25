#ifndef DETERMINIZE_H
#define DETERMINIZE_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include <algorithm>
#include"generate_state.h"
using namespace std;

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

void automaton_determinize(viii &afnd, int &states_cont, int &terms_cont, vpsb &states_name, vs &terms_name, vi &transition_cont, vi &alive, map<string, int> &map_states, map<string, int> &map_terms, char last_state_generated[]);


#endif
