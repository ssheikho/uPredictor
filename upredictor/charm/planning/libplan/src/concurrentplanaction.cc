#include "concurrentplanaction.h"
#include "action.h"
#include "domain.h"
#include "objecttable.h"
#include "paramlist.h"
#include "plannerutil.h"

#include <cstdlib>
#include <iostream>

using namespace std;

ConcurrentPlanAction::ConcurrentPlanAction(ParamList &pl) :
	ConcurrentPlanStep(), _pl(pl) {}
ConcurrentPlanAction::~ConcurrentPlanAction() {}

PlanState *ConcurrentPlanAction::doAction(PlanState *to) {
	PlanState *s = _pl.doAction(to);
	if(!s) abort();
	return s;
}

int ConcurrentPlanAction::attemptInsertion(
	ParamList &pl, vector<ConcurrentPlan *> &inProgress) {
	abort();
}

void ConcurrentPlanAction::applyToPlanState(PlanState *state) {
	_pl.applyToPlanState(state);
}

PlanState *ConcurrentPlanAction::doStep(PlanState *state) {
	return _pl.doAction(state);
}

int ConcurrentPlanAction::getType() {
	return action;
}

void ConcurrentPlanAction::printContents(int actionSpaces, int lineNumber,
	bool cr, int digitsForAction) {
	cout << "[" << fixedWidthIntString(_pl.getIndex(), digitsForAction) << "]";
	if(cr) cout << endl;
}

int ConcurrentPlanAction::getNTimeSteps() {
	return 1;
}

bool ConcurrentPlanAction::doesntInterfere(ParamList &pl) {
	Action &a = pl.getAction();
	Action &b = _pl.getAction();
	bool retVal = !a.getDomain().NCT().isNoConcur(a.getIndex(), b.getIndex());
	//cout << "ConcurrentPlanAction::doesntInterfere:	" << a.getName() << "	" <<
	//	b.getName() << "	" << retVal << endl;
	return retVal;
}

int ConcurrentPlanAction::getNTotalTimelines() {
	return 1;
}
pair<int, int> ConcurrentPlanAction::fillInPlanMat(
	ConcurrentPlanStep ***steps, int startRow, int startCol) {
	pair<int, int> retVal;
	retVal.first = 0;
	retVal.second = 1;

	steps[startRow][startCol] = this;

	return retVal;
}

void ConcurrentPlanAction::fillInPlanMatTwo(ConcurrentPlanStepPtr **steps) {
	steps[_stepNumber.first][_stepNumber.second] = this;
}

string ConcurrentPlanAction::getString() {
	Action &action = _pl.getAction();
	ObjectTable &ot = _pl.getObjectTable();
	string retVal = action.getName();

	for(int i = 0; i < action.getNParam(); i++)
		retVal += "_" + ot.getObjectName(_pl.getParamObj(i));
	return retVal;
}

double ConcurrentPlanAction::computePerformanceTime() {
	return _timeToPerform = _pl.getTimeMean();
}

int ConcurrentPlanAction::computeStepLen() {
	return _stepLen = 1;
}

pair<int, int> ConcurrentPlanAction::label(int startRow, int startCol,
	int printTabs) {
	for(int i = 0; i < printTabs; i++) cout << "	";
	//cout << "ConcurrentPlanAction::label:	" << startRow << "	" << startCol <<
	//	endl;

	_stepNumber.first = startRow;
	_stepNumber.second = startCol;

	return pair<int, int>(1,1);
}

bool ConcurrentPlanAction::isAPL() {
	return true;
}

ParamList *ConcurrentPlanAction::getPL() {
	return &_pl;
}

