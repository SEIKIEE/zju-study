#include "declare.h"
#include "symbolTable.h"

#include <cstdio>
#include <iostream>

using namespace lwd;
using namespace std;

void asm_init() {
	cout <<
".macro print_int (%x)\n\
	li $v0, 1\n\
	add $a0, $zero, %x\n\
	syscall\n\
.end_macro\n\n\
.macro print_char (%x)\n\
	li $v0, 11\n\
	add $a0, $zero, %x\n\
	syscall\n\
.end_macro\n\n\
.macro print_str (%str)\n\
	.data\n\
		myLabel: .asciiz %str\n\n\
	.text\n\
	li $v0, 4\n\
	la $a0, myLabel\n\
	syscall\n\
.end_macro\n" << endl;

	cout << "addi $sp, $sp,   -100" << endl;
	cout << "add  $fp, $zero, $sp" << endl;
}

void asm_clean() {
	cout << "addi $sp, $sp, 100" << endl;
}

int main(int argc, char *argv[]) {
	//extern int yydebug;
	//yydebug = 1;	

	if(yyparse()) {
		fprintf(stderr, "\n");
		return 1;
	}
	fprintf(stderr, "parse complete\n");

	program *root = savedRoot;
	if(!root->semanticCheck(gtable.insertScope())||!gtable.checkLabel()) {
		fprintf(stderr, "semantic error.\n");
		return 1;
	}
	fprintf(stderr, "semantic check complete.\n");

	asm_init();

	// 为数组参数申请空间
	char temp[30];
	assert(root->child2->child1->child4 != NULL);	// var_part
	var_decl_list * vars = root->child2->child1->child4->child1;
	// program scope
	int pscope = 1;
	while (vars != NULL) {
		if (vars->child2->choice1 == 2) {	// 数组
			assert(vars->child2->child1.choice2->child1->choice1 == 4);	// range
			int arraySize = vars->child2->child1.choice2->child1->child1.choice4->size;

			name_list * varName = vars->child1;
			while (varName != NULL) {
				// 写数组地址
				identifier * newvariden = gtable.lookUp(varName->child2, pscope);
				assert(newvariden->type == aarray_type);
				// 开栈
				sprintf(temp, "%d", -1 * arraySize * 4);
				cout << "addi $sp, $sp, " + string(temp) << endl;
				cout << "sw $sp, " + to_string(newvariden->offset) + "($fp)" << endl;

				varName = varName->child1;
			}
		}
		else {}

		vars = vars->next;
	}

	cout << root->cgen() << endl;
	//asm_clean();

	return 0;
}
