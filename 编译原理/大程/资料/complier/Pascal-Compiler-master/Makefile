all: y.tab.out test_lex

y.tab.out: 	lex.yy.o 	y.tab.o
	gcc -o y.tab.out lex.yy.o y.tab.o

lex.yy.c: 	pascal.l 
	flex pascal.l

lex.yy.o: 	lex.yy.c 	y.tab
	gcc -c lex.yy.c

y.tab: 		pascal.y
	yacc -dvt pascal.y

y.tab.o: 	y.tab 		lex.yy.h
	gcc -c y.tab.c

clean_o:
	rm -rf *.o

clean:
	rm -rf *.o y.tab.c lex.yy.c *~ *.output y.tab.h *.out

test_lex: lex.yy.o tools/test_lex.c
	gcc -c tools/test_lex.c
	gcc test_lex.o lex.yy.o -o tools/lex.yy.out

test:
	tools/lex.yy.out < sample/test.pas | tools/token.py ./y.tab.h
