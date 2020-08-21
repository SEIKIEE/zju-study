#include "global.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "CodeGenerater.h"

char filename[30] = "test.pas";
FILE * source ;
FILE * listing ;
int TraceScan = True;
int lineno = 0;

void help(void)
{
    printf("The Usage: compiler pascal_source_filename [assemble_filename]\n");
}

//
int err_flag = 0;

int main(int argc, char **argv)
{
	TreeNode* syntax_tree;
	//char* outputfile;
	if(argc < 2) {
		help();
		exit(1);
	}
    source = fopen(argv[1], "r");
    
    //file not found
    if (source == NULL) {
        printf("fatal error: file %s does not exists\n", argv[1]);
        return 1;
    }
    
    //for debug
    listing = fopen("tmp.list", "w+");
    
	if(argc == 3){
		InitialGenerater(argv[2]);
	}
	else{
		InitialGenerater("out.asm");
	}
   
    syntax_tree = parse();
    
    if (syntax_tree == NULL || err_flag == 1) {
        printf("compile error.\n");
        return 1;
    }
    
    //code generation
    BuildCode(syntax_tree);

	fclose(listing);
	
    return 0;

}





