#include "plan.h"
#include "paramlist.h"
#include "planninggraph.h"
#include "plannerutil.h"
#include <iostream>

Plan::Plan(vector<int> &plan, vector<int> &edges, PlanningGraph &pg) :
	_nStates(plan.size()), _plan(new int[_nStates]),
	_edges(new int[_nStates - 1]), _pg(pg) {
	int ctr = 0;
	for(int i = _nStates - 1; i >= 0; i--)
		_plan[ctr++] = plan[i];

	ctr = 0;
	for(int i = _nStates - 2; i >= 0; i--)
		_edges[ctr++] = edges[i];
}

Plan::~Plan() {
	delete[] _plan;
	delete[] _edges;
}

void Plan::printContents() {
	for(int i = 0; i < (_nStates - 2); i++) {
		cout << "[" << _plan[i] << "]";
		_pg.getPLT().getPL(_edges[i]).printContents(false);
		cout << "[" << _plan[i + 1] << "]";
		cout << "-" << _edges[i] << "-> ";
	}

	cout << "[" << _plan[_nStates - 2] << "]";
	_pg.getPLT().getPL(_edges[_nStates - 2]).printContents(false);
	cout << "[" << _plan[_nStates - 1] << "]";
	cout << endl;
}

bool Plan::equals(Plan &p) {
	bool retVal = true;

	if(_nStates = p._nStates)
		for(int i = 0; i < _nStates; i++) retVal &= _edges[i] == p._edges[i];
	else
		retVal = false;

	return retVal;
}

int Plan::getParamList(int index) {
	return _edges[index];
}

int Plan::getState(int index) {
	return _plan[index];
}

int Plan::getNStates() {
	return _nStates;
}

PlanningGraph &Plan::getPlanningGraph() {
	return _pg;
}

bool Plan::planHasACycle() {
	return hasRepeat(_plan, _nStates);
}
