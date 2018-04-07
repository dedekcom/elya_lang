
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 1 "dpars4.y"

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include "lex.yy.c"
  #define YYDEBUG 1
 
 FILE *fin;
 int idkod = -1;
 int ilambdas = -1;
 int iglobalambda = -1;
 void preparevars();
 #define ILEKOD	100
 char *skod[ILEKOD];
 int ilekod[ILEKOD], ilimkod[ILEKOD], ikodprev[ILEKOD];
 char *beginkod();
 void endkod();
 void printkod();
 char sclassname[256], scallmethod[256];
 #define ILELOCAL	100
 #define ILESTACK	100
 #define IDNAME		128
 #define ILEATTR		100
 int ioptimized = 1;
 int idlocal[ILEKOD];		// licznik zmiennych lokalnych
 int ktorylocal[ILEKOD];
 void zerujlocals();
 int iloctab=0;
 int idstack=0;
 int ilecalls = 0;	// ilosc elementow do (x,y,z..) = ...
 void printlocals();
 char sav[ILESTACK][IDNAME],	// do zapamietywania
 	local[ILELOCAL][IDNAME][ILEKOD],	// tablica zmiennych lokalnych
 	sattr[ILEATTR][IDNAME];
 char sloc[20];		// obliczona nazwa zmiennej lokalnej
 char sclass[20];		// nazwa typu: class, module, game
 void dderror(char *s1, char *s2)	{ printf("error: %s%s",s1,s2); exit(1);	}
 void addlocal(char *s);
 void addrellocal(char *styp, char *s);
 void addlocarray( char *styp, char *snom, char *sile );
 char *getlocal(char *s);
 void ddpush(char *s)	{ strcpy(sav[idstack],s); idstack++; }
 char sbuild[2048], spom[2048];
 char sident[IDNAME][ILEKOD], sidentr[IDNAME][ILEKOD];
 void prepare()	{ strcpy(sbuild,""); }
 void prebuild(char *s)	{ strcpy(spom,sbuild);  strcpy(sbuild,s);  strcat(sbuild,spom); }
 void build(char *s)	{ strcat(sbuild,s); }
 void build2(char *s1, char *s2)	{ build(s1); build(s2); }
 void build3(char *s1, char *s2, char *s3) { build2(s1,s2); build(s3); }
 void pushbuild()	{ ddpush(sbuild); prepare(); }
 char *ddpop()	{ idstack--; if(idstack>=0) return sav[idstack]; else dderror("idstack<","0");  }
 void popbuild()	{ strcpy(sbuild,ddpop()); } 
 void ddstart(char *filename);
 void ddend();
 void ddput(char *s);
 void ddput2(char *s1, char *s2); 
 void ddput3(char *s1, char *s2, char *s3); 
 void putbuild()	{ ddput(ddpop()); } 
 void expr(char *s)	{ ddput3("\tpop $b\n\tpopax\n\t",s," $a,$b\n"); }
 void qexpr(char *sinstr, char *svar);		// quick expression
 void sexpr(char *sinstr);				// slow expression
 char *lastlocal();
 int ilastlocal=0;
 char *localname(int pos);
 void stdnew();
 void qifexp1();
 void qifexp2();
 void qifexp3();
 void argexpr();
 void calloper(char *c);
 
 void insertattr(char *c);
 void putattr();
 
 int loopc=0;		// licznik petli (do budowy)
 int lstack=-1;	// pobor petli 
 char *pushloop();
 char *poploop();
 char *lastloop();
 char *getloop(int id);
 #define ILELOOPS	10000
 char sloop[ILELOOPS][10];
 void cmp(char *s);
 void neg();
 void checkand();
 void checkor();
 void endandor();
 void ifpart1();
 void ifpart2();
 void ifpart3();
 void startloop();
 
 void matchbody();
 void matchlist();
 void endclass();


/* Line 189 of yacc.c  */
#line 171 "y.tab.c"

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

/* Line 214 of yacc.c  */
#line 98 "dpars4.y"

    char s[1024];



/* Line 214 of yacc.c  */
#line 331 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 343 "y.tab.c"

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
# if YYENABLE_NLS
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  139
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  108
/* YYNRULES -- Number of rules.  */
#define YYNRULES  280
/* YYNRULES -- Number of states.  */
#define YYNSTATES  459

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,     2,     2,     2,    67,    61,     2,
      74,    75,    65,    64,    70,    63,    83,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    78,
      59,    73,    60,    79,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,    84,    77,     2,    81,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    62,    72,     2,     2,     2,     2,
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
      55,    56,    57,    58,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    13,    15,    17,    19,
      21,    25,    27,    29,    33,    35,    39,    41,    45,    48,
      51,    53,    55,    58,    61,    64,    67,    70,    73,    76,
      79,    82,    85,    88,    91,    94,    97,   100,   102,   105,
     109,   112,   116,   119,   122,   124,   127,   131,   134,   136,
     140,   143,   149,   153,   156,   158,   161,   163,   165,   167,
     169,   172,   175,   177,   180,   182,   185,   187,   189,   195,
     196,   201,   203,   206,   207,   213,   216,   219,   221,   223,
     226,   229,   232,   236,   240,   243,   249,   251,   254,   256,
     259,   261,   264,   266,   269,   272,   274,   276,   279,   281,
     284,   286,   290,   293,   295,   298,   300,   304,   306,   310,
     313,   315,   319,   321,   324,   328,   332,   337,   338,   345,
     346,   347,   357,   360,   363,   365,   367,   369,   371,   373,
     375,   377,   379,   381,   383,   387,   390,   393,   396,   399,
     403,   407,   411,   415,   419,   422,   425,   429,   433,   437,
     441,   445,   451,   455,   459,   462,   465,   468,   471,   475,
     479,   482,   485,   488,   491,   494,   497,   502,   506,   508,
     510,   512,   518,   520,   522,   524,   526,   529,   532,   534,
     536,   539,   542,   544,   548,   552,   556,   560,   564,   568,
     572,   576,   580,   584,   588,   592,   596,   599,   602,   606,
     610,   614,   618,   622,   626,   630,   634,   638,   642,   646,
     650,   654,   658,   661,   664,   667,   669,   673,   677,   681,
     685,   689,   693,   697,   700,   704,   708,   711,   713,   715,
     717,   719,   721,   723,   725,   727,   729,   731,   733,   735,
     738,   740,   743,   745,   747,   749,   753,   758,   764,   769,
     774,   776,   778,   782,   784,   788,   789,   793,   795,   798,
     800,   803,   806,   808,   812,   816,   818,   820,   822,   824,
     826,   830,   832,   836,   839,   841,   845,   847,   849,   851,
     853
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      86,     0,    -1,    86,    87,    -1,    87,    -1,    89,    -1,
      19,    99,    -1,   105,    -1,     3,    -1,     5,    -1,     4,
      -1,    88,    91,    94,    -1,    25,    -1,    90,    -1,    90,
      69,    93,    -1,    25,    -1,    92,    70,    93,    -1,    92,
      -1,    71,    95,    72,    -1,    71,    72,    -1,    95,    99,
      -1,    99,    -1,    25,    -1,    25,    73,    -1,    42,    64,
      -1,    42,    63,    -1,    42,    65,    -1,    42,    66,    -1,
      42,    67,    -1,    42,    73,    -1,    42,    28,    -1,    42,
      29,    -1,    42,    59,    -1,    42,    60,    -1,    42,    35,
      -1,    42,    32,    -1,    42,    33,    -1,    42,    34,    -1,
      96,    -1,   147,    96,    -1,    19,   147,    96,    -1,    19,
      96,    -1,    20,   147,    96,    -1,    20,    96,    -1,    97,
     100,    -1,    97,    -1,    98,   103,    -1,    74,   101,    75,
      -1,    74,    75,    -1,   102,    -1,   102,    70,   101,    -1,
     147,    25,    -1,   147,    25,    76,    23,    77,    -1,    71,
     104,    72,    -1,    71,    72,    -1,    78,    -1,   104,   105,
      -1,   105,    -1,   133,    -1,   127,    -1,   119,    -1,   149,
      78,    -1,   159,    78,    -1,   140,    -1,   144,    78,    -1,
     118,    -1,   129,    78,    -1,   103,    -1,   117,    -1,    21,
      74,   159,    75,    71,    -1,    -1,   159,    70,   108,   107,
      -1,   159,    -1,   159,    55,    -1,    -1,   159,    70,   110,
     107,    55,    -1,   109,   113,    -1,   111,   112,    -1,   111,
      -1,   105,    -1,    79,    55,    -1,   114,   113,    -1,   115,
      72,    -1,   106,   112,   116,    -1,    17,   189,    78,    -1,
      17,    78,    -1,    18,   120,   122,   124,   105,    -1,   121,
      -1,    74,   149,    -1,    74,    -1,    74,   129,    -1,   123,
      -1,    78,   159,    -1,    78,    -1,    78,   125,    -1,   149,
      75,    -1,    75,    -1,     9,    -1,   126,   136,    -1,   102,
      -1,   102,   130,    -1,   128,    -1,   128,    70,   129,    -1,
      73,   159,    -1,    15,    -1,   131,   136,    -1,   132,    -1,
     132,   134,   105,    -1,    16,    -1,    74,   159,    75,    -1,
     135,   105,    -1,    10,    -1,   137,   146,   145,    -1,   138,
      -1,   139,    78,    -1,   138,   188,    78,    -1,   139,   130,
      78,    -1,   139,    48,   159,    78,    -1,    -1,   139,    71,
     141,   104,    72,    78,    -1,    -1,    -1,   138,   188,    71,
     142,   100,   143,   104,    72,    78,    -1,    12,    25,    -1,
      12,   185,    -1,   185,    -1,    25,    -1,   185,    -1,    25,
      -1,   147,    -1,     6,    -1,    14,    -1,    13,    -1,     7,
      -1,    80,    -1,    76,   159,    77,    -1,   190,   130,    -1,
     185,   130,    -1,   190,    33,    -1,   190,    34,    -1,   190,
      36,   159,    -1,   190,    37,   159,    -1,   190,    38,   159,
      -1,   190,    39,   159,    -1,   190,    40,   159,    -1,   185,
      33,    -1,   185,    34,    -1,   185,    36,   159,    -1,   185,
      37,   159,    -1,   185,    38,   159,    -1,   185,    39,   159,
      -1,   185,    40,   159,    -1,    62,   187,    62,    73,   189,
      -1,   185,    48,   159,    -1,   190,    48,   159,    -1,   185,
      57,    -1,   190,    57,    -1,   185,    58,    -1,   190,    58,
      -1,    81,    73,   159,    -1,    11,    48,   159,    -1,    11,
      57,    -1,    11,    58,    -1,   154,    31,    -1,   154,    30,
      -1,   154,    31,    -1,   154,    30,    -1,    82,    74,   160,
      75,    -1,    74,   160,    75,    -1,   163,    -1,    79,    -1,
      69,    -1,   158,   155,   159,   156,   159,    -1,   160,    -1,
     154,    -1,   158,    -1,   157,    -1,   152,   161,    -1,   153,
     161,    -1,   154,    -1,   162,    -1,   151,   161,    -1,   150,
     161,    -1,   168,    -1,   163,    64,   163,    -1,   163,    63,
     163,    -1,   163,    65,   163,    -1,   163,    66,   163,    -1,
     163,    67,   163,    -1,   163,    61,   163,    -1,   163,    62,
     163,    -1,   163,    28,   163,    -1,   163,    29,   163,    -1,
     163,    32,   163,    -1,   163,    35,   163,    -1,   163,    59,
     163,    -1,   163,    60,   163,    -1,    63,   163,    -1,    82,
     163,    -1,    74,   163,    75,    -1,    74,   157,    75,    -1,
     163,    43,   163,    -1,   163,    44,   163,    -1,   163,    45,
     163,    -1,   163,    46,   163,    -1,   163,    47,   163,    -1,
     163,    49,   163,    -1,   163,    50,   163,    -1,   163,    51,
     163,    -1,   163,    52,   163,    -1,   163,    53,   163,    -1,
     163,    54,   163,    -1,   164,    25,   188,    -1,   164,    25,
      -1,   163,    56,    -1,   166,    56,    -1,   168,    -1,   166,
      64,   166,    -1,   166,    63,   166,    -1,   166,    65,   166,
      -1,   166,    66,   166,    -1,   166,    67,   166,    -1,   166,
      61,   166,    -1,   166,    62,   166,    -1,    63,   166,    -1,
      74,   166,    75,    -1,   165,    25,   188,    -1,   165,    25,
      -1,    23,    -1,    24,    -1,    22,    -1,   192,    -1,   167,
      -1,   169,    -1,    81,    -1,   170,    -1,   177,    -1,   181,
      -1,   179,    -1,    71,    -1,   171,   100,    -1,    71,    -1,
     173,   100,    -1,    25,    -1,   185,    -1,    27,    -1,   175,
      83,   184,    -1,   175,   171,   104,    72,    -1,   175,   188,
     172,   104,    72,    -1,   176,   173,   104,    72,    -1,   176,
     174,   104,    72,    -1,    25,    -1,   185,    -1,   178,    41,
     184,    -1,    11,    -1,   180,    83,   184,    -1,    -1,    83,
     182,   184,    -1,    25,    -1,    25,    73,    -1,   185,    -1,
     185,    73,    -1,   183,   188,    -1,   183,    -1,    59,   166,
      60,    -1,    84,   159,    84,    -1,   148,    -1,   190,    -1,
     139,    -1,   102,    -1,    81,    -1,   186,    70,   187,    -1,
     186,    -1,    74,   189,    75,    -1,    74,    75,    -1,   159,
      -1,   159,    70,   189,    -1,    25,    -1,    25,    -1,   191,
      -1,   148,    -1,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   122,   122,   123,   126,   127,   128,   131,   132,   133,
     136,   139,   142,   143,   146,   149,   150,   153,   154,   157,
     158,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   179,   180,   181,
     182,   183,   184,   187,   188,   190,   193,   194,   197,   198,
     201,   202,   205,   206,   207,   210,   211,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   227,   230,
     230,   231,   233,   234,   234,   236,   238,   239,   241,   243,
     245,   247,   250,   253,   254,   257,   261,   263,   264,   265,
     268,   271,   272,   274,   276,   277,   280,   282,   296,   297,
     300,   301,   304,   307,   309,   312,   313,   315,   317,   320,
     323,   326,   328,   331,   332,   333,   334,   335,   335,   337,
     337,   337,   341,   342,   345,   348,   351,   352,   353,   356,
     357,   358,   359,   360,   363,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   395,   397,   399,   401,   403,   404,   405,   407,
     409,   411,   414,   415,   417,   418,   420,   421,   423,   424,
     426,   427,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   463,   465,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   482,   483,   484,
     487,   488,   489,   490,   493,   496,   497,   498,   501,   503,
     505,   507,   509,   513,   516,   518,   519,   520,   521,   522,
     525,   526,   529,   532,   534,   535,   535,   537,   538,   539,
     541,   544,   545,   548,   549,   552,   553,   554,   555,   556,
     558,   559,   562,   563,   566,   567,   570,   575,   580,   581,
     582
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_CLASS", "KW_MODULE", "KW_GAME",
  "KW_INT", "KW_DEF", "KW_DO", "KW_WHILE", "KW_NEW", "KW_THIS",
  "KW_DELETE", "KW_STRING", "KW_REAL", "KW_IF", "KW_ELSE", "KW_RETURN",
  "KW_FOR", "KW_PUBLIC", "KW_VIRTUAL", "KW_MATCH", "NM_STRING", "NM_INT",
  "NM_REAL", "IDENTIFIER", "IDENTTAB", "KW_FUNC", "BH_E", "BH_NE",
  "BH_ANDAND", "BH_OROR", "BH_AE", "BH_PP", "BH_MM", "BH_LE", "BH_PE",
  "BH_MNE", "BH_MLE", "BH_DE", "BH_MDE", "BH_CP", "KW_OPERATOR", "OPP",
  "OPM", "OPMU", "OPD", "OPMO", "OPE", "OPEQ", "OPNE", "OPAE", "OPLE",
  "OPA", "OPL", "OPSET", "OPPOINTER", "OPPP", "OPMM", "'<'", "'>'", "'&'",
  "'|'", "'-'", "'+'", "'*'", "'/'", "'%'", "NEG", "':'", "','", "'{'",
  "'}'", "'='", "'('", "')'", "'['", "']'", "';'", "'?'", "'@'", "'_'",
  "'!'", "'.'", "'\\\\'", "$accept", "SPACE", "SPACE1", "BEGINCLASS",
  "CLASS", "CLASSNAME", "CLASSES", "PARENTNAME", "INHERIT_LIST",
  "CLASSBODY", "CLASSBODY1", "METHODNAME2", "METHODNAME", "METHOD2",
  "METHOD", "ARGUMENTS", "ARGUMENTS1", "ARGUMENT", "METHODBODY",
  "METHODBODY1", "METHODBODY2", "MATCHSTART", "MEXPR", "$@1", "MATCHBODY3",
  "$@2", "MATCHBODY2", "MATCHBODY", "MATCHEXPR2", "MATCHEND2", "MATCHEND1",
  "MATCHEND", "MATCH", "RETEXPR", "FOREXPR", "EQFOR1", "EQFOR1A", "CMPFOR",
  "CMPFOR1", "EQFOR2", "EQFOR2A", "STARTWHILE", "WHILEEXPR", "LOCALNEW1",
  "LOCALNEW", "ATTRIB", "STARTIF", "STARTIF1", "IFEXPR", "IFELS",
  "IFBODY1", "IFBODY", "STARTORDNEW", "ORDNEW2", "ORDNEW1", "ORDNEW",
  "$@3", "$@4", "$@5", "ORDDELETE", "ARGTONEW2", "ARGTONEW1", "BASETYPE",
  "REFERENCE", "EQUATION", "OREXP", "ANDEXP", "STARTOREXP", "STARTANDEXP",
  "EXPRANDOR2", "QIFEXP1", "QIFEXP2", "QIFEXPR", "EXPRANDOR3", "EXPR",
  "EXPRANDOR", "EXPRTOANDOR", "EXPR3", "EXPR1", "STARTCALLEXPR",
  "STARTCALLEXPR2", "EXPR2", "NUMBER", "VALUE", "CALLMETHOD", "CALLMETH",
  "CALLAMBDASTART", "CALLAMBDASTART2", "CALLAMBDASTART3",
  "CALLAMBDASTART4", "CALLOBJECTSTART", "CALLFUNCSTART", "CALLOBJECT",
  "CALLPARENTSTART", "CALLPARENT", "CALLTHISSTART", "CALLTHIS", "$@6",
  "METHODCALLED", "CALLTHIS1", "ARGEXPR", "LARG", "LARGS", "ARGSMETH",
  "ARGSMETH1", "NAMEIDENT", "NAMEIDENTR", "VARIABLE", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,    60,
      62,    38,   124,    45,    43,    42,    47,    37,   314,    58,
      44,   123,   125,    61,    40,    41,    91,    93,    59,    63,
      64,    95,    33,    46,    92
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    87,    87,    87,    88,    88,    88,
      89,    90,    91,    91,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    98,    98,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   104,   104,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   108,
     107,   107,   109,   110,   109,   111,   112,   112,   113,   114,
     115,   116,   117,   118,   118,   119,   120,   121,   121,   121,
     122,   123,   123,   124,   125,   125,   126,   127,   128,   128,
     129,   129,   130,   131,   132,   133,   133,   134,   135,   136,
     137,   138,   139,   140,   140,   140,   140,   141,   140,   142,
     143,   140,   144,   144,   145,   145,   146,   146,   146,   147,
     147,   147,   147,   147,   148,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150,   151,   152,   153,   154,   154,   154,   155,
     156,   157,   158,   158,   159,   159,   160,   160,   161,   161,
     162,   162,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   164,   165,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   167,   167,   167,
     168,   168,   168,   168,   169,   170,   170,   170,   171,   172,
     173,   174,   175,   175,   176,   177,   177,   177,   177,   177,
     178,   178,   179,   180,   181,   182,   181,   183,   183,   183,
     183,   184,   184,   185,   185,   186,   186,   186,   186,   186,
     187,   187,   188,   188,   189,   189,   190,   191,   192,   192,
     192
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       3,     1,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     3,
       2,     3,     2,     2,     1,     2,     3,     2,     1,     3,
       2,     5,     3,     2,     1,     2,     1,     1,     1,     1,
       2,     2,     1,     2,     1,     2,     1,     1,     5,     0,
       4,     1,     2,     0,     5,     2,     2,     1,     1,     2,
       2,     2,     3,     3,     2,     5,     1,     2,     1,     2,
       1,     2,     1,     2,     2,     1,     1,     2,     1,     2,
       1,     3,     2,     1,     2,     1,     3,     1,     3,     2,
       1,     3,     1,     2,     3,     3,     4,     0,     6,     0,
       0,     9,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     5,     3,     3,     2,     2,     2,     2,     3,     3,
       2,     2,     2,     2,     2,     2,     4,     3,     1,     1,
       1,     5,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     3,     4,     5,     4,     4,
       1,     1,     3,     1,     3,     0,     3,     1,     2,     1,
       2,     2,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     3,     2,     1,     3,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     7,     9,     8,   129,   132,    96,   110,   280,     0,
     131,   130,   103,     0,     0,     0,     0,   229,   227,   228,
     277,   244,     0,     0,     0,     0,     0,     0,    54,   133,
     233,     0,   255,     0,     0,     3,     0,     4,    98,    66,
       6,     0,    67,    64,    59,     0,    58,   100,     0,     0,
     105,    57,     0,   112,     0,    62,     0,     0,   279,     0,
       0,     0,   173,   175,   174,     0,   172,   168,     0,   231,
     182,   232,   234,     0,     0,   235,     0,   237,     0,   236,
     243,     0,   278,   230,     0,   160,   161,   122,   123,   280,
     277,    84,   233,   274,   243,     0,    88,     0,    86,     0,
       0,    21,     0,    37,    44,     0,     5,     0,     0,     0,
       0,     0,     0,   215,   276,   269,   268,   112,   267,   265,
     271,     0,   266,     0,     0,   196,    53,     0,    56,     0,
       0,   172,   168,     0,     0,     0,   197,     0,     0,     1,
       2,    11,    12,     0,     0,    99,     0,    77,     0,     0,
       0,     0,    97,     0,    65,   104,   107,     0,   127,     0,
     128,   126,     0,     0,     0,   117,   113,     0,    63,    50,
      60,     0,     0,   178,   176,   179,   177,   165,   164,   169,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   212,   238,     0,
       0,     0,   240,     0,     0,     0,     0,   144,   145,     0,
       0,     0,     0,     0,     0,   154,   156,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   155,   157,   135,   159,
       0,    83,     0,     0,    89,    87,     0,    92,     0,    90,
      40,     0,    42,     0,    22,    29,    30,    34,    35,    36,
      33,    31,    32,    24,    23,    25,    26,    27,    28,     0,
      43,    45,    38,     0,   223,     0,   226,   214,   263,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,    55,
     199,   167,   198,   134,   158,   172,   257,   262,   256,   259,
     264,     0,     0,    10,   102,    78,    75,    76,     0,     0,
       0,    82,    72,    73,     0,   109,   101,   106,   125,   111,
     124,   273,     0,   119,   114,     0,     0,   115,     0,   181,
     180,   163,   162,     0,   190,   191,   192,   193,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   194,
     195,   188,   189,   184,   183,   185,   186,   187,   211,   245,
       0,     0,     0,     0,   241,     0,     0,   252,   254,   146,
     147,   148,   149,   150,   152,   139,   140,   141,   142,   143,
     153,   275,    91,     0,     0,    39,    41,    47,     0,    48,
       0,   224,   225,   221,   222,   217,   216,   218,   219,   220,
     270,     0,   166,   258,   261,   260,    14,    16,    13,    18,
       0,    20,    79,    80,    81,     0,   108,   272,     0,   116,
       0,     0,   170,     0,   246,   239,     0,   248,   249,    95,
      93,     0,    85,    46,     0,    68,   151,     0,    17,    19,
       0,    71,   120,     0,    51,   171,   247,    94,    49,    15,
      74,    69,     0,   118,     0,     0,    70,     0,   121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    34,    35,    36,    37,   142,   143,   407,   408,   303,
     410,   103,   104,   105,   106,   270,   388,    38,    39,   127,
     128,    41,   440,   454,   146,   415,   147,   148,   306,   309,
     310,   311,    42,    43,    44,    97,    98,   248,   249,   384,
     430,    45,    46,    47,    48,   227,    49,    50,    51,   157,
     151,   152,    52,    53,    54,    55,   326,   418,   452,    56,
     319,   159,    57,    58,    59,   171,   172,    60,    61,    62,
     180,   423,    63,    64,    65,    66,   174,   175,    67,    68,
     111,   112,    69,    70,    71,    72,   210,   362,   213,   214,
      73,    74,    75,    76,    77,    78,    79,   137,   297,   298,
      94,   120,   121,   163,    95,    81,    82,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -271
static const yytype_int16 yypact[] =
{
     525,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   135,     8,
    -271,  -271,  -271,  1097,   -52,    43,   -36,  -271,  -271,  -271,
    1290,  -271,  1259,    63,  1165,   604,  1191,  1191,  -271,  -271,
     -29,  1233,  -271,  1191,   499,  -271,    33,  -271,    -7,  -271,
    -271,  1191,  -271,  -271,  -271,    10,  -271,    39,   -14,    10,
      96,  -271,    40,    44,    58,  -271,    54,    92,  -271,    77,
    1191,  1191,    12,  -271,    62,    85,  -271,  1442,   142,  -271,
    -271,  -271,  -271,   148,   100,  -271,   136,  -271,    93,  -271,
    1373,  1411,  -271,  -271,  1191,  -271,  -271,  -271,  -271,   103,
      87,  -271,  -271,   121,   171,   111,    94,   143,  -271,    68,
      68,   147,  1369,  -271,   151,   -30,  -271,    -6,  1191,  1259,
    1259,   204,  1169,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
     160,   174,  -271,  1191,  1165,   187,  -271,   635,  -271,   169,
      62,   170,  1325,   177,  1191,  1191,   187,    66,   162,  -271,
    -271,  -271,   188,   189,  1191,  -271,  1029,  1191,   183,   -15,
    1191,  1029,  -271,    65,  -271,  -271,  -271,  1029,  -271,    88,
    -271,  -271,  1123,   119,  1191,  -271,  -271,   185,  -271,   190,
    -271,  1191,  1191,    30,  -271,  -271,  -271,  -271,  -271,  -271,
    1191,  -271,  1165,  1165,  1165,  1165,  1165,  1165,  1165,  1165,
    1165,  1165,  1165,  1165,  1165,  1165,  1165,  -271,  1165,  1165,
    1165,  1165,  1165,  1165,  1165,  1165,  1165,    44,  -271,    66,
    1029,   203,  -271,  1055,  1029,    66,    66,  -271,  -271,  1191,
    1191,  1191,  1191,  1191,  1191,  -271,  -271,  -271,  -271,  -271,
    1191,  1191,  1191,  1191,  1191,  1191,  -271,  -271,  -271,  -271,
    1191,  -271,    32,   -29,  -271,  -271,  1424,  1191,   205,  -271,
    -271,    -6,  -271,    -6,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   181,
    -271,  -271,  -271,   206,   226,  1102,    44,  -271,  -271,  1259,
    1259,  1259,  1259,  1259,  1259,  1259,    63,   212,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,   213,   217,    44,  -271,   219,
    -271,   268,   308,  -271,  -271,  -271,  -271,  -271,   244,  1029,
     234,  -271,  -271,  -271,   232,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,   233,  -271,  -271,   239,  1029,  -271,   287,  -271,
    -271,  -271,  -271,   242,   400,   400,   400,   400,   161,   161,
     117,   117,   187,   400,   400,   400,   400,   400,   400,   400,
     400,  1467,  1467,   161,   161,   117,   117,   187,  -271,  -271,
     714,   151,  1029,   273,  -271,   740,   819,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,   347,  1029,  -271,  -271,  -271,   249,   255,
     258,  -271,  -271,   238,   238,   168,   168,   129,   129,   226,
    -271,  1191,  -271,  -271,  -271,  -271,  -271,   260,  -271,  -271,
     379,  -271,  -271,  -271,  -271,  1191,  -271,  -271,   151,  -271,
     845,   254,  -271,  1191,  -271,  -271,   924,  -271,  -271,  -271,
    -271,   259,  -271,  -271,    65,  -271,  -271,   268,  -271,  -271,
     280,   267,  -271,   261,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  1029,  -271,  1191,   950,  -271,   262,  -271
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -271,  -271,   304,  -271,  -271,  -271,  -271,  -271,   -91,  -271,
    -271,   -72,  -271,  -271,  -270,  -195,   -89,   -22,   246,  -193,
       3,  -271,  -102,  -271,  -271,  -271,  -271,   214,    50,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,   -70,    57,  -271,  -271,  -271,  -271,
    -271,   315,  -271,   -11,   -10,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,   -13,    -9,   -92,  -271,  -271,  -271,  -271,   -37,
    -271,  -271,   -20,   -19,    18,   -21,   -50,  -271,   292,  -271,
    -271,   -80,  -271,   -12,  -271,  -271,   156,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   104,
       0,  -271,    84,   -65,  -146,    -8,  -271,  -271
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -277
static const yytype_int16 yytable[] =
{
      80,   116,   107,    40,   245,   131,   129,   130,   211,    88,
     113,   176,   117,   118,   119,   122,   322,   360,   364,   101,
     365,   366,    96,   173,   173,    80,   244,   250,   252,   274,
     275,    93,   411,    87,    80,   272,   102,    40,   108,   160,
     312,    25,   177,   178,   134,   133,     4,     5,    28,     4,
       5,   138,   161,    10,    11,   313,    10,    11,   141,   149,
     331,   332,    99,   100,   154,   158,   144,    22,   101,     4,
       5,     4,     5,     7,     4,     5,    10,    11,    10,    11,
      84,    10,    11,   316,   150,   102,   251,   253,   114,    85,
      86,   296,    33,   101,   381,   145,   246,   113,   113,    22,
       4,     5,   239,   129,   130,   242,   164,    10,    11,   153,
     102,   167,   156,   318,   295,   129,   130,   169,   162,   114,
      29,   329,   330,    29,    33,    22,   273,    80,  -250,   165,
     289,   144,   168,   420,   173,   173,   166,   299,   238,    27,
     439,   179,   358,    29,   115,    29,    80,    22,    29,   305,
      33,    80,   294,    22,   315,   170,    23,    80,  -242,   320,
     317,  -242,   304,   181,   190,   149,   425,   207,   314,   426,
    -242,   212,    33,   197,    29,   243,   216,   215,    33,   385,
      93,   386,   325,    84,   206,   277,  -253,     4,     5,   241,
     323,   240,    85,    86,    10,    11,   285,   324,   333,   393,
     394,   395,   396,   397,   398,   399,   188,   189,   190,   299,
      80,   392,  -251,    80,    80,   299,   299,   197,  -253,   208,
     254,   247,   162,   442,   277,   269,   204,   205,   206,   276,
     286,   209,   404,   283,   284,   285,   287,   369,   370,   371,
     372,   373,   374,   197,   290,   291,   300,   389,   375,   376,
     377,   378,   379,   380,   293,   436,   387,   301,    93,   455,
     302,    29,   308,   327,   116,   382,   328,   113,   113,   113,
     113,   113,   113,   113,   208,   117,   118,   119,   122,     4,
       5,   390,   277,   383,    89,   401,    10,    11,   402,   107,
     403,   431,   405,   406,   277,    17,    18,    19,    90,   412,
      21,   281,   282,   283,   284,   285,   414,   416,   417,    80,
     421,   422,   305,   359,     4,     5,   125,   419,   132,   367,
     368,    10,    11,   136,   433,   434,    80,    99,   100,   435,
     437,   444,    22,   101,   447,   450,    24,   451,   140,   453,
     458,   389,   131,   129,   130,   448,   449,    26,   387,    27,
     102,   271,   456,    29,    92,    31,    32,    33,   242,   413,
      80,   307,    80,   289,   155,    80,    80,   361,   289,   289,
     400,     0,   114,     0,     0,     0,     0,     0,     0,     0,
     409,     0,     0,   246,    80,     4,     5,   432,    29,     0,
       0,     0,    10,    11,     0,     0,     0,   107,    99,   100,
       0,     0,     0,     0,   101,     0,    22,     0,     0,    23,
       0,     0,   389,     0,     0,   132,   136,     0,     0,    93,
      80,   102,   429,   289,     0,     0,    80,   132,   243,   289,
       0,    33,     0,   441,     0,     0,     0,     0,     0,     0,
       0,   445,     0,   186,   187,   188,   189,   190,     0,     0,
       0,   438,    80,     0,     0,    80,   197,     0,   289,    29,
       0,   200,   201,   202,   203,   204,   205,   206,     0,     0,
       0,     0,   441,     0,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,     0,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   139,
       0,     0,     1,     2,     3,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,     0,    13,    14,    15,     0,
      16,    17,    18,    19,    20,     0,    21,     0,     1,     2,
       3,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,    15,     0,    16,    17,    18,    19,
      20,     0,    21,     0,     0,     0,     0,     0,    22,     0,
       0,    23,    24,     0,     0,     0,     0,     0,     0,     0,
      25,     0,     0,    26,     0,    27,     0,    28,     0,    29,
      30,    31,    32,    33,    22,     0,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     0,    25,     0,     0,    26,
       0,    27,     0,    28,     0,    29,    30,    31,    32,    33,
       4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
       0,    13,    14,     0,     0,    16,    17,    18,    19,    20,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,     0,   132,    16,    17,    18,    19,
      20,     0,    21,    22,     0,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    25,   126,     0,    26,     0,
      27,     0,    28,     0,    29,    30,    31,    32,    33,     0,
       0,     0,     0,     0,    22,     0,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     0,    25,   288,     0,    26,
       0,    27,     0,    28,     0,    29,    30,    31,    32,    33,
       4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
       0,    13,    14,     0,     0,    16,    17,    18,    19,    20,
       0,    21,     0,     0,     0,     0,     4,     5,     0,     6,
       7,     8,     9,    10,    11,    12,     0,    13,    14,     0,
       0,    16,    17,    18,    19,    20,     0,    21,     0,     0,
       0,     0,     0,    22,     0,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    25,   424,     0,    26,     0,
      27,     0,    28,     0,    29,    30,    31,    32,    33,    22,
       0,     0,    23,    24,     0,     0,     0,     0,     0,     0,
       0,    25,   427,     0,    26,     0,    27,     0,    28,     0,
      29,    30,    31,    32,    33,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,     0,    13,    14,     0,     0,
      16,    17,    18,    19,    20,     0,    21,     0,     0,     0,
       0,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,     0,     0,    16,    17,    18,    19,
      20,     0,    21,     0,     0,     0,     0,     0,    22,     0,
       0,    23,    24,     0,     0,     0,     0,     0,     0,     0,
      25,   428,     0,    26,     0,    27,     0,    28,     0,    29,
      30,    31,    32,    33,    22,     0,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     0,    25,   443,     0,    26,
       0,    27,     0,    28,     0,    29,    30,    31,    32,    33,
       4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
       0,    13,    14,     0,     0,    16,    17,    18,    19,    20,
       0,    21,     0,     0,     0,     0,     4,     5,     0,     6,
       7,     8,     9,    10,    11,    12,     0,    13,    14,     0,
       0,    16,    17,    18,    19,    20,     0,    21,     0,     0,
       0,     0,     0,    22,     0,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    25,   446,     0,    26,     0,
      27,     0,    28,     0,    29,    30,    31,    32,    33,    22,
       0,     0,    23,    24,     0,     0,     0,     0,     0,     0,
       0,    25,   457,     0,    26,     0,    27,     0,    28,     0,
      29,    30,    31,    32,    33,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,     0,    13,    14,     0,     0,
      16,    17,    18,    19,    20,     0,    21,     0,     0,     0,
       0,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,     0,     0,    16,    17,    18,    19,
      20,     0,    21,     0,     0,     0,     0,     0,    22,     0,
       0,    23,    24,     0,     0,     0,     0,     0,     0,     0,
      25,     0,     0,    26,     0,    27,     0,    28,    89,    29,
      30,    31,    32,    33,    22,     0,     0,    23,    24,    17,
      18,    19,    90,     0,    21,     0,    25,     0,     0,   363,
       0,    27,     0,    28,    89,    29,    30,    31,    32,    33,
       0,     0,     0,     0,     0,    17,    18,    19,    90,     0,
      21,     0,     0,     0,     0,     0,    22,     0,   277,     0,
      24,     0,     0,   279,   280,   281,   282,   283,   284,   285,
       0,    26,     0,    27,     0,    91,    89,   391,    92,    31,
      32,    33,    22,     0,     0,     0,    24,    17,    18,    19,
      90,     0,    21,     0,     0,     0,     0,    26,   321,    27,
       0,     0,    89,     0,    92,    31,    32,    33,     0,     0,
       0,     0,     0,    17,    18,    19,    90,     0,    21,     0,
       0,     0,     0,     0,    22,   277,     0,     0,    24,   278,
     279,   280,   281,   282,   283,   284,   285,     0,     0,   123,
       0,    27,     0,     0,    89,     0,    92,   124,    32,    33,
      22,     0,     0,     0,    24,    17,    18,    19,    90,     0,
      21,     0,     0,     0,     0,    26,     0,    27,     0,     0,
      89,     0,    92,    31,    32,    33,     0,     0,     0,     0,
       0,    17,    18,    19,    90,     0,    21,     0,     0,     0,
       0,     0,    22,     0,     0,     0,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,     0,    27,
       0,     0,     0,     0,    92,   124,    32,    33,    22,     0,
       0,     0,   109,  -276,  -276,     0,  -276,  -276,  -276,  -276,
    -276,  -250,     0,   110,     0,    27,     0,     0,  -276,     0,
      92,     0,    32,    33,     0,     0,     0,  -276,  -276,     0,
       0,     0,     0,   182,   183,     0,     0,   184,     0,     0,
     185,  -242,     0,  -276,  -242,     0,     0,     0,   186,   187,
     188,   189,   190,  -242,   191,   192,   193,   194,   195,   196,
       0,   197,     0,     0,   198,   199,   200,   201,   202,   203,
     204,   205,   206,     0,     0,     0,     0,   255,   256,     0,
     292,   257,   258,   259,   260,     0,   217,   218,     0,   219,
     220,   221,   222,   223,  -251,     0,     0,     0,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,   261,   262,
     225,   226,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,   268,     0,   228,   229,   144,   230,   231,   232,
     233,   234,     0,     0,     0,     0,     0,   217,   218,   235,
     219,   220,   221,   222,   223,     0,     0,     0,   236,   237,
     182,   183,   224,     0,   184,     0,     0,   185,     0,     0,
       0,   225,   226,     0,   144,   186,   187,   188,   189,   190,
       0,   191,   192,   193,   194,   195,   196,   144,   197,     0,
       0,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     186,   187,   188,   189,   190,     0,     0,     0,     0,     0,
       0,     0,     0,   197,     0,     0,     0,     0,     0,     0,
     202,   203,   204,   205,   206
};

static const yytype_int16 yycheck[] =
{
       0,    23,    15,     0,    96,    26,    26,    26,    73,     9,
      22,    61,    23,    23,    23,    23,   162,   210,   213,    25,
     213,   214,    74,    60,    61,    25,    96,    99,   100,   109,
     110,    13,   302,    25,    34,   107,    42,    34,    74,    52,
      55,    71,    30,    31,    73,    27,     6,     7,    78,     6,
       7,    33,    52,    13,    14,    70,    13,    14,    25,    41,
      30,    31,    19,    20,    78,    25,    73,    59,    25,     6,
       7,     6,     7,    10,     6,     7,    13,    14,    13,    14,
      48,    13,    14,   153,    74,    42,    99,   100,    25,    57,
      58,    25,    84,    25,   240,    38,    96,   109,   110,    59,
       6,     7,    84,   123,   123,    11,    48,    13,    14,    70,
      42,    54,    16,    25,   135,   135,   135,    25,    74,    25,
      80,   171,   172,    80,    84,    59,   108,   127,    41,    71,
     127,    73,    78,   326,   171,   172,    78,   137,    81,    76,
     410,    79,   207,    80,    81,    80,   146,    59,    80,   146,
      84,   151,   134,    59,   151,    78,    62,   157,    71,   159,
     157,    74,   144,    78,    47,   147,   361,    25,   150,   362,
      83,    71,    84,    56,    80,    81,    83,    41,    84,   251,
     162,   253,   164,    48,    67,    56,    83,     6,     7,    78,
      71,    70,    57,    58,    13,    14,    67,    78,   180,   279,
     280,   281,   282,   283,   284,   285,    45,    46,    47,   209,
     210,   276,    41,   213,   214,   215,   216,    56,    83,    71,
      73,    78,    74,   418,    56,    74,    65,    66,    67,    25,
      70,    83,   297,    65,    66,    67,    62,   219,   220,   221,
     222,   223,   224,    56,    75,    75,    84,   269,   230,   231,
     232,   233,   234,   235,    77,   401,    75,    69,   240,   452,
      71,    80,    79,    78,   286,   247,    76,   279,   280,   281,
     282,   283,   284,   285,    71,   286,   286,   286,   286,     6,
       7,    75,    56,    78,    11,    73,    13,    14,    75,   302,
      73,   383,    73,    25,    56,    22,    23,    24,    25,    55,
      27,    63,    64,    65,    66,    67,    72,    75,    75,   309,
      23,    69,   309,   209,     6,     7,    24,    78,    26,   215,
     216,    13,    14,    31,    75,    70,   326,    19,    20,    71,
      70,    77,    59,    25,    75,    55,    63,    70,    34,    78,
      78,   363,   363,   363,   363,   434,   437,    74,    75,    76,
      42,   105,   454,    80,    81,    82,    83,    84,    11,   309,
     360,   147,   362,   360,    49,   365,   366,   211,   365,   366,
     286,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    -1,   383,   384,     6,     7,   384,    80,    -1,
      -1,    -1,    13,    14,    -1,    -1,    -1,   410,    19,    20,
      -1,    -1,    -1,    -1,    25,    -1,    59,    -1,    -1,    62,
      -1,    -1,   434,    -1,    -1,   123,   124,    -1,    -1,   401,
     420,    42,    75,   420,    -1,    -1,   426,   135,    81,   426,
      -1,    84,    -1,   415,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   423,    -1,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    72,   452,    -1,    -1,   455,    56,    -1,   455,    80,
      -1,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,   454,    -1,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,    -1,
     198,   199,   200,   201,   202,   203,   204,   205,   206,     0,
      -1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    27,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    74,    -1,    76,    -1,    78,    -1,    80,
      81,    82,    83,    84,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    81,    82,    83,    84,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    -1,   363,    21,    22,    23,    24,
      25,    -1,    27,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      76,    -1,    78,    -1,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    81,    82,    83,    84,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    -1,    -1,    -1,    -1,     6,     7,    -1,     9,
      10,    11,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      76,    -1,    78,    -1,    80,    81,    82,    83,    84,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    -1,    74,    -1,    76,    -1,    78,    -1,
      80,    81,    82,    83,    84,     6,     7,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      -1,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    -1,    74,    -1,    76,    -1,    78,    -1,    80,
      81,    82,    83,    84,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    81,    82,    83,    84,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    -1,    -1,    -1,    -1,     6,     7,    -1,     9,
      10,    11,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      76,    -1,    78,    -1,    80,    81,    82,    83,    84,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    -1,    74,    -1,    76,    -1,    78,    -1,
      80,    81,    82,    83,    84,     6,     7,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      -1,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    74,    -1,    76,    -1,    78,    11,    80,
      81,    82,    83,    84,    59,    -1,    -1,    62,    63,    22,
      23,    24,    25,    -1,    27,    -1,    71,    -1,    -1,    74,
      -1,    76,    -1,    78,    11,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    59,    -1,    56,    -1,
      63,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      -1,    74,    -1,    76,    -1,    78,    11,    75,    81,    82,
      83,    84,    59,    -1,    -1,    -1,    63,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    11,    -1,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    59,    56,    -1,    -1,    63,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,    74,
      -1,    76,    -1,    -1,    11,    -1,    81,    82,    83,    84,
      59,    -1,    -1,    -1,    63,    22,    23,    24,    25,    -1,
      27,    -1,    -1,    -1,    -1,    74,    -1,    76,    -1,    -1,
      11,    -1,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    59,    -1,
      -1,    -1,    63,    33,    34,    -1,    36,    37,    38,    39,
      40,    41,    -1,    74,    -1,    76,    -1,    -1,    48,    -1,
      81,    -1,    83,    84,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    32,    -1,    -1,
      35,    71,    -1,    73,    74,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    28,    29,    -1,
      75,    32,    33,    34,    35,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      57,    58,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    33,    34,    73,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    33,    34,    48,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    57,    58,
      28,    29,    48,    -1,    32,    -1,    -1,    35,    -1,    -1,
      -1,    57,    58,    -1,    73,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    73,    56,    -1,
      -1,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    17,    18,    19,    21,    22,    23,    24,
      25,    27,    59,    62,    63,    71,    74,    76,    78,    80,
      81,    82,    83,    84,    86,    87,    88,    89,   102,   103,
     105,   106,   117,   118,   119,   126,   127,   128,   129,   131,
     132,   133,   137,   138,   139,   140,   144,   147,   148,   149,
     152,   153,   154,   157,   158,   159,   160,   163,   164,   167,
     168,   169,   170,   175,   176,   177,   178,   179,   180,   181,
     185,   190,   191,   192,    48,    57,    58,    25,   185,    11,
      25,    78,    81,   159,   185,   189,    74,   120,   121,    19,
      20,    25,    42,    96,    97,    98,    99,   147,    74,    63,
      74,   165,   166,   168,    25,    81,   102,   138,   139,   148,
     186,   187,   190,    74,    82,   163,    72,   104,   105,   157,
     158,   160,   163,   159,    73,    74,   163,   182,   159,     0,
      87,    25,    90,    91,    73,   130,   109,   111,   112,   159,
      74,   135,   136,    70,    78,   136,    16,   134,    25,   146,
     147,   185,    74,   188,    48,    71,    78,   130,    78,    25,
      78,   150,   151,   154,   161,   162,   161,    30,    31,    79,
     155,    78,    28,    29,    32,    35,    43,    44,    45,    46,
      47,    49,    50,    51,    52,    53,    54,    56,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    25,    71,    83,
     171,   188,    71,   173,   174,    41,    83,    33,    34,    36,
      37,    38,    39,    40,    48,    57,    58,   130,    33,    34,
      36,    37,    38,    39,    40,    48,    57,    58,   130,   159,
      70,    78,    11,    81,   129,   149,   185,    78,   122,   123,
      96,   147,    96,   147,    73,    28,    29,    32,    33,    34,
      35,    59,    60,    63,    64,    65,    66,    67,    73,    74,
     100,   103,    96,   159,   166,   166,    25,    56,    60,    61,
      62,    63,    64,    65,    66,    67,    70,    62,    72,   105,
      75,    75,    75,    77,   159,   160,    25,   183,   184,   185,
      84,    69,    71,    94,   159,   105,   113,   112,    79,   114,
     115,   116,    55,    70,   159,   105,   129,   105,    25,   145,
     185,    75,   189,    71,    78,   159,   141,    78,    76,   161,
     161,    30,    31,   159,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   188,   184,
     104,   171,   172,    74,   100,   104,   104,   184,   184,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   189,   159,    78,   124,    96,    96,    75,   101,   102,
      75,    75,   188,   166,   166,   166,   166,   166,   166,   166,
     187,    73,    75,    73,   188,    73,    25,    92,    93,    72,
      95,    99,    55,   113,    72,   110,    75,    75,   142,    78,
     104,    23,    69,   156,    72,   100,   104,    72,    72,    75,
     125,   149,   105,    75,    70,    71,   189,    70,    72,    99,
     107,   159,   100,    72,    77,   159,    72,    75,   101,    93,
      55,    70,   143,    78,   108,   104,   107,    72,    78
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
# if YYLTYPE_IS_TRIVIAL
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
        case 6:

/* Line 1455 of yacc.c  */
#line 128 "dpars4.y"
    {	printkod();	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 131 "dpars4.y"
    { ddput("\tclass "); strcpy(sclass,"class"); preparevars();}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 132 "dpars4.y"
    { ddput("\tgame "); strcpy(sclass,"game"); preparevars(); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 133 "dpars4.y"
    { ddput("\tmodule "); strcpy(sclass,"module"); preparevars(); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 136 "dpars4.y"
    { endclass(); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 139 "dpars4.y"
    { ddput2((yyvsp[(1) - (1)].s), "\n"); strcpy(sclassname, (yyvsp[(1) - (1)].s)); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 146 "dpars4.y"
    { ddput3("\tparent ", (yyvsp[(1) - (1)].s),"\n"); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 161 "dpars4.y"
    {  ddput3("\tmethod ",(yyvsp[(1) - (1)].s),"\n"); 	zerujlocals(); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 162 "dpars4.y"
    {  ddput3("\tmethod ",(yyvsp[(1) - (2)].s),"=\n"); 	zerujlocals(); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 163 "dpars4.y"
    {  ddput("\tmethod operator+\n");		zerujlocals(); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 164 "dpars4.y"
    {  ddput("\tmethod operator-\n");		zerujlocals(); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 165 "dpars4.y"
    {  ddput("\tmethod operator*\n");		zerujlocals(); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 166 "dpars4.y"
    {  ddput("\tmethod operator/\n");		zerujlocals(); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 167 "dpars4.y"
    {  ddput("\tmethod operator%\n");		zerujlocals(); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 168 "dpars4.y"
    {  ddput("\tmethod operator=\n");		zerujlocals(); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 169 "dpars4.y"
    {  ddput("\tmethod operator==\n");		zerujlocals(); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 170 "dpars4.y"
    {  ddput("\tmethod operator!=\n");		zerujlocals(); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 171 "dpars4.y"
    {  ddput("\tmethod operator<\n");		zerujlocals(); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 172 "dpars4.y"
    {  ddput("\tmethod operator>\n");		zerujlocals(); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 173 "dpars4.y"
    {  ddput("\tmethod operator<=\n");		zerujlocals(); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 174 "dpars4.y"
    {  ddput("\tmethod operator>=\n");		zerujlocals(); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 175 "dpars4.y"
    {  ddput("\tmethod operator++\n");		zerujlocals(); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 176 "dpars4.y"
    {  ddput("\tmethod operator--\n");		zerujlocals(); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 180 "dpars4.y"
    { ddpop(); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 181 "dpars4.y"
    { ddpop(); }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 183 "dpars4.y"
    { ddpop(); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 187 "dpars4.y"
    {	printlocals();	}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 190 "dpars4.y"
    { ddput("\tend method\n"); printkod(); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 201 "dpars4.y"
    { iloctab=0; addrellocal( ddpop(), (yyvsp[(2) - (2)].s));  }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 202 "dpars4.y"
    { addlocarray( ddpop(), (yyvsp[(2) - (5)].s), (yyvsp[(4) - (5)].s) ); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 227 "dpars4.y"
    {	ddput("\tspushs\n"); pushloop(); /*petla fin*/	}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 230 "dpars4.y"
    { matchlist(); }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 231 "dpars4.y"
    { matchlist();  ddput3("\tjmp ",getloop(-1),"\n"); }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 233 "dpars4.y"
    {		ddput3("\tcmpst\n\tjne ",pushloop(),"\n\tspop $a\n"); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 234 "dpars4.y"
    { pushloop(); pushloop(); matchlist(); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 234 "dpars4.y"
    { ddput2(poploop(),":\n\tspop $a\n"); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 236 "dpars4.y"
    { ddput3("\tjmp ",getloop(-1),"\n"); ddput2(poploop(),":\n"); }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 243 "dpars4.y"
    {	ddput("\tspop $a\n");	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 247 "dpars4.y"
    { ddput2(poploop(),":\n");	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 253 "dpars4.y"
    { ddput("\tret\n");	 }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 254 "dpars4.y"
    { ddput("\tret\n"); }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 257 "dpars4.y"
    { ddput3("\tjmp ", poploop(), "\n");
								ddput2( poploop(), ":\n"); poploop();	}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 261 "dpars4.y"
    { startloop(); }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 268 "dpars4.y"
    {	ifpart1(); char *c3=pushloop(), *c4=pushloop(); 
							ddput3("\tjmp ", c4, "\n"); ddput2(c3,":\n"); }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 272 "dpars4.y"
    { ddput("\tpush 1\n");	}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 274 "dpars4.y"
    { ddput3("\tjmp ",getloop(-3),"\n");  ddput2( poploop(), ":\n"); }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 280 "dpars4.y"
    { startloop();	}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 282 "dpars4.y"
    { ifpart2(); poploop(); }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 297 "dpars4.y"
    { ddput3("\tpop ",lastlocal(),"\n"); }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 307 "dpars4.y"
    {	pushloop();	}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 312 "dpars4.y"
    { ifpart3(); poploop();  }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 313 "dpars4.y"
    { ifpart3(); }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 315 "dpars4.y"
    { ifpart2(); }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 317 "dpars4.y"
    { ifpart1(); }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 323 "dpars4.y"
    { prepare(); build("\tnew "); pushbuild(); }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 328 "dpars4.y"
    { stdnew(); }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 332 "dpars4.y"
    { stdnew(); }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 333 "dpars4.y"
    { ddput3("\tpop ",sident[idkod+1],"\n"); }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 334 "dpars4.y"
    { ddput3("\tcall ",sident[idkod+1],",operator=\n");}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 335 "dpars4.y"
    { ddpush( beginkod() );	}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 335 "dpars4.y"
    { endkod(); ddput3("\tcall ",sident[idkod+1],","); 
			ddput2(ddpop(),"\n"); }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 337 "dpars4.y"
    { stdnew(); ddpush( beginkod() ); }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 337 "dpars4.y"
    { printlocals(); }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 338 "dpars4.y"
    { endkod(); ddput3("\tcall ",sident[idkod+1],",");	ddput2(ddpop(),"\n"); }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 341 "dpars4.y"
    {	ddput3("\tdelete ",(yyvsp[(2) - (2)].s),"\n");	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 342 "dpars4.y"
    {	ddput("\tspop $d\n\tdelete [$d]\n");	}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 345 "dpars4.y"
    { 	char tmp[100]; strcpy(tmp,ddpop()); popbuild(); 
								prebuild("\tspop $e\n"); pushbuild();  ddpush(tmp);  // najpierw new, potem argument
								ddpush("[$e]");  }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 348 "dpars4.y"
    { ddpush((yyvsp[(1) - (1)].s)); }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 351 "dpars4.y"
    { popbuild(); prebuild("\tspop $d\n"); pushbuild(); ddpush("[$d]");  }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 352 "dpars4.y"
    { ddpush((yyvsp[(1) - (1)].s)); }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 356 "dpars4.y"
    { ddpush("int");	}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 357 "dpars4.y"
    { ddpush("real");	}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 358 "dpars4.y"
    { ddpush("string");	}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 359 "dpars4.y"
    { ddpush("def");	}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 360 "dpars4.y"
    { ddpush("def");	}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 363 "dpars4.y"
    { ddput("\tpopax\n\tmov $a,[$a]\n\tpsax\n");}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 366 "dpars4.y"
    { ddput3("\tpop ",sident[idkod+1],"\n"); }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 367 "dpars4.y"
    { ddput("\tspop $b\n\tpopax\n\tmov [$b],$a\n"); }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 368 "dpars4.y"
    { ddput3("\tadd ",sident[idkod+1],",1\n");	ddput3("\tpop ",sident[idkod+1],"\n"); }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 369 "dpars4.y"
    { ddput3("\tsub ",sident[idkod+1],",1\n");	ddput3("\tpop ",sident[idkod+1],"\n"); }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 370 "dpars4.y"
    { qexpr("add", sident[idkod+1]); }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 371 "dpars4.y"
    { qexpr("sub", sident[idkod+1]); }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 372 "dpars4.y"
    { qexpr("mul", sident[idkod+1]); }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 373 "dpars4.y"
    { ddput3("\tpopax\n\tdiv ",sident[idkod+1],",$a\n");	ddput3("\tmov ",sident[idkod+1],",$a\n");	}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 374 "dpars4.y"
    { ddput3("\tpopax\n\tdiv ",sident[idkod+1],",$a\n");	ddput3("\tmov ",sident[idkod+1],",$d\n");	}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 375 "dpars4.y"
    { ddput("\tspop $b\n\tadd [$b],1\n\tpop [$b]\n"); }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 376 "dpars4.y"
    { ddput("\tspop $b\n\tsub [$b],1\n\tpop [$b]\n"); }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 377 "dpars4.y"
    { sexpr("add"); }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 378 "dpars4.y"
    { sexpr("sub"); }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 379 "dpars4.y"
    { sexpr("mul"); }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 380 "dpars4.y"
    { ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$a\n"); }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 381 "dpars4.y"
    { ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$d\n"); }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 382 "dpars4.y"
    { putattr(); }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 383 "dpars4.y"
    {ddput("\tspop $a\n\tcall [$a],operator=\n");}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 384 "dpars4.y"
    {ddput3("\tcall ",sident[idkod+1],",operator=\n");}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 385 "dpars4.y"
    {	ddput("\tspop $a\n\tcall [$a],operator++\n");}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 386 "dpars4.y"
    {ddput3("\tcall ",sident[idkod+1],",operator++\n");}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 387 "dpars4.y"
    {	ddput("\tspop $a\n\tcall [$a],operator--\n");}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 388 "dpars4.y"
    {ddput3("\tcall ",sident[idkod+1],",operator--\n");}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 389 "dpars4.y"
    {	ddput("\tpopax\n");	}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 390 "dpars4.y"
    { ddput("\tcthis operator=\n");	}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 391 "dpars4.y"
    { ddput("\tcthis operator++\n");	}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 392 "dpars4.y"
    { ddput("\tcthis operator--\n");	}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 395 "dpars4.y"
    {	checkor();		}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 397 "dpars4.y"
    {	checkand();	}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 399 "dpars4.y"
    {	pushloop();pushloop();	checkor();		}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 401 "dpars4.y"
    {	pushloop();pushloop();	checkand();	}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 403 "dpars4.y"
    {	neg();	}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 407 "dpars4.y"
    {	qifexp1();	}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 409 "dpars4.y"
    {	qifexp2();	}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 411 "dpars4.y"
    {	qifexp3();	}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 420 "dpars4.y"
    {	endandor();	}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 421 "dpars4.y"
    {	endandor();	}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 431 "dpars4.y"
    { expr("add"); }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 432 "dpars4.y"
    { expr("sub"); }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 433 "dpars4.y"
    { expr("mul"); }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 434 "dpars4.y"
    { expr("div"); ddput("\tpsax\n");}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 435 "dpars4.y"
    { expr("div"); ddput("\tpush $d\n"); }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 436 "dpars4.y"
    { expr("and");	}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 437 "dpars4.y"
    { expr("or");	}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 438 "dpars4.y"
    { cmp("je"); }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 439 "dpars4.y"
    { cmp("jne"); }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 440 "dpars4.y"
    { cmp("jae"); }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 441 "dpars4.y"
    { cmp("jle"); }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 442 "dpars4.y"
    { cmp("jl"); }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 443 "dpars4.y"
    { cmp("ja"); }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 444 "dpars4.y"
    { ddput("\tpopax\n\tsub 0,$a\n"); }
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 445 "dpars4.y"
    { neg(); }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 448 "dpars4.y"
    {calloper("+");}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 449 "dpars4.y"
    {calloper("-");}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 450 "dpars4.y"
    {calloper("*");}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 451 "dpars4.y"
    {calloper("/");}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 452 "dpars4.y"
    {calloper("%");}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 453 "dpars4.y"
    {calloper("==");}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 454 "dpars4.y"
    {calloper("!=");}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 455 "dpars4.y"
    {calloper(">=");}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 456 "dpars4.y"
    {calloper("<=");}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 457 "dpars4.y"
    {calloper(">");}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 458 "dpars4.y"
    {calloper("<");}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 459 "dpars4.y"
    {	ddput3("\tspop $h\n\tcall $h,",(yyvsp[(2) - (3)].s),"\n");	}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 460 "dpars4.y"
    {	ddput3("\tspop $h\n\tcall $h,",(yyvsp[(2) - (2)].s),"\n");	}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 463 "dpars4.y"
    {	ddput("\tspushs\n");	}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 465 "dpars4.y"
    {	ddput("\tspushs\n");	}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 469 "dpars4.y"
    { expr("add"); }
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 470 "dpars4.y"
    { expr("sub"); }
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 471 "dpars4.y"
    { expr("mul"); }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 472 "dpars4.y"
    { expr("div"); ddput("\tpsax\n");}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 473 "dpars4.y"
    { expr("div"); ddput("\tpush $d\n"); }
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 474 "dpars4.y"
    { expr("and");	}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 475 "dpars4.y"
    { expr("or");	}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 476 "dpars4.y"
    { ddput("\tpopax\n\tsub 0,$a\n"); }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 478 "dpars4.y"
    {	ddput3("\tspop $a\n\tcall $a,",(yyvsp[(2) - (3)].s),"\n");	}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 479 "dpars4.y"
    {	ddput3("\tspop $a\n\tcall $a,",(yyvsp[(2) - (2)].s),"\n");	}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 482 "dpars4.y"
    {	ddput3("\tpush ",(yyvsp[(1) - (1)].s),"\n"); }
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 483 "dpars4.y"
    {	ddput3("\tpush ",(yyvsp[(1) - (1)].s),"\n"); }
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 484 "dpars4.y"
    {	ddput3("\tpush ",(yyvsp[(1) - (1)].s),"\n"); }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 493 "dpars4.y"
    { putbuild(); }
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 501 "dpars4.y"
    {	popbuild(); build2(beginkod(),"\n"); pushbuild(); }
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 503 "dpars4.y"
    {	printlocals();	}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 505 "dpars4.y"
    {	popbuild(); build2(beginkod(),"\"\n"); pushbuild(); }
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 507 "dpars4.y"
    {	printlocals();	}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 509 "dpars4.y"
    { char *c=getlocal((yyvsp[(1) - (1)].s)); 
									if(c==NULL) build3("\tcall ", (yyvsp[(1) - (1)].s), ","); 
									else build3("\tcall ",c, ",");  
								pushbuild(); }
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 513 "dpars4.y"
    { build("\tspop $a\n\tcall [$a],"); 
								pushbuild(); }
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 516 "dpars4.y"
    {	build("\tpush \"");	pushbuild();	}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 519 "dpars4.y"
    {	endkod();	}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 520 "dpars4.y"
    {	endkod();	 }
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 521 "dpars4.y"
    {	endkod();	}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 522 "dpars4.y"
    {	endkod();	}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 525 "dpars4.y"
    { build3("\tclparent ", (yyvsp[(1) - (1)].s), ","); pushbuild(); }
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 526 "dpars4.y"
    { build("\tspop $a\n\t clparent [$a],"); 
								pushbuild(); 	}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 532 "dpars4.y"
    { build("\tcthis "); pushbuild(); }
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 535 "dpars4.y"
    { build("\tcthis "); pushbuild(); }
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 537 "dpars4.y"
    { popbuild(); build2((yyvsp[(1) - (1)].s),"\n"); pushbuild(); }
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 538 "dpars4.y"
    { popbuild(); build2((yyvsp[(1) - (2)].s),"=\n"); pushbuild(); }
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 539 "dpars4.y"
    { popbuild(); prebuild("\tspop $d\n"); build("[$d]\n"); 
							pushbuild();}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 541 "dpars4.y"
    { popbuild(); prebuild("\tspop $d\n\tadd $d,\"=\"\n"); build("[$d]\n"); 
							pushbuild();}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 548 "dpars4.y"
    {	argexpr();	 }
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 549 "dpars4.y"
    {	argexpr();	}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 552 "dpars4.y"
    {	insertattr(NULL);	}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 553 "dpars4.y"
    {	insertattr(sident[idkod+1]);	}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 554 "dpars4.y"
    {	insertattr(sident[idkod+1]);	}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 555 "dpars4.y"
    {	int i; for( i=iloctab;i>0;i--) insertattr( localname(ktorylocal[idkod+1]-i) );	}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 556 "dpars4.y"
    {	insertattr("_");	}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 570 "dpars4.y"
    {	char tmp[256]; strcpy(tmp,(yyvsp[(1) - (1)].s)); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sident[idkod+1],tmp);
						else strcpy(sident[idkod+1],c); }
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 575 "dpars4.y"
    {	char tmp[256]; strcpy(tmp,(yyvsp[(1) - (1)].s)); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sidentr[idkod+1],tmp);
						else strcpy(sidentr[idkod+1],c); }
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 580 "dpars4.y"
    { ddput3("\tpush ",sidentr[idkod+1],"\n"); }
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 582 "dpars4.y"
    {	ddput("\tcthis getname\n");	}
    break;



/* Line 1455 of yacc.c  */
#line 3546 "y.tab.c"
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



/* Line 1675 of yacc.c  */
#line 585 "dpars4.y"


void sexpr(char *s)	{
	ddput3("\tpopax\n\tspop $b\n\t",s," [$b],$a\n\tpop [$b]\n");
}

void qexpr(char *sinstr, char *svar)	{
	ddput3("\tpopax\n\t",sinstr," ");
	ddput3( svar, ",$a\n\tpop ",svar);
	ddput("\n");
}

void checkand()	{
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",getloop(-1),"\n");
	} else {
		ddput3("\tcmp0\n\tje ",getloop(-1),"\n");
	}
}

void checkor()	{
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tjne ",lastloop(),"\n");
	} else {
		ddput3("\tcmp0\n\tjne ",lastloop(),"\n");
	}
}

void endandor()	{
	char *c1=getloop(-1);
	char *c2=lastloop();
	char *c3=pushloop();
	ddput3("\tjmp ",c3,"\n");		// jmp next
	ddput3(c1,":\n\tpush 0\n\tjmp ",c3);	// endand: push 0 jmp next
	ddput3("\n",c2,":\n\tpush 1\n");	// endor: push1
	ddput2(c3,":\n");
	poploop();		// out next:
	poploop();		// out endor:
	poploop();		// out endand
}

void startloop()	{
	ddput2( pushloop(), ":\n" );
}

void ifpart1()	{
	char *c2 = pushloop();
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",c2,"\n");
	} else {
		ddput3("\tcmp0\n\tje ",c2,"\n");
	}
}

void ifpart2()	{
	char *c2 = poploop();
	char *c1 = lastloop();
	ddput3("\tjmp ",c1,"\n");
	ddput2( c2, ":\n");
}

void ifpart3()	{
	ddput2( poploop(), ":\n" );
}

void cmp(char *s)	{
	if( ioptimized==0 )	{
		char *c1 = pushloop(), *c2 = pushloop();
		ddput3("\tpop $b\n\tpopax\n\tcmp $a,$b\n\t",s," ");
		ddput3( c1,"\n\tpush 0\n\tjmp ", c2);
		ddput3("\n",c1,":\n\tpush 1\n");
		ddput2(c2, ":\n");
		poploop();
		poploop();
	} else {
		ddput3("\tcmp",s,"\n");
	}
}

void neg()	{
	if( ioptimized==0 )	{
		char *c1 = pushloop(), *c2 = pushloop();
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",c1,"\n\tpush 0\n\tjmp ");
		ddput3(c2,"\n",c1);
		ddput3(":\n\tpush 1\n",c2,":\n");
		poploop();
		poploop();
	} else {
		ddput("\tneg\n");
	}
}

void preparevars()	{
	iglobalambda = ilambdas;
	ilambdas=-1;
	int i;
	if( idkod!=-1 )	{
		printf("\n idkod!=-1! %d\n", idkod );
		exit(1);
	}
	for( i=0; i<ILEKOD;i++)	{
		if( skod[i] != NULL )	{
			printf("\nskod!=NULL");
			free(skod[i]);
			skod[i]=NULL;
		}
		idlocal[i] = 0;
		ktorylocal[i]=0;
		ikodprev[i] = 0;
		ilimkod[i] = 0;
		ilekod[i] = 0;
	}
}

void printlocals()	{
	int i;
	for(i=ktorylocal[idkod+1];i>0; i--)	{
		ddput3("\tpop ",localname(i-1),"\n");
	}
}

char *pushloop()	{
	lstack++;
	loopc++;	
	char tmp[10], *c;
	c = sloop[lstack];
	strcpy(c,"l");
	sprintf(tmp,"%d",loopc);
	strcat(c,tmp);
	return lastloop();
}

char *poploop()	{
	if(lstack<0)	{
		dderror("stack pointer ","<0");
	}
	lstack--;
	return sloop[lstack+1];
}

char *getloop(int id)	{
	if(id>0)	{
		dderror("getloop id ",">0");
	}
	if(lstack+id<0)	{
		dderror("loop stack pointer ","<0");
	}
	return sloop[lstack+id];
}

char *lastloop()	{
	if(lstack<0)	{
		dderror("loop stack pointer ","<0");
	}
	return sloop[lstack];
}

char *localname(int pos)	{
	strcpy(sloc,"$");
	char tmp[20];
	sprintf(tmp,"%d",pos+1);
	strcat(sloc,tmp);
	return sloc;
}

void addlocal(char *s)	{
	int ile = idlocal[idkod+1], i, found=-1;
	for( i=0; i<ile; i++)	{
		if( strcmp(local[i][idkod+1], s)==0 )
			found=i;
	}
	if( found>=0 )	{
		ilastlocal=found;
	} else {
		strcpy(local[ile][idkod+1],s);
		ilastlocal = ile;
		idlocal[idkod+1]++;
	}
}

void addrellocal(char *styp, char *s)	{
	ddput3("\tlocal",styp," ");  
	addlocal( s );
	ddput2( getlocal( s ) , "\n"); 
	ktorylocal[idkod+1]++;
	iloctab++;
}

void addlocarray( char *styp, char *snom, char *sile )	{
	iloctab = 0;
	int ile = atoi( sile );
	if(ile<=0)	{
		dderror("array size ","< 0");
	}
	int i;
	char s1[20], s2[64];
	for(i =0; i<ile; i++)	{
		strcpy( s2, snom );
		sprintf(s1,"%d",i);
		strcat(s2,s1);
		addrellocal( styp, s2 );
	}
}

char *lastlocal()	{
	//return localname(idlocal[idkod+1]-1);
	return localname( ilastlocal );
}

char *getlocal(char *s)	{
	int pos = -1;
	int i;
	for(i=0; i<idlocal[idkod+1]; i++)	{
		if(strcmp(s,local[i][idkod+1])==0)	{
			pos=i;
		}
	}
	if(pos==-1)	{
		return NULL;
	} else {
		return localname(pos);
	}
}

void ddstart(char *filename)	{
	prepare();		// string build
	if(filename==NULL)	{
		fin = fopen("ddag.odd","w");
	} else fin = fopen(filename,"w");
	if(fin==NULL)	{
		printf("nieudane stworzenie pliku!");
		exit(1);
	}
	ddput("; Dominik Dagiel   ix 2005\n\n");
}

void ddend()	{
	fclose(fin);
}
void ddput2(char *s1, char *s2)	{	ddput(s1);	ddput(s2);}
void ddput3(char *s1, char *s2, char *s3)	{	ddput(s1);	ddput(s2);	ddput(s3);}
void ddput(char *s)	{
	if( idkod>=0 )	{
		int id = 0;
		if( skod[idkod]==NULL )	{
			skod[idkod] = (char*)malloc( ilimkod[idkod]*sizeof(char));
		}
		while(s[id]!='\0')	{
			if( ilekod[idkod] >= ilimkod[idkod]-1 )	{
				ilimkod[idkod] *= 2;
				char *c = (char*)malloc( ilimkod[idkod]*sizeof(char));
				skod[idkod][ ilekod[idkod] ] = '\0';
				strcpy( c, skod[idkod] );
				free( skod[idkod] );
				skod[idkod] = c;
			}
			skod[idkod][ ilekod[idkod] ] = s[id];
			ilekod[idkod]++;
			id++;
		}
	} else {
		fputs(s,fin);
	}
}
char *beginkod()	{
	char snr[16];
	ilambdas++;
	sprintf(snr, "%d", ilambdas);
	
	ikodprev[ilambdas] = idkod;
	idkod = ilambdas;
	
	skod[idkod] = NULL;
	ilimkod[idkod] = 1024;
	ilekod[idkod] = 0;
	idlocal[idkod+1] = 0;
	ktorylocal[idkod+1]=0;
	
	strcpy(scallmethod, sclassname);
	strcat(scallmethod, snr );
	return scallmethod;
}
void endkod()	{
	idkod = ikodprev[idkod];
}
void printkod()	{
	int i;
	char snr[16], s[256];
	if( idkod!=-1 )	{
		printf("\n idkod!=-1! %d\n", idkod );
		exit(1);
	}
	for(i=0; i<=ilambdas; i++)	{
		if( skod[i]!=NULL )	{
			strcpy(s, sclassname );
			sprintf(snr, "%d", i);
			strcat(s, snr );
			ddput3("\tmethod ", s, "\n");
			printf("\n ilekod, ilambdas : %d, %d\n",ilekod[i], ilambdas ); 
			skod[i][ ilekod[i] ] = '\0';
			ddput( skod[i] );
			free( skod[i] );
			skod[i] = NULL;
			ilekod[i] = 0;
			ddput("\tend method\n");
		}
	}
}

void zerujlocals()	{
	idlocal[idkod+1]=0;
	ktorylocal[idkod+1]=0;
}

void stdnew()	{
	strcpy(sident[idkod+1],ddpop()); 		// drugi argument
	char styp[100];
	strcpy(styp, ddpop());	// typ 
	putbuild(); 	// buduje ewentualne popy oraz "new "
	ddput3(styp,",",sident[idkod+1]); 
	ddput("\n");
}

void qifexp1()	{
	char *c1 = pushloop();
	char *c2 = pushloop();
	ddput3("\tcmp0\n\tje ",c2,"\n");
}
void qifexp2()	{
	char *c2 = poploop();
	char *c1 = lastloop();
	ddput3("\tjmp ",c1,"\n");
	ddput2(c2,":\n");
}
void qifexp3()	{	ddput2(poploop(),":\n");}

void argexpr()	{
	if(ioptimized==0) {
		ddput("\tpopax\n\tspush $a\n");
	} else {
		ddput("\tspushs\n");
	}
}

int yyerror(char *s)	{
    printf( "Syntax Error %s\n",s);
    exit( 1 );
}

int clears(char *s)	{
	int i, j=0;
	char z;
	for(i=0; s[i]!='\0'; i++)	{
		z = s[i];
		if( (z>='a'&&z<='z')||(z>='A'&&z<='Z')||(z>='0'&&z<='9')||
			z=='/' || z=='.' || z=='_' || z==':')	{
			s[j]=z;
			j++;
		}
	}
	s[j]='\0';
	return j;
}

void putattr()	{
	while(ilecalls>0) {
		if( sattr[ilecalls-1][0]=='\0' )	{
			ddput("\tspop $b\n\tpopax\n\tmov [$b],$a\n");
		} else if( strcmp(sattr[ilecalls-1],"_")==0 ) {
			ddput("\tpopax\n");
		} else {
			ddput3("\tpop ",sattr[ilecalls-1],"\n");
		}
		ilecalls--;
	}
}

void matchbody()	{
	ddput3("\tcmpst\n\tjne ",pushloop(),"\n");
}

void matchlist()	{
	ddput3("\tcmpst\n\tje ",lastloop(),"\n");
}

void insertattr(char *c)	{
	if( c==NULL )	{
		ddput("\tspushs\n");
		sattr[ilecalls][0]='\0';
	} else {
		strcpy( sattr[ilecalls], c );
	}
	ilecalls++;
}

void calloper(char *c)	{
	ddput3("\tpopax\n\tpop $b\n\tpsax\n\tcall [$b],operator",c,"\n");
}

void endclass()	{
	ddput3("\tend ",sclass,"\n\n");
	if( idkod>-1 )	{
		printf("\nerror! idkod>0! %d\n", idkod);
		exit(1); 
	}
	ilambdas = iglobalambda;
	strcpy( sclassname, "global" );
}

int main(int argc, char *argv[])
{
	//yydebug=0;
	FILE *fprj;
	int readobj=0;
	char srobj[128], z, srob[128];
	int iposob=0, i, koniec=0, idarg=1;
	
	strcpy(sclassname, "global");
	for( i=0; i<ILEKOD;i++)	{
		skod[i]=NULL;
		ktorylocal[i]=0;
		idlocal[i]=0;
		ikodprev[i] = 0;
	}
	
	ioptimized = 1;		// std poziom optymalizacji
	
	while(idarg<argc)	{
		if( strcmp( argv[idarg], "-O" )==0 )	{
			if( idarg+1<argc )	{
				ioptimized = atoi( argv[idarg+1] );
				idarg+=2;
			} else {
				printf("\nnot added argument to \"-O\"");
				return 1;
			}
		} else {
			if( (fprj=fopen(argv[idarg],"r"))==NULL)	{
				printf("\nunable to open %s",argv[1]);
				ddstart(NULL);
			} else {
				while( fgets(srobj,128,fprj)!=NULL && !koniec)	{
					if(clears(srobj))	{
						if(!strcmp(srobj,"out:"))	{
							readobj=1;
						} else if(readobj)	{
							printf("\nsrobj = %s", srobj);
							strcpy(srob,srobj);
							koniec = 1;
							readobj=0;
						}
					}
				}
				fclose(fprj);
				if(koniec)	{
					ddstart(srob);
				} else {
					printf("\nout not precisied");
					ddstart(NULL);
				}
			}
			idarg++;
		}
	}
	if( !koniec )	{
		printf("\nnot given output ");
		ddstart(NULL);
	}
    yyparse();
    ddend();
    return 0;
}


