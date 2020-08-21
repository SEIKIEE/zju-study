#include "CodeGen.h"

int curLabel = 0; // needed in using float and string
ofstream ofs;
vector<string> dataLabel;

void OpenCodeGen() {
	ofs.open("outputMips.asm", ofstream::out); 
}
void CloseCodeGen() {
	ofs.close();
}

void CodeGen(const char * arg0, const char * arg1, const char * arg2, const char * arg3)
{
	ofs << arg0 <<' '<< arg1 <<' '<< arg2 <<' '<< arg3<<'\n';
}
void CodeGen(const char * arg0, const char * arg1, int arg2, const char * arg3)
{
	ofs << arg0 << ' ' << arg1 << ' ' << arg2 << ' ' << arg3 << '\n';
}

// generate string label, push it into dataStr
// type : 1) .asciiz 2) .float for this program
// lexeme: 1) string  2) float  
string GenStringLabel(const char * type,const char * lexeme) {
	stringstream ss1;
	ss1 << "Label" << curLabel; 
	string Label = ss1.str();
	
	stringstream ss2;
	ss2 << lexeme;
	string str = ss2.str();

	dataLabel.push_back(Label + ": ." + type + " " + str); // push string to dataStr
	curLabel++;
	return Label;
}

string GenFloatLabel(const char * type,const char * lexeme) {
	stringstream ss;
	ss << lexeme;
	string str = ss.str();

	stringstream ss2;
	ss2 << "Label" << curLabel;
	string Label = ss2.str();
	dataLabel.push_back(Label + ": ." + type + " " + lexeme); // push string to dataStr
	curLabel++;
	return Label;
}

void Prolog() {
	ofs << "#Prolog: " << endl;
	ofs << ".text " << endl;
	ofs << ".globl  main " << endl;
	ofs << "main: " << endl;
	ofs << "move  $fp  $sp \t\t " << endl;
	ofs << "la  $a0  ProgBegin " << endl;
	ofs << "li  $v0 4 " << endl;
	ofs << "syscall " << endl;
	ofs << "#End of Prolog" << endl;
	ofs << "\t#all code will go below here...\n";
}

void Postlog()
{
	ofs << "\n#Postlog:" << endl;
	ofs << "la  $a0  ProgEnd" << endl;
	ofs << "li  $v0  4" << endl;
	ofs << "syscall" << endl;
	ofs << "li  $v0  10" << endl;
	ofs << "syscall" << endl;
	ofs << "\n.data" << endl;
	ofs << "ProgBegin:  .asciiz \"Program Begin\\n\"" << endl;
	ofs << "ProgEnd:   .asciiz \"\\nProgram End\\n\"" << endl;
	ofs << "CR:" << " .asciiz " << "\"\\n\"" << endl; // added this for convenience in writeln
	for (int i = 0; i < dataLabel.size(); i++) {
		ofs << dataLabel[i] << '\n';
	}
}