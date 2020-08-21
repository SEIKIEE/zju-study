#include "declare.h"
#include "symbolTable.h"
#include "util.h"

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;
//using namespace lwd;

namespace lwd {

void lower(char str[]) {
	char * p= str;
	while(*p!='\0') {
		*p = *p <= 'Z' && *p >= 'A'? *p-'A'+'a' : *p;
		p++;
	}
}

program *parse() {
	yyparse();
	return savedRoot;
}

void reportNameCollision(lwd::identifier *id, int scope) {
	lwd::identifier *temp = gtable.lookUp(id, scope);
	printf("Inside reportNameCollision(), id = %s, scope = %d; prev_id = %s, prev_scope = %d\n", id->name.c_str(), id->scope, temp->name.c_str(), temp->scope); 
	assert(temp->scope==id->scope&&temp->name==id->name);
	fprintf(stderr, "error at line %d : %s was previously defined at line %d.\n", 
		 id->lineno, temp->name.c_str(), temp->lineno);
}

void reportNameMissing(lwd::identifier *id, int scope) {
	assert(gtable.lookUp(id, scope)==NULL);
	fprintf(stderr, "error at line %d : %s is used but never defined.\n", 
		id->lineno, id->name.c_str());
}

void reportTypeMismatch(lwd::identifier *id, int scope) {
	if(id->type==ssimple_type&&id->stype==iidref) {
		assert(id->value.idref->typedefinition==false);
		fprintf(stderr, "error at line %d : need %s be a type, but was previously defined not.\n", 
			id->lineno, id->value.idref->name.c_str());
	}
}

void reportTypeMismatch(int lineno, identifier *id, expression *exp) {
	assert(!typeEqual(id, exp));
	fprintf(stderr, "error at line %d : type mismatch between %s and %s.\n", 
		lineno, typeString(id).c_str(), typeString(exp).c_str());
}

void reportTypeMismatch(int lineno, expression *exp, SimpleType stype) {
	string t;
	switch(stype) {
	case iinteger: t = "integer"; break;
	case rreal: t = "real"; break;
	case cchar: t = "char"; break;
	case sstring: t = "string"; break;
	default: break;//error
	}
	fprintf(stderr, "error at line %d : type mismatch, need %s, found %s\n", 
		lineno, t.c_str(), typeString(exp).c_str());
}

void reportTypeMismatch(int lineno, identifier *id, Type type) {
	string t;
	switch(type) {
	case pprocedure: t = "procedure"; break;
	case pprogram: t = "program"; break;
	case ffunction: t = "function"; break;
	case ccallable: t = "callable"; break;
	case ssimple_type: t = "simple_type"; break;
	case aarray_type: t = "array_type"; break;
	default: break; //error
	}
	fprintf(stderr, "error at line %d : type mismatch, need %s, found %s\n", 
		lineno, t.c_str(), typeString(id).c_str());

}

void reportTypeMismatch(int lineno, expression *exp1, expr *exp2) {
	assert(!typeEqual(exp1, exp2));
	fprintf(stderr, "error at line %d : type mismatch between %s and %s.\n", 
		lineno, typeString(exp1).c_str(), typeString(exp2).c_str());

}

std::string typeString(identifier *id) {
	return tString(id->type, id->stype);
}

std::string typeString(expression *exp) {
	return tString(ssimple_type, exp->value.stype);//support only simple type now
}

std::string typeString(expr *exp) {
	return tString(ssimple_type, exp->value.stype);//support only simple type now
}

std::string tString(Type type, SimpleType stype) {
	switch(type) {
	case ssimple_type:
	case ffunction:
	case aarray_type:
		switch(stype) {
		case iinteger: return string("integer");
		case rreal: return string("real");
		case cchar: return string("char");
		case sstring: return string("string");
		}
	case rrecord_type: //not implemented
	default: return string("tString() error");//error
	}
}

/****************************/
bool typeEqual(identifier *id, expression *exp) {
	//cout << id->name << " : " << id->type << id->stype << " " << exp->value.stype << endl;
	return tEqual((id->type==ffunction||id->type==aarray_type)?ssimple_type:id->type, id->stype, ssimple_type, exp->value.stype);//support simple type only now
}

bool typeEqual(identifier *id1, identifier *id2) {
	//cout << id1->name << " : " << id1->type << id1->stype << " " << id2->name << " : " << id2->type << id2->stype << endl;
	return tEqual(id2->type==ffunction?ssimple_type:id2->type, id1->stype, 
				id2->type==ffunction?ssimple_type:id2->type, id2->stype);
}

bool typeEqual(expression *exp1, expression *exp2) {
	return tEqual(ssimple_type, exp1->value.stype, ssimple_type, exp2->value.stype);//support simple type only now
}

bool typeEqual(expression *exp1, expr *exp2) {
	return tEqual(exp1->type, exp1->value.stype, exp2->type, exp2->value.stype);//support simple type only now
}

bool tEqual(const Type &t1, const SimpleType &s1, const Type &t2, const SimpleType &s2) {
	return t1==t2 && s1==s2;
}

bool parametersMatch(identifier *id, args_list *args, int lineno) {
	return true;//not implemented
	/*
	expression *exp = args;
	for(int i=0; i<id->paras->size(); ++i) {
		if(exp==NULL) {
			fprintf(stderr, "error at line %d : parameter number incorrect at calling %s.\n", 
				lineno, id->name.c_str());
			return false;
		}
		if(!typeEqual(gtable.lookUp(id->paras->at(i), gtable.lookUpScope(id)), exp)) {
			fprintf(stderr, "error at line %d : parameter types mismatch at calling %s.\n", 
				lienno, id->name.c_str());
			return false;
		}
		exp = exp->next;
	}
	if(exp!=NULL) {
		fprintf(stderr, "error at line %d : parameter number incorrect at calling %s.\n", 
			lineno, id->name.c_str());
		return false;
	}
	return true;
	*/
}

}
