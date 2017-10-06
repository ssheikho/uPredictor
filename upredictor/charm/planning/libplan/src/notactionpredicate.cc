#include "notactionpredicate.h"
#include <iostream>

using namespace std;

NotActionPredicate::NotActionPredicate(
	ActionPredicate *pred, bool maintainPointer) :
	_pred(pred), _maintainPointer(maintainPointer) {}

NotActionPredicate::~NotActionPredicate() {
	if(_maintainPointer) delete _pred;
}

void NotActionPredicate::printContents(bool cr) {
	cout << "(not ";
	_pred->printContents(false);
	cout << ")";
	if(cr) cout << endl;
}

bool NotActionPredicate::preconditionsMet(
	map<int, vector<PlanStatePred *> > &pred, ParamList &params) {
	return !_pred->preconditionsMet(pred, params);
}

void NotActionPredicate::apply(
	PlanState &to, ParamList &params, bool invert) {
	_pred->apply(to, params, !invert);
}
