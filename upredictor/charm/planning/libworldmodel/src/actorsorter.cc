#include "actorsorter.h"
#include "actoreventline.h"
#include "actorplan.h"
#include "concurrentplan.h"
#include "concurrentplangrid.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "plan.h"
#include "planstate.h"
#include "worldmodel.h"

#include <iostream>

using namespace std;

ActorSorter::ActorSorter() : _nActors(0), _plt(NULL) {}

ActorSorter::~ActorSorter() {}

void ActorSorter::addActor(string name) {
	_actorMap[name] = _nActors;
	_actorReverseMap[_nActors] = name;
	_nActors++;
}

void ActorSorter::addAction(string action, string actor) {
	_actionToActor[action] = _actorMap[actor];
}

void ActorSorter::processPLT(ParamListTable *plt) {
	_plt = plt;
	for(int i = 0; i < plt->size(); i++) {
		ParamList &pl =  plt->getPL(i);		
		Action &act = pl.getAction();
		int actor = _actionToActor[act.getName()];
		_plToActor[pl.getIndex()] = actor;
	}
}

ActorPlan *ActorSorter::processPlan(Plan *p, WorldModel &wm) {
	ActorPlan *retVal = generateAP(p);

	for(int i = 0; i < (p->getNStates() - 1); i++) {
		int paramList = p->getParamList(i);
		ParamList *pl = &_plt->getPL(paramList);
		int act = _plToActor[paramList];
		ActorEventLine *eel = retVal->getAEL(act);
		eel->add(pl);
	}

	return retVal;
}

ActorPlan *ActorSorter::generateAP(Plan *p) {
	ActorPlan *ap = new ActorPlan(p);

	for(map<int, string>::iterator i = _actorReverseMap.begin();
		i != _actorReverseMap.end(); i++) {
		ap->addAEL(i->first, new ActorEventLine(i->second));
	}

	return ap;
}

/*
ActorPlan *ActorSorter::generateAP(ConcurrentPlan *cp) {
	ActorPlan *ap = new ActorPlan(cp);
	//_actors.push_back();
	ap->addAEL(new ActorEventLine("Robot"));
	ap->addAEL(new ActorEventLine("Person"));
	return ap;
}
*/

void ActorSorter::printContents() {
	cout << "Actors:" << endl;
	for(map<string, int>::iterator i = _actorMap.begin(); i != _actorMap.end();
		i++) {
		cout << "	Actor:	" << i->first << endl;
	}

	cout << "Actions:" << endl;
	for(map<string, int>::iterator i = _actionToActor.begin();
		i != _actionToActor.end(); i++) {
		cout << _actorReverseMap[i->second] << "	:	" << i->first << endl;
	}
}

//REPLAN, FROM PLANS, USE CURRENT WORLD STATE, RATHER THAN PREVIOUS.  CHECK IF
//	ACTIONS ARE THE SAME, IE, CHECK THE TIMER FOR THE NEXT STATE ON BOTH QUEUES
//	IF IT IS THE SAME THING, KEEP GOING.  IF NOT, KILL, CREDIT THE CURRENT TIME
//	ELAPSED TO THE NEW ACTION, THEN CONTINUE PROCESSING.

//Briefly, this will operate the timer, accept plans, match them against its
//	internal structure, fit them, then feed them to the appropriate playback
//	mechanism, rather than having the plan play back directly.
