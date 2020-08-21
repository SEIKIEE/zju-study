/*
This is a baby pascal compiler, it contains: 
1. Lexical Analyzer (Scanner)
2. Syntax Analyzer  (Parser)
3. Semantic Analyzer (Parser + ST)
4. Code Generation  
These four parts all need to cooperate with 
1. SymbolTable (ST) 
2. ErrorHander
*/
/*
future work: 1) add error recovery 2) optimization code gen 3) make type coercion (int to float) easy 
*/
#include "Parser.h"
int main()
{
	testParser();
	return 0;
}

