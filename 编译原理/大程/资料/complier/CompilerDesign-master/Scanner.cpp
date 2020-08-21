#include "Scanner.h"
using namespace std;
//|------------------main variables-------------------|

//|-----------const variables-------------------|
const int BUF_MAX_LEN = 4096;	// the max num of characters in a line
const int DEFAULT_TOKEN_NUM = -99; // default token number
const int RESERVED_NUM = 7; // num of reserved characters
const int KEYWORD_NUM = 22; // num of keywords
const char SOURCE_PATH[64] = "in.txt"; // path of source file 
const char TOKEN_FILE_PATH[128] = "tokenFile.txt"; // path of output token
const char LISTING_FILE_PATH[128] = "listingFile.txt"; // path of echo input with line num and additional info

//|----------------------------------------------|
FILE *infile;   // the path of source file
FILE *tokenFile;  // store tokens
FILE *listingFile; //echos the input file, with addition of info

char buffer[BUF_MAX_LEN];   // a line of char in source file
int line;   // line number of source file
int curIndex; // current index in buffer[]

Tokens reserved[RESERVED_NUM]; //store special single character
Tokens keyword[KEYWORD_NUM]; // stroe key word

//|------------------main routines-------------------|
// get token
Tokens GetToken()
{
	Tokens token;
	InitTokens(token);

	do {
		/*skip space and comments*/
		if (SkipSpace() == true) continue;
		if (SkipComments() == true) continue;

		/*match EOF*/
		if ((token = MatchEnd()).number != DEFAULT_TOKEN_NUM)
			return token;

		/*match Id*/
		else if ((token = MatchId()).number != DEFAULT_TOKEN_NUM)
		{
			MatchKeyword(token);
			return token;
		}

		/*match Lit*/
		else if ((token = MatchNumber()).number != DEFAULT_TOKEN_NUM)
			return token;

		/*string*/
		else if ((token = MatchString()).number != DEFAULT_TOKEN_NUM)
			return token;

		/*colonequal and colon*/
		else if ((token = MatchColonEqual()).number != DEFAULT_TOKEN_NUM)
			return token;

		/*single symbol*/
		else if ((token = MatchReserved()).number != DEFAULT_TOKEN_NUM)
			return token;

		else {//default
			char c = GetChar(); //skip illegal character 
			char buf[2] = "";
			buf[0] = c;
			_warning("Lexical Error: illegal character ",GetLine(),buf);
		}
	} while (1); // if get token return immediately.
	return token;
}

// write token in tokenFile 
void WriteTokenFile(Tokens tokenRec)
{
	fprintf_s(tokenFile, "%-8d %s\n", tokenRec.number, tokenRec.lexeme);
}

// echos the input file in listingFile, with line num
// called by : FillBuffer()
void EchosInputWithLine() {
	fprintf_s(listingFile, "%-3d %s", line, buffer);
}
FILE * GetListingFile() {
	return listingFile;
}

// called when the end of file
// write warning or error info in listing file
void WriteErrorInfo()
{
	_writeErrorInfo(listingFile);
}

// file path of input 
void InitScanner()
{
	OpenFile();

	/*init variables*/
	line = 0;  //the begin of a line
	curIndex = 0;
	InitReserved();
	InitKeyword();
}

// open input and output file
void OpenFile()
{
	/*open file*/
	infile = fopen(SOURCE_PATH, "r");
	if (infile == NULL)
	{
		_fatal_error("Error: Could not open the in.txt file!");
	}
	tokenFile = fopen(TOKEN_FILE_PATH , "w");
	if (tokenFile == NULL)
	{
		_fatal_error("Error: Could not open the tokenFile.txt file!");
	}
	listingFile = fopen(LISTING_FILE_PATH, "w");
	if (listingFile == NULL)
	{
		_fatal_error("Error: Could not open the listingFile.txt file!");
	}
}

// close input and output file
void CloseFile()
{
	fclose(infile);
	fclose(tokenFile);
	fclose(listingFile);
}


// read one line of input file, putting it in buffer[] of char 
// for GetChar
void FillBuffer()
{
	char * s = fgets(buffer, sizeof(buffer), infile);
	if (s == NULL)  // end of the file
	{
		*(buffer) = EOF;  // mark EOF (important!!!)
		return;
	}
	else 
	{
		line++;  // line incr
		EchosInputWithLine(); //echo input in listing file
	}
}

// get char from buffer
char GetChar() 
{
	if (buffer[curIndex] == '\0') // refill, if buffer is empty
	{
		FillBuffer();
		curIndex = 0; // reset curIndex to 0
	} // endif
	return buffer[curIndex++];
}

int GetLine()
{
	return line;
}

// skip space: space, tab, newline
// return : true if the first character is space 
bool SkipSpace()
{
	bool result = false;
	char c;

	c = GetChar();
	if(c == ' ' || c == '\t' || c == '\n') 
	{
		result = true;
	}
	while ( c == ' ' || c == '\t' || c == '\n')
	{ c = GetChar(); } 
	
	curIndex--; // move left one index 
	return result;
}

// (*.....*)
bool SkipComments() // skip comments
{
	bool result = false;
	char c = GetChar();

	while (c == '(') 
	{
		c = GetChar();

		if (c != '*') // no backup ( rightnow, backup in MatchReserve
		{
			curIndex -= 2; //move left two index
			return false; 
		} //endif

		result = true; // mark true, after doing (*
		do {
			do {
				c = GetChar();
			} while (c != '*'&& c != EOF);// endwhile
			c = GetChar();
		} while (c != ')'&& c != EOF);//endwhile
		c = GetChar();
	}

	curIndex--; // move left one index 
	return result;
}

// match EOF
Tokens MatchEnd()
{
	Tokens token;
	InitTokens(token);

	char c = GetChar();
	if(c == EOF)
	{
		strcpy(token.lexeme, "");
		token.number = EOF;
	}
	curIndex--; //move left 
	return token;
}

// match Identifier
// Let (Let|Dig)*
Tokens MatchId()
{
	Tokens token;
	InitTokens(token);

	char c = GetChar();
	/*	step 1: match the 1st char	*/
	if (matchLet(c)) {
		int begin = curIndex - 1;
		/*	step 2: every character after 1st, which meets the identifier, loop	*/
		/*	\until a character not meets it	*/
		while (matchLet(c) || matchDig(c)) {
			c = GetChar();
		}
		curIndex--;
		if (curIndex - begin - 2 > ID_MAX_LENGTH) // the max of ID 256
		{
			_warning("Lexical Error: ",GetLine(),"the len of Id > MAX LENGTH 256");
			token = CompleteDFA(begin, begin + ID_MAX_LENGTH - 1, IDTOK);
		}
		token = CompleteDFA(begin, curIndex, IDTOK);

		getFirst(token.lexeme, ID_LENGTH); // get first 8
		convertToLittleCase(token.lexeme); // convert to Little Case
		
		return token;
	}
	else { 
		curIndex--; 
	}
	return token;
}

// must check before match dot
// Dig Dig*| Dig Dig*.Dig Dig*
Tokens MatchNumber()
{
	Tokens token;
	InitTokens(token);
	
	char c = GetChar();
    /*step 1: Digmatch the first char*/
	if (matchDig(c)) {
		int begin = curIndex - 1;

		/*step 2: Dig* every character after 1st, which equal dig, go to loop	*/
		/*\ until a character not meets it	*/
		while (matchDig(c)) {
			c = GetChar();
		}
		/*step 3: . check this number token do or not contains point */
		/*\ if not return */
		if (c!='.')
		{
			curIndex--;
			token = CompleteDFA(begin, curIndex, LITTOK);
			return token;
		}

		c = GetChar();
		/*step 4:	Dig	*/
		if (!matchDig(c)) //
		{
			curIndex-=2;
			token = CompleteDFA(begin,curIndex,LITTOK);
			return token;
		}
		/*	step 5: Dig* */
		while (matchDig(c)) {
			c = GetChar();
		}
		curIndex--;
		token = CompleteDFA(begin, curIndex, LITTOK);
		return token;
	}
	else { 
		curIndex--; 
	}
	return token;
}

// "" or ''
Tokens MatchString()
{
	Tokens token;
	InitTokens(token);

	char c = GetChar();
	if (c =='\"') // match "
	{
		int begin = curIndex-1;
		do {
			c = GetChar();
		} while (c!= '\"');
		token = CompleteDFA(begin, curIndex, STRLITTOK);
		//return token;
	}
	else if (c == '\'') {
		int begin = curIndex - 1;
		do {
			c = GetChar();
		} while (c != '\'');
		token = CompleteDFA(begin, curIndex, STRLITTOK);
		//return token;
	}
	else {
		curIndex--;
	}
	return token;
}

// := or :
Tokens MatchColonEqual()
{
	Tokens token;
	InitTokens(token);

	char c = GetChar();
	if (c != ':')
	{
		curIndex--;
	}
	else 
	{
		int begin = curIndex - 1;
		c = GetChar();
		if (c != '=') {
			curIndex--; // move left one character
			token = CompleteDFA(begin,curIndex,COLON);
		}
		else {
			token = CompleteDFA(begin, curIndex,ASTOK);
		}
	}	
	return token;
}

// match with reserved[], like + - *
Tokens MatchReserved()
{
	int begin = curIndex;

	Tokens token;
	InitTokens(token);
	char c = GetChar();

	/*Is c contained in reserved[]*/
	for (int i = 0; i < RESERVED_NUM; i++)
	{
		if (isContain(c, reserved[i].lexeme))
		{	
			token = CompleteDFA(begin, curIndex, reserved[i].number);
			return token;
		}
	}

	curIndex = begin; //fail to match
	return token;
}

// match lexeme is or not keyword
// if token.lexeme is same with one of keyword, change token.number
void MatchKeyword(Tokens &token)
{
	for (int i = 0; i < KEYWORD_NUM; i++)
	{
		if (!strcmp(token.lexeme, keyword[i].lexeme))//cmp with keyword 
		{
			token.number = keyword[i].number;
		}
	}
}

// CompleteDFA DFA, get current token 
Tokens CompleteDFA(int begin, int cur, int tokenNum)
{
	Tokens token;
	token.number = tokenNum;
	int i = begin;
	for (; i < cur; i++) // backup buffer[begin,cur) to lexeme[0,cur-begin-1]
	{
		token.lexeme[i - begin] = buffer[i];
	}
	token.lexeme[i - begin] = '\0';// end lexeme[cur-begin]
	return token;
}

// init keyword and reserved word
void InitKeyword() {
	keyword[0].number = 13;
	strcpy(keyword[0].lexeme, "program");
	keyword[1].number = 14;
	strcpy(keyword[1].lexeme, "begin");
	keyword[2].number = 15;
	strcpy(keyword[2].lexeme, "end");
	keyword[3].number = 16;
	strcpy(keyword[3].lexeme, "const");
	keyword[4].number = 17;
	strcpy(keyword[4].lexeme, "var");
	keyword[5].number = 18;
	strcpy(keyword[5].lexeme, "while");
	keyword[6].number = 19;
	strcpy(keyword[6].lexeme, "do");
	keyword[7].number = 20;
	strcpy(keyword[7].lexeme, "if");
	keyword[8].number = 21;
	strcpy(keyword[8].lexeme, "then");
	keyword[9].number = 22;
	strcpy(keyword[9].lexeme, "integer");
	keyword[10].number = 22;
	strcpy(keyword[10].lexeme, "real");
	keyword[11].number = 22;
	strcpy(keyword[11].lexeme, "boolean");
	keyword[12].number = 11;
	strcpy(keyword[12].lexeme, "mod");
	keyword[13].number = 11;
	strcpy(keyword[13].lexeme, "div");
	keyword[14].number = 11;
	strcpy(keyword[14].lexeme, "and");
	keyword[15].number = 10;
	strcpy(keyword[15].lexeme, "or");
	keyword[16].number = 23;
	strcpy(keyword[16].lexeme, "not");
	keyword[17].number = 24;
	strcpy(keyword[17].lexeme, "write");
	keyword[18].number = 24;
	strcpy(keyword[18].lexeme, "writeln");
	keyword[19].number = 25;
	strcpy(keyword[19].lexeme, "read");
	keyword[20].number = 2;
	strcpy(keyword[20].lexeme, "true");
	keyword[21].number = 2;
	strcpy(keyword[21].lexeme, "false");
}

void InitReserved()
{
	reserved[0].number = LEFTPARENTHESIS;
	strcpy(reserved[0].lexeme, "(");
	reserved[1].number = RIGHTPARENTHESIS;
	strcpy(reserved[1].lexeme, ")");
	reserved[2].number = SEMICOLON;
	strcpy(reserved[2].lexeme, ";");
	reserved[3].number = DOT;
	strcpy(reserved[3].lexeme, ".");
	reserved[4].number = ADDOPTOK;
	strcpy(reserved[4].lexeme, "+-");
	reserved[5].number = MULOPTOK;
	strcpy(reserved[5].lexeme, "*/");
	reserved[6].number = RELOPTOK;
	strcpy(reserved[6].lexeme, "<>=");
}

//|-------------------- all below is for test -------------------|
void testScanner()
{
	InitScanner();
	Tokens tokenRec;
	do{
		tokenRec = GetToken();
		WriteToScren(tokenRec);
		WriteTokenFile(tokenRec);
	} while (tokenRec.number != EOF);
	
	WriteErrorInfo();
	CloseFile();
}