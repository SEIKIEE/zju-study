
#ifndef _ERRORHANDER_H_
#define _ERRORHANDER_H_
#include <stdio.h>	// printf() print msg
#include <stdlib.h>	// exit() terminating program
#include <vector> //vector<T>
#include <string>
#include <sstream>	// for stringstream
#include "Scanner.h"

using namespace std;

//|-------------------warning ----------------------------|
// routine : name of procedure  
// line: the line of program
// info: info of warning 
void _warning(char * routine, int line, char *info);

//|-------------------fatal error ------------------------|
// routine : name of procedure  
// line: the line of program
// info: info of warning
void _fatal_error(char * routine, int line, char * info);

void _fatal_error(char *msg);

//|------------- write error to file-----------------------|
void _writeErrorInfo(FILE *file);

#endif // !_ERRORHANDER_H_