#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "global.h"

#define HASHSIZE 221
#define SHIFT 4
#define ConstValueSize 100
#define TypeTableSize 100

#define GLOBAL_HASHLIST_NAME "main program"
#define COMPOUND_HASHLIST_NAME "{}"

extern FILE * listing;
/*****************************with extra variable information, BucketList is designed to resolve hash confiction*/
typedef struct BucketListRec
{
	char * name;
	ExpType type;
	int num1; // use in limit and array
	int num2; //
	ExpType childtype;
	int memloc;
	struct BucketListRec * next;
} * BucketList;



typedef struct HashListRec/*one points to global, the rest stores all the function declaration*/
{
	char * declName;//global decalration should be '\0'
	struct HashListRec * child;
	struct HashListRec * parent;
	BucketList bucketList[HASHSIZE];
	struct HashListRec * next;
	int memBase; 
	int offset; /*used to record bucketList->memloc*/
	int paranum; //the number of parameter (if this is a function)
} * HashList;

/*************************The top table combines global and function*/


typedef struct
{
	int paramCnt;
	int offset;//-1 if not exist
	ExpType type;
	ExpType childtype;
	int isfathervar; //0 :Õý³£ 1£º ÊÇFatherParameter
	int num1;
	int num2;
}st_varInfo;

typedef struct {
    char* name;
    ExpType type;
    union{
        int int_val;
        double real_val;
        char char_val;
    } val;
}* ConstValueItem;

typedef struct {
    char* name;
    TreeNode* node;
}* TypeItem;



st_varInfo st_execute(TreeNode * node, int lineno);
void st_insertdecl_var_list(TreeNode*node);

void st_leave(TreeNode * node);

void printSymTab();

void CT_insert(ConstValueItem item);
ConstValueItem CT_lookup(char* name);

void TT_insert(TypeItem item);
TypeItem TT_lookup(char* name);



#endif
