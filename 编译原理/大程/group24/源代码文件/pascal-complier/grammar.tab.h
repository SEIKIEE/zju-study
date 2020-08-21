/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     PROGRAM = 258,
     FUNCTION = 259,
     PROCEDURE = 260,
     CONST = 261,
     TYPE = 262,
     VAR = 263,
     IF = 264,
     THEN = 265,
     ELSE = 266,
     REPEAT = 267,
     UNTIL = 268,
     WHILE = 269,
     DO = 270,
     CASE = 271,
     TO = 272,
     DOWNTO = 273,
     FOR = 274,
     EQUAL = 275,
     UNEQUAL = 276,
     GE = 277,
     GT = 278,
     LE = 279,
     LT = 280,
     ASSIGN = 281,
     PLUS = 282,
     MINUS = 283,
     MUL = 284,
     DIV = 285,
     OR = 286,
     AND = 287,
     NOT = 288,
     MOD = 289,
     READ = 290,
     WRITE = 291,
     WRITELN = 292,
     LB = 293,
     RB = 294,
     SEMI = 295,
     DOT = 296,
     DOTDOT = 297,
     LP = 298,
     RP = 299,
     COMMA = 300,
     COLON = 301,
     INTEGER_TYPE = 302,
     BOOLEAN_TYPE = 303,
     CHAR_TYPE = 304,
     REAL_TYPE = 305,
     TRUE = 306,
     FALSE = 307,
     MAXINT = 308,
     ARRAY = 309,
     OF = 310,
     RECORD = 311,
     TOKEN_BEGIN = 312,
     END = 313,
     GOTO = 314,
     TOKEN_ID = 315,
     TOKEN_INTEGER = 316,
     REAL = 317,
     CHAR = 318,
     STRING = 319,
     ABS = 320,
     CHR = 321,
     ODD = 322,
     ORD = 323,
     PRED = 324,
     SQR = 325,
     SQRT = 326,
     SUCC = 327,
     ERROR = 328
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define FUNCTION 259
#define PROCEDURE 260
#define CONST 261
#define TYPE 262
#define VAR 263
#define IF 264
#define THEN 265
#define ELSE 266
#define REPEAT 267
#define UNTIL 268
#define WHILE 269
#define DO 270
#define CASE 271
#define TO 272
#define DOWNTO 273
#define FOR 274
#define EQUAL 275
#define UNEQUAL 276
#define GE 277
#define GT 278
#define LE 279
#define LT 280
#define ASSIGN 281
#define PLUS 282
#define MINUS 283
#define MUL 284
#define DIV 285
#define OR 286
#define AND 287
#define NOT 288
#define MOD 289
#define READ 290
#define WRITE 291
#define WRITELN 292
#define LB 293
#define RB 294
#define SEMI 295
#define DOT 296
#define DOTDOT 297
#define LP 298
#define RP 299
#define COMMA 300
#define COLON 301
#define INTEGER_TYPE 302
#define BOOLEAN_TYPE 303
#define CHAR_TYPE 304
#define REAL_TYPE 305
#define TRUE 306
#define FALSE 307
#define MAXINT 308
#define ARRAY 309
#define OF 310
#define RECORD 311
#define TOKEN_BEGIN 312
#define END 313
#define GOTO 314
#define TOKEN_ID 315
#define TOKEN_INTEGER 316
#define REAL 317
#define CHAR 318
#define STRING 319
#define ABS 320
#define CHR 321
#define ODD 322
#define ORD 323
#define PRED 324
#define SQR 325
#define SQRT 326
#define SUCC 327
#define ERROR 328




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

