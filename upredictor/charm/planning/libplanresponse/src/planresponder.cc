#include "planresponder.h"
#include "actionexecutor.h"
#include "paramlist.h"
#include "plan.h"
#include "planlentable.h"
#include "planninggraph.h"
#include "problem.h"
#include "replanner.h"
#include "worldmodel.h"

#include <iostream>

PlanResponder::PlanResponder(Replanner &replanner, WorldModel &wm,
	ActionExecutor &ae, WhenPlanDone *wpd) :
	_replanner(replanner),  _wm(wm),  _ae(ae) {
	_replanner.replan(true, _wm.getCurrentState());
	_pg = &_replanner.getProblem().getPG();
	_paramListTable = &_pg->getPLT();
	_plt = new PlanLenTable();
	_plt->clear();
	_plt->compile(_pg->getPlans());
}

PlanResponder::~PlanResponder() {}
	
ParamList *PlanResponder::getNextInstruction() {
	PlanState *ps = _wm.getCurrentState();
	_replanner.replan(true, ps);
	_plt->clear();
	_plt->compile(_pg->getPlans());
	ParamList *pl = NULL;
	if(_plt->size() > 0) {
		Plan &p = _plt->getFirst();
		int paramList = p.getParamList(0);
		pl = &_paramListTable->getPL(paramList);
	}
	return pl;
}

void PlanResponder::sendNextInstruction() {
	//cout << "PlanResponder::sendNextInstruction()" << endl;
	ParamList *pl = getNextInstruction();
	if(pl) {
		_ae.execute(pl);
		//cout << "DOING THIS:	";
		//pl->printContents();
	}
	//SEND HERE
	_wm.waitForUpdate();
	//cout << "/PlanResponder::sendNextInstruction()" << endl;
}

void PlanResponder::startThread() {
	pthread_create(&_thread, NULL, prThread, this);
}

void PlanResponder::waitThread() {
	pthread_join(_thread, NULL);
}

void *PlanResponder::prThread(void *in) {
	PlanResponder *pr = (PlanResponder *) in;
	while(true) {
		pr->sendNextInstruction();
	}
}
