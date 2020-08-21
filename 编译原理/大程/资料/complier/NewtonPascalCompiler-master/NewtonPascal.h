#ifndef _NewtonPascal_H_
#define _NewtonPascal_H_

struct SyntaxTreeNode {
	int type;
	union value {
	    double DValue;
	    char* SValue;
	    int IValue;
	    float FValue;
  	};
	//char text[48];
	struct SyntaxTreeNode* sNodeNext; // 指向同一层的节点
	struct SyntaxTreeNode* sNodeSon;  // 指向子节点

	char* pcode;
};

typedef SyntaxTreeNode* SyntaxTree;

void ProcessTree(struct SyntaxTreeNode* sNode);
struct SyntaxTreeNode* MallocNewNode();
struct SyntaxTreeNode* FatherAddSon(struct SyntaxTreeNode* sNodeFather, struct SyntaxTreeNode* sNodeSon);
struct SyntaxTreeNode* NewFatherAddSon(int Type, struct SyntaxTreeNode* sNodeSon);
struct SyntaxTreeNode* NewFatherAddSon(int Type, struct SyntaxTreeNode* sNodeSon1, struct SyntaxTreeNode* sNodeSon2);
struct SyntaxTreeNode* NewFatherAddSon(int Type, struct SyntaxTreeNode* sNodeSon1, struct SyntaxTreeNode* sNodeSon2, struct SyntaxTreeNode* sNodeSon3);
void FreeTree(struct SyntaxTreeNode* sNode);

#endif
/*
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



//some extern functions of lex or yacc

extern int yylex();
extern void yyrestart(FILE* f);
void yyerror(const char *s, ...);

extern int yylineno;
extern FILE* yyin;
extern char* yytext;*/
