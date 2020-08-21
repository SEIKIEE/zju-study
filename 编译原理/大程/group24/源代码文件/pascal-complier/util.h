#ifndef _UTIL_H_
#define _UTIL_H_

SyntaxTree newStmtNode(StmtKind s);
SyntaxTree newExpNode(ExpKind e);
SyntaxTree newDeclNode(DeclKind d);
SyntaxTree newTypeNode(TypeKind type);

void freeNode(SyntaxTree);
char* copyString(char*);

#endif
