#ifndef _UTIL_H_
#define _UTIL_H_


TreeNode * newStmtNode(StmtKind s);

TreeNode * newExpNode(ExpKind e);
TreeNode * newOpExpNode(TreeNode*, TreeNode*,TokenType);

TreeNode * newDeclNode(DeclKind d);

TreeNode * newTypeNode(TypeKind type);


void freeNode(TreeNode*);

char * copyString(char*);


#endif
