#include "actiontoactor.h"
#include "actionmap.h"
#include "actor.h"
#include "actortable.h"
#include "paramlist.h"

#include <iostream>

ActionToActor::ActionToActor(ActionMap &am, ActorTable *at) :
	_am(am), _at(at) {}
ActionToActor::~ActionToActor() {}

void ActionToActor::registerAction(int actor, string action) {
	Actor *act = _at->getActor(actor);
	int actionIndex = _am.resolveIndex(action);

	//cout << "ActionToActor::registerAction:	" <<
	//	act->getName() << "	" << action << endl;
	
	_m[actionIndex] = act->getIndex();
}

void ActionToActor::execute(ParamList *pl) {
	_at->getActor(_m[pl->getAction().getIndex()])->execute(pl);
}
