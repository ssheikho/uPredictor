#include "planninggraph.h"
#include "actionmap.h"
#include "concurrentplan.h"
#include "domain.h"
#include "paramlist.h"
#include "plan.h"
#include "plannerutil.h"
#include "problem.h"

#include <cstdlib>
#include <iostream>

PlanningGraph::PlanningGraph(Problem *problem) : _problem(problem),
	_plt(problem)
	//, _planTree(-1, 0, NULL, _plt, this)
	{}

PlanningGraph::~PlanningGraph() {}
	
void PlanningGraph::doPlanning(PlanState *fromState) {
	_sw.resetAndStart();

	_plans.clear();

	if(fromState) {
		_rootState = _pst.addCopyOrReturnExisting(fromState);

		if(!fromState->containsAllOf(_problem->getGoalState()))
			_ready.push_back(&_pst.getState(_rootState));

	} else {
		//JWH Push the root note onto the ready queue
		//cout << "Planning from Problem Root State" << endl;
		_rootState = _pst.addCopyOrReturnExisting(&_problem->getRootState());
		_ready.push_back(&_pst.getState(_rootState));
	}


	//cout << "Parameter Permutations:	" << _plt.size() << endl;

	int readyIters = 0;
	while(_ready.size()) {
		expandOneLevel(false);
		readyIters++;
		//cout << "Ready Iterations:	" << readyIters 
		//	<< endl;
			//<< "	" << _rootState << endl;
		//cout << "Ready Queue Size:	" << _ready.size() << endl;
	}

	//cout << "Identifying goal states" << endl;
	//identifyGoalStates();

	//cout << "Compiling plans" << endl;
	compilePlans();

	/*
	//Build a plan tree that we'll never see or use again
	for(int i = 0; i < _plans.size(); i++) {
		_planTree.insert(_plans.get(i), 0);
	}
	_planTree.idLabelTree();
	*/


	printSummary();
	cout << "Time to totally-ordered plans:	" << _sw.lap() << " seconds" <<
		endl;
}

void PlanningGraph::identifyGoalStates() {
	_goals.clear();
	for(int i = 0; i < _pst.getNumStates(); i++) {
		PlanState &curState = _pst.getState(i);
		if(curState.containsAllOf(_problem->getGoalState()))
			_goals.push_back(&curState);
	}
}

void PlanningGraph::compilePlans() {
	_plans.clear();

	vector<int> plan, edges;
	for(int i = 0; i < _goals.size(); i++) {
		plan.clear();
		plan.push_back(_goals[i]->getIndex());
		compilePlans(plan, edges, _goals[i]->getIndex());
	}
}

/*
int i = 0; i < _backLinks[fromState].size(); i++) {
*/


void PlanningGraph::compilePlans(
	vector<int> &plan, vector<int> &edges, int fromState) {

	for(set<int>::iterator i = _backLinks[fromState].begin();
		i != _backLinks[fromState].end(); i++) {

		if(!vectorContains(plan, *i)) {
			plan.push_back(*i);
			edges.push_back(_forwardLinks[*i][fromState]);

			if(*i == _rootState) {
				//cout << "PlanningGraph::compilePlans" << endl;
				//printIntVect(plan, true);
				//printIntVect(edges, true);

				Plan *p = new Plan(plan, edges, *this);
				if(!_plans.insert(p, false)) delete p;
			} else {
				compilePlans(plan, edges, *i);
			}

			plan.pop_back();
			edges.pop_back();
		}
	}

}

bool PlanningGraph::vectorContains(vector<int> &plan, int state) {
	bool retVal = false;
	for(int i = 0; ((i < plan.size()) && (!retVal)); i++)
		if(plan[i] == state) retVal = true;
	return retVal;
}

void PlanningGraph::expandOneLevel(bool ignoreNot) {
	vector<PlanState *> frontierStates;
	vector<int> frontierParams;
	vector<bool> stateExists;

	for(int i = 0; i < _ready.size(); i++)
		for(int j = 0; j < _plt.size(); j++) {
			ParamList &pl = _plt.getPL(j);
			if(_ready[i]->preconditionsMet(pl)) {
				bool isNew;
				PlanState *s = transition(_ready[i], &pl, isNew);

				//cout << "preconditionsMet:	" << isNew << endl;
				stateExists.push_back(!isNew);
				frontierParams.push_back(pl.getIndex());
				frontierStates.push_back(s);
			}
		}

	_ready.clear();

	for(int i = 0; i < frontierStates.size(); i++) {
		if(!stateExists[i])	{
			if(frontierStates[i]->containsAllOf(_problem->getGoalState())) {
				_goals.push_back(frontierStates[i]);
			} else {
				_ready.push_back(frontierStates[i]);
			}
		}
	}
}

void PlanningGraph::printGoalStates() {
	for(int i = 0; i < _goals.size(); i++) {
		cout << "STATE:	" << i << endl;
		_goals[i]->printContents();
	}
}

void PlanningGraph::printSummary() {
	int edgecount = 0;
	for(map<int, set<int> >:: iterator i = _backLinks.begin();
		i != _backLinks.end(); i++) {
		edgecount += i->second.size();
	}

	cout << "Plan completed:	" << endl;
	cout << "	Graph nodes:	" << _pst.getNumStates() << endl;
	cout << "	Graph edges:	" << edgecount << endl;
	cout << "	Feasible plans:	" << _plans.size() << endl;
}

void PlanningGraph::printBackMatrix() {
	cout << "======Back Links======" << endl << "[ ]";
	for(int i = 0; i < _pst.getNumStates(); i++)
		cout << "[" << i << "]";
	cout << endl;

	for(int i = 0; i < _pst.getNumStates(); i++) {
		cout << "[" << i << "]";
		for(int j = 0; j < _pst.getNumStates(); j++) {
			if(_backLinks[i].find(j) == _backLinks[i].end()) {
				cout << " 0 ";
			} else {
				cout << " 1 ";
			}
		}
		cout << endl;
	}
}

PlanTable &PlanningGraph::getPlans() {
	return _plans;
}

ParamListTable &PlanningGraph::getPLT() {
	return _plt;
}

PlanStateTable &PlanningGraph::getPST() {
	return _pst;
}

PlanState *PlanningGraph::transition(
	PlanState *from, ParamList *link, bool &isNew) {
	//cout << "PlanningGraph::transition:	" << from->getIndex() << endl;
	isNew = false;
	PlanState *retVal = NULL;
	int fromIdx = from->getIndex();
	int linkIdx = link->getIndex();

	if(fromIdx == -1) {
		retVal = link->doAction(from, false);
		//abort();
	} else {
		map<int, int> &actLink = _forwardAcrossActions[fromIdx];
		map<int, int>::iterator alIter = actLink.find(linkIdx);

		if(alIter == actLink.end()) {
			PlanState *p = link->doAction(from, false);
			int refState = _pst.stateExists(*p);
			isNew = refState == -1;
			if(isNew) refState = _pst.add(p);

			(_forwardLinks[fromIdx])[refState] = linkIdx;
			(_forwardAcrossActions[fromIdx])[linkIdx] = refState;
			(_backLinks[refState]).insert(fromIdx);

			retVal = &_pst.getState(refState);
		} else {
			int refState = (_forwardAcrossActions[fromIdx])[linkIdx];
			retVal = &_pst.getState(refState);
		}

		if(!retVal) abort();
	}

	//cout << "PlanningGraph::transition:	" << fromIdx << "	" <<
	//	retVal->getIndex() << "	" << linkIdx << "	" << isNew << endl;

	return retVal;
}
