#ifndef DETERMINIZE_H
#define DETERMINIZE_H

#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include <algorithm>
#include"utilities.h"
using namespace std;

typedef pair<string, bool>psb;
typedef vector<psb>vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

void automaton_determinize(viii &afnd, int &states_cont, int &terms_cont, vpsb &states_name, vs &terms_name, vi &transition_cont, vi &alive, map<string, int> &map_states, map<string, int> &map_terms, char last_state_generated[]);

void transition_determinize(viii &afnd, int i, int j, int &states_cont, map <string, int> &map_states, vpsb &states_name, int &terms_cont, vii &states_dictionary, char last_state_generated[], vi &alive, vs &terms_name);

void remove_unreachable(int states_cont, int terms_cont, viii &afnd, vi &vis, vpsb &states_name, vs &terms_name, map<string, int> &map_states, map<string, int> &map_terms);

#endif
