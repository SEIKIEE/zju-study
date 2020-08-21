#ifndef _TOKENS_H_	//avoid duplicate include
#define _TOKENS_H_

#include "stdio.h"
#include "string.h"

const int ID_MAX_LENGTH = 256;
const int ID_LENGTH = 8;

struct Tokens {
	char  lexeme[ID_MAX_LENGTH];
	int   number;
};

//|-----------main routines----|

void InitTokens(Tokens & token);

void WriteToScren(Tokens token); //print token

#endif