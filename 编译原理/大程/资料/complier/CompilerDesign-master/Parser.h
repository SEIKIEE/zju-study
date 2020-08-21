/*
Syntax analysis: the 2nd phase of a compiler.
using Recursive Descent to parse the input.
program(): the enter routine

Input: token returned by Scanner.GetToken()
Output: left derivation number
*/

/*
Semantic Analyzer Parser + ST
if identify name, check it in ST, if not exist, add it, if exist complain
if using name, check it in ST, if not exist, error
if meet BGINTOK, openScope
if meet ENDTOK, closeScope
*/
#ifndef _PARSER_H_
#define _PARSER_H_
#include "Tokens.h" // struct Tokens
#include "Scanner.h" // GetToken()
#include "SymTable.h" // find() insert()
#include "CodeGen.h" // CodeGen()

struct ExpressionRecord
{
	char type;
	int loc;
};

//|---------------------------------parser---------------------------------|
// match number of token, if matched, set tokenRec as next token
void match(Tokens  &tokenRec, int ExpTokenNum);
//|---------------------main routines for parser---------------------------|
//(1) program : PROGTOK IDTOK¡¯(¡® ¡®)¡¯  [CONSTTOK constdecl {constdecl}]
//	[VARTOK vardecl{ vardecl }]  BEGINTOK statmt{ ¡®; ¡¯ statmt } ENDTOK ¡®.¡¯
bool program();
//(2¡¯) constdecl: IDTOK '=' LITTOK ';'
void constdecl(Tokens &tokenRec);
//(2)  vardecl: IDTOK ':' BASTYPETOK  ';'
void vardecl(Tokens &tokenRec);
//(3) statmt: assignstat| ifstat| readstat| writestat| blockst| loopst
void statmt(Tokens &tokenRec);
//(4) assignstat: idnonterm  ASTOK express 
void assignstat(Tokens &tokenRec);
//(5) ifstat: IFTOK express THENTOK  statmt  
void ifstat(Tokens &tokenRec);
//(6) readstat: READTOK '(' idnonterm ')' 
void readstat(Tokens &tokenRec);
//(7) writestat: WRITETOK '(' (STRLITTOK | express) ')' 
void writestat(Tokens &tokenRec);
//(8) whilest: WHILETOK express DOTOK statmt 
void loopst(Tokens &tokenRec);
//(9) blockst: [VARTOK vardecl {vardecl}]   BEGINTOK   statmt {;statmt} ENDTOK   
void blockst(Tokens &tokenRec);
//(10) express: term { ADDOPTOK term }
void express(Tokens &tokenRec, ExpressionRecord & er);
//(11) term: relfactor {MULOPTOK relfactor}  
void term(Tokens &tokenRec, ExpressionRecord & er);
//(12) relfact: factor  [ RELOPTOK factor ]
void relfact(Tokens &tokenRec, ExpressionRecord & er);
//(13) factor: NOTTOK  factor    |   idnonterm   |   LITTOK  | '(' express ')'
void factor(Tokens &tokenRec, ExpressionRecord & er);
//(14) idnonterm: IDTOK
void idnonterm(Tokens &tokenRec, SymTabRecord *&ST_Ptr);
//|----------------------assis-----------------------------------|
char GetTypeFrom(char *);
string i_str(const char * c, const int i);
//|-------------------- all below is for test -------------------|
void testParser();
#endif // !_PARSER_H_
