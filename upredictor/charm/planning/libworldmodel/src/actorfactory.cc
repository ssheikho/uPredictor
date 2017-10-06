#include "actorfactory.h"
#include "autoactor.h"
#include "printactor.h"

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

ActorFactory::ActorFactory(WorldModel &wm) : _wm(wm) {}
ActorFactory::~ActorFactory() {}

Actor *ActorFactory::getActor(
	ActionToActor &ata, string name, int id, string type, string configfile) {
	cout << "ActorFactory::getActor:	" << name << "	" << type << endl;
	Actor *retVal = NULL;

	if(strcmp(type.c_str(), "AutoActor") == 0) {
		retVal = new AutoActor(name, id, ata, _wm);
	} else if(strcmp(type.c_str(), "PrintActor") == 0) {
		retVal = new PrintActor(name, id, ata, _wm);
	}

	return retVal;
}

/*
	#include "smcconnection.h"
	#include "smcpersonactor.h"
	#include "smcresponseactor.h"

	, SMCEMT &emt, SMCConnection &smc, PFPerson &person

	else if(strcmp(type.c_str(), "SMCResponseActor") == 0) {
		SMCResponseActor *respAct =
			new SMCResponseActor(name, id, ata, _wm, _emt, _smc);
		_smc.addMessageHandler(respAct);
		retVal = respAct;
	} else if(strcmp(type.c_str(), "SMCPersonActor") == 0) {
		retVal = new SMCPersonActor(_person, name, id, ata, _wm);
	}

	, _emt(emt), _smc(smc), _person(person)
*/
