#!/bin/bash
g++ code/main.cpp code/grammar.cpp code/generate_state.cpp -O2
time ./a.out
