#include "actorplan.h"
#include "actoreventline.h"
#include "concurrentplan.h"
#include "concurrentplangrid.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "plan.h"
#include "planstate.h"
#include "worldmodel.h"

ActorPlan::ActorPlan(Plan *p) : _p(p), _nSteps(0) {}
//ActorPlan::ActorPlan(ConcurrentPlan *cp) : _p(NULL), _cp(cp), _maxSteps(0) {}
ActorPlan::~ActorPlan() {}

int ActorPlan::getNSteps() {
	return _nSteps;
}

void ActorPlan::setNSteps(int nSteps) {
	_nSteps = nSteps;
}

void ActorPlan::addAEL(int index, ActorEventLine *ael) {
	_actors[index] = ael;
}

ActorEventLine *ActorPlan::getAEL(int index) {
	return _actors[index];
}

Plan *ActorPlan::getPlan() {
	return _p;
}

int ActorPlan::getNActors() {
	return _actors.size();
}

void ActorPlan::printContents() {
	for(int i = 0; i < _actors.size(); i++) {
		_actors[i]->printContents();
	}
}

bool ActorPlan::allNullAt(int index) {
	bool retVal = true;
	for(int i = 0; i < _actors.size(); i++) {
		retVal &= !_actors[i]->actionAtTimeSlot(index);
	}
	return retVal;
}

bool ActorPlan::equals(ActorPlan *ap) {
	bool retVal = ap->_actors.size() == _actors.size();
	for(int i = 0; ((i < _actors.size()) && (retVal)); i++)
		retVal = _actors[i]->equals(ap->_actors[i]);
	return retVal;//_actors[1]->equals(ap->_actors[1]);
}

int ActorPlan::nextKeyFrame(int startAt) {

}
