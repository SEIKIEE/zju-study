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
#include "grammar.tab.h"
#define ENDFILE 0
#endif

typedef int TokenType;
extern FILE *source;
extern FILE *listing;
extern FILE *code;
extern FILE *visualTree;

extern int lineno;
extern int TraceScan;

typedef enum
{
    GeOp,
    GtOp,
    LeOp,
    LtOp,
    EqualOp,
    UnequalOp,
    PlusOp,
    MinusOp,
    OrOp,
    MulOp,
    DivOp,
    ModOp,
    AndOp,
    NotOp,
    AbsOp,
    ChrOp,
    OddOp,
    OrdOp,
    PredOp,
    SqrOp,
    SqrtOp,
    SuccOp,
    ReadOp,
    WriteOp,
    WritelnOp,
    ToOp,
    DowntoOp
} OpKind;

typedef enum
{
    StatementNode,
    ExpressionNode,
    DeclareNode,
    TypeNode
} NodeKind;

typedef enum
{
    LabelStmt,
    AssignStmt,
    GotoStmt,
    IfStmt,
    RepeatStmt,
    WhileStmt,
    ForStmt,
    CaseStmt,
    ProcIdStmt,
    ProcSysStmt,
    FuncIdStmt,
    FuncSysStmt
} StmtKind; /* 语句类型 */

typedef enum
{
    IdExp,
    ConstExp,
    OpExp,
    CaseExp
} ExpKind; /* 表达式类型 */

typedef enum
{
    ProgramDecl,
    ProgramheadDecl,
    RoutineDecl,
    RoutineheadDecl,
    FunctionDecl,
    FunctionheadDecl,
    ProcedureDecl,
    ProcedureheadDecl,
    ConstDecl,
    VarDecl,
    TypeDecl,
    VarParaDecl
} DeclKind;

typedef enum
{
    SimpleSysType,
    SimpleIdType,
    SimpleEnumType,
    simpleLimitType,
    ArrayType,
    RecordType
} TypeKind;

/* ExpType is used for type checking */
typedef enum
{
    UnknowExpType,
    UserExpType,
    VoidExpType,
    IntExpType,
    RealExpType,
    PointerExpType,
    CharExpType,
    StringExpType,
    BoolExpType,
    ArrayExpType,
    RecordExpType,
    EnumExpType,
    LimitExpType,
    FuncExpType
} ExpType;

#define MAXCHILDREN 4

typedef struct TreeNode
{
    struct TreeNode *child[MAXCHILDREN];
    struct TreeNode *sibling;
    int lineno;
    NodeKind nodeKind;
    union {
        StmtKind stmt;
        ExpKind exp;
        DeclKind decl;
        TypeKind type;
    } kind;
    union {
        OpKind op;
        int intValue;
        char charValue;
        char *stringValue;
        float realValue;
        char *name;
    } attr;
    ExpType type; /* for type checking of exps */
} * SyntaxTree;

extern int traceScan;

#endif
