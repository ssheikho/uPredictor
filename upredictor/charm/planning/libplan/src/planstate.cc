#include "planstate.h"
#include "domain.h"
#include "objecttable.h"
#include "paramlist.h"
#include "planstate.h"
#include "planstatepred.h"
#include "planstatepredtable.h"
#include "problem.h"

#include <iostream>

PlanState::PlanState(PlanState *state) :
	_problem(state->_problem), _pspt(state->_pspt),
	//_idx(state->_idx),
	_idx(-1),
	_fromCopy(true) {
	_state = state->_state;
	/*
	for(map<int, vector<PlanStatePred *> >::iterator
		itera = state->_state.begin();
		itera != state->_state.end(); itera++) {
		int pred = itera->first;
		vector<PlanStatePred *> v = state->_state[pred];
		for(int i = 0; i < v.size(); i++)
			_state[pred].push_back(v[i]);
	}
	*/
}

PlanState::PlanState(Problem *problem, PlanStatePredTable &pspt) :
	_problem(problem), _pspt(pspt),
	_fromCopy(false) {}

PlanState::~PlanState() {}

void PlanState::init(string pred, vector<string> &vals) {
	int predIdx = _problem->getDomain().predicates().getIndex(pred);
	PlanStatePred *predicate = _pspt.getPredicate(predIdx, vals, _problem);
	_state[predIdx].push_back(predicate);
}

void PlanState::add(PlanStatePred *p) {
	//cout << "PlanState::ADDING:	" << endl;
	//p->printContents();
	_state[p->getPred()].push_back(p);
}

void PlanState::del(PlanStatePred *p) {
	vector<PlanStatePred *> &v = _state[p->getPred()];
	int eraseMe = -1;
	for(int i = 0; ((i < v.size()) && (eraseMe == -1)); i++) {
		if(v[i]->equals(*p)) {
			//cout << "DELETING:	" << _idx << endl;
			//p->printContents();
			//cout << "/DELETING:	" << _idx << endl;

			eraseMe = i;
		}
	}

	if(eraseMe != -1) {
		//cout << "ERASING:	" << _state[p->getPred()].size() << endl;
		//p->printContents();

		if(_state[p->getPred()].size())
			_state[p->getPred()].erase(_state[p->getPred()].begin() + eraseMe);
		else
			_state[p->getPred()].clear();

		//cout << "/ERASING:	" << _state[p->getPred()].size() << endl;
	}
}

void PlanState::printContents() {
	cout << "Predicates:	" << _idx << endl;
	for(map<int, vector<PlanStatePred *> >::iterator itera = _state.begin();
		itera != _state.end(); itera++) {
		for(vector<PlanStatePred *>::iterator iterb = itera->second.begin();
		iterb != itera->second.end(); iterb++) {
			(*iterb)->printContents();
		}
	}
}

bool PlanState::preconditionsMet(ParamList &pl) {
	bool retVal = false;
	//cout << "PlanState::preconditionsMet" << endl;
	retVal = pl.preconditionsMet(_state);
	//cout << "/PlanState::preconditionsMet" << endl;
	return retVal;
}

bool PlanState::postConditionsMet(ParamList &pl) {
	bool retVal = false;
	//cout << "PlanState::preconditionsMet" << endl;
	retVal = pl.postConditionsMet(_state);
	//cout << "/PlanState::preconditionsMet" << endl;
	return retVal;
}

Problem &PlanState::getProblem() {
	return *_problem;
}

void PlanState::setIndex(int idx) {
	_idx = idx;
}

int PlanState::getIndex() {
	return _idx;
}

bool PlanState::contains(PlanStatePred &p) {
	bool retVal = false;

	int predIdx = p.getPred();
	bool containsPredicate = _state.count(predIdx);
	if(containsPredicate) {
		vector<PlanStatePred *> &v = _state[predIdx];
		for(int i = 0; ((i < v.size()) && (!retVal)); i++)
			retVal = v[i]->equals(p);
	}

	return retVal;
}

bool PlanState::containsAllOf(PlanState &p) {
	bool retVal = true;
	
	for(map<int, vector<PlanStatePred *> >::iterator itera = p._state.begin();
		itera != p._state.end(); itera++) {
		for(vector<PlanStatePred *>::iterator iterb = itera->second.begin();
		iterb != itera->second.end(); iterb++) {
			retVal &= contains(**iterb);
		}
	}

	return retVal;
}

bool PlanState::equals(PlanState &p) {
	bool retVal = false;
	if((_idx == -1) || (p._idx == -1)) {
		retVal = _state == p._state;
	} else {
		retVal = _idx == p._idx;
	}

	//cout << "PlanState::equals:	" << retVal << endl;
	return retVal; //containsAllOf(p) && p.containsAllOf(*this);
}

