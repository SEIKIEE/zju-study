#ifndef analyze_h
#define analyze_h

#include "util.h"

extern int errFlag;
extern Symtab dummySymtab;

typedef enum {
    Redefinition,
    Undefinition,
    FuncUndefinition,
    ConstModification,
    ArgumentNumber,
    ErrorInType,
    TypeMismatch
} ErrorType;

void buildSymtab(SyntaxTree syntaxTree, Symtab symtab);
void paramCheck(Bucket funcBucket, SyntaxTree paramNode, Symtab symtab);
ExpType semanticAnalysis(SyntaxTree treeNode, Symtab symtab, int modification);

#endif /* analyze_h */
