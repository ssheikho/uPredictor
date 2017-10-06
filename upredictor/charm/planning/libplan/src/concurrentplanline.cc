#include "concurrentplanline.h"
#include "concurrentactiontable.h"
#include "concurrentplan.h"
#include "concurrentplanaction.h"
#include "concurrentplanconcurrency.h"
#include "paramlist.h"

#include <cstdlib>
#include <iostream>

ConcurrentPlanLine::ConcurrentPlanLine(
	ConcurrentPlan *cp, PlanState *rootState) : ConcurrentPlanStep(), _cp(cp),
	_weAppendIntoLastNow(false) {
	//if(!rootState) abort();
	//_states.push_back(new PlanState(rootState));
	_states.push_back(rootState);
	//int rootIdx = rootState->getIndex();
	//if(rootIdx == -1) abort();
	//_states.push_back(rootState->getIndex());
}

ConcurrentPlanLine::~ConcurrentPlanLine() {}
		
int ConcurrentPlanLine::attemptInsertion(
	ParamList &pl, vector<ConcurrentPlan *> &inProgress) {
	int inserted = INSERT_STATUS_NOT_INSERTED;
	if(_weAppendIntoLastNow) {
		inserted = _pls[_pls.size() - 1]->attemptInsertion(pl, inProgress);
		if(inserted) {
			//delete _states.back();
			_states.pop_back();
			ConcurrentPlanStep *cps = _pls.back();
			PlanState *s = cps->doStep(_states.back());
			if(!s) abort();
			_states.push_back(s);
		}
	} else {
		if(actionCanBeAppliedBeforeLast(pl)) {
			splitLastWithThis(pl);
			inserted = INSERT_STATUS_INSERTED;
		} else if (actionCanBeAddedToEnd(pl)) {
			addParamList(pl);
			inserted = INSERT_STATUS_INSERTED;
		}
	}

	return inserted;
}

bool ConcurrentPlanLine::actionCanBeAddedToEnd(ParamList &pl) {
	int size = _states.size();
	PlanState *s = _states[size - 1];
	return s->preconditionsMet(pl);
}

bool ConcurrentPlanLine::doesntInterfere(ParamList &pl) {
	bool retVal = true;

	for(int i = 0; ((i < _pls.size()) && (retVal)); i++) {
		retVal &= _pls[i]->doesntInterfere(pl);
	}

	for(int i = 0; ((i < _states.size()) && retVal); i++) {
		retVal &= _states[i]->preconditionsMet(pl);
	}

	return retVal;
}

bool ConcurrentPlanLine::actionCanBeAppliedBeforeLast(ParamList &pl) {
	bool retVal = false;
	if(	(_states.size() > 2) &&
		(_states[_states.size() - 2]->preconditionsMet(pl)) &&
		(_pls.back()->doesntInterfere(pl))
		)
		retVal = true;
	return retVal;
}

void ConcurrentPlanLine::addPlanStep(ConcurrentPlanStep *cps) {
	addPlanStep(cps, cps->doStep(_states.back()));
}

void ConcurrentPlanLine::addPlanStep(
	ConcurrentPlanStep *cps, PlanState *state) {
	//_paramLists.push_back(pl.getIndex());
	_pls.push_back(cps);
	_states.push_back(state);
}

void ConcurrentPlanLine::addParamList(ParamList &pl) {
	//_paramLists.push_back(pl.getIndex());
	ConcurrentPlanAction *cpa = _cp->getCAT().getPlanStep(pl);
	_pls.push_back(cpa);
	PlanState *s = _states[_states.size() - 1];
	if(!s) abort();
	s = cpa->doAction(s);
	if(!s) abort();
	_states.push_back(s);
}

void ConcurrentPlanLine::splitLastWithThis(ParamList &pl) {
	ConcurrentPlanConcurrency *concurrency =
		new ConcurrentPlanConcurrency(_cp, _states[_states.size() - 2]);

	ConcurrentPlanStep *cps = _pls.back();
	PlanState *ps = _states.back();
	_pls.pop_back();
	_states.pop_back();

	concurrency->getTimeline(0)->addPlanStep(cps, ps);
	concurrency->addTimeline()->addParamList(pl);

	addPlanStep(concurrency);

	_weAppendIntoLastNow = true;
}

void ConcurrentPlanLine::applyToPlanState(PlanState *state) {
	for(int i = 0; i < _pls.size(); i++) _pls[i]->applyToPlanState(state);
}

PlanState *ConcurrentPlanLine::doStep(PlanState *state) {
	PlanState *retVal = state;

	for(int i = 0; i < _pls.size(); i++) {
		//cout << "ConcurrentPlanLine::doStep:	" << i << "	" <<
		//	retVal->getIndex() << endl;
		PlanState *newVal = _pls[i]->doStep(retVal);
		if(newVal == retVal) {
			_pls[i]->printGrid();
			retVal->printContents();
			abort();
		} else {
			retVal = newVal;	
		}
	}

	return retVal;
}

int ConcurrentPlanLine::getType() {
	return line;
}

void ConcurrentPlanLine::printContents(int actionSpaces, int lineNumber,
	bool cr, int digitsForAction) {
	if(actionSpaces == -1) actionSpaces = _pls.size();
	for(int i = 0; i < actionSpaces; i++)
		_pls[i]->printContents(actionSpaces, 0, false, digitsForAction);
	if(cr) cout << endl;
}

int ConcurrentPlanLine::getNTimeSteps() {
	int retVal = 0;
	for(int i = 0; i < _pls.size(); i++)
		retVal += _pls[i]->getNTimeSteps();
	return retVal;
}

int ConcurrentPlanLine::getNTotalTimelines() {
	int retVal = 1;
	for(int i = 0; i <  _pls.size(); i++) {
		retVal += _pls[i]->getNTotalTimelines() - 1;
	}
	return retVal;
}

pair<int, int> ConcurrentPlanLine::fillInPlanMat(
	ConcurrentPlanStep ***steps, int startRow, int startCol) {
	pair<int, int> retVal;
	for(int i = 0; i <  _pls.size(); i++) {
		pair<int, int> a = _pls[i]->fillInPlanMat(
			steps, retVal.first + startRow, retVal.second + startCol);
		retVal.first += a.first;
		retVal.second += a.second;
	}
	return retVal;
}

void ConcurrentPlanLine::fillInPlanMatTwo(ConcurrentPlanStep ***steps) {
	for(int i = 0; i < _pls.size(); i++)
		_pls[i]->fillInPlanMatTwo(steps);
}

string ConcurrentPlanLine::getString() {
	abort();
}

double ConcurrentPlanLine::computePerformanceTime() {
	_timeToPerform = 0;

	for(int i = 0; i < _pls.size(); i++)
		_timeToPerform += _pls[i]->computePerformanceTime();

	return _timeToPerform;
}

int ConcurrentPlanLine::computeStepLen() {
	_stepLen = 0;
	
	for(int i = 0; i < _pls.size(); i++)
		_stepLen += _pls[i]->computeStepLen();

	return _stepLen;
}

pair<int, int> ConcurrentPlanLine::label(int startRow, int startCol,
	int printTabs) {
	for(int i = 0; i < printTabs; i++) cout << "	";
	//cout << "ConcurrentPlanLine::label:	" << startRow << "	" <<
	//	startCol << endl;
	pair<int, int> retVal;
	retVal.first = 0;
	retVal.second = 0;

	for(int i = 0; i <  _pls.size(); i++) {
		pair<int, int> a = _pls[i]->label(
			retVal.first + startRow, retVal.second + startCol, printTabs + 1);
		retVal.first += a.first - 1;
		retVal.second += a.second;
	}

	//if(retVal.first == 0)
	retVal.first += 1;

	for(int i = 0; i < printTabs; i++) cout << "	";
	//cout << "/ConcurrentPlanLine::label:	" << startRow << "	" <<
	//	startCol << "	" << retVal.first << "	" <<
	//	retVal.second << endl;
	return retVal;
}

bool ConcurrentPlanLine::isAPL() {
	return false;
}

ParamList *ConcurrentPlanLine::getPL() {
	return NULL;
}

