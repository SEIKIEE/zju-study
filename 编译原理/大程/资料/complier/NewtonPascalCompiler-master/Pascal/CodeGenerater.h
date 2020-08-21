#ifndef CODEGEN_H
#define CODEGEN_H


#include <stdio.h>
#include "global.h"
#include "symtab.h"
#include "tiny.tab.h"

#ifdef CG_DEBUG
extern FILE* tmp_out;
#endif

int BuildCode(TreeNode* pnode);
char* InitialGenerater(char* o_name);



#endif
