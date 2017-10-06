#include "andactionpredicate.h"
#include <iostream>

AndActionPredicate::AndActionPredicate(
	vector<ActionPredicate*> &preds, bool maintainPointer) :
	_npreds(preds.size()), _preds(new ActionPredicate*[_npreds]),
	_maintainPointer(maintainPointer) {
	for(int i = 0; i < _npreds; i++) _preds[i] = preds[i];	
}

AndActionPredicate::~AndActionPredicate() {
	for(int i = 0; i < _npreds; i++) delete _preds[i];
	delete[] _preds;	
}

void AndActionPredicate::printContents(bool cr) {
	cout << "(and" << endl;
	for(int i = 0; i < _npreds; i++) {
		cout << "	";
		_preds[i]->printContents(true);
	}
	cout << endl << ")";
	if(cr) cout << endl;
}

bool AndActionPredicate::preconditionsMet(
	map<int, vector<PlanStatePred *> > &pred, ParamList &params) {
	bool retVal = true;
	for(int i = 0; ((i < _npreds) && (retVal)); i++)
		retVal &= _preds[i]->preconditionsMet(pred, params);
	return retVal;
}

void AndActionPredicate::apply(PlanState &to, ParamList &params, bool invert) {
	for(int i = 0; i < _npreds; i++)
		_preds[i]->apply(to, params, invert);
}
