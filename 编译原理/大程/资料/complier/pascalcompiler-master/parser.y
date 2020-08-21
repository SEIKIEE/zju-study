%{

#include <cstdio>
#include <iostream>
#include "declare.h"
static int global_direction;
static int label;
//#define YYDEBUG 1
using namespace lwd;

%}

%token INTVALUE REALVALUE CHARVALUE STRINGVALUE
%token INTEGER REAL CHAR STRING IDENTIFIER
%token PLUS MINUS MUL DIV LT GT LE GE EQUAL UNEQUAL ASSIGN
%token LP RP LB RB DOT COMMA SEMI COLON DOTDOT
%token AND ARRAY BBEGIN CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO IF
%token IN LABEL MOD NIL NOT OF OR OTHERWISE PROCEDURE PROGRAM RECORD
%token READ REPEAT THEN TO TYPE UNTIL VAR WHILE
%token TESTFUNC TESTPROC TESTCON WRITE WRITELN

%union {
	identifier *p0;
	program *p1;
	program_head *p2;
	routine *p3;
	routine_head *p4;
	routine_body *p5;
	label_part *p6;
	const_part *p7;
	type_part *p8;
	var_part *p9;
	routine_part *p10;
	const_expr *p11;
	const_expr_list *p12;
	const_value *p13;
	type_definition *p14;
	type_decl_list *p15;
	type_decl *p16;
	simple_type_decl *p17;
	array_type_decl *p18;
	record_type_decl *p19;
	sys_type *p20;
	name_list *p21;
	range *p22;
	idrange *p23;
	field_decl *p24;
	field_decl_list *p25;
	var_decl *p26;
	var_decl_list *p27;
	function_decl *p28;
	function_decl_list *p29;
	function_head *p30;
	procedure_decl *p31;
	procedure_decl_list *p32;
	procedure_head *p33;
	sub_routine *p34;
	parameters *p35;
	para_type_list *p36;
	para_decl_list *p37;
	var_para_list *p38;
	val_para_list *p39;
	compound_stmt *p40;
	stmt *p41;
	stmt_list *p42;
	non_label_stmt *p43;
	assign_stmt *p44;
	proc_stmt *p45;
	if_stmt *p46;
	repeat_stmt *p47;
	while_stmt *p48;
	for_stmt *p49;
	case_stmt *p50;
	goto_stmt *p51;
	sys_proc *p52;
	expression *p53;
	args_list *p54;
	expression_list *p55;
	else_clause *p56;
	case_expr *p57;
	case_expr_list *p58;
	expr *p59;
	term *p60;
	factor *p61;
	sys_funct *p62;	
	sys_con *p63;
	void *p64;
}

%type <p0> ID
%type <p1> program command
%type <p2> program_head
%type <p3> routine
%type <p4> routine_head
%type <p5> routine_body
%type <p6> label_part
%type <p7> const_part
%type <p8> type_part
%type <p9> var_part
%type <p10> routine_part
%type <p11> const_expr
%type <p12> const_expr_list
%type <p13> const_value
%type <p14> type_definition
%type <p15> type_decl_list
%type <p16> type_decl
%type <p17> simple_type_decl
%type <p18> array_type_decl
%type <p19> record_type_decl
%type <p20> sys_type
%type <p21> name_list
%type <p24> field_decl
%type <p25> field_decl_list
%type <p26> var_decl
%type <p27> var_decl_list
%type <p28> function_decl
%type <p30> function_head
%type <p31> procedure_decl
%type <p33> procedure_head
%type <p34> sub_routine
%type <p35> parameters
%type <p36> para_type_list
%type <p37> para_decl_list
%type <p38> var_para_list
%type <p39> val_para_list
%type <p40> compound_stmt
%type <p41> stmt
%type <p42> stmt_list
%type <p43> non_label_stmt
%type <p44> assign_stmt
%type <p45> proc_stmt
%type <p46> if_stmt
%type <p47> repeat_stmt
%type <p48> while_stmt
%type <p49> for_stmt
%type <p50> case_stmt
%type <p51> goto_stmt
%type <p52> sys_proc
%type <p53> expression
%type <p54> args_list
%type <p55> expression_list
%type <p56> else_clause
%type <p57> case_expr
%type <p58> case_expr_list
%type <p59> expr
%type <p60> term
%type <p61> factor
%type <p62> sys_funct
%type <p63> sys_con

%type <p64> INTVALUE REALVALUE CHARVALUE STRINGVALUE 
%type <p64> INTEGER REAL CHAR STRING IDENTIFIER
%type <p64> PLUS MINUS MUL DIV LT GT LE GE EQUAL UNEQUAL ASSIGN
%type <p64> LP RP LB RB DOT COMMA SEMI COLON DOTDOT
%type <p64> AND ARRAY BBEGIN CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO IF
%type <p64> IN LABEL MOD NIL NOT OF OR OTHERWISE PROCEDURE PROGRAM RECORD
%type <p64> REPEAT THEN TO TYPE UNTIL VAR WHILE
%type <p64> TESTPROC TESTFUNC TESTCON WRITE WRITELN
%type <p64> semi rp rb end colon then

%start command

%%

semi : SEMI
	| error { fprintf(stderr, " : Possibly missing ';'\n"); }
	;
	
rp : RP
	| error { fprintf(stderr, " : Possibly missing ')'\n"); }
	;

rb : RB
	| error { fprintf(stderr, " : Possibly missing ']'\n"); }
	;

end : END
	| error { fprintf(stderr, " : Possibly missing 'end'\n"); }
	;

colon : COLON
	| error { fprintf(stderr, " : Possibly missing ':'\n"); }
	;

then : THEN
	| error { fprintf(stderr, " : Possibly missing 'then'\n"); }
	;
	
command : program { savedRoot = $1; }
		;
		
program : program_head routine DOT { $$ = new program($1,$2); }
		;

program_head : PROGRAM ID semi { $$ = new program_head($2); }
			;
			
ID : IDENTIFIER { $$ = new identifier(yytext, lineno); }
	;
	
routine : routine_head routine_body { $$ = new routine($1,$2); }
		;

sub_routine : routine_head  routine_body { $$ = new sub_routine($1,$2); }
			;

routine_head : label_part  const_part  type_part  var_part  routine_part { $$ = new routine_head($1,$2,$3,$4,$5); }
			;

label_part : { $$ = new label_part(); }
			;

const_part : CONST  const_expr_list { $$ = new const_part($2); } 
			| { $$ = new const_part(NULL); }
			;
			
const_expr_list : const_expr_list  const_expr { 
					const_expr_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
					$$ = $1;
				}
				| const_expr { $$ = (const_expr_list *)$1; }
				;
				
const_expr : ID EQUAL  const_value  semi { $$ = new const_expr($1,$3,NULL); }
			;
			
const_value : INTVALUE { $$ = new const_value(1,yytext); }	
			| REALVALUE { $$ = new const_value(2,yytext); }
			| CHARVALUE { $$ = new const_value(3,yytext); }
			| STRINGVALUE { $$ = new const_value(4,yytext); }
			| sys_con { $$ = new const_value(5,yytext); }
			;
sys_con : TESTCON { $$ = new sys_con(); }
		;
		
type_part : TYPE type_decl_list { $$ = new type_part($2); }
			| { $$ = new type_part(NULL); }
			;
			
type_decl_list : type_decl_list type_definition {
					type_decl_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
					$$ = $1;
				}
				| type_definition { $$ = (type_decl_list *)$1; }
				;
				
type_definition : ID EQUAL type_decl semi { $$ = new type_definition($1,$3,NULL); }
				;

type_decl : simple_type_decl { $$ = new type_decl($1); }
			| array_type_decl { $$ = new type_decl($1); }
			| record_type_decl { $$ = new type_decl($1); }
			;
			
simple_type_decl : sys_type { $$ = new simple_type_decl($1); }
				| ID { $$ = new simple_type_decl($1); }
				| LP name_list rp { $$ = new simple_type_decl($2); }
                | const_value DOTDOT const_value { $$ = new simple_type_decl(new range($1,$3)); }
                | MINUS const_value DOTDOT const_value { 
					range *temp = new range($2,$4); 
					temp->negate(1);
					$$ = new simple_type_decl(temp);
				}
                | MINUS const_value DOTDOT MINUS const_value {
					range *temp = new range($2,$5);
					temp->negate();
					$$ = new simple_type_decl(temp);
				}
                | ID DOTDOT ID { $$ = new simple_type_decl(new idrange($1,$3)); }
				;
			
sys_type : INTEGER { $$ = new sys_type(1); }
		| REAL { $$ = new sys_type(2); }
		| CHAR { $$ = new sys_type(3); }
		| STRING { $$ = new sys_type(4); }
		;
		
array_type_decl : ARRAY LB simple_type_decl rb OF type_decl { $$ = new array_type_decl($3,$6); }
				;
				
record_type_decl : RECORD  field_decl_list  end { $$ = new record_type_decl($2); }
				;
				
field_decl_list : field_decl_list field_decl {
					field_decl_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
					$$ = $1;
				}
				| field_decl { $$ = (field_decl_list *)$1; }
				;
				
field_decl : name_list colon type_decl semi { $$ = new field_decl($1,$3,NULL); }
			;
			
name_list : name_list COMMA ID { $$ = new name_list($1,$3); }
		| ID { $$ = new name_list(NULL,$1); }
		;
		
var_part : VAR var_decl_list { $$ = new var_part($2); }
		| { $$ = new var_part(NULL); }
		;
		
var_decl_list : var_decl_list var_decl {
					var_decl_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
					$$ = $1;
				}
			| var_decl { $$ = (var_decl_list *)$1; }
			;
			
var_decl : name_list colon type_decl semi { $$ = new var_decl($1,$3,NULL); }
		;
		
routine_part : routine_part function_decl {
				function_decl *node = $1->child1;
				if(node==NULL)
					$1->child1 = $2;
				else {
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
				}
				$$ = $1;
			}
			| routine_part procedure_decl {
				procedure_decl *node = $1->child2;
				if(node==NULL)
					$1->child2 = $2;
				else {
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
				}
				$$ = $1;
			}
			| function_decl { $$ = new routine_part($1,NULL); }
			| procedure_decl { $$ = new routine_part(NULL,$1); }
			| { $$ = new routine_part(NULL,NULL); }
			;
			
function_decl : function_head semi sub_routine semi { $$ = new function_decl($1,$3,NULL); }
				;
				
function_head : FUNCTION ID parameters colon simple_type_decl { $$ = new function_head($2,$3,$5); }
				;
				
procedure_decl : procedure_head semi sub_routine semi { $$ = new procedure_decl($1,$3,NULL); }
				;
				
procedure_head : PROCEDURE ID parameters { $$ = new procedure_head($2,$3); }
				;
				
parameters : LP para_decl_list rp { $$ = new parameters($2); }
			| { $$ = NULL; }
			;
			
para_decl_list : para_decl_list semi para_type_list { 
					para_decl_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $3;
					$$ = $1;
				}
				| para_type_list { $$ = (para_decl_list *)$1; }
				;
				
para_type_list : var_para_list colon simple_type_decl { $$ = new para_type_list($1,$3,NULL); }
				| val_para_list colon simple_type_decl { $$ = new para_type_list($1,$3,$3,NULL); }
				;
				
var_para_list : VAR name_list { $$ = (var_para_list *)$2; }
				;
				
val_para_list : name_list { $$ = (val_para_list *) $1; }
				;
				
routine_body : compound_stmt { $$ = new routine_body($1); }
			;

compound_stmt : BBEGIN stmt_list end { $$ = new compound_stmt($2,lineno); }
			;
			
stmt_list : stmt_list stmt semi {
			stmt_list *node = $1;
			if(node==NULL)
				$1 = (stmt_list *)$2;
			else {
				while(node->next!=NULL)
					node = node->next;
				node->next = $2;
			}
			$$ = $1;
		}
		| { $$ = NULL; }
		;
		
stmt : INTVALUE { 
		sscanf(yytext, "%d", &label);
	}
	colon non_label_stmt {
		$$ = new stmt(label, $4, NULL);
	}
	| non_label_stmt { $$ = new stmt($1, NULL); }
	;
	
non_label_stmt : assign_stmt { $$ = new non_label_stmt($1); }
				| proc_stmt { $$ = new non_label_stmt($1); }
				| compound_stmt { $$ = new non_label_stmt($1); }
				| if_stmt { $$ = new non_label_stmt($1); }
				| repeat_stmt { $$ = new non_label_stmt($1); }
				| while_stmt { $$ = new non_label_stmt($1); }
				| for_stmt { $$ = new non_label_stmt($1); }
				| case_stmt { $$ = new non_label_stmt($1); }
				| goto_stmt { $$ = new non_label_stmt($1); }
				;

assign_stmt : ID ASSIGN  expression { $$ = new assign_stmt($1,$3); }
           | ID LB expression rb ASSIGN expression { $$ = new assign_stmt($1,$3,$6); }
           | ID DOT ID ASSIGN expression  { $$ = new assign_stmt($1,$3,$5); }
			;
			
proc_stmt : ID { $$ = new proc_stmt($1, lineno); }
          | ID LP args_list rp { $$ = new proc_stmt($1,$3, lineno); }
          | sys_proc { $$ = new proc_stmt($1, lineno); }
          | sys_proc LP expression_list rp { $$ = new proc_stmt($1,$3, lineno); }
          | READ LP factor rp{ $$ = new proc_stmt($3, lineno); }
		;
		
sys_proc : WRITE { $$ = new sys_proc(wwrite); }
	| WRITELN { $$ = new sys_proc(wwriteln); }
		;
		
args_list : args_list COMMA expression {
			args_list *node = $1;
			while(node->next!=NULL)
				node = node->next;
			node->next = $3;
			$$ = $1;
		}
		| expression { $$ = (args_list *)$1; }
		;
		
if_stmt : IF expression then stmt else_clause { $$ = new if_stmt($2,$4,$5); }
		;
		
else_clause : ELSE stmt { $$ = new else_clause($2); }
			| { $$ = new else_clause(); }
			;
			
repeat_stmt : REPEAT stmt_list UNTIL expression { $$ = new repeat_stmt($2,$4); }
			;
			
while_stmt : WHILE expression DO stmt { $$ = new while_stmt($2,$4); }
			;
			
for_stmt : FOR ID ASSIGN expression direction expression DO stmt { $$ = new for_stmt($2,$4,global_direction,$6,$8); }
			;
			
direction : TO { global_direction = 1; }
		| DOWNTO { global_direction = 2; }
		;
		
case_stmt : CASE expression OF case_expr_list end { $$ = new case_stmt($2,$4); }
		;
		
case_expr_list : case_expr_list case_expr {
					case_expr_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $2;
					$$ = $1;
				}
				| case_expr { $$ = (case_expr_list *)$1; }
				;
				
case_expr : const_value colon stmt semi { $$ = new case_expr($1,$3,NULL); }
          | ID colon stmt semi { $$ = new case_expr($1,$3,NULL); }
		  ;
		  
goto_stmt : GOTO INTVALUE {
				int temp;
				sscanf(yytext,"%d",&temp);
				$$ = new goto_stmt(temp);
			}
			;
			
expression_list : expression_list COMMA expression { 
					expression_list *node = $1;
					while(node->next!=NULL)
						node = node->next;
					node->next = $3;
					$$ = $1;
				}
				| expression { $$ = (expression_list *)$1; }
				;
				
expression : expression GE expr { $$ = new expression($1,1,$3,NULL, lineno); }
			| expression GT expr { $$ = new expression($1,2,$3,NULL, lineno); }
			| expression LE expr { $$ = new expression($1,3,$3,NULL, lineno); }
			| expression LT expr { $$ = new expression($1,4,$3,NULL, lineno); }
			| expression EQUAL expr { $$ = new expression($1,5,$3,NULL, lineno); }
			| expression UNEQUAL expr { $$ = new expression($1,6,$3,NULL, lineno); }
			| expr { $$ = new expression(NULL,1,$1,NULL, lineno); }
			;
			
expr : expr PLUS term { $$ = new expr($1,1,$3, lineno); }
	| expr MINUS term { $$ = new expr($1,2,$3, lineno); }
	| expr OR term { $$ = new expr($1,3,$3, lineno); }
	| term { $$ = new expr(NULL,1,$1, lineno); }
	;
	
term : term MUL factor { $$ = new term($1,1,$3, lineno); }
	| term DIV factor { $$ = new term($1,2,$3, lineno); }
	| term MOD factor { $$ = new term($1,3,$3, lineno); }
	| term AND factor { $$ = new term($1,4,$3, lineno); }
	| factor { $$ = new term(NULL,1,$1, lineno); }
	;
	
factor : ID { $$ = new factor($1); }
		| ID LP args_list rp { $$ = new factor($1,$3); }
		| sys_funct { $$ = new factor($1); }
		| sys_funct LP args_list rp { $$ = new factor($1,$3); }
		| const_value { $$ = new factor($1); }
		| LP expression rp { $$ = new factor($2); }
		| NOT factor { $$ = new factor($2); }
		| MINUS factor { $$ = new factor($2,$2); }
		| ID LB expression rb { $$ = new factor($1,$3,$3); }
		| ID DOT ID { $$ = new factor($1,$3); }
		;
		
sys_funct : TESTFUNC { $$ = new sys_funct(); }
		;
		
%%

int yyerror(const std::string &msg) { 
	fprintf(stderr, "%s occurred at line %d", msg.c_str(), lineno); 
	error = true;
	return 0;
}
