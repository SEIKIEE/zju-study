#ifndef _SCAN_H_
#define _SCAN_H_

#define MAXTOKENLEN 40
#include "global.h"
extern char tokenString[MAXTOKENLEN+1];
extern char previoustokenString[MAXTOKENLEN+1];

TokenType getToken();

#endif
