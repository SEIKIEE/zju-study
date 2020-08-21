#include "global.h"
#include "util.h"

SyntaxTree newStmtNode(StmtKind stmtKind)
{
    SyntaxTree t = (SyntaxTree)malloc(sizeof(struct TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = StatementNode;
        t->lineno = lineno;
        t->kind.stmt = stmtKind;
    }
    return t;
}

SyntaxTree newExpNode(ExpKind expKind)
{
    SyntaxTree t = (SyntaxTree)malloc(sizeof(struct TreeNode));
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        int i;
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = ExpressionNode;
        t->lineno = lineno;
        t->kind.exp = expKind;
        t->type = VoidExpType;
    }
    return t;
}

SyntaxTree newDeclNode(DeclKind declKind)
{
    SyntaxTree t = (SyntaxTree)malloc(sizeof(struct TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = DeclareNode;
        t->kind.decl = declKind;
        t->lineno = lineno;
    }
    return t;
}

SyntaxTree newTypeNode(TypeKind typeKind)
{
    SyntaxTree t = (SyntaxTree)malloc(sizeof(struct TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = TypeNode;
        t->lineno = lineno;
        t->kind.type = typeKind;
    }
    return t;
}

void freeNode(SyntaxTree node)
{
    int i;
    for (i = 0; i < MAXCHILDREN; i++)
        free(node->child[i]);
    free(node->sibling);
    free(node);
}

char* copyString(char* s)
{
    int n;
    char* t;
    if (s == NULL)
        return NULL;
    n = (int)strlen(s) + 1;
    t = (char*)malloc(sizeof(char) * n);
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else
        strcpy(t, s);
    return t;
}
