%{
	#include<stdio.h>
	struct Type{
		int iVal;
		double dVal;
		int type;
	};
	#define YYSTYPE struct Type
	#include "p2.tab.h"
	extern int TYPE;
	char* a;
%}
%%
[ \t] {/*skip*/}
[0-9]+ {yylval.type = 0; yylval.iVal = atoi(yytext); return INT;}
[0-9]+\.[0-9]+ {TYPE = 1; yylval.type = 1; yylval.dVal = atof(yytext); return DOUBLE;}
[\n\.\+\-\*\/()^] {return yytext[0];}
%%
