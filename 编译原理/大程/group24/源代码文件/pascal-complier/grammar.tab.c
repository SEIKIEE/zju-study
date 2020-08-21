/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 2 "grammar.y"

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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 273 "grammar.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   585

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNRULES -- Number of states.  */
#define YYNSTATES  310

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    14,    17,    20,    23,    26,
      29,    34,    37,    38,    41,    43,    48,    50,    52,    54,
      56,    58,    60,    62,    65,    66,    69,    71,    76,    78,
      80,    82,    84,    88,    92,    97,   103,   107,   109,   111,
     113,   115,   122,   126,   129,   131,   136,   140,   142,   145,
     146,   149,   151,   156,   159,   160,   163,   166,   168,   170,
     173,   178,   184,   189,   193,   194,   198,   202,   204,   208,
     211,   213,   215,   217,   219,   223,   226,   230,   231,   235,
     239,   241,   243,   245,   247,   249,   251,   253,   255,   257,
     259,   263,   270,   276,   278,   283,   288,   290,   295,   297,
     302,   308,   309,   312,   317,   322,   331,   340,   346,   349,
     351,   356,   361,   364,   368,   370,   374,   378,   382,   386,
     390,   394,   396,   400,   404,   408,   410,   414,   418,   422,
     426,   428,   430,   432,   434,   436,   438,   440,   442,   444,
     446,   451,   453,   457,   460,   463,   468,   472,   477,   482,
     487,   492,   497,   502,   507,   512,   516
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    76,    77,    41,    -1,     1,    40,    -1,
       3,   107,    40,    -1,     1,    40,    -1,    79,   108,    -1,
       1,    40,    -1,    79,   108,    -1,     1,    40,    -1,    80,
      84,    94,    97,    -1,     6,    81,    -1,    -1,    81,    82,
      -1,    82,    -1,   107,    20,    83,    40,    -1,   106,    -1,
      62,    -1,    63,    -1,    64,    -1,    51,    -1,    52,    -1,
      53,    -1,     7,    85,    -1,    -1,    85,    86,    -1,    86,
      -1,   107,    20,    87,    40,    -1,    88,    -1,    89,    -1,
      90,    -1,   107,    -1,    43,    93,    44,    -1,    83,    42,
      83,    -1,    28,    83,    42,    83,    -1,    28,    83,    42,
      28,    83,    -1,   107,    42,   107,    -1,    47,    -1,    48,
      -1,    50,    -1,    49,    -1,    54,    38,    88,    39,    55,
      87,    -1,    56,    91,    58,    -1,    91,    92,    -1,    92,
      -1,    93,    46,    87,    40,    -1,    93,    45,   107,    -1,
     107,    -1,     8,    95,    -1,    -1,    95,    96,    -1,    96,
      -1,    93,    46,    87,    40,    -1,     1,    40,    -1,    -1,
      97,    98,    -1,    97,   100,    -1,    98,    -1,   100,    -1,
       1,    40,    -1,    99,    40,    78,    40,    -1,     4,   107,
     102,    46,    88,    -1,   101,    40,    78,    40,    -1,     5,
     107,   102,    -1,    -1,    43,   103,    44,    -1,   103,    40,
     104,    -1,   104,    -1,   105,    46,    88,    -1,     8,    93,
      -1,    93,    -1,    61,    -1,    60,    -1,   109,    -1,    57,
     110,    58,    -1,     1,    40,    -1,   110,     1,    40,    -1,
      -1,   110,   111,    40,    -1,   106,    46,   112,    -1,   112,
      -1,   113,    -1,   114,    -1,   109,    -1,   115,    -1,   117,
      -1,   118,    -1,   119,    -1,   120,    -1,   123,    -1,   107,
      26,   125,    -1,   107,    38,   125,    39,    26,   125,    -1,
     107,    41,   107,    26,   125,    -1,   107,    -1,   107,    43,
     129,    44,    -1,    35,    43,   128,    44,    -1,    36,    -1,
      36,    43,   124,    44,    -1,    37,    -1,    37,    43,   124,
      44,    -1,     9,   125,    10,   111,   116,    -1,    -1,    11,
     111,    -1,    12,   110,    13,   125,    -1,    14,   125,    15,
     111,    -1,    19,   107,    26,   125,    17,   125,    15,   111,
      -1,    19,   107,    26,   125,    18,   125,    15,   111,    -1,
      16,   125,    55,   121,    58,    -1,   121,   122,    -1,   122,
      -1,    83,    46,   111,    40,    -1,   107,    46,   111,    40,
      -1,    59,   106,    -1,   124,    45,   125,    -1,   125,    -1,
     125,    22,   126,    -1,   125,    23,   126,    -1,   125,    24,
     126,    -1,   125,    25,   126,    -1,   125,    20,   126,    -1,
     125,    21,   126,    -1,   126,    -1,   126,    27,   127,    -1,
     126,    28,   127,    -1,   126,    31,   127,    -1,   127,    -1,
     127,    29,   128,    -1,   127,    30,   128,    -1,   127,    34,
     128,    -1,   127,    32,   128,    -1,   128,    -1,   107,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,   107,    43,   129,    44,
      -1,    83,    -1,    43,   125,    44,    -1,    33,   128,    -1,
      28,   128,    -1,   107,    38,   125,    39,    -1,   107,    41,
     107,    -1,    65,    43,   129,    44,    -1,    66,    43,   129,
      44,    -1,    67,    43,   129,    44,    -1,    68,    43,   129,
      44,    -1,    69,    43,   129,    44,    -1,    70,    43,   129,
      44,    -1,    71,    43,   129,    44,    -1,    72,    43,   129,
      44,    -1,   129,    45,   125,    -1,   125,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    36,    36,    47,    52,    59,    64,    71,    76,    84,
      88,    97,   100,   102,   115,   120,   128,   132,   138,   144,
     152,   158,   164,   171,   175,   177,   190,   195,   202,   203,
     204,   206,   213,   219,   226,   234,   243,   250,   255,   260,
     265,   271,   279,   284,   298,   301,   307,   320,   323,   326,
     328,   341,   344,   352,   358,   361,   374,   387,   388,   390,
     395,   406,   415,   426,   435,   436,   439,   452,   455,   462,
     466,   472,   479,   485,   488,   491,   496,   501,   502,   516,
     522,   525,   527,   529,   531,   533,   535,   537,   539,   541,
     544,   550,   558,   567,   573,   580,   586,   591,   597,   602,
     609,   617,   618,   621,   628,   635,   644,   654,   661,   674,
     677,   683,   690,   696,   709,   712,   719,   726,   733,   740,
     747,   754,   759,   766,   773,   780,   785,   792,   799,   806,
     813,   816,   820,   822,   824,   826,   828,   830,   832,   834,
     836,   843,   845,   847,   853,   859,   865,   871,   877,   883,
     889,   895,   901,   907,   913,   920,   933
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE",
  "CONST", "TYPE", "VAR", "IF", "THEN", "ELSE", "REPEAT", "UNTIL", "WHILE",
  "DO", "CASE", "TO", "DOWNTO", "FOR", "EQUAL", "UNEQUAL", "GE", "GT",
  "LE", "LT", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "OR", "AND", "NOT",
  "MOD", "READ", "WRITE", "WRITELN", "LB", "RB", "SEMI", "DOT", "DOTDOT",
  "LP", "RP", "COMMA", "COLON", "INTEGER_TYPE", "BOOLEAN_TYPE",
  "CHAR_TYPE", "REAL_TYPE", "TRUE", "FALSE", "MAXINT", "ARRAY", "OF",
  "RECORD", "TOKEN_BEGIN", "END", "GOTO", "TOKEN_ID", "TOKEN_INTEGER",
  "REAL", "CHAR", "STRING", "ABS", "CHR", "ODD", "ORD", "PRED", "SQR",
  "SQRT", "SUCC", "ERROR", "$accept", "program", "program_head", "routine",
  "sub_routine", "routine_head", "const_part", "const_expr_list",
  "const_expr", "const_value", "type_part", "type_decl_list",
  "type_definition", "type_decl", "simple_type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "name_list",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_name_list", "INTEGER", "ID",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "case_stmt", "case_expr_list", "case_expr",
  "goto_stmt", "expression_list", "expression", "expr", "term", "factor",
  "args_list", 0
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    81,    82,    83,    83,    83,    83,
      83,    83,    83,    84,    84,    85,    85,    86,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    90,    91,    91,    92,    93,    93,    94,    94,
      95,    95,    96,    97,    97,    97,    97,    97,    97,    98,
      98,    99,   100,   101,   102,   102,   103,   103,   104,   105,
     105,   106,   107,   108,   109,   110,   110,   110,   110,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     115,   116,   116,   117,   118,   119,   119,   120,   121,   121,
     122,   122,   123,   124,   124,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     3,     2,     2,     2,     2,     2,
       4,     2,     0,     2,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     2,     1,     4,     1,     1,
       1,     1,     3,     3,     4,     5,     3,     1,     1,     1,
       1,     6,     3,     2,     1,     4,     3,     1,     2,     0,
       2,     1,     4,     2,     0,     2,     2,     1,     1,     2,
       4,     5,     4,     3,     0,     3,     3,     1,     3,     2,
       1,     1,     1,     1,     3,     2,     3,     0,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     5,     1,     4,     4,     1,     4,     1,     4,
       5,     0,     2,     4,     4,     8,     8,     5,     2,     1,
       4,     4,     2,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     2,     2,     4,     3,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     3,    72,     0,     1,     0,
       0,     0,     0,    24,     4,     5,    11,    14,     0,     2,
       0,     6,    73,     0,    49,    13,     0,     0,     0,    23,
      26,     0,     0,     0,    20,    21,    22,    71,    17,    18,
      19,     0,    16,    75,     0,     0,     0,     0,     0,     0,
       0,    96,    98,    74,     0,     0,    93,    83,     0,    80,
      81,    82,    84,    85,    86,    87,    88,    89,    25,     0,
       0,    48,    51,    47,     0,     0,     0,     0,    57,     0,
      58,     0,    15,    76,     0,     0,     0,   132,   133,   134,
     135,   136,   137,   138,   139,   141,   131,     0,   121,   125,
     130,     0,     0,     0,     0,     0,     0,     0,   112,     0,
       0,     0,     0,     0,    78,     0,     0,    37,    38,    40,
      39,     0,     0,     0,     0,    28,    29,    30,    31,     0,
       0,    50,    53,    64,    64,     0,    55,    56,     0,     0,
     144,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,    79,    90,     0,     0,
     156,     0,     0,     0,     0,     0,    44,     0,     0,    27,
       0,    46,     0,     0,     0,    63,    59,     0,     0,     0,
       0,   142,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   146,     0,   101,   119,   120,   115,   116,   117,   118,
     122,   123,   124,   126,   127,   129,   128,   103,   104,     0,
       0,     0,   109,     0,    95,    97,     0,    99,     0,     0,
      94,     0,     0,    32,     0,    42,    43,     0,    33,    36,
      52,     0,    70,     0,    67,     0,     0,     7,    60,     8,
      62,   147,   148,   149,   150,   151,   152,   153,   154,   145,
     140,     0,   100,     0,     0,   107,   108,     0,     0,   113,
       0,    92,   155,     0,    34,     0,     0,    69,     0,    65,
       0,    61,   102,     0,     0,     0,     0,    91,    35,     0,
      45,    66,    68,   110,   111,     0,     0,    41,   105,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    11,   198,   199,    13,    16,    17,    95,
      24,    29,    30,   124,   125,   126,   127,   185,   186,    70,
      33,    71,    72,    77,    78,    79,    80,    81,   194,   253,
     254,   255,    42,    96,    21,    57,    28,    58,    59,    60,
      61,    62,   272,    63,    64,    65,    66,   231,   232,    67,
     173,   180,    98,    99,   100,   181
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -178
static const yytype_int16 yypact[] =
{
      74,   -34,   -31,    35,    44,  -178,  -178,     6,  -178,    25,
     -31,    45,    13,   102,  -178,    59,   -31,  -178,    99,  -178,
      24,  -178,  -178,   -31,   121,  -178,   459,   103,   135,   -31,
    -178,   117,   -31,    14,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   108,  -178,  -178,   115,   328,   200,   328,   328,   -31,
     110,   119,   123,  -178,   129,   128,    -4,  -178,   162,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   358,
     -29,   -31,  -178,  -178,   163,   -31,   -31,    19,  -178,   164,
    -178,   165,  -178,  -178,   328,   328,   328,   126,   167,   168,
     172,   175,   185,   187,   189,  -178,    57,   466,    75,    34,
    -178,   280,   517,    33,   181,   328,   328,   328,  -178,   317,
     328,   328,   -31,   328,  -178,   459,   -31,  -178,  -178,  -178,
    -178,   170,   -31,   191,   194,  -178,  -178,  -178,   197,   -31,
     358,  -178,  -178,   199,   199,   203,  -178,  -178,   219,   219,
    -178,  -178,   434,   328,   328,   328,   328,   328,   328,   328,
     328,   328,   -31,   328,   309,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   328,   328,   328,   309,
     455,   328,   196,    -3,   554,    52,  -178,   554,   440,   218,
     554,    67,   204,    81,   385,    29,  -178,    89,   459,  -178,
     -31,  -178,   207,     2,   206,  -178,  -178,   213,   215,    13,
     216,  -178,    95,    97,   113,   116,   134,   140,   142,   153,
     446,  -178,   155,   251,    75,    75,    75,    75,    75,    75,
      34,    34,    34,  -178,  -178,  -178,  -178,   554,  -178,   217,
     220,   441,  -178,   548,  -178,  -178,   328,  -178,   238,   328,
    -178,   328,   389,  -178,   228,  -178,  -178,   358,  -178,  -178,
    -178,   -31,   223,    64,  -178,   224,   385,    59,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   309,  -178,   309,   309,  -178,  -178,   328,   328,   554,
     328,   554,   554,   459,  -178,   222,   233,   223,     2,  -178,
     385,  -178,  -178,   235,   239,   528,   539,   554,  -178,   358,
    -178,  -178,  -178,  -178,  -178,   309,   309,  -178,  -178,  -178
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,   139,   276,  -178,  -178,   268,   -25,
    -178,  -178,   256,  -126,  -177,  -178,  -178,  -178,   105,  -113,
    -178,  -178,   227,  -178,   210,  -178,   214,  -178,   161,  -178,
      12,  -178,   -23,    -2,   106,   -10,   255,  -141,   193,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    76,  -178,
     201,    70,   425,   -39,   -73,   381
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -78
static const yytype_int16 yytable[] =
{
       7,    41,    22,   183,   192,    55,     5,   244,    18,   187,
     251,   140,   141,   213,    18,    74,   129,   130,    75,    76,
     135,    31,   110,    75,    76,    27,    56,    31,   228,     6,
      73,   108,   172,   -77,   111,     8,   -77,   112,   -77,   113,
     -77,   235,   236,   -77,   123,     9,    14,   104,   -12,   -12,
      10,   -12,   -12,   155,   156,   157,   158,   159,   160,   -77,
     -77,   -77,     6,   164,   165,    15,   166,   128,   167,    73,
      20,   -54,   187,   133,   134,     1,   -10,     2,    55,   291,
     252,   -77,   -77,   -77,   -77,   -77,    19,   245,   170,     6,
     182,   223,   224,   225,   226,   151,   237,   236,   152,    56,
     153,   -12,   161,   162,   288,   123,   163,    56,   289,    23,
     179,   240,   241,   302,    73,    97,    -9,   102,   103,    26,
      73,   286,   220,   221,   222,   243,   129,   191,   128,    32,
     292,    55,   293,   294,   129,   247,    44,    69,   287,   261,
     241,   262,   241,    43,    45,   229,    55,    46,    82,    47,
     211,    48,    56,   105,    49,    83,   142,   263,   241,   123,
     264,   241,   106,   248,   308,   309,   107,    56,   230,   143,
      50,    51,    52,   307,   109,   252,   174,   174,   265,   241,
     177,   178,   128,    73,   266,   241,   267,   241,   249,    22,
      37,    73,    20,    53,    54,     6,    37,   268,   241,   270,
     241,    27,   114,   132,   138,   139,   229,   171,   184,   -77,
     144,   145,   -77,   -77,   -77,   146,   -77,   284,   147,   -77,
     197,   210,   123,   -12,   -12,    10,   -12,   -12,   148,   230,
     149,   123,   150,   188,   189,   -77,   -77,   -77,   227,   190,
     234,   233,   193,   196,   239,   128,   242,   250,    55,    73,
      55,    55,   256,   257,   128,   258,   260,   -77,   298,   -77,
     -77,   -77,   271,   273,   280,   123,   274,   285,   129,    56,
     290,    56,    56,   300,   123,   303,   -12,   299,   200,   304,
      12,    44,    55,    55,    25,    68,    73,   136,   128,    45,
     246,   137,    46,   168,    47,   195,    48,   128,   131,    49,
     301,   101,   176,    56,    56,   259,   279,   276,   175,   281,
       0,   282,     0,     0,     0,    50,    51,    52,    45,     0,
       0,    46,     0,    47,     0,    48,    45,     0,    49,    46,
       0,    47,     0,    48,     0,     0,    49,    20,     0,    54,
       6,    37,     0,     0,    50,    51,    52,   295,   296,     0,
     297,     0,    50,    51,    52,     0,    84,     0,     0,     0,
       0,    85,     0,     0,     0,     0,    20,     0,    54,     6,
      37,    86,     0,     0,    20,     0,    54,     6,     0,    34,
      35,    36,     0,     0,     0,     0,   115,     0,     6,    37,
      38,    39,    40,    87,    88,    89,    90,    91,    92,    93,
      94,   116,     0,     0,     0,   117,   118,   119,   120,    34,
      35,    36,   121,   115,   122,     0,     0,   283,     6,    37,
      38,    39,    40,     0,     0,     0,     0,     0,   116,     0,
       0,     0,   117,   118,   119,   120,    34,    35,    36,     0,
      34,    35,    36,     0,     0,     6,    37,    38,    39,    40,
      37,    38,    39,    40,   155,   156,   157,   158,   159,   160,
     155,   156,   157,   158,   159,   160,   155,   156,   157,   158,
     159,   160,     0,     0,     0,     0,   154,     0,   201,   238,
       0,     0,     0,     0,     0,   269,   155,   156,   157,   158,
     159,   160,    34,    35,    36,     0,     0,     0,     0,   275,
       0,     6,    37,    38,    39,    40,    34,    35,    36,     0,
      34,    35,    36,     0,     0,     6,    37,    38,    39,    40,
      37,    38,    39,    40,   202,   203,   204,   205,   206,   207,
     208,   209,   169,     0,   212,     0,     0,   155,   156,   157,
     158,   159,   160,   305,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,   306,     0,     0,     0,     0,   155,
     156,   157,   158,   159,   160,   277,   278,     0,   155,   156,
     157,   158,   159,   160,   155,   156,   157,   158,   159,   160,
     214,   215,   216,   217,   218,   219
};

static const yytype_int16 yycheck[] =
{
       2,    26,    12,   116,   130,    28,    40,   184,    10,   122,
       8,    84,    85,   154,    16,     1,    45,    46,     4,     5,
       1,    23,    26,     4,     5,     1,    28,    29,   169,    60,
      32,    54,   105,     9,    38,     0,    12,    41,    14,    43,
      16,    44,    45,    19,    69,     1,    40,    49,     4,     5,
       6,     7,     8,    20,    21,    22,    23,    24,    25,    35,
      36,    37,    60,    29,    30,    40,    32,    69,    34,    71,
      57,    57,   185,    75,    76,     1,    57,     3,   101,   256,
     193,    57,    58,    59,    60,    61,    41,    58,    55,    60,
     115,   164,   165,   166,   167,    38,    44,    45,    41,   101,
      43,    57,    27,    28,    40,   130,    31,   109,    44,     7,
     112,    44,    45,   290,   116,    45,    57,    47,    48,    20,
     122,   247,   161,   162,   163,    44,    45,   129,   130,     8,
     271,   154,   273,   274,    45,    46,     1,    20,   251,    44,
      45,    44,    45,    40,     9,   170,   169,    12,    40,    14,
     152,    16,   154,    43,    19,    40,    86,    44,    45,   184,
      44,    45,    43,   188,   305,   306,    43,   169,   170,    43,
      35,    36,    37,   299,    46,   288,   106,   107,    44,    45,
     110,   111,   184,   185,    44,    45,    44,    45,   190,   199,
      61,   193,    57,    58,    59,    60,    61,    44,    45,    44,
      45,     1,    40,    40,    40,    40,   231,    26,    38,     9,
      43,    43,    12,    13,    14,    43,    16,   242,    43,    19,
       1,   151,   247,     4,     5,     6,     7,     8,    43,   231,
      43,   256,    43,    42,    40,    35,    36,    37,   168,    42,
      44,   171,    43,    40,    26,   247,    42,    40,   271,   251,
     273,   274,    46,    40,   256,    40,    40,    57,   283,    59,
      60,    61,    11,    46,    26,   290,    46,    39,    45,   271,
      46,   273,   274,    40,   299,    40,    57,    55,   139,    40,
       4,     1,   305,   306,    16,    29,   288,    77,   290,     9,
     185,    77,    12,    13,    14,   134,    16,   299,    71,    19,
     288,    46,   109,   305,   306,   199,   236,   231,   107,   239,
      -1,   241,    -1,    -1,    -1,    35,    36,    37,     9,    -1,
      -1,    12,    -1,    14,    -1,    16,     9,    -1,    19,    12,
      -1,    14,    -1,    16,    -1,    -1,    19,    57,    -1,    59,
      60,    61,    -1,    -1,    35,    36,    37,   277,   278,    -1,
     280,    -1,    35,    36,    37,    -1,    28,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    57,    -1,    59,    60,
      61,    43,    -1,    -1,    57,    -1,    59,    60,    -1,    51,
      52,    53,    -1,    -1,    -1,    -1,    28,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    43,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    28,    56,    -1,    -1,    28,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    -1,
      51,    52,    53,    -1,    -1,    60,    61,    62,    63,    64,
      61,    62,    63,    64,    20,    21,    22,    23,    24,    25,
      20,    21,    22,    23,    24,    25,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    10,    -1,    44,    39,
      -1,    -1,    -1,    -1,    -1,    39,    20,    21,    22,    23,
      24,    25,    51,    52,    53,    -1,    -1,    -1,    -1,    58,
      -1,    60,    61,    62,    63,    64,    51,    52,    53,    -1,
      51,    52,    53,    -1,    -1,    60,    61,    62,    63,    64,
      61,    62,    63,    64,   143,   144,   145,   146,   147,   148,
     149,   150,    15,    -1,   153,    -1,    -1,    20,    21,    22,
      23,    24,    25,    15,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    15,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    17,    18,    -1,    20,    21,
      22,    23,    24,    25,    20,    21,    22,    23,    24,    25,
     155,   156,   157,   158,   159,   160
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    75,    76,    40,    60,   107,     0,     1,
       6,    77,    79,    80,    40,    40,    81,    82,   107,    41,
      57,   108,   109,     7,    84,    82,    20,     1,   110,    85,
      86,   107,     8,    94,    51,    52,    53,    61,    62,    63,
      64,    83,   106,    40,     1,     9,    12,    14,    16,    19,
      35,    36,    37,    58,    59,   106,   107,   109,   111,   112,
     113,   114,   115,   117,   118,   119,   120,   123,    86,    20,
      93,    95,    96,   107,     1,     4,     5,    97,    98,    99,
     100,   101,    40,    40,    28,    33,    43,    65,    66,    67,
      68,    69,    70,    71,    72,    83,   107,   125,   126,   127,
     128,   110,   125,   125,   107,    43,    43,    43,   106,    46,
      26,    38,    41,    43,    40,    28,    43,    47,    48,    49,
      50,    54,    56,    83,    87,    88,    89,    90,   107,    45,
      46,    96,    40,   107,   107,     1,    98,   100,    40,    40,
     128,   128,   125,    43,    43,    43,    43,    43,    43,    43,
      43,    38,    41,    43,    10,    20,    21,    22,    23,    24,
      25,    27,    28,    31,    29,    30,    32,    34,    13,    15,
      55,    26,   128,   124,   125,   124,   112,   125,   125,   107,
     125,   129,    83,    93,    38,    91,    92,    93,    42,    40,
      42,   107,    87,    43,   102,   102,    40,     1,    78,    79,
      78,    44,   129,   129,   129,   129,   129,   129,   129,   129,
     125,   107,   129,   111,   126,   126,   126,   126,   126,   126,
     127,   127,   127,   128,   128,   128,   128,   125,   111,    83,
     107,   121,   122,   125,    44,    44,    45,    44,    39,    26,
      44,    45,    42,    44,    88,    58,    92,    46,    83,   107,
      40,     8,    93,   103,   104,   105,    46,    40,    40,   108,
      40,    44,    44,    44,    44,    44,    44,    44,    44,    39,
      44,    11,   116,    46,    46,    58,   122,    17,    18,   125,
      26,   125,   125,    28,    83,    39,    87,    93,    40,    44,
      46,    88,   111,   111,   111,   125,   125,   125,    83,    55,
      40,   104,    88,    40,    40,    15,    15,    87,   111,   111
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 37 "grammar.y"
    {   
                            (yyval) = newDeclNode(ProgramDecl);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (3)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(2) - (3)])->child[0];
                            (yyval)->child[1] = (yyvsp[(2) - (3)])->child[1];
                            savedTree = (yyval);
                            freeNode((yyvsp[(1) - (3)]));
                            free((yyvsp[(2) - (3)]));
                        ;}
    break;

  case 3:
#line 48 "grammar.y"
    {
                            yyerror("error");
                        ;}
    break;

  case 4:
#line 53 "grammar.y"
    {
                            (yyval) = newDeclNode(ProgramheadDecl);
                            (yyval)->attr.name = copyString((yyvsp[(2) - (3)])->attr.name);
                            freeNode((yyvsp[(2) - (3)]));
                        ;}
    break;

  case 5:
#line 60 "grammar.y"
    {
                            yyerror("error");
                        ;}
    break;

  case 6:
#line 65 "grammar.y"
    {
                            (yyval) = newDeclNode(RoutineDecl);
                            (yyval)->child[0] = (yyvsp[(1) - (2)]);
                            (yyval)->child[1] = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 7:
#line 72 "grammar.y"
    {
                            yyerror("error");
                        ;}
    break;

  case 8:
#line 77 "grammar.y"
    {
                             (yyval) = newDeclNode(RoutineDecl);
                             (yyval)->child[0] = (yyvsp[(1) - (2)]);
                             (yyval)->child[1] = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 9:
#line 85 "grammar.y"
    {
                            yyerror("error");
                        ;}
    break;

  case 10:
#line 89 "grammar.y"
    {
                            (yyval) = newDeclNode(RoutineheadDecl);
                            (yyval) ->child[0] = (yyvsp[(1) - (4)]);
                            (yyval) ->child[1] = (yyvsp[(2) - (4)]);
                            (yyval) ->child[2] = (yyvsp[(3) - (4)]);
                            (yyval) ->child[3] = (yyvsp[(4) - (4)]);
                        ;}
    break;

  case 11:
#line 98 "grammar.y"
    {(yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 12:
#line 100 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 13:
#line 103 "grammar.y"
    {
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 14:
#line 116 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 15:
#line 121 "grammar.y"
    {
                            (yyval) = newDeclNode(ConstDecl);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (4)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 16:
#line 129 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 17:
#line 133 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = RealExpType;
                            (yyval)->attr.realValue = atof(tokenString);
                        ;}
    break;

  case 18:
#line 139 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = CharExpType;
                            (yyval)->attr.charValue = tokenString[1];
                        ;}
    break;

  case 19:
#line 145 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = StringExpType;
                            (yyval)->attr.stringValue = (char*)malloc(strlen(tokenString) - 1);
                            memmove((yyval)->attr.stringValue, tokenString + 1, strlen(tokenString) - 2);
                            (yyval)->attr.stringValue[strlen(tokenString) - 2] = '\0';
                        ;}
    break;

  case 20:
#line 153 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = BoolExpType;
                            (yyval)->attr.intValue = 1;
                        ;}
    break;

  case 21:
#line 159 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = BoolExpType;
                            (yyval)->attr.intValue = 0;
                        ;}
    break;

  case 22:
#line 165 "grammar.y"
    {
                            (yyval) = newExpNode(ConstExp);
                            (yyval)->type = IntExpType;
                            (yyval)->attr.intValue = 2147483647;
                        ;}
    break;

  case 23:
#line 172 "grammar.y"
    {   
                            (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 24:
#line 175 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 25:
#line 178 "grammar.y"
    {
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 26:
#line 191 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 27:
#line 196 "grammar.y"
    {   
                            (yyval) = newDeclNode(TypeDecl);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 28:
#line 202 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 29:
#line 203 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 30:
#line 204 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 31:
#line 207 "grammar.y"
    {
                            (yyval) = newTypeNode(SimpleIdType);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (1)])->attr.name);
                            (yyval)->type = UserExpType;
                            freeNode((yyvsp[(1) - (1)]));
                        ;}
    break;

  case 32:
#line 214 "grammar.y"
    {   
                            (yyval) = newTypeNode(SimpleEnumType);
                            (yyval)->child[0] = (yyvsp[(2) - (3)]);
							(yyval)->type = EnumExpType;
                        ;}
    break;

  case 33:
#line 220 "grammar.y"
    {   
                            (yyval) = newTypeNode(simpleLimitType);
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
							(yyval)->type = LimitExpType;
                        ;}
    break;

  case 34:
#line 227 "grammar.y"
    {
                            (yyval) = newTypeNode(simpleLimitType);
                            (yyval)->child[0] = (yyvsp[(2) - (4)]);
                            (yyval)->child[0]->attr.intValue *= -1;
                            (yyval)->child[1] = (yyvsp[(4) - (4)]);
							(yyval)->type = LimitExpType;
                        ;}
    break;

  case 35:
#line 235 "grammar.y"
    {   
                            (yyval) = newTypeNode(simpleLimitType);
                            (yyval)->child[0] = (yyvsp[(2) - (5)]);
                            (yyval)->child[0]->attr.intValue *= -1;
                            (yyval)->child[1] = (yyvsp[(5) - (5)]);
                            (yyval)->child[1]->attr.intValue *= -1;
							(yyval)->type = LimitExpType;
                        ;}
    break;

  case 36:
#line 244 "grammar.y"
    {
                            (yyval) = newTypeNode(simpleLimitType);
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
							(yyval)->type = LimitExpType;
                        ;}
    break;

  case 37:
#line 251 "grammar.y"
    {   
                            (yyval) = newTypeNode(SimpleSysType);
                            (yyval)->type = IntExpType;
                        ;}
    break;

  case 38:
#line 256 "grammar.y"
    {   
                            (yyval) = newTypeNode(SimpleSysType);
                            (yyval)->type = BoolExpType;
                        ;}
    break;

  case 39:
#line 261 "grammar.y"
    {   
                            (yyval) = newTypeNode(SimpleSysType);
                            (yyval)->type = RealExpType;
                        ;}
    break;

  case 40:
#line 266 "grammar.y"
    {   
                            (yyval) = newTypeNode(SimpleSysType);
                            (yyval)->type = CharExpType;
                        ;}
    break;

  case 41:
#line 272 "grammar.y"
    {
                            (yyval) = newTypeNode(ArrayType);
                            (yyval)->child[0] = (yyvsp[(3) - (6)]);
                            (yyval)->child[1] = (yyvsp[(6) - (6)]);
                            (yyval)->type = ArrayExpType;
                        ;}
    break;

  case 42:
#line 280 "grammar.y"
    {
                            (yyval) = (yyvsp[(2) - (3)]);
                        ;}
    break;

  case 43:
#line 285 "grammar.y"
    {
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else {
                                (yyval)=(yyvsp[(2) - (2)]);
                            }
                        ;}
    break;

  case 44:
#line 299 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 45:
#line 302 "grammar.y"
    {
                            (yyval) = newTypeNode(RecordType);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 46:
#line 308 "grammar.y"
    {
                            YYSTYPE t = (yyvsp[(1) - (3)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(3) - (3)]);
                                (yyval) = (yyvsp[(1) - (3)]);
                            }
                            else
                                (yyval) = (yyvsp[(1) - (3)]);
                        ;}
    break;

  case 47:
#line 321 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 48:
#line 324 "grammar.y"
    {(yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 49:
#line 326 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 50:
#line 329 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval)=(yyvsp[(2) - (2)]);
                        ;}
    break;

  case 51:
#line 342 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 52:
#line 345 "grammar.y"
    {   
                            (yyval) = newDeclNode(VarDecl);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 53:
#line 353 "grammar.y"
    {
                            yyerror("error\n");
                        ;}
    break;

  case 54:
#line 358 "grammar.y"
    {   
                            (yyval) = NULL;
                        ;}
    break;

  case 55:
#line 362 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 56:
#line 375 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 57:
#line 387 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 58:
#line 388 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 59:
#line 391 "grammar.y"
    {
                            yyerror("error\n");
                        ;}
    break;

  case 60:
#line 396 "grammar.y"
    {
                            (yyval) = newDeclNode(FunctionDecl);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (4)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(1) - (4)])->child[0];    //参数列表
                            (yyval)->child[1] = (yyvsp[(1) - (4)])->child[1];    //返回类型
                            (yyval)->child[2] = (yyvsp[(3) - (4)])->child[0];    //变量定义
                            (yyval)->child[3] = (yyvsp[(3) - (4)])->child[1];    //子过程
                            free((yyvsp[(1) - (4)]));
                        ;}
    break;

  case 61:
#line 407 "grammar.y"
    {
                            (yyval) = newDeclNode(FunctionheadDecl);
                            (yyval)->attr.name = copyString((yyvsp[(2) - (5)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(3) - (5)]);  //参数列表
                            (yyval)->child[1] = (yyvsp[(5) - (5)]);  //返回类型
                            freeNode((yyvsp[(2) - (5)]));
                        ;}
    break;

  case 62:
#line 416 "grammar.y"
    {
                            (yyval) = newDeclNode(ProcedureDecl);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (4)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(1) - (4)])->child[0];    //参数类型
                            (yyval)->child[1] = NULL;            //返回类型
                            (yyval)->child[2] = (yyvsp[(3) - (4)])->child[0];    //变量定义
                            (yyval)->child[3] = (yyvsp[(3) - (4)])->child[1];    //子过程
                            free((yyvsp[(1) - (4)]));
                        ;}
    break;

  case 63:
#line 427 "grammar.y"
    {   
                            (yyval) = newDeclNode(ProcedureheadDecl);
                            (yyval)->attr.name = copyString((yyvsp[(2) - (3)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(3) - (3)]);
                            freeNode((yyvsp[(2) - (3)]));
                        ;}
    break;

  case 64:
#line 435 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 65:
#line 437 "grammar.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 66:
#line 440 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (3)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(3) - (3)]);
                                (yyval) = (yyvsp[(1) - (3)]);
                            }
                            else
                                (yyval) = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 67:
#line 453 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 68:
#line 456 "grammar.y"
    {
                            (yyval) = newDeclNode(VarParaDecl);
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 69:
#line 463 "grammar.y"
    {
                            (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 70:
#line 467 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 71:
#line 473 "grammar.y"
    {
                          (yyval) = newExpNode(ConstExp);
                          (yyval)->type = IntExpType;
                          (yyval)->attr.intValue = atoi(tokenString);
                      ;}
    break;

  case 72:
#line 480 "grammar.y"
    {   
                            (yyval) = newExpNode(IdExp);
                            (yyval)->attr.name=copyString(tokenString);
                        ;}
    break;

  case 73:
#line 486 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 74:
#line 489 "grammar.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 75:
#line 492 "grammar.y"
    {
                        yyerror("error\n");
                    ;}
    break;

  case 76:
#line 497 "grammar.y"
    {
                        yyerror("error\n");
                    ;}
    break;

  case 77:
#line 501 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 78:
#line 503 "grammar.y"
    {
                            YYSTYPE t = (yyvsp[(1) - (3)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (3)]);
                                (yyval) = (yyvsp[(1) - (3)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (3)]);
                        ;}
    break;

  case 79:
#line 517 "grammar.y"
    {
                            (yyval) = newStmtNode(LabelStmt);
                            (yyval)->attr.intValue = (yyvsp[(1) - (3)])->attr.intValue;
                            (yyval)->child[0] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 80:
#line 523 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 81:
#line 526 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 82:
#line 528 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 83:
#line 530 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 84:
#line 532 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 85:
#line 534 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 86:
#line 536 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 87:
#line 538 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 88:
#line 540 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 89:
#line 542 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 90:
#line 545 "grammar.y"
    {   
                            (yyval) = newStmtNode(AssignStmt);
			                (yyval)->child[0] = (yyvsp[(1) - (3)]);
			                (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 91:
#line 551 "grammar.y"
    {  
                            (yyval) = newStmtNode(AssignStmt);
			                (yyvsp[(1) - (6)])->type = ArrayExpType;
			                (yyval)->child[0] = (yyvsp[(1) - (6)]);
			                (yyval)->child[1] = (yyvsp[(3) - (6)]);
                            (yyval)->child[2] = (yyvsp[(6) - (6)]);
			            ;}
    break;

  case 92:
#line 559 "grammar.y"
    {   
                            (yyval) = newStmtNode(AssignStmt);
                            (yyvsp[(1) - (5)])->type = RecordExpType;
                            (yyval)->child[0] = (yyvsp[(1) - (5)]);
                            (yyvsp[(1) - (5)])->child[0] = (yyvsp[(3) - (5)]);
                            (yyval)->child[1] = (yyvsp[(5) - (5)]);
                        ;}
    break;

  case 93:
#line 568 "grammar.y"
    {
							(yyval) = newStmtNode(FuncIdStmt);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (1)])->attr.name);
                            freeNode((yyvsp[(1) - (1)]));
                        ;}
    break;

  case 94:
#line 574 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncIdStmt);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (4)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                            freeNode((yyvsp[(1) - (4)]));
                        ;}
    break;

  case 95:
#line 581 "grammar.y"
    {
                            (yyval) = newStmtNode(ProcSysStmt);
                            (yyval)->attr.op = ReadOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 96:
#line 587 "grammar.y"
    {   
                            (yyval) = newStmtNode(ProcSysStmt);
                            (yyval)->attr.op = WriteOp;
                        ;}
    break;

  case 97:
#line 592 "grammar.y"
    {   
                            (yyval) = newStmtNode(ProcSysStmt);
                            (yyval)->attr.op = WriteOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 98:
#line 598 "grammar.y"
    {   
                            (yyval) = newStmtNode(ProcSysStmt);
                            (yyval)->attr.op = WritelnOp;
                        ;}
    break;

  case 99:
#line 603 "grammar.y"
    {   
                            (yyval) = newStmtNode(ProcSysStmt);
                            (yyval)->attr.op = WritelnOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 100:
#line 610 "grammar.y"
    {   
                            (yyval) = newStmtNode(IfStmt);
                            (yyval)->child[0] = (yyvsp[(2) - (5)]);
                            (yyval)->child[1] = (yyvsp[(4) - (5)]);
                            (yyval)->child[2] = (yyvsp[(5) - (5)]);
                        ;}
    break;

  case 101:
#line 617 "grammar.y"
    {(yyval) = NULL;;}
    break;

  case 102:
#line 619 "grammar.y"
    {(yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 103:
#line 622 "grammar.y"
    {
                            (yyval) = newStmtNode(RepeatStmt);
                            (yyval)->child[0] = (yyvsp[(2) - (4)]);
                            (yyval)->child[1] = (yyvsp[(4) - (4)]);
                        ;}
    break;

  case 104:
#line 629 "grammar.y"
    {   
                            (yyval) = newStmtNode(WhileStmt);
                            (yyval)->child[0] = (yyvsp[(2) - (4)]);
                            (yyval)->child[1] = (yyvsp[(4) - (4)]);
                        ;}
    break;

  case 105:
#line 636 "grammar.y"
    {
                            (yyval) = newStmtNode(ForStmt);
                            (yyval)->attr.op = ToOp;
                            (yyval)->child[0] = (yyvsp[(2) - (8)]);
                            (yyval)->child[1] = (yyvsp[(4) - (8)]);
                            (yyval)->child[2] = (yyvsp[(6) - (8)]);
                            (yyval)->child[3] = (yyvsp[(8) - (8)]);
                        ;}
    break;

  case 106:
#line 645 "grammar.y"
    {
                            (yyval) = newStmtNode(ForStmt);
                            (yyval)->attr.op = DowntoOp;
                            (yyval)->child[0] = (yyvsp[(2) - (8)]);
                            (yyval)->child[1] = (yyvsp[(4) - (8)]);
                            (yyval)->child[2] = (yyvsp[(6) - (8)]);
                            (yyval)->child[3] = (yyvsp[(8) - (8)]);
                        ;}
    break;

  case 107:
#line 655 "grammar.y"
    {   
                            (yyval) = newStmtNode(CaseStmt);
                            (yyval)->child[0] = (yyvsp[(2) - (5)]);
                            (yyval)->child[1] = (yyvsp[(4) - (5)]);
                        ;}
    break;

  case 108:
#line 662 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (2)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(2) - (2)]);
                                (yyval) = (yyvsp[(1) - (2)]);
                            }
                            else
                                (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 109:
#line 675 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 110:
#line 678 "grammar.y"
    {
                            (yyval) = newExpNode(CaseExp);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 111:
#line 684 "grammar.y"
    {
                            (yyval) = newExpNode(CaseExp);
                            (yyval)->child[0] = (yyvsp[(1) - (4)]);
                            (yyval)->child[1] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 112:
#line 691 "grammar.y"
    {   
                            (yyval) = newStmtNode(GotoStmt);
                            (yyval)->attr.intValue = (yyvsp[(2) - (2)])->attr.intValue;
                        ;}
    break;

  case 113:
#line 697 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (3)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(3) - (3)]);
                                (yyval) = (yyvsp[(1) - (3)]);
                            }
                            else
                                (yyval) = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 114:
#line 710 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 115:
#line 713 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = GeOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 116:
#line 720 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = GtOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 117:
#line 727 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = LeOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 118:
#line 734 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = LtOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 119:
#line 741 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = EqualOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 120:
#line 748 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = UnequalOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 121:
#line 755 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 122:
#line 760 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = PlusOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 123:
#line 767 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = MinusOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 124:
#line 774 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = OrOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 125:
#line 781 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 126:
#line 786 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = MulOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 127:
#line 793 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = DivOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 128:
#line 800 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = ModOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 129:
#line 807 "grammar.y"
    {
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = AndOp;
                            (yyval)->child[0] = (yyvsp[(1) - (3)]);
                            (yyval)->child[1] = (yyvsp[(3) - (3)]);;
                        ;}
    break;

  case 130:
#line 814 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 131:
#line 817 "grammar.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 132:
#line 821 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 133:
#line 823 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 134:
#line 825 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 135:
#line 827 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 136:
#line 829 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 137:
#line 831 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 138:
#line 833 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 139:
#line 835 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 140:
#line 837 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncIdStmt);
                            (yyval)->attr.name = copyString((yyvsp[(1) - (4)])->attr.name);
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                            freeNode((yyvsp[(1) - (4)]));
                        ;}
    break;

  case 141:
#line 844 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 142:
#line 846 "grammar.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 143:
#line 848 "grammar.y"
    {   
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = NotOp;
                            (yyval)->child[0] = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 144:
#line 854 "grammar.y"
    {   
                            (yyval) = newExpNode(OpExp);
                            (yyval)->attr.op = MinusOp;
                            (yyval)->child[0] = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 145:
#line 860 "grammar.y"
    {   
                            (yyval) = (yyvsp[(1) - (4)]);
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                            (yyval)->type = ArrayExpType;
                        ;}
    break;

  case 146:
#line 866 "grammar.y"
    {   
                            (yyval) = (yyvsp[(1) - (3)]);
                            (yyval)->child[0] = (yyvsp[(3) - (3)]);
                            (yyval)->type = RecordExpType;
                        ;}
    break;

  case 147:
#line 872 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = AbsOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 148:
#line 878 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = ChrOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 149:
#line 884 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = OddOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 150:
#line 890 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = OrdOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 151:
#line 896 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = PredOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 152:
#line 902 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = SqrOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 153:
#line 908 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = SqrtOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 154:
#line 914 "grammar.y"
    {   
                            (yyval) = newStmtNode(FuncSysStmt);
                            (yyval)->attr.op = SuccOp;
                            (yyval)->child[0] = (yyvsp[(3) - (4)]);
                        ;}
    break;

  case 155:
#line 921 "grammar.y"
    {   
                            YYSTYPE t = (yyvsp[(1) - (3)]);
                            if(t != NULL)
                            {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = (yyvsp[(3) - (3)]);
                                (yyval) = (yyvsp[(1) - (3)]);
                            }
                            else
                                (yyval) = (yyvsp[(3) - (3)]);
                        ;}
    break;

  case 156:
#line 934 "grammar.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;


/* Line 1267 of yacc.c.  */
#line 3122 "grammar.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 936 "grammar.y"

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

