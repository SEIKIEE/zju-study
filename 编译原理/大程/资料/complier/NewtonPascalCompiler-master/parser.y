%{

#include "NewtonPascal.h"
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE SyntaxTree

%}


//terminal symbol
%token NAME
%token PROGRAM
%token CONST
%token TYPE
%token SYS_TYPE SYS_PROC SYS_FUNCT
%token ARRAY
%token OF
%token RECORD
%token BEGIN END
//token NULL
%token FUNCTION
%token PROCEDURE
%token VAR
%token READ
%token IF THEN ELSE
%token REPEAT UNTIL
%token WHILE DO
%token FOR TO DOWNTO
%token CASE
%token GOTO
%token INTEGER REAL CHAR STRING SYS_CON
%token LP RP
%token LB RB
%token DOT DOTDOT
%token COMMA
%token COLON
%token MUL DIV
%token SEMI
%token PLUS MINUS
%token OR MOD AND NOT
%token ID
%token GE GT
%token LE LT
%token EQUAL UNEQUAL
%token ASSIGN

%type<sNode> NAME
%type<sNode> PROGRAM
%type<sNode> CONST
%type<sNode> TYPE
%type<sNode> SYS_TYPE SYS_PROC SYS_FUNCT
%type<sNode> ARRAY
%type<sNode> OF
%type<sNode> RECORD
%type<sNode> BEGIN END
//%token<sNode> NULL
%type<sNode> FUNCTION
%type<sNode> PROCEDURE
%type<sNode> VAR
%type<sNode> READ
%type<sNode> IF THEN ELSE
%type<sNode> REPEAT UNTIL
%type<sNode> WHILE DO
%type<sNode> FOR TO DOWNTO
%type<sNode> CASE
%type<sNode> GOTO
%type<sNode> INTEGER REAL CHAR STRING SYS_CON
%type<sNode> LP RP
%type<sNode> LB RB
%type<sNode> DOT DOTDOT
%type<sNode> COMMA
%type<sNode> COLON
%type<sNode> MUL DIV
%type<sNode> SEMI
%type<sNode> PLUS MINUS
%type<sNode> OR MOD AND NOT
%type<sNode> ID
%type<sNode> GE GT
%type<sNode> LE LT
%type<sNode> EQUAL UNEQUAL
%type<sNode> ASSIGN


//nonterminal symbol
%token PROGRAM
%token PROGRAM_HEAD
%token ROUTINE
%token ROUTINE_HEAD
%token ROUTINE_BODY
%token SUB_ROUTINE
%token LABEL_PART
%token CONST_PART
%token TYPE_PART
%token VAR_PART
%token ROUTINE_PART
%token CONST_EXPR_LIST
%token CONST_VALUE
%token TYPE_DECL_LIST
%token TYPE_DEFINITION
%token TYPE_DECL
%token SIMPLE_TYPE_DECL ARRAY_TYPE_DECL RECORD_TYPE_DECL
%token NAME_LIST
%token FIELD_DECL_LIST FIELD_DECL
%token VAR_DECL_LIST VAR_DECL
%token FUNCTION_DECL
%token PROCEDURE_DECL
%token FUNCTION_HEAD
%token PARAMETERS
%token PROCEDURE_HEAD
%token PARA_DECL_LIST
%token VAR_PARA_LIST
%token COMPOUND_STMT
%token STMT_LIST STMT
%token NON_LABEL_STMT
%token ASSIGN_STMT PROC_STMT COMPOUND_STMT IF_STMT REPEAT_STMT WHILE_STMT
%token FOR_STMT CASE_STMT GOTO_STMT
%token EXPRESSION EXPRESSION_LIST
%token ELSE_CLAUSE
%token DIRECTION
%token CASE_EXPR_LIST
%token CASE_EXPR
%token TERM FACTOR
%token ARGS_LIST


%type<sNode> program
%type<sNode> program_head
%type<sNode> routine
%type<sNode> routine_head
%type<sNode> routine_body
%type<sNode> sub_routine
%type<sNode> label_part
%type<sNode> const_part
%type<sNode> type_part
%type<sNode> var_part
%type<sNode> routine_part
%type<sNode> const_expr_list
%type<sNode> const_value
%type<sNode> type_decl_list
%type<sNode> type_definition
%type<sNode> type_decl
%type<sNode> simple_type_decl array_type_decl record_type_decl
%type<sNode> name_list
%type<sNode> field_decl_list field_decl
%type<sNode> var_decl_list var_decl
%type<sNode> function_decl
%type<sNode> procedure_decl
%type<sNode> function_head
%type<sNode> parameters
%type<sNode> procedure_head
%type<sNode> para_decl_list
%type<sNode> var_para_list
%type<sNode> compound_stmt
%type<sNode> stmt_list stmt
%type<sNode> non_label_stmt
%type<sNode> assign_stmt proc_stmt compound_stmt if_stmt repeat_stmt while_stmt
%type<sNode> for_stmt case_stmt goto_stmt
%type<sNode> expression expression_list
%type<sNode> else_clause
%type<sNode> direction
%type<sNode> case_expr_list
%type<sNode> case_expr
%type<sNode> term factor
%type<sNode> args_list



%%

program:
program_head routine DOT {}

program_head:
PROGRAM ID SEMI {}

routine:
routine_head routine_body {}

sub_routine:
routine_head routine_body {}

routine_head:
label_part const_part type_part var_part routine_part {}

label_part:
NULL {}

const_part:
CONST const_expr_list {}
| NULL {}

const_expr_list:
const_expr_list NAME EQUAL const_value SEMI {}
| NAME EQUAL const_value SEMI {}

const_value:
INTEGER {}
| REAL {}
| CHAR {}
| STRING {}
| SYS_CON {}

type_part:
TYPE type_decl_list {}
| NULL {}

type_decl_list:
type_decl_list type_definition {}
| type_definition {}

type_definition:
NAME EQUAL type_decl SEMI {}

type_decl:
simple_type_decl {}
| array_type_decl {}
| record_type_decl {}

simple_type_decl:
SYS_TYPE {}
| NAME {}
| LP name_list RP {}
| const_value DOTDOT const_value {}
| MINUS const_value DOTDOT const_value {}
| MINUS const_value DOTDOT MINUS const_value {}
| NAME DOTDOT NAME

array_type_decl:
ARRAY LB simple_type_decl RB OF type_decl {}

record_type_decl:
RECORD field_decl_list END {}

field_decl_list:
field_decl_list field_decl {}
| field_decl{}

field_decl:
name_list COLON type_decl SEMI {}

name_list:
name_list COMMA ID {}
| ID {}

var_part:
VAR var_decl_list {}
| NULL {}

var_decl_list:
var_decl_list var_decl {}
| var_decl {}

var_decl:
name_list COLON type_decl SEMI {}

routine_part:
routine_part function_decl {}
| routine_part procedure_decl {}
| function_decl {}
| procedure_decl {}
| NULL {}

function_decl:
function_head SEMI sub_routine SEMI {}

function_head:
FUNCTION ID parameters COLON simple_type_decl {}

procedure_decl:
procedure_head SEMI sub_routine SEMI {}

procedure_head:
PROCEDURE ID parameters {}

parameters:
LP para_decl_list RP {}
| NULL {}

para_decl_list:
para_decl_list SEMI para_type_list {}
| para_type_list {}

para_type_list:
var_para_list COLON simple_type_decl {}
| val_para_list COLON simple_type_decl {}

var_para_list:
VAR name_list {}

val_para_list:
name_list {}

routine_body:
compound_stmt {}

compound_stmt:
BEGIN stmt_list END {}

stmt_list:
stmt_list stmt SEMI {}
| NULL {}

stmt:
INTEGER COLON non_label_stmt {}
| non_label_stmt {}

non_label_stmt:
assign_stmt {}
| proc_stmt {}
| compound_stmt {}
| if_stmt {}
| repeat_stmt {}
| while_stmt {}
| for_stmt {}
| case_stmt {}
| goto_stmt {}

assign_stmt:
ID ASSIGN expression {}
| ID LB expression RB ASSIGN expression {}
| ID DOT ID ASSIGN expression {}

proc_stmt:
ID {}
| ID LP args_list RP {}
| SYS_PROC {}
| SYS_PROC LP expression_list RP {}
| READ LP factor RP {}

if_stmt:
IF expression THEN stmt else_clause {}

else_clause:
ELSE stmt {}
| NULL {}

repeat_stmt:
REPEAT stmt_list UNTIL expression {}

while_stmt:
WHILE expression DO stmt {}

for_stmt:
FOR ID ASSIGN expression direction expression DO stmt {}

direction:
TO {}
| DOWNTO {}

case_stmt:
CASE expression OF case_expr_list END {}

case_expr_list:
case_expr_list case_expr {}
| case_expr {}

case_expr:
const_value COLON stmt SEMI {}
| ID COLON stmt SEMI {}

goto_stmt:
GOTO INTEGER {}

expression_list:
expression_list COMMA expression {}
| expression {}

expression:
expression GE expr {}
| expression GT expr {}
| expression LE expr {}
| expression LT expr {}
| expression EQUAL expr {}
| expression UNEQUAL expr {}
| expr {}

expr:
expr PLUS term {}
| expr MINUS term {}
| expr OR term {}
| term {}

term:
term MUL factor {}
| term DIV factor {}
| term MOD factor {}
| term AND factor {}
| factor {}

factor:
NAME {}
| NAME LP args_list RP {}
| SYS_FUNCT {}
| SYS_FUNCT LP args_list RP {}
| const_value {}
| LP expression RP {}
| NOT factor {}
| MINUS factor {}
| ID LB expression RB {}
| ID DOT ID {}

args_list:
args_list COMMA expression {}
| expression {}

%%


void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "line %d: error near '%s': ", yylineno, yytext);

    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}


int main(int argc, char* argv[])
{
	//initialize
	FILE *ifp = NULL, *ofp = NULL;

	//filename
	char infile[100] = "";
	char outfile[100] = "";

	//if no arguments on command line: newton-pascal
	if (argc < 2)
	{
		printf("newton-pascal: error: no input files\n");
		return 1;
	}
	else
	{
		//analyize remaining arguments
		for (int i = 1; i < argc; i++) {

			if (strcmp(argv[i], "-o") == 0) {

				//lack output file after "-o"
				if (i + 1 >= argc)
				{
					printf("newton-pascal: error: argument to '-o' is missing (expected 1 value)\n");
					return 1;
				}
				else
				{
					//move to next arg
					i++;

					//copy output file name
					strcpy(outfile, argv[i]);
				}

			}

			//argv[i]: input file
			else {

				//open input file
				strcpy(infile, argv[i]);

				ifp = fopen(infile, "r");

				if (ifp == NULL)
				{
					printf("newton-pascal: error: no such file or directory: '%s'\n", argv[i]); //no such file found
					return 1;
				}
				else
				{
					yyin = ifp; //redirect yyin to argv[i]
				}
			}

		}


		//no input file
		if (strcmp(infile, "") == 0)
		{
			printf("newton-pascal: error: no input files\n");
			return 1;
		}

		//no output file name: give a default name
		if (strcmp(outfile, "") == 0)
			strcpy(outfile, "default.S");

		//redirect yyout to argv[i]
		ofp = fopen(outfile, "w");

		if (ofp == NULL)
		{
			printf("newton-pascal: error: no such file or directory: '%s'\n", outfile); //no such file found
			return 1;
		}
		else
		{
			yyout = ofp; //redirect yyout to argv[i]
		}

	}

	//start parser
	yyparse();

	//close input and output files
	fclose(ifp);
	fclose(ofp);

	return 0;
}
