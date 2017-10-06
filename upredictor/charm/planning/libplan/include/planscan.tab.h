/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2053 of yacc.c  */
#line 55 "planscan.y"

	int ival;
	float fval;
	char *sval;


/* Line 2053 of yacc.c  */
#line 116 "planscan.tab.h"
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
