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
     IDENTIFIER = 258,
     TYPE_IDENTIFIER = 259,
     CHARACTER_CONSTANT = 260,
     STRING_LITERAL = 261,
     FLOAT_CONSTANT = 262,
     INTEGER_CONSTANT = 263,
     ASSIGN = 264,
     MINUS = 265,
     PLUS = 266,
     SEMICOLON = 267,
     AMP = 268,
     PERCENT = 269,
     SLASH = 270,
     STAR = 271,
     EXCL = 272,
     COMMA = 273,
     PERIOD = 274,
     COLON = 275,
     RR = 276,
     LR = 277,
     RB = 278,
     LB = 279,
     RP = 280,
     LP = 281,
     DOTDOTDOT = 282,
     BARBAR = 283,
     AMPAMP = 284,
     NEQ = 285,
     EQL = 286,
     GEQ = 287,
     LEQ = 288,
     GTR = 289,
     LSS = 290,
     ARROW = 291,
     MINUSMINUS = 292,
     PLUSPLUS = 293,
     WHILE_SYM = 294,
     UNION_SYM = 295,
     TYPEDEF_SYM = 296,
     SWITCH_SYM = 297,
     STRUCT_SYM = 298,
     STATIC_SYM = 299,
     SIZEOF_SYM = 300,
     RETURN_SYM = 301,
     IF_SYM = 302,
     FOR_SYM = 303,
     ENUM_SYM = 304,
     ELSE_SYM = 305,
     DO_SYM = 306,
     DEFAULT_SYM = 307,
     CONTINUE_SYM = 308,
     CASE_SYM = 309,
     BREAK_SYM = 310,
     AUTO_SYM = 311
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPE_IDENTIFIER 259
#define CHARACTER_CONSTANT 260
#define STRING_LITERAL 261
#define FLOAT_CONSTANT 262
#define INTEGER_CONSTANT 263
#define ASSIGN 264
#define MINUS 265
#define PLUS 266
#define SEMICOLON 267
#define AMP 268
#define PERCENT 269
#define SLASH 270
#define STAR 271
#define EXCL 272
#define COMMA 273
#define PERIOD 274
#define COLON 275
#define RR 276
#define LR 277
#define RB 278
#define LB 279
#define RP 280
#define LP 281
#define DOTDOTDOT 282
#define BARBAR 283
#define AMPAMP 284
#define NEQ 285
#define EQL 286
#define GEQ 287
#define LEQ 288
#define GTR 289
#define LSS 290
#define ARROW 291
#define MINUSMINUS 292
#define PLUSPLUS 293
#define WHILE_SYM 294
#define UNION_SYM 295
#define TYPEDEF_SYM 296
#define SWITCH_SYM 297
#define STRUCT_SYM 298
#define STATIC_SYM 299
#define SIZEOF_SYM 300
#define RETURN_SYM 301
#define IF_SYM 302
#define FOR_SYM 303
#define ENUM_SYM 304
#define ELSE_SYM 305
#define DO_SYM 306
#define DEFAULT_SYM 307
#define CONTINUE_SYM 308
#define CASE_SYM 309
#define BREAK_SYM 310
#define AUTO_SYM 311




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

	#define YYSTYPE_IS_DECLARED 1
	typedef long YYSTYPE;

	#include "type.h"
	#include "func.h"
	#include <stdio.h>
	#include <stdlib.h>

	extern int line_no, syntax_err;
	extern A_NODE *root;
	extern A_ID *current_id;
	extern int current_level;
	extern A_TYPE *int_type, *float_type, *char_type, *void_type, *string_type;

	int yyerror(char *s);
	int yylex();


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
#line 237 "y.tab.c"

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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNRULES -- Number of states.  */
#define YYNSTATES  293

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

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
      55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    15,    20,
      21,    25,    26,    28,    30,    33,    37,    39,    41,    44,
      47,    49,    51,    53,    54,    56,    58,    62,    64,    68,
      70,    74,    76,    80,    82,    84,    86,    87,    88,    96,
      97,    98,   105,   108,   110,   112,   114,   117,   121,   123,
     127,   129,   130,   137,   138,   144,   147,   149,   153,   155,
     156,   161,   164,   166,   168,   171,   173,   177,   182,   183,
     189,   190,   192,   194,   198,   200,   204,   207,   210,   211,
     213,   215,   217,   220,   224,   228,   233,   237,   242,   243,
     245,   247,   250,   252,   254,   256,   258,   260,   262,   267,
     271,   272,   278,   280,   283,   289,   297,   303,   309,   317,
     323,   329,   330,   332,   336,   339,   342,   343,   345,   347,
     351,   352,   354,   356,   358,   360,   362,   366,   368,   370,
     374,   376,   380,   382,   384,   386,   388,   392,   396,   398,
     402,   406,   410,   414,   416,   418,   422,   426,   428,   432,
     436,   440,   442,   447,   449,   452,   455,   458,   461,   464,
     467,   470,   473,   478,   480,   485,   490,   494,   498,   501,
     504,   506,   508,   510,   512,   514,   518
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      58,     0,    -1,    59,    -1,    60,    -1,    59,    60,    -1,
      61,    -1,    66,    -1,    -1,    67,    91,    62,   106,    -1,
      -1,    91,    63,   106,    -1,    -1,    65,    -1,    66,    -1,
      65,    66,    -1,    67,    69,    12,    -1,    74,    -1,    68,
      -1,    74,    67,    -1,    68,    67,    -1,    56,    -1,    44,
      -1,    41,    -1,    -1,    70,    -1,    71,    -1,    70,    18,
      71,    -1,    91,    -1,    91,     9,    72,    -1,   117,    -1,
      22,    73,    21,    -1,    72,    -1,    73,    18,    72,    -1,
      75,    -1,    85,    -1,     4,    -1,    -1,    -1,    80,     3,
      76,    22,    77,    81,    21,    -1,    -1,    -1,    80,    78,
      22,    79,    81,    21,    -1,    80,     3,    -1,    43,    -1,
      40,    -1,    82,    -1,    81,    82,    -1,    74,    83,    12,
      -1,    84,    -1,    83,    18,    84,    -1,    91,    -1,    -1,
      49,     3,    86,    22,    88,    21,    -1,    -1,    49,    87,
      22,    88,    21,    -1,    49,     3,    -1,    89,    -1,    88,
      18,    89,    -1,     3,    -1,    -1,     3,    90,     9,   118,
      -1,    92,    93,    -1,    93,    -1,    16,    -1,    16,    92,
      -1,     3,    -1,    26,    91,    25,    -1,    93,    24,   116,
      23,    -1,    -1,    93,    26,    94,    95,    25,    -1,    -1,
      96,    -1,    97,    -1,    97,    18,    27,    -1,    98,    -1,
      97,    18,    98,    -1,    67,    91,    -1,    67,    99,    -1,
      -1,   100,    -1,   101,    -1,    92,    -1,    92,   101,    -1,
      26,   100,    25,    -1,    24,   116,    23,    -1,   101,    24,
     116,    23,    -1,    26,    95,    25,    -1,   101,    26,    95,
      25,    -1,    -1,   103,    -1,   104,    -1,   103,   104,    -1,
     105,    -1,   106,    -1,   108,    -1,   109,    -1,   110,    -1,
     113,    -1,    54,   117,    20,   104,    -1,    52,    20,   104,
      -1,    -1,    22,   107,    64,   102,    21,    -1,    12,    -1,
     118,    12,    -1,    47,    26,   118,    25,   104,    -1,    47,
      26,   118,    25,   104,    50,   104,    -1,    42,    26,   118,
      25,   104,    -1,    39,    26,   118,    25,   104,    -1,    51,
     104,    39,    26,   118,    25,    12,    -1,    48,    26,   111,
      25,   104,    -1,   112,    12,   112,    12,   112,    -1,    -1,
     118,    -1,    46,   112,    12,    -1,    53,    12,    -1,    55,
      12,    -1,    -1,   115,    -1,   120,    -1,   115,    18,   120,
      -1,    -1,   117,    -1,   118,    -1,   119,    -1,   120,    -1,
     121,    -1,   133,     9,   120,    -1,   122,    -1,   123,    -1,
     122,    28,   123,    -1,   124,    -1,   123,    29,   124,    -1,
     125,    -1,   126,    -1,   127,    -1,   128,    -1,   127,    31,
     128,    -1,   127,    30,   128,    -1,   129,    -1,   128,    35,
     129,    -1,   128,    34,   129,    -1,   128,    33,   129,    -1,
     128,    32,   129,    -1,   130,    -1,   131,    -1,   130,    11,
     131,    -1,   130,    10,   131,    -1,   132,    -1,   131,    16,
     132,    -1,   131,    15,   132,    -1,   131,    14,   132,    -1,
     133,    -1,    26,   136,    25,   132,    -1,   134,    -1,    38,
     133,    -1,    37,   133,    -1,    13,   132,    -1,    16,   132,
      -1,    17,   132,    -1,    10,   132,    -1,    11,   132,    -1,
      45,   133,    -1,    45,    26,   136,    25,    -1,   135,    -1,
     134,    24,   118,    23,    -1,   134,    26,   114,    25,    -1,
     134,    19,     3,    -1,   134,    36,     3,    -1,   134,    38,
      -1,   134,    37,    -1,     3,    -1,     8,    -1,     7,    -1,
       5,    -1,     6,    -1,    26,   118,    25,    -1,    67,    99,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    30,    30,    35,    36,    40,    41,    45,    45,    47,
      47,    52,    53,    57,    58,    62,    67,    68,    69,    70,
      75,    76,    77,    81,    82,    86,    87,    92,    93,    97,
      98,   102,   104,   108,   109,   110,   115,   116,   114,   119,
     119,   119,   122,   127,   128,   132,   133,   137,   142,   143,
     148,   153,   152,   155,   155,   157,   162,   163,   167,   170,
     169,   175,   176,   180,   181,   185,   186,   187,   189,   189,
     196,   197,   201,   202,   207,   208,   213,   215,   221,   222,
     226,   227,   228,   233,   234,   236,   238,   240,   245,   246,
     250,   252,   256,   257,   258,   259,   260,   261,   265,   267,
     272,   272,   279,   280,   284,   286,   288,   293,   295,   297,
     302,   307,   308,   312,   314,   316,   321,   322,   326,   328,
     333,   334,   338,   342,   346,   350,   351,   356,   360,   361,
     366,   367,   372,   376,   380,   384,   385,   387,   392,   393,
     395,   397,   399,   404,   408,   409,   411,   416,   417,   419,
     421,   426,   427,   432,   433,   435,   437,   438,   439,   440,
     441,   442,   444,   449,   450,   452,   454,   456,   458,   460,
     465,   467,   468,   469,   470,   471,   475
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPE_IDENTIFIER",
  "CHARACTER_CONSTANT", "STRING_LITERAL", "FLOAT_CONSTANT",
  "INTEGER_CONSTANT", "ASSIGN", "MINUS", "PLUS", "SEMICOLON", "AMP",
  "PERCENT", "SLASH", "STAR", "EXCL", "COMMA", "PERIOD", "COLON", "RR",
  "LR", "RB", "LB", "RP", "LP", "DOTDOTDOT", "BARBAR", "AMPAMP", "NEQ",
  "EQL", "GEQ", "LEQ", "GTR", "LSS", "ARROW", "MINUSMINUS", "PLUSPLUS",
  "WHILE_SYM", "UNION_SYM", "TYPEDEF_SYM", "SWITCH_SYM", "STRUCT_SYM",
  "STATIC_SYM", "SIZEOF_SYM", "RETURN_SYM", "IF_SYM", "FOR_SYM",
  "ENUM_SYM", "ELSE_SYM", "DO_SYM", "DEFAULT_SYM", "CONTINUE_SYM",
  "CASE_SYM", "BREAK_SYM", "AUTO_SYM", "$accept", "program",
  "translation_unit", "external_declaration", "function_definition", "@1",
  "@2", "declaration_list_opt", "declaration_list", "declaration",
  "declaration_specifiers", "storage_class_specifier",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", "type_specifier",
  "struct_type_specifier", "@3", "@4", "@5", "@6", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_type_specifier",
  "@7", "@8", "enumerator_list", "enumerator", "@9", "declarator",
  "pointer", "direct_declarator", "@10", "parameter_type_list_opt",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "abstract_declarator_opt", "abstract_declarator",
  "direct_abstract_declarator", "statement_list_opt", "statement_list",
  "statement", "labeled_statement", "compound_statement", "@11",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_expression", "expression_opt", "jump_statement",
  "arg_expression_list_opt", "arg_expression_list",
  "constant_expression_opt", "constant_expression", "expression",
  "comma_expression", "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "bitwise_or_expression", "bitwise_xor_expression",
  "bitwise_and_expression", "equality_expression", "relational_expression",
  "shift_expression", "additive_expression", "multiplicative_expression",
  "cast_expression", "unary_expression", "postfix_expression",
  "primary_expression", "type_name", 0
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
     305,   306,   307,   308,   309,   310,   311
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    62,    61,    63,
      61,    64,    64,    65,    65,    66,    67,    67,    67,    67,
      68,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    76,    77,    75,    78,
      79,    75,    75,    80,    80,    81,    81,    82,    83,    83,
      84,    86,    85,    87,    85,    85,    88,    88,    89,    90,
      89,    91,    91,    92,    92,    93,    93,    93,    94,    93,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   100,   101,   101,   101,   101,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     107,   106,   108,   108,   109,   109,   109,   110,   110,   110,
     111,   112,   112,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   118,   119,   120,   120,   121,   122,   122,
     123,   123,   124,   125,   126,   127,   127,   127,   128,   128,
     128,   128,   128,   129,   130,   130,   130,   131,   131,   131,
     131,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   135,   135,   135,   135,   136
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     4,     0,
       3,     0,     1,     1,     2,     3,     1,     1,     2,     2,
       1,     1,     1,     0,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     0,     0,     7,     0,
       0,     6,     2,     1,     1,     1,     2,     3,     1,     3,
       1,     0,     6,     0,     5,     2,     1,     3,     1,     0,
       4,     2,     1,     1,     2,     1,     3,     4,     0,     5,
       0,     1,     1,     3,     1,     3,     2,     2,     0,     1,
       1,     1,     2,     3,     3,     4,     3,     4,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     3,
       0,     5,     1,     2,     5,     7,     5,     5,     7,     5,
       5,     0,     1,     3,     2,     2,     0,     1,     1,     3,
       0,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     1,     4,     4,     3,     3,     2,     2,
       1,     1,     1,     1,     1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    65,    35,    63,     0,    44,    22,    43,    21,    53,
      20,     0,     2,     3,     5,     6,    23,    17,    16,    33,
      39,    34,     9,     0,    62,    64,     0,    55,     0,     1,
       4,     0,    24,    25,    27,    19,    18,    42,     0,     0,
      61,   120,    68,    66,     0,     0,    15,     0,     0,     0,
       0,    40,   100,    10,   170,   173,   174,   172,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   121,
     122,   123,   124,   125,   127,   128,   130,   132,   133,   134,
     135,   138,   143,   144,   147,   151,   153,   163,    70,     0,
      58,     0,    56,    26,    27,     0,    28,    29,     8,    37,
       0,    11,   159,   151,   160,   156,   157,   158,    78,     0,
       0,     0,   155,   154,     0,   161,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,     0,   169,   168,    78,     0,    71,
      72,    74,     0,     0,     0,    54,    31,     0,     0,     0,
       0,    45,    88,    12,    13,    23,   120,    70,    81,   176,
      79,    80,   175,     0,     0,   129,   131,   137,   136,   142,
     141,   140,   139,   146,   145,   150,   149,   148,   126,   166,
       0,     0,   117,   118,   167,    70,    76,    81,    77,    69,
       0,    52,     0,    57,     0,    30,     0,     0,    48,    50,
      41,    46,   102,     0,     0,   111,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,    92,    93,    94,    95,
      96,    97,     0,    14,     0,     0,     0,    82,   120,    70,
     152,   162,   164,   165,     0,    73,    75,    60,    32,    38,
      47,     0,     0,     0,     0,   112,     0,   111,     0,     0,
     114,     0,   115,   101,    91,   103,    84,    86,    83,     0,
       0,   119,    49,     0,     0,   113,     0,     0,     0,     0,
      99,     0,    85,    87,     0,     0,     0,     0,   111,     0,
      98,   107,   106,   104,   109,     0,     0,     0,   111,     0,
     105,   110,   108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    49,    39,   152,   153,    15,
     137,    17,    31,    32,    33,    96,   147,    18,    19,    50,
     148,    38,   100,    20,   150,   151,   197,   198,    21,    44,
      28,    91,    92,   143,    22,    23,    24,    88,   225,   139,
     140,   141,   159,   160,   161,   213,   214,   215,   216,   217,
     101,   218,   219,   220,   267,   244,   221,   181,   182,    68,
      69,   222,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   110
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -165
static const yytype_int16 yypact[] =
{
     225,  -165,  -165,    12,    27,  -165,  -165,  -165,  -165,    29,
    -165,    48,   225,  -165,  -165,  -165,    27,    85,    85,  -165,
      49,  -165,  -165,    30,    61,  -165,    32,    46,    58,  -165,
    -165,   104,   103,  -165,    22,  -165,  -165,   108,   117,   127,
      61,   372,  -165,  -165,   147,   170,  -165,    27,   336,   127,
     160,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   372,
     372,   372,   372,   372,   205,   389,   389,   425,   153,  -165,
    -165,  -165,  -165,  -165,   157,   164,  -165,  -165,  -165,    77,
     200,  -165,   152,   209,  -165,   180,   234,  -165,    85,   170,
     190,    63,  -165,  -165,   191,   336,  -165,  -165,  -165,  -165,
      20,    85,  -165,  -165,  -165,  -165,  -165,  -165,    23,   179,
     182,   372,  -165,  -165,   205,  -165,  -165,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   211,   372,   372,   216,  -165,  -165,   107,   202,  -165,
     212,  -165,   126,   227,   170,  -165,  -165,   150,    20,    27,
     154,  -165,   272,    85,  -165,    27,   372,   289,   119,  -165,
    -165,   162,  -165,   372,   214,   164,  -165,   200,   200,  -165,
    -165,  -165,  -165,   209,   209,  -165,  -165,  -165,  -165,  -165,
     221,   230,   238,  -165,  -165,   116,  -165,    62,  -165,  -165,
      18,  -165,   372,  -165,   336,  -165,   177,    64,  -165,  -165,
    -165,  -165,  -165,   226,   231,   372,   233,   236,   272,   243,
     252,   372,   255,   265,   272,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,   261,  -165,   253,   262,   266,   162,   372,    85,
    -165,  -165,  -165,  -165,   372,  -165,  -165,  -165,  -165,  -165,
    -165,    27,   372,   372,   278,  -165,   372,   372,   256,   272,
    -165,   276,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   269,
     279,  -165,  -165,   281,   282,  -165,   283,   287,   285,   277,
    -165,   272,  -165,  -165,   272,   272,   272,   272,   372,   372,
    -165,  -165,  -165,   271,  -165,   304,   297,   272,   372,   316,
    -165,  -165,  -165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,   319,  -165,  -165,  -165,  -165,  -165,   -82,
       8,  -165,  -165,  -165,   288,   -89,  -165,   -84,  -165,  -165,
    -165,  -165,  -165,  -165,   186,  -121,  -165,    95,  -165,  -165,
    -165,   248,   196,  -165,    -1,    -2,   -21,  -165,   -83,  -165,
    -165,   158,   213,  -130,  -137,  -165,  -165,   -97,  -165,    88,
    -165,  -165,  -165,  -165,  -165,  -164,  -165,  -165,  -165,  -138,
     -44,   -41,  -165,  -116,  -165,  -165,   237,   239,  -165,  -165,
    -165,    72,   178,  -165,    70,   -50,   -25,  -165,  -165,   241
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -60
static const yytype_int16 yytable[] =
{
      70,    25,    40,    26,    97,   138,   146,    70,    16,   102,
     104,   105,   106,   107,   178,    34,   149,   183,   224,   154,
      16,   227,     2,   109,     2,    35,    36,   226,     3,   201,
       1,    48,    27,     1,   103,   103,   103,   103,   103,     3,
     112,   113,   115,     3,    -7,   235,    94,   156,    29,   157,
     227,    97,    37,     4,    70,   226,     4,    43,     5,     6,
       5,     7,     8,     7,   149,     1,   149,     9,   -51,     9,
     109,   223,   108,   109,    10,   201,   240,   175,   176,   177,
      45,   144,   241,   268,   145,    41,   156,    42,   185,     2,
     259,   180,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   238,   158,   119,   120,   155,
       1,   248,   149,   230,   285,    70,    46,   254,   261,     1,
       2,    47,   108,     3,   291,     5,     6,    53,     7,     8,
     -36,   156,     3,   185,     9,   187,   186,    98,   103,    51,
     156,    10,   185,   156,   144,   157,   260,   191,   199,    52,
      97,   237,   270,    70,    94,   158,     5,     6,     2,     7,
       8,   155,   125,   126,   245,     9,    40,   251,   194,    89,
      70,   195,    10,    90,   280,   200,   116,   281,   282,   283,
     284,     2,    99,   187,    26,   117,   228,    70,   229,   130,
     290,   167,   168,   118,     5,   173,   174,     7,   239,   -59,
      48,   263,   264,     9,   162,   266,   245,   163,    54,     2,
      55,    56,    57,    58,   179,    59,    60,     5,    61,   184,
       7,    62,    63,   127,   128,   129,     9,   189,     1,     2,
     190,    64,   121,   122,   123,   124,   192,   245,   286,   231,
     199,     3,    65,    66,   232,     5,     6,   245,     7,     8,
      67,     4,   242,   131,     9,   233,   234,   243,   132,   246,
     133,    10,   247,   249,   250,     5,     6,   252,     7,     8,
     134,   135,   136,   255,     9,    54,   256,    55,    56,    57,
      58,    10,    59,    60,   202,    61,   253,   257,    62,    63,
     265,   258,   272,     2,    52,   269,   271,   278,    64,   169,
     170,   171,   172,   279,   273,     3,   274,   275,   276,    65,
      66,   203,   277,   156,   204,   157,   288,    67,   205,   206,
     207,   287,   289,   208,   209,   210,   211,   212,   292,     5,
       6,    30,     7,     8,   196,    93,   262,   142,     9,    54,
     193,    55,    56,    57,    58,    10,    59,    60,   236,    61,
     188,     0,    62,    63,   165,   164,     0,   166,    95,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    54,     0,    55,    56,    57,
      58,    67,    59,    60,     0,    61,     0,     0,    62,    63,
       0,     0,    54,     0,    55,    56,    57,    58,    64,    59,
      60,     0,    61,     0,     0,    62,    63,     0,     0,    65,
      66,     0,     0,     0,     0,   111,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    54,     0,
      55,    56,    57,    58,    67,    59,    60,     0,    61,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,     0,     0,     0,     0,     0,     0,
      67
};

static const yytype_int16 yycheck[] =
{
      41,     3,    23,     4,    48,    88,    95,    48,     0,    59,
      60,    61,    62,    63,   130,    16,   100,   133,   156,   101,
      12,   158,     4,    64,     4,    17,    18,   157,    16,   150,
       3,     9,     3,     3,    59,    60,    61,    62,    63,    16,
      65,    66,    67,    16,    22,    27,    47,    24,     0,    26,
     187,    95,     3,    26,    95,   185,    26,    25,    40,    41,
      40,    43,    44,    43,   148,     3,   150,    49,    22,    49,
     111,   153,    64,   114,    56,   196,    12,   127,   128,   129,
      22,    18,    18,   247,    21,    24,    24,    26,    26,     4,
     228,   132,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   194,   108,    30,    31,   101,
       3,   208,   196,   163,   278,   156,    12,   214,   234,     3,
       4,    18,   114,    16,   288,    40,    41,    39,    43,    44,
      22,    24,    16,    26,    49,   137,   137,    49,   163,    22,
      24,    56,    26,    24,    18,    26,   229,    21,   149,    22,
     194,   192,   249,   194,   155,   157,    40,    41,     4,    43,
      44,   153,    10,    11,   205,    49,   187,   211,    18,    22,
     211,    21,    56,     3,   271,    21,    23,   274,   275,   276,
     277,     4,    22,   185,   185,    28,    24,   228,    26,     9,
     287,   119,   120,    29,    40,   125,   126,    43,    21,     9,
       9,   242,   243,    49,    25,   246,   247,    25,     3,     4,
       5,     6,     7,     8,     3,    10,    11,    40,    13,     3,
      43,    16,    17,    14,    15,    16,    49,    25,     3,     4,
      18,    26,    32,    33,    34,    35,     9,   278,   279,    25,
     241,    16,    37,    38,    23,    40,    41,   288,    43,    44,
      45,    26,    26,    19,    49,    25,    18,    26,    24,    26,
      26,    56,    26,    20,    12,    40,    41,    12,    43,    44,
      36,    37,    38,    12,    49,     3,    23,     5,     6,     7,
       8,    56,    10,    11,    12,    13,    21,    25,    16,    17,
      12,    25,    23,     4,    22,    39,    20,    12,    26,   121,
     122,   123,   124,    26,    25,    16,    25,    25,    25,    37,
      38,    39,    25,    24,    42,    26,    12,    45,    46,    47,
      48,    50,    25,    51,    52,    53,    54,    55,    12,    40,
      41,    12,    43,    44,   148,    47,   241,    89,    49,     3,
     144,     5,     6,     7,     8,    56,    10,    11,   190,    13,
     137,    -1,    16,    17,   117,   114,    -1,   118,    22,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,     3,    -1,     5,     6,     7,
       8,    45,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,     3,    -1,     5,     6,     7,     8,    26,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    37,
      38,    -1,    -1,    -1,    -1,    26,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,     3,    -1,
       5,     6,     7,     8,    45,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    16,    26,    40,    41,    43,    44,    49,
      56,    58,    59,    60,    61,    66,    67,    68,    74,    75,
      80,    85,    91,    92,    93,    92,    91,     3,    87,     0,
      60,    69,    70,    71,    91,    67,    67,     3,    78,    63,
      93,    24,    26,    25,    86,    22,    12,    18,     9,    62,
      76,    22,    22,   106,     3,     5,     6,     7,     8,    10,
      11,    13,    16,    17,    26,    37,    38,    45,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,    94,    22,
       3,    88,    89,    71,    91,    22,    72,   117,   106,    22,
      79,   107,   132,   133,   132,   132,   132,   132,    67,   118,
     136,    26,   133,   133,    26,   133,    23,    28,    29,    30,
      31,    32,    33,    34,    35,    10,    11,    14,    15,    16,
       9,    19,    24,    26,    36,    37,    38,    67,    95,    96,
      97,    98,    88,    90,    18,    21,    72,    73,    77,    74,
      81,    82,    64,    65,    66,    67,    24,    26,    92,    99,
     100,   101,    25,    25,   136,   123,   124,   128,   128,   129,
     129,   129,   129,   131,   131,   132,   132,   132,   120,     3,
     118,   114,   115,   120,     3,    26,    91,    92,    99,    25,
      18,    21,     9,    89,    18,    21,    81,    83,    84,    91,
      21,    82,    12,    39,    42,    46,    47,    48,    51,    52,
      53,    54,    55,   102,   103,   104,   105,   106,   108,   109,
     110,   113,   118,    66,   116,    95,   100,   101,    24,    26,
     132,    25,    23,    25,    18,    27,    98,   118,    72,    21,
      12,    18,    26,    26,   112,   118,    26,    26,   104,    20,
      12,   117,    12,    21,   104,    12,    23,    25,    25,   116,
      95,   120,    84,   118,   118,    12,   118,   111,   112,    39,
     104,    20,    23,    25,    25,    25,    25,    25,    12,    26,
     104,   104,   104,   104,   104,   112,   118,    50,    12,    25,
     104,   112,    12
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
#line 31 "yacc.y"
    {root=makeNode(N_PROGRAM,NIL,(yyvsp[(1) - (1)]),NIL); checkForwardReference();}
    break;

  case 3:
#line 35 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 4:
#line 36 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));}
    break;

  case 5:
#line 40 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 6:
#line 41 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 7:
#line 45 "yacc.y"
    {(yyval)=setFunctionDeclaratorSpecifier((yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]));}
    break;

  case 8:
#line 46 "yacc.y"
    {(yyval)=setFunctionDeclaratorBody((yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]));current_id=(yyvsp[(2) - (4)]);}
    break;

  case 9:
#line 47 "yacc.y"
    {(yyval)=setFunctionDeclaratorSpecifier((yyvsp[(1) - (1)]),makeSpecifier(int_type,0));}
    break;

  case 10:
#line 48 "yacc.y"
    {(yyval)=setFunctionDeclaratorBody((yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));current_id=(yyvsp[(1) - (3)]);}
    break;

  case 11:
#line 52 "yacc.y"
    {(yyval)=NIL;}
    break;

  case 12:
#line 53 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 13:
#line 57 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 14:
#line 58 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));}
    break;

  case 15:
#line 63 "yacc.y"
    {(yyval)=setDeclaratorListSpecifier((yyvsp[(2) - (3)]),(yyvsp[(1) - (3)]));}
    break;

  case 16:
#line 67 "yacc.y"
    {(yyval)=makeSpecifier((yyvsp[(1) - (1)]),0);}
    break;

  case 17:
#line 68 "yacc.y"
    {(yyval)=makeSpecifier(0,(yyvsp[(1) - (1)]));}
    break;

  case 18:
#line 69 "yacc.y"
    {(yyval)=updateSpecifier((yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]),0);}
    break;

  case 19:
#line 71 "yacc.y"
    {(yyval)=updateSpecifier((yyvsp[(2) - (2)]),0,(yyvsp[(1) - (2)]));}
    break;

  case 20:
#line 75 "yacc.y"
    {(yyval)=S_AUTO;}
    break;

  case 21:
#line 76 "yacc.y"
    {(yyval)=S_STATIC;}
    break;

  case 22:
#line 77 "yacc.y"
    {(yyval)=S_TYPEDEF;}
    break;

  case 23:
#line 81 "yacc.y"
    {(yyval)=makeDummyIdentifier();}
    break;

  case 24:
#line 82 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 25:
#line 86 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 26:
#line 88 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 27:
#line 92 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 28:
#line 93 "yacc.y"
    {(yyval)=setDeclaratorInit((A_ID*)(yyvsp[(1) - (3)]),(A_NODE*)(yyvsp[(3) - (3)]));}
    break;

  case 29:
#line 97 "yacc.y"
    {(yyval)=(A_NODE*)makeNode(N_INIT_LIST_ONE,NIL,(yyvsp[(1) - (1)]),NIL);}
    break;

  case 30:
#line 98 "yacc.y"
    {(yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 31:
#line 103 "yacc.y"
    {(yyval)=makeNode(N_INIT_LIST,(yyvsp[(1) - (1)]),NIL,makeNode(N_INIT_LIST_NIL,NIL,NIL,NIL));}
    break;

  case 32:
#line 104 "yacc.y"
    {(yyval)=makeNodeList(N_INIT_LIST,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 33:
#line 108 "yacc.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 34:
#line 109 "yacc.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 35:
#line 110 "yacc.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 36:
#line 115 "yacc.y"
    {(yyval)=setTypeStructOrEnumIdentifier((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),ID_STRUCT);}
    break;

  case 37:
#line 116 "yacc.y"
    { (yyval)=current_id;current_level++;}
    break;

  case 38:
#line 117 "yacc.y"
    {checkForwardReference();(yyval)=setTypeField((yyvsp[(3) - (7)]),(yyvsp[(6) - (7)]));current_level--;
	current_id=(yyvsp[(5) - (7)]);}
    break;

  case 39:
#line 119 "yacc.y"
    {(yyval)=makeType((yyvsp[(1) - (1)]));}
    break;

  case 40:
#line 119 "yacc.y"
    {(yyval)=current_id;current_level++;}
    break;

  case 41:
#line 120 "yacc.y"
    {checkForwardReference();(yyval)=setTypeField((yyvsp[(2) - (6)]),(yyvsp[(5) - (6)]));
	current_level--;current_id=(yyvsp[(4) - (6)]);}
    break;

  case 42:
#line 123 "yacc.y"
    {(yyval)=getTypeOfStructOrEnumRefIdentifier((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),ID_STRUCT);}
    break;

  case 43:
#line 127 "yacc.y"
    {(yyval)=T_STRUCT;}
    break;

  case 44:
#line 128 "yacc.y"
    {(yyval)=T_UNION;}
    break;

  case 45:
#line 132 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 46:
#line 133 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));}
    break;

  case 47:
#line 138 "yacc.y"
    {(yyval)=setStructDeclaratorListSpecifier((yyvsp[(2) - (3)]),(yyvsp[(1) - (3)]));}
    break;

  case 48:
#line 142 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 49:
#line 144 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 50:
#line 148 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 51:
#line 153 "yacc.y"
    {(yyval)=setTypeStructOrEnumIdentifier(T_ENUM,(yyvsp[(2) - (2)]),ID_ENUM);}
    break;

  case 52:
#line 154 "yacc.y"
    {(yyval)=setTypeField((yyvsp[(3) - (6)]),(yyvsp[(5) - (6)]));}
    break;

  case 53:
#line 155 "yacc.y"
    {(yyval)=makeType(T_ENUM);}
    break;

  case 54:
#line 156 "yacc.y"
    {(yyval)=setTypeField((yyvsp[(2) - (5)]),(yyvsp[(4) - (5)]));}
    break;

  case 55:
#line 158 "yacc.y"
    {(yyval)=getTypeOfStructOrEnumRefIdentifier(T_ENUM,(yyvsp[(2) - (2)]),ID_ENUM);}
    break;

  case 56:
#line 162 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 57:
#line 163 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 58:
#line 168 "yacc.y"
    {(yyval)=setDeclaratorKind(makeIdentifier((yyvsp[(1) - (1)])),ID_ENUM_LITERAL);}
    break;

  case 59:
#line 170 "yacc.y"
    {(yyval)=setDeclaratorKind(makeIdentifier((yyvsp[(1) - (1)])),ID_ENUM_LITERAL);}
    break;

  case 60:
#line 171 "yacc.y"
    {(yyval)=setDeclaratorInit((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]));}
    break;

  case 61:
#line 175 "yacc.y"
    {(yyval)=setDeclaratorElementType((yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]));}
    break;

  case 62:
#line 176 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 63:
#line 180 "yacc.y"
    {(yyval)=makeType(T_POINTER);}
    break;

  case 64:
#line 181 "yacc.y"
    {(yyval)=setTypeElementType((yyvsp[(2) - (2)]),makeType(T_POINTER));}
    break;

  case 65:
#line 185 "yacc.y"
    {(yyval)=makeIdentifier((yyvsp[(1) - (1)]));}
    break;

  case 66:
#line 186 "yacc.y"
    {(yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 67:
#line 188 "yacc.y"
    {(yyval)=setDeclaratorElementType((yyvsp[(1) - (4)]),setTypeExpr(makeType(T_ARRAY),(yyvsp[(3) - (4)])));}
    break;

  case 68:
#line 189 "yacc.y"
    {(yyval)=current_id;current_level++;}
    break;

  case 69:
#line 191 "yacc.y"
    {checkForwardReference();current_id=(yyvsp[(3) - (5)]);current_level--;
	(yyval)=setDeclaratorElementType((yyvsp[(1) - (5)]),setTypeField(makeType(T_FUNC),(yyvsp[(4) - (5)])));}
    break;

  case 70:
#line 196 "yacc.y"
    {(yyval)=NIL;}
    break;

  case 71:
#line 197 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 72:
#line 201 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 73:
#line 202 "yacc.y"
    {(yyval)=linkDeclaratorList(
	(yyvsp[(1) - (3)]),setDeclaratorKind(makeDummyIdentifier(),ID_PARM));}
    break;

  case 74:
#line 207 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 75:
#line 209 "yacc.y"
    {(yyval)=linkDeclaratorList((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 76:
#line 214 "yacc.y"
    {(yyval)=setParameterDeclaratorSpecifier((yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]));}
    break;

  case 77:
#line 216 "yacc.y"
    {(yyval)=setParameterDeclaratorSpecifier(setDeclaratorType(
	makeDummyIdentifier(),(yyvsp[(2) - (2)])),(yyvsp[(1) - (2)]));}
    break;

  case 78:
#line 221 "yacc.y"
    {(yyval)=NIL;}
    break;

  case 79:
#line 222 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 80:
#line 226 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 81:
#line 227 "yacc.y"
    {(yyval)=makeType(T_POINTER);}
    break;

  case 82:
#line 229 "yacc.y"
    {(yyval)=setTypeElementType((yyvsp[(2) - (2)]),makeType(T_POINTER));}
    break;

  case 83:
#line 233 "yacc.y"
    {(yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 84:
#line 235 "yacc.y"
    {(yyval)=setTypeExpr(makeType(T_ARRAY),(yyvsp[(2) - (3)]));}
    break;

  case 85:
#line 237 "yacc.y"
    {(yyval)=setTypeElementType((yyvsp[(1) - (4)]),setTypeExpr(makeType(T_ARRAY),(yyvsp[(3) - (4)])));}
    break;

  case 86:
#line 239 "yacc.y"
    {(yyval)=setTypeExpr(makeType(T_FUNC),(yyvsp[(2) - (3)]));}
    break;

  case 87:
#line 241 "yacc.y"
    {(yyval)=setTypeElementType((yyvsp[(1) - (4)]),setTypeExpr(makeType(T_FUNC),(yyvsp[(3) - (4)])));}
    break;

  case 88:
#line 245 "yacc.y"
    {(yyval)=makeNode(N_STMT_LIST_NIL,NIL,NIL,NIL);}
    break;

  case 89:
#line 246 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 90:
#line 250 "yacc.y"
    {(yyval)=makeNode(N_STMT_LIST,(yyvsp[(1) - (1)]),NIL,
	makeNode(N_STMT_LIST_NIL,NIL,NIL,NIL));}
    break;

  case 91:
#line 252 "yacc.y"
    {(yyval)=makeNodeList(N_STMT_LIST,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));}
    break;

  case 92:
#line 256 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 93:
#line 257 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 94:
#line 258 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 95:
#line 259 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 96:
#line 260 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 97:
#line 261 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 98:
#line 266 "yacc.y"
    {(yyval)=makeNode(N_STMT_LABEL_CASE, (yyvsp[(2) - (4)]),NIL,(yyvsp[(4) - (4)]));}
    break;

  case 99:
#line 268 "yacc.y"
    {(yyval)=makeNode(N_STMT_LABEL_DEFAULT,NIL,(yyvsp[(3) - (3)]),NIL);}
    break;

  case 100:
#line 272 "yacc.y"
    {(yyval)=current_id;current_level++;}
    break;

  case 101:
#line 273 "yacc.y"
    {checkForwardReference();
	(yyval)=makeNode(N_STMT_COMPOUND,(yyvsp[(3) - (5)]),NIL,(yyvsp[(4) - (5)])); current_id=(yyvsp[(2) - (5)]);
	current_level--;}
    break;

  case 102:
#line 279 "yacc.y"
    {(yyval)=makeNode(N_STMT_EMPTY,NIL,NIL,NIL);}
    break;

  case 103:
#line 280 "yacc.y"
    {(yyval)=makeNode(N_STMT_EXPRESSION,NIL,(yyvsp[(1) - (2)]),NIL);}
    break;

  case 104:
#line 285 "yacc.y"
    {(yyval)=makeNode(N_STMT_IF,(yyvsp[(3) - (5)]),NIL,(yyvsp[(5) - (5)]));}
    break;

  case 105:
#line 287 "yacc.y"
    {(yyval)=makeNode(N_STMT_IF_ELSE,(yyvsp[(3) - (7)]),(yyvsp[(5) - (7)]),(yyvsp[(7) - (7)]));}
    break;

  case 106:
#line 289 "yacc.y"
    {(yyval)=makeNode(N_STMT_SWITCH,(yyvsp[(3) - (5)]),NIL,(yyvsp[(5) - (5)]));}
    break;

  case 107:
#line 294 "yacc.y"
    {(yyval)=makeNode(N_STMT_WHILE,(yyvsp[(3) - (5)]),NIL,(yyvsp[(5) - (5)]));}
    break;

  case 108:
#line 296 "yacc.y"
    {(yyval)=makeNode(N_STMT_DO,(yyvsp[(2) - (7)]),NIL,(yyvsp[(5) - (7)]));}
    break;

  case 109:
#line 298 "yacc.y"
    {(yyval)=makeNode(N_STMT_FOR,(yyvsp[(3) - (5)]),NIL,(yyvsp[(5) - (5)]));}
    break;

  case 110:
#line 303 "yacc.y"
    {(yyval)=makeNode(N_FOR_EXP,(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]));}
    break;

  case 111:
#line 307 "yacc.y"
    {(yyval)=NIL;}
    break;

  case 112:
#line 308 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 113:
#line 313 "yacc.y"
    {(yyval)=makeNode(N_STMT_RETURN,NIL,(yyvsp[(2) - (3)]),NIL);}
    break;

  case 114:
#line 315 "yacc.y"
    {(yyval)=makeNode(N_STMT_CONTINUE,NIL,NIL,NIL);}
    break;

  case 115:
#line 317 "yacc.y"
    {(yyval)=makeNode(N_STMT_BREAK,NIL,NIL,NIL);}
    break;

  case 116:
#line 321 "yacc.y"
    {(yyval)=makeNode(N_ARG_LIST_NIL,NIL,NIL,NIL);}
    break;

  case 117:
#line 322 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 118:
#line 327 "yacc.y"
    {(yyval)=makeNode(N_ARG_LIST,(yyvsp[(1) - (1)]),NIL,makeNode(N_ARG_LIST_NIL,NIL,NIL,NIL));}
    break;

  case 119:
#line 329 "yacc.y"
    {(yyval)=makeNodeList(N_ARG_LIST,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 120:
#line 333 "yacc.y"
    {(yyval)=NIL;}
    break;

  case 121:
#line 334 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 122:
#line 338 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 123:
#line 342 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 124:
#line 346 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 125:
#line 350 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 126:
#line 352 "yacc.y"
    {(yyval)=makeNode(N_EXP_ASSIGN,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 127:
#line 356 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 128:
#line 360 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 129:
#line 362 "yacc.y"
    {(yyval)=makeNode(N_EXP_OR,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 130:
#line 366 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 131:
#line 368 "yacc.y"
    {(yyval)=makeNode(N_EXP_AND,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 132:
#line 372 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 133:
#line 376 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 134:
#line 380 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 135:
#line 384 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 136:
#line 386 "yacc.y"
    {(yyval)=makeNode(N_EXP_EQL,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 137:
#line 388 "yacc.y"
    {(yyval)=makeNode(N_EXP_NEQ,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 138:
#line 392 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 139:
#line 394 "yacc.y"
    {(yyval)=makeNode(N_EXP_LSS,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 140:
#line 396 "yacc.y"
    {(yyval)=makeNode(N_EXP_GTR,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 141:
#line 398 "yacc.y"
    {(yyval)=makeNode(N_EXP_LEQ,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 142:
#line 400 "yacc.y"
    {(yyval)=makeNode(N_EXP_GEQ,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 143:
#line 404 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 144:
#line 408 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 145:
#line 410 "yacc.y"
    {(yyval)=makeNode(N_EXP_ADD,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 146:
#line 412 "yacc.y"
    {(yyval)=makeNode(N_EXP_SUB,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 147:
#line 416 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 148:
#line 418 "yacc.y"
    {(yyval)=makeNode(N_EXP_MUL,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 149:
#line 420 "yacc.y"
    {(yyval)= makeNode(N_EXP_DIV,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 150:
#line 422 "yacc.y"
    {(yyval)= makeNode(N_EXP_MOD,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 151:
#line 426 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 152:
#line 428 "yacc.y"
    {(yyval)=makeNode(N_EXP_CAST,(yyvsp[(2) - (4)]),NIL,(yyvsp[(4) - (4)]));}
    break;

  case 153:
#line 432 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 154:
#line 434 "yacc.y"
    {(yyval)=makeNode(N_EXP_PRE_INC,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 155:
#line 436 "yacc.y"
    {(yyval)=makeNode(N_EXP_PRE_DEC,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 156:
#line 437 "yacc.y"
    {(yyval)=makeNode(N_EXP_AMP,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 157:
#line 438 "yacc.y"
    {(yyval)=makeNode(N_EXP_STAR,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 158:
#line 439 "yacc.y"
    {(yyval)=makeNode(N_EXP_NOT,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 159:
#line 440 "yacc.y"
    {(yyval)=makeNode(N_EXP_MINUS,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 160:
#line 441 "yacc.y"
    {(yyval)=makeNode(N_EXP_PLUS,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 161:
#line 443 "yacc.y"
    {(yyval)=makeNode(N_EXP_SIZE_EXP,NIL,(yyvsp[(2) - (2)]),NIL);}
    break;

  case 162:
#line 445 "yacc.y"
    {(yyval)=makeNode(N_EXP_SIZE_TYPE,NIL,(yyvsp[(3) - (4)]),NIL);}
    break;

  case 163:
#line 449 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 164:
#line 451 "yacc.y"
    {(yyval)=makeNode(N_EXP_ARRAY,(yyvsp[(1) - (4)]),NIL,(yyvsp[(3) - (4)]));}
    break;

  case 165:
#line 453 "yacc.y"
    {(yyval)=makeNode(N_EXP_FUNCTION_CALL,(yyvsp[(1) - (4)]),NIL,(yyvsp[(3) - (4)]));}
    break;

  case 166:
#line 455 "yacc.y"
    {(yyval)=makeNode(N_EXP_STRUCT,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 167:
#line 457 "yacc.y"
    {(yyval)=makeNode(N_EXP_ARROW,(yyvsp[(1) - (3)]),NIL,(yyvsp[(3) - (3)]));}
    break;

  case 168:
#line 459 "yacc.y"
    {(yyval)=makeNode(N_EXP_POST_INC,NIL,(yyvsp[(1) - (2)]),NIL);}
    break;

  case 169:
#line 461 "yacc.y"
    {(yyval)=makeNode(N_EXP_POST_DEC,NIL,(yyvsp[(1) - (2)]),NIL);}
    break;

  case 170:
#line 466 "yacc.y"
    {(yyval)=makeNode(N_EXP_IDENT,NIL,getIdentifierDeclared((yyvsp[(1) - (1)])),NIL);}
    break;

  case 171:
#line 467 "yacc.y"
    {(yyval)=makeNode(N_EXP_INT_CONST,NIL,(yyvsp[(1) - (1)]),NIL);}
    break;

  case 172:
#line 468 "yacc.y"
    {(yyval)=makeNode(N_EXP_FLOAT_CONST,NIL,(yyvsp[(1) - (1)]),NIL);}
    break;

  case 173:
#line 469 "yacc.y"
    {(yyval)=makeNode(N_EXP_CHAR_CONST,NIL,(yyvsp[(1) - (1)]),NIL);}
    break;

  case 174:
#line 470 "yacc.y"
    {(yyval)=makeNode(N_EXP_STRING_LITERAL,NIL,(yyvsp[(1) - (1)]),NIL);}
    break;

  case 175:
#line 471 "yacc.y"
    {(yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 176:
#line 476 "yacc.y"
    {(yyval)=setTypeNameSpecifier((yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]));}
    break;


/* Line 1267 of yacc.c.  */
#line 2658 "y.tab.c"
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


#line 479 "yacc.y"

extern char *yytext;

void print_current_id_list () {
	
	A_ID *id;
	id = current_id;
	printf("(current_id) ");
	while (id != NIL) {
		printf("%s > ", id -> name);
		id = id -> prev;
	}
	printf("NULL\n");
}

int yyerror(char *s) 
{
	printf("line %d: %s near %s \n", line_no, s, yytext);
	exit(1);
}

int yywrap()
{
	return(1);
}
