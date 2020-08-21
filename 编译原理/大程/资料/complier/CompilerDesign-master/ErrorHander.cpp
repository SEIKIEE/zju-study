
#include "ErrorHander.h"

//|-------------error warning variables-------------|
vector<string> warningScannerBuf; // C++ Lib vector<T>


//|-------store warning info into vector--------------|
void _warning(char * routine, int line, char * info)
{
	stringstream ss; //convert all parameters to string
	ss << routine << "\tline:" << line << "\ttoken:" << info;
	string errorMsg = ss.str();
	warningScannerBuf.push_back(errorMsg); // put into warning buffer
}

//|-----------------fatal error exit------------------|
void _fatal_error(char * msg)
{
	printf("Fatal error%s ", msg);
	exit(-1);
}

// routine : name of procedure  
// line: the line of program
// info: info of warning
//"Fatal Error: syntax error(parser)"
void _fatal_error(char * routine, int line, char * info)
{
	stringstream ss; //convert all parameters to string
	ss <<"Terminating: "<< routine << "\tline:" << line << "\ttoken:" << info;
	string errorMsg = ss.str();
	warningScannerBuf.push_back(errorMsg); // put into warning buffer
	WriteErrorInfo();
	printf(" Terminating: [%s] ", routine);
	printf(" line: [%d] ", line);
	printf(" token: [%s]: ", info);
	exit(-1);
}

//|------------- write error to file-----------------------|
void _writeErrorInfo(FILE *file)
{
	if (file == NULL) return;

	char msg[1024];

	fprintf_s(file, "\n|=========== %s\t%d ==========|\n", "warning:", warningScannerBuf.size());

	for (auto i = warningScannerBuf.begin(); i < warningScannerBuf.end(); i++) {
		strcpy(msg, (*i).c_str());
		fprintf_s(file, "%s\n", msg);
	}
}