#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef False
#define False 0
#endif

#ifndef True
#define True 1
#endif

#ifndef YYPARSER
#include "tiny.tab.h"
#define ENDFILE 0
#endif



#define MAXRESERVED 8
typedef int TokenType;
extern FILE* source;
extern FILE* listing;
//extern FILE* code;

extern int lineno;


typedef enum{
    NODE_STATEMENT, NODE_EXPRESSION, NODE_DECLARE, NODE_TYPE
}NodeKind;

typedef enum{
    STMT_LABEL,
    STMT_ASSIGN,STMT_GOTO,STMT_IF,STMT_REPEAT,STMT_WHILE,STMT_FOR,STMT_CASE,
    STMT_PROC_ID,STMT_PROC_SYS
}StmtKind;

typedef enum{
    OP,EXP_ID,NUMBER,CONST,INDEX,
    EXP_CONST,
    EXP_OP,EXP_CASE,EXP_FUNC
}ExpKind;

typedef enum{
    DECL_ROUTINEHEAD,
    DECL_FUNCTION,DECL_FUNCTIONHEAD,
    DECL_PROCEDURE,DECL_PROCEDUREHEAD,
    DECL_CONST,DECL_VAR,DECL_TYPE,
    DECL_VAR_PARA,DECL_VAL_PARA
}DeclKind;

typedef enum{
    TYPE_SIMPLE_SYS,TYPE_SIMPLE_ID, TYPE_SIMPLE_ENUM, TYPE_SIMPLE_LIMIT,
    TYPE_ARRAY, TYPE_RECORD
}TypeKind;

//
typedef enum{
    EXPTYPE_UNKNOW,EXPTYPE_VOID,EXPTYPE_INT,EXPTYPE_REAL,EXPTYPE_POINTER,
    EXPTYPE_CHAR,EXPTYPE_STRING,EXPTYPE_BOOL,
    EXPTYPE_ARRAY,EXPTYPE_RECORD,EXPTYPE_ENUM,EXPTYPE_LIMIT,EXPTYPE_FUNC
}ExpType;

#define MAXCHILDREN 4

typedef struct treeNode{
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    NodeKind nodekind;
    int lineno;
    union{
        StmtKind stmt;
        ExpKind exp;
        DeclKind decl;
        TypeKind type;
    }kind;
    union{
        TokenType op;
        char * name;
        int val;
        char char_val;
        char * string_val;
        float real_val;
    }attr;
    ExpType type;
}TreeNode;

extern int TraceScan;





#endif
