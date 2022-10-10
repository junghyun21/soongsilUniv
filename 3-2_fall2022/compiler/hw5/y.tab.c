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
     AND = 293,
     XOR = 294,
     OR = 295,
     QUEST = 296,
     PLUSPLUS = 297,
     WHILE_SYM = 298,
     UNION_SYM = 299,
     TYPEDEF_SYM = 300,
     SWITCH_SYM = 301,
     STRUCT_SYM = 302,
     STATIC_SYM = 303,
     SIZEOF_SYM = 304,
     RETURN_SYM = 305,
     IF_SYM = 306,
     FOR_SYM = 307,
     ENUM_SYM = 308,
     ELSE_SYM = 309,
     DO_SYM = 310,
     DEFAULT_SYM = 311,
     CONTINUE_SYM = 312,
     CASE_SYM = 313,
     BREAK_SYM = 314,
     AUTO_SYM = 315,
     GOTO_SYM = 316,
     REGISTER_SYM = 317,
     EXTERN_SYM = 318,
     CONST_SYM = 319,
     VOLATILE_SYM = 320
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
#define AND 293
#define XOR 294
#define OR 295
#define QUEST 296
#define PLUSPLUS 297
#define WHILE_SYM 298
#define UNION_SYM 299
#define TYPEDEF_SYM 300
#define SWITCH_SYM 301
#define STRUCT_SYM 302
#define STATIC_SYM 303
#define SIZEOF_SYM 304
#define RETURN_SYM 305
#define IF_SYM 306
#define FOR_SYM 307
#define ENUM_SYM 308
#define ELSE_SYM 309
#define DO_SYM 310
#define DEFAULT_SYM 311
#define CONTINUE_SYM 312
#define CASE_SYM 313
#define BREAK_SYM 314
#define AUTO_SYM 315
#define GOTO_SYM 316
#define REGISTER_SYM 317
#define EXTERN_SYM 318
#define CONST_SYM 319
#define VOLATILE_SYM 320




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

     #include <stdio.h>
     #include <stdlib.h>
     int line_no = 1;
     int yyerror(char *s);
     int yylex();
	 int current_level = 0; // 스코프 처리 규칙


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
#line 245 "y.tab.c"

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
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   568

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  163
/* YYNRULES -- Number of states.  */
#define YYNSTATES  286

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

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
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    18,    21,
      24,    28,    30,    32,    34,    37,    40,    43,    45,    47,
      49,    51,    53,    55,    57,    59,    61,    65,    67,    69,
      71,    77,    82,    85,    87,    89,    91,    94,    98,   100,
     102,   108,   113,   116,   118,   120,   125,   128,   130,   132,
     135,   137,   141,   146,   151,   152,   154,   155,   157,   159,
     161,   164,   167,   169,   171,   173,   176,   180,   184,   188,
     193,   198,   200,   204,   206,   210,   212,   214,   216,   218,
     220,   222,   227,   231,   235,   240,   241,   244,   245,   248,
     250,   253,   259,   267,   273,   279,   287,   297,   298,   300,
     304,   307,   310,   314,   316,   318,   320,   322,   324,   328,
     330,   335,   340,   344,   348,   351,   354,   355,   357,   359,
     361,   364,   367,   370,   373,   376,   379,   382,   385,   390,
     392,   397,   399,   402,   404,   408,   412,   416,   418,   422,
     426,   428,   432,   436,   440,   444,   446,   450,   454,   456,
     460,   462,   466,   468,   472,   474,   478,   480,   484,   486,
     492,   494,   496,   498
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      68,     0,    -1,    69,    -1,    70,    -1,    69,    70,    -1,
      71,    -1,    72,    -1,    73,    88,   102,    -1,    88,   102,
      -1,    73,    12,    -1,    73,    76,    12,    -1,    78,    -1,
      74,    -1,    75,    -1,    78,    73,    -1,    74,    73,    -1,
      75,    73,    -1,    60,    -1,    48,    -1,    45,    -1,    62,
      -1,    63,    -1,    64,    -1,    65,    -1,    77,    -1,    88,
      -1,    88,     9,    98,    -1,    79,    -1,    85,    -1,     4,
      -1,    80,     3,    22,    81,    21,    -1,    80,    22,    81,
      21,    -1,    80,     3,    -1,    47,    -1,    44,    -1,    82,
      -1,    81,    82,    -1,    78,    83,    12,    -1,    84,    -1,
      88,    -1,    53,     3,    22,    86,    21,    -1,    53,    22,
      86,    21,    -1,    53,     3,    -1,    87,    -1,     3,    -1,
       3,     9,   127,    12,    -1,    89,    90,    -1,    90,    -1,
      16,    -1,    16,    89,    -1,     3,    -1,    26,    88,    25,
      -1,    90,    24,    91,    23,    -1,    90,    26,    92,    25,
      -1,    -1,   127,    -1,    -1,    93,    -1,    94,    -1,    95,
      -1,    73,    88,    -1,    73,    96,    -1,    73,    -1,    89,
      -1,    97,    -1,    89,    97,    -1,    26,    96,    25,    -1,
      24,    91,    23,    -1,    26,    92,    25,    -1,    97,    24,
      91,    23,    -1,    97,    26,    92,    25,    -1,   127,    -1,
      22,    99,    21,    -1,    98,    -1,    99,    18,    98,    -1,
     101,    -1,   102,    -1,   105,    -1,   106,    -1,   107,    -1,
     109,    -1,    58,   127,    20,   100,    -1,    56,    20,   100,
      -1,     3,    20,   100,    -1,    22,   103,   104,    21,    -1,
      -1,   103,    72,    -1,    -1,   104,   100,    -1,    12,    -1,
     128,    12,    -1,    51,    26,   128,    25,   100,    -1,    51,
      26,   128,    25,   100,    54,   100,    -1,    46,    26,   128,
      25,   100,    -1,    43,    26,   128,    25,   100,    -1,    55,
     100,    43,    26,   128,    25,    12,    -1,    52,    26,   108,
      12,   108,    12,   108,    25,   100,    -1,    -1,   128,    -1,
      50,   108,    12,    -1,    57,    12,    -1,    59,    12,    -1,
      61,     3,    12,    -1,     3,    -1,     8,    -1,     7,    -1,
       5,    -1,     6,    -1,    26,   128,    25,    -1,   110,    -1,
     111,    24,   128,    23,    -1,   111,    26,   112,    25,    -1,
     111,    19,     3,    -1,   111,    36,     3,    -1,   111,    42,
      -1,   111,    37,    -1,    -1,   113,    -1,   129,    -1,   111,
      -1,    42,   114,    -1,    37,   114,    -1,    13,   115,    -1,
      16,   115,    -1,    17,   115,    -1,    10,   115,    -1,    11,
     115,    -1,    49,   114,    -1,    49,    26,   116,    25,    -1,
     114,    -1,    26,   116,    25,   115,    -1,    73,    -1,    73,
      96,    -1,   115,    -1,   117,    16,   115,    -1,   117,    15,
     115,    -1,   117,    14,   115,    -1,   117,    -1,   118,    11,
     117,    -1,   118,    10,   117,    -1,   118,    -1,   119,    35,
     118,    -1,   119,    34,   118,    -1,   119,    33,   118,    -1,
     119,    32,   118,    -1,   119,    -1,   120,    31,   119,    -1,
     120,    30,   119,    -1,   120,    -1,   121,    38,   120,    -1,
     121,    -1,   122,    39,   121,    -1,   122,    -1,   123,    40,
     122,    -1,   123,    -1,   124,    29,   123,    -1,   124,    -1,
     125,    28,   124,    -1,   125,    -1,   125,    41,   128,    20,
     126,    -1,   128,    -1,   129,    -1,   126,    -1,   114,     9,
     129,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    24,    24,    28,    29,    33,    34,    38,    39,    43,
      44,    48,    49,    50,    51,    52,    53,    57,    58,    59,
      60,    61,    65,    66,    70,    74,    75,    79,    80,    81,
      85,    86,    87,    91,    92,    96,    97,   101,   105,   109,
     113,   114,   115,   119,   123,   124,   128,   129,   133,   134,
     138,   139,   140,   141,   144,   146,   149,   151,   155,   159,
     163,   164,   165,   169,   170,   171,   175,   176,   177,   178,
     179,   183,   184,   188,   189,   193,   194,   195,   196,   197,
     198,   202,   203,   204,   208,   211,   213,   216,   218,   222,
     223,   227,   228,   229,   233,   234,   235,   238,   240,   244,
     245,   246,   247,   251,   252,   253,   254,   255,   256,   260,
     261,   262,   263,   264,   265,   266,   269,   271,   275,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   292,
     293,   297,   298,   302,   303,   304,   305,   309,   310,   311,
     315,   316,   317,   318,   319,   323,   324,   325,   329,   330,
     334,   335,   339,   340,   344,   345,   349,   350,   354,   355,
     359,   363,   367,   368
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
  "EQL", "GEQ", "LEQ", "GTR", "LSS", "ARROW", "MINUSMINUS", "AND", "XOR",
  "OR", "QUEST", "PLUSPLUS", "WHILE_SYM", "UNION_SYM", "TYPEDEF_SYM",
  "SWITCH_SYM", "STRUCT_SYM", "STATIC_SYM", "SIZEOF_SYM", "RETURN_SYM",
  "IF_SYM", "FOR_SYM", "ENUM_SYM", "ELSE_SYM", "DO_SYM", "DEFAULT_SYM",
  "CONTINUE_SYM", "CASE_SYM", "BREAK_SYM", "AUTO_SYM", "GOTO_SYM",
  "REGISTER_SYM", "EXTERN_SYM", "CONST_SYM", "VOLATILE_SYM", "\"then\"",
  "$accept", "program", "translate_unit", "external_declaration",
  "function_definition", "declaration", "declaration_specifiers",
  "storage_class_specifier", "type_qualifier", "init_declarator_list",
  "init_declarator", "type_specifier", "struct_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "declarator", "pointer",
  "direct_declarator", "constant_expression_opt",
  "parameter_type_list_opt", "parameter_type_list", "parameter_list",
  "parameter_declaration", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "statement", "labeled_statement", "compound_statement",
  "declaration_list", "statement_list", "expression_statement",
  "selection_statement", "iteration_statement", "expression_opt",
  "jump_statement", "primary_expression", "postfix_expression",
  "arg_expression_list_opt", "arg_expression_list", "unary_expression",
  "cast_expression", "type_name", "multiplicative_expression",
  "additive_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "constant_expression", "expression",
  "assignment_expression", 0
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
     315,   316,   317,   318,   319,   320,   321
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    76,    77,    77,    78,    78,    78,
      79,    79,    79,    80,    80,    81,    81,    82,    83,    84,
      85,    85,    85,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    92,    93,    94,
      95,    95,    95,    96,    96,    96,    97,    97,    97,    97,
      97,    98,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   102,   103,   103,   104,   104,   105,
     105,   106,   106,   106,   107,   107,   107,   108,   108,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   112,   112,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   115,
     115,   116,   116,   117,   117,   117,   117,   118,   118,   118,
     119,   119,   119,   119,   119,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   128,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     2,
       3,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       5,     4,     2,     1,     1,     1,     2,     3,     1,     1,
       5,     4,     2,     1,     1,     4,     2,     1,     1,     2,
       1,     3,     4,     4,     0,     1,     0,     1,     1,     1,
       2,     2,     1,     1,     1,     2,     3,     3,     3,     4,
       4,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     4,     3,     3,     4,     0,     2,     0,     2,     1,
       2,     5,     7,     5,     5,     7,     9,     0,     1,     3,
       2,     2,     3,     1,     1,     1,     1,     1,     3,     1,
       4,     4,     3,     3,     2,     2,     0,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     1,
       4,     1,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    50,    29,    48,     0,    34,    19,    33,    18,     0,
      17,    20,    21,    22,    23,     0,     2,     3,     5,     6,
       0,    12,    13,    11,    27,     0,    28,     0,     0,    47,
      49,     0,    42,     0,     1,     4,     9,     0,    24,    25,
      15,    16,    14,    32,     0,    85,     8,    46,    54,    56,
      51,     0,    44,     0,    43,    10,     0,     7,     0,     0,
       0,    35,    87,   103,   106,   107,   105,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   119,
     129,   133,   137,   140,   145,   148,   150,   152,   154,   156,
     158,   162,    55,   160,   161,    62,     0,    57,    58,    59,
       0,     0,    41,     0,    26,    71,     0,     0,    38,    39,
      31,    36,    86,     0,     0,   129,   125,   126,   122,   123,
     124,   131,     0,     0,     0,   121,   120,     0,   127,    52,
       0,     0,   116,     0,   115,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    56,    60,    63,    61,    64,
      53,    40,     0,    73,     0,    30,    37,    25,   103,    89,
      84,     0,     0,    97,     0,     0,     0,     0,     0,     0,
       0,     0,    88,    75,    76,    77,    78,    79,    80,     0,
      56,    63,   132,     0,   108,     0,   112,     0,     0,   117,
     118,   113,   163,   136,   135,   134,   139,   138,   144,   143,
     142,   141,   147,   146,   149,   151,   153,   155,   157,     0,
       0,     0,     0,    65,    54,    56,    45,     0,    72,     0,
       0,     0,     0,    98,     0,    97,     0,     0,   100,     0,
     101,     0,    90,   130,   128,   110,   111,     0,    67,    68,
      66,     0,     0,    74,    83,     0,     0,    99,     0,     0,
       0,    82,     0,   102,   159,    69,    70,     0,     0,     0,
      97,     0,    81,    94,    93,    91,     0,     0,     0,    97,
       0,    92,     0,    95,     0,    96
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    17,    18,    19,    95,    21,    22,    37,
      38,    23,    24,    25,    60,    61,   107,   108,    26,    53,
      54,    27,    28,    29,    77,   221,    97,    98,    99,   222,
     159,   104,   164,   182,   183,   184,    62,   114,   185,   186,
     187,   232,   188,    78,    79,   198,   199,    80,    81,   122,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   189,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -222
static const yytype_int16 yypact[] =
{
     222,  -222,  -222,   -10,    85,  -222,  -222,  -222,  -222,    14,
    -222,  -222,  -222,  -222,  -222,    44,   222,  -222,  -222,  -222,
      78,   275,   275,   275,  -222,    15,  -222,    12,    16,   171,
    -222,    13,    35,    79,  -222,  -222,  -222,    75,  -222,    34,
    -222,  -222,  -222,    74,     7,  -222,  -222,   171,   474,   275,
    -222,    79,    94,   106,  -222,  -222,   452,  -222,     7,    85,
      31,  -222,   275,  -222,  -222,  -222,  -222,  -222,   474,   474,
     474,   474,   474,   154,   502,   502,   519,   129,  -222,   221,
     147,  -222,   107,    52,    82,    61,   135,   138,   150,   165,
     -19,  -222,  -222,  -222,  -222,   257,   175,  -222,  -222,  -222,
     191,   474,  -222,   452,  -222,  -222,   128,   208,  -222,  -222,
    -222,  -222,  -222,    78,   338,  -222,  -222,  -222,  -222,  -222,
    -222,   104,   196,   199,   474,  -222,  -222,   154,  -222,  -222,
     225,   474,   474,   227,  -222,  -222,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   189,  -222,    86,  -222,   180,
    -222,  -222,   220,  -222,   145,  -222,  -222,   226,   219,  -222,
    -222,   215,   218,   474,   224,   229,   395,   239,   234,   474,
     249,   259,  -222,  -222,  -222,  -222,  -222,  -222,  -222,   253,
     252,   203,  -222,   474,  -222,   246,  -222,   241,   247,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,   107,   107,    52,    52,
      52,    52,    82,    82,    61,   135,   138,   150,   165,   254,
     265,   255,   264,   180,   474,   275,  -222,   452,  -222,   395,
     474,   474,   278,  -222,   474,   474,   248,   395,  -222,   272,
    -222,   281,  -222,  -222,  -222,  -222,  -222,   474,  -222,  -222,
    -222,   271,   270,  -222,  -222,   273,   276,  -222,   277,   291,
     251,  -222,   395,  -222,  -222,  -222,  -222,   395,   395,   395,
     474,   474,  -222,  -222,  -222,   250,   294,   282,   395,   474,
     296,  -222,   284,  -222,   395,  -222
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -222,  -222,  -222,   295,  -222,   256,    24,  -222,  -222,  -222,
    -222,   -32,  -222,  -222,   263,   -45,  -222,  -222,  -222,   262,
    -222,     0,    -2,    -7,  -144,   -47,  -222,  -222,  -222,   -82,
    -150,   -98,  -222,  -160,  -222,    46,  -222,  -222,  -222,  -222,
    -222,  -221,  -222,  -222,  -222,  -222,  -222,    -4,   -39,   183,
      28,    66,    38,   176,   177,   179,   174,   178,  -222,    80,
     -53,   -48,  -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      93,    30,    96,   105,    31,   163,     3,   223,    93,   152,
     220,     2,    59,   158,   259,   111,   236,    32,    43,     1,
      39,    47,   153,   200,    20,   123,    59,   202,    59,   116,
     117,   118,   119,   120,    45,     2,    33,    44,    50,   192,
      20,   223,     4,    56,    34,    40,    41,    42,   162,   276,
     105,     5,   110,    93,     7,    93,    45,    51,   282,   109,
       9,   111,   140,   141,   115,   115,   115,   115,   115,   254,
     125,   126,   128,    46,    59,     5,   123,   261,     7,   123,
     251,     1,    52,   197,     9,    57,   113,    55,     1,     1,
      36,   146,   147,   157,     3,   156,    58,   121,   203,   204,
     205,     3,   272,   101,     4,   219,    93,   273,   274,   275,
     154,     4,   155,   167,   142,   143,   144,   145,   281,   191,
       3,   137,   138,   139,   285,   233,   239,   102,   154,   253,
     190,    93,     2,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   165,
      47,   121,   129,   157,   243,    31,   136,    63,     2,    64,
      65,    66,    67,   227,    68,    69,   228,    70,   206,   207,
      71,    72,     5,   148,   105,     7,    93,   149,   252,    93,
      73,     9,   255,   256,   212,   213,   258,   233,   191,   115,
     150,    74,     1,     2,   151,    48,    75,    49,     5,     6,
     160,     7,     8,    76,   224,     3,   225,     9,   208,   209,
     210,   211,   161,   154,    10,   155,    11,    12,    13,    14,
     166,   193,   233,   277,   194,     1,     2,   154,   196,   190,
     201,   233,   226,     5,     6,    56,     7,     8,     3,   229,
     130,   230,     9,   115,   231,   131,   238,   132,     4,    10,
     234,    11,    12,    13,    14,   235,     2,   133,   134,   237,
       1,   240,   241,   135,   245,   242,     5,     6,     3,     7,
       8,   244,   246,     3,   247,     9,   154,   271,   190,     2,
     249,   154,    10,   155,    11,    12,    13,    14,   248,   250,
     257,   260,   262,   263,   265,   266,     5,     6,   267,     7,
       8,   268,   269,   270,   278,     9,   279,   280,   283,   284,
     195,    35,    10,   100,    11,    12,    13,    14,   112,     5,
       6,   106,     7,     8,   214,   217,   215,   264,     9,   216,
     218,     0,     0,     0,     0,    10,     0,    11,    12,    13,
      14,   168,     0,    64,    65,    66,    67,     0,    68,    69,
     169,    70,     0,     0,    71,    72,     0,     0,     0,   170,
      45,     0,     0,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    74,     0,     0,     0,     0,
      75,   171,     0,     0,   172,     0,     0,    76,   173,   174,
     175,     0,     0,   176,   177,   178,   179,   180,   168,   181,
      64,    65,    66,    67,     0,    68,    69,   169,    70,     0,
       0,    71,    72,     0,     0,     0,     0,    45,     0,     0,
       0,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    74,     0,     0,     0,     0,    75,   171,     0,
       0,   172,     0,     0,    76,   173,   174,   175,     0,     0,
     176,   177,   178,   179,   180,    63,   181,    64,    65,    66,
      67,     0,    68,    69,     0,    70,     0,     0,    71,    72,
       0,     0,     0,     0,   103,     0,     0,    63,    73,    64,
      65,    66,    67,     0,    68,    69,     0,    70,     0,    74,
      71,    72,     0,     0,    75,     0,     0,     0,     0,     0,
      73,    76,     0,     0,     0,    63,     0,    64,    65,    66,
      67,    74,    68,    69,     0,    70,    75,     0,    71,    72,
       0,     0,    63,    76,    64,    65,    66,    67,   124,    68,
      69,     0,    70,     0,     0,    71,    72,     0,     0,    74,
       0,     0,     0,     0,    75,   127,     0,     0,     0,     0,
       0,    76,     0,     0,     0,     0,    74,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,    76
};

static const yytype_int16 yycheck[] =
{
      48,     3,    49,    56,     4,   103,    16,   157,    56,    28,
     154,     4,    44,    95,   235,    60,   176,     3,     3,     3,
      20,    28,    41,   132,     0,    73,    58,   136,    60,    68,
      69,    70,    71,    72,    22,     4,    22,    22,    25,   121,
      16,   191,    26,     9,     0,    21,    22,    23,   101,   270,
     103,    44,    21,   101,    47,   103,    22,    22,   279,    59,
      53,   106,    10,    11,    68,    69,    70,    71,    72,   229,
      74,    75,    76,    27,   106,    44,   124,   237,    47,   127,
     224,     3,     3,   131,    53,    39,    62,    12,     3,     3,
      12,    30,    31,    95,    16,    95,    22,    73,   137,   138,
     139,    16,   262,     9,    26,   153,   154,   267,   268,   269,
      24,    26,    26,   113,    32,    33,    34,    35,   278,   121,
      16,    14,    15,    16,   284,   173,   179,    21,    24,   227,
      26,   179,     4,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,    21,
     157,   127,    23,   155,   193,   155,     9,     3,     4,     5,
       6,     7,     8,    18,    10,    11,    21,    13,   140,   141,
      16,    17,    44,    38,   227,    47,   224,    39,   225,   227,
      26,    53,   230,   231,   146,   147,   234,   235,   190,   193,
      40,    37,     3,     4,    29,    24,    42,    26,    44,    45,
      25,    47,    48,    49,    24,    16,    26,    53,   142,   143,
     144,   145,    21,    24,    60,    26,    62,    63,    64,    65,
      12,    25,   270,   271,    25,     3,     4,    24,     3,    26,
       3,   279,    12,    44,    45,     9,    47,    48,    16,    20,
      19,    26,    53,   247,    26,    24,    12,    26,    26,    60,
      26,    62,    63,    64,    65,    26,     4,    36,    37,    20,
       3,    12,     3,    42,    23,    12,    44,    45,    16,    47,
      48,    25,    25,    16,    20,    53,    24,    26,    26,     4,
      25,    24,    60,    26,    62,    63,    64,    65,    23,    25,
      12,    43,    20,    12,    23,    25,    44,    45,    25,    47,
      48,    25,    25,    12,    54,    53,    12,    25,    12,    25,
     127,    16,    60,    51,    62,    63,    64,    65,    62,    44,
      45,    58,    47,    48,   148,   151,   149,   247,    53,   150,
     152,    -1,    -1,    -1,    -1,    60,    -1,    62,    63,    64,
      65,     3,    -1,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    -1,    -1,    55,    56,    57,    58,    59,     3,    61,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    59,     3,    61,     5,     6,     7,
       8,    -1,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,     3,    26,     5,
       6,     7,     8,    -1,    10,    11,    -1,    13,    -1,    37,
      16,    17,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      26,    49,    -1,    -1,    -1,     3,    -1,     5,     6,     7,
       8,    37,    10,    11,    -1,    13,    42,    -1,    16,    17,
      -1,    -1,     3,    49,     5,     6,     7,     8,    26,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    42,    26,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    16,    26,    44,    45,    47,    48,    53,
      60,    62,    63,    64,    65,    68,    69,    70,    71,    72,
      73,    74,    75,    78,    79,    80,    85,    88,    89,    90,
      89,    88,     3,    22,     0,    70,    12,    76,    77,    88,
      73,    73,    73,     3,    22,    22,   102,    90,    24,    26,
      25,    22,     3,    86,    87,    12,     9,   102,    22,    78,
      81,    82,   103,     3,     5,     6,     7,     8,    10,    11,
      13,    16,    17,    26,    37,    42,    49,    91,   110,   111,
     114,   115,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    73,    92,    93,    94,    95,
      86,     9,    21,    22,    98,   127,    81,    83,    84,    88,
      21,    82,    72,    73,   104,   114,   115,   115,   115,   115,
     115,    73,   116,   128,    26,   114,   114,    26,   114,    23,
      19,    24,    26,    36,    37,    42,     9,    14,    15,    16,
      10,    11,    32,    33,    34,    35,    30,    31,    38,    39,
      40,    29,    28,    41,    24,    26,    88,    89,    96,    97,
      25,    21,   127,    98,    99,    21,    12,    88,     3,    12,
      21,    43,    46,    50,    51,    52,    55,    56,    57,    58,
      59,    61,   100,   101,   102,   105,   106,   107,   109,   128,
      26,    89,    96,    25,    25,   116,     3,   128,   112,   113,
     129,     3,   129,   115,   115,   115,   117,   117,   118,   118,
     118,   118,   119,   119,   120,   121,   122,   123,   124,   128,
      91,    92,    96,    97,    24,    26,    12,    18,    21,    20,
      26,    26,   108,   128,    26,    26,   100,    20,    12,   127,
      12,     3,    12,   115,    25,    23,    25,    20,    23,    25,
      25,    91,    92,    98,   100,   128,   128,    12,   128,   108,
      43,   100,    20,    12,   126,    23,    25,    25,    25,    25,
      12,    26,   100,   100,   100,   100,   108,   128,    54,    12,
      25,   100,   108,    12,    25,   100
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
      
/* Line 1267 of yacc.c.  */
#line 1790 "y.tab.c"
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


#line 370 "yacc.y"

extern char *yytext;

int yyerror(char *s) 
{
     printf("line %d: %s near %s \n", line_no, s, yytext);
     exit(1);
}

int main()
{
     yyparse();
     printf("검사 완료\n");
}

int yywrap()
{
     return(1);
}

