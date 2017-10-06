c   [a-zA-Z]
a   [a-zA-Z\_\-]
i   [0-9\-]
d   [0-9]

%{
#include <iostream>
using namespace std;
#include "planscan.tab.h"

#define YY_DECL extern "C" int yylex()

extern "C" int yywrap(void) {
	return 1;
}

%}
%%
[0-9]+   		{	yylval.ival = atoi(yytext);
					return INT;										}
[0-9]+\.[0-9]+	{	yylval.fval = strtof(yytext, NULL);		
					return FLOAT;									}
":types"		{	return TYPES;									}
":predicates"	{	return PREDICATES;								}
":action"		{	return ACTION;									}
":parameters"	{	return PARAMETERS;								}
":precondition"	{	return PRECONDITION;							}
":effect"		{	return EFFECT;									}
":domain"		{	return COLON_DOMAIN;							}
":objects"		{	return COLON_OBJECTS;							}
":init"			{	return COLON_INIT;								}
":goal"			{	return COLON_GOAL;								}
"problem"		{	return PROBLEM;									}
":problem"		{	return COLON_PROBLEM;							}
"and"			{	return AND;										}
"not"			{	return NOT;										}
"define"		{	return DEFINE;									}
"domain"		{	return DOMAIN;									}
"times"			{	return TIMES;									}
":times"		{	return COLON_TIMES;								}
":command"		{	return COLON_COMMAND;							}
":duration"		{	return COLON_DURATION;							}

"actors"		{	return ACTORS;									}
":actor"		{	return COLON_ACTOR;								}
":actors"		{	return COLON_ACTORS;							}
":actortype"	{	return COLON_ACTORTYPE;							}
":conffile"		{	return COLON_CONF_FILE;							}

"state-machines"	{	return STATEMACHINES;						}
":state-machines"	{	return COLON_STATEMACHINES;					}
":state-machine"	{	return COLON_STATEMACHINE;					}
":states"			{	return COLON_STATES;						}
":state"			{	return COLON_STATE;							}
":state-listing"	{	return COLON_STATELISTING;					}
":on-entry"			{	return COLON_ONENTRY;						}
":message"			{	return COLON_MESSAGE;						}
":message-events"	{	abort();									}


"concurrency-exceptions"	{	return CONCURRENCYEXEPTIONS;		}
":action-noconcur"			{	return COLON_ACTIONNOCONCUR;		}
":actions"		{	return COLON_ACTIONS;							}

":"				{	return COLON;									}
"{"				{	return LB;										}
"}"				{	return RB;										}
"("				{	return LP;										}
")"				{	return RP;										}
"-"				{	return DASH;									}
"?"{c}({a}|{i})* {
					yylval.sval = yytext;
					return PARAMETER;
				}
[ \t\n]         ;
{c}({a}|{i})*	{	
					yylval.sval = new char[strlen(yytext) + 1];
					strcpy(yylval.sval, yytext);
					//cout << "NAME:	" << yylval.sval << endl;
					return NAME;									}
<<EOF>>  		{	return 0;										}
%%
