#!/bin/bash
g++ code/main.cpp code/grammar.cpp code/utilities.cpp code/determinize.cpp -O2
time ./a.out
