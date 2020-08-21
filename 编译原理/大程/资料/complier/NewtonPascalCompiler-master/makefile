#a.out : tiny.l tiny.y global.h scan.h parse.h util.c main.c 
#	flex tiny.l
#	yacc -d tiny.y
#	gcc util.c lex.yy.c y.tab.c main.c -lfl -o a.out
complier: main.o util.o y.tab.o lex.yy.o symtab.o CodeGenerater.o
	cc main.o util.o y.tab.o lex.yy.o symtab.o CodeGenerater.o -LS -o compiler
util.o: util.c util.h global.h y.tab.h
	cc -c util.c
y.tab.o: y.tab.c y.tab.h util.h global.h lex.yy.c
	cc -c y.tab.c
lex.yy.o: lex.yy.c y.tab.h util.h global.h
	cc -c lex.yy.c
main.o: main.c global.h util.h y.tab.h
	cc -c main.c
CodeGenerater.o: CodeGenerater.c CodeGenerater.h global.h y.tab.h symtab.h
	cc -c CodeGenerater.c
symtab.o: symtab.c symtab.h util.h global.h
	cc -c symtab.c
