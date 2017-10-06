#include "atomicactionpredicate.h"
#include "action.h"
#include "domain.h"
#include "objecttable.h"
#include "paramlist.h"
#include "planstate.h"
#include "planstatepred.h"
#include "problem.h"

#include <iostream>

//JWH	Type checking would go in here.
AtomicActionPredicate::AtomicActionPredicate(string name,
	vector<string> &parameters, Action &action) :
	_action(action),
	_predicateID(_action.getDomain().predicates().getIndex(name)),
	_nparam(parameters.size()), _parameterMap(new int[_nparam]) {
	for(int i = 0; i < _nparam; i++)
		_parameterMap[i] = action.resolveIndex(parameters[i]);
}

AtomicActionPredicate::~AtomicActionPredicate() {
	delete[] _parameterMap;
}

void AtomicActionPredicate::printContents(bool cr) {
	//_action.getDomain().predicates().printContents();
	cout << "(" << _action.getDomain().predicates().getName(_predicateID);
	for(int i = 0; i < _nparam; i++)
		cout << " " << _action.getParam(_parameterMap[i]);
	cout << ")";
	if(cr) cout << endl;
}

bool AtomicActionPredicate::preconditionsMet(
		map<int, vector<PlanStatePred *> > &pred, ParamList &params) {
	//cout << "AtomicActionPredicate::preconditionsMet" << endl;
	bool retVal = false;

	vector<PlanStatePred *> &predVect = pred[_predicateID];
	for(int i = 0; ((i < predVect.size()) && !retVal); i++) {
		bool match = true;
		for(int j = 0; ((j < _nparam) && match); j++) {
			match &= predVect[i]->getObj(j) ==
				params.getParamObj(_parameterMap[j]);
		}
		retVal = match;
	}

	/*
	if(retVal) {
		cout << "(" << _action.getDomain().predicates().getName(_predicateID);
		for(int i = 0; i < _nparam; i++)
			cout << " " <<
				params.getObjectTable().getObjectName(
					params.getParamObj(_parameterMap[i]));
		cout << ")";
		cout << endl;
	}
	*/

	//cout << "/AtomicActionPredicate::preconditionsMet" << endl;
	return retVal;
}

void AtomicActionPredicate::apply(
	PlanState &to, ParamList &params, bool invert) {
	int *objects = new int[_nparam];
	for(int i = 0; i < _nparam; i++)
		objects[i] = params.getParamObj(_parameterMap[i]);

	Problem *problem = &to.getProblem();
	PlanStatePred *p = problem->getPSPT().getPredicate(
		_predicateID, _nparam, objects, problem);

	if(invert) {
		to.del(p);
	} else {
		to.add(p);
	}
}



