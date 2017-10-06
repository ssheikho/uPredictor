#include "concurrentplantable.h"
#include "concurrentplan.h"
#include "plantable.h"

ConcurrentPlanTable::ConcurrentPlanTable() {
	//ConcurrentPlan::populatePlans(plans, _concurrentPlans, _cat);
	////JWH This is the wrong place to do this.. I should change this.
	//for(int i = 0; i < _plans.size(); i++) {
	//	ConcurrentPlan c(&_plans.get(i));
	//}

}
ConcurrentPlanTable::~ConcurrentPlanTable() {}

int ConcurrentPlanTable::getNumberConcurrentPlans() {
	return _concurrentPlans.size();
}

ConcurrentPlan &ConcurrentPlanTable::getConcurrentPlan(int index) {
	return *_concurrentPlans[index];
}

void ConcurrentPlanTable::clear() {
	for(int i = 0; i < _concurrentPlans.size(); i++) {
		delete _concurrentPlans[i];
	}
	_concurrentPlans.clear();
}

void ConcurrentPlanTable::populate(PlanTable &plans) {
	clear();
	ConcurrentPlan::populatePlans(plans, _concurrentPlans, _cat);
}
