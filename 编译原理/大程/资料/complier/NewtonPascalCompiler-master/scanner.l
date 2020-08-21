
%option yylineno nodedefault

%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "parser.hpp"

extern void yyerror(const char* s, ...);

%}

%x COMMENT

%%




-?[0-9]+    {   
				 
        }


-?[0-9]+"."[0-9]* |
-?"."[0-9]+     |   
-?[0-9]+E[-+]?[0-9]+ |  
-?[0-9]+"."[0-9]*E[-+]?[0-9]+   |       
-?"."[0-9]+E[-+]?[0-9]+         {   
				
        }


'(\\.|''|[^'\n])*'  |
\"(\\.|\"\"|[^"\n])*\"          {   
				  
        }

'(\\.|[^'\n])*$                 {   yyerror("Unterminated string %s", yytext);  }
\"(\\.|[^"\n])*$                 {   yyerror("Unterminated string %s", yytext);  }


[-+&~|^/%()*,.!]               {   return yytext[0];   }


[A-Za-z][A-Za-z0-9_]*   {   
				 
        }

`[^`/\\.\n]+`   {
				
        }

`[^`\n]*$       {  yyerror("Unterminated name %s", yytext);  }

[\n]			{	}
				

[ \t]                 {		}

.                       {  yyerror("mystery character '%c'", *yytext);    }

%%

int yywrap()
{
    return 1;
}



