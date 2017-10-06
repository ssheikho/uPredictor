#include "subplan.h"
#include "plan.h"

SubPlan::SubPlan(Plan *plan, int startStep, int endStep) :
	_plan(plan), _startStep(startStep), _endStep(endStep) {}

SubPlan::~SubPlan() {}

int SubPlan::getState(int index) {
	return _plan->getState(_startStep + index);
}

int SubPlan::getNStates() {
	return _endStep - _startStep;
}
