#ifndef symtab_h
#define symtab_h

#include "global.h"

#define GLOBAL_NAMESPACE "program"
#define SIZE 211
#define SHIFT 4
#define NUMBER 2
#define PARAM 0
#define FUNC 1
#define SYMTAB_SIZE 13

typedef enum
{
    ParamType,
    FuncType
} BucketType;

typedef struct ParameterNode
{
    char *name;       /* 名字 */
    ExpType type;     /* 类型 */
    int modification; /* 是否可以修改 */
    union {
        int intValue;
        char charValue;
        char *stringValue;
        float realValue;
    } value[NUMBER]; /* 值 */
    struct ParameterNode *next;
} * Parameter;

typedef struct FunctionNode
{
    int paramCount;        /* 参数个数 */
    Parameter paramAddr;   /* 参数链表 */
    ExpType returnType;    /* 返回值类型 */
    SyntaxTree funcOpAddr; /* 函数体 */
} * Function;

typedef struct Entry
{
    char *name;      /* 名字 */
    int lineno;      /* 源代码中的行号 */
    BucketType type; /* 区分是作用域名与非作用域名 */
    Function function;
    Parameter parameter;
    struct Entry *next;
} * Bucket;

typedef struct SymtabNode
{
    char *nameSpace;
    Bucket table[SIZE];
    SyntaxTree treeAddr;
    struct SymtabNode *parent;
    struct SymtabNode *child;
    struct SymtabNode *next;
} * Symtab;

void SymtabInsert(Symtab symtab, Bucket bucket);
Symtab SymtabCreate(char *nameSpace, Symtab parent);
Bucket SymtabSearch(Symtab symtab, char *name);
Bucket CurrentSymtabSearch(Symtab symtab, char *name);
char *SymtabSearchName(Symtab symtab, char *name);

Parameter createParamNode(SyntaxTree keyNode, SyntaxTree valueNode);
Bucket createParamBucket(SyntaxTree keyNode, SyntaxTree valueNode);
Bucket createFuncBucket(SyntaxTree keyNode, SyntaxTree resNode, SyntaxTree opNode);
void setFunctionParameter(Bucket funcBucket, SyntaxTree argsKeyNode, SyntaxTree argsValueNode);

#endif /* symtab_h */
