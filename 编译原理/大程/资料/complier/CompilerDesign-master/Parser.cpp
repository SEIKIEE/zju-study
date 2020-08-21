#include "Parser.h"

int CurrentOffSet = 0; // offset in data stack for mips
int loopNum = 0; // for loopstat
int ifNum = 0; // for ifstat and refactor

void match(Tokens  &tok, int ExpTokenNum)
{
	if (tok.number != ExpTokenNum)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
	tok = GetToken();	//get next token
}

// (1) program : PROGTOK IDTOK¡¯(¡® ¡®)¡¯  [CONSTTOK constdecl {constdecl}]
// 	[VARTOK vardecl{ vardecl }]  BEGINTOK statmt{ ¡®; ¡¯ statmt } ENDTOK ¡®.¡¯
bool program()
{
	Tokens tok;
	tok = GetToken(); // just get token, detials hides in scanner

					  // match FIRST 
	if (tok.number != PROGTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme); // if First not matched, recovery error later...
	printf("1\t");

	match(tok, PROGTOK);
	match(tok, IDTOK);
	match(tok, LEFTPARENTHESIS);
	match(tok, RIGHTPARENTHESIS);

	Prolog();

	//[CONSTTOK constdecl{ constdecl }]
	if (tok.number == CONSTTOK)
	{
		match(tok, CONSTTOK);
		constdecl(tok);				// call constdecl
									/*{constdecl}*/
		while (tok.number == IDTOK)
		{
			constdecl(tok);
		}
	}

	/*[VARTOK vardecl{ vardecl }]*/
	if (tok.number == VARTOK) {
		match(tok, VARTOK);
		vardecl(tok);
		while (tok.number == IDTOK)	// match first of vardecl
		{
			vardecl(tok);
		}
	}

	match(tok, BEGINTOK);
	openScope(); // after BEGINTOK open a scope in ST

	statmt(tok);

	/*{¡®;¡¯ statmt}*/
	while (tok.number == SEMICOLON) {
		match(tok, SEMICOLON);
		statmt(tok);
	}
	match(tok, ENDTOK);
	closeScope(); // after ENDTOK close a scope in ST

	match(tok, DOT);
	match(tok, EOF);
	Postlog(); // write data in the end of mips file

	return true;
}
//(2¡¯) constdecl: IDTOK '=' LITTOK ';'
void constdecl(Tokens &tok) {
	/* FIRST(constdecl)*/
	if (tok.number != IDTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);

	printf("2'\t");

	char locName[IDMAXLENGTH];  // store Id name
	char locValue[IDMAXLENGTH];
	strcpy_s(locName, tok.lexeme);

	match(tok, IDTOK);
	if (tok.lexeme[0] != '=')
		_warning("Parser Error unmatched type", GetLine(), tok.lexeme);
	tok = GetToken();

	char type = GetTypeFrom(tok.lexeme);  // store type name 

	strcpy_s(locValue, tok.lexeme);
	match(tok, LITTOK);
	match(tok, SEMICOLON);

	/* check the current record is in symbol table */
	if (findInCurScope(locName) != nullptr)
		_warning("Parser Error: Duplicate definition", GetLine(), locName);																	/* insert it*/
	else
		insert(locName, type, CurrentOffSet, 0);	//< no found in symbolTable, insert it
	CodeGen("li", "$t0", locValue, "");
	CodeGen("sw ", "$t0 ", CurrentOffSet, "($fp)");
	CurrentOffSet -= 4;
}

//(2)  vardecl: IDTOK ':' BASTYPETOK  ';'
void vardecl(Tokens & tok)
{
	if (tok.number != IDTOK)
		_fatal_error("Parser Error unmatch", GetLine(), tok.lexeme);
	printf("2\t");

	//backup name
	char name[IDMAXLENGTH];
	strcpy_s(name, tok.lexeme);

	match(tok, IDTOK);
	match(tok, COLON);
	char type = tok.lexeme[0];
	match(tok, BASTYPETOK);
	match(tok, SEMICOLON);

	/* check the current record is in symbol table */
	if (findInCurScope(name) != nullptr)
		_warning("Parser + ST Error: Duplicate definition", GetLine(), name);																/* insert it*/
	else
		insert(name, type, CurrentOffSet, 1);	// no found in symbolTable, insert it
	CurrentOffSet -= 4;
}

//(3) statmt: assignstat| ifstat| readstat| writestat| blockst| loopst
void statmt(Tokens &tok) {
	// FIRST of statmt
	switch (tok.number)
	{
	case IDTOK: printf("3\t");
		assignstat(tok);
		break;
	case IFTOK:
		printf("3\t");
		ifstat(tok);
		break;
	case READTOK:
		printf("3\t");
		readstat(tok);
		break;
	case WRITETOK:
		printf("3\t");
		writestat(tok);
		break;
	case VARTOK:
		printf("3\t");
		blockst(tok);
		break;
	case BEGINTOK:
		printf("3\t");
		blockst(tok);
		break;
	case WHILETOK:
		printf("3\t");
		loopst(tok);
		break;
	default: _fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}
}

//(4) assignstat: idnonterm  ASTOK express 
void assignstat(Tokens &tok) {
	ExpressionRecord er; // local vars
	SymTabRecord *ST_Ptr = nullptr; // local vars
	int localLoc = CurrentOffSet;  // for recovery

	if (tok.number != IDTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
	printf("4\t");

	idnonterm(tok, ST_Ptr);  // now ST_Ptr, if not null has type and location
	match(tok, ASTOK);
	express(tok, er); // now er has a type and a location
	// match type
	if (ST_Ptr->type == 'r'&&er.type == 'r') {
		CodeGen("l.s", "$f0", er.loc, "($fp)");
		CodeGen("s.s", "$f0", ST_Ptr->location, "($fp)");
	}
	else if (ST_Ptr->type == 'r'&&er.type == 'i') {
		CodeGen("l.s", "$f2", er.loc, "($fp)");
		CodeGen("cvt.s.w", "$f0", "$f2", ""); // convert to float
		CodeGen("s.s", "$f0", ST_Ptr->location, "($fp)");
	}
	else if (ST_Ptr->type == 'i'&&er.type == 'i' || ST_Ptr->type == 'b'&&er.type == 'b') {
		CodeGen("lw", "$t0", er.loc, "($fp)"); // Generate code to load er.loc into some register
		CodeGen("sw", "$t0", ST_Ptr->location, "($fp)"); // store this register into ST_Ptr.loc
	}
	else {
		_warning("CodeGen type no match", GetLine(), ST_Ptr->name); // NonFatalError
	}

	CurrentOffSet = localLoc; // important!!! recovery
}
//(5) ifstat: IFTOK express THENTOK  statmt  
void ifstat(Tokens &tok) {
	ExpressionRecord er;
	int locIfNum = ifNum;
	int localLoc  = CurrentOffSet;
	if (tok.number != IFTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
	printf("5\t");

	ifNum++; // incr ifNum
	match(tok, IFTOK);
	express(tok, er);
	CurrentOffSet = localLoc;
	if (er.type != 'b')
	{
		_warning("CodeGen Error unmatched type", GetLine(), tok.lexeme);
	}
	CodeGen("lw", "$t0", er.loc, "($fp)");
	CodeGen("beqz ", "$t0 ", i_str("endIf", locIfNum).c_str(), "");
	match(tok, THENTOK);
	statmt(tok);
	CodeGen(i_str("endIf", locIfNum).c_str(), ":", "", "");
}

//(6) readstat: READTOK '(' idnonterm ')' 
void readstat(Tokens &tok) {
	if (tok.number != READTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);

	printf("6\t");
	SymTabRecord * ST_Ptr = nullptr; // needed for call to idnonterm()
	char name[IDMAXLENGTH] = "";


	match(tok, READTOK);
	match(tok, LEFTPARENTHESIS);
	strcpy_s(name, tok.lexeme);
	idnonterm(tok, ST_Ptr);
	match(tok, RIGHTPARENTHESIS);
	if (ST_Ptr->isVar == 0)
	{
		_warning("CodeGen Error constant cannot read", GetLine(), name);
		return;
	}
	switch (ST_Ptr->type)
	{
	case 'r':
		CodeGen("li", "$v0", 6, ""); // 6 is for read float
		CodeGen("syscall", "", "", "");
		CodeGen("s.s", "$f0", ST_Ptr->location, "($fp)");
		break;
	case 'b':
		_warning("CodeGen Error boolean type cannot read", GetLine(), name);
		break;
	default:
		CodeGen("li", "$v0", 5, ""); // 5 is for read integer
		CodeGen("syscall", "", "", "");
		CodeGen("sw", "$v0", ST_Ptr->location, "($fp)");
		break;
	}
}

//(7) writestat: WRITETOK '(' (STRLITTOK | express) ')' 
void writestat(Tokens &tok) {
	if (tok.number != WRITETOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);

	printf("7\t");
	ExpressionRecord er;
	bool isWriteln = false;

	if (strlen(tok.lexeme)>6)  // wrtieln
		isWriteln = true;

	match(tok, WRITETOK);
	match(tok, LEFTPARENTHESIS);

	//FIRST of express : NOTTOK IDTOK LITTOK (
	switch (tok.number)
	{
	case STRLITTOK:
		CodeGen("la", "$a0", GenStringLabel("asciiz", tok.lexeme).c_str(), "");
		CodeGen("li", "$v0", 4, "");
		CodeGen("syscall", "", "", "");
		match(tok, STRLITTOK);
		break;
	case NOTTOK:
		// will do in LITTOK
	case IDTOK:
		// will do in LITTOK
	case LITTOK:
		express(tok, er);
		if (er.type == 'i' || er.type == 'b') { // integer boolean
			CodeGen("lw", "$a0 ", er.loc, "($fp)");
			CodeGen("li", "$v0 ", 1, ""); // print integer
			CodeGen("syscall", "", "", "");
		}
		else { // float
			CodeGen("l.s", "$f0 ", er.loc, "($fp)");
			CodeGen("mov.s", "$f12", "$f0", "");
			CodeGen("li", "$v0", 2, ""); // print float
			CodeGen("syscall", "", "", "");
		}
		break;
	case LEFTPARENTHESIS:
		match(tok, LEFTPARENTHESIS);
		express(tok, er);
		match(tok, RIGHTPARENTHESIS);
		break;
	default:
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}

	if (isWriteln == true)
	{
		CodeGen("la", "$a0", "CR", "");
		CodeGen("li", "$v0", 4, "");
		CodeGen("syscall", "", "", "");
	}
	match(tok, RIGHTPARENTHESIS);
}

//(8) whilest: WHILETOK express DOTOK statmt 
void loopst(Tokens &tok) {
	if (tok.number != WHILETOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);

	printf("8\t");
	ExpressionRecord er;
	int localLoc = CurrentOffSet;  // for recovery
	int locLoopNum = loopNum;

	match(tok, WHILETOK);

	CodeGen(i_str("topLoop", locLoopNum).c_str(), ":", "", ""); //top loop label
	loopNum++;
	express(tok, er);
	if (er.type != 'b')
	{
		_warning("CodeGen Error unmatched type", GetLine(), tok.lexeme);
	}
	CurrentOffSet = localLoc;

	CodeGen("lw", "$t0", er.loc, "($fp)");
	CodeGen("beqz ", "$t0", i_str("endLoop", locLoopNum).c_str(), "");
	match(tok, DOTOK);
	statmt(tok);
	CodeGen("j", (i_str("topLoop", locLoopNum)).c_str(), "", "");
	CodeGen(i_str("endLoop", locLoopNum).c_str(), ":", "", "");
}

//(9) blockst: [VARTOK vardecl {vardecl}]   BEGINTOK   statmt {;statmt} ENDTOK   
void blockst(Tokens &tok) {
	// [VARTOK vardecl {vardecl}]
	if (tok.number == VARTOK) {
		match(tok, VARTOK);	//DOTOK
		vardecl(tok);

		while (tok.number == IDTOK)
		{
			vardecl(tok);
		}
	}
	if (tok.number == BEGINTOK) {
		printf("9\t");

		match(tok, BEGINTOK);
		openScope(); // after BEGINTOK close scope in ST
		statmt(tok);

		//{;statmt}
		while (tok.number == SEMICOLON) {
			match(tok, SEMICOLON);
			statmt(tok);
		}
		match(tok, ENDTOK);
		closeScope(); // after ENDTOK close scope in ST
	}
	else {
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
	}
}
//(10) express: term { ADDOPTOK term }
void express(Tokens &tok, ExpressionRecord &er) {
	int backupLoc = CurrentOffSet; // back up the current offset, needed recovery in the end of every opeartion
	ExpressionRecord lop;  // copy the incoming parameter, as left operand
						   /* FIRST(express) */
	switch (tok.number)
	{
	case NOTTOK:
		printf("10\t");
		break;
	case IDTOK:
		printf("10\t");
		break;
	case LITTOK:
		printf("10\t");
		break;
	case LEFTPARENTHESIS:
		printf("10\t");
		break;
	default:
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}
	term(tok, er);

	while (tok.number == ADDOPTOK)
	{
		lop = er;
		char ch = tok.lexeme[0]; //rember the addop

		match(tok, ADDOPTOK);
		term(tok, er); // get the right operand
		CurrentOffSet = backupLoc;  // important !!!
		string st; // which operaion will we generate
		switch (ch)
		{
		case '+':
			st = "add";
			break;
		case '-':
			st = "sub";
			break;
		case 'o':
			st = "or";
			break;
		}
		if (ch == 'o' &&lop.type == 'b'&&er.type == 'b')
		{
			CodeGen("lw", "$t0", lop.loc, "($fp)");
			CodeGen("lw", "$t1", er.loc, "($fp)");
			CodeGen(st.c_str(), "$t0", "$t1", "$t0");
			CodeGen("sw", "$t0", CurrentOffSet, "($fp)");
			er.loc = CurrentOffSet;
			CurrentOffSet -= 4;
		}
		else if (ch == '+' || ch == '-') {
			if (lop.type == 'i'&&er.type == 'i') { // integer
				CodeGen("lw", "$t0", lop.loc, "($fp)");
				CodeGen("lw", "$t1", er.loc, "($fp)");
				CodeGen(st.c_str(), "$t0", "$t0", "$t1");
				CodeGen("sw", "$t0", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;
			}
			else if (lop.type == 'i'&&er.type == 'r') {
				st = st + ".s";
				CodeGen("l.s", "$f2", lop.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen("cvt.s.w", "$f0", "$f2", ""); // convert to float
				CodeGen("l.s", "$f1", er.loc, "($fp)");
				CodeGen(st.c_str(), "$f0", "$f0", "$f1");
				CodeGen("s.s", "$f0", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;

			}
			else if (lop.type == 'r'&&er.type == 'i') {
				st = st + ".s";
				CodeGen("l.s", "$f0", lop.loc, "($fp)");
				CodeGen("l.s", "$f2", er.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen("cvt.s.w", "$f1", "$f2", ""); // convert to float
				CodeGen(st.c_str(), "$f0", "$f0", "$f1");
				CodeGen("s.s", "$f0", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				er.type = 'r'; // necessary for er.type is integer
				CurrentOffSet -= 4;

			}
			else if (lop.type == 'r'&&er.type == 'r') {
				st = st + ".s";
				CodeGen("l.s", "$f0", lop.loc, "($fp)");
				CodeGen("l.s", "$f1", er.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen(st.c_str(), "$f0", "$f0", "$f1");
				CodeGen("s.s", "$f0", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;
			}
			else {// no match
				_warning("Parser Error unmatched", GetLine(), tok.lexeme);
			}
		}
		else {// no match
			_warning("Parser Error unmatched", GetLine(), tok.lexeme);
		}
	}
}

//(11) term: relfactor {MULOPTOK relfactor}  
void term(Tokens &tok, ExpressionRecord &er) {
	int backupLoc = CurrentOffSet;
	ExpressionRecord lop;

	/* FIRST(term) */
	switch (tok.number)
	{
	case NOTTOK:
		printf("11\t");
		break;
	case IDTOK:
		printf("11\t");
		break;
	case LITTOK:
		printf("11\t");
		break;
	case LEFTPARENTHESIS:
		printf("11\t");
		break;
	default:
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}

	relfact(tok, er);
	while (tok.number == MULOPTOK)
	{
		lop = er; // copy er, as left operand
		char ch = tok.lexeme[0]; //rember the mulop

		match(tok, MULOPTOK);
		relfact(tok, er); //get the right operand
		CurrentOffSet = backupLoc;  // important !!!

		string st; // which operaion will we generate
		switch (ch)
		{
		case '*': st = "mul"; break;
		case '/': st = "div"; break;
		case 'd': st = "div"; break;
		case 'm': st = "div"; break;
		case 'a': st = "and"; break;
		}

		if (ch == 'a' &&lop.type == 'b'&&er.type == 'b')
		{
			CodeGen("lw", "$t0", lop.loc, "($fp)");
			CodeGen("lw", "$t1", er.loc, "($fp)");
			CodeGen(st.c_str(), "$t0", "$t0", "$t1");
			CodeGen("sw", "$t0", CurrentOffSet, "($fp)"); // codegen sw of register $t0 into currentOffset and increment it by 4
			er.loc = CurrentOffSet; // set er.type to correct type if necessary, er.loc to currentOffset -4
			CurrentOffSet -= 4;
		}
		else if (ch == '*' || ch == '/' || ch == 'd') {
			if (lop.type == 'i'&&er.type == 'i') { // integer
				CodeGen("lw", "$t0", lop.loc, "($fp)");
				CodeGen("lw", "$t1", er.loc, "($fp)");
				CodeGen(st.c_str(), "$t2", "$t0", "$t1");

				CodeGen("sw", "$t2", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;
			}
			else if (lop.type == 'i'&&er.type == 'r') {
				st = st + ".s";
				CodeGen("l.s", "$f2", lop.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen("cvt.s.w", "$f0", "$f2", ""); // convert to float
				CodeGen("l.s", "$f1", er.loc, "($fp)");
				CodeGen(st.c_str(), "$f3", "$f0", "$f1"); // set $f0 as $f0 times $f1
				CodeGen("s.s", "$f3", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;

			}
			else if (lop.type == 'r'&&er.type == 'i') {
				st = st + ".s";
				CodeGen("l.s", "$f0", lop.loc, "($fp)");
				CodeGen("l.s", "$f2", er.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen("cvt.s.w", "$f1", "$f2", ""); // convert to float
				CodeGen(st.c_str(), "$f3", "$f0", "$f1"); //  set $f0 as $f0 times $f1
				CodeGen("s.s", "$f3", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				er.type = 'r'; // necessary for er.type is integer
				CurrentOffSet -= 4;
			}
			else if (lop.type == 'r'&&er.type == 'r') {
				st = st + ".s";
				CodeGen("l.s", "$f0", lop.loc, "($fp)");
				CodeGen("l.s", "$f1", er.loc, "($fp)"); // f2 is tmp register for convert
				CodeGen(st.c_str(), "$f3", "$f0", "$f1"); // set $f0 as $f0 times $f1
				CodeGen("s.s", "$f3", CurrentOffSet, "($fp)");
				er.loc = CurrentOffSet;
				CurrentOffSet -= 4;
			}
			else {// no match
				_warning("Parser Error unmatched", GetLine(), tok.lexeme);
			}
		}
		else if (ch == 'm' && lop.type == 'i' && er.type == 'i') {
			CodeGen("lw", "$t0", lop.loc, "($fp)");
			CodeGen("lw", "$t1", er.loc, "($fp)");
			CodeGen(st.c_str(), "", "$t0", "$t1");
			CodeGen("mfhi", "$t0", "", "");
			CodeGen("sw", "$t0", CurrentOffSet, "($fp)");
			er.loc = CurrentOffSet;
			CurrentOffSet -= 4;
		}
		else {// no match
			_warning("Parser Error unmatched", GetLine(), tok.lexeme);
		}
	}
}

//(12) relfact: factor  [ RELOPTOK factor ]
void relfact(Tokens &tok, ExpressionRecord &er) {

	ExpressionRecord lop;
	int backupLoc = CurrentOffSet;
	//int locIfNum = ifNum;

	/*FIRST(factor)*/
	switch (tok.number)
	{
	case NOTTOK:
		printf("12\t");
		break;
	case IDTOK:
		printf("12\t");
		break;
	case LITTOK:
		printf("12\t");
		break;
	case LEFTPARENTHESIS:
		printf("12\t");
		break;
	default:
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}
	factor(tok, er);
	if (tok.number == RELOPTOK)
	{
		lop = er;
		char ch = tok.lexeme[0]; // rember the relop
		string st; // which operaion will we generate
		match(tok, RELOPTOK);
		factor(tok, er);
		CurrentOffSet = backupLoc;  // important !!!

		switch (ch)
		{
		case '=': st = "eq";  break;
		case '>': st = "gt"; break;
		case '<': st = "lt"; break;
		}
		if ((lop.type == 'i' && er.type == 'i') // integer 
			|| (lop.type == 'b' && er.type == 'b')) { // boolean
			st = "s" + st; // generate operator
			CodeGen("lw", "$t0", lop.loc, "($fp)");
			CodeGen("lw", "$t1", er.loc, "($fp)");
			CodeGen(st.c_str(),"$t2","$t0","$t1");
			CodeGen("sw", "$t2", CurrentOffSet, "($fp)");
			er.loc = CurrentOffSet;
			er.type = 'b';
			CurrentOffSet -= 4;
		}
		else if (lop.type == 'r' || er.type == 'r') { // real
			int locIfNum = ifNum;
			ifNum++;
			CodeGen("li", "$t0", "0", ""); // init $t0
			CodeGen("l.s", "$f0", lop.loc, "($fp)");
			CodeGen("l.s", "$f2", er.loc, "($fp)");
			if (lop.type == 'r' && er.type == 'r')
			{
			}
			else if (lop.type == 'r' && er.type == 'i'){
				CodeGen("cvt.s.w", "$f4", "$f2", ""); // convert to float
				CodeGen("mov.s", "$f2", "$f4", "");
			}
			else if (lop.type == 'i' && er.type == 'r') {
				CodeGen("cvt.s.w", "$f4", "$f0", ""); // convert to float
				CodeGen("mov.s", "$f0", "$f4", "");
			}
			st = "c." + st + ".s"; // generate operator, like "c.eq.s"			
			
			if (ch == '>') { // since not instruction of "c.gt.s"
				CodeGen("c.lt.s","", "$f2", "$f0"); // a trick for >
			}
			else
			{
				CodeGen(st.c_str(), "", "$f0", "$f2"); // set fp flag as 0, when it is true
			}
			CodeGen("bc1f", i_str("endIf", locIfNum).c_str(), "", ""); 
			CodeGen("li", "$t0", "1", ""); // set $t0 1
			CodeGen(i_str("endIf", locIfNum).c_str(), ":", "", "");
			CodeGen("sw", "$t0", CurrentOffSet, "($fp)");
			er.loc = CurrentOffSet;
			er.type = 'b';
			CurrentOffSet -= 4;
		}
		else {
			_warning("CodeGen Error unmatched type", GetLine(), tok.lexeme);
		}
	}

}
//(13) factor: NOTTOK  factor    |   idnonterm   |   LITTOK  | '(' express ')'
void factor(Tokens &tok, ExpressionRecord & er) {
	SymTabRecord * ST_Ptr = nullptr; //needed fo call to idnonterm

	switch (tok.number)
	{
	case NOTTOK:
		printf("13\t");
		match(tok, NOTTOK);
		factor(tok, er);
		if (er.type != 'b')
			_warning("GenCode Error unmatched type", GetLine(), tok.lexeme);
		CodeGen("lw", "$t0", er.loc, "($fp)");
		CodeGen("xori ", "$t0 ", 1, ""); // 0 xori 1 = 1 --- 1 xori 1 = 0
		CodeGen("sw ", "$t0 ", er.loc, "($fp)");
		break;
	case IDTOK:
		printf("13\t");
		idnonterm(tok, ST_Ptr); // get ST_Ptr
		if (ST_Ptr == nullptr)
		{
			_warning("Parser Error no found", GetLine(), tok.lexeme);
		}
		else {
			er.type = ST_Ptr->type;
			er.loc = ST_Ptr->location;
		}
		break;
	case LITTOK:
		printf("13\t");
		er.type = GetTypeFrom(tok.lexeme);
		er.loc = CurrentOffSet;
		CurrentOffSet -= 4;
		switch (er.type)
		{
		case 'b':	//boolean
			if (tok.lexeme[0] == 't') { //true
				CodeGen("li", "$t0 ", 1, "");
				CodeGen("sw", "$t0 ", er.loc, "($fp)");
			}
			else {
				CodeGen("li", "$t0 ", 0, "");
				CodeGen("sw", "$t0 ", er.loc, "($fp)");
			}
			break;
		case 'i':	//integer
			CodeGen("li", "$t0 ", tok.lexeme, "");
			CodeGen("sw", "$t0 ", er.loc, "($fp)");
			break;
		case 'r':	//real
			CodeGen("l.s ", "$f0 ", GenFloatLabel("float", tok.lexeme).c_str(), "");
			CodeGen("s.s", "$f0 ", er.loc, "($fp)");
			break;
		default:
			break;
		}
		match(tok, LITTOK);
		break;
	case LEFTPARENTHESIS:
		printf("13\t");
		match(tok, LEFTPARENTHESIS);
		express(tok, er);
		match(tok, RIGHTPARENTHESIS);
		break;
	default:
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
		break;
	}
}
//(14) idnonterm: IDTOK
void idnonterm(Tokens &tok, SymTabRecord  * &ST_Ptr) {
	/* the first of term*/
	if (tok.number != IDTOK)
		_fatal_error("Parser no match", GetLine(), tok.lexeme);
	printf("14\t");

	char name[IDMAXLENGTH] = ""; // store lexeme in local
	strcpy_s(name, tok.lexeme);

	match(tok, IDTOK);

	ST_Ptr = findInAllScopes(name);
	if (ST_Ptr == nullptr)
		_fatal_error("Parser + ST Error: no defintion", GetLine(), name);
}

//|----------------------assist-----------------------------------|
char GetTypeFrom(char *type)
{
	if (type[0] == 't' || type[0] == 'f')
		return 'b';  // boolean
	else if (isContain('.', type)) // isContain is in Utility.h
		return 'r';  // real
	else
		return 'i';  // integer
}
string i_str(const char * c, const int i) {
	stringstream ss;
	ss << c << i;
	return ss.str();
}
//|-------------------- all below is for test -------------------|
void testParser()
{
	bool result = false;
	initSymTable();
	InitScanner();
	OpenCodeGen();
	result = program();

	if (result == true) {
		printf("successful parsering!\n");
	}

	_writeErrorInfo(GetListingFile());
	CloseCodeGen();
	displaySymTable(GetListingFile());
}
