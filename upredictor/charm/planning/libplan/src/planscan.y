%{
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

%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":

%define parse.lac full

%union {
	int ival;
	float fval;
	char *sval;
};

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING NAME PARAMETER
%token END 0
%token DEFINE DOMAIN TYPES PREDICATES ACTION PARAMETERS PRECONDITION EFFECT
%token PROBLEM TIMES CONCURRENCYEXEPTIONS
%token COLON_DOMAIN COLON_OBJECTS COLON_INIT COLON_GOAL
%token COLON SEMICOLON COLON_PROBLEM COLON_TIMES COLON_COMMAND COLON_DURATION
%token COLON_ACTIONNOCONCUR
%token ACTORS COLON_ACTORS COLON_ACTOR COLON_ACTIONS COLON_ACTORTYPE
%token COLON_CONF_FILE
%token LB RB LP RP DASH
%token AND NOT
%token STATEMACHINES COLON_STATEMACHINES COLON_STATEMACHINE COLON_STATES
%token COLON_STATELISTING COLON_STATE COLON_ONENTRY COLON_MESSAGE

%token CR

%type <sval> problem_name problem_domain_name time_problem_block actors_name
%type <sval> state_machines_name state_machine_action_name
%type <sval> actor_type conf_file

%start start

//( (:action <ACTION> <NAME_LIST>) (:command <CMD>) (:duration <TIME>) )

%%

start: domain | problem | time | concurrency_exceptions | actors |
	state_machines;

state_machines:LP DEFINE state_machines_name problem_domain_name state_machines_block RP;

state_machines_block: LP COLON_STATEMACHINES state_machine_list RP;

state_machine_list: state_machine state_machine_list | /*empty*/;

state_machine_action_name: LP ACTION NAME RP {
	$$ = $3;
};

state_list_heading:LP COLON_STATES state_list RP;

state_list: state state_list | /*empty*/;

message_block_option: message_block | /*empty*/;

message_block: LP COLON_MESSAGE NAME RP;

on_entry_option: on_entry_block | /*empty*/;

on_entry_block:LP COLON_ONENTRY message_block_option RP;

state: LP
	COLON_STATE NAME
	on_entry_option
	RP;

//message_events_block:;

//mesage_events_list: on_message message_events_List | /*empty*/;

//on_message:;

state_listing: LP COLON_STATELISTING name_list RP {};

state_machine: LP COLON_STATEMACHINE state_machine_action_name state_listing
	state_list_heading RP;

state_machines_name: LP STATEMACHINES NAME RP {
	$$ = $3;
};

actors: LP DEFINE actors_name_domain actors_listing RP {};

actors_name_domain: actors_name problem_domain_name {
	//fillActorTable->setName($1); 
	//fillActorTable->setDomain(domainmap->getDomain($2));
};

actors_listing: LP COLON_ACTORS actor_list RP;

actor_list: actor actor_list | /*empty*/;

actor: LP COLON_ACTOR NAME actor_type conf_file actor_action_list RP {
	fillActorSorter->addActor($3);
	for(int i = 0; i < nameList.size(); i++)
		fillActorSorter->addAction(nameList[i], $3);
	nameList.clear();
	/*
		Actor *actor = fillActorTable->getActor($3, $4, $5);
		for(int i = 0; i < nameList.size(); i++)
			actor->registerAction(nameList[i]);
		nameList.clear();
	*/
};

conf_file:LP COLON_CONF_FILE NAME RP {
	$$ = $3;
};

actor_type:LP COLON_ACTORTYPE NAME RP {
	$$ = $3;
};

actor_action_list: LP COLON_ACTIONS name_list RP;

actors_name: LP ACTORS NAME RP {
	$$ = $3;
};

concurrency_exceptions: LP DEFINE concurrency_exceptions_name problem_domain_name action_noconcur_list RP {};

concurrency_exceptions_name: LP CONCURRENCYEXEPTIONS NAME RP {
	//cout << "concurrency_exceptions_name" << endl;
};

action_noconcur_list: action_noconcur action_noconcur_list | /*empty*/ {};

action_noconcur: LP COLON_ACTIONNOCONCUR NAME NAME RP {
	int l = fillDomain->actions().resolveIndex($3);
	int r = fillDomain->actions().resolveIndex($4);
	fillDomain->NCT().add(l, r);
	//noConcurLeft.push_back(l);
	//noConcurRight.push_back(r);
};

time: LP DEFINE time_name_block problem_domain_name time_problem_block time_list_block RP {
	//cout << $4 << "	" << $5 << endl;
};

time_list_block: LP COLON_TIMES time_item_list RP;

time_item_list: time_item time_item_list | /*empty*/;

time_item: LP action_block command_block duration_block RP;

action_block: LP ACTION NAME name_list RP {
	//ParamList &pl = 
};

command_block: LP COLON_COMMAND NAME RP;

duration_block: LP COLON_DURATION FLOAT FLOAT RP { cout << $4 << endl;};

time_name_block: LP TIMES NAME RP {	cout << $3 << endl;	};

time_problem_block: LP COLON_PROBLEM NAME RP {
	$$ = $3;
};

problem: LP DEFINE problem_id_objs_init problem_goal RP;

problem_id_objs_init: problem_id_objs problem_init {};

problem_id_objs: problem_id problem_objects {
	fillProblem->getPSPT().preCacheAllPermutes(fillProblem);
};

problem_id: problem_name problem_domain_name {
	fillDomain = domainmap->getDomain($2);
	fillProblem = fillDomain->newProblem($1);
	//cout << fillProblem->getName() << endl;
};

problem_goal: LP COLON_GOAL problem_goal_predicate RP {};

problem_goal_predicate: problem_goal_atomic_predicate | problem_goal_and_predicate {};

problem_and_predicate: LP AND problem_atomic_predicate_list RP {};
problem_goal_and_predicate: LP AND problem_goal_atomic_predicate_list RP {};

problem_init: LP COLON_INIT problem_atomic_predicate_list RP {};

problem_atomic_predicate_list: problem_atomic_predicate problem_atomic_predicate_list | /*empty*/;

problem_goal_atomic_predicate_list: problem_goal_atomic_predicate problem_goal_atomic_predicate_list | /*empty*/;

problem_predicate: LP NAME name_list RP;

problem_atomic_predicate: LP NAME name_list RP {
	fillProblem->getRootState().init($2, nameList);
	nameList.clear();
};

problem_goal_atomic_predicate: LP NAME name_list RP {
	fillProblem->getGoalState().init($2, nameList);
	nameList.clear();
};

problem_objects: LP COLON_OBJECTS problem_object_enumeration RP {};

problem_object_enumeration: problem_object_list_type problem_object_enumeration | /*empty*/;

problem_object_list_type: name_list DASH NAME {
	/*
	for(int i = 0; i < nameList.size(); i++)
		cout << "	" << nameList[i] << endl;
	cout << "	-	" << $3 << endl;
	*/
	//cout << fillProblem->getName() << endl;
	fillProblem->getObjectTable().populateObjects(nameList, $3);
	nameList.clear();
};

problem_name: LP PROBLEM NAME RP {
	$$ = $3;
};

domain: LP DEFINE domain_name domain_item_list RP {};

problem_domain_name: LP COLON_DOMAIN NAME RP {
	$$ = $3;
};

domain_name: LP DOMAIN NAME RP {
	fillDomain = domainmap->newDomain($3);
};

domain_item_list: domain_item domain_item_list | /*empty*/;

domain_item: domain_types | domain_predicates | domain_action;

domain_action: LP ACTION domain_action_name_parameters_precondition domain_action_effect RP {
	fillAction->setEffect(predList[0], true);
	predList.clear();
};


domain_action_name_parameters_precondition: domain_action_name_parameters domain_action_precondition {
	fillAction->setPrecondition(predList[0], true);
	predList.clear();
};

domain_action_name_parameters: domain_action_name domain_action_parameters {
	fillAction = fillDomain->actions().insert(newActionname, nameList,
		typeList);
	nameList.clear();
	typeList.clear();
};

domain_action_name: NAME {
	newActionname = $1;
};

domain_action_parameters: PARAMETERS LP parameter_list RP {};

domain_action_precondition: PRECONDITION domain_action_predicate {};
domain_action_effect: EFFECT domain_action_predicate {};

prefix_and_clause: LP AND domain_action_predicate_list RP {
	AndActionPredicate *andPred = new AndActionPredicate(predList, true);
	predList.clear();
	predList.push_back(andPred);
	//andPred->printContents();
};

domain_action_predicate_list: domain_action_predicate domain_action_predicate_list | /*empty*/ {};

domain_action_predicate: domain_action_unit_predicate | prefix_and_clause {
	predList.clear();
};

domain_action_unit_predicate: domain_action_atomic_predicate | prefix_not_clause {};

domain_action_atomic_predicate: LP domain_action_atomic_predicate_name variable_list RP {
	AtomicActionPredicate *pred =
		fillAction->createActionPredicate(newActionname, nameList);
	predList.push_back(pred);
	nameList.clear();
	//pred->printContents();
};

domain_action_atomic_predicate_name: NAME {
	newActionname = $1;
};

prefix_not_clause: LP NOT domain_action_unit_predicate RP {
	ActionPredicate *pred = predList[predList.size() - 1];
	predList.pop_back();
	//predList.clear();
	NotActionPredicate *notPred = new NotActionPredicate(pred, true);
	predList.push_back(notPred);
	//pred->printContents();
	//notPred->printContents();
};

variable_list: variable_list_item variable_list | /*empty*/;

variable_list_item: PARAMETER {
	nameList.push_back($1);
};

domain_types: LP TYPES name_list RP {
	for(int i = 0; i < nameList.size(); i++)
		fillDomain->types().insert(nameList[i]);
	nameList.clear();
};

domain_predicates: LP PREDICATES domain_predicate_list RP;

domain_predicate_list: domain_predicate domain_predicate_list | /*empty*/ {};

domain_predicate: LP NAME parameter_list RP {
	fillDomain->predicates().insert($2, nameList, typeList);
	nameList.clear();
	typeList.clear();
};

name_list: name_list_item name_list | /*empty*/;

name_list_item: NAME {
	nameList.push_back($1);
};

parameter_list: parameter_list_item parameter_list | /*empty*/;

parameter_list_item: parameter DASH NAME {
	typeList.push_back($3);
};

parameter: PARAMETER {
	nameList.push_back($1);
};

%%

void yyerror(const char *s) {
	cout << "Error:	" << s << endl;
	abort();
	exit(-1);
}
