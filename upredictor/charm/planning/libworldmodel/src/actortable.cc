#include "actortable.h"
#include "actorfactory.h"
#include "autoactor.h"
#include "printactor.h"
#include "planscan.tab.h"

#include <cstdio>

using namespace std;

extern FILE *yyin;
extern ActorTable *fillActorTable;

ActorTable::ActorTable(ActionMap &am, ActorFactory &af) :
	_af(af),
	_name("YOUVEPROBABLYNEVERHEARDOFTHEM"),
	_domain(NULL), _ata(am, this) {}
ActorTable::~ActorTable() {}

Actor *ActorTable::getActor(string name, string type, string conf) {
	Actor *retVal = NULL;

	if(_m.find(name) == _m.end()) {
		retVal = _af.getActor(_ata, name, _v.size(), type, "CONF");
		_v.push_back(retVal);
		_m[name] = retVal->getIndex();
	} else {
		retVal = _v[_m[name]];
	}

	return retVal;
}

Actor *ActorTable::getActor(int index) {
	return _v[index];
}

void ActorTable::load(string fileName) {
	FILE *inFile = fopen(fileName.c_str(), "r");
	yyin = inFile;

	fillActorTable = this;

	yyparse();
	fclose(inFile);
}

void ActorTable::setName(string name) {
	_name = name;
}

void ActorTable::setDomain(Domain *domain) {
	_domain = domain;
}

ActionToActor &ActorTable::getATA() {
	return _ata;
}
