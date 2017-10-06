#include "planstatetable.h"
#include "planstate.h"

#include <iostream>

PlanStateTable::PlanStateTable() : _stateCtr(0) {}
PlanStateTable::~PlanStateTable() {}

int PlanStateTable::stateExists(PlanState &p) {
	int retVal = -1;
	for(int i = 0; ((i < _committed.size()) && (retVal == -1)); i++)
		if(_committed[i]->equals(p)) retVal = i;
	return retVal;
}

int PlanStateTable::addCopyOrReturnExisting(PlanState *p) {
	int extantState = stateExists(*p);
	if(extantState == -1) {
		PlanState *ps = new PlanState(p);
		_committed.push_back(ps);
		ps->setIndex(extantState = _stateCtr++);
	} else {
		//delete p;
	}

	return extantState;
}

int PlanStateTable::addOrReturnExistingAndDelete(PlanState *p) {
	int extantState = stateExists(*p);
	if(extantState == -1) {
		_committed.push_back(p);
		p->setIndex(extantState = _stateCtr++);
	} else {
		delete p;
	}

	return extantState;
}

int PlanStateTable::add(PlanState *p) {
	int extantState = -1;
	_committed.push_back(p);
	p->setIndex(extantState = _stateCtr++);
	return extantState;
}

int PlanStateTable::getNumStates() {
	return _committed.size();
}

PlanState &PlanStateTable::getState(int index) {
	//cout << "PlanStateTable::getState:	" << index << "	" << _committed.size()
	//	<< endl;
	return *_committed[index];
}

void PlanStateTable::printStates() {
	for(int i = 0; i < _committed.size(); i++) {
		cout << "STATE:	" << i << endl;
		_committed[i]->printContents();
	}
}
