#include "concurrentplan.h"
#include "concurrentplanconcurrency.h"
#include "concurrentplanline.h"
#include "concurrentplanstep.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "plan.h"
#include "plannerutil.h"
#include "planninggraph.h"
#include "planstate.h"
#include "planstatetable.h"

#include <cstdlib>
#include <iostream>

/*
JWH

The algorithm is as follows:
	1)  Check against the root state.  If the action works, then it is a
			candidate to start it's own concurrent timeline.
	2)  It remains a candidate if none of the existing concurrent timelines
			interfere with it.  This is to say, if the state works for every
			state of every other timeline.
	3)  If it is still a candidate after step 2, then it becomes the root of its
			own timeline.
	4)  If it is not a candidate after step 2, but works at the end of exactly
			one existing timeline, then it may be appended to the end of that
			timeline.
	5)  If it is not a candidate after step 2, but works at the end of more than
			one timeline, then the entire concurrent plan must be replicated and
			formed into two concurrent plans
	6)  If it is not a candidate after step 2, and works at the end of no
			timelines, then it is a point at which multiple timelines must
			merge.

	If Step 6), then:
	1)  Identify the timelines to be merged by running all of their actions
			against the root state.  Any working combination of timelines shall
			be formed into its own concurrent plan, which replaces those two
			timelines with its own timeline.
	2)  If it is all current timelines, then all of those timelines end and are
			combined into a single concurrent plan.  That concurrent plan
			becomes a node in a larger concurrent plan.
*/

ConcurrentPlan::ConcurrentPlan(Plan *plan, ConcurrentActionTable &cat) :
	_plan(plan), _cat(cat),
	_pg(_plan->getPlanningGraph()), _plt(_pg.getPLT()), _pst(_pg.getPST()),
	_currentInsertion(0),
	_concurrency(
		new ConcurrentPlanConcurrency(this, 
			&_pst.getState(plan->getState(0)))),
	_crazyCakes(false) {}
	/*
	_concurrency =
		);

	for(int i = 0; i < (plan->getNStates() - 1); i++) {
		insert(plan->getParamList(i));
	}
	*/


ConcurrentPlan::~ConcurrentPlan() {}

int ConcurrentPlan::insertNextPlanState(vector<ConcurrentPlan *> &inProgress) {
	int retVal = ConcurrentPlanStep::INSERT_STATUS_NOT_INSERTED;
	int paramList = _plan->getParamList(_currentInsertion++);
	//_plan->printContents();
	while(retVal = insert(paramList, inProgress) ==
			ConcurrentPlanStep::INSERT_STATUS_NOT_INSERTED) {
		//if(_crazyCakes)
		//	cout << "OMG" << endl;
	}
	//if(!inserted) {
	//	
	//}
	return retVal;
}

bool ConcurrentPlan::hasNextInsertion() {
	return _currentInsertion < (_plan->getNStates() - 1);
}

int ConcurrentPlan::insert(int paramList,
	vector<ConcurrentPlan *> &inProgress) {
	int insertedIntoConcurrency = _concurrency->insert(paramList, inProgress);
	if(insertedIntoConcurrency == ConcurrentPlanStep::INSERT_STATUS_NOT_INSERTED) {
		//cout << "ConcurrentPlan::INSERT_STATUS_NOT_INSERTED" << endl;
		//_plt.getPL(paramList).printContents(true);
		//ConcurrentPlanLine *cpl =
		//	new ConcurrentPlanLine(this, _concurrency->getRootState());
		//cpl->addPlanStep(_concurrency);
		ConcurrentPlanConcurrency *_oldConcur = _concurrency;
		_concurrency =
			new ConcurrentPlanConcurrency(this, _concurrency->getRootState());
		_concurrency->getTimeline(0)->addPlanStep(_oldConcur);
	} else if(insertedIntoConcurrency ==
		ConcurrentPlanStep::INSERT_STATUS_SKIP) {
		//cout << "ConcurrentPlan::INSERT_STATUS_SKIP" << endl;
		//_plt.getPL(paramList).printContents(true);
		//ConcurrentPlanLine *cpl =
		//	new ConcurrentPlanLine(this, _concurrency->getRootState());
		//cpl->addPlanStep(_concurrency);
		ConcurrentPlanConcurrency *_oldConcur = _concurrency;
		_concurrency =
			new ConcurrentPlanConcurrency(this, _concurrency->getRootState());
		_concurrency->getTimeline(0)->addPlanStep(_oldConcur);
	} else if(insertedIntoConcurrency ==
		ConcurrentPlanStep::INSERT_STATUS_INSERT_AT_END) {
		//cout << "ConcurrentPlan::INSERT_STATUS_INSERT_AT_END" << endl;
		//_plt.getPL(paramList).printContents(true);
		//ConcurrentPlanLine *cpl =
		//	new ConcurrentPlanLine(this, _concurrency->getRootState());
		//cpl->addPlanStep(_concurrency);
		ConcurrentPlanConcurrency *_oldConcur = _concurrency;
		_concurrency =
			new ConcurrentPlanConcurrency(this, _concurrency->getRootState());
		_concurrency->getTimeline(0)->addPlanStep(_oldConcur);
	}

	_status = insertedIntoConcurrency;
	return insertedIntoConcurrency;
}

void ConcurrentPlan::populatePlans(PlanTable &pt,
	vector<ConcurrentPlan *> &finished, ConcurrentActionTable &cat) {
	//int i = 0;

	vector<ConcurrentPlan *> inProgress;
	for(int i = 0; i < pt.size(); i++)
		inProgress.push_back(new ConcurrentPlan(&pt.get(i), cat));

	cout << "Compressing Plans:	" << inProgress.size() << endl;
	int hasNext = ConcurrentPlanStep::INSERT_STATUS_INSERTED;
	while(inProgress.size()) {
		//cout << "Compressing Plans	A:	" << inProgress.size() << endl;
		ConcurrentPlan *plan = inProgress.front();
		//if(inProgress.size() == 4759) {
		//	plan->_crazyCakes = true;
		//	plan->getPlan().printContents();
		//}
		inProgress.erase(inProgress.begin());
		//cout << "Compressing Plans	B:	" << inProgress.size() << endl;

		int status = 0;
		while(	(plan->hasNextInsertion()) &&
				(status != ConcurrentPlanStep::INSERT_STATUS_SKIP) &&
				(plan->_status != ConcurrentPlanStep::INSERT_STATUS_SKIP)) {
			//cout << "OMG" << endl;
			status = plan->insertNextPlanState(inProgress);
		}

		if(
			(status != ConcurrentPlanStep::INSERT_STATUS_SKIP) && 
			(plan->_status != ConcurrentPlanStep::INSERT_STATUS_SKIP))
			finished.push_back(plan);
	}

	//while(concurrentPlan->hasNextInsertion())
	//	concurrentPlan->insertNextPlanState();
	
	////JWH This is the wrong place to do this.. I should change this.
	//for(int i = 0; i < _plans.size(); i++) {
	//	ConcurrentPlan c(&_plans.get(i));
	//}
}

ParamListTable &ConcurrentPlan::getPLT() {
	return _plt;
}

ConcurrentActionTable &ConcurrentPlan::getCAT() {
	return _cat;
}

/*
void ConcurrentPlan::printContents() {
	int ts = getNTimeSteps();
}
*/

void ConcurrentPlan::printContents(int actionSpaces, int lineNumber,
	bool cr, int digitsForAction) {
	_concurrency->printContents(actionSpaces, lineNumber,
		cr, digitsForAction);
}

int ConcurrentPlan::getNTimeSteps() {
	return _concurrency->getNTimeSteps();
}

void ConcurrentPlan::label() {
	_concurrency->label(0, 0, 0);
}

void ConcurrentPlan::printGrid() {
	_concurrency->printGrid();
}

ConcurrentPlanGrid *ConcurrentPlan::generateGrid() {
	_concurrency->generateGrid();
}

Plan &ConcurrentPlan::getPlan() {
	return *_plan;
}

double ConcurrentPlan::computePerformanceTime() {
	return _concurrency->computePerformanceTime();
}

double ConcurrentPlan::getPerformanceTime() {
	return _concurrency->getPerformanceTime();
}

int ConcurrentPlan::computeStepLen() {
	return _concurrency->computeStepLen();
}

int ConcurrentPlan::getStepLen() {
	return _concurrency->getStepLen();
}

