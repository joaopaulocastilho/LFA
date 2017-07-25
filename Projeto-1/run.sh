#!/bin/bash
g++ code/main.cpp code/grammar.cpp code/generate_state.cpp code/determinize.cpp -O2
time ./a.out
