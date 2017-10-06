#include "concurrentplanresponder.h"
#include "actionexecutor.h"
#include "concurrentplan.h"
#include "concurrentplangrid.h"
#include "concurrentreplanner.h"
#include "paramlist.h"
#include "plan.h"
#include "planlentable.h"
#include "planninggraph.h"
#include "problem.h"
#include "worldmodel.h"

#include <iostream>

ConcurrentPlanResponder::ConcurrentPlanResponder(ConcurrentReplanner &replanner,
	WorldModel &wm, ActionExecutor &ae, WhenPlanDone *wpd) :
	_replanner(replanner),  _wm(wm),  _ae(ae), _cp(NULL), _cpg(NULL) {
	_replanner.replan(true, _wm.getCurrentState());
	_pg = &_replanner.getProblem().getPG();
	_paramListTable = &_pg->getPLT();
	_plt = new PlanLenTable();
	_plt->clear();
	_plt->compile(_pg->getPlans());
}

ConcurrentPlanResponder::~ConcurrentPlanResponder() {}
	
int ConcurrentPlanResponder::update() {
	PlanState *ps = _wm.getCurrentState();
	_replanner.replan(true, ps);
	int noConPlan = _replanner.getCPT().getNumberConcurrentPlans();
	if(noConPlan) {
		_cp = _replanner.getCPTT().getFirst();
		if(_cpg) delete _cpg;
		cout << "noConPlan:	" << noConPlan << endl;
		if(noConPlan == 0) {
			_cpg = NULL;
			cout << "No good plans" << endl;
		} else {
			_cpg = _replanner.getCPTT().getFirst()->generateGrid();
		}
	} else {
		cout << "No workable plans" << endl;
	}
	return noConPlan;
}

void ConcurrentPlanResponder::sendNextInstructions() {
	int nPlans = update();
	if(nPlans) {
		if(_cpg) {
			_cp->getPlan().printContents();
			_cpg->print();
			int sent = 0;
				for(int i = 0; i < _cpg->_rows; i++) {
					ConcurrentPlanStep *ps = _cpg->get(i,0);
					if(ps) {
						ParamList *pl = ps->getPL();
						if(pl) {
							cout <<
								"ConcurrentPlanResponder::sendNextInstructions():	" <<
								i << endl;
							pl->printContents();
							_ae.execute(pl);
							sent++;
						}
					}
				}

			if(sent == 0) {
				int plno = _cp->getPlan().getParamList(0);
				ParamList &pl =
					_cp->getPlan().getPlanningGraph().getPLT().getPL(plno);
				_ae.execute(&pl);
			}
		}
	} else {
		_wm.getCurrentState()->printContents();

		struct timespec to_sleep = { 0, 100 };
		int ret = nanosleep(&to_sleep, &to_sleep);
		cout << "SLEEPING" << endl;
	}
}

void ConcurrentPlanResponder::startThread() {
	pthread_create(&_thread, NULL, prThread, this);
}

void ConcurrentPlanResponder::waitThread() {
	pthread_join(_thread, NULL);
}

void *ConcurrentPlanResponder::prThread(void *in) {
	ConcurrentPlanResponder *pr = (ConcurrentPlanResponder *) in;
	while(true) {
		pr->sendNextInstructions();
		pr->_wm.waitForUpdate();
	}
}
