#include "planlentable.h"
#include "plan.h"
#include "plantable.h"

PlanLenTable::PlanLenTable() {}
PlanLenTable::~PlanLenTable() {}

void PlanLenTable::compile(PlanTable &pt) {
	clear();
	for(int i = 0; i < pt.size(); i++) {
		Plan &p = pt.get(i);
		_m[p.getNStates()].push_back(&p);
	}
}

void PlanLenTable::clear() {
	_m.clear();
}

Plan &PlanLenTable::getFirst() {
	return **_m.begin()->second.begin();
}

int PlanLenTable::size() {
	int retVal = 0;

	for(map<int, vector<Plan *> >::iterator i = _m.begin();
		i != _m.end(); i++) {
		retVal += i->second.size();
	}
	
	return retVal;
}
