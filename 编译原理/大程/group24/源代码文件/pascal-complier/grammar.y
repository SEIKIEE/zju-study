
%{
#define YYPARSER

#include "global.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include <stdarg.h>

#define YYSTYPE SyntaxTree

static SyntaxTree savedTree;    /* stores syntax tree for later return */
extern int yylineno;
extern int errFlag;
static int yylex(void)
{
    return getToken();
}
int yyerror(char const *str);
%}

%token PROGRAM FUNCTION PROCEDURE CONST TYPE VAR
%token IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%token EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD READ WRITE WRITELN
%token LB RB SEMI DOT DOTDOT LP RP COMMA COLON
%token INTEGER_TYPE BOOLEAN_TYPE CHAR_TYPE REAL_TYPE
%token TRUE FALSE MAXINT
%token ARRAY OF RECORD TOKEN_BEGIN END GOTO
%token TOKEN_ID TOKEN_INTEGER REAL CHAR STRING
%token ABS CHR ODD ORD PRED SQR SQRT SUCC
%token error ERROR

%%

program             :   program_head routine DOT
                        {   
                            $$ = newDeclNode(ProgramDecl);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $2->child[0];
                            $$->child[1] = $2->child[1];
                            savedTree = $$;
                            freeNode($1);
                            free($2);
                        }
                    ;
program_head        :   error SEMI
                        {
                            yyerror("error");
                        }
                    ;
program_head        :   PROGRAM ID SEMI
                        {
                            $$ = newDeclNode(ProgramheadDecl);
                            $$->attr.name = copyString($2->attr.name);
                            freeNode($2);
                        }
                    ;
routine             :   error SEMI
                        {
                            yyerror("error");
                        }
                    ;
routine             :   routine_head routine_body
                        {
                            $$ = newDeclNode(RoutineDecl);
                            $$->child[0] = $1;
                            $$->child[1] = $2;
                        }
                    ;
sub_routine         :   error SEMI
                        {
                            yyerror("error");
                        }
                    ;
sub_routine         :   routine_head routine_body
                        {
                             $$ = newDeclNode(RoutineDecl);
                             $$->child[0] = $1;
                             $$->child[1] = $2;
                        }
                    ;

routine_head        :   error SEMI
                        {
                            yyerror("error");
                        }
routine_head        :   const_part type_part var_part routine_part
                        {
                            $$ = newDeclNode(RoutineheadDecl);
                            $$ ->child[0] = $1;
                            $$ ->child[1] = $2;
                            $$ ->child[2] = $3;
                            $$ ->child[3] = $4;
                        }
                    ;
const_part          :   CONST const_expr_list
                        {$$ = $2;}
                    |
                        {$$ = NULL;}
                    ;
const_expr_list     :   const_expr_list const_expr
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   const_expr
                        {
                            $$ = $1;
                        }
                    ;
const_expr          :   ID EQUAL const_value SEMI
                        {
                            $$ = newDeclNode(ConstDecl);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    ;
const_value         :   INTEGER
                        {
                            $$ = $1;
                        }
                    |   REAL
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = RealExpType;
                            $$->attr.realValue = atof(tokenString);
                        }
                    |   CHAR
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = CharExpType;
                            $$->attr.charValue = tokenString[1];
                        }
                    |   STRING
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = StringExpType;
                            $$->attr.stringValue = (char*)malloc(strlen(tokenString) - 1);
                            memmove($$->attr.stringValue, tokenString + 1, strlen(tokenString) - 2);
                            $$->attr.stringValue[strlen(tokenString) - 2] = '\0';
                        }
                    |   TRUE
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = BoolExpType;
                            $$->attr.intValue = 1;
                        }
                    |   FALSE
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = BoolExpType;
                            $$->attr.intValue = 0;
                        }
                    |   MAXINT
                        {
                            $$ = newExpNode(ConstExp);
                            $$->type = IntExpType;
                            $$->attr.intValue = 2147483647;
                        }
                    ;
type_part           :   TYPE type_decl_list
                        {   
                            $$ = $2;
                        }
                    |   {$$ = NULL;}
                    ;
type_decl_list      :   type_decl_list  type_definition
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   type_definition
                        {
                            $$ = $1;
                        }
                    ;
type_definition     :   ID EQUAL type_decl SEMI
                        {   
                            $$ = newDeclNode(TypeDecl);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    ;
type_decl           :   simple_type_decl    {$$ = $1;}
                    |   array_type_decl     {$$ = $1;}
                    |   record_type_decl    {$$ = $1;}
                    ;
simple_type_decl    :   ID
                        {
                            $$ = newTypeNode(SimpleIdType);
                            $$->attr.name = copyString($1->attr.name);
                            $$->type = UserExpType;
                            freeNode($1);
                        }
                    |   LP name_list RP
                        {   
                            $$ = newTypeNode(SimpleEnumType);
                            $$->child[0] = $2;
							$$->type = EnumExpType;
                        }
                    |   const_value DOTDOT const_value
                        {   
                            $$ = newTypeNode(simpleLimitType);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
							$$->type = LimitExpType;
                        }
                    |   MINUS const_value DOTDOT const_value
                        {
                            $$ = newTypeNode(simpleLimitType);
                            $$->child[0] = $2;
                            $$->child[0]->attr.intValue *= -1;
                            $$->child[1] = $4;
							$$->type = LimitExpType;
                        }
                    |   MINUS const_value DOTDOT MINUS const_value
                        {   
                            $$ = newTypeNode(simpleLimitType);
                            $$->child[0] = $2;
                            $$->child[0]->attr.intValue *= -1;
                            $$->child[1] = $5;
                            $$->child[1]->attr.intValue *= -1;
							$$->type = LimitExpType;
                        }
                    |   ID DOTDOT ID
                        {
                            $$ = newTypeNode(simpleLimitType);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
							$$->type = LimitExpType;
                        }
                    |   INTEGER_TYPE
                        {   
                            $$ = newTypeNode(SimpleSysType);
                            $$->type = IntExpType;
                        }
                    |   BOOLEAN_TYPE
                        {   
                            $$ = newTypeNode(SimpleSysType);
                            $$->type = BoolExpType;
                        }
                    |   REAL_TYPE
                        {   
                            $$ = newTypeNode(SimpleSysType);
                            $$->type = RealExpType;
                        }
                    |   CHAR_TYPE
                        {   
                            $$ = newTypeNode(SimpleSysType);
                            $$->type = CharExpType;
                        }
                    ;
array_type_decl     :   ARRAY LB simple_type_decl RB OF type_decl
                        {
                            $$ = newTypeNode(ArrayType);
                            $$->child[0] = $3;
                            $$->child[1] = $6;
                            $$->type = ArrayExpType;
                        }
                    ;
record_type_decl    :   RECORD field_decl_list END
                        {
                            $$ = $2;
                        }
                    ;
field_decl_list     :   field_decl_list field_decl
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else {
                                $$=$2;
                            }
                        }
                    |   field_decl 
                        {$$ = $1;}
                    ;
field_decl          :   name_list COLON type_decl SEMI
                        {
                            $$ = newTypeNode(RecordType);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
name_list           :   name_list COMMA ID
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $3;
                                $$ = $1;
                            }
                            else
                                $$ = $1;
                        }
                    |   ID 
                        {$$ = $1;}
                    ;
var_part            :   VAR var_decl_list
                        {$$ = $2;}
                    |
                        {$$ = NULL;}
                    ;
var_decl_list       :   var_decl_list var_decl
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$=$2;
                        }
                    |   var_decl    
                        {$$ = $1;}
                    ;
var_decl            :   name_list COLON type_decl SEMI
                        {   
                            $$ = newDeclNode(VarDecl);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    ;

routine_part        :   error SEMI
                        {
                            yyerror("error\n");
                        }
                    ;
routine_part        :
                        {   
                            $$ = NULL;
                        }
                    |   routine_part function_decl
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   routine_part procedure_decl
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   function_decl   {$$ = $1;}
                    |   procedure_decl  {$$ = $1;}
                    ;
function_decl       :   error SEMI
                        {
                            yyerror("error\n");
                        }
                    ;
function_decl       :   function_head SEMI sub_routine SEMI
                        {
                            $$ = newDeclNode(FunctionDecl);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $1->child[0];    //参数列表
                            $$->child[1] = $1->child[1];    //返回类型
                            $$->child[2] = $3->child[0];    //变量定义
                            $$->child[3] = $3->child[1];    //子过程
                            free($1);
                        }
                    ;
function_head       :   FUNCTION ID parameters COLON simple_type_decl
                        {
                            $$ = newDeclNode(FunctionheadDecl);
                            $$->attr.name = copyString($2->attr.name);
                            $$->child[0] = $3;  //参数列表
                            $$->child[1] = $5;  //返回类型
                            freeNode($2);
                        }
                    ;
procedure_decl      :   procedure_head SEMI sub_routine SEMI
                        {
                            $$ = newDeclNode(ProcedureDecl);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $1->child[0];    //参数类型
                            $$->child[1] = NULL;            //返回类型
                            $$->child[2] = $3->child[0];    //变量定义
                            $$->child[3] = $3->child[1];    //子过程
                            free($1);
                        }
                    ;
procedure_head      :   PROCEDURE ID parameters
                        {   
                            $$ = newDeclNode(ProcedureheadDecl);
                            $$->attr.name = copyString($2->attr.name);
                            $$->child[0] = $3;
                            freeNode($2);
                        }
                    ;
parameters          :
                        {$$ = NULL;}
                    |   LP para_decl_list RP
                        {$$ = $2;}
                    ;
para_decl_list      :   para_decl_list  SEMI  para_type_list
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $3;
                                $$ = $1;
                            }
                            else
                                $$ = $3;
                        }
                    |   para_type_list
                        {$$ = $1;}
                    ;
para_type_list      :   var_name_list COLON simple_type_decl
                        {
                            $$ = newDeclNode(VarParaDecl);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    ;
var_name_list       :   VAR name_list
                        {
                            $$ = $2;
                        }
                    |   name_list
                        {
                            $$ = $1;
                        }
                    ;

INTEGER           :   TOKEN_INTEGER
                      {
                          $$ = newExpNode(ConstExp);
                          $$->type = IntExpType;
                          $$->attr.intValue = atoi(tokenString);
                      }
                  ;
ID                :   TOKEN_ID
                        {   
                            $$ = newExpNode(IdExp);
                            $$->attr.name=copyString(tokenString);
                        }
                    ;
routine_body        :   compound_stmt   
                        {$$ = $1;}
                    ;
compound_stmt       :   TOKEN_BEGIN stmt_list END 
                        {$$ = $2;}
                    ;
stmt_list:          error SEMI
                    {
                        yyerror("error\n");
                    }
                    |
                    stmt_list error SEMI
                    {
                        yyerror("error\n");
                    }
stmt_list           :
                        {$$ = NULL;}
                    |   stmt_list stmt SEMI
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    ;
stmt                :   INTEGER COLON non_label_stmt
                        {
                            $$ = newStmtNode(LabelStmt);
                            $$->attr.intValue = $1->attr.intValue;
                            $$->child[0] = $3;
                        }
                    |   non_label_stmt
                        {$$ = $1;}
                    ;
non_label_stmt       :  assign_stmt 
                        {$$ = $1;}
                    |   proc_stmt   
                        {$$ = $1;}
                    |   compound_stmt   
                        {$$ = $1;}
                    |   if_stmt     
                        {$$ = $1;}
                    |   repeat_stmt 
                        {$$ = $1;}
                    |   while_stmt  
                        {$$ = $1;}
                    |   for_stmt    
                        {$$ = $1;}
                    |   case_stmt
                        {$$ = $1;}
                    |   goto_stmt
                        {$$ = $1;}
                    ;
assign_stmt         :   ID ASSIGN expression
                        {   
                            $$ = newStmtNode(AssignStmt);
			                $$->child[0] = $1;
			                $$->child[1] = $3;
                        }
		            |   ID LB expression RB ASSIGN expression
			            {  
                            $$ = newStmtNode(AssignStmt);
			                $1->type = ArrayExpType;
			                $$->child[0] = $1;
			                $$->child[1] = $3;
                            $$->child[2] = $6;
			            }
                    |   ID DOT ID ASSIGN expression
                        {   
                            $$ = newStmtNode(AssignStmt);
                            $1->type = RecordExpType;
                            $$->child[0] = $1;
                            $1->child[0] = $3;
                            $$->child[1] = $5;
                        }
                    ;
proc_stmt           :   ID
						{
							$$ = newStmtNode(FuncIdStmt);
                            $$->attr.name = copyString($1->attr.name);
                            freeNode($1);
                        }
                    |   ID LP args_list RP
                        {   
                            $$ = newStmtNode(FuncIdStmt);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $3;
                            freeNode($1);
                        }
                    |   READ LP factor RP
                        {
                            $$ = newStmtNode(ProcSysStmt);
                            $$->attr.op = ReadOp;
                            $$->child[0] = $3;
                        }
                    |   WRITE
                        {   
                            $$ = newStmtNode(ProcSysStmt);
                            $$->attr.op = WriteOp;
                        }
                    |   WRITE LP expression_list RP
                        {   
                            $$ = newStmtNode(ProcSysStmt);
                            $$->attr.op = WriteOp;
                            $$->child[0] = $3;
                        }
                    |   WRITELN
                        {   
                            $$ = newStmtNode(ProcSysStmt);
                            $$->attr.op = WritelnOp;
                        }
                    |   WRITELN LP expression_list RP
                        {   
                            $$ = newStmtNode(ProcSysStmt);
                            $$->attr.op = WritelnOp;
                            $$->child[0] = $3;
                        }
                    ;
if_stmt             :   IF expression THEN stmt else_clause
                        {   
                            $$ = newStmtNode(IfStmt);
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                            $$->child[2] = $5;
                        }
                    ;
else_clause         :   {$$ = NULL;}
                    |   ELSE stmt    
                        {$$ = $2;}
                    ;
repeat_stmt         :   REPEAT stmt_list UNTIL expression
                        {
                            $$ = newStmtNode(RepeatStmt);
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                        }
                    ;
while_stmt          :   WHILE expression DO stmt
                        {   
                            $$ = newStmtNode(WhileStmt);
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                        }
                    ;
for_stmt            :   FOR ID ASSIGN expression TO expression DO stmt
                        {
                            $$ = newStmtNode(ForStmt);
                            $$->attr.op = ToOp;
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                            $$->child[2] = $6;
                            $$->child[3] = $8;
                        }
                    |   FOR ID ASSIGN expression DOWNTO expression DO stmt
                        {
                            $$ = newStmtNode(ForStmt);
                            $$->attr.op = DowntoOp;
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                            $$->child[2] = $6;
                            $$->child[3] = $8;
                        }
                    ;
case_stmt           :   CASE expression OF case_expr_list END
                        {   
                            $$ = newStmtNode(CaseStmt);
                            $$->child[0] = $2;
                            $$->child[1] = $4;
                        }
                    ;
case_expr_list      :   case_expr_list  case_expr
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   case_expr 
                        {$$ = $1;}
                    ;
case_expr           :   const_value COLON stmt SEMI
                        {
                            $$ = newExpNode(CaseExp);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   ID  COLON stmt SEMI
                        {
                            $$ = newExpNode(CaseExp);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    ;
goto_stmt           :   GOTO  INTEGER
                        {   
                            $$ = newStmtNode(GotoStmt);
                            $$->attr.intValue = $2->attr.intValue;
                        }
                    ;
expression_list     :   expression_list COMMA expression
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $3;
                                $$ = $1;
                            }
                            else
                                $$ = $3;
                        }
                    |   expression
                        {$$ = $1;}
                    ;
expression          :   expression GE expr
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = GeOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expression GT expr 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = GtOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expression LE expr 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = LeOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expression LT expr 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = LtOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expression EQUAL expr 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = EqualOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expression UNEQUAL expr 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = UnequalOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expr 
                        {
                            $$ = $1;
                        }
                    ;
expr                :   expr PLUS term  
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = PlusOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expr MINUS term  
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = MinusOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   expr OR term  
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = OrOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   term 
                        {
                            $$ = $1;
                        } 
                    ;
term                :   term MUL factor 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = MulOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   term DIV factor 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = DivOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   term MOD factor 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = ModOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    |   term AND factor 
                        {
                            $$ = newExpNode(OpExp);
                            $$->attr.op = AndOp;
                            $$->child[0] = $1;
                            $$->child[1] = $3;;
                        }
                    |   factor 
                        {$$ = $1;}
                    ;
factor              :   ID
                        {
                            $$ = $1;
                        }
                    |   ABS
                        {$$ = $1;}
                    |   CHR
                        {$$ = $1;}
                    |   ODD
                        {$$ = $1;}
                    |   ORD
                        {$$ = $1;}
                    |   PRED
                        {$$ = $1;}
                    |   SQR
                        {$$ = $1;}
                    |   SQRT
                        {$$ = $1;}
                    |   SUCC
                        {$$ = $1;}
                    |   ID LP args_list RP
                        {   
                            $$ = newStmtNode(FuncIdStmt);
                            $$->attr.name = copyString($1->attr.name);
                            $$->child[0] = $3;
                            freeNode($1);
                        }
                    |   const_value 
                        {$$ = $1;}
                    |   LP expression RP    
                        {$$ = $2;}
                    |   NOT factor
                        {   
                            $$ = newExpNode(OpExp);
                            $$->attr.op = NotOp;
                            $$->child[0] = $2;
                        }
                    |   MINUS factor
                        {   
                            $$ = newExpNode(OpExp);
                            $$->attr.op = MinusOp;
                            $$->child[0] = $2;
                        }
                    |   ID LB expression RB
                        {   
                            $$ = $1;
                            $$->child[0] = $3;
                            $$->type = ArrayExpType;
                        }
                    |   ID DOT ID
                        {   
                            $$ = $1;
                            $$->child[0] = $3;
                            $$->type = RecordExpType;
                        }
                    |   ABS LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = AbsOp;
                            $$->child[0] = $3;
                        }
                    |   CHR LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = ChrOp;
                            $$->child[0] = $3;
                        }
                    |   ODD LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = OddOp;
                            $$->child[0] = $3;
                        }
                    |   ORD LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = OrdOp;
                            $$->child[0] = $3;
                        }
                    |   PRED LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = PredOp;
                            $$->child[0] = $3;
                        }
                    |   SQR LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = SqrOp;
                            $$->child[0] = $3;
                        }
                    |   SQRT LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = SqrtOp;
                            $$->child[0] = $3;
                        }
                    |   SUCC LP args_list RP
                        {   
                            $$ = newStmtNode(FuncSysStmt);
                            $$->attr.op = SuccOp;
                            $$->child[0] = $3;
                        }
                    ;
args_list           :   args_list COMMA expression
                        {   
                            YYSTYPE t = $1;
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $3;
                                $$ = $1;
                            }
                            else
                                $$ = $3;
                        }
                    |   expression  
                        {$$ = $1;}
                    ;
%%
int yyerror(const char *msg) 
{
    extern char *yytext;
    if(msg = NULL)
    {
        msg = "grammar";
    }
    fprintf(stderr, "[Syntax error]: Error in line %d error near '%s'\n", yylineno, yytext);
    errFlag = 1;
    return 0;
}

SyntaxTree parse(void)
{
    yyparse();
    return savedTree;
}
