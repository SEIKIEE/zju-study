#include "tokens.h"

const int DEFAULT_TOKEN_NUM = -99; // default token number

//|-----------main routines----------|
void InitTokens(Tokens & token)
{
	strcpy(token.lexeme, "");
	token.number = DEFAULT_TOKEN_NUM;
}

void WriteToScren(Tokens token)
{
	printf("%-8d %-10s\n", token.number, token.lexeme);
}
