#include "smcpersonactor.h"
#include "paramlist.h"

#include <cstdlib>
#include <iostream>

using namespace std;

SMCPersonActor::SMCPersonActor(PFPerson &person, string name, int id,
	ActionToActor &ata, WorldModel &wm) : Actor(name, id, ata, wm),
	_person(person) {}
SMCPersonActor::~SMCPersonActor() {}

void SMCPersonActor::execute(ParamList *pl) {
	cout << "NOTHING ACTUALLY HAPPENED:	";
	pl->printContents();
}

void SMCPersonActor::configure() {}
