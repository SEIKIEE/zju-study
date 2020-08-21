#include "symTabRecord.h"
#include <cstring>

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

std::string toString(SymTabRecord *ptr)
{
	char buffer [100];
	int cx;
	cx = snprintf(buffer, 100, "scope :%-8dname:%-16stype:%-16c location:%-8disVar:%-8d\n", ptr->scope, ptr->name, ptr->type, ptr->location, ptr->isVar);
	std::string result(buffer, cx);
	return result;
}