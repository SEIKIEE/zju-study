#ifndef _SYMTABLE_H_ //avoid duplicate include
#define _SYMTABLE_H_

#include "symTabRecord.h" // SymTabRecord
#include "Utility.h" // convert to Little Case
#include <sstream>	// for stringstream
#include <unordered_map>	// unordered_map
#include<stack>		// use scopeStack

//|------------------main routines-------------------|
void initSymTable();
void openScope();
void closeScope();
void insert(char* name, char type, int location, int isVar);
SymTabRecord* findInCurScope(char *name);
SymTabRecord* findInAllScopes(char *name);
void displaySymTable();
void displaySymTable(FILE * file);

//|-------------------- all below is for test -------------------|
void testFindInLocalScope(char *name);
void testFindInAllScopes(char *name);
void testST();
#endif // !_SYMTABLE_H_
