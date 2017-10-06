#include "planstatepred.h"
#include "domain.h"
#include "objecttable.h"
#include "problem.h"

#include <iostream>

/*
PlanStatePred::PlanStatePred(
	int pred, vector<string> &vals, Problem *problem) : _pred(pred),
	_nobj(vals.size()), _objects(new int[_nobj]), _refs(0), _problem(problem) {
	ObjectTable &obj = _problem->getObjectTable();
	for(int i = 0; i < _nobj; i++)
		_objects[i] = obj.getObjectID(vals[i]);
}
*/

PlanStatePred::PlanStatePred(
	int pred, int nobj, int *obj, int idx, Problem *problem) :
	_pred(pred), _nobj(nobj), _objects(obj), _idx(idx), _problem(problem) {}

PlanStatePred::~PlanStatePred() {}

void PlanStatePred::printContents() {
	ObjectTable &obj = _problem->getObjectTable();

	cout << "(" << _problem->getDomain().predicates().getName(_pred);
		//<< "-" << _pred;
	for(int i = 0; i < _nobj; i++)
		cout << " " << obj.getObjectName(_objects[i]);
	cout << ")" << endl;
}

int PlanStatePred::getPred() {
	return _pred;
}

int PlanStatePred::getObj(int index) {
	return _objects[index];
}

Problem &PlanStatePred::getProblem() {
	return *_problem;
}

bool PlanStatePred::equals(int pred, int nobj, int *obj) {
	bool retVal = true;

	if(pred == _pred) {
		for(int i = 0; (i < nobj) && (retVal); i++)
			retVal &= obj[i] == _objects[i];
	} else {
		retVal = false;
	}
	
	//if(retVal) cout << "Equal predicates" << endl;

	return retVal;
}

bool PlanStatePred::equals(PlanStatePred &p) {
	return p._idx == _idx;
}

int PlanStatePred::getIndex() {
	return _idx;
}
