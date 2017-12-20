#!/bin/bash
g++ code/main.cpp code/automato.cpp code/determinimiza.cpp code/lexica.cpp code/sintatica.cpp code/utilidades.cpp -Wall -O2
time ./a.out
