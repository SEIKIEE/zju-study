#a.out : tiny.l tiny.y global.h scan.h parse.h util.c main.c 
#	flex tiny.l
#	yacc -d tiny.y
#	gcc util.c lex.yy.c y.tab.c main.c -lfl -o com.exe

complier: main.c symtab.c tiny.tab.c lex.yy.c util.c CodeGenerater.c
	gcc main.c symtab.c tiny.tab.c lex.yy.c util.c CodeGenerater.c -o compiler
tiny.tab.c: tiny.y
	bison -d tiny.y
lex.yy.c: tiny.l
	flex tiny.l
