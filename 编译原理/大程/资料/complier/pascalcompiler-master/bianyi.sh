#!/bin/bash
g++ declare.cpp lex.yy.c main.cpp symbolTable.cpp util.cpp y.tab.c -std=c++0x -o2 -o sb.o  2>res  
