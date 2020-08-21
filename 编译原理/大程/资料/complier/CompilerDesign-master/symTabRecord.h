#ifndef _SYMTABRECORD_H_
#define	_SYMTABRECORD_H_

#include "ErrorHander.h"

const int IDMAXLENGTH = 256;
const int IDLENGTH = 8;
const int TYPELENGTH = 16;

struct SymTabRecord
{
	char name[IDMAXLENGTH];
	int scope;
	char type;
	int location;
	int isVar;  
};

SymTabRecord  getSymTabRecord(char *name, int scope, char type, int location, int isVar);
void display(SymTabRecord *recPtr);
void display(SymTabRecord rec);

#endif 
