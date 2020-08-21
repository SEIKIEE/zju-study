#include "global.h"
#include "util.h"


TreeNode * newDeclNode(DeclKind kind)
{
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else{
        for(i=0;i<MAXCHILDREN;i++)
          t->child[i]=NULL;
        t->sibling=NULL;
        t->nodekind=NODE_DECLARE;  
        t->kind.decl = kind;
        t->lineno=lineno;
    }
    return t;
}


TreeNode * newStmtNode(StmtKind kind){
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else{
        for(i=0;i<MAXCHILDREN;i++)
          t->child[i]=NULL;
        t->sibling=NULL;
        t->nodekind=NODE_STATEMENT;
        t->kind.stmt=kind;
        t->lineno=lineno;
    }
    return t;
}


TreeNode * newExpNode(ExpKind kind){
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else{
        for(i=0;i<MAXCHILDREN;i++)
          t->child[i]=NULL;
        t->sibling=NULL;
        t->nodekind=NODE_EXPRESSION;
        t->kind.exp=kind;
        t->lineno=lineno;
        t->type = EXPTYPE_VOID;
    }
    return t;
}
    
TreeNode * newOpExpNode(TreeNode * first, TreeNode * second, TokenType op){
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else{
        for(i=0;i<MAXCHILDREN;i++)
          t->child[i]=NULL;
        t->sibling=NULL;
        t->nodekind=NODE_EXPRESSION;
        t->kind.exp=EXP_OP;
        t->attr.op=op;
        t->lineno=lineno;
        t->child[0]=first;
        t->child[1]=second;
    }
    return t;

}

TreeNode * newTypeNode(TypeKind type){
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else{
        for(i=0;i<MAXCHILDREN;i++)
          t->child[i]=NULL;
        t->sibling=NULL;
        t->nodekind=NODE_TYPE;   
        t->kind.type=type;
        t->lineno=lineno;
    }
    return t;
}

void freeNode(TreeNode *node){
    int i;
    for(i=0;i<MAXCHILDREN;i++)
      free(node->child[i]);
    free(node->sibling);
    free(node);
}


char* copyString(char *s)
{
    int n;
    char *t;
    if(s==NULL)
      return NULL;
    n = (int)strlen(s) + 1;
    t=(char*)malloc(sizeof(char)*n);
    if(t==NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);
    else
      strcpy(t,s);
    return t;
}

//used for printTree
static int indentno = 0;
#define INDENT indentno+=4
#define UNINDENT indentno-=4





















