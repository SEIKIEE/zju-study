#ifndef quadruple_h
#define quadruple_h

#include "global.h"

extern FILE* ircode;

/*#define ASSIGN 0
 #define PLUS 1
 #define SUB 2
 #define MUL 3
 #define RDIV 4
 #define MINUS 5
 #define DIV 6
 #define MOD 7
 #define EQ 8
 #define LT 9
 #define GT 10
 #define LE 11
 #define GE 12
 #define NE 13
 #define OFFE 14     //[]=
 #define EOFF 15
 #define GOTO 16
 #define PARAM 17
 #define CALL 18*/

//typedef enum {};
typedef enum {
    constassign, assign, plus, sub, minus, mul, divide, mod,
    andi, ori, noti,
    lt, eq, gt, le, ge, ne,
    array1, array2,
    if_goto, if_f_goto, lab, gotolab,
    funcf, entryf, ret, retwithvalue, ret0, beginargs, argparam, call,
    param, valuefromcall,
    //param, call, calln,
    wt, wtln, rd
} QuadOpKind;

typedef enum { Empty, IntConst, RealConst, String }AddrKind;

typedef struct {
    AddrKind kind;
    union {
        int intVal;
        float realVal;
        char* name;
    } contents;
    
} Address;

typedef struct Quad{
    QuadOpKind op;
    Address addr1, addr2, addr3;
    struct Quad * next;
} * pQuad;

extern pQuad QuadListHead;
extern pQuad QuadListEnd;
void initQuadList();
void genCode(SyntaxTree node, char* resName);
void printQuad(int, pQuad);
void printIRcode();

#endif /* quadruple_h */
