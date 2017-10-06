#include "action.h"
#include "atomicactionpredicate.h"
#include "domain.h"
#include "objecttable.h"
#include "paramlist.h"
#include <iostream>

Action::Action(string name,
	vector<string> &nameList, vector<string> &typeList, Domain &domain,
	int actionIndex) :
	_name(name), _domain(domain),
	_nparam(nameList.size()),
	_parameters(new string[_nparam]), _types(new int[_nparam]),
	_precond(NULL), _effect(NULL),
	_maintainPrecondPointer(false), _maintainEffectPointer(false),
	_actionIndex(actionIndex) {
	for(int i = 0; i < _nparam; i++) {
		_types[i] = _domain.types().getIndex(typeList[i]);
		_paramMap[_parameters[i] = nameList[i]] = i;
	}
}

Action::~Action() {
	delete[] _parameters;
	delete[] _types;
	if(_maintainPrecondPointer && _precond) delete _precond;
	if(_maintainEffectPointer && _effect) delete _effect;
}

Domain &Action::getDomain() {
	return _domain;
}

string Action::getName() {
	return _name;
}

string Action::getParam(int index) {
	return _parameters[index];
}

int Action::resolveIndex(string param) {
	return _paramMap[param];
}


AtomicActionPredicate *Action::createActionPredicate(
	string name, vector<string> &parameters) {
	return new AtomicActionPredicate(name, parameters, *this);
}

void Action::setPrecondition(ActionPredicate *precond, bool maintainPointer) {
	if(_maintainPrecondPointer && _precond) delete _precond;
	_precond = precond;
	_maintainPrecondPointer = maintainPointer;
}

void Action::setEffect(ActionPredicate *effect, bool maintainPointer) {
	if(_maintainEffectPointer && _effect) delete _effect;
	_effect = effect;
	_maintainEffectPointer = maintainPointer;
}

void Action::printContents() {
	cout << "Action:	" << _name << endl;
	cout << "	Parameters:" << endl;
	for(int i = 0; i < _nparam; i++)
		cout << "	" << _parameters[i] << "	" <<
			_domain.types().getName(_types[i]) << endl;
	if(_precond)
		_precond->printContents(true);
	if(_effect)
		_effect->printContents(true);
}

vector<ParamList *> Action::permuteParameters(
	ObjectTable &ot, Problem *problem,
	ParamListTable *plt) {
	int curPermutation[_nparam];
	return permuteParameters(ot, curPermutation, 0, problem, plt);
}

vector<ParamList *> Action::permuteParameters(ObjectTable &ot,
	int *curPermutation, int curParam, Problem *problem, ParamListTable *plt) {
	vector<ParamList *> retval;
	int curObj = 0;
	bool foundOne = false;
	while((curObj = ot.findNext(curObj, _types[curParam])) != -1) {
		curPermutation[curParam] = curObj;
		if(curParam == (_nparam - 1)) {
			ParamList *pl =
				new ParamList(*this, ot, problem, _nparam, curPermutation, plt);
			retval.push_back(pl);
		}else {
			vector<ParamList *> sub =
				permuteParameters(ot, curPermutation, curParam + 1, problem,
				plt);
			retval.insert(retval.end(), sub.begin(), sub.end());
		}
		curObj++;
		foundOne = true;
	}

	return retval;
}

bool Action::preconditionsMet(
	map<int, vector<PlanStatePred *> > &pred, ParamList &params) {
	bool retVal = false;
	//cout << "Action::preconditionsMet" << endl;
	retVal = _precond->preconditionsMet(pred, params);
	//cout << "/Action::preconditionsMet" << endl;
	return retVal;
}

bool Action::postConditionsMet(
	map<int, vector<PlanStatePred *> > &pred, ParamList &params) {
	bool retVal = false;
	//cout << "Action::preconditionsMet" << endl;
	retVal = _effect->preconditionsMet(pred, params);
	//cout << "/Action::preconditionsMet" << endl;
	return retVal;
}

void Action::applyEffect(PlanState &to, ParamList &params) {
	_effect->apply(to, params, false);
}

void Action::setIndex(int index) {
	_actionIndex = index;
}

int Action::getIndex() {
	return _actionIndex;
}

int Action::getNParam() {
	return _nparam;
}


