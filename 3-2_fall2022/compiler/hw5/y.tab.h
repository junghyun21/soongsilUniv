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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

