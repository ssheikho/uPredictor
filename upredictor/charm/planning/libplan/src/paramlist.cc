#include "paramlist.h"
#include "action.h"
#include "objecttable.h"
#include "planninggraph.h"
#include "planstate.h"
#include "problem.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ParamList::ParamList(Action &action, ObjectTable &ot, Problem *problem,
	int nvals, int *vals, ParamListTable *plt) :
	_action(action), _ot(ot), _problem(problem),
	_nvals(nvals), _vals(new int[_nvals]),
	_index(-1), _plt(plt),
	//_meanTime(1.25), _stdDevTime(0.25),
	_command("NULL-COMMAND") {
	for(int i = 0; i < _nvals; i++) _vals[i] = vals[i];
}

ParamList::~ParamList() {
	delete[] _vals;
}

void ParamList::printContents(bool cr) {	
	cout << "(" << _action.getName();
	for(int i = 0; i < _nvals; i++)
		cout << "	" << _ot.getObjectName(_vals[i]);
	cout << ")";
	if(cr) cout << endl;
}

bool ParamList::preconditionsMet(map<int, vector<PlanStatePred *> > &pred) {
	bool retVal = false;
	//cout << "ParamList::preconditionsMet" << endl;
	retVal = _action.preconditionsMet(pred, *this);
	//cout << "/ParamList::preconditionsMet" << endl;
	return retVal;
}

bool ParamList::postConditionsMet(map<int, vector<PlanStatePred *> > &pred) {
	bool retVal = false;
	//cout << "ParamList::preconditionsMet" << endl;
	retVal = _action.postConditionsMet(pred, *this);
	//cout << "/ParamList::preconditionsMet" << endl;
	return retVal;
}

int ParamList::getParamObj(int index) {
	return _vals[index];
}

string ParamList::getConcreteParam(int index) {
	return _ot.getObjectName(_vals[index]);
}

Action &ParamList::getAction() {
	return _action;
}

ObjectTable &ParamList::getObjectTable() {
	return _ot;
}

Problem *ParamList::getProblem() {
	return _problem;
}

void ParamList::setIndex(int index) {
	_index = index;
}

int ParamList::getIndex() {
	return _index;
}

int ParamList::getNVals() {
	return _nvals;
}

PlanState *ParamList::doAction(PlanState *to, bool checkExists) {
	PlanState *retVal = NULL;

	if(checkExists) {
		bool isNew;
		retVal = _problem->getPG().transition(to, this, isNew);
	} else {
		retVal = new PlanState(to);
		_action.applyEffect(*retVal, *this);
	}

	if(!retVal) abort();

	return retVal;
}

void ParamList::applyToPlanState(PlanState *state) {
	_action.applyEffect(*state, *this);
}

double ParamList::getTimeMean() {
	return _tv.getMean();//_meanTime;
}

double ParamList::getTimeStdDev() {
	return _tv.getStdDev();//_meanTime;
}

/*
void ParamList::setTimeMean(double t) {
	//return 0.0;//_meanTime;
}

void ParamList::setTimeStdDev(double t) {
	//return 0.0;//_meanTime;
}
*/

void ParamList::save(ofstream &o) {
	o << "		(	(:action " << _action.getName();
	for(int i = 0; i < _nvals; i++)
		o << " " << _ot.getObjectName(_vals[i]);
	o << ")" << endl;

	o << "			(:command " << _command << ")" << endl;
	//o << "			(:duration " << _meanTime << " " << _stdDevTime <<
	//	"))" << endl;
}

void ParamList::addTime(double time) {
	cout << "ParamList::addTime:	" << time << endl;
	_tv.addTime(time);
	_plt->save();
}

TimeVector &ParamList::getTV() {
	return _tv;
}
