#include "replanner.h"
#include "planninggraph.h"
#include "planstate.h"
#include "problem.h"

#include <iostream>

using namespace std;

Replanner::Replanner(Problem &problem) : _problem(problem) {
	_problem.generatePG();
}

Replanner::~Replanner() {}

void Replanner::replan(bool showTimes, PlanState *fromState) {
	_sw.resetAndStart();
	_problem.getPG().doPlanning(fromState);
	if(showTimes) {
		_problem.getPG().printSummary();
		cout << "Time to totally-ordered plans:	" << _sw.lap() << " seconds" <<
			endl;
	}
	
	/*
	sw.resetAndStart();
	ConcurrentPlanTable cpt(fillPlanningGraph->getPlans());
	cout << "Time to concurrent plans:	" << sw.lap() << " seconds" << endl;

	sw.resetAndStart();
	ConPlanTimeTable cptt(cpt);
	cptt.update();
	cout << "Time to best plan:	" << sw.lap() << " seconds" << endl;

	if(true) {
		ConcurrentPlan *cp = cptt.getFirst();
		cp->label();
		cp->getPlan().printContents();
		cp->printGrid();

		cout << "Time to execute:	" << cp->getPerformanceTime() << endl;
		cout << "Time steps:	" << cp->getStepLen() << endl;
	}

	if(false)
		for(int i = 0; i < cpt.getNumberConcurrentPlans(); i++) {
			cpt.getConcurrentPlan(i).label();
			cpt.getConcurrentPlan(i).getPlan().printContents();
			cpt.getConcurrentPlan(i).printGrid();
		}
	*/

}

Problem &Replanner::getProblem() {
	return _problem;
}
