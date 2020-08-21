%{
	#include<stdio.h>
	#include<math.h>
	struct Type{
		int iVal;
		double dVal;
		int type;
	};
	#define YYSTYPE struct Type
	int yyerror(char const *str);
	char* a;
	int yylex(void);
	int TYPE;
	extern char *yytext;
%}
%token INT
%token DOUBLE
%left '+''-'
%left '*''/'
%left '^'
%right UMINUS
%%

lines: lines exp '\n'
		{
			if($2.type == 1)
				printf("=%lf\n",$2.dVal);
			else printf("=%d\n",$2.iVal);
			TYPE = 0;
		}
	 | lines '\n'
	 | /* empty */
	 ;

exp : exp 
{
	printf("=%s\n",yytext);
}
'+' exp	
		{
			if(TYPE == 1)
			{
				$$.type = 1;
				$$.dVal = ($1.type == 1?$1.dVal:(double)$1.iVal) + ($3.type == 1?$3.dVal:(double)$3.iVal);
			} else {
				$$.type = 0;
				$$.iVal = $1.iVal + $3.iVal;
			}
		}
	 | exp '-' exp
	 	{
	 		if(TYPE == 1)
			{
				$$.type = 1;
				$$.dVal = ($1.type == 1?$1.dVal:(double)$1.iVal) - ($3.type == 1?$3.dVal:(double)$3.iVal);
				//printf("=%lf\n",$$.dVal);
			} else {
				$$.type = 0;
				$$.iVal = $1.iVal - $3.iVal;
				//printf("=%d\n",$$.iVal);
			}
	 	}
	 | exp '*' exp	
	 	{
	 		if(TYPE == 1)
			{
				$$.type = 1;
				$$.dVal = ($1.type == 1?$1.dVal:(double)$1.iVal) * ($3.type == 1?$3.dVal:(double)$3.iVal);
				//printf("=%lf\n",$$.dVal);
			} else {
				$$.type = 0;
				$$.iVal = $1.iVal * $3.iVal;
				//printf("=%d\n",$$.iVal);
			}
	 	}
	 | exp '/' exp	
	 	{
	 		if(TYPE == 1)
			{
				$$.type = 1;
				$$.dVal = ($1.type == 1?$1.dVal:(double)$1.iVal) / ($3.type == 1?$3.dVal:(double)$3.iVal);
				//printf("=%lf\n",$$.dVal);
			} else {
				$$.type = 0;
				$$.iVal = $1.iVal / $3.iVal;
				//printf("=%d\n",$$.iVal);
			}
	 	}
	 | exp '^' exp	
	 	{
	 		if(TYPE == 1)
			{
				$$.type = 1;
				$$.dVal = pow(($1.type == 1?$1.dVal:$1.iVal),($3.type == 1?$3.dVal:$3.iVal));
				//printf("=%lf\n",$$.dVal);
			} else {
				$$.type = 0;
				$$.iVal = pow($1.iVal,$3.iVal);
				//printf("=%d\n",$$.iVal);
			}
	 	}
	 | '(' exp ')'		{$$ = $2;}
	 | '-' exp %prec UMINUS
	 	{
	 		if(TYPE == 1)
	 		{
	 			$$.type = 1;
	 			$$.dVal = ($2.type == 1?$2.dVal:(double)$2.iVal)*(-1);
	 		} else {
	 			$$.iVal = $2.iVal * (-1);
	 		}
	 	}
	 | INT {$$ = $1;}
	 | DOUBLE {$$ = $1;} 
	 ;

%%
int main()
{
	yyparse();
	return 0;
}

int yyerror(char const *msg)
{
	extern char *yytext;
	return 0;
}
 