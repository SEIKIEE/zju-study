#ifndef _LWD_SYMBOLTABLE_H_
#define _LWD_SYMBOLTABLE_H_

#include "declare.h"

#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstdio>
#include <iostream>

//#define SYMBOLTABLE_DEBUG

namespace lwd {

struct scopeValue{
	int parent;//-1 stands for root
	int choice;//0=universal, only valid for the program name in pascal
	union {
		lwd::program *type1;
		lwd::function_decl *type2;
		lwd::procedure_decl *type3;
	} type;
	scopeValue(int p, lwd::program *t):parent(p),choice(1) { type.type1 = t; }
	scopeValue(int p, lwd::function_decl *t):parent(p),choice(2) { type.type2 = t; }
	scopeValue(int p, lwd::procedure_decl *t):parent(p),choice(3) { type.type3 = t; }
	scopeValue(int p):parent(p),choice(0) { }
	scopeValue(int p, const std::string &s): parent(p), choice(0) { }
	void print() const { 
		printf("parent : %d, type : ", parent);
		switch(choice) {
		case 0: printf("universal"); break;
		case 1: printf("program, name : %s", type.type1->child1->child1->name.c_str()); break;
		case 2: printf("function, name : %s", type.type2->child1->child1->name.c_str()); break;
		case 3: printf("procedure, name : %s", type.type3->child1->child1->name.c_str()); break;
		case 4: printf("error choice"); break;
		}
		printf("\n");
	}
};

class symbolTable {
private :
	std::vector<scopeValue> scope;
	std::map<std::string,std::vector<lwd::identifier *> > table;
	std::set<int> label;
	std::set<int> usedlabel;
	std::set<identifier *> const_pool;
public :
	void printScope();
	void printIdentifier();
	void printConst();
	void addConst(lwd::identifier *id) { const_pool.insert(id); }
	//identifier *getConst(identifier *i, int scopee);
	std::set<lwd::identifier *> &getConstPoll() { return const_pool; }
	/*
	insert a new scope into the table
	return value=scope_id for this scope, -1 means there already exists this scope
	*/
	int insertScope() {//for global scope only
#ifdef SYMBOLTABLE_DEBUG
		printf("Inside insertScope().\n"); 
#endif
		scope.push_back(scopeValue(-1, "global"));
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of insertScope().\n"); 
#endif
		return scope.size()-1;
	}

	int insertScope(lwd::program *id, int parent_scope) {
#ifdef SYMBOLTABLE_DEBUG
		printf("Inside insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		if(lookUpScope(id)!=-1) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of insertScope(), id = %s, pscope = %d\n", 
				id->child1->child1->name.c_str(), parent_scope);
#endif
			return -1;
		}
		scope.push_back(scopeValue(parent_scope, id));
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		return scope.size()-1;
	}
	int insertScope(lwd::function_decl *id, int parent_scope) {
#ifdef SYMBOLTABLE_DEBUG
		printf("Inside insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		if(lookUpScope(id)!=-1) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of insertScope(), id = %s, pscope = %d\n", 
				id->child1->child1->name.c_str(), parent_scope);
#endif
			return -1;
		}
		scope.push_back(scopeValue(parent_scope, id));
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		return scope.size()-1;
	}
	int insertScope(lwd::procedure_decl *id, int parent_scope) {
#ifdef SYMBOLTABLE_DEBUG
		printf("Inside insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		if(lookUpScope(id)!=-1) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of insertScope(), id = %s, pscope = %d\n", 
				id->child1->child1->name.c_str(), parent_scope);
#endif
			return -1;
		}
		scope.push_back(scopeValue(parent_scope, id));
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of insertScope(), id = %s, pscope = %d\n", 
			id->child1->child1->name.c_str(), parent_scope);
#endif
		return scope.size()-1;
	}

	/*
	search for the specified scope
	return value is the id for that scope
	-1 means no such scope exists
	*/
	int lookUpScope(lwd::program *id);
	int lookUpScope(lwd::function_decl *id);
	int lookUpScope(lwd::procedure_decl *id);

	/*
	get the scopeValue of the specified scope
	*/
	scopeValue getScope(int s) const { 
		//for(int i=0; i<scope.size(); ++i)
		//	scope[i].print();
		//std::cout << " in getScope : " << s << std::endl; 
		assert(s<scope.size()); 
		return scope.at(s); 
	}
	
	/*
	insert a new identifier into the table
	if there already exists this name in this scope, return false
	*/
	bool insertID(lwd::identifier *id, int scope);
	
	/*
	look for the identifier specified by name and scope
	will return the identifier found in the most nested scope, iscope is set to be the scope of found identifier
	if it does not exist, return value is NULL
	*/
	lwd::identifier *lookUp(const lwd::identifier * const id, int s, int &is) const ;
	
	lwd::identifier *lookUp(const std::string &id, int s, int &is) const;
	
	/*
	similar to the one above except this only looks in the specified scope, not potential parent scopes
	*/

	lwd::identifier *lookUp(const lwd::identifier * const id, int s) const {
	#ifdef SYMBOLTABLE_DEBUG
		printf("Inside lookUp(), id = %s , scope = %d\n", 
			id->name.c_str(), s);
	#endif
		return lookUp(id, s, s);
	}

	lwd::identifier *lookUp(const std::string &id, int s) const {
		int temp;
		return lookUp(id, s, temp);
	}
	
	/*
	delete and return the specified identifier in the table
	if it does not exist, the return value is NULL
	*/
	//lwd::identifier *pop(const identifier * const id, int s);

	bool addLabel(int l) { 
		label.insert(l);
		return true;
	}
	bool addUsedLabel(int l) {
		usedlabel.insert(l);
		return true;
	}
	bool checkLabel();
};

extern symbolTable gtable;

}

#endif
