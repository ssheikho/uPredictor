#include "concurrentplanstep.h"
#include "concurrentplangrid.h"
#include "planstate.h"

#include <iostream>
#include <string>

ConcurrentPlanStep::ConcurrentPlanStep() : _timeToPerform(0), _stepLen(0) {
	_stepNumber.first = -1;
	_stepNumber.second = -1;
}

ConcurrentPlanStep::~ConcurrentPlanStep() {}

/*
PlanState *ConcurrentPlanStep::doStep(PlanState *state) {
	PlanState *retVal = new PlanState(state);
	applyToPlanState(retVal);
	return retVal;
}
*/

ConcurrentPlanGrid *ConcurrentPlanStep::generateGrid() {
	pair<int, int> size = label(0, 0, 0);
	int a = size.first;
	int b = size.second;

	//cout << "ConcurrentPlanStep::generateGrid:	" << size.first << "	" <<
	//	size.second << endl;

	ConcurrentPlanGrid *grid = new ConcurrentPlanGrid(a, b);
	fillInPlanMatTwo((ConcurrentPlanStep ***)grid->_steps);

	return grid;
}

void ConcurrentPlanStep::printGrid() {
	ConcurrentPlanGrid *grid = generateGrid();

	string printable[grid->_rows][grid->_cols];
	for(int i = 0; i < grid->_rows; i++) {
		for(int j = 0; j < grid->_cols; j++) {
			if(grid->_steps[i][j])
				printable[i][j] = grid->_steps[i][j]->getString();
			else
				printable[i][j] = "";
		}
	}

	for(int i = 0; i < grid->_rows; i++) {
		for(int j = 0; j < grid->_cols; j++) {
			cout << "[" << printable[i][j] << "]";
		}
		cout << endl;
	}
	delete grid;
}

double ConcurrentPlanStep::getPerformanceTime() {
	return _timeToPerform;
}

int ConcurrentPlanStep::getStepLen() {
	return _stepLen;
}

