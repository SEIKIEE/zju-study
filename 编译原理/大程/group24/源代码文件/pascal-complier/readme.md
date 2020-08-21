flex lexical.l

bison -dv grammar.y

gcc -o complier analyze.c grammar.tab.c lex.yy.c main.c quadruple.c symtab.c util.c visual.c