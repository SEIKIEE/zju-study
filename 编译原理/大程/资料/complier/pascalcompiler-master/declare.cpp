#include "declare.h"
#include "symbolTable.h"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using namespace lwd;

int compound_stmt::serial = 0;
char compound_stmt::buff[20];

static int currentScope = 0;
static int sbCounter = 0;

symbolTable lwd::gtable;
lwd::program *lwd::savedRoot;
bool lwd::error = false;

void lwd::stprint(SimpleType s) {
	switch(s) {
		case iinteger: printf("integer\n"); break;
		case rreal: printf("real\n"); break;
		case cchar: printf("char\n"); break;
		case sstring: printf("string\n"); break;
		case ssys_con: printf("sys_con\n"); break;
		case iidref: printf("idref\n"); break;
		case eenum: printf("enum\n"); break;
		case rrange: printf("range\n"); break;
		case iidrange: printf("idrange\n"); break;
		case bbool: printf("bool\n"); break;
		default: printf("error\n"); break;
	}
}

	bool program::semanticCheck(int scope) {
		bool temp1 = child1->semanticCheck(this, scope);
		bool temp2 = child2->semanticCheck(gtable.insertScope(this, scope));
		
#ifdef SEMANTIC_DEBUG
		printf("\n------------------------------------\n\n");
		printf("all scopes : \n");
		gtable.printScope();
		printf("\n------------------------------------\n\n");
		printf("all identifiers : \n");
		gtable.printIdentifier();
		printf("\n------------------------------------\n\n");
		printf("all constants : \n");
		gtable.printConst();
		fflush(stdout);
		cout << endl;
#endif
		return temp1&&temp2;
	}

	bool program_head::semanticCheck(program *root, int scope) { 
		child1->constant = true; 
		child1->typedefinition = false;
		child1->type = pprogram;
		child1->value.prog = root;
		child1->scope = scope;
		child1->offset = 8;
		bool temp = gtable.insertID(child1, scope); 
		if(!temp)
			reportNameCollision(child1, scope);
		return temp;
	}

	bool routine::semanticCheck(int scope) { 
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = child2->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool sub_routine::semanticCheck(int scope) { 
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = child2->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool routine_head::semanticCheck(int scope) {
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = child2->semanticCheck(scope);
		bool temp3 = child3->semanticCheck(scope);
		bool temp4 = child4->semanticCheck(scope);
		bool temp5 = child5->semanticCheck(scope);
		return temp1&&temp2&&temp3&&temp4&&temp5;
	}
	
	bool const_part::semanticCheck(int scope) { 	
		return child1==NULL?true:child1->semanticCheck(scope); 
	}

	bool const_expr::semanticCheck(int scope) { 	
		child2->semanticCheck(child1, scope);
		bool temp1 = gtable.insertID(child1, scope); 
		if(!temp1)
			reportNameCollision(child1, scope);
		gtable.addConst(child1);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool const_value::semanticCheck(identifier *id, int scope) {
		id->typedefinition = false;
		id->constant = true;
		id->type = ssimple_type;
		id->scope = scope;
		switch(choice1) {
		case 1: id->stype = iinteger; id->value.i = child1.choice1; break;
		case 2: id->stype = rreal; id->value.f = child1.choice2; break;
		case 3: id->stype = cchar; id->value.c = child1.choice3; break;
		case 4: id->stype = sstring; id->value.s = child1.choice4; break;
		case 5: id->stype = ssys_con; /*to be continued*/break;
		default: break;//error
		}
		return true;
	}

	bool type_part::semanticCheck(int scope) { 
		return child1==NULL?true:child1->semanticCheck(scope); 
	}

	bool type_definition::semanticCheck(int scope) {
		child2->semanticCheck(child1, scope, 1);
		bool temp1 = gtable.insertID(child1, scope);//1 stands for type definition
		if(!temp1)
			reportNameCollision(child1, scope);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool type_decl::semanticCheck(identifier *id, int scope, int type) {//1 stands for type definition, 2stands for variable definition
		switch(choice1) {
		case 1: return child1.choice1->semanticCheck(id, scope, type);
		case 2: return child1.choice2->semanticCheck(id, scope, type);
		case 3: return child1.choice3->semanticCheck(id, scope, type);
		default: break;//error
		}
		return true;
	}

	bool simple_type_decl::semanticCheck(identifier *id, int scope, int type) {
		id->constant = id->typedefinition = type==1;
		id->scope = scope;
		id->type = ssimple_type;
		switch(choice1) {
		case 1: id->stype = child1.choice1->child1; /*cout << id->name << " type : " << id->stype << endl;*/ break;
		case 2: //to be continued
		case 3: 
		case 4:
		case 5:
		default: break;//error
		}
		/*cout << id->name << " finished simple type" << endl;*/
		return true;
	}

	bool simple_type_decl::semanticCheck(name_list *ids, int scope, int type) {
		while(ids!=NULL) {
			semanticCheck(ids->child2, scope, type);
			ids = ids->child1;
		}
		return true;
	}

	bool type_decl::semanticCheck(name_list *ids, int scope, int type) {//1 stands for type definition, 2stands for variable definition
		bool temp1 = ids->child1==NULL?true:semanticCheck(ids->child1, scope, type);
		bool temp2 = semanticCheck(ids->child2, scope, type);
		return temp1&&temp2;
	}
/*********************************************/
	bool array_type_decl::semanticCheck(identifier *id, int scope, int type) {
		id->scope = scope;
		id->typedefinition = id->constant = type==1;
		id->type = aarray_type;
		id->value.array = this;
		//bool temp = gtable.insertID(id, scope);
		//if(!temp)
		//	reportNameCollision(id, scope);
		assert(child1->choice1==4);
		assert(child2->choice1==1);
		bool temp2 = child1->child1.choice4->semanticCheck();
		return temp2;
	}
	
/*******************************/
	bool range::semanticCheck() {
		if(child1->choice1!=1||child2->choice1!=1) {
			printf("Error at line %d : can only use integer to index array.\n", lineno);
			return false;
		}
		size = child2->child1.choice1 - child1->child1.choice1 + 1;
		assert(size>0);
		return true;
	}

	bool name_list::semanticCheck(int scope) { 
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		scopeValue s = gtable.getScope(scope);
		switch(s.choice) {
		case 1: {
			program *pp = s.type.type1; 
			child2->offset = pp->child1->child1->offset; 
			pp->child1->child1->offset +=4; 
			break;
		}
		case 2: {
			function_decl *fp = s.type.type2; 
			child2->offset = fp->child1->child1->offset; 
			fp->child1->child1->offset+=4; 
			break;
		}
		case 3: {
			procedure_decl *rp = s.type.type3; 
			child2->offset = rp->child1->child1->offset; 
			rp->child1->child1->offset+=4; 
			break;
		}
		default: break; //error
		}
		bool temp2 = gtable.insertID(child2, scope);
		if(!temp2)
			reportNameCollision(child2, scope);
		return temp1&&temp2;
	}

	bool var_part::semanticCheck(int scope) { 
		return child1==NULL?true:child1->semanticCheck(scope); 
	}

	bool var_decl::semanticCheck(int scope) {
		child2->semanticCheck(child1, scope, 2);//2 stands for variable definition
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool routine_part::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->nameCheck(scope);
		bool temp2 = child2==NULL?true:child2->nameCheck(scope);
		if(!temp1||!temp2)
			return false;
		bool temp3 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp4 = child2==NULL?true:child2->semanticCheck(scope);
		return temp3&&temp4;
	}

	bool function_decl::nameCheck(int scope) { 
		bool temp1 = child1->semanticCheck(this, scope);
		bool temp2 = next==NULL?true:next->nameCheck(scope);
		//reversePosition(gtable.lookUpScope(this));
		return temp1&&temp2;
	}

	void function_decl::reversePosition(int scope) {
		int off = child1->child1->offset;
		const std::vector<std::string> *lst = child1->child1->paras;
		assert(lst!=NULL);
		for(int i=0; i< lst->size(); ++i) {
			identifier *id = gtable.lookUp(lst->at(i), scope);
			assert(id!=NULL);
			int no = (id->offset-8)/4+1;
			id->offset = off-no*4;
		}
		/*
		cout << "function " << child1->child1->name << " : size->" << child1->child1->offset << endl;
		for(int i=0; i< lst->size(); ++i) {
			identifier *id = gtable.lookUp(lst->at(i), scope);
			cout << "identifier " << id->name << " : offset->" << id->offset << endl;
		}
		*/
	}

	bool function_decl::semanticCheck(int scope) {
		int temp = gtable.lookUpScope(this); 		
		//printf("!!!%d\n", scope);
		//printf("!!!%d\n", temp);
		bool temp1 = child2->semanticCheck(temp);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
#ifdef SEMANTIC_DEBUG
		printf("stack size of %s : %d\n", child1->child1->name.c_str(), gtable.lookUp(child1->child1, scope)->offset);
		fflush(stdout);
#endif
		return temp1&&temp2;
	}

	bool function_head::semanticCheck(function_decl *root, int scope) {
		child1->scope = scope;
		child1->value.func = root;
		child3->semanticCheck(child1, scope, 2);
		child1->type = ffunction;
		child1->constant = false;
		child1->offset = 8;
		if(!gtable.insertID(child1, scope)) {
			reportNameCollision(child1, scope);
			return false;
		}
		int temp = gtable.insertScope(root, scope);
		return child2==NULL?true:child2->semanticCheck(child1, temp);
	}

	bool procedure_decl::nameCheck(int scope) { 
		bool temp1 = child1->semanticCheck(this, scope);
		bool temp2 = next==NULL?true:next->nameCheck(scope);
		//reversePosition(gtable.lookUpScope(this));
		return temp1&&temp2;
	}

	void procedure_decl::reversePosition(int scope) {
		int off = child1->child1->offset;
		const std::vector<std::string> *lst = child1->child1->paras;
		assert(lst!=NULL);
		for(int i=0; i< lst->size(); ++i) {
			identifier *id = gtable.lookUp(lst->at(i), scope);
			assert(id!=NULL);
			int no = (id->offset-8)/4+1;
			id->offset = off-no*4;
		}
		/*
		cout << "procedure " << child1->child1->name << " : size->" << child1->child1->offset << endl;
		for(int i=0; i< lst->size(); ++i) {
			identifier *id = gtable.lookUp(lst->at(i), scope);
			cout << "identifier " << id->name << " : offset->" << id->offset << endl;
		}
		*/
	}

	bool procedure_decl::semanticCheck(int scope) {
		int temp = gtable.lookUpScope(this); 		
		//printf("!!!%d\n", scope);
		//printf("!!!%d\n", temp);
		bool temp1 = child2->semanticCheck(temp);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
#ifdef SEMANTIC_DEBUG
		printf("stack size of %s : %d\n", child1->child1->name.c_str(), gtable.lookUp(child1->child1, scope)->offset);
		fflush(stdout);
#endif
		return temp1&&temp2;
	}

	bool procedure_head::semanticCheck(procedure_decl *root, int scope) {
		child1->scope = scope;
		child1->type = pprocedure;
		child1->value.proc = root;
		child1->constant = true;
		child1->typedefinition = false;
		child1->paras = NULL;
		child1->offset = 8;
		if(!gtable.insertID(child1, scope)) {
			reportNameCollision(child1, scope);
			return false;
		}
		int temp =  gtable.insertScope(root, scope);
		return child2==NULL?true:child2->semanticCheck(child1, temp);
	}

	bool parameters::semanticCheck(identifier *root, int scope) {
		if(child1==NULL) {
			root->paras = NULL;
			return true; 
		}
		root->paras = new std::vector<std::string>();
		return child1->semanticCheck(root, scope);
	}

	bool para_type_list::semanticCheck(identifier *root, int scope) {
		bool temp1, temp2, temp3;
		if(choice1==1) {
			addParameters(root, child1.choice1, 1);
			temp1 = child2->semanticCheck(child1.choice1, scope, 2);
			temp2 = child1.choice1->semanticCheck(scope);
		}
		else {
			addParameters(root, child1.choice2, 2);
			temp1 = child2->semanticCheck(child1.choice1, scope, 2);
			temp2 = child1.choice2->semanticCheck(scope);
		}
		temp3 = next==NULL?true:next->semanticCheck(root, scope);
#ifdef SEMANTIC_DEBUG		
		printf("Parameters of %s : \n", root->name.c_str());
		for(int i=0; i< root->paras->size(); ++i) {
			printf("%s ", root->paras->at(i).c_str());
		}
		printf("\n");
		fflush(stdout);
#endif
		return temp1&&temp2&&temp3;
	}

	void para_type_list::addParameters(identifier *root, name_list *ids, int type) {//1 for passByReference
		if(ids->child1!=NULL)
			addParameters(root, ids->child1, type);
		root->paras->push_back(ids->child2->name);
		ids->child2->passByReference = type==1;
	}

	bool routine_body::semanticCheck(int scope) {
		return child1==NULL?true:child1->semanticCheck(scope);
	}

	bool compound_stmt::semanticCheck(int scope) {
		return child1==NULL?true:child1->semanticCheck(scope);
	}
/**************************************/
	bool assign_stmt::semanticCheck(int scope) {
		identifier *id = gtable.lookUp(child1, scope);
		if(id==NULL) {
			reportNameMissing(child1, scope);
			return false;
		}
		if(id->constant) {
			fprintf(stderr, "Error at line %d : can't assign value to constant identifier '%s'.\n",
				id->lineno, id->name.c_str());
			return false;
		}
		bool temp;
		switch(choice2) {
		case 1:	{
			if(!child2.choice1->semanticCheck(scope))
				return false;
			temp = typeEqual(id, child2.choice1);
			if(!temp)
				reportTypeMismatch(child1->lineno, id, child2.choice1);
			return temp;
		}
		case 2: {
			bool temp1 = child2.choice2.child1->semanticCheck(scope);
			bool temp2 = child2.choice2.child2->semanticCheck(scope);
			if(!temp1||!temp2)
				return false;
			if(child2.choice2.child1->type!=ssimple_type||child2.choice2.child1->value.stype!=iinteger) {
				reportTypeMismatch(child1->lineno, child2.choice2.child1, iinteger);
				return false;
			}
			//for simplicity, if id is an array, assume id is an array of systype, and systype is stored in stype
			if(!typeEqual(id, child2.choice2.child2)) {//need judge id is an array
				reportTypeMismatch(child1->lineno, id, child2.choice2.child2);
				return false;
			}
			return temp1&&temp2;
		}
		case 3: {//not supported
			identifier *idd = gtable.lookUp(child2.choice3.child1, scope);
			child2.choice3.child2->semanticCheck(scope);
			//no type check
			if(idd==NULL) {
				reportNameMissing(child2.choice3.child1, scope);
				return false;
			}
			return true;
		}
		default: return false; //error
		}
	}
/*********************************************/
	bool proc_stmt::semanticCheck(int scope) {
		switch(choice1) {
		case 1: {
			identifier *id = gtable.lookUp(child1.choice1, scope);
			if(id==NULL) {
				reportNameMissing(child1.choice1, scope);
				return false;
			}
			return (id->type==ffunction||id->type==pprocedure)&&id->paras==NULL;
		}
		case 2: {
			identifier *id = gtable.lookUp(child1.choice2.child1, scope);
			if(id==NULL) {
				reportNameMissing(child1.choice2.child1, scope);
				return false;
			} 
			if(id->type!=ffunction&&id->type!=pprocedure) {
				reportTypeMismatch(child1.choice2.child1->lineno, id, ccallable);
				return false;
			}
			if(!child1.choice2.child2->semanticCheck(scope))
				return false;
			//return parametersMatch(id, child1.choice2.child2, child1.choice2.child1->lineno);
			//no arguments check
			return true;
		}
		case 3: //system procedure with no parameters
			return true;
		case 4:	// write writeln
			return child1.choice4.child2->semanticCheck(scope);
		case 5: {
			if(!child1.choice5->semanticCheck(scope))
				return false;
			if(child1.choice5->choice1!=1&&child1.choice5->choice1!=9) {
				printf("Error at line %d : expression inside read() is not assignable.\n", lineno);//!!!
				return false;
			}
			return true;
		}
		default: return false; // error
		}
	}

	bool if_stmt::semanticCheck(int scope) {
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = child2==NULL?true:child2->semanticCheck(scope);
		bool temp3 = child3==NULL?true:child3->semanticCheck(scope);
		return temp1&&temp2&&temp3;
	}

	bool else_clause::semanticCheck(int scope) {
		return choice1==0?true:child1->semanticCheck(scope);
	}

	bool repeat_stmt::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp2 = child2==NULL?true:child2->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool while_stmt::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp2 = child2==NULL?true:child2->semanticCheck(scope);
		return temp1&&temp2;
	}

/*****************************************/
	bool for_stmt::semanticCheck(int scope) {
		bool temp1 = gtable.lookUp(child1, scope)!=NULL;
		bool temp2 = child2==NULL?true:child2->semanticCheck(scope);
		bool temp3 = child4==NULL?true:child4->semanticCheck(scope);
		bool temp4 = child5==NULL?true:child5->semanticCheck(scope);
		if(!temp1)
			reportNameMissing(child1, scope);
		if(!temp2||!temp3) return false;
		temp2 = child2==NULL?true:
							(child2->type==ssimple_type&&(child2->value.stype==iinteger||child2->value.stype==cchar));
		temp3 = child4==NULL?true:
							(child4->type==ssimple_type&&(child4->value.stype==iinteger||child4->value.stype==cchar));
		return temp1&&temp2&&temp3&&temp4&&typeEqual(child2, child4);
	}

	bool case_stmt::semanticCheck(int scope) {
		bool temp1 = child1->semanticCheck(scope);
		bool temp2 = child2->semanticCheck(scope);
		return temp1&&temp2;
	}

	bool case_expr::semanticCheck(int scope) {
		bool temp1;
		switch(choice1) {
		case 1: 
			temp1 = true; 
			break;
		case 2: {
			identifier *id = gtable.lookUp(child1.choice2, scope);
			if(id==NULL) {
				temp1=false;
				reportNameMissing(child1.choice2, scope);
				break;
			}
			if(!id->constant) {
				fprintf(stderr, "Error at line %d : %s is not a constant value.\n", 
					id->lineno, id->name.c_str());
				temp1=false;
				break;
			}
			temp1 = true;
			break;
		}
		default: temp1=false; break;//error
		}
		bool temp2 = child2->semanticCheck(scope);
		bool temp3 = next==NULL?true:next->semanticCheck(scope);
		return temp1&&temp2&&temp3;
	}

	bool expression::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp2 = child3->semanticCheck(scope);
		bool temp3 = next==NULL?true:next->semanticCheck(scope);
		
		if(!temp1||!temp2)
			return false;
		
		if(child1!=NULL&&!typeEqual(child1, child3)) {
			//reportTypeMismatch(child1, child3);
			return false;
		}

		type = child3->type;
		value = child3->value;
			//printf("expression");
			//stprint(value.stype);
		return temp3;
	}

	bool expr::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp2 = child3->semanticCheck(scope);
		if(!temp1||!temp2)
			return false;
		// no type check
		type = child3->type;
		value = child3->value;
			//printf("expr");
			//stprint(value.stype);
		return true;
	}

	bool term::semanticCheck(int scope) {
		bool temp1 = child1==NULL?true:child1->semanticCheck(scope);
		bool temp2 = child3->semanticCheck(scope);
		if(!temp1||!temp2)
			return false;
		// no type check
		type = child3->type;
		value = child3->value;
		//	printf("term");
		//	stprint(value.stype);
		return true;
	}

/**************************************/
	bool factor::semanticCheck(int scope) {
		switch(choice1) {
		case 1: {
			identifier *id = gtable.lookUp(child1.choice1, scope);
			if(id==NULL) {
				reportNameMissing(child1.choice1, scope);
				return false;
			}
			//no identifier type (proc func or var) check 
			type = id->type; 
			value.stype = id->stype;
			return true;
		}
		case 2: {
			identifier *id = gtable.lookUp(child1.choice2.child1, scope);
			if(id==NULL) {
				reportNameMissing(child1.choice2.child1, scope);
				return false;
			}
			//no identifier type (proc func or var) check 
			type = id->type; 
			value.stype = id->stype;
			return child1.choice2.child2->semanticCheck(scope);		
		}	
		case 3: return true;//to be implemented
		case 4: return child1.choice4.child2->semanticCheck(scope); //to beimplemented
		case 5: {
			type = ssimple_type;
			switch(child1.choice5->choice1) {
			case 1: value.stype = iinteger; break;
			case 2: value.stype = rreal; break;
			case 3: value.stype = cchar; break;
			case 4: value.stype = sstring; break;
			default: break; //error
			}
			//printf("factor");
			//stprint(value.stype);
			return true;
		}
		case 6:
			if(child1.choice6->semanticCheck(scope)) {
				type = child1.choice6->type;
				value = child1.choice6->value;
				return true;
			}
			return false;
		case 7://not feasible
			if(child1.choice7->semanticCheck(scope)) {
				type = child1.choice6->type;
				value = child1.choice6->value;
				return true;
			}
			return false;
		case 8:
			if(child1.choice8->semanticCheck(scope)) {
				type = child1.choice6->type;
				value = child1.choice6->value;
				return true;
			}
			return false;
		case 9: {
			identifier *id = gtable.lookUp(child1.choice9.child1, scope);
			if(id==NULL) {
				reportNameMissing(id, scope);
				return false;
			}
			if(id->type!=aarray_type) {//看ID是否为数组
				printf("Error at line %d : %s is not array type.\n", child1.choice9.child1->lineno, child1.choice9.child1->name.c_str());
				return false;
			}
			if(!child1.choice9.child2->semanticCheck(scope))//看expression semanticCheck
				return false;
			if(child1.choice9.child2->type!=ssimple_type||child1.choice9.child2->value.stype!=iinteger) {//看[]内是否为integer
				printf("Error at line %d : expression inside '[]' is not an integer.\n", child1.choice9.child2->lineno);//!!!
				return false;
			}
			return true;
		}
		case 10: return true;//to be implemented
		default: return false; //error
		}
	}

	bool stmt::semanticCheck(int scope) {
		bool temp0 = choice1==0?true:gtable.addLabel(child1);
#ifdef SEMANTIC_DEBUG
		if(choice1)
			printf("new label %d.\n", child1);		
#endif
		if(!temp0)
			fprintf(stderr, "Error : label %d redefined.\n", child1);
		bool temp1 = child2->semanticCheck(scope);
		bool temp2 = next==NULL?true:next->semanticCheck(scope);
		return temp0&&temp1&&temp2;
	}

	bool non_label_stmt::semanticCheck(int scope) {
		switch(choice1) {
		case 1: return child1.choice1->semanticCheck(scope);
		case 2: return child1.choice2->semanticCheck(scope);
		case 3: return child1.choice3->semanticCheck(scope);
		case 4: return child1.choice4->semanticCheck(scope);
		case 5: return child1.choice5->semanticCheck(scope);
		case 6: return child1.choice6->semanticCheck(scope);
		case 7: return child1.choice7->semanticCheck(scope);
		case 8: return child1.choice8->semanticCheck(scope);
		case 9: return child1.choice9->semanticCheck(scope);
		default: return false;//error
		}
	}

	bool goto_stmt::semanticCheck(int scope) {
		gtable.addUsedLabel(child1);
		return true;
	}

string program::cgen() {
	string res;
	int originalScope = currentScope;

	// program_head
	res += child1->cgen();

	currentScope = gtable.lookUpScope(this);
	// routine
	res += child2->cgen();

	currentScope = originalScope;

	return res;
}

string program_head::cgen() {
	string res;
	char temp[30];

	sprintf(temp, "%d", currentScope);
	string label = child1->name + string(temp);

	// 打印标号，压栈 ra
	res += label + ":\n";
	res += "sw $ra, 0($fp)\n";

	return res;
}

string routine::cgen() {
	string res;

	res += child2->cgen();	// routine_body
	res += "addi $sp, $sp, 100\n";		// System stack clean
	res += "addi $v0, $zero, 17\n";		// Exit
	res += "syscall\n";
	res += child1->cgen();	// routine_head

	return res;
}

string routine_head::cgen() {
	string res;

	res += child1->cgen();
	res += child2->cgen();
	res += child3->cgen();
	res += child4->cgen();
	res += child5->cgen();

	return res;
}

string label_part::cgen() {
	string res;

	res += "";

	return res;
}

string const_part::cgen() {
	string res;

	res += "";

	return res;
}

string const_expr::cgen() {
	string res;

	res += "";

	return res;
}

string const_value::cgen() {
	string res;

	res += "";

	return res;
}

string sys_con::cgen() {
	string res;

	res += "";

	return res;
}

string type_part::cgen() {
	string res;

	res += "";

	return res;
}

string type_definition::cgen() {
	string res;

	res += "";

	return res;
}

string type_decl::cgen() {
	string res;

	res += "";

	return res;
}

string simple_type_decl::cgen() {
	string res;

	res += "";

	return res;
}

string sys_type::cgen() {
	string res;

	res += "";

	return res;
}

string range::cgen() {
	string res;

	res += "";

	return res;
}

string idrange::cgen() {
	string res;

	res += "";

	return res;
}

string array_type_decl::cgen() {
	string res;

	res += "";

	return res;
}

string record_type_decl::cgen() {
	string res;

	res += "";

	return res;
}

string field_decl::cgen() {
	string res;

	res += "";

	return res;
}

string name_list::cgen() {
	string res;

	res += "";
	// TODO: NAME_LIST

	return res;
}

string var_part::cgen() {
	string res;

	res += "";

	return res;
}

string var_decl::cgen() {
	string res;

	res += "";

	return res;
}

string routine_part::cgen() {
	string res;

	function_decl_list * fptr = child1;
	while (fptr != NULL) {
		res += fptr->cgen();
		fptr = fptr->next;
	}

	procedure_decl_list * pptr = child2;
	while (pptr != NULL) {
		res += pptr->cgen();
		pptr = pptr->next;
	}

	return res;
}

string function_decl::cgen() {
	string res;
	int originalScope = currentScope;

	// function_head
	res += child1->cgen();

	currentScope = gtable.lookUpScope(this);
	// sub_routine
	res += child2->cgen();

	currentScope = originalScope;

	return res;
}

string function_head::cgen() {
	string res;
	char temp[30];

	sprintf(temp, "%d", currentScope);
	string label = child1->name + string(temp);

	// 打印标号，压栈 ra
	res += label + ":\n";
	res += "sw $ra, 0($fp)\n";

	return res;
}

string procedure_decl::cgen() {
	string res;

	int originalScope = currentScope;

	// procedure_head
	res += child1->cgen();

	currentScope = gtable.lookUpScope(this);
	// sub_routine
	res += child2->cgen();

	currentScope = originalScope;

	return res;
}

string procedure_head::cgen() {
	string res;
	char temp[30];

	sprintf(temp, "%d", currentScope);
	string label = child1->name + string(temp);

	// 打印标号，压栈 ra
	res += label + ":\n";
	res += "sw $ra, 0($fp)\n";

	return res;
}

string parameters::cgen() {
	string res;

	res += "";

	return res;
}

string para_type_list::cgen() {
	string res;

	res += "";

	return res;
}

string sub_routine::cgen() {
	string res;

	res += child2->cgen();	// routine_body
	res += "lw $ra, 0($fp)\n";
	res += "jr $ra\n";		// return
	res += child1->cgen();	// routine_head

	return res;
}

string routine_body::cgen() {
	string res;

	res += child1->cgen();

	return res;
}

string sys_proc::cgen(SimpleType choice1) {
	string res;

	//res += child1->cgen();

	switch (choice1) {
		case  iinteger: {	// int
			res += "add $t0, $zero, $v0\n";
			res += "print_int($t0)\n";
			break;}
		case  rreal: {	// float
			res += "add.s $f12, $f31, $f0\n";
			res += "li $v0, 2\n";
			res += "syscall\n";
			break;}
		case  cchar: {	// char
			res += "add $t0, $zero, $v0\n";
			res += "print_char($t0)\n";
			break;}
		default:{
			break;}	// Error
	}
	
	return res;
}

string sys_funct::cgen() {
	string res;

	res += "";

	return res;
}

string compound_stmt::cgen() {
	string res;

	stmt_list * ptr = child1;
	while (ptr != NULL) {
		res += ptr->cgen();
		ptr = ptr->next;
	}

	return res;
}

/******************************************/
/* CZ                                     */
/* stmt, non_label_stmt, assign_stmt,     */
/* proc_stmt, expression, expr, term      */
/******************************************/
string stmt::cgen() {
	string res;
	char temp[30];

	if (choice1) {	// 有标号
		sprintf(temp, "%d", child1);
		res += "Label_" + string(temp) + ":\n";
	}
	res += child2->cgen();

	return res;
}

string non_label_stmt::cgen() {
	string res;

	switch (choice1) {
		case  1: { res += child1.choice1->cgen(); break;}
		case  2: { res += child1.choice2->cgen(); break;}
		case  3: { res += child1.choice3->cgen(); break;}
		case  4: { res += child1.choice4->cgen(); break;}
		case  5: { res += child1.choice5->cgen(); break;}
		case  6: { res += child1.choice6->cgen(); break;}
		case  7: { res += child1.choice7->cgen(); break;}
		case  8: { res += child1.choice8->cgen(); break;}
		case  9: { res += child1.choice9->cgen(); break;}
		default: {break;}	// Error
	}

	return res;
}

string assign_stmt::cgen() {
	string res;
	char temp[30];

	switch (choice2) {
		case  1: {	// ID
			res += child2.choice1->cgen();
			// 查 child1 地址
			identifier *newChild1 = gtable.lookUp(child1, currentScope);
			if (newChild1->type == ffunction) {
			}
			else {
				int scopePtr = currentScope;
				res += "add $t0, $zero, $fp\n";
				while (scopePtr != newChild1->scope) {
					res += "lw $t0, 4($t0)\n";
					scopePtr = (gtable.getScope(scopePtr)).parent;
				}
				sprintf(temp, "%d", newChild1->offset);
				res += "addi $t0, $t0, " + string(temp) + "\n";
				if(newChild1->stype == rreal){
					res += "swc1 $f0, 0($t0)\n";
				}
				else{
					res += "sw $v0, 0($t0)\n";
				}
			}

			break;}
		case  2: {	// Array
			res += child2.choice2.child2->cgen();
			res += "addi $sp, $sp, -4\n";
			res += "sw   $v0, 0($sp)\n";

			// 计算数组偏移地址 -> $v0
			res += child2.choice2.child1->cgen();

			// 查 数组首 地址 -> $t0
			identifier *newChild1 = gtable.lookUp(child1, currentScope);
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newChild1->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = (gtable.getScope(scopePtr)).parent;
			}
			sprintf(temp, "%d", newChild1->offset);
			res += "addi $t0, $t0, " + string(temp) + "\n";
			res += "lw   $t0, 0($t0)\n";

			// 计算数组元素地址 -> $t0
			res += "sll $v0, $v0, 2\n";
			res += "add $t0, $t0, $v0\n";

			// 赋值
			res += "lw   $v0, 0($sp)\n";
			res += "addi $sp, $sp, 4\n";
			res += "sw   $v0, 0($t0)\n";

			break;}
		case  3: {
			res += child2.choice3.child2->cgen();
			// TODO:
			break;}
		default: {break;}	// Error
	}

	

	return res;
}

string proc_stmt::cgen() {
	string res;
	char temp[30];

	switch (choice1) {
		case  1: {		// 没有参数的 Procedure
			// 参数压栈
			identifier * newiden = gtable.lookUp(child1.choice1, currentScope);
			assert(newiden->type == ffunction || newiden->type == pprocedure);
			int totalSize = newiden->offset;
			int argsCounter = 0;
			int varSize = totalSize - 8 - argsCounter * 4;
			int childscope = -1;
			switch (newiden->type) {
				case ffunction:
					childscope = gtable.lookUpScope(newiden->value.func);
					break;
				case pprocedure:
					childscope = gtable.lookUpScope(newiden->value.proc);
					break;
				default: break;		// Error
			}
			//cout << "CURRENT SCOPE: |" << currentScope << "|" << endl;
			//cout << "PROC CHILDSCOPE: |" << childscope << "|" << endl;
			assert(childscope != -1);

			// 获取 access link -> $t0
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newiden->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = gtable.getScope(scopePtr).parent;
			}
			sprintf(temp, "%d", -1 * varSize - 4);	// access link
			res += "sw $t0, " + string(temp) + "($sp)\n";

			sprintf(temp, "%d", -1 * totalSize);	// 开栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "add $t7, $zero, $fp\n";		// 保存 $fp for control link
			res += "add $fp, $zero, $sp\n";

			sprintf(temp, "%d", -4);	// 开栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "sw $t7, 0($sp)\n";

			// 为数组参数申请空间
			assert(newiden->type == pprocedure);	// procedure_decl
			assert(newiden->value.proc->child2->child1->child4 != NULL);	// var_part
			var_decl_list * vars = newiden->value.proc->child2->child1->child4->child1;
			// procedure scope
			int pscope = gtable.lookUpScope(newiden->value.proc);
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
						res += "addi $sp, $sp, " + string(temp) + "\n";
						res += "sw $sp, " + to_string(newvariden->offset) + "($fp)\n";

						varName = varName->child1;
					}
				}
				else {}

				vars = vars->next;
			}

			// 找 function 地址
			int funcScope = gtable.lookUp(child1.choice1, currentScope)->scope;
			sprintf(temp, "%d", funcScope);

			// 跳转
			res += "jal " + child1.choice1->name + string(temp) + "\n";

			// 返回的时候清栈
			res += "lw $fp, -4($fp)\n";
			sprintf(temp, "%d", 4);	// 收栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			sprintf(temp, "%d", totalSize);	// 收栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";

			break;}
		case  2: {		// 有参数的 Procedure
			// 参数压栈
			identifier * newiden = gtable.lookUp(child1.choice1, currentScope);

			assert(newiden->type == pprocedure);
			int totalSize = newiden->offset;
			int argsCounter = 0;
			assert(newiden->paras!=NULL);
			argsCounter = newiden->paras->size();
			int varSize = totalSize - 8 - argsCounter * 4;
			int childscope = -1;
			switch (newiden->type) {
				case ffunction:
					childscope = gtable.lookUpScope(newiden->value.func);
					break;
				case pprocedure:
					childscope = gtable.lookUpScope(newiden->value.proc);
					break;
				default: break;		// Error
			}
			//cout << "CURRENT SCOPE: |" << currentScope << "|" << endl;
			//cout << "PROC CHILDSCOPE: |" << childscope << "|" << endl;
			assert(childscope != -1);

			args_list * ptr = child1.choice2.child2;
			string ref_restore = "";	// Restore for references
			for (int i = 0; i < argsCounter; i++) {
				// 计算参数值
				res += ptr->cgen();
				// 压栈
				sprintf(temp, "%d", -1 * totalSize + 8 + i * 4);
				res += "sw $v0, " + string(temp) + "($sp)\n";

				//cout << "finding " << newiden->paras->at(i) << endl;
				identifier * newArgId = gtable.lookUp(newiden->paras->at(i), childscope);
				assert(newArgId != NULL);
				// 参数为引用则生成赋值语句
				//cout << newArgId->passByReference << endl;
				if (newArgId->passByReference) {
					//sprintf(temp, "%d", 8 + i * 4);
					ref_restore += "lw $t1, " + string(temp) + "($sp)\n";

					int scopePtr = currentScope;
					ref_restore += "add $t0, $zero, $fp\n";
					assert(ptr->child3->child3->child3->choice1 == 1);
					identifier *sbid = gtable.lookUp(ptr->child3->child3->child3->child1.choice1, currentScope);
					assert(sbid != NULL);

					while (scopePtr != sbid->scope) {
						ref_restore += "lw $t0, 4($t0)\n";
						scopePtr = gtable.getScope(scopePtr).parent;
					}
					sprintf(temp, "%d", sbid->offset);

					ref_restore += "sw $t1, " + string(temp) + "($t0)\n";
				}

				ptr = ptr->next;
			}

			// 获取 access link -> $t0
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newiden->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = gtable.getScope(scopePtr).parent;
			}
			sprintf(temp, "%d", -1 * totalSize + 4);	// access link
			res += "sw $t0, " + string(temp) + "($sp)\n";


			sprintf(temp, "%d", -1 * totalSize);		// 开栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "add $t7, $zero, $fp\n";		// 保存 $fp for control link
			res += "add $fp, $zero, $sp\n";

			sprintf(temp, "%d", -4);	// 开栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "sw $t7, 0($sp)\n";

			// 为数组参数申请空间
			assert(newiden->type == pprocedure);	// procedure_decl
			assert(newiden->value.proc->child2->child1->child4 != NULL);	// var_part
			var_decl_list * vars = newiden->value.proc->child2->child1->child4->child1;
			// procedure scope
			int pscope = gtable.lookUpScope(newiden->value.proc);
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
						res += "addi $sp, $sp, " + string(temp) + "\n";
						res += "sw $sp, " + to_string(newvariden->offset) + "($fp)\n";

						varName = varName->child1;
					}
				}
				else {}

				vars = vars->next;
			}

			// 找 function 地址
			int funcScope = gtable.lookUp(child1.choice2.child1, currentScope)->scope;
			sprintf(temp, "%d", funcScope);

			// 跳转
			res += "jal " + child1.choice2.child1->name + string(temp) + "\n";

			// 清栈
			res += "lw $fp, -4($fp)\n";
			sprintf(temp, "%d", 4);	// 收栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			sprintf(temp, "%d", totalSize);	// 收栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";

			// 返回的时候对引用进行赋值
			res += ref_restore;
			
			break;}
		case  3: {		// 有参数的 Sys_proc
			break;}
		case  4: {		// 有参数的 Sys_proc
			if (child1.choice4.child2->child3->child3->child3->choice1 == 5 &&
				child1.choice4.child2->child3->child3->child3->child1.choice5->choice1 == 4) {
				// 输出字符串
				assert(child1.choice4.child2->child3->child3->child3->child1.choice5->child1.choice4 != NULL);
				res += "print_str(\"" + *(child1.choice4.child2->child3->child3->child3->child1.choice5->child1.choice4) + "\")\n";
			}
			else {
				// 输出 expression
				res += child1.choice4.child2->cgen();	// expression
				res += child1.choice4.child1->cgen(child1.choice4.child2->value.stype);	// sys_proc
			}

			switch (child1.choice4.child1->child1) {
				case wwrite: break;
				case wwriteln: 
					res += "addi $t0, $zero, 10\n";
					res += "print_char($t0)\n";
					break;
			}
			break;}
		case  5: {		// Read
			SimpleType tarSType;

			switch (child1.choice5->choice1) {
				case  1:{	// ID
					identifier * newiden = gtable.lookUp(child1.choice5->child1.choice1, currentScope);
					assert(newiden != NULL);
					assert(newiden->type == ssimple_type);
					tarSType = newiden->stype;		// Target simple type
					// 查找 ID 地址 -> $t0
					int scopePtr = currentScope;
					res += "add $t0, $zero, $fp\n";
					while (scopePtr != newiden->scope) {
						res += "lw $t0, 4($t0)\n";
						scopePtr = gtable.getScope(scopePtr).parent;
					}
					char temp[30];
					sprintf(temp, "%d", newiden->offset);
					res += "addi $t0, $t0, " + string(temp) + "\n";

					break;
					}
				case  9:{	// Array
					identifier *newiden = gtable.lookUp(child1.choice5->child1.choice9.child1, currentScope);
					assert(newiden != NULL);
					assert(newiden->type == aarray_type);
					tarSType = newiden->stype;
					int scopePtr = currentScope;
					res += child1.choice5->child1.choice9.child2->cgen();
					res += "add $t0, $zero, $fp\n";
					while(scopePtr != newiden->scope) {
						res += "lw $t0, 4($t0)\n";
						scopePtr = gtable.getScope(scopePtr).parent;
					}				
					char temp[30];
					sprintf(temp, "%d", newiden->offset);
					res += "addi $t0, $t0, " + string(temp) + "\n";
					res += "lw $t1, 0($t0)\n";
					res += "sll $v0, $v0, 2\n";
					res += "add $t0, $t1, $v0\n";

					break;
				}
				default: break;		// Error
			}

			switch (tarSType) {
				case iinteger:
					res += "li $v0, 5\n";
					res += "syscall\n";

					res += "sw $v0, 0($t0)\n";
					break;
				case rreal:
					res += "li $v0, 6\n";
					res += "syscall\n";
					
					res += "swc1 $f0, 0($t0)\n";
					break;
				case cchar:
					break;
				default: break;		// Error
			}

			break;}
		default: {break;}		// Error
	}

	return res;
}

string expression::cgen() {
	string res;

	if (child1 != NULL) {
		res += child1->cgen();
		res += "addi $sp, $sp, -4\n";
		res += "sw $v0, 0($sp)\n";

		res += child3->cgen();
	
		res += "lw $v1, 0($sp)\n";
		switch (child2) {
			case gge: {		res += "sge $v0, $v1, $v0\n"; break;}
			case ggt: {		res += "sgt $v0, $v1, $v0\n"; break;}
			case lle: {		res += "sle $v0, $v1, $v0\n"; break;}
			case llt: {		res += "slt $v0, $v1, $v0\n"; break;}
			case eequal: {	res += "seq $v0, $v1, $v0\n"; break;}
			case uunequal: {	res += "sne $v0, $v1, $v0\n"; break;}
			default:  {break;}	// Error
		}

		res += "addi $sp, $sp, 4\n";	// 弹栈
	}
	else {
		res += child3->cgen();
	}

	return res;
}

/******************************************/
/* GJY                                    */
/* repeat_stmt, while_stmt, for_stmt,     */
/* factor                                 */
/******************************************/
string repeat_stmt::cgen() {
	string res;

	sbCounter++;
	string repeatAddr =  string("until_") + to_string(sbCounter);
	res += repeatAddr + ":\n";

	stmt_list * ptr = child1;
	while (ptr != NULL) {
		res += ptr->cgen();
		ptr = ptr->next;
	}

	res += child2->cgen();
	res += "beq $v0, $zero, " + repeatAddr + "\n";

	return res;
}

string while_stmt::cgen(){
	string res;

	sbCounter++;
	string whileAddr1 = "while_start_" + to_string(sbCounter);
	string whileAddr2 = "while_end_" + to_string(sbCounter);

	res += whileAddr1 + ":\n";
	res += child1->cgen();
	res += "beq $v0, $zero, " + whileAddr2 + "\n";

	res += child2->cgen();
	res += "j " + whileAddr1 + "\n";
	res += whileAddr2 + ":\n";

	return res;
}

string for_stmt::cgen() {
	string res;
	char temp[30];

	sbCounter++;
	string forAddr1 = "for_start_" + to_string(sbCounter);
	string forAddr2 = "for_end_" + to_string(sbCounter);

	identifier *newChild1 = gtable.lookUp(child1, currentScope);
	// 类型检测,不是简单类型要报错
	//if (newChild1->type != simple_type || newChild1->simpletype != integer) {}	// Error
	// 查找 child1 地址
	int scopePtr = currentScope;
	res += "add $t0, $zero, $fp\n";
	while (scopePtr != newChild1->scope) {
		res += "lw $t0, 4($t0)\n";
		scopePtr = gtable.getScope(scopePtr).parent;
	}
	sprintf(temp, "%d", newChild1->offset);
	string offset(temp);
	res += "addi $sp, $sp, -4\n";
	res += "sw $t0, 0($sp)\n";

	res += child4->cgen();	// terminate condition
	switch (child3) {	// 1: to  2: downto
		case  1: { res += "addi $v0, $v0, 1\n";  break;}
		case  2: { /*res += "addi $v0, $v0, -1\n";*/ break;}
		default: {break;}	// Error
	}
	res += "addi $sp, $sp, -4\n";
	res += "sw $v0, 0($sp)\n";
	
	res += child2->cgen();	// initial condition
	res += "lw $t0, 4($sp)\n";
	res += "sw $v0, " + offset + "($t0)\n";

	res += forAddr1 + ":\n";
	switch (child3) {	// 1: to  2: downto
		case 1: {
			res += "lw   $v1, 0($sp)\n";
			res += "slt  $t0, $v0, $v1\n";
			res += "beq  $t0, $zero, " + forAddr2 + "\n";
			break;}
		case 2: {
			res += "lw   $v1, 0($sp)\n";
			res += "slt  $t0, $v0, $v1\n";
			res += "bne  $t0, $zero, " + forAddr2 + "\n";
			break;}
		default:
			{break;}	// Error
	}

	res += child5->cgen();
	res += "lw   $t0, 4($sp)\n";
	res += "lw   $v0, " + offset + "($t0)\n";
	switch (child3) {	// 1: to  2: downto
		case  1: {
			res += "addi $v0, $v0, 1\n";
			break;
		}
		case  2: {
			res += "addi $v0, $v0, -1\n";
			break;
		}
		default: {break;}	// Error
	}
	res += "sw   $v0, " + offset + "($t0)\n";

	res += "j " + forAddr1 + "\n";
	res += forAddr2 + ":\n";
	// Restore var
	res += "lw $t0, 4($sp)\n";
	res += "lw $v0, " + offset + "($t0)\n";
	switch (child3) {	// 1: to  2: downto
		case  1: res += "addi $v0, $v0, -1\n"; break;
		case  2: res += "addi $v0, $v0, 1\n";  break;
		default: break;	// Error
	}
	res += "sw $v0, " + offset + "($t0)\n";

	res += "addi $sp, $sp, 8\n";	// 收栈

	return res;
}

string factor::cgen() {
	string res;
	char temp[30];

	switch (choice1) {
		case  1: {	// id
			identifier *newChild1 = gtable.lookUp(child1.choice1, currentScope);
			// 查找 child1 地址
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newChild1->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = gtable.getScope(scopePtr).parent;
			}


			//string offset(temp);
			if(newChild1->constant){
				if(value.stype == rreal){
					res += ".data\n";
					sbCounter++;
					string lable = to_string(sbCounter);
					res += "data_" + lable + ":\n";
					
					res +=".float "+ to_string(newChild1->value.f) +"\n";
					res +=".text\n";
					res += "lwc1 $f0, data_"+lable + "\n";
				}
				else{
					res += "addi $v0, $zero, " + to_string(newChild1->value.i) +"\n";
				}
			}
			else{
				sprintf(temp, "%d", newChild1->offset);
				if(value.stype == rreal){
				//浮点
					res += "lwc1 $f0, " + string(temp) + "($t0)\n";
				}
				else{
					res += "lw $v0, " + string(temp) + "($t0)\n";	
				}
			}
			break;}
		case  2: {	// function
			// 参数压栈
			identifier * newiden = gtable.lookUp(child1.choice1, currentScope);

			assert(newiden->type == ffunction);
			int totalSize = newiden->offset;
			int argsCounter = 0;
			assert(newiden->paras!=NULL);
			argsCounter = newiden->paras->size();
			int varSize = totalSize - 8 - argsCounter * 4;
			int childscope = -1;
			switch (newiden->type) {
				case ffunction:
					childscope = gtable.lookUpScope(newiden->value.func);
					break;
				case pprocedure:
					childscope = gtable.lookUpScope(newiden->value.proc);
					break;
				default: break;		// Error
			}
			assert(childscope != -1);

			args_list * ptr = child1.choice2.child2;
			string ref_restore = "";	// Restore for references
			for (int i = 0; i < argsCounter; i++) {
				// 计算参数值
				res += ptr->cgen();
				// 压栈
				sprintf(temp, "%d", -1 * totalSize + 8 + i * 4);
				res += "sw $v0, " + string(temp) + "($sp)\n";

				identifier * newArgId = gtable.lookUp(newiden->paras->at(i), childscope);
				assert(newArgId != NULL);
				// 参数为引用则生成赋值语句
				//cout << newArgId->passByReference << endl;
				if (newArgId->passByReference) {
					ref_restore += "lw $t1, " + string(temp) + "($sp)\n";

					int scopePtr = currentScope;
					ref_restore += "add $t0, $zero, $fp\n";
					assert(ptr->child3->child3->child3->choice1 == 1);
					identifier *sbid = gtable.lookUp(ptr->child3->child3->child3->child1.choice1, currentScope);
					assert(sbid != NULL);

					while (scopePtr != sbid->scope) {
						ref_restore += "lw $t0, 4($t0)\n";
						scopePtr = gtable.getScope(scopePtr).parent;
					}
					sprintf(temp, "%d", sbid->offset);

					ref_restore += "sw $t1, " + string(temp) + "($t0)\n";
				}

				ptr = ptr->next;
			}

			// 获取 access link -> $t0
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newiden->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = gtable.getScope(scopePtr).parent;
			}
			sprintf(temp, "%d", -1 * totalSize + 4);	// access link
			res += "sw $t0, " + string(temp) + "($sp)\n";

			sprintf(temp, "%d", -1 * totalSize);		// 开栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "add $t7, $zero, $fp\n";		// 保存 $fp for control link
			res += "add $fp, $zero, $sp\n";

			sprintf(temp, "%d", -4);	// 开栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			res += "sw $t7, 0($sp)\n";

			// 为数组参数申请空间
			assert(newiden->type == ffunction);	// function_decl
			assert(newiden->value.func->child2->child1->child4 != NULL);	// var_part
			var_decl_list * vars = newiden->value.func->child2->child1->child4->child1;
			// procedure scope
			int pscope = gtable.lookUpScope(newiden->value.func);
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
						res += "addi $sp, $sp, " + string(temp) + "\n";
						res += "sw $sp, " + to_string(newvariden->offset) + "($fp)\n";

						varName = varName->child1;
					}
				}
				else {}

				vars = vars->next;
			}

			// 找 function 地址
			int funcScope = gtable.lookUp(child1.choice2.child1, currentScope)->scope;
			sprintf(temp, "%d", funcScope);

			// 跳转
			res += "jal " + child1.choice2.child1->name + string(temp) + "\n";

			// 返回的时候清栈
			res += "lw $fp, -4($fp)\n";
			sprintf(temp, "%d", 4);	// 收栈（control link）
			res += "addi $sp, $sp, " + string(temp) + "\n";
			sprintf(temp, "%d", totalSize);	// 收栈（参数、access link、$ra）
			res += "addi $sp, $sp, " + string(temp) + "\n";

			// 返回的时候对引用进行赋值
			res += ref_restore;

			break;}
		case  3: {	// sys_func, no params
			break;}
		case  4: {	// sys_func, with params
			break;}
		case  5: {	// 常数
			switch (child1.choice5->choice1) {
				case  1: {	// int
					sprintf(temp, "%d", child1.choice5->child1.choice1);
					res += "addi $v0, $zero, " + string(temp) + "\n"; break;}
				case  2: {
					res += ".data\n";
					sbCounter++;
					string lable = to_string(sbCounter);
					res += "data_" + lable + ":\n";
					sprintf(temp, "%f", child1.choice5->child1.choice2);
					res +=".float "+ string(temp)+"\n";
					res +=".text\n";
					res += "lwc1 $f0, data_"+lable + "\n";
					break;}	// float
				case  3: {	// char
					sprintf(temp, "%d", child1.choice5->child1.choice3);
					res += "addi $v0, $zero, " + string(temp) + "\n";
					break;}
				default: {break;}
			}
			break;}
		case  6: {	// expression
			res += child1.choice6->cgen();
			break;}
		case  7: {	// not factor
			// TODO:
			break;}
		case  8: {	// minus factor
			res += child1.choice8->cgen();
			if(value.stype == rreal){
				//$f31 is saved and the value is always 0
				res += "sub.s $f0, $f31, $f0\n";
			}
			else{
				res += "sub $v0, $zero, $v0\n";
			}
			break;}
		case  9: {	// array
			res += child1.choice9.child2->cgen();	// 算数组内偏移 -> $v0

			identifier *newChild1 = gtable.lookUp(child1.choice9.child1, currentScope);
			assert(newChild1 != NULL);
			// 查找 数组 起始地址 -> $t0
			int scopePtr = currentScope;
			res += "add $t0, $zero, $fp\n";
			while (scopePtr != newChild1->scope) {
				res += "lw $t0, 4($t0)\n";
				scopePtr = gtable.getScope(scopePtr).parent;
			}
			sprintf(temp, "%d", newChild1->offset);
			string offset(temp);
			res += "lw $t0, " + offset + "($t0)\n";

			// 取数组元素值 -> $v0
			res += "sll $v0, $v0, 2\n";
			res += "add $t0, $t0, $v0\n";
			res += "lw  $v0, 0($t0)\n";

			break;}
		case 10: {	// X.b
			// TODO:
			break;}
		default:
			{break;}	// Error
	}

	return res;
}

/***
* 
* @author: 高奔
* 添加  cgen()
***/

/**
* if_stmt
* else_clause
**/          
std::string if_stmt::cgen(){
	sbCounter++;
	std::string lable = to_string(sbCounter);
	std::string res;
	std::string elseaddr = "else_" + lable;
	std::string endifaddr = "endif_" + lable;
	res += child1->cgen();
	res = res + "beq $v0, $zero, " + elseaddr + "\n";
	if(child2)
		res += child2->cgen();
	res = res + "j " + endifaddr +"\n";
	res = res + elseaddr + ":\n";
	if(child3) 
		res += child3->cgen();
	res = res + endifaddr + ":\n";
	return res;
}
std::string else_clause::cgen(){
	std::string res;
	if(choice1 != 0 && child1){
		res += child1->cgen();
	}
	return res;
}
/**
* goto_stmt
**/
std::string goto_stmt::cgen(){
	std::string res;
	std::string targetaddr = "Label_" + to_string(child1);
	res = res + "j " + targetaddr + "\n";
	return res;
}

/**
* case_stmt
* -----------   略去  case_expr_list 直接使用case_expr的链表
* case_expr
**/
std::string case_stmt::cgen() {
	std::string res;

	sbCounter++;
	std::string lable = to_string(sbCounter);
	std::string endcaseaddr = "endcaseaddr_" + lable;

	res += child1->cgen();	// 算 expression

	case_expr *temp = child2;
	int nextLabelCounter = 0;
	while (temp != NULL) {
		nextLabelCounter = sbCounter + 1;
		res += temp->cgen();
		res += "j " + endcaseaddr + "\n";
		res += "nextcaseaddr_" + to_string(nextLabelCounter) + ":\n";
		temp = temp->next;	// 好奇怪
	}

	res = res + endcaseaddr + ":\n";
	return res;
}

std::string case_expr::cgen() {
	std::string res;

	sbCounter++;
	std::string nextcaseaddr = "nextcaseaddr_" + to_string(sbCounter);

	// Get const value
	switch (choice1) {
		case  1:
			switch (child1.choice1->choice1) {
				case  1:	// int
					res += "addi $t1, $zero, " + to_string(child1.choice1->child1.choice1) + "\n";
					break;
				case  2:	// float error
					break;
				case  3:	// char
					res += "addi $t1, $zero, " + to_string(child1.choice1->child1.choice3) + "\n";
					break;
				default: break;		// Error
			}
			break;
		case  2:
			/*res += child1.choice2->cgen();*/
			break;
		default: break;		// Error
	}
	
	res += "bne  $v0, $t1 " + nextcaseaddr + "\n";
	
	res += child2->cgen();

	return res;
}

/**
*  ----------------#expression_list	 #expression  陈正
*  expr term   高奔
*  ---------------#factor 	顾建业
**/
std::string expr::cgen(){
	std::string res;

	if(child1 != NULL) {
		res += child1->cgen();
		res = res + "addi $sp, $sp, -4\n";
		
		if(value.stype == rreal){
			res = res + "swc1 $f0, 0($sp)\n";
			res += child3->cgen();
			res = res + "lwc1 $f1, 0($sp)\n";
			switch(child2){
			case pplus:
				res += "add.s $f0, $f1, $f0\n";
				break;
			case mminus:
				res += "sub.s $f0, $f1, $f0\n";
				break;
			default: break;
			}
		}
		else{
			res = res + "sw $v0, 0($sp)\n";
			res += child3->cgen();
			res = res + "lw $t1, 0($sp)\n";
			switch(child2){
			case pplus:
				res += "add $v0, $t1, $v0\n";
				break;
			case mminus:
				res += "sub $v0, $t1, $v0\n";
				break;
			case oor:
				res += "or $v0, $t1, $v0\n";
				break;
			default: break;
			}
		}
		res = res + "addi $sp, $sp, 4\n";
	}
	else {
		res += child3->cgen();
	}

	return res;
}

std::string term::cgen(){
	std::string res;

	if (child1 != NULL) {
		res += child1->cgen();
		res = res + "addi $sp, $sp, -4\n";
		
		if(value.stype == rreal){
			res = res + "swc1 $f0, 0($sp)\n";
			res += child3->cgen();
			res = res + "lwc1 $f1, 0($sp)\n";
			switch(child2){
				//** warning: 乘法 除法 取模的 mips 指令
			//mult 
			case mmul:
				res += "mul.s $f0, $f1, $f0\n";
				break;
			case ddiv:
				res += "div.s $f0, $f1, $f0\n";
				break;
			default: break;
			}
		}
		else{
			res = res + "sw $v0, 0($sp)\n";
			res += child3->cgen();
			res = res + "lw $t1, 0($sp)\n";
			switch(child2){
			//** warning: 乘法 除法 取模的 mips 指令
			//mult 
			case mmul:
				res += "mult $t1, $v0\n";
				res += "mflo $v0\n";
				break;
			case ddiv:
				res += "div $t1, $v0\n";
				res += "mflo $v0\n";
				break;
			case mmod:
				res += "div $v0, $t1, $v0\n";
				res += "mfhi $v0\n";
				break;
			case aand:
				res += "and $v0, $t1, $v0\n";
				break;
			default: break;
			}
		}
		res = res + "addi $sp, $sp, 4\n";
	}
	else {
		res += child3->cgen();
	}

	return res;
}
/*****************	高奔 finish	****************************/


