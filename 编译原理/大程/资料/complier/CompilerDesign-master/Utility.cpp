#include <string.h>
#include "Utility.h"

// NOT case sensitive, so convert to LittleCase
void convertToLittleCase(char *s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
}

// only the first num characters are significant.
void getFirst(char * s, int n)
{
	if (((int)strlen(s)) <= n)	// qualify length smaller than n
	{
		return;
	}
	char cpy[256];
	strcpy(cpy, s);
	strncpy(s, cpy, n);
	s[n] = '\0';	// important!!!
}


// match Let
bool matchLet(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	return false;
}

// match Dig 
bool matchDig(char c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
//
bool isContain(char c, char * str)
{
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == c)
			return true;
		i++;
	}
	return false;
}