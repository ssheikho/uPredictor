#include "plantable.h"
#include "plan.h"
#include <iostream>

PlanTable::PlanTable() {}
PlanTable::~PlanTable() {}

bool PlanTable::insert(Plan *p, bool checkEquiv, bool checkCycle) {
	bool inTable = false;
	if(checkEquiv) {
		for(int i = 0; ((i < _v.size()) && !inTable); i++)
			inTable = _v[i]->equals(*p);
		if(inTable) {
			cout << "Actually rejected a plan" << endl;
		} else {
			_v.push_back(p);
		}
	} else {
		if(!((checkCycle)&&(p->planHasACycle())))
			_v.push_back(p);
	}

	return !inTable;
}

Plan &PlanTable::get(int index) {
	return *_v[index];
}

int PlanTable::size() {
	return _v.size();
}

void PlanTable::printPlans(int limit) {
	if(limit == -1) limit = _v.size();
	else limit = limit < _v.size() ? limit : _v.size();

	for(int i = 0; i < limit; i++) {
		cout << "PLAN:	" << i << endl;
		_v[i]->printContents();
	}
}

void PlanTable::clear() {
	for(int i = 0; i < _v.size(); i++) delete _v[i];
	_v.clear();
}
