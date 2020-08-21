#include "symtab.h"
#include "util.h"

Symtab currentSymtab;

static int hash(char* key)
{
    int temp = 0;
    int i = 0;
    while (key[i] != '\0') {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

/* search if exist same bucket */
static int equal(Bucket a, Bucket b)
{
    if (a == NULL || b == NULL) {
        printf("Error: bucket is NULL.\n");
        return 0;
    }
    if (a->name != b->name)
        return 0;
    return 1;
}

/*
 * 对符号表整体进行操作的函数
 */

/* 为一个作用域创建一个符号表 */
Symtab SymtabCreate(char* nameSpace, Symtab parent)
{
    Symtab symtab = (Symtab)malloc(sizeof(struct SymtabNode));
    symtab->nameSpace = copyString(nameSpace);
    symtab->parent = parent;
    if (parent != NULL) {
        symtab->next = parent->child;
        parent->child = symtab;
    }
    symtab->child = NULL;
    memset(symtab->table, 0, sizeof(Bucket) * SIZE);
    return symtab;
}

/* 将bucket插入符号表中 */
void SymtabInsert(Symtab symtab, Bucket bucket)
{
    int h;
    Bucket bucketHead, bucketTemp;
    if (symtab == NULL || bucket == NULL) {
        printf("Error: symtab or bucket is NULL.\n");
        return;
    }
    h = hash(bucket->name);
    bucketHead = symtab->table[h];
    bucketTemp = bucketHead;
    while (bucketTemp != NULL && equal(bucketTemp, bucket) == 0) {
        bucketTemp = bucketTemp->next;
    }
    if (bucketTemp == NULL) {
        /* insert into head */
        bucket->next = bucketHead;
        symtab->table[h] = bucket;
    } else {
        // TO-DO: now just replace
        bucketTemp = bucket;
    }
}

/*
 * 对符号表中table的bucket进行操作的函数
 */

/* 创建一个Parameter */
Parameter createParamNode(SyntaxTree keyNode, SyntaxTree valueNode)
{
    Parameter parameter = (Parameter)malloc(sizeof(struct ParameterNode));
    Parameter parameterNext;
    parameter->name = keyNode->attr.name;
    parameter->next = NULL;
    parameter->type = valueNode->type;
    parameter->modification = 1;
    switch (valueNode->nodeKind) {
    case ExpressionNode:
        if (valueNode->kind.exp == ConstExp) {
            parameter->modification = 0;
            switch (valueNode->type) {

            case UnknowExpType:
                break;
            case UserExpType:
                break;
            case VoidExpType:
                break;
            case IntExpType:
                parameter->value[0].intValue = valueNode->attr.intValue;
                break;
            case RealExpType:
                parameter->value[0].realValue = valueNode->attr.realValue;
                break;
            case PointerExpType:
                break;
            case CharExpType:
                parameter->value[0].charValue = valueNode->attr.charValue;
                break;
            case StringExpType:
                parameter->value[0].stringValue = copyString(valueNode->attr.stringValue);
                break;
            case BoolExpType:
                parameter->value[0].intValue = valueNode->attr.intValue;
                break;
            case ArrayExpType:
                break;
            case RecordExpType:
                break;
            case EnumExpType:
                break;
            case LimitExpType:
                break;
            case FuncExpType:
                break;
            }
        }
        break;
    case TypeNode:
        switch (valueNode->kind.type) {

        case SimpleSysType:

            break;
        case SimpleIdType:

            break;
        case SimpleEnumType:

            break;
        case simpleLimitType:
            parameter->value[0].intValue = valueNode->child[0]->attr.intValue;
            parameter->value[1].intValue = valueNode->child[1]->attr.intValue;
            break;
        case ArrayType:
            parameterNext = createParamNode(keyNode, valueNode->child[0]);
            parameterNext->type = valueNode->child[1]->type;
            parameter->next = parameterNext;
            break;
        case RecordType:

            break;
        }
        break;
    default:
        break;
    }
    return parameter;
}

/* 创建一个parameter类型的bucket */
Bucket createParamBucket(SyntaxTree keyNode, SyntaxTree valueNode)
{
    Bucket bucket = (Bucket)malloc(sizeof(struct Entry));

    bucket->lineno = keyNode->lineno;
    bucket->name = copyString(keyNode->attr.name);
    bucket->type = ParamType;
    bucket->next = NULL;

    bucket->parameter = createParamNode(keyNode, valueNode);

    return bucket;
}

/* 创建一个function类型的bucket */
Bucket createFuncBucket(SyntaxTree keyNode, SyntaxTree resNode, SyntaxTree opNode)
{
    Bucket bucket = (Bucket)malloc(sizeof(struct Entry));

    bucket->lineno = keyNode->lineno;
    bucket->name = copyString(keyNode->attr.name);
    bucket->next = NULL;
    bucket->type = FuncType;

    bucket->function = (Function)malloc(sizeof(struct FunctionNode));
    bucket->function->funcOpAddr = opNode;
    bucket->function->returnType = resNode == NULL ? VoidExpType : resNode->type;
    bucket->function->paramCount = 0;
    bucket->function->paramAddr = NULL;

    return bucket;
}

/* 处理参数列表 */
void setFunctionParameter(Bucket funcBucket, SyntaxTree argsKeyNode, SyntaxTree argsValueNode)
{
    Parameter temp;
    Parameter argsBucket;
    if (argsKeyNode == NULL)
        return;
    funcBucket->function->paramCount++;
    argsBucket = createParamNode(argsKeyNode, argsValueNode);
    temp = funcBucket->function->paramAddr;
    if (temp == NULL) {
        funcBucket->function->paramAddr = argsBucket;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = argsBucket;
    }
    setFunctionParameter(funcBucket, argsKeyNode->sibling, argsValueNode);
}

Bucket CurrentSymtabSearch(Symtab symtab, char* name)
{
    Bucket bucket = symtab->table[hash(name)];
    while (bucket != NULL && strcmp(bucket->name, name)) {
        bucket = bucket->next;
    }
    return bucket;
}

Bucket SymtabSearch(Symtab symtab, char* name)
{
    Bucket bucket = NULL;
    if (symtab == NULL)
        return NULL;
    bucket = symtab->table[hash(name)];
    while (bucket != NULL && strcmp(bucket->name, name)) {
        bucket = bucket->next;
    }
    return bucket == NULL ? SymtabSearch(symtab->parent, name) : bucket;
}

char* SymtabSearchName(Symtab symtab, char* name)
{
    Bucket bucket = NULL;
    if (symtab == NULL)
        return "NULL";
    bucket = symtab->table[hash(name)];
    while (bucket != NULL && strcmp(bucket->name, name)) {
        bucket = bucket->next;
    }
    return bucket == NULL?SymtabSearchName(symtab->parent, name):symtab->nameSpace;
}
