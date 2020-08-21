
#ifndef _UTILITY_H_
#define _UTILITY_H_
#include "ErrorHander.h"

void convertToLittleCase(char *s); // convert to lit case

void getFirst(char * s, int n); // get first n characters

bool matchLet(char c); // match Let

bool matchDig(char c); // match Dig 

bool isContain(char c, char * str); // check c is in str

#endif // !_UTILITY_H_