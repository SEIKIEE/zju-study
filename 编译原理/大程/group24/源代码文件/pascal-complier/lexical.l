%option yylineno case-insensitive

%{
#include "global.h"
#include "util.h"
#include "scan.h"
#include "grammar.tab.h"
char tokenString[MAXTOKENLEN+1];
%}

digit [0-9]
letter [a-zA-Z]
intvalue {digit}+
realvalue {digit}+\.{digit}+
charvalue \'.\'
stringvalue \"[^\"]*\"
identifier ("_"|{letter})("_"|{letter}|{digit})*
newline \n
whitespace [ \t]+

%%
"abs"             {return ABS;}
"and"             {return AND;}
"array"           {return ARRAY;}
"begin"           {return TOKEN_BEGIN;}
"boolean"         {return BOOLEAN_TYPE;}
"case"            {return CASE;}
"char"            {return CHAR_TYPE;}
"chr"             {return CHR;}
"const"           {return CONST;}
"div"             {return DIV;}
"do"              {return DO;}
"downto"          {return DOWNTO;}
"else"            {return ELSE;}
"end"             {return END;}
"false"           {return FALSE;}
"for"             {return FOR;}
"function"        {return FUNCTION;}
"goto"            {return GOTO;}
"if"              {return IF;}
"integer"         {return INTEGER_TYPE;}
"maxint"          {return MAXINT;}
"not"             {return NOT;}
"odd"             {return ODD;}
"of"              {return OF;}
"or"              {return OR;}
"ord"             {return ORD;}
"pred"            {return PRED;}
"procedure"		  {return PROCEDURE;}
"program"         {return PROGRAM;}
"read"            {return READ;}
"real"            {return REAL_TYPE;}
"read"            {return READ;}
"record"          {return RECORD;}
"repeat"          {return REPEAT;}
"sqr"             {return SQR;}
"sqrt"            {return SQRT;}
"succ"            {return SUCC;}
"then"            {return THEN;}
"to"              {return TO;}
"true"            {return TRUE;}
"type"            {return TYPE;}
"until"           {return UNTIL;}
"var"             {return VAR;}
"while"           {return WHILE;}
"write"           {return WRITE;}
"writeln"         {return WRITELN;}

"("         {return LP;}
")"         {return RP;}
"["         {return LB;}
"]"         {return RB;}
"."         {return DOT;}
".."        {return DOTDOT;}
","         {return COMMA;}
";"         {return SEMI;}
":"         {return COLON;}
"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MUL;}
"/"         {return DIV;}
"%"         {return MOD;}
">="        {return GE;}
">"         {return GT;}
"<="        {return LE;}
"<"         {return LT;}
":="        {return ASSIGN;}
"="         {return EQUAL;}
"<>"        {return UNEQUAL;}

{intvalue}       {return  TOKEN_INTEGER;}
{realvalue}      {return  REAL;}
{charvalue}      {return  CHAR;}
{stringvalue}    {return  STRING;}
{identifier}     {return  TOKEN_ID;}
{newline}        {lineno++;}
{whitespace}     {}

'(\\.|[^'\n])*$                  {yyerror("lexical");}
\"(\\.|[^"\n])*$                 {yyerror("lexical");}
"{"[^{}]*"}" 	                 {/* ignore comments */}

%%

int yywrap (void)
{
    return 1;
}

TokenType getToken(void)
{
	static int first = True;
	TokenType currentToken;
    if(first)
    {
        first = False;
        lineno++;
        yyin = source;
        yyout = listing;
    }
	currentToken = yylex();
	strncpy(tokenString,yytext,MAXTOKENLEN);
	if(TraceScan) {
		fprintf(listing,"\t%d:\t%s\n",lineno, tokenString);
	}
	return currentToken;
}
