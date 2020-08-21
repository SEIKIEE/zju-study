#include "symTabRecord.h"
#include "string.h"	// strcpy strlen


SymTabRecord getSymTabRecord(char * name, int scope, char type, int location, int isVar)
{
	SymTabRecord rec;

	strcpy(rec.name, name);
	rec.scope = scope;
	rec.type = type;
	rec.location = location;
	rec.isVar = isVar;
	return rec;
}

void display(SymTabRecord *recPtr)
{
	printf("scope :%-8dname:%-16stype:%-16c location:%-8disVar:%-8d\n", recPtr->scope, recPtr->name, recPtr->type, recPtr->location, recPtr->isVar);
}

void display(SymTabRecord rec)
{
	printf("scope :%-8dname:%-16stype:%-16c location:%-8disVar:%-8d\n", rec.scope, rec.name, rec.type, rec.location,rec.isVar);
}