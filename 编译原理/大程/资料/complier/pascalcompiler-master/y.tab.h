/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTVALUE = 258,
     REALVALUE = 259,
     CHARVALUE = 260,
     STRINGVALUE = 261,
     INTEGER = 262,
     REAL = 263,
     CHAR = 264,
     STRING = 265,
     IDENTIFIER = 266,
     PLUS = 267,
     MINUS = 268,
     MUL = 269,
     DIV = 270,
     LT = 271,
     GT = 272,
     LE = 273,
     GE = 274,
     EQUAL = 275,
     UNEQUAL = 276,
     ASSIGN = 277,
     LP = 278,
     RP = 279,
     LB = 280,
     RB = 281,
     DOT = 282,
     COMMA = 283,
     SEMI = 284,
     COLON = 285,
     DOTDOT = 286,
     AND = 287,
     ARRAY = 288,
     BBEGIN = 289,
     CASE = 290,
     CONST = 291,
     DO = 292,
     DOWNTO = 293,
     ELSE = 294,
     END = 295,
     FOR = 296,
     FUNCTION = 297,
     GOTO = 298,
     IF = 299,
     IN = 300,
     LABEL = 301,
     MOD = 302,
     NIL = 303,
     NOT = 304,
     OF = 305,
     OR = 306,
     OTHERWISE = 307,
     PROCEDURE = 308,
     PROGRAM = 309,
     RECORD = 310,
     READ = 311,
     REPEAT = 312,
     THEN = 313,
     TO = 314,
     TYPE = 315,
     UNTIL = 316,
     VAR = 317,
     WHILE = 318,
     TESTFUNC = 319,
     TESTPROC = 320,
     TESTCON = 321,
     WRITE = 322,
     WRITELN = 323
   };
#endif
/* Tokens.  */
#define INTVALUE 258
#define REALVALUE 259
#define CHARVALUE 260
#define STRINGVALUE 261
#define INTEGER 262
#define REAL 263
#define CHAR 264
#define STRING 265
#define IDENTIFIER 266
#define PLUS 267
#define MINUS 268
#define MUL 269
#define DIV 270
#define LT 271
#define GT 272
#define LE 273
#define GE 274
#define EQUAL 275
#define UNEQUAL 276
#define ASSIGN 277
#define LP 278
#define RP 279
#define LB 280
#define RB 281
#define DOT 282
#define COMMA 283
#define SEMI 284
#define COLON 285
#define DOTDOT 286
#define AND 287
#define ARRAY 288
#define BBEGIN 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FOR 296
#define FUNCTION 297
#define GOTO 298
#define IF 299
#define IN 300
#define LABEL 301
#define MOD 302
#define NIL 303
#define NOT 304
#define OF 305
#define OR 306
#define OTHERWISE 307
#define PROCEDURE 308
#define PROGRAM 309
#define RECORD 310
#define READ 311
#define REPEAT 312
#define THEN 313
#define TO 314
#define TYPE 315
#define UNTIL 316
#define VAR 317
#define WHILE 318
#define TESTFUNC 319
#define TESTPROC 320
#define TESTCON 321
#define WRITE 322
#define WRITELN 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 22 "parser.y"

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



/* Line 2068 of yacc.c  */
#line 256 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


