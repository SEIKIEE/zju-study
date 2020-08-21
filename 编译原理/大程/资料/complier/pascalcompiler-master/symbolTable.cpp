#include "declare.h"
#include "symbolTable.h"

#include <cassert>
#include <map>
#include <vector>
#include <iterator>

using namespace std;
using namespace lwd;

int symbolTable::lookUpScope(program *id) {
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	for(int i=0; i<scope.size(); ++i)
		if(scope.at(i).choice==1&&
			scope.at(i).type.type1->child1->child1->name==id->child1->child1->name) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of lookUpScope(), id = %s \n", 
				id->child1->child1->name.c_str());
#endif
			return i;
	}
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	return -1;
}

int symbolTable::lookUpScope(function_decl *id) {
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	for(int i=0; i<scope.size(); ++i)
		if(scope.at(i).choice==2&&
			scope.at(i).type.type2->child1->child1->name==id->child1->child1->name) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of lookUpScope(), id = %s \n", 
				id->child1->child1->name.c_str());
#endif
			return i;
}
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	return -1;
}

int symbolTable::lookUpScope(procedure_decl *id) {
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	for(int i=0; i<scope.size(); ++i)
		if(scope.at(i).choice==3&&
			scope.at(i).type.type3->child1->child1->name==id->child1->child1->name) {
#ifdef SYMBOLTABLE_DEBUG
			printf("Out of lookUpScope(), id = %s \n", 
				id->child1->child1->name.c_str());
#endif
			return i;
	}
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of lookUpScope(), id = %s \n", 
		id->child1->child1->name.c_str());
#endif
	return -1;
}

bool symbolTable::insertID(lwd::identifier *id, int s) {
	assert(s<0||s<scope.size());
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside insertID(), id = %s , scope = %d\n", 
		id->name.c_str(), s);
#endif
	identifier *temp = lookUp(id, s);
	if(temp!=NULL&&temp->scope==s) {
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of insertID(), id = %s , scope = %d\n", 
			id->name.c_str(), s);
#endif
		
		return false;
	}
	map<string,vector<lwd::identifier *> >::iterator iter = table.find(id->name);
	if(iter==table.end()) {
		table.insert(pair<string,vector<lwd::identifier *> >(id->name,vector<lwd::identifier *>()));
		iter = table.find(id->name);
	}
	iter->second.push_back(id);
	id->scope = s;
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of insertID(), id = %s , scope = %d\n", 
		id->name.c_str(), s);
#endif
	return true;
}

lwd::identifier *symbolTable::lookUp(const lwd::identifier * const id, int s, int &is) const {
	assert(s<scope.size());
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside lookUp(), id = %s , scope = %d\n", 
		id->name.c_str(), s);
#endif
	map<string,vector<lwd::identifier *> >::const_iterator iter = table.find(id->name);
	if(iter==table.end()) {
#ifdef SYMBOLTABLE_DEBUG
		printf("No such element named %s\n", id->name.c_str());		
#endif
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of lookUp(), id = %s , scope = %d\n", 
			id->name.c_str(), s);
#endif
		return NULL;
	}
	const vector<lwd::identifier *> & ids = iter->second;
	while(s!=-1) {
		for(int i=0; i<ids.size(); ++i) {
#ifdef SYMBOLTABLE_DEBUG
			printf("id %s in scope %d\n", ids[i]->name.c_str(), ids[i]->scope);
#endif
			if(ids[i]->scope==s) {
				is = s;
#ifdef SYMBOLTABLE_DEBUG
				printf("Out of lookUp(), id = %s , scope = %d\n", 
				id->name.c_str(), s);
#endif
				return ids[i];
			}
		}
		s = scope[s].parent;
	}
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of lookUp(), id = %s , scope = %d\n", 
		id->name.c_str(), s);
#endif
	return NULL;
}

lwd::identifier * symbolTable::lookUp(const std::string &name, int s, int &is) const {
	assert(s<scope.size());
#ifdef SYMBOLTABLE_DEBUG
	printf("Inside lookUp(), name = %s , scope = %d\n", 
		name.c_str(), s);
#endif
	map<string,vector<lwd::identifier *> >::const_iterator iter = table.find(name);
	if(iter==table.end()) {
#ifdef SYMBOLTABLE_DEBUG
		printf("No such element named %s\n", name.c_str());		
#endif
#ifdef SYMBOLTABLE_DEBUG
		printf("Out of lookUp(), name = %s , scope = %d\n", 
			name.c_str(), s);
#endif
		return NULL;
	}
	const vector<lwd::identifier *> & ids = iter->second;
	while(s!=-1) {
		for(int i=0; i<ids.size(); ++i) {
#ifdef SYMBOLTABLE_DEBUG
			printf("id %s in scope %d\n", ids[i]->name.c_str(), ids[i]->scope);
#endif
			if(ids[i]->scope==s) {
				is = s;
#ifdef SYMBOLTABLE_DEBUG
				printf("Out of lookUp(), name = %s , scope = %d\n", 
				name.c_str(), s);
#endif
				return ids[i];
			}
		}
		s = scope[s].parent;
	}
#ifdef SYMBOLTABLE_DEBUG
	printf("Out of lookUp(), name = %s , scope = %d\n", 
		name.c_str(), s);
#endif
	return NULL;
}

bool symbolTable::checkLabel() {
	set<int> diff;
	for(set<int>::iterator iter = usedlabel.begin(); iter!=usedlabel.end(); ++iter) 
		if(label.find(*iter)==label.end())
			diff.insert(*iter);
	for(set<int>::iterator iter = diff.begin(); iter!=diff.end(); ++iter) 
		printf("Label %d used but not defined.\n", *iter);
	return diff.empty();
}
/*
identifier *getConst(identifier *id, int scopee) {
	for(set<identifier *>::iterator iter = const_pool.begin(); iter!=const_pool.end(); ++iter) {
		identifier *oid = *iter;
		if(oid->name==id->name) {
			int sc = oid->scope;
			while(scopee>0) {
				if(scopee==sc)
					return oid;
				scopee = gtable.getScope(scopee).parent;
			}
		}
	}
	return NULL;
}
*/
void symbolTable::printScope() {
	for(int i=0; i<scope.size(); ++i) {
		printf("scope %d -> ", i);	
		scope[i].print();
	}
}

void symbolTable::printIdentifier() {
	for(map<string,vector<identifier *> >::iterator iter = table.begin(); iter!=table.end(); ++iter) {
		printf("id name : %s, occurred scope : ", iter->first.c_str());
		for(int i=0; i< iter->second.size(); ++i) 
			printf("%d ", iter->second[i]->scope);
		printf("\n");
	}
}

void symbolTable::printConst() {
	for(set<identifier *>::iterator iter = const_pool.begin(); iter!=const_pool.end(); ++iter) {
		printf("constant %s, ", (*iter)->name.c_str());
		switch((*iter)->stype) {
		case iinteger: printf("type integer, value %d", (*iter)->value.i); break;
		case rreal: printf("type real, value %f", (*iter)->value.f); break;
		case cchar: printf("type char, value %c", (*iter)->value.c); break;
		case sstring: printf("type string, value %s", (*iter)->value.s->c_str()); break;
		}
		printf("\n");
	}
}
