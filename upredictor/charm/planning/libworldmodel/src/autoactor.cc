#include "autoactor.h"
#include "paramlist.h"

#include <iostream>

using namespace std;

AutoActor::AutoActor(string name, int id, ActionToActor &ata, WorldModel &wm) :
	Actor(name, id, ata, wm) {}
AutoActor::~AutoActor() {}

void AutoActor::execute(ParamList *pl) {
	cout << "ACTOR:	" << _name << "	EXECUTING:	";
	pl->printContents(true);
	notifyParamList(pl);
}

void AutoActor::configure() {
	cout << "ACTOR:	TYPE:	AutoActor	" << _name << "	CONFIGURING";
}
