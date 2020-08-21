#include "global.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "quadruple.h"
#include "analyze.h"
#include "visual.h"

FILE* source;
FILE* listing;
FILE* code;
FILE* visualTree;
FILE* ircode;

int lineno = 0;
int TraceScan = True;
int errFlag = 0;

Symtab dummySymtab;

pQuad QuadListHead;
pQuad QuadListEnd;

int main(int argc, const char* argv[])
{
    SyntaxTree syntaxTree;
    
    if(argc < 2)
    {
        printf("Enter the pascal_source_filename\n");
        return 0;
    }
    
    source = fopen(argv[1], "r");
    /* file not found */
    if (source == NULL) {
        printf("fatal error: file %s does not exists\n", argv[1]);
        return 1;
    }
    
    listing = fopen("tokens.txt", "w+");

    syntaxTree = parse();
    fclose(listing);

    visualTree = fopen("syntaxTree.txt", "w+");
    showSyntaxTree(syntaxTree);
    fclose(visualTree);

    dummySymtab = NULL;
    buildSymtab(syntaxTree, dummySymtab);
    if (syntaxTree == NULL || errFlag == 1) {
        printf("------------------------------Compile Error------------------------------\n");
        return 1;
    }
    
    ircode = fopen("ircode.txt", "w+");
    initQuadList();
    genCode(syntaxTree, "ircode");
    printIRcode();
    fclose(ircode);
        
    return 0;
}
