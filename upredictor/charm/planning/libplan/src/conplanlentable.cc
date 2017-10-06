#include "conplanlentable.h"
#include "concurrentplan.h"

#include <cstdlib>

ConPlanLenTable::ConPlanLenTable() {}
ConPlanLenTable::~ConPlanLenTable() {}

void ConPlanLenTable::clear() {
	for(map<int, vector<ConcurrentPlan *> >::iterator i = _m.begin();
		i != _m.end(); i++)
		i->second.clear();
}

void ConPlanLenTable::insert(ConcurrentPlan *p) {
	_m[p->computeStepLen()].push_back(p);
}

ConcurrentPlan *ConPlanLenTable::getFirst() {
	ConcurrentPlan *retVal = NULL;
	
	for(map<int, vector<ConcurrentPlan *> >::iterator i = _m.begin();
		((i!= _m.end()) && (!retVal)); i++) {
		if(i->second.size()) {
			retVal = *i->second.begin();
		}
	}

	return retVal;
}
