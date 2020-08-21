
#ifndef genCode_hpp
#define genCode_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

#define REG_SIZE 18
#define MEM_SIZE 4

void buildCode(string irPath,string obPath);
void writeCode(string path,string obcode);
void loadIrcode(string path);
void loadVariable(void);
void assignRegister(void);
string translate(vector<string> line);
string getRegister(string s);
string getTempRegister(void);
string emitCallBeforeCode(void);
string emitCallAfterCode(void);
void releaseTempReg(void);

#endif /* genCode_hpp */
