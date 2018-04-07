
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     KW_CLASS = 258,
     KW_MODULE = 259,
     KW_GAME = 260,
     KW_INT = 261,
     KW_DEF = 262,
     KW_DO = 263,
     KW_WHILE = 264,
     KW_NEW = 265,
     KW_THIS = 266,
     KW_DELETE = 267,
     KW_STRING = 268,
     KW_REAL = 269,
     KW_IF = 270,
     KW_ELSE = 271,
     KW_RETURN = 272,
     KW_FOR = 273,
     KW_PUBLIC = 274,
     KW_VIRTUAL = 275,
     KW_MATCH = 276,
     NM_STRING = 277,
     NM_INT = 278,
     NM_REAL = 279,
     IDENTIFIER = 280,
     IDENTTAB = 281,
     KW_FUNC = 282,
     BH_E = 283,
     BH_NE = 284,
     BH_ANDAND = 285,
     BH_OROR = 286,
     BH_AE = 287,
     BH_PP = 288,
     BH_MM = 289,
     BH_LE = 290,
     BH_PE = 291,
     BH_MNE = 292,
     BH_MLE = 293,
     BH_DE = 294,
     BH_MDE = 295,
     BH_CP = 296,
     KW_OPERATOR = 297,
     OPP = 298,
     OPM = 299,
     OPMU = 300,
     OPD = 301,
     OPMO = 302,
     OPE = 303,
     OPEQ = 304,
     OPNE = 305,
     OPAE = 306,
     OPLE = 307,
     OPA = 308,
     OPL = 309,
     OPSET = 310,
     OPPOINTER = 311,
     OPPP = 312,
     OPMM = 313,
     NEG = 314
   };
#endif
/* Tokens.  */
#define KW_CLASS 258
#define KW_MODULE 259
#define KW_GAME 260
#define KW_INT 261
#define KW_DEF 262
#define KW_DO 263
#define KW_WHILE 264
#define KW_NEW 265
#define KW_THIS 266
#define KW_DELETE 267
#define KW_STRING 268
#define KW_REAL 269
#define KW_IF 270
#define KW_ELSE 271
#define KW_RETURN 272
#define KW_FOR 273
#define KW_PUBLIC 274
#define KW_VIRTUAL 275
#define KW_MATCH 276
#define NM_STRING 277
#define NM_INT 278
#define NM_REAL 279
#define IDENTIFIER 280
#define IDENTTAB 281
#define KW_FUNC 282
#define BH_E 283
#define BH_NE 284
#define BH_ANDAND 285
#define BH_OROR 286
#define BH_AE 287
#define BH_PP 288
#define BH_MM 289
#define BH_LE 290
#define BH_PE 291
#define BH_MNE 292
#define BH_MLE 293
#define BH_DE 294
#define BH_MDE 295
#define BH_CP 296
#define KW_OPERATOR 297
#define OPP 298
#define OPM 299
#define OPMU 300
#define OPD 301
#define OPMO 302
#define OPE 303
#define OPEQ 304
#define OPNE 305
#define OPAE 306
#define OPLE 307
#define OPA 308
#define OPL 309
#define OPSET 310
#define OPPOINTER 311
#define OPPP 312
#define OPMM 313
#define NEG 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 98 "dpars4.y"

    char s[1024];



/* Line 1676 of yacc.c  */
#line 176 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


