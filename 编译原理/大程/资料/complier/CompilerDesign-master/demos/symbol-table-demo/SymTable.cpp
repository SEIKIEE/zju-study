#include <iostream>
#include "SymTable.h"

using namespace std;
//|------------------main variables-------------------|
std::unordered_map<std::string, SymTabRecord> symbolTable;  // the data struct of unordered_map is hashtable
std::stack<int> scopeStack; // store active scope
int curScope;
int maxScope;    // use  maxScope to remeber the max scope

//|-----------------------------------------------|
void initSymTable() {
    curScope = 0;
    maxScope = 0;
    scopeStack.push(0);
}

//|-----------------------------------------------|
//|--Function: openScope
//|--Description: update maxScope, current scope, scopeStack 
//|--Calls: 1) stack.push
//|--Called By: 1) parser
//|------------------------------------------------|
void openScope() {
    maxScope++;    //increase maxScope
    curScope = maxScope;
    scopeStack.push(curScope);    //put cur scope number into scope stack
}

//|-----------------------------------------------|
//|--Function: closeScope
//|--Description: update scopeStack and current scope
//|--Calls: 1) stack.pop 2)stack.empty 3) stack.top
//|--Called By: 1) parser
//|------------------------------------------------|
void closeScope() {
    if (!scopeStack.empty())    //check stack
    {
        scopeStack.pop();    //< pop the top of stack
    }
    if (!scopeStack.empty())    //check stack
    {
        curScope = scopeStack.top(); //< set the top of stack as currentScope
    }
}

//|------------------------------------------------|
//|--Function: insert
//|--Calls: 1) map.find end insert (C++ STL)
//|--Called By: 1) parser
//|------------------------------------------------|
void insert(char *name, char type, int location, int isVar) {
    getFirst(name, IDLENGTH);    // get first 8 char
    convertToLittleCase(name);

    /*  get a key for ST  key = currentScope + name	*/
    stringstream ss;
    ss << curScope << name;
    string key = ss.str();

    /*  find key in symbolTable */
    auto it = symbolTable.find(key);
    if (it != symbolTable.end()) {
        return; // exist in ST, ignore it
    } else {   /* insert rec into ST*/
        symbolTable.insert(make_pair(key, getSymTabRecord(name, curScope, type, location, isVar)));
    }
}

//|----------------------------------------------------|
//|--Function: findInCurScope
//|--Calls: 1) unordered_map.find (C++ STL)
//|--Called By: 1) paser
//|----------------------------------------------------|
SymTabRecord *findInCurScope(char *name) {
    getFirst(name, IDLENGTH);    // the first 8 is important
    convertToLittleCase(name);

    /*  get a key   key = currentScope + scope	*/
    std::stringstream ss;
    ss << curScope << name;
    std::string key = ss.str();

    /*  find key in ST */
    auto it = (symbolTable).find(key);
    if (it != (symbolTable).end()) //< exist
    {
        return &(it->second);    // a pointer of record in ST
    } else {
        return nullptr;    //< no exist
    }
}

//|-----------------------------------|
//|--Function: findInAllScopes
//|--Calls: 1) map.find (C++ STL)
//|--Called By: paser
//|-----------------------------------|
SymTabRecord *findInAllScopes(char *name) {
    getFirst(name, IDLENGTH);
    convertToLittleCase(name);

    /* step 1: get a copy of scopeStack */
    std::stack<int> scopeStackCopy = scopeStack;

    /* step 2: check active scope is empty */
    while (!scopeStackCopy.empty()) {
        /* step 2.1: get top scope number, then pop */
        int tmpScope = scopeStackCopy.top();
        scopeStackCopy.pop();

        /* step 2.2 : get a key: tmpScope + name  */
        stringstream ss;
        ss << tmpScope << name;
        string key = ss.str();

        /* step 2.3: find the key */
        auto it = symbolTable.find(key);
        if (it != symbolTable.end()) {
            return &(it->second);    // return pointer of record
        }
    }
    return nullptr; // not found in all visual active scope
}

//|------- function: display ST -------------------|
void displaySymTable() {
    printf("\n|----------------------SymbolTable---------------------|\n");
    for (auto it = symbolTable.begin(); it != symbolTable.end(); it++) {
        cout << toString(&(it->second));
    }
}

//|----------------------------------- all below is for test ----------------------------------|
void testFindInLocalScope(char *name) {
    SymTabRecord *rec = nullptr;

    printf("\nWe are now in scope: \"%d\", \tfinding in local scope: \"%s\" \n", curScope, name);
    if ((rec = findInCurScope(name)) != nullptr) {
        printf("Result: ^0^ Found it in lcoal\n");
        std::cout << toString(rec);
    } else {
        printf("Result: -_- No found in local\n");
    }
}

void testFindInAllScopes(char *name) {
    SymTabRecord *rec = nullptr;

    printf("\nWe are now in scope: \"%d\"  \tfinding in all scopes: \"%s\" \n", curScope, name);
    if ((rec = findInAllScopes(name)) != nullptr) {
        printf("result: ^0^ Found it in scope: \"%d\"\n", rec->scope);
        std::cout << toString(rec);
    } else {
        printf("result: -_- No found in all scopes\n");
    }
}

void testST() {
    initSymTable();
    char name[IDMAXLENGTH] = "";
    int in = 8;
    SymTabRecord *stPtr = NULL;
    do {
        printf("\n|----1. openScope    2.insert      3. findinCurScope 4. findinAllScopes ------|\n");
        printf("|----5. closeScope   6. display    7. clear screen   8. exit------------------|\n");
        printf("Enter your instruction number(1-9): ");
        scanf("%d", &in);    // get instrction from keyboard
        switch (in) {
            case 1:
                openScope();
                printf("Open a scope\n");
                break;
            case 2:
                printf("Enter a name: ");
                scanf("%s", name);
                insert(name, 'i', -12, 1);
                break;
            case 3:
                printf("Enter a name: ");
                scanf("%s", name);
                testFindInLocalScope(name);
                break;
            case 4:
                printf("Enter a name: ");
                scanf("%s", name);
                testFindInAllScopes(name);
                break;
            case 5:
                printf("Close a scope\n");
                closeScope();
                break;
            case 6:
                displaySymTable();
                break;
            case 7:
                system("cmd /c cls");
                break;
            default:
                break;
        }
    } while (8 != in);
}