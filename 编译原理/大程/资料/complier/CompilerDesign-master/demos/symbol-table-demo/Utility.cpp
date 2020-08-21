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

bool isAlphabetic(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
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