%option yylineno case-insensitive

%{
#include "global.h"
#include "util.h"
#include "scan.h"
char previoustokenString[MAXTOKENLEN+1];
char tokenString[MAXTOKENLEN+1];
extern int yyerror(char* messega);
%}

digit [0-9]
real {digit}+\.{digit}+
number {digit}+
letter [a-zA-Z]
identifier [A-Za-z][A-Za-z0-9_]*
newline \n
whitespace [ \t]+
char \'.\'
string \".*\"
%%
"program"       {return TOKEN_PROGRAM;}
"if"        {return TOKEN_IF;}
"then"      {return TOKEN_THEN;}
"else"      {return TOKEN_ELSE;}
"repeat"    {return TOKEN_REPEAT;}
"until"     {return TOKEN_UNTIL;}
"while"     {return TOKEN_WHILE;}
"do"        {return TOKEN_DO;}
"case"      {return TOKEN_CASE;}
"to"        {return TOKEN_TO;}
"downto"    {return TOKEN_DOWNTO;}
"for"       {return TOKEN_FOR;}
"read"      {return TOKEN_READ;}
"write"     {return TOKEN_WRITE;}
"writeln"   {return TOKEN_WRITELN;}

"["         {return TOKEN_LB;}
"]"         {return TOKEN_RB;}
";"         {return TOKEN_SEMI;}
".."        {return TOKEN_DOTDOT;}
"."         {return TOKEN_DOT;}
"("         {return TOKEN_LP;}
")"         {return TOKEN_RP;}
","         {return TOKEN_COMMA;}
":"         {return TOKEN_COLON;}

":="        {return TOKEN_ASSIGN;}
"="         {return TOKEN_EQUAL;} 
"+"         {return TOKEN_PLUS;}
"-"         {return TOKEN_MINUS;}
"or"        {return TOKEN_OR;}
"<>"        {return TOKEN_UNEQUAL;}
">="        {return TOKEN_GE;}
">"         {return TOKEN_GT;}
"<="        {return TOKEN_LE;}
"<"         {return TOKEN_LT;}
"*"         {return TOKEN_MUL;}
"/"        {return TOKEN_DIV;}
"mod"       {return TOKEN_MOD;}
"and"       {return TOKEN_AND;}
"not"       {return TOKEN_NOT;}

"goto"      {return TOKEN_GOTO;}
"integer"   {return TOKEN_INTEGER_TYPE;}
"boolean"   {return TOKEN_BOOLEAN_TYPE;}
"char"      {return TOKEN_CHAR_TYPE;}
"real"      {return TOKEN_REAL_TYPE;}
"true"      {return TOKEN_TRUE;}
"false"     {return TOKEN_FALSE;}
"maxint"    {return TOKEN_MAXINT;}
"array"     {return TOKEN_ARRAY;}
"of"        {return TOKEN_OF;}
"record"    {return TOKEN_RECORD;}
"begin"     {return TOKEN_BEGIN;}
"end"       {return TOKEN_END;}
"const"     {return TOKEN_CONST;}
"type"      {return TOKEN_TYPE;}
"var"       {return TOKEN_VAR;}
"function"  {return TOKEN_FUNCTION;}
"procedure" {return TOKEN_PROCEDURE;}
{number}    {return TOKEN_INT;}
{real}      {return TOKEN_REAL;}
{char}      {return TOKEN_CHAR;}
{string}    {return TOKEN_STRING;}
{identifier} {return TOKEN_ID;}
{newline}   {lineno++;}
{whitespace}    {}

'(\\.|[^'\n])*$                  {  yyerror("Unterminated string %s", yytext);  }
\"(\\.|[^"\n])*$                 {  yyerror("Unterminated string %s", yytext);  }

"{"[^{}]*"}" 	{/* ignore comments */}


%%

int yywrap (void)
{
    return 1;
}

TokenType getToken()
{
    static int firstTime=True;
    TokenType currentToken;
    if(firstTime){
        firstTime = False;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(previoustokenString,tokenString,MAXTOKENLEN);
    strncpy(tokenString,yytext,MAXTOKENLEN);
    if(TraceScan){
        fprintf(listing,"\t%d: ",lineno);
        //printToken(currentToken,tokenString);
    }
    return currentToken;
}
