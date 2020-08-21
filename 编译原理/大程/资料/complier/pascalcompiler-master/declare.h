#ifndef _LWD_DECLARE_H_
#define _LWD_DECLARE_H_

#include <string>
#include <cstdio>
#include <vector>
#include <cstring>

//#include "symbolTable.h"

extern int lineno;
extern char *yytext;
int yylex();
int yyerror(const std::string &);
int yyparse();

//#define SEMANTIC_DEBUG

namespace lwd {
struct identifier;
struct program;
struct program_head;
struct routine;
struct routine_head;
struct routine_body;
struct label_part;
struct const_part;
struct type_part;
struct var_part;
struct routine_part;
struct const_expr;
typedef const_expr const_expr_list;
struct const_value;
struct type_definition;
typedef type_definition type_decl_list;
struct type_decl;
struct simple_type_decl;
struct array_type_decl;
struct record_type_decl;
struct sys_type;
struct name_list;
struct range;
struct idrange;
struct field_decl;
typedef field_decl field_decl_list;
struct var_decl;
typedef var_decl var_decl_list;
struct function_decl;
typedef function_decl function_decl_list;
struct function_head;
struct procedure_decl;
typedef procedure_decl procedure_decl_list;
struct procedure_head;
struct sub_routine;
struct parameters;
struct para_type_list;
typedef para_type_list para_decl_list;
typedef name_list var_para_list;
typedef name_list val_para_list;
struct compound_stmt;
struct stmt;
typedef stmt stmt_list;
struct non_label_stmt;
struct assign_stmt;
struct proc_stmt;
struct if_stmt;
struct repeat_stmt;
struct while_stmt;
struct for_stmt;
struct case_stmt;
struct goto_stmt;
struct sys_proc;
struct expression;
typedef expression args_list;
typedef expression expression_list;
struct else_clause;
struct case_expr;
typedef case_expr case_expr_list;
struct expr;
struct term;
struct factor;
struct sys_funct;
struct sys_con;

enum Type {
	ssimple_type,
	aarray_type,
	rrecord_type,
	pprogram,
	pprocedure,
	ffunction,
	ccallable
};

enum SimpleType {
	iinteger,
	rreal,
	cchar,
	sstring,
	ssys_con,
	iidref,
	eenum,
	rrange,
	iidrange,
	bbool
};

void stprint(SimpleType s);

enum SysCon {

};

enum SysProc {
	wwrite,
	wwriteln
};

enum SysFunct {

};

enum Operator {
	gge,
	ggt,
	lle,
	llt,
	eequal,
	uunequal,
	pplus,
	mminus,
	oor,
	mmul,
	ddiv,
	mmod,
	aand
};

union u {
	SimpleType stype;
	identifier *idref;
	array_type_decl *array;
	record_type_decl *record;
};

extern lwd::program *savedRoot;
extern bool error;

lwd::program *parse();
void lower(char str[]);
void reportNameCollision(lwd::identifier *id, int scope);
void reportNameMissing(lwd::identifier *id, int scope);
void reportTypeMismatch(lwd::identifier *id, int scope);
void reportTypeMismatch(int lineno, identifier *id, expression *exp);
void reportTypeMismatch(int lineno, expression *exp1, expr *exp2);
void reportTypeMismatch(int lineno, expression *exp, SimpleType stype);
void reportTypeMismatch(int lineno, lwd::identifier *id, Type type);
std::string typeString(lwd::identifier *id);
std::string typeString(expression *exp);
std::string typeString(expr *exp);
std::string tString(Type type, SimpleType stype);
bool typeEqual(lwd::identifier *id, expression *exp);
bool typeEqual(lwd::identifier *id1, lwd::identifier *id2);
bool typeEqual(expression *exp1, expression *exp2);
bool typeEqual(expression *exp1, expr *exp2);
bool tEqual(const Type &t1, const SimpleType &s1, const Type &t2, const SimpleType &s2);
bool parametersMatch(identifier *id, args_list *args);

struct identifier {
	std::string name;
	int lineno;
	Type type;
	SimpleType stype;
	std::vector<std::string> *paras;//for function & procedure
	union {
		int i;
		float f;
		char c;
		std::string *s;
		SysCon syscon;
		identifier *idref;
		name_list *e;
		range *r;
		idrange *idr;
		array_type_decl *array;
		record_type_decl *record;
		program *prog;
		procedure_decl *proc;
		function_decl *func;
	} value;
	int offset;
	int scope;
	bool constant;
	bool typedefinition;
	bool passByReference;//for parameters 
	identifier(const char n[], int l):name(n),lineno(l) {}
	identifier(const std::string &n, int l):name(n),lineno(l) {}
	//std::string cgen();
};

struct program {
	program_head *child1;
	routine *child2;
	program(program_head *c1, routine *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct program_head {
	identifier *child1;
	program_head(identifier *c1):child1(c1) {}
	bool semanticCheck(program *root, int scope);
	std::string cgen();
};

struct routine {
	routine_head *child1;
	routine_body *child2;
	routine(routine_head *c1, routine_body *c2):child1(c1),child2(c2) { }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct sub_routine {
	routine_head *child1;
	routine_body *child2;
	sub_routine(routine_head *c1, routine_body *c2):child1(c1),child2(c2) { }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct routine_head {
	label_part *child1;
	const_part *child2;
	type_part *child3;
	var_part *child4;
	routine_part *child5;
	routine_head(label_part *c1, const_part *c2, type_part *c3, var_part *c4, routine_part *c5):child1(c1),child2(c2),child3(c3),child4(c4),child5(c5) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct label_part {
	//nothing
	bool semanticCheck(int scope) { return true; }
	std::string cgen();
};

struct const_part {
	const_expr_list *child1;
	const_part(const_expr_list *c1):child1(c1) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct const_expr {
	identifier *child1;
	const_value *child2;
	const_expr *next;
	const_expr(identifier *c1, const_value *c2, const_expr *n):child1(c1),child2(c2),next(n) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct const_value {
	int choice1;
	union {
		int choice1;
		float choice2;
		char choice3;
		std::string *choice4;
		sys_con *choice5;
	} child1;
	const_value(int c, const char *buff):choice1(c) {
		//printf("%d\n", c);
		switch(choice1) {
		case 1: sscanf(buff, "%d", &(child1.choice1)); break;
		case 2: sscanf(buff, "%f", &(child1.choice2)); break;
		case 3: sscanf(buff+1, "%c", &(child1.choice3)); break;
		case 4: child1.choice4 = new std::string(buff+1, strlen(buff)-2); break;
		default : break;//error
		}
	}
	const_value(sys_con *c1):choice1(5) { child1.choice5 = c1; }
	void negate() { choice1==1?child1.choice1 = -child1.choice1:
					choice1==2?child1.choice2 = -child1.choice2:
					child1.choice3 = -child1.choice3; }
	bool semanticCheck(identifier *id, int scope);
	std::string cgen();
};

struct sys_con {
	int choice1;
	SysCon child1;
	std::string cgen();
};

struct type_part {
	type_decl_list *child1;
	type_part(type_decl_list *c1):child1(c1) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct type_definition {
	identifier *child1;
	type_decl *child2;
	type_definition *next;
	type_definition(identifier *c1, type_decl *c2, type_definition *n):child1(c1),child2(c2),next(n) { printf("type_definition constructor : %s\n", c1->name.c_str()); }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct type_decl {
	int choice1;
	union {
		simple_type_decl *choice1;
		array_type_decl *choice2;
		record_type_decl *choice3;
	} child1;
	type_decl(simple_type_decl *c1):choice1(1) { child1.choice1 = c1; }
	type_decl(array_type_decl *c2):choice1(2) { child1.choice2 = c2; }
	type_decl(record_type_decl *c3):choice1(3) { child1.choice3 = c3; }
	bool semanticCheck(identifier *id, int scope, int type);
	bool semanticCheck(name_list *ids, int scope, int type);
	std::string cgen();
};

struct simple_type_decl {
	int choice1;
	union {
		sys_type *choice1;
		lwd::identifier *choice2;
		name_list *choice3;
		range *choice4;
		idrange *choice5;
	} child1;
	simple_type_decl(sys_type *c1):choice1(1) { child1.choice1 = c1; }
	simple_type_decl(lwd::identifier *c2):choice1(2) { child1.choice2 = c2; }
	simple_type_decl(name_list *c3):choice1(3) { child1.choice3 = c3; }
	simple_type_decl(range *c4):choice1(4) { child1.choice4 = c4; }
	simple_type_decl(idrange *c5):choice1(5) { child1.choice5 = c5; }
	bool semanticCheck(identifier *id, int scope, int type);
	bool semanticCheck(name_list *ids, int scope, int type);
	std::string cgen();
};

struct sys_type {
	SimpleType child1;
	sys_type(int c1) {
		switch(c1) {
		case 1: child1 = iinteger; break;
		case 2: child1 = rreal; break;
		case 3: child1 = cchar; break;
		case 4: child1 = sstring; break;
		default: break;//error
		}
	}
	std::string cgen();
};
/***********************************/
struct range {
	int lineno;
	const_value *child1;
	const_value *child2;
	range(const_value *c1, const_value *c2):child1(c1),child2(c2),size(-1) {}
	int size;//useful only for array
	void negate() { child1->negate(); child2->negate(); }
	void negate(int c) { c==1?child1->negate():child2->negate(); }
	bool semanticCheck();
	std::string cgen();
};

struct idrange {
	identifier *child1;
	identifier *child2;
	idrange(identifier *c1, identifier *c2):child1(c1),child2(c2) {}
	std::string cgen();
};

struct array_type_decl {
	simple_type_decl *child1;//implement only range
	type_decl *child2;//implement only sys_type
	array_type_decl(simple_type_decl *c1, type_decl *c2):child1(c1),child2(c2) {}
	bool semanticCheck(identifier *id, int scope, int type);
	std::string cgen();
};

struct record_type_decl {
	field_decl_list *child1;
	record_type_decl(field_decl_list *c1):child1(c1) {}
	bool semanticCheck(identifier *id, int scope, int type) {
		//not implemented
		return true;
	}
	std::string cgen();
};

struct field_decl {
	name_list *child1;
	type_decl *child2;
	field_decl *next;
	field_decl(name_list *c1, type_decl *c2, field_decl *n):child1(c1),child2(c2),next(n) {}
	std::string cgen();
};

struct name_list {
	name_list *child1;
	identifier *child2;
	name_list(name_list *c1, identifier *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct var_part {
	var_decl_list *child1;
	var_part(var_decl_list *c1):child1(c1) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct var_decl {
	name_list *child1;
	type_decl *child2;
	var_decl *next;
	var_decl(name_list *c1, type_decl *c2, var_decl *n):child1(c1),child2(c2),next(n) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct routine_part {
	function_decl_list *child1;
	procedure_decl_list *child2;
	routine_part(function_decl_list *c1, procedure_decl_list *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct function_decl {
	function_head *child1;
	sub_routine *child2;
	function_decl *next;
	function_decl(function_head *c1, sub_routine *c2, function_decl *n):child1(c1),child2(c2),next(n) {}
	bool nameCheck(int scope);
	bool semanticCheck(int scope);
	void reversePosition(int scope);
	std::string cgen();
};

struct function_head {
	identifier *child1;
	parameters *child2;
	simple_type_decl *child3;
	function_head(identifier *c1, parameters *c2, simple_type_decl *c3):child1(c1),child2(c2),child3(c3) {}
	bool semanticCheck(function_decl *root, int scope);
	std::string cgen();
};

struct procedure_decl {
	procedure_head *child1;
	sub_routine *child2;
	procedure_decl *next;
	procedure_decl(procedure_head *c1, sub_routine *c2, procedure_decl *n):child1(c1),child2(c2),next(n) {}
	bool nameCheck(int scope);
	bool semanticCheck(int scope);
	void reversePosition(int scope);
	std::string cgen();
};

struct procedure_head {
	identifier *child1;
	parameters *child2;
	procedure_head(identifier *c1, parameters *c2):child1(c1),child2(c2) {}
	bool semanticCheck(procedure_decl *root, int scope);
	std::string cgen();
};

struct parameters {
	para_decl_list *child1;
	parameters(para_decl_list *c1):child1(c1) {}
	bool semanticCheck(identifier *root, int scope);
	std::string cgen();
};

struct para_type_list {
	int choice1;
	union {
		var_para_list *choice1;
		val_para_list *choice2;
	} child1;
	simple_type_decl *child2;
	para_type_list *next;
	para_type_list(var_para_list *c1, simple_type_decl *c2, para_type_list *n):choice1(1),child2(c2),next(n) { child1.choice1 = c1; }
	para_type_list(val_para_list *c1, simple_type_decl *c2, simple_type_decl *dummy,para_type_list *n):choice1(2),child2(c2),next(n) { child1.choice2 = c1; }
	bool semanticCheck(identifier *root, int scope);
	void addParameters(identifier *root, name_list *ids, int type);
	std::string cgen();
};

struct routine_body {
	compound_stmt *child1;
	routine_body(compound_stmt *c):child1(c) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct compound_stmt {
	static int serial;
	static char buff[20];
	stmt_list *child1;
	identifier *temp;
	compound_stmt(stmt_list *c1, identifier *t):child1(c1),temp(t) {}
	compound_stmt(stmt_list *c1, int lineno):child1(c1){
		sprintf(buff,"#comp%d", serial++);
		temp = new identifier(buff, lineno);
	}//!!!
	bool semanticCheck(int scope);
	std::string cgen();
};

struct stmt {
	int choice1;//0=no child1
	int child1;
	non_label_stmt *child2;
	stmt *next;
	stmt(int c1,non_label_stmt *c2, stmt *n):choice1(1),child1(c1),child2(c2),next(n) {}
	stmt(non_label_stmt *c2, stmt *n):choice1(0),child2(c2),next(n) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct non_label_stmt {
	int choice1;
	union {
		assign_stmt *choice1;
		proc_stmt *choice2;
		compound_stmt *choice3;
		if_stmt *choice4;
		repeat_stmt *choice5;
		while_stmt *choice6;
		for_stmt *choice7;
		case_stmt *choice8;
		goto_stmt *choice9;
	} child1;
	non_label_stmt(assign_stmt *c1):choice1(1) { child1.choice1 = c1; }
	non_label_stmt(proc_stmt *c1):choice1(2) { child1.choice2 = c1; }
	non_label_stmt(compound_stmt *c1):choice1(3) { child1.choice3 = c1; }
	non_label_stmt(if_stmt *c1):choice1(4) { child1.choice4 = c1; }
	non_label_stmt(repeat_stmt *c1):choice1(5) { child1.choice5 = c1; }
	non_label_stmt(while_stmt *c1):choice1(6) { child1.choice6 = c1; }
	non_label_stmt(for_stmt *c1):choice1(7) { child1.choice7 = c1; }
	non_label_stmt(case_stmt *c1):choice1(8) { child1.choice8 = c1; }
	non_label_stmt(goto_stmt *c1):choice1(9) { child1.choice9 = c1; }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct assign_stmt {
	identifier *child1;
	int choice2;
	union {
		expression *choice1;
		struct {
			expression *child1;
			expression *child2;
		} choice2;
		struct {
			identifier *child1;
			expression *child2;
		} choice3;
	} child2;
	assign_stmt(identifier *c1, expression *c2):child1(c1),choice2(1) { child2.choice1 = c2; }
	assign_stmt(identifier *c1, expression *c21, expression *c22):child1(c1),choice2(2) { 
		child2.choice2.child1 = c21; 
		child2.choice2.child2 = c22;
	}
	assign_stmt(identifier *c1, identifier *c21, expression *c22):child1(c1),choice2(3) { 
		child2.choice3.child1 = c21; 
		child2.choice3.child2 = c22;
	}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct proc_stmt {
	int lineno;
	int choice1;
	union {
		identifier *choice1;
		struct {
			identifier *child1;
			args_list *child2;
		} choice2;
		sys_proc *choice3;
		struct {
			sys_proc *child1;
			expression_list *child2;
		} choice4;
		factor *choice5;
	} child1;
	proc_stmt(identifier *c1, int l):choice1(1), lineno(l) { child1.choice1 = c1; }
	proc_stmt(identifier *c11,args_list *c12, int l):choice1(2), lineno(l) {
		child1.choice2.child1 = c11;
		child1.choice2.child2 = c12;
	}
	proc_stmt(sys_proc *c1, int l):choice1(3), lineno(l) { child1.choice3 = c1; }
	proc_stmt(sys_proc *c11,expression_list *c12, int l):choice1(4), lineno(l) {
		child1.choice4.child1 = c11;
		child1.choice4.child2 = c12;
	}
	proc_stmt(factor *c1, int l):choice1(5), lineno(l) { child1.choice5 = c1; }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct if_stmt {
	expression *child1;
	stmt *child2;
	else_clause *child3;
	if_stmt(expression *c1,stmt *c2,else_clause *c3)
		:child1(c1),child2(c2),child3(c3) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct else_clause {
	int choice1;//0=no stmt
	stmt *child1;
	else_clause():choice1(0) {}
	else_clause(stmt *c1):choice1(1),child1(c1) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct repeat_stmt {
	stmt_list *child1;
	expression *child2;
	repeat_stmt(stmt_list *c1,expression *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct while_stmt {
	expression *child1;
	stmt *child2;
	while_stmt(expression *c1, stmt *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct for_stmt {
	identifier *child1;
	expression *child2;
	int child3;//1=to,2=downto
	expression *child4;
	stmt *child5;
	for_stmt(identifier *c1,expression *c2,int c3,expression *c4,stmt *c5)
		:child1(c1),child2(c2),child3(c3),child4(c4),child5(c5) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct case_stmt {
	expression *child1;
	case_expr_list *child2;
	case_stmt(expression *c1,case_expr_list *c2):child1(c1),child2(c2) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct case_expr {
	int choice1;
	union {
		const_value *choice1;
		identifier *choice2;
	} child1;
	stmt *child2;
	case_expr *next;
	case_expr(const_value *c1,stmt *c2,case_expr *n)
		:choice1(1),child2(c2),next(n) { child1.choice1 = c1; }
	case_expr(identifier *c1,stmt *c2,case_expr *n)
		:choice1(2),child2(c2),next(n) { child1.choice2 = c1; }
	bool semanticCheck(int scope);
	std::string cgen();
};

struct goto_stmt {
	int child1;
	goto_stmt(int c1):child1(c1) {}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct expression {
	int lineno;
	expression *child1;
	Operator child2;
	expr *child3;
	expression *next;
	Type type;
	/*
	union {
		SimpleType stype;
		identifier *idref;
		array_type_decl *array;
		record_type_decl *record;
	} value;
	*/
	u value;
	expression(expression *c1, int c2, expr *c3, expression *n, int l)
		:child1(c1),child3(c3),next(n), lineno(l) {
		switch(c2) {
		case 1: child2 = gge; break;
		case 2: child2 = ggt; break;
		case 3: child2 = lle; break;
		case 4: child2 = llt; break;
		case 5: child2 = eequal; break;
		case 6: child2 = uunequal; break;
		default: break;//error
		}
	}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct expr {
	expr *child1;
	Operator child2;
	term *child3;
	Type type;
	int lineno;
	/*
	union {
		SimpleType stype;
		identifier *idref;
		array_type_decl *array;
		record_type_decl *record;
	} value;
	*/
	u value;
	expr(expr *c1, int c2, term *c3, int l):child1(c1),child3(c3), lineno(l) {
		switch(c2) {
		case 1: child2 = pplus; break;
		case 2: child2 = mminus; break;
		case 3: child2 = oor; break;
		default: break;//error
		}
	}
	bool semanticCheck(int scope);

	std::string cgen();
};

struct term {
	term *child1;
	Operator child2;
	factor *child3;
	Type type;
	int lineno;
	/*
	union {
		SimpleType stype;
		identifier *idref;
		array_type_decl *array;
		record_type_decl *record;
	} value;
	*/
	u value;
	term(term *c1,int c2,factor *c3, int l):child1(c1),child3(c3), lineno(l) {
		switch(c2) {
		case 1: child2 = mmul; break;
		case 2: child2 = ddiv; break;
		case 3: child2 = mmod; break;
		case 4: child2 = aand; break;
		default: break;//error
		}
	}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct factor {
	int choice1;
	union {
		identifier *choice1;
		struct {
			identifier *child1;
			args_list *child2;
		} choice2;
		sys_funct *choice3;
		struct {
			sys_funct *child1;
			args_list *child2;
		} choice4;
		const_value *choice5;
		expression *choice6;
		factor *choice7;
		factor *choice8;
		struct {
			identifier *child1;
			expression *child2;
		} choice9;
		struct {
			identifier *child1;
			identifier *child2;
		} choice10;
	} child1;
	Type type;
	/*
	union {
		SimpleType stype;
		identifier *idref;
		array_type_decl *array;
		record_type_decl *record;
	} value;
	*/
	u value;
	factor(identifier *c1):choice1(1) { child1.choice1 = c1; }
	factor(identifier *c11,args_list *c12):choice1(2) { 
		child1.choice2.child1 = c11;
		child1.choice2.child2 = c12;
	}
	factor(sys_funct *c1):choice1(3) { child1.choice3 = c1; }
	factor(sys_funct *c11,args_list *c12):choice1(4) {
		child1.choice4.child1 = c11;
		child1.choice4.child2 = c12;		
	}
	factor(const_value *c1):choice1(5) { child1.choice5 = c1; }
	factor(expression *c1):choice1(6) { child1.choice6 = c1; }
	factor(factor *c1):choice1(7) { child1.choice7 = c1; }
	factor(factor *c1, factor *dummy):choice1(8) { child1.choice8 = c1; }
	factor(identifier *c11,expression *c12, expression *dummy):choice1(9) {
		child1.choice9.child1 = c11;
		child1.choice9.child2 = c12;		
	}
	factor(identifier *c11,identifier *c12):choice1(10) {
		child1.choice10.child1 = c11;
		child1.choice10.child2 = c12;		
	}
	bool semanticCheck(int scope);
	std::string cgen();
};

struct sys_proc {
	SysProc child1;
	sys_proc(SysProc s):child1(s) {}
	std::string cgen(SimpleType t);
};

struct sys_funct {
	SysFunct child1;
	std::string cgen();
};

}

#endif
