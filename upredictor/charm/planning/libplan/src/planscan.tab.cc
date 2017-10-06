/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "planscan.y"

#include "action.h"
#include "actor.h"
#include "actorsorter.h"
#include "actortable.h"
#include "andactionpredicate.h"
#include "atomicactionpredicate.h"
#include "actionpredicate.h"
#include "domain.h"
#include "domainmap.h"
#include "notactionpredicate.h"
#include "planninggraph.h"
#include "problem.h"

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define YYERROR_VERBOSE

// stuff from flex that bison needs to know about:
//extern "C" int yyparse (void); //added so that planner compiles on MARSBAR
extern "C" int yylex();
//extern "C" FILE *yyin;
 
void yyerror(const char *s);

DomainMap *domainmap = NULL;
Domain *fillDomain = NULL;
Action *fillAction = NULL;
Problem *fillProblem = NULL;
PlanningGraph *fillPlanningGraph = NULL;
ActorTable *fillActorTable = NULL;
ActorSorter *fillActorSorter = NULL;

vector<string> nameList, typeList;
string newActionname;

vector<ActionPredicate *> predList;

//vector<int> noConcurLeft, noConcurRight;


/* Line 371 of yacc.c  */
#line 114 "planscan.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "planscan.tab.h".  */
#ifndef YY_YY_PLANSCAN_TAB_H_INCLUDED
# define YY_YY_PLANSCAN_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     INT = 258,
     FLOAT = 259,
     STRING = 260,
     NAME = 261,
     PARAMETER = 262,
     DEFINE = 263,
     DOMAIN = 264,
     TYPES = 265,
     PREDICATES = 266,
     ACTION = 267,
     PARAMETERS = 268,
     PRECONDITION = 269,
     EFFECT = 270,
     PROBLEM = 271,
     TIMES = 272,
     CONCURRENCYEXEPTIONS = 273,
     COLON_DOMAIN = 274,
     COLON_OBJECTS = 275,
     COLON_INIT = 276,
     COLON_GOAL = 277,
     COLON = 278,
     SEMICOLON = 279,
     COLON_PROBLEM = 280,
     COLON_TIMES = 281,
     COLON_COMMAND = 282,
     COLON_DURATION = 283,
     COLON_ACTIONNOCONCUR = 284,
     ACTORS = 285,
     COLON_ACTORS = 286,
     COLON_ACTOR = 287,
     COLON_ACTIONS = 288,
     COLON_ACTORTYPE = 289,
     COLON_CONF_FILE = 290,
     LB = 291,
     RB = 292,
     LP = 293,
     RP = 294,
     DASH = 295,
     AND = 296,
     NOT = 297,
     STATEMACHINES = 298,
     COLON_STATEMACHINES = 299,
     COLON_STATEMACHINE = 300,
     COLON_STATES = 301,
     COLON_STATELISTING = 302,
     COLON_STATE = 303,
     COLON_ONENTRY = 304,
     COLON_MESSAGE = 305,
     CR = 306
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 55 "planscan.y"

	int ival;
	float fval;
	char *sval;


/* Line 387 of yacc.c  */
#line 216 "planscan.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PLANSCAN_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 244 "planscan.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
# define YYCOPY_NEEDED 1
#endif


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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   256

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  266

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    22,
      27,    30,    31,    36,    41,    44,    45,    47,    48,    53,
      55,    56,    61,    67,    72,    79,    84,    90,    93,    98,
     101,   102,   110,   115,   120,   125,   130,   137,   142,   145,
     146,   152,   160,   165,   168,   169,   175,   181,   186,   192,
     197,   202,   208,   211,   214,   217,   222,   224,   226,   231,
     236,   239,   240,   243,   244,   249,   254,   259,   262,   263,
     267,   272,   278,   283,   288,   291,   292,   294,   296,   298,
     304,   307,   310,   312,   317,   320,   323,   328,   331,   332,
     334,   336,   338,   340,   345,   347,   352,   355,   356,   358,
     363,   368,   371,   372,   377,   380,   381,   383,   386,   387,
     391
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      53,     0,    -1,   106,    -1,    90,    -1,    81,    -1,    77,
      -1,    68,    -1,    54,    -1,    38,     8,    67,   107,    55,
      39,    -1,    38,    44,    56,    39,    -1,    66,    56,    -1,
      -1,    38,    12,     6,    39,    -1,    38,    46,    59,    39,
      -1,    64,    59,    -1,    -1,    61,    -1,    -1,    38,    50,
       6,    39,    -1,    63,    -1,    -1,    38,    49,    60,    39,
      -1,    38,    48,     6,    62,    39,    -1,    38,    47,   131,
      39,    -1,    38,    45,    57,    65,    58,    39,    -1,    38,
      43,     6,    39,    -1,    38,     8,    69,    70,    39,    -1,
      76,   107,    -1,    38,    31,    71,    39,    -1,    72,    71,
      -1,    -1,    38,    32,     6,    74,    73,    75,    39,    -1,
      38,    35,     6,    39,    -1,    38,    34,     6,    39,    -1,
      38,    33,   131,    39,    -1,    38,    30,     6,    39,    -1,
      38,     8,    78,   107,    79,    39,    -1,    38,    18,     6,
      39,    -1,    80,    79,    -1,    -1,    38,    29,     6,     6,
      39,    -1,    38,     8,    88,   107,    89,    82,    39,    -1,
      38,    26,    83,    39,    -1,    84,    83,    -1,    -1,    38,
      85,    86,    87,    39,    -1,    38,    12,     6,   131,    39,
      -1,    38,    27,     6,    39,    -1,    38,    28,     4,     4,
      39,    -1,    38,    17,     6,    39,    -1,    38,    25,     6,
      39,    -1,    38,     8,    91,    94,    39,    -1,    92,    97,
      -1,    93,   102,    -1,   105,   107,    -1,    38,    22,    95,
      39,    -1,   101,    -1,    96,    -1,    38,    41,    99,    39,
      -1,    38,    21,    98,    39,    -1,   100,    98,    -1,    -1,
     101,    99,    -1,    -1,    38,     6,   131,    39,    -1,    38,
       6,   131,    39,    -1,    38,    20,   103,    39,    -1,   104,
     103,    -1,    -1,   131,    40,     6,    -1,    38,    16,     6,
      39,    -1,    38,     8,   108,   109,    39,    -1,    38,    19,
       6,    39,    -1,    38,     9,     6,    39,    -1,   110,   109,
      -1,    -1,   127,    -1,   128,    -1,   111,    -1,    38,    12,
     112,   117,    39,    -1,   113,   116,    -1,   114,   115,    -1,
       6,    -1,    13,    38,   133,    39,    -1,    14,   120,    -1,
      15,   120,    -1,    38,    41,   119,    39,    -1,   120,   119,
      -1,    -1,   121,    -1,   118,    -1,   122,    -1,   124,    -1,
      38,   123,   125,    39,    -1,     6,    -1,    38,    42,   121,
      39,    -1,   126,   125,    -1,    -1,     7,    -1,    38,    10,
     131,    39,    -1,    38,    11,   129,    39,    -1,   130,   129,
      -1,    -1,    38,     6,   133,    39,    -1,   132,   131,    -1,
      -1,     6,    -1,   134,   133,    -1,    -1,   135,    40,     6,
      -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    91,    91,    91,    91,    92,    94,    96,
      98,    98,   100,   104,   106,   106,   108,   108,   110,   112,
     112,   114,   116,   127,   129,   132,   136,   138,   143,   145,
     145,   147,   160,   164,   168,   170,   174,   176,   180,   180,
     182,   190,   194,   196,   196,   198,   200,   204,   206,   208,
     210,   214,   216,   218,   222,   228,   230,   230,   233,   235,
     237,   237,   239,   239,   243,   248,   253,   255,   255,   257,
     268,   272,   274,   278,   282,   282,   284,   284,   284,   286,
     292,   297,   304,   308,   310,   311,   313,   320,   320,   322,
     322,   326,   326,   328,   336,   340,   350,   350,   352,   356,
     362,   364,   364,   366,   372,   372,   374,   378,   378,   380,
     384
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "END", "error", "$undefined", "INT", "FLOAT", "STRING", "NAME",
  "PARAMETER", "DEFINE", "DOMAIN", "TYPES", "PREDICATES", "ACTION",
  "PARAMETERS", "PRECONDITION", "EFFECT", "PROBLEM", "TIMES",
  "CONCURRENCYEXEPTIONS", "COLON_DOMAIN", "COLON_OBJECTS", "COLON_INIT",
  "COLON_GOAL", "COLON", "SEMICOLON", "COLON_PROBLEM", "COLON_TIMES",
  "COLON_COMMAND", "COLON_DURATION", "COLON_ACTIONNOCONCUR", "ACTORS",
  "COLON_ACTORS", "COLON_ACTOR", "COLON_ACTIONS", "COLON_ACTORTYPE",
  "COLON_CONF_FILE", "LB", "RB", "LP", "RP", "DASH", "AND", "NOT",
  "STATEMACHINES", "COLON_STATEMACHINES", "COLON_STATEMACHINE",
  "COLON_STATES", "COLON_STATELISTING", "COLON_STATE", "COLON_ONENTRY",
  "COLON_MESSAGE", "CR", "$accept", "start", "state_machines",
  "state_machines_block", "state_machine_list",
  "state_machine_action_name", "state_list_heading", "state_list",
  "message_block_option", "message_block", "on_entry_option",
  "on_entry_block", "state", "state_listing", "state_machine",
  "state_machines_name", "actors", "actors_name_domain", "actors_listing",
  "actor_list", "actor", "conf_file", "actor_type", "actor_action_list",
  "actors_name", "concurrency_exceptions", "concurrency_exceptions_name",
  "action_noconcur_list", "action_noconcur", "time", "time_list_block",
  "time_item_list", "time_item", "action_block", "command_block",
  "duration_block", "time_name_block", "time_problem_block", "problem",
  "problem_id_objs_init", "problem_id_objs", "problem_id", "problem_goal",
  "problem_goal_predicate", "problem_goal_and_predicate", "problem_init",
  "problem_atomic_predicate_list", "problem_goal_atomic_predicate_list",
  "problem_atomic_predicate", "problem_goal_atomic_predicate",
  "problem_objects", "problem_object_enumeration",
  "problem_object_list_type", "problem_name", "domain",
  "problem_domain_name", "domain_name", "domain_item_list", "domain_item",
  "domain_action", "domain_action_name_parameters_precondition",
  "domain_action_name_parameters", "domain_action_name",
  "domain_action_parameters", "domain_action_precondition",
  "domain_action_effect", "prefix_and_clause",
  "domain_action_predicate_list", "domain_action_predicate",
  "domain_action_unit_predicate", "domain_action_atomic_predicate",
  "domain_action_atomic_predicate_name", "prefix_not_clause",
  "variable_list", "variable_list_item", "domain_types",
  "domain_predicates", "domain_predicate_list", "domain_predicate",
  "name_list", "name_list_item", "parameter_list", "parameter_list_item",
  "parameter", YY_NULL
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
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    53,    53,    53,    53,    54,    55,
      56,    56,    57,    58,    59,    59,    60,    60,    61,    62,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    79,
      80,    81,    82,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    95,    96,    97,
      98,    98,    99,    99,   100,   101,   102,   103,   103,   104,
     105,   106,   107,   108,   109,   109,   110,   110,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   119,   120,
     120,   121,   121,   122,   123,   124,   125,   125,   126,   127,
     128,   129,   129,   130,   131,   131,   132,   133,   133,   134,
     135
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     6,     4,
       2,     0,     4,     4,     2,     0,     1,     0,     4,     1,
       0,     4,     5,     4,     6,     4,     5,     2,     4,     2,
       0,     7,     4,     4,     4,     4,     6,     4,     2,     0,
       5,     7,     4,     2,     0,     5,     5,     4,     5,     4,
       4,     5,     2,     2,     2,     4,     1,     1,     4,     4,
       2,     0,     2,     0,     4,     4,     4,     2,     0,     3,
       4,     5,     4,     4,     2,     0,     1,     1,     1,     5,
       2,     2,     1,     4,     2,     2,     4,     2,     0,     1,
       1,     1,     1,     4,     1,     4,     2,     0,     1,     4,
       4,     2,     0,     4,     2,     0,     1,     2,     0,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     6,     5,     4,     3,     2,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    39,     0,     0,     0,     0,    52,     0,
      53,    54,     0,     0,    75,    78,    76,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    26,     0,
       0,    39,     0,     0,     0,    51,    61,    68,   105,   102,
       0,    71,    74,    73,    70,    49,    37,    35,    25,     0,
      11,     8,     0,     0,    30,     0,    36,    38,     0,     0,
       0,     0,     0,    57,    56,     0,     0,    61,   106,     0,
      68,     0,   105,     0,     0,     0,   102,    82,     0,     0,
       0,    72,     0,     0,    11,     0,    28,    29,     0,     0,
      44,    41,   105,    63,    55,   105,    59,    60,    66,    67,
       0,   104,    99,   108,   100,   101,     0,     0,     0,    80,
       0,    81,     0,     9,    10,     0,     0,    50,     0,     0,
      44,     0,     0,     0,    63,     0,    69,   110,     0,   108,
       0,     0,    90,    85,    89,    91,    92,    79,    84,   108,
       0,     0,     0,     0,    40,     0,     0,    42,    43,    65,
      58,    62,    64,   103,   107,     0,    94,    88,     0,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,    88,     0,     0,    98,     0,    97,    83,     0,
     105,     0,     0,     0,     0,     0,     0,   105,     0,     0,
       0,    86,    87,    95,    93,    96,    12,     0,    15,    24,
      33,     0,   105,    31,     0,     0,     0,    45,    23,     0,
       0,    15,    32,     0,    46,    47,     0,     0,    13,    14,
      34,     0,    20,    48,     0,     0,    19,    17,    22,     0,
       0,    16,     0,    21,     0,    18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    56,   113,   171,   212,   240,   260,   261,
     255,   256,   241,   193,   114,    12,     4,    13,    31,    83,
      84,   196,   173,   216,    14,     5,    15,    60,    61,     6,
      90,   149,   150,   176,   199,   220,    16,    63,     7,    17,
      18,    19,    36,    92,    93,    38,    96,   153,    97,   154,
      40,    99,   100,    20,     8,    29,    21,    43,    44,    45,
     108,   109,   110,   141,   139,   137,   162,   201,   202,   164,
     165,   189,   166,   206,   207,    46,    47,   105,   106,   101,
     102,   158,   159,   160
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -152
static const yytype_int16 yypact[] =
{
     -26,     8,    17,  -152,  -152,  -152,  -152,  -152,  -152,   -16,
    -152,    -3,   -15,   -14,   -15,   -15,   -15,   -12,   -10,    -9,
     -15,    -8,    25,    26,    27,    29,    36,    37,    28,     6,
      14,     7,  -152,    10,    11,    30,    12,    32,  -152,    35,
    -152,  -152,    -1,    19,    -8,  -152,  -152,  -152,    20,    21,
      22,    23,    24,    31,    44,    33,    34,    18,  -152,    38,
      39,    10,    40,    41,    42,  -152,    43,     1,    58,    45,
      60,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,    46,
      48,  -152,    50,    49,    18,    62,  -152,  -152,    63,    61,
      51,    -2,    52,  -152,  -152,    65,    53,    43,  -152,    54,
       1,    55,    58,    57,    66,    59,    45,  -152,    69,    75,
      81,  -152,    56,    64,    48,    68,  -152,  -152,    70,    67,
      71,  -152,    58,    72,  -152,    58,  -152,  -152,  -152,  -152,
      91,  -152,  -152,    92,  -152,  -152,    73,    74,    73,  -152,
      76,  -152,    77,  -152,  -152,    78,    79,  -152,    82,    80,
      71,    83,    94,    84,    72,    85,  -152,  -152,    86,    92,
      87,    -5,  -152,  -152,  -152,  -152,  -152,  -152,  -152,    92,
      90,    88,    95,    93,  -152,    96,    97,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,    98,  -152,    73,    99,   100,
      89,   106,   101,   102,   111,   103,   105,   115,   107,   108,
    -152,   112,    73,    -4,   113,  -152,   114,   100,  -152,   116,
      58,   104,   117,   118,   124,   121,   119,    58,   126,    47,
     120,  -152,  -152,  -152,  -152,  -152,  -152,   122,   109,  -152,
    -152,   123,    58,  -152,   127,   128,   129,  -152,  -152,   125,
     130,   109,  -152,   131,  -152,  -152,   132,   133,  -152,  -152,
    -152,   135,   134,  -152,   136,   137,  -152,   139,  -152,   110,
     140,  -152,   138,  -152,   141,  -152
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,   142,  -152,  -152,  -136,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,   143,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,   144,  -152,  -152,
    -152,    13,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,   145,   -13,  -152,   146,
    -152,   147,  -152,  -152,  -152,     5,  -152,   148,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,   -57,  -133,   -23,
    -152,  -152,  -152,   -39,  -152,  -152,  -152,   149,  -152,   -68,
    -152,  -151,  -152,  -152
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -106
static const yytype_int16 yytable[] =
{
     103,   186,   186,   163,   122,   168,    22,    98,   184,    68,
      69,    70,     1,    23,    24,    25,     9,    10,   190,    32,
      33,    34,    11,    28,    30,    41,    35,    26,    37,    39,
      42,    48,    49,    50,   131,    51,   187,   188,   188,   123,
      27,  -105,    52,    53,    55,    57,    58,    54,    59,    62,
      79,    65,    64,    66,   151,    67,    82,   155,    71,    73,
      74,    75,    76,    77,    98,    88,   107,    85,   118,   119,
      78,   125,   133,    81,   145,   236,   146,    80,    86,    89,
      91,    95,   115,   104,   136,   111,   112,   120,   116,   138,
     121,   124,   126,   128,   140,   130,   132,   156,   134,   157,
     122,   142,   191,   143,   200,   249,   147,   205,   197,   148,
     152,   161,   209,   167,   169,   170,   172,   213,   174,   177,
     175,   217,   179,   180,   182,   183,   192,   185,   208,   194,
     231,   195,   235,   246,   218,   198,   251,   203,   214,   252,
     211,   181,   227,   215,   264,   222,   219,   239,   210,   234,
     228,   221,   223,   224,   232,   226,   229,   230,   233,   237,
     262,   238,   242,   178,   243,   204,   244,   245,   225,   248,
     250,     0,   254,   247,   253,     0,   258,   259,     0,   263,
     265,     0,     0,     0,     0,   257,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,     0,     0,     0,     0,   129,     0,     0,
       0,     0,     0,     0,     0,   135,   144
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      68,     6,     6,   136,     6,   138,     9,     6,   159,    10,
      11,    12,    38,    16,    17,    18,     8,     0,   169,    14,
      15,    16,    38,    38,    38,    20,    38,    30,    38,    38,
      38,     6,     6,     6,   102,     6,    41,    42,    42,    41,
      43,    40,     6,     6,    38,    31,    39,    19,    38,    38,
       6,    39,    22,    21,   122,    20,    38,   125,    39,    39,
      39,    39,    39,    39,     6,    25,     6,    29,     6,     6,
      39,     6,     6,    39,     6,    28,     6,    44,    39,    38,
      38,    38,    32,    38,    15,    39,    38,    26,    39,    14,
      39,    39,    39,    39,    13,    40,    39,     6,    39,     7,
       6,    45,    12,    39,     6,   241,    39,     7,    12,    38,
      38,    38,     6,    39,    38,    38,    38,     6,    39,    39,
      38,     6,    39,    39,    39,    39,    38,    40,    39,    34,
       6,    38,     6,     4,    27,    38,     4,    38,    35,     6,
      38,   154,   210,    38,     6,   202,    38,    38,    47,   217,
      46,    39,    39,    39,    33,    39,    39,    39,    39,    39,
      50,    39,    39,   150,   232,   188,    39,    39,   207,    39,
      39,    -1,    38,    48,    39,    -1,    39,    38,    -1,    39,
      39,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   114
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    53,    54,    68,    77,    81,    90,   106,     8,
       0,    38,    67,    69,    76,    78,    88,    91,    92,    93,
     105,   108,     9,    16,    17,    18,    30,    43,    38,   107,
      38,    70,   107,   107,   107,    38,    94,    38,    97,    38,
     102,   107,    38,   109,   110,   111,   127,   128,     6,     6,
       6,     6,     6,     6,    19,    38,    55,    31,    39,    38,
      79,    80,    38,    89,    22,    39,    21,    20,    10,    11,
      12,    39,   109,    39,    39,    39,    39,    39,    39,     6,
      44,    39,    38,    71,    72,    29,    39,    79,    25,    38,
      82,    38,    95,    96,   101,    38,    98,   100,     6,   103,
     104,   131,   132,   131,    38,   129,   130,     6,   112,   113,
     114,    39,    38,    56,    66,    32,    39,    71,     6,     6,
      26,    39,     6,    41,    39,     6,    39,    98,    39,   103,
      40,   131,    39,     6,    39,   129,    15,   117,    14,   116,
      13,   115,    45,    39,    56,     6,     6,    39,    38,    83,
      84,   131,    38,    99,   101,   131,     6,     7,   133,   134,
     135,    38,   118,   120,   121,   122,   124,    39,   120,    38,
      38,    57,    38,    74,    39,    38,    85,    39,    83,    39,
      39,    99,    39,    39,   133,    40,     6,    41,    42,   123,
     133,    12,    38,    65,    34,    38,    73,    12,    38,    86,
       6,   119,   120,    38,   121,     7,   125,   126,    39,     6,
      47,    38,    58,     6,    35,    38,    75,     6,    27,    38,
      87,    39,   119,    39,    39,   125,    39,   131,    46,    39,
      39,     6,    33,    39,   131,     6,    28,    39,    39,    38,
      59,    64,    39,   131,    39,    39,     4,    48,    39,    59,
      39,     4,     6,    39,    38,    62,    63,    49,    39,    38,
      60,    61,    50,    39,     6,    39
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (YYID (0))

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (YYID (0))
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


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
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
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
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 12:
/* Line 1787 of yacc.c  */
#line 100 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 127 "planscan.y"
    {}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 132 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 136 "planscan.y"
    {}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 138 "planscan.y"
    {
	//fillActorTable->setName($1); 
	//fillActorTable->setDomain(domainmap->getDomain($2));
}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 147 "planscan.y"
    {
	fillActorSorter->addActor((yyvsp[(3) - (7)].sval));
	for(int i = 0; i < nameList.size(); i++)
		fillActorSorter->addAction(nameList[i], (yyvsp[(3) - (7)].sval));
	nameList.clear();
	/*
		Actor *actor = fillActorTable->getActor($3, $4, $5);
		for(int i = 0; i < nameList.size(); i++)
			actor->registerAction(nameList[i]);
		nameList.clear();
	*/
}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 160 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 164 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 170 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 174 "planscan.y"
    {}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 176 "planscan.y"
    {
	//cout << "concurrency_exceptions_name" << endl;
}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 180 "planscan.y"
    {}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 182 "planscan.y"
    {
	int l = fillDomain->actions().resolveIndex((yyvsp[(3) - (5)].sval));
	int r = fillDomain->actions().resolveIndex((yyvsp[(4) - (5)].sval));
	fillDomain->NCT().add(l, r);
	//noConcurLeft.push_back(l);
	//noConcurRight.push_back(r);
}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 190 "planscan.y"
    {
	//cout << $4 << "	" << $5 << endl;
}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 200 "planscan.y"
    {
	//ParamList &pl = 
}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 206 "planscan.y"
    { cout << (yyvsp[(4) - (5)].fval) << endl;}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 208 "planscan.y"
    {	cout << (yyvsp[(3) - (4)].sval) << endl;	}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 210 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 216 "planscan.y"
    {}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 218 "planscan.y"
    {
	fillProblem->getPSPT().preCacheAllPermutes(fillProblem);
}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 222 "planscan.y"
    {
	fillDomain = domainmap->getDomain((yyvsp[(2) - (2)].sval));
	fillProblem = fillDomain->newProblem((yyvsp[(1) - (2)].sval));
	//cout << fillProblem->getName() << endl;
}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 228 "planscan.y"
    {}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 230 "planscan.y"
    {}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 233 "planscan.y"
    {}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 235 "planscan.y"
    {}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 243 "planscan.y"
    {
	fillProblem->getRootState().init((yyvsp[(2) - (4)].sval), nameList);
	nameList.clear();
}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 248 "planscan.y"
    {
	fillProblem->getGoalState().init((yyvsp[(2) - (4)].sval), nameList);
	nameList.clear();
}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 253 "planscan.y"
    {}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 257 "planscan.y"
    {
	/*
	for(int i = 0; i < nameList.size(); i++)
		cout << "	" << nameList[i] << endl;
	cout << "	-	" << $3 << endl;
	*/
	//cout << fillProblem->getName() << endl;
	fillProblem->getObjectTable().populateObjects(nameList, (yyvsp[(3) - (3)].sval));
	nameList.clear();
}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 268 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 272 "planscan.y"
    {}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 274 "planscan.y"
    {
	(yyval.sval) = (yyvsp[(3) - (4)].sval);
}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 278 "planscan.y"
    {
	fillDomain = domainmap->newDomain((yyvsp[(3) - (4)].sval));
}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 286 "planscan.y"
    {
	fillAction->setEffect(predList[0], true);
	predList.clear();
}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 292 "planscan.y"
    {
	fillAction->setPrecondition(predList[0], true);
	predList.clear();
}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 297 "planscan.y"
    {
	fillAction = fillDomain->actions().insert(newActionname, nameList,
		typeList);
	nameList.clear();
	typeList.clear();
}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 304 "planscan.y"
    {
	newActionname = (yyvsp[(1) - (1)].sval);
}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 308 "planscan.y"
    {}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 310 "planscan.y"
    {}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 311 "planscan.y"
    {}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 313 "planscan.y"
    {
	AndActionPredicate *andPred = new AndActionPredicate(predList, true);
	predList.clear();
	predList.push_back(andPred);
	//andPred->printContents();
}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 320 "planscan.y"
    {}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 322 "planscan.y"
    {
	predList.clear();
}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 326 "planscan.y"
    {}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 328 "planscan.y"
    {
	AtomicActionPredicate *pred =
		fillAction->createActionPredicate(newActionname, nameList);
	predList.push_back(pred);
	nameList.clear();
	//pred->printContents();
}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 336 "planscan.y"
    {
	newActionname = (yyvsp[(1) - (1)].sval);
}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 340 "planscan.y"
    {
	ActionPredicate *pred = predList[predList.size() - 1];
	predList.pop_back();
	//predList.clear();
	NotActionPredicate *notPred = new NotActionPredicate(pred, true);
	predList.push_back(notPred);
	//pred->printContents();
	//notPred->printContents();
}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 352 "planscan.y"
    {
	nameList.push_back((yyvsp[(1) - (1)].sval));
}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 356 "planscan.y"
    {
	for(int i = 0; i < nameList.size(); i++)
		fillDomain->types().insert(nameList[i]);
	nameList.clear();
}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 364 "planscan.y"
    {}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 366 "planscan.y"
    {
	fillDomain->predicates().insert((yyvsp[(2) - (4)].sval), nameList, typeList);
	nameList.clear();
	typeList.clear();
}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 374 "planscan.y"
    {
	nameList.push_back((yyvsp[(1) - (1)].sval));
}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 380 "planscan.y"
    {
	typeList.push_back((yyvsp[(3) - (3)].sval));
}
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 384 "planscan.y"
    {
	nameList.push_back((yyvsp[(1) - (1)].sval));
}
    break;


/* Line 1787 of yacc.c  */
#line 2366 "planscan.tab.c"
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
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

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if 1
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
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 388 "planscan.y"


void yyerror(const char *s) {
	cout << "Error:	" << s << endl;
	abort();
	exit(-1);
}
