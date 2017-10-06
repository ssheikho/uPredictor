#include "concurrentreplanner.h"
#include "planninggraph.h"
#include "planstate.h"
#include "problem.h"

#include <iostream>

using namespace std;

ConcurrentReplanner::ConcurrentReplanner(Problem &problem) :
	_problem(problem), _cptt(_cpt) {
	_problem.generatePG();
}

ConcurrentReplanner::~ConcurrentReplanner() {}

void ConcurrentReplanner::replan(bool showTimes, PlanState *fromState) {
	_sw.resetAndStart();
	_problem.getPG().doPlanning(fromState);
	if(showTimes) {
		_problem.getPG().printSummary();
		cout << "Time to totally-ordered plans:	" << _sw.lap() << " seconds" <<
			endl;
	}

	_sw.resetAndStart();
	_cpt.populate(_problem.getPG().getPlans());
	if(showTimes) {
		cout << "Time to concurrent plans:	" << _sw.lap() << " seconds" <<
			endl;
	}

	_sw.resetAndStart();
	_cptt.update();
	if(showTimes) {
		cout << "Time to best plan:	" << _sw.lap() << " seconds" << endl;
	}

}

Problem &ConcurrentReplanner::getProblem() {
	return _problem;
}

ConcurrentPlanTable &ConcurrentReplanner::getCPT() {
	return _cpt;
}

ConPlanTimeTable &ConcurrentReplanner::getCPTT() {
	return _cptt;
}
