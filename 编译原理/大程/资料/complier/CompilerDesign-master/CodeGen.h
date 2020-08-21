#ifndef _CODEGEN_H_
#define _CODEGEN_H_
#include <string>
#include <fstream> // file stream
#include <vector> // push label after .data
#include <sstream>	// for stringstream

using namespace std;
void OpenCodeGen(); // open file stream
void CloseCodeGen(); // close file
void CodeGen(const char * arg0, const char * arg1, int arg2, const char * arg3);
void CodeGen(const char *arg0, const char *arg1, const char *arg2, const char *arg3);
string GenStringLabel(const char * type, const char * lexeme);
string GenFloatLabel(const char * type, const char * lexeme);

void Prolog();
void Postlog(); 
#endif // !_CODEGEN_H_
