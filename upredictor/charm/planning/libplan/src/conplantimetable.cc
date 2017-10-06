#include "conplantimetable.h"
#include "concurrentplan.h"
#include "concurrentplantable.h"
#include "conplanlentable.h"

ConPlanTimeTable::ConPlanTimeTable(ConcurrentPlanTable &cpt) : _cpt(cpt) {}

ConPlanTimeTable::~ConPlanTimeTable() {}

void ConPlanTimeTable::clear() {
	for(map<double, ConPlanLenTable *>::iterator i = _m.begin();
		i != _m.end(); i++)
		i->second->clear();
	_m.clear();
}

void ConPlanTimeTable::update() {
	clear();
	for(int i = 0; i < _cpt.getNumberConcurrentPlans(); i++) {
		ConcurrentPlan *p = &_cpt.getConcurrentPlan(i);
		double t = p->computePerformanceTime();
		if(_m.find(t) == _m.end())
			_m[t] = new ConPlanLenTable();
		_m[t]->insert(p);
	}
}

ConcurrentPlan *ConPlanTimeTable::getFirst() {
	return _m.begin()->second->getFirst();
}
