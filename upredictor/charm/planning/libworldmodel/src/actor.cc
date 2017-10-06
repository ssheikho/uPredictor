#include "actor.h"
#include "actiontoactor.h"
#include "paramlist.h"
#include "worldmodel.h"

#include <iostream>

using namespace std;

Actor::Actor(string name, int id, ActionToActor &ata, WorldModel &wm) :
	_name(name), _id(id), _ata(ata), _wm(wm) {}
Actor::~Actor() {}

string Actor::getName() {
	return _name;
}

int Actor::getIndex() {
	return _id;
}

void Actor::registerAction(string action) {
	//cout << "Actor::registerAction:	" << _name << "	" << action << endl;
	_ata.registerAction(_id, action);
}

void Actor::notifyParamList(ParamList *pl) {
	_wm.apply(*pl);
}

/*Check SMC state.  If it was the last state, then continue.  If it is the initial state, reset the planner.

It may be faster for the robot to plan servotoperson, then to deal with the variance timings in handovertoperson


	(:joint-actions
		(:joint-action handOverToPerson
			(:actors robot operator)
			(:notifier robot)
		)
	)

*/
