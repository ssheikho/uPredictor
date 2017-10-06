#include "serialplan.h"
#include "paramlist.h"
#include "planninggraph.h"
#include <iostream>

SerialPlan::SerialPlan(vector<int> &plan, vector<int> &edges, PlanningGraph &pg) :
	_nStates(plan.size()), _plan(new int[_nStates]),
	_edges(new int[_nStates - 1]), _pg(pg) {
	int ctr = 0;
	for(int i = _nStates - 1; i >= 0; i--)
		_plan[ctr++] = plan[i];

	ctr = 0;
	for(int i = _nStates - 2; i >= 0; i--)
		_edges[ctr++] = edges[i];
}

SerialPlan::~Plan() {
	delete[] _plan;
	delete[] _edges;
}

void SerialPlan::printContents() {
	for(int i = 0; i < (_nStates - 2); i++) {
		cout << "[" << _plan[i] << "]";
		_pg.getPLT().getPL(_edges[i]).printContents(false);
		cout << "[" << _plan[i + 1] << "]";
		cout << " -> ";
	}

	cout << "[" << _plan[_nStates - 2] << "]";
	_pg.getPLT().getPL(_edges[_nStates - 2]).printContents(false);
	cout << "[" << _plan[_nStates - 1] << "]";
	cout << endl;
}

bool SerialPlan::equals(Plan &p) {
	bool retVal = true;

	if(_nStates = p._nStates)
		for(int i = 0; i < _nStates; i++) retVal &= _edges[i] == p._edges[i];
	else
		retVal = false;

	return retVal;
}

int SerialPlan::getParamList(int index) {
	return _edges[index];
}

int SerialPlan::getState(int index) {
	return _plan[index];
}

int SerialPlan::getNStates() {
	return _nStates;
}

PlanningGraph &SerialPlan::getPlanningGraph() {
	return _pg;
}
