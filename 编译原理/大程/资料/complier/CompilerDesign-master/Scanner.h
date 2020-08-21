/*
Lexical analysis: the 1st phase of a compiler.
GetToken: returns token including 1)an integer token number
2)a string/lexeme,
by removing any whitespace or comments in the source code.
Input: source code
Output: a token return to caller who called GetToken().

For testing this function.
Input: source code
Output: 1) tokenFile, a file of tokens
2) a listing file, echos the input  file, the addition of line numbers,
and possibly, lexical error messages.
*/

#ifndef _SCANNER_H_ //< avoid duplicate include
#define _SCANNER_H_
#include <cstdio>   // FILE
#include "string.h"  // strcpy
#include "ErrorHander.h" // error in FillBuffer()
#include"tokens.h"
#include "Utility.h"
#include <vector>

enum Token
{
	IDTOK = 1,
	LITTOK = 2,	// true false
	STRLITTOK = 3,	// "" ''
	ASTOK = 4,	// :=
	LEFTPARENTHESIS = 5,	// (
	RIGHTPARENTHESIS = 6,	// )
	COLON = 7,		// :
	SEMICOLON = 8,	// ;
	DOT = 9,		// .
	ADDOPTOK = 10,	// or + -
	MULOPTOK = 11,	// mod div and * /
	RELOPTOK = 12,   // < > =
	// key wrod below
	PROGTOK = 13,	
	BEGINTOK = 14,
	ENDTOK = 15,
	CONSTTOK = 16,
	VARTOK = 17,
	WHILETOK = 18,
	DOTOK = 19,
	IFTOK = 20,
	THENTOK = 21,
	BASTYPETOK = 22,
	NOTTOK = 23,
	WRITETOK = 24,
	READTOK =25
	//EOF = -1
};

//|------------------main routines-------------------|
Tokens GetToken();
void WriteTokenFile(Tokens tokenRec);
void EchosInputWithLine();
void WriteErrorInfo();
FILE * GetListingFile();

void InitScanner(); // file path of input 
void OpenFile();
void CloseFile();
void FillBuffer(); // fill buffer from input file
char GetChar(); // get char from buffer
int GetLine(); // get current line , needed in parser

bool SkipSpace(); //skip space
bool SkipComments(); // skip comments
Tokens MatchEnd(); // match EOF
Tokens MatchId(); // match identifier
Tokens MatchNumber();
Tokens MatchString();
Tokens MatchColonEqual();
Tokens MatchReserved();
void MatchKeyword(Tokens &token);

Tokens CompleteDFA(int begin, int cur, int tokenNum); //complete DFA

void InitKeyword();
void InitReserved();

//|-------------------- all below is for test -------------------|
void testScanner();

#endif