/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"


#include <cstdio>
#include <iostream>
#include "declare.h"
static int global_direction;
static int label;
//#define YYDEBUG 1
using namespace lwd;



/* Line 268 of yacc.c  */
#line 84 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
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



/* Line 293 of yacc.c  */
#line 326 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 338 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   476

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNRULES -- Number of states.  */
#define YYNSTATES  283

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    33,    37,    39,    42,
      45,    51,    52,    55,    56,    59,    61,    66,    68,    70,
      72,    74,    76,    78,    81,    82,    85,    87,    92,    94,
      96,    98,   100,   102,   106,   110,   115,   121,   125,   127,
     129,   131,   133,   140,   144,   147,   149,   154,   158,   160,
     163,   164,   167,   169,   174,   177,   180,   182,   184,   185,
     190,   196,   201,   205,   209,   210,   214,   216,   220,   224,
     227,   229,   231,   235,   239,   240,   241,   246,   248,   250,
     252,   254,   256,   258,   260,   262,   264,   266,   270,   277,
     283,   285,   290,   292,   297,   302,   304,   306,   310,   312,
     318,   321,   322,   327,   332,   341,   343,   345,   351,   354,
     356,   361,   366,   369,   373,   375,   379,   383,   387,   391,
     395,   399,   401,   405,   409,   413,   415,   419,   423,   427,
     431,   433,   435,   440,   442,   447,   449,   453,   456,   459,
     464,   468
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      76,     0,    -1,    29,    -1,     1,    -1,    24,    -1,     1,
      -1,    26,    -1,     1,    -1,    40,    -1,     1,    -1,    30,
      -1,     1,    -1,    58,    -1,     1,    -1,    77,    -1,    78,
      80,    27,    -1,    54,    79,    70,    -1,    11,    -1,    82,
     113,    -1,    82,   113,    -1,    83,    84,    89,   100,   103,
      -1,    -1,    36,    85,    -1,    -1,    85,    86,    -1,    86,
      -1,    79,    20,    87,    70,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,    88,    -1,    66,    -1,    60,    90,
      -1,    -1,    90,    91,    -1,    91,    -1,    79,    20,    92,
      70,    -1,    93,    -1,    95,    -1,    96,    -1,    94,    -1,
      79,    -1,    23,    99,    71,    -1,    87,    31,    87,    -1,
      13,    87,    31,    87,    -1,    13,    87,    31,    13,    87,
      -1,    79,    31,    79,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    33,    25,    93,    72,    50,    92,    -1,
      55,    97,    73,    -1,    97,    98,    -1,    98,    -1,    99,
      74,    92,    70,    -1,    99,    28,    79,    -1,    79,    -1,
      62,   101,    -1,    -1,   101,   102,    -1,   102,    -1,    99,
      74,    92,    70,    -1,   103,   104,    -1,   103,   106,    -1,
     104,    -1,   106,    -1,    -1,   105,    70,    81,    70,    -1,
      42,    79,   108,    74,    93,    -1,   107,    70,    81,    70,
      -1,    53,    79,   108,    -1,    23,   109,    71,    -1,    -1,
     109,    70,   110,    -1,   110,    -1,   111,    74,    93,    -1,
     112,    74,    93,    -1,    62,    99,    -1,    99,    -1,   114,
      -1,    34,   115,    73,    -1,   115,   116,    70,    -1,    -1,
      -1,     3,   117,    74,   118,    -1,   118,    -1,   119,    -1,
     120,    -1,   114,    -1,   123,    -1,   125,    -1,   126,    -1,
     127,    -1,   129,    -1,   132,    -1,    79,    22,   134,    -1,
      79,    25,   134,    72,    22,   134,    -1,    79,    27,    79,
      22,   134,    -1,    79,    -1,    79,    23,   122,    71,    -1,
     121,    -1,   121,    23,   133,    71,    -1,    56,    23,   137,
      71,    -1,    67,    -1,    68,    -1,   122,    28,   134,    -1,
     134,    -1,    44,   134,    75,   116,   124,    -1,    39,   116,
      -1,    -1,    57,   115,    61,   134,    -1,    63,   134,    37,
     116,    -1,    41,    79,    22,   134,   128,   134,    37,   116,
      -1,    59,    -1,    38,    -1,    35,   134,    50,   130,    73,
      -1,   130,   131,    -1,   131,    -1,    87,    74,   116,    70,
      -1,    79,    74,   116,    70,    -1,    43,     3,    -1,   133,
      28,   134,    -1,   134,    -1,   134,    19,   135,    -1,   134,
      17,   135,    -1,   134,    18,   135,    -1,   134,    16,   135,
      -1,   134,    20,   135,    -1,   134,    21,   135,    -1,   135,
      -1,   135,    12,   136,    -1,   135,    13,   136,    -1,   135,
      51,   136,    -1,   136,    -1,   136,    14,   137,    -1,   136,
      15,   137,    -1,   136,    47,   137,    -1,   136,    32,   137,
      -1,   137,    -1,    79,    -1,    79,    23,   122,    71,    -1,
     138,    -1,   138,    23,   122,    71,    -1,    87,    -1,    23,
     134,    71,    -1,    49,   137,    -1,    13,   137,    -1,    79,
      25,   134,    72,    -1,    79,    27,    79,    -1,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   165,   165,   166,   169,   170,   173,   174,   177,   178,
     181,   182,   185,   186,   189,   192,   195,   198,   201,   204,
     207,   210,   213,   214,   217,   224,   227,   230,   231,   232,
     233,   234,   236,   239,   240,   243,   250,   253,   256,   257,
     258,   261,   262,   263,   264,   265,   270,   275,   278,   279,
     280,   281,   284,   287,   290,   297,   300,   303,   304,   307,
     308,   311,   318,   321,   324,   335,   346,   347,   348,   351,
     354,   357,   360,   363,   364,   367,   374,   377,   378,   381,
     384,   387,   390,   393,   404,   407,   407,   413,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   427,   428,   429,
     432,   433,   434,   435,   436,   439,   440,   443,   450,   453,
     456,   457,   460,   463,   466,   469,   470,   473,   476,   483,
     486,   487,   490,   497,   504,   507,   508,   509,   510,   511,
     512,   513,   516,   517,   518,   519,   522,   523,   524,   525,
     526,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTVALUE", "REALVALUE", "CHARVALUE",
  "STRINGVALUE", "INTEGER", "REAL", "CHAR", "STRING", "IDENTIFIER", "PLUS",
  "MINUS", "MUL", "DIV", "LT", "GT", "LE", "GE", "EQUAL", "UNEQUAL",
  "ASSIGN", "LP", "RP", "LB", "RB", "DOT", "COMMA", "SEMI", "COLON",
  "DOTDOT", "AND", "ARRAY", "BBEGIN", "CASE", "CONST", "DO", "DOWNTO",
  "ELSE", "END", "FOR", "FUNCTION", "GOTO", "IF", "IN", "LABEL", "MOD",
  "NIL", "NOT", "OF", "OR", "OTHERWISE", "PROCEDURE", "PROGRAM", "RECORD",
  "READ", "REPEAT", "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE",
  "TESTFUNC", "TESTPROC", "TESTCON", "WRITE", "WRITELN", "$accept", "semi",
  "rp", "rb", "end", "colon", "then", "command", "program", "program_head",
  "ID", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_expr", "const_value", "sys_con",
  "type_part", "type_decl_list", "type_definition", "type_decl",
  "simple_type_decl", "sys_type", "array_type_decl", "record_type_decl",
  "field_decl_list", "field_decl", "name_list", "var_part",
  "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "$@1",
  "non_label_stmt", "assign_stmt", "proc_stmt", "sys_proc", "args_list",
  "if_stmt", "else_clause", "repeat_stmt", "while_stmt", "for_stmt",
  "direction", "case_stmt", "case_expr_list", "case_expr", "goto_stmt",
  "expression_list", "expression", "expr", "term", "factor", "sys_funct", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    84,    85,    85,    86,    87,    87,    87,
      87,    87,    88,    89,    89,    90,    90,    91,    92,    92,
      92,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    94,    95,    96,    97,    97,    98,    99,    99,   100,
     100,   101,   101,   102,   103,   103,   103,   103,   103,   104,
     105,   106,   107,   108,   108,   109,   109,   110,   110,   111,
     112,   113,   114,   115,   115,   117,   116,   116,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   119,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   123,
     124,   124,   125,   126,   127,   128,   128,   129,   130,   130,
     131,   131,   132,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     2,     2,
       5,     0,     2,     0,     2,     1,     4,     1,     1,     1,
       1,     1,     1,     2,     0,     2,     1,     4,     1,     1,
       1,     1,     1,     3,     3,     4,     5,     3,     1,     1,
       1,     1,     6,     3,     2,     1,     4,     3,     1,     2,
       0,     2,     1,     4,     2,     2,     1,     1,     0,     4,
       5,     4,     3,     3,     0,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     0,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     6,     5,
       1,     4,     1,     4,     4,     1,     1,     3,     1,     5,
       2,     0,     4,     4,     8,     1,     1,     5,     2,     1,
       4,     4,     2,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     4,     1,     4,     1,     3,     2,     2,     4,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    14,    21,    17,     0,     1,     0,     0,
      23,     3,     2,    16,    15,    84,    18,    81,     0,    34,
       0,     0,    22,    25,     0,    60,     9,    85,     0,     8,
       0,     0,     0,     0,    84,     0,   105,   106,    82,   100,
      90,     0,    87,    88,    89,   102,    91,    92,    93,    94,
      95,    96,     0,    24,     0,    33,    36,     0,    68,     0,
      27,    28,    29,    30,     0,     0,     0,   151,    32,   141,
     145,    31,     0,   131,   135,   140,   143,     0,   122,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,    35,    58,     0,    59,    62,     0,     0,    20,    66,
       0,    67,     0,    11,    10,     0,   148,     0,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    12,
       0,     0,     0,     0,    97,     0,   108,     0,     0,     0,
     124,    26,    48,    49,    50,    51,     0,     0,     0,     0,
      42,     0,     0,    38,    41,    39,    40,     0,     0,    61,
      74,    74,    64,    65,    21,    21,    86,     5,     4,   146,
       0,     0,   150,   128,   126,   127,   125,   129,   130,     0,
       0,     0,   119,   132,   133,   134,   136,   137,   139,   138,
       0,     0,   111,   104,   112,   113,     0,   101,     7,     6,
       0,     0,     0,   103,     0,     0,     0,     0,    55,     0,
       0,     0,    37,    57,     0,     0,     0,    72,     0,     0,
       0,   142,   149,     0,     0,   117,   118,   144,   116,   115,
       0,     0,   109,   107,     0,    99,   123,     0,    43,     0,
      53,    54,     0,    47,    44,    63,     0,    80,     0,    76,
       0,     0,     0,    69,    19,    71,     0,     0,     0,   110,
      98,     0,    45,     0,     0,    79,     5,     0,    73,     0,
       0,    70,   121,   120,     0,    46,     0,    56,    75,    77,
      78,   114,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,   169,   200,    38,   105,   130,     2,     3,     4,
      69,     8,   218,   219,    10,    19,    22,    23,    70,    71,
      25,    55,    56,   152,   153,   154,   155,   156,   207,   208,
      93,    58,    94,    95,    98,    99,   100,   101,   102,   216,
     248,   249,   250,   251,    16,    40,    20,    41,    59,    42,
      43,    44,    45,   135,    46,   232,    47,    48,    49,   230,
      50,   181,   182,    51,   139,   136,    73,    74,    75,    76
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -187
static const yytype_int16 yypact[] =
{
     -19,    35,    47,  -187,  -187,  -187,    15,  -187,    24,    34,
      43,  -187,  -187,  -187,  -187,  -187,  -187,  -187,    35,    40,
     245,    78,    35,  -187,    35,    50,  -187,  -187,   229,  -187,
      35,   102,   229,    95,  -187,   229,  -187,  -187,  -187,   317,
    -187,    15,  -187,  -187,  -187,   100,  -187,  -187,  -187,  -187,
    -187,  -187,     6,  -187,    99,    35,  -187,    35,   -39,    30,
    -187,  -187,  -187,  -187,   229,   229,   229,  -187,  -187,   190,
    -187,  -187,   391,    25,    67,  -187,   108,   112,  -187,   170,
     229,   280,   314,   229,   229,   229,    35,  -187,   229,    15,
     254,  -187,  -187,    27,    35,  -187,    35,    35,   -39,  -187,
      15,  -187,    15,  -187,  -187,   358,  -187,   433,  -187,   229,
     229,    35,   229,   229,   229,   229,   229,   229,    37,   229,
     229,   229,   229,   229,   229,   229,   229,   229,  -187,  -187,
     315,    96,   229,   315,   448,   121,   448,   412,   113,   154,
     448,  -187,  -187,  -187,  -187,  -187,     6,    35,   125,    35,
     120,   122,    15,  -187,  -187,  -187,  -187,    35,   254,  -187,
     135,   135,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
     121,   412,  -187,    25,    25,    25,    25,    25,    25,    30,
      30,    21,  -187,    67,    67,    67,  -187,  -187,  -187,  -187,
     121,   368,   126,  -187,   448,  -187,   229,  -187,  -187,  -187,
     138,   229,   229,  -187,   133,   171,   357,    38,  -187,    27,
      35,     6,  -187,  -187,    15,    -3,    30,  -187,    15,    34,
      15,  -187,  -187,   315,   315,  -187,  -187,  -187,  -187,  -187,
     229,   315,  -187,   448,   229,   448,   448,   134,  -187,    85,
    -187,  -187,   254,  -187,  -187,  -187,    35,   139,    29,  -187,
      30,    30,   357,  -187,  -187,  -187,    15,    15,   426,  -187,
     448,     6,  -187,   118,    15,   139,     2,    -3,  -187,   357,
     357,  -187,  -187,  -187,   315,  -187,   254,  -187,  -187,  -187,
    -187,  -187,  -187
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -187,   -37,   -64,  -170,  -119,   -88,  -187,  -187,  -187,  -187,
      -1,  -187,     5,   169,  -187,  -187,  -187,   153,   -45,  -187,
    -187,  -187,   124,  -152,  -186,  -187,  -187,  -187,  -187,   -31,
    -113,  -187,  -187,    91,  -187,    98,  -187,   103,  -187,    32,
    -187,   -73,  -187,  -187,   -21,    -7,   168,  -115,  -187,   105,
    -187,  -187,  -187,   -76,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    22,  -187,  -187,    42,   359,    23,   230,  -187
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
       6,   222,    17,    96,    87,   158,   214,    89,     5,    60,
      61,    62,    63,    -3,    97,   192,    11,    21,   195,    39,
     239,    21,    26,    54,    60,    61,    62,    63,   103,    77,
     266,   103,     5,   170,   205,     1,   209,   119,   120,    26,
      60,    61,    62,    63,    12,   151,     5,     7,     5,     5,
     190,    14,   141,   168,    54,   157,    92,   104,    12,   246,
     104,    29,   225,   164,    -3,   165,   271,   193,    15,   263,
      72,   197,    68,   180,    79,   203,   121,    82,    29,    18,
      39,   122,   123,   279,   280,   138,   198,    68,   240,   150,
     264,   223,   224,    92,   209,   160,   161,   167,    52,   124,
      24,   204,   247,    68,    39,    78,   221,   107,   256,   257,
     172,   199,    57,   151,   125,   212,   259,   179,    80,    90,
     168,   242,   167,    88,   282,   134,   227,   137,   252,    39,
     140,   126,    39,   265,   127,   201,   180,    60,    61,    62,
      63,   238,   183,   184,   185,   168,    92,   261,    92,   196,
     206,   210,   171,   211,   247,   167,   213,   150,   215,   281,
     234,   151,   269,   270,   237,   231,   244,   157,   276,   191,
     220,   128,   167,     9,   194,    53,   241,   245,   168,    91,
     179,   253,   202,   255,   268,   159,   112,   113,   114,   115,
     116,   117,   262,   217,   278,   168,   162,   151,   254,   157,
      68,   163,    81,   226,     0,   150,    92,   151,     0,   243,
     166,   267,    17,   109,    92,   110,   275,   111,     0,   272,
     273,     0,    39,    39,   151,   151,     0,   277,   129,     0,
      39,   151,    60,    61,    62,    63,     0,     0,   233,     0,
       5,   150,    64,   235,   236,    92,    26,     0,    27,     0,
       0,   150,    65,     0,     0,     0,     5,    60,    61,    62,
      63,   142,   143,   144,   145,     5,    92,   146,   150,   150,
       0,     0,   258,    39,     0,   150,   260,   147,    66,    15,
      28,     0,     0,    27,     0,    29,    30,   148,    31,    32,
       0,     5,     0,    67,   106,    68,   108,     0,     0,     0,
       0,    33,    34,     0,     0,     0,     0,     0,    35,   149,
     131,     0,    36,    37,    15,    28,     0,     0,    27,     0,
      68,    30,     0,    31,    32,     0,     5,     0,     0,     0,
     112,   113,   114,   115,   116,   117,    33,    34,     0,    83,
      84,   132,    85,    35,    86,     0,     0,    36,    37,    15,
      28,   133,   186,   187,   188,   189,    30,     0,    31,    32,
      60,    61,    62,    63,   142,   143,   144,   145,     5,     5,
     146,    33,    34,     0,     0,     0,     0,     0,    35,     0,
     147,     0,    36,    37,   112,   113,   114,   115,   116,   117,
       0,     0,    15,    28,     0,     0,     0,     0,     0,    30,
       0,    31,    32,     0,     0,     0,   228,   112,   113,   114,
     115,   116,   117,   198,    33,    34,     0,     0,     0,     0,
       0,    35,     0,    68,     0,    36,    37,   229,   112,   113,
     114,   115,   116,   117,   167,     0,     0,     0,   199,     0,
       0,   118,   112,   113,   114,   115,   116,   117,     0,   112,
     113,   114,   115,   116,   117,     0,     0,   168,     0,     0,
       0,     0,     0,   274,   112,   113,   114,   115,   116,   117,
       0,   173,   174,   175,   176,   177,   178
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-187))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,   171,     9,    42,    41,    93,   158,    52,    11,     3,
       4,     5,     6,    11,    53,   130,     1,    18,   133,    20,
     206,    22,     1,    24,     3,     4,     5,     6,     1,    30,
       1,     1,    11,   109,   147,    54,   149,    12,    13,     1,
       3,     4,     5,     6,    29,    90,    11,     0,    11,    11,
     126,    27,    89,    24,    55,    28,    57,    30,    29,    62,
      30,    40,   181,   100,    62,   102,   252,   131,    34,   239,
      28,   135,    66,   118,    32,   139,    51,    35,    40,    36,
      81,    14,    15,   269,   270,    86,     1,    66,   207,    90,
     242,   179,   180,    94,   207,    96,    97,     1,    20,    32,
      60,   146,   215,    66,   105,     3,   170,    65,   223,   224,
     111,    26,    62,   158,    47,   152,   231,   118,    23,    20,
      24,   209,     1,    23,   276,    83,   190,    85,   216,   130,
      88,    23,   133,   246,    22,    22,   181,     3,     4,     5,
       6,   205,   119,   120,   121,    24,   147,    13,   149,    28,
      25,    31,   110,    31,   267,     1,   157,   158,    23,   274,
      22,   206,   250,   251,    31,    39,   211,    28,    50,   127,
     165,     1,     1,     4,   132,    22,   207,   214,    24,    55,
     181,   218,    28,   220,   248,    94,    16,    17,    18,    19,
      20,    21,   237,   161,   267,    24,    98,   242,   219,    28,
      66,    98,    34,   181,    -1,   206,   207,   252,    -1,   210,
     105,   248,   219,    23,   215,    25,   261,    27,    -1,   256,
     257,    -1,   223,   224,   269,   270,    -1,   264,    58,    -1,
     231,   276,     3,     4,     5,     6,    -1,    -1,   196,    -1,
      11,   242,    13,   201,   202,   246,     1,    -1,     3,    -1,
      -1,   252,    23,    -1,    -1,    -1,    11,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   267,    13,   269,   270,
      -1,    -1,   230,   274,    -1,   276,   234,    23,    49,    34,
      35,    -1,    -1,     3,    -1,    40,    41,    33,    43,    44,
      -1,    11,    -1,    64,    64,    66,    66,    -1,    -1,    -1,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,    55,
      80,    -1,    67,    68,    34,    35,    -1,    -1,     3,    -1,
      66,    41,    -1,    43,    44,    -1,    11,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    21,    56,    57,    -1,    22,
      23,    61,    25,    63,    27,    -1,    -1,    67,    68,    34,
      35,    37,   122,   123,   124,   125,    41,    -1,    43,    44,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    11,
      13,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      23,    -1,    67,    68,    16,    17,    18,    19,    20,    21,
      -1,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    43,    44,    -1,    -1,    -1,    38,    16,    17,    18,
      19,    20,    21,     1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    66,    -1,    67,    68,    59,    16,    17,
      18,    19,    20,    21,     1,    -1,    -1,    -1,    26,    -1,
      -1,    50,    16,    17,    18,    19,    20,    21,    -1,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    37,    16,    17,    18,    19,    20,    21,
      -1,   112,   113,   114,   115,   116,   117
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    76,    77,    78,    11,    79,     0,    80,    82,
      83,     1,    29,    70,    27,    34,   113,   114,    36,    84,
     115,    79,    85,    86,    60,    89,     1,     3,    35,    40,
      41,    43,    44,    56,    57,    63,    67,    68,    73,    79,
     114,   116,   118,   119,   120,   121,   123,   125,   126,   127,
     129,   132,    20,    86,    79,    90,    91,    62,   100,   117,
       3,     4,     5,     6,    13,    23,    49,    64,    66,    79,
      87,    88,   134,   135,   136,   137,   138,    79,     3,   134,
      23,   115,   134,    22,    23,    25,    27,    70,    23,    87,
      20,    91,    79,    99,   101,   102,    42,    53,   103,   104,
     105,   106,   107,     1,    30,    74,   137,   134,   137,    23,
      25,    27,    16,    17,    18,    19,    20,    21,    50,    12,
      13,    51,    14,    15,    32,    47,    23,    22,     1,    58,
      75,   137,    61,    37,   134,   122,   134,   134,    79,   133,
     134,    70,     7,     8,     9,    10,    13,    23,    33,    55,
      79,    87,    92,    93,    94,    95,    96,    28,    74,   102,
      79,    79,   104,   106,    70,    70,   118,     1,    24,    71,
     122,   134,    79,   135,   135,   135,   135,   135,   135,    79,
      87,   130,   131,   136,   136,   136,   137,   137,   137,   137,
     122,   134,   116,    71,   134,   116,    28,    71,     1,    26,
      72,    22,    28,    71,    87,    99,    25,    97,    98,    99,
      31,    31,    70,    79,    92,    23,   108,   108,    81,    82,
      81,    71,    72,    74,    74,    73,   131,    71,    38,    59,
     128,    39,   124,   134,    22,   134,   134,    31,    71,    93,
      73,    98,    74,    79,    87,    70,    62,    99,   109,   110,
     111,   112,    74,    70,   113,    70,   116,   116,   134,   116,
     134,    13,    87,    72,    92,    99,     1,    70,    71,    74,
      74,    93,    70,    70,    37,    87,    50,    70,   110,    93,
      93,   116,    92
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 166 "parser.y"
    { fprintf(stderr, " : Possibly missing ';'\n"); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 170 "parser.y"
    { fprintf(stderr, " : Possibly missing ')'\n"); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 174 "parser.y"
    { fprintf(stderr, " : Possibly missing ']'\n"); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 178 "parser.y"
    { fprintf(stderr, " : Possibly missing 'end'\n"); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 182 "parser.y"
    { fprintf(stderr, " : Possibly missing ':'\n"); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 186 "parser.y"
    { fprintf(stderr, " : Possibly missing 'then'\n"); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 189 "parser.y"
    { savedRoot = (yyvsp[(1) - (1)].p1); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 192 "parser.y"
    { (yyval.p1) = new program((yyvsp[(1) - (3)].p2),(yyvsp[(2) - (3)].p3)); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 195 "parser.y"
    { (yyval.p2) = new program_head((yyvsp[(2) - (3)].p0)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 198 "parser.y"
    { (yyval.p0) = new identifier(yytext, lineno); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 201 "parser.y"
    { (yyval.p3) = new routine((yyvsp[(1) - (2)].p4),(yyvsp[(2) - (2)].p5)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 204 "parser.y"
    { (yyval.p34) = new sub_routine((yyvsp[(1) - (2)].p4),(yyvsp[(2) - (2)].p5)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 207 "parser.y"
    { (yyval.p4) = new routine_head((yyvsp[(1) - (5)].p6),(yyvsp[(2) - (5)].p7),(yyvsp[(3) - (5)].p8),(yyvsp[(4) - (5)].p9),(yyvsp[(5) - (5)].p10)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 210 "parser.y"
    { (yyval.p6) = new label_part(); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 213 "parser.y"
    { (yyval.p7) = new const_part((yyvsp[(2) - (2)].p12)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 214 "parser.y"
    { (yyval.p7) = new const_part(NULL); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 217 "parser.y"
    { 
					const_expr_list *node = (yyvsp[(1) - (2)].p12);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p11);
					(yyval.p12) = (yyvsp[(1) - (2)].p12);
				}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 224 "parser.y"
    { (yyval.p12) = (const_expr_list *)(yyvsp[(1) - (1)].p11); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 227 "parser.y"
    { (yyval.p11) = new const_expr((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p13),NULL); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 230 "parser.y"
    { (yyval.p13) = new const_value(1,yytext); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    { (yyval.p13) = new const_value(2,yytext); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 232 "parser.y"
    { (yyval.p13) = new const_value(3,yytext); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 233 "parser.y"
    { (yyval.p13) = new const_value(4,yytext); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 234 "parser.y"
    { (yyval.p13) = new const_value(5,yytext); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 236 "parser.y"
    { (yyval.p63) = new sys_con(); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 239 "parser.y"
    { (yyval.p8) = new type_part((yyvsp[(2) - (2)].p15)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 240 "parser.y"
    { (yyval.p8) = new type_part(NULL); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 243 "parser.y"
    {
					type_decl_list *node = (yyvsp[(1) - (2)].p15);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p14);
					(yyval.p15) = (yyvsp[(1) - (2)].p15);
				}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 250 "parser.y"
    { (yyval.p15) = (type_decl_list *)(yyvsp[(1) - (1)].p14); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 253 "parser.y"
    { (yyval.p14) = new type_definition((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p16),NULL); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 256 "parser.y"
    { (yyval.p16) = new type_decl((yyvsp[(1) - (1)].p17)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 257 "parser.y"
    { (yyval.p16) = new type_decl((yyvsp[(1) - (1)].p18)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 258 "parser.y"
    { (yyval.p16) = new type_decl((yyvsp[(1) - (1)].p19)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 261 "parser.y"
    { (yyval.p17) = new simple_type_decl((yyvsp[(1) - (1)].p20)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 262 "parser.y"
    { (yyval.p17) = new simple_type_decl((yyvsp[(1) - (1)].p0)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    { (yyval.p17) = new simple_type_decl((yyvsp[(2) - (3)].p21)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 264 "parser.y"
    { (yyval.p17) = new simple_type_decl(new range((yyvsp[(1) - (3)].p13),(yyvsp[(3) - (3)].p13))); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 265 "parser.y"
    { 
					range *temp = new range((yyvsp[(2) - (4)].p13),(yyvsp[(4) - (4)].p13)); 
					temp->negate(1);
					(yyval.p17) = new simple_type_decl(temp);
				}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 270 "parser.y"
    {
					range *temp = new range((yyvsp[(2) - (5)].p13),(yyvsp[(5) - (5)].p13));
					temp->negate();
					(yyval.p17) = new simple_type_decl(temp);
				}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 275 "parser.y"
    { (yyval.p17) = new simple_type_decl(new idrange((yyvsp[(1) - (3)].p0),(yyvsp[(3) - (3)].p0))); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 278 "parser.y"
    { (yyval.p20) = new sys_type(1); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 279 "parser.y"
    { (yyval.p20) = new sys_type(2); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 280 "parser.y"
    { (yyval.p20) = new sys_type(3); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 281 "parser.y"
    { (yyval.p20) = new sys_type(4); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 284 "parser.y"
    { (yyval.p18) = new array_type_decl((yyvsp[(3) - (6)].p17),(yyvsp[(6) - (6)].p16)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 287 "parser.y"
    { (yyval.p19) = new record_type_decl((yyvsp[(2) - (3)].p25)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 290 "parser.y"
    {
					field_decl_list *node = (yyvsp[(1) - (2)].p25);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p24);
					(yyval.p25) = (yyvsp[(1) - (2)].p25);
				}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 297 "parser.y"
    { (yyval.p25) = (field_decl_list *)(yyvsp[(1) - (1)].p24); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 300 "parser.y"
    { (yyval.p24) = new field_decl((yyvsp[(1) - (4)].p21),(yyvsp[(3) - (4)].p16),NULL); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 303 "parser.y"
    { (yyval.p21) = new name_list((yyvsp[(1) - (3)].p21),(yyvsp[(3) - (3)].p0)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 304 "parser.y"
    { (yyval.p21) = new name_list(NULL,(yyvsp[(1) - (1)].p0)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 307 "parser.y"
    { (yyval.p9) = new var_part((yyvsp[(2) - (2)].p27)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 308 "parser.y"
    { (yyval.p9) = new var_part(NULL); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 311 "parser.y"
    {
					var_decl_list *node = (yyvsp[(1) - (2)].p27);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p26);
					(yyval.p27) = (yyvsp[(1) - (2)].p27);
				}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 318 "parser.y"
    { (yyval.p27) = (var_decl_list *)(yyvsp[(1) - (1)].p26); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 321 "parser.y"
    { (yyval.p26) = new var_decl((yyvsp[(1) - (4)].p21),(yyvsp[(3) - (4)].p16),NULL); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 324 "parser.y"
    {
				function_decl *node = (yyvsp[(1) - (2)].p10)->child1;
				if(node==NULL)
					(yyvsp[(1) - (2)].p10)->child1 = (yyvsp[(2) - (2)].p28);
				else {
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p28);
				}
				(yyval.p10) = (yyvsp[(1) - (2)].p10);
			}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 335 "parser.y"
    {
				procedure_decl *node = (yyvsp[(1) - (2)].p10)->child2;
				if(node==NULL)
					(yyvsp[(1) - (2)].p10)->child2 = (yyvsp[(2) - (2)].p31);
				else {
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p31);
				}
				(yyval.p10) = (yyvsp[(1) - (2)].p10);
			}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 346 "parser.y"
    { (yyval.p10) = new routine_part((yyvsp[(1) - (1)].p28),NULL); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 347 "parser.y"
    { (yyval.p10) = new routine_part(NULL,(yyvsp[(1) - (1)].p31)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 348 "parser.y"
    { (yyval.p10) = new routine_part(NULL,NULL); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 351 "parser.y"
    { (yyval.p28) = new function_decl((yyvsp[(1) - (4)].p30),(yyvsp[(3) - (4)].p34),NULL); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 354 "parser.y"
    { (yyval.p30) = new function_head((yyvsp[(2) - (5)].p0),(yyvsp[(3) - (5)].p35),(yyvsp[(5) - (5)].p17)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 357 "parser.y"
    { (yyval.p31) = new procedure_decl((yyvsp[(1) - (4)].p33),(yyvsp[(3) - (4)].p34),NULL); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 360 "parser.y"
    { (yyval.p33) = new procedure_head((yyvsp[(2) - (3)].p0),(yyvsp[(3) - (3)].p35)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 363 "parser.y"
    { (yyval.p35) = new parameters((yyvsp[(2) - (3)].p37)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 364 "parser.y"
    { (yyval.p35) = NULL; }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 367 "parser.y"
    { 
					para_decl_list *node = (yyvsp[(1) - (3)].p37);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(3) - (3)].p36);
					(yyval.p37) = (yyvsp[(1) - (3)].p37);
				}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 374 "parser.y"
    { (yyval.p37) = (para_decl_list *)(yyvsp[(1) - (1)].p36); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 377 "parser.y"
    { (yyval.p36) = new para_type_list((yyvsp[(1) - (3)].p38),(yyvsp[(3) - (3)].p17),NULL); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 378 "parser.y"
    { (yyval.p36) = new para_type_list((yyvsp[(1) - (3)].p39),(yyvsp[(3) - (3)].p17),(yyvsp[(3) - (3)].p17),NULL); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 381 "parser.y"
    { (yyval.p38) = (var_para_list *)(yyvsp[(2) - (2)].p21); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 384 "parser.y"
    { (yyval.p39) = (val_para_list *) (yyvsp[(1) - (1)].p21); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 387 "parser.y"
    { (yyval.p5) = new routine_body((yyvsp[(1) - (1)].p40)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 390 "parser.y"
    { (yyval.p40) = new compound_stmt((yyvsp[(2) - (3)].p42),lineno); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 393 "parser.y"
    {
			stmt_list *node = (yyvsp[(1) - (3)].p42);
			if(node==NULL)
				(yyvsp[(1) - (3)].p42) = (stmt_list *)(yyvsp[(2) - (3)].p41);
			else {
				while(node->next!=NULL)
					node = node->next;
				node->next = (yyvsp[(2) - (3)].p41);
			}
			(yyval.p42) = (yyvsp[(1) - (3)].p42);
		}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 404 "parser.y"
    { (yyval.p42) = NULL; }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 407 "parser.y"
    { 
		sscanf(yytext, "%d", &label);
	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 410 "parser.y"
    {
		(yyval.p41) = new stmt(label, (yyvsp[(4) - (4)].p43), NULL);
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 413 "parser.y"
    { (yyval.p41) = new stmt((yyvsp[(1) - (1)].p43), NULL); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 416 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p44)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 417 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p45)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 418 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p40)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 419 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p46)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 420 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p47)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 421 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p48)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 422 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p49)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 423 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p50)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 424 "parser.y"
    { (yyval.p43) = new non_label_stmt((yyvsp[(1) - (1)].p51)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 427 "parser.y"
    { (yyval.p44) = new assign_stmt((yyvsp[(1) - (3)].p0),(yyvsp[(3) - (3)].p53)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 428 "parser.y"
    { (yyval.p44) = new assign_stmt((yyvsp[(1) - (6)].p0),(yyvsp[(3) - (6)].p53),(yyvsp[(6) - (6)].p53)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 429 "parser.y"
    { (yyval.p44) = new assign_stmt((yyvsp[(1) - (5)].p0),(yyvsp[(3) - (5)].p0),(yyvsp[(5) - (5)].p53)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 432 "parser.y"
    { (yyval.p45) = new proc_stmt((yyvsp[(1) - (1)].p0), lineno); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 433 "parser.y"
    { (yyval.p45) = new proc_stmt((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p54), lineno); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 434 "parser.y"
    { (yyval.p45) = new proc_stmt((yyvsp[(1) - (1)].p52), lineno); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 435 "parser.y"
    { (yyval.p45) = new proc_stmt((yyvsp[(1) - (4)].p52),(yyvsp[(3) - (4)].p55), lineno); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 436 "parser.y"
    { (yyval.p45) = new proc_stmt((yyvsp[(3) - (4)].p61), lineno); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 439 "parser.y"
    { (yyval.p52) = new sys_proc(wwrite); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 440 "parser.y"
    { (yyval.p52) = new sys_proc(wwriteln); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 443 "parser.y"
    {
			args_list *node = (yyvsp[(1) - (3)].p54);
			while(node->next!=NULL)
				node = node->next;
			node->next = (yyvsp[(3) - (3)].p53);
			(yyval.p54) = (yyvsp[(1) - (3)].p54);
		}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 450 "parser.y"
    { (yyval.p54) = (args_list *)(yyvsp[(1) - (1)].p53); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 453 "parser.y"
    { (yyval.p46) = new if_stmt((yyvsp[(2) - (5)].p53),(yyvsp[(4) - (5)].p41),(yyvsp[(5) - (5)].p56)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 456 "parser.y"
    { (yyval.p56) = new else_clause((yyvsp[(2) - (2)].p41)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 457 "parser.y"
    { (yyval.p56) = new else_clause(); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 460 "parser.y"
    { (yyval.p47) = new repeat_stmt((yyvsp[(2) - (4)].p42),(yyvsp[(4) - (4)].p53)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 463 "parser.y"
    { (yyval.p48) = new while_stmt((yyvsp[(2) - (4)].p53),(yyvsp[(4) - (4)].p41)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 466 "parser.y"
    { (yyval.p49) = new for_stmt((yyvsp[(2) - (8)].p0),(yyvsp[(4) - (8)].p53),global_direction,(yyvsp[(6) - (8)].p53),(yyvsp[(8) - (8)].p41)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 469 "parser.y"
    { global_direction = 1; }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 470 "parser.y"
    { global_direction = 2; }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 473 "parser.y"
    { (yyval.p50) = new case_stmt((yyvsp[(2) - (5)].p53),(yyvsp[(4) - (5)].p58)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 476 "parser.y"
    {
					case_expr_list *node = (yyvsp[(1) - (2)].p58);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(2) - (2)].p57);
					(yyval.p58) = (yyvsp[(1) - (2)].p58);
				}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 483 "parser.y"
    { (yyval.p58) = (case_expr_list *)(yyvsp[(1) - (1)].p57); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 486 "parser.y"
    { (yyval.p57) = new case_expr((yyvsp[(1) - (4)].p13),(yyvsp[(3) - (4)].p41),NULL); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 487 "parser.y"
    { (yyval.p57) = new case_expr((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p41),NULL); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 490 "parser.y"
    {
				int temp;
				sscanf(yytext,"%d",&temp);
				(yyval.p51) = new goto_stmt(temp);
			}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 497 "parser.y"
    { 
					expression_list *node = (yyvsp[(1) - (3)].p55);
					while(node->next!=NULL)
						node = node->next;
					node->next = (yyvsp[(3) - (3)].p53);
					(yyval.p55) = (yyvsp[(1) - (3)].p55);
				}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 504 "parser.y"
    { (yyval.p55) = (expression_list *)(yyvsp[(1) - (1)].p53); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 507 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),1,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 508 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),2,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 509 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),3,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 510 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),4,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 511 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),5,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 512 "parser.y"
    { (yyval.p53) = new expression((yyvsp[(1) - (3)].p53),6,(yyvsp[(3) - (3)].p59),NULL, lineno); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 513 "parser.y"
    { (yyval.p53) = new expression(NULL,1,(yyvsp[(1) - (1)].p59),NULL, lineno); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 516 "parser.y"
    { (yyval.p59) = new expr((yyvsp[(1) - (3)].p59),1,(yyvsp[(3) - (3)].p60), lineno); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 517 "parser.y"
    { (yyval.p59) = new expr((yyvsp[(1) - (3)].p59),2,(yyvsp[(3) - (3)].p60), lineno); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 518 "parser.y"
    { (yyval.p59) = new expr((yyvsp[(1) - (3)].p59),3,(yyvsp[(3) - (3)].p60), lineno); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 519 "parser.y"
    { (yyval.p59) = new expr(NULL,1,(yyvsp[(1) - (1)].p60), lineno); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 522 "parser.y"
    { (yyval.p60) = new term((yyvsp[(1) - (3)].p60),1,(yyvsp[(3) - (3)].p61), lineno); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 523 "parser.y"
    { (yyval.p60) = new term((yyvsp[(1) - (3)].p60),2,(yyvsp[(3) - (3)].p61), lineno); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 524 "parser.y"
    { (yyval.p60) = new term((yyvsp[(1) - (3)].p60),3,(yyvsp[(3) - (3)].p61), lineno); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 525 "parser.y"
    { (yyval.p60) = new term((yyvsp[(1) - (3)].p60),4,(yyvsp[(3) - (3)].p61), lineno); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 526 "parser.y"
    { (yyval.p60) = new term(NULL,1,(yyvsp[(1) - (1)].p61), lineno); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 529 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (1)].p0)); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 530 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p54)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 531 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (1)].p62)); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 532 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (4)].p62),(yyvsp[(3) - (4)].p54)); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 533 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (1)].p13)); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 534 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(2) - (3)].p53)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 535 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(2) - (2)].p61)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 536 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(2) - (2)].p61),(yyvsp[(2) - (2)].p61)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 537 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (4)].p0),(yyvsp[(3) - (4)].p53),(yyvsp[(3) - (4)].p53)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 538 "parser.y"
    { (yyval.p61) = new factor((yyvsp[(1) - (3)].p0),(yyvsp[(3) - (3)].p0)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 541 "parser.y"
    { (yyval.p62) = new sys_funct(); }
    break;



/* Line 1806 of yacc.c  */
#line 2979 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 544 "parser.y"


int yyerror(const std::string &msg) { 
	fprintf(stderr, "%s occurred at line %d", msg.c_str(), lineno); 
	error = true;
	return 0;
}

