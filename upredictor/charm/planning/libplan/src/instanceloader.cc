#include "instanceloader.h"

#include "planscan.tab.h"

#include <cstdio>

using namespace std;

extern DomainMap *domainmap;
extern ActorSorter *fillActorSorter;
extern FILE *yyin;

InstanceLoader::InstanceLoader(string domainFile, string problemFile,
	string actorFile) {
	domainmap = &_domains;
	fillActorSorter = &_actorSorter;

	FILE *inDomain = fopen(domainFile.c_str(), "r");
	yyin = inDomain;
	yyparse();
	fclose(inDomain);

	FILE *inProblem = fopen(problemFile.c_str(), "r");
	yyin = inProblem;
	yyparse();
	fclose(inProblem);

	FILE *inActors = fopen(actorFile.c_str(), "r");
	yyin = inActors;
	yyparse();
	fclose(inActors);
}

InstanceLoader::~InstanceLoader() {}

DomainMap &InstanceLoader::getDomains() {
	return _domains;
}

ActorSorter &InstanceLoader::getAS() {
	return _actorSorter;
}
