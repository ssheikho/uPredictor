#include "concurrentplanconcurrency.h"
#include "concurrentplan.h"
#include "concurrentplanline.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "plannerutil.h"

#include <cstdlib>
#include <iostream>

ConcurrentPlanConcurrency::ConcurrentPlanConcurrency(
	ConcurrentPlan *cp, PlanState *rootState, bool seedOneTimeline) :
	_cp(cp), _rootState(rootState) {
	if(seedOneTimeline)	addTimeline();
}

ConcurrentPlanConcurrency::~ConcurrentPlanConcurrency() {}

ConcurrentPlanLine *ConcurrentPlanConcurrency::addTimeline() {
	ConcurrentPlanLine *retVal = new ConcurrentPlanLine(_cp, _rootState);
	_timeLines.push_back(retVal);
	return retVal;
}

ConcurrentPlanLine *ConcurrentPlanConcurrency::getTimeline(int index) {
	return _timeLines[index];
}

int ConcurrentPlanConcurrency::getNumTimelines() {
	return _timeLines.size();
}

bool ConcurrentPlanConcurrency::applicableToRootState(ParamList &pl) {
	_rootState->preconditionsMet(pl);
}

int ConcurrentPlanConcurrency::getNumApplicableTimelines(ParamList &pl) {
	int retVal = 0;
	for(int i = 0; i < _timeLines.size(); i++) {
		if(_timeLines[i]->actionCanBeAddedToEnd(pl)) retVal++;
	}
	return retVal;
}

vector<ConcurrentPlanLine *>
	ConcurrentPlanConcurrency::getApplicableTimelines(ParamList &pl) {
	vector<ConcurrentPlanLine *> retVal;
	for(int i = 0; i < _timeLines.size(); i++) {
		if(_timeLines[i]->actionCanBeAddedToEnd(pl))
			retVal.push_back(_timeLines[i]);
	}
	return retVal;
}

int ConcurrentPlanConcurrency::insert(
	int paramList, vector<ConcurrentPlan *> &inProgress) {
	return attemptInsertion(_cp->getPLT().getPL(paramList), inProgress);
}

int ConcurrentPlanConcurrency::attemptInsertion(
	ParamList &pl, vector<ConcurrentPlan *> &inProgress) {
	int inserted = INSERT_STATUS_NOT_INSERTED;

	//Step 1)	Check action against root state.  If it works, then it gets its
	//			own timeline.
	bool atrs = applicableToRootState(pl);
	bool nts = _timeLines[0]->getNTimeSteps();
	//cout << "ConcurrentPlanConcurrency::attemptInsertion:	" << atrs <<
	//	"	" << nts << endl;
	if(atrs && nts) {
		//Step 2)	It remains a candidate if none of the existing concurrent
		//			timelines interfere with it.
		if(doesntInterfere(pl)) {
			//Step 3)
			addTimeline()->addParamList(pl);
			inserted = INSERT_STATUS_INSERTED;
		} else {
			inserted = insertNotAtRoot(pl, inProgress);
		}
	} else {
		inserted = insertNotAtRoot(pl, inProgress);
	}

	return inserted;
}

int ConcurrentPlanConcurrency::insertNotAtRoot(ParamList &pl,
	vector<ConcurrentPlan *> &inProgress) {
	int inserted = INSERT_STATUS_NOT_INSERTED;

	//JWH The other permutation will show up, because other orders are all
	//		tried at the planning phase.  Therefore, we can safely choose to
	//		insert only into the first workable permutation.
	int ctr = 0;
	for(int i = 0; ((i < _timeLines.size()) && (ctr == 0)); i++) {
		//JWH This is a dirty hack, and will need to be superceded
		int attemptValue = _timeLines[i]->attemptInsertion(pl, inProgress);
		switch(attemptValue) {
			case INSERT_STATUS_INSERTED:
				inserted = INSERT_STATUS_INSERTED;
				ctr++;
				break;
			/*
			case INSERT_STATUS_INSERT_AT_END:
				ConcurrentPlanConcurrency *con =
					new ConcurrentPlanConcurrency(_cp, _rootState, false);
				while(_timeLines.size()) {
					con->_timeLines.push_back(_timeLines[0]);
					_timeLines.erase(_timeLines.begin());
				}
				ConcurrentPlanLine *cpl = addTimeline();
				cpl->addPlanStep(con);
				inserted = INSERT_STATUS_INSERTED;
				ctr++;
				break;
			*/
		}
	}
	
	if(ctr > 1) {
		//cout << "Well, we never thought that this would happen!" << endl;
		//for(int i = 0; i < _timeLines.size(); i++) {
		//	cout << "Timelines:	" <<
		//		_timeLines[i]->getNTotalTimelines() << "	" <<
		//		_timeLines[i]->getNTimeSteps() << endl;
		//	_timeLines[i]->printGrid();
		//}
		abort();
	} else if(ctr == 0) {
		//Try all possible combinations of timelines for insertion at the end
		//	to see if:
		//			a)  Insertion can occur at the end of any timeline
		//			b)  Insertion can occur at the end of a combination of
		//					timelines
		//			c)	Insertion can occur at the end of the combination of all
		//					timeslines (subsumed by b)
		vector<set<int> > combos = tryAllCombos(pl, _timeLines.size());
		if(combos.size() == 1) {
			set<int> &a = combos[0];
			if(a.size() == 1) {
				abort();
			} else {
				ConcurrentPlanConcurrency *con =
					new ConcurrentPlanConcurrency(_cp, _rootState, false);
				vector<ConcurrentPlanLine *> l;
				for(set<int>::iterator i = a.begin(); i != a.end(); i++)
					l.push_back(_timeLines[*i]);
				for(int i = 0; i < l.size(); i++) {
					con->_timeLines.push_back(l[i]);
					_timeLines.erase(
						_timeLines.begin() + lameFind(_timeLines, l[i]));
				}
				ConcurrentPlanLine *cpl = addTimeline();
				cpl->addPlanStep(con);
				cpl->addParamList(pl);
				//abort();
				inserted = INSERT_STATUS_INSERTED;
			}
		} else {
			//if(inProgress.size() == 999) {
			//	cout << combos.size() << "	" << inProgress.size() << endl;
			//	cout << "A" << endl;
			//	_rootState->printContents();
			//	PlanState *state = doStep(_rootState);
			//	pl.printContents(true);
			//	cout << "B" << endl;
			//	state->printContents();
			//}
			//cout << "INSERT_STATUS_SKIP" << endl;
			//pl.printContents(true);
			inserted = INSERT_STATUS_SKIP;
		}
	}

	return inserted;
}

bool ConcurrentPlanConcurrency::applicableAtEndOfCombo(
	ParamList &pl, set<int> &in) {
	//PlanState state(_rootState);
	//applyToPlanState(&state, in);
	PlanState *state = doStep(_rootState, in);

	//cout << "ConcurrentPlanConcurrency::applicableAtEndOfCombo" << endl;
	//pl.printContents();
	//state.printContents();
	return state->preconditionsMet(pl);
	//return state.preconditionsMet(pl);
}

vector<set<int> > ConcurrentPlanConcurrency::tryAllCombos(ParamList &pl, int in) {
	vector<pair<set<int>, set<int> > > ready, nextReady, committed;
	pair<set<int>, set<int> > a;
	for(int i = 0; i < in; i++)
		a.second.insert(i);
	ready.push_back(a);

	while(ready.size()) {
		//cout << "ready.size():	" << ready.size() << endl;

		for(vector<pair<set<int>, set<int> > >::iterator i = ready.begin();
			i!= ready.end(); i++) {
			
			if(i->first.size())
				committed.push_back(*i);

			for(set<int>::iterator j = i->second.begin();
				j!= i->second.end(); j++) {
				pair<set<int>, set<int> > newEntry;
				newEntry.first = i->first;
				newEntry.second = i->second;
				newEntry.first.insert(*j);
				newEntry.second.erase(*j);
				if(!setIsInVectorLeft(nextReady, newEntry.first))
					nextReady.push_back(newEntry);
			}
		}

		ready = nextReady;
		nextReady.clear();
	}

	vector<set<int> > goodsets;
	for(vector<pair<set<int>, set<int> > >::iterator i = committed.begin();
		i!= committed.end(); i++) {
		if(applicableAtEndOfCombo(pl, i->first))
			goodsets.push_back(i->first);
	}

	vector<set<int> > finalsets;
	for(int i = 0; i < goodsets.size(); i++)
		if(!fullySubsumedBySmaller(goodsets[i], goodsets))
			finalsets.push_back(goodsets[i]);

	//cout << "ConcurrentPlanConcurrency::tryAllCombos:	" << goodsets.size()
	//	<< "	" << finalsets.size() << endl;

	return finalsets;
}


bool ConcurrentPlanConcurrency::setIsInVectorLeft(
	vector<pair<set<int>, set<int> > > &v, set<int> &in) {
	bool retVal = false;
	for(int i = 0; ((i < v.size()) && (!retVal)); i++) {
		retVal = true;
		for(set<int>::iterator j = in.begin();
			((j != in.end()) && (retVal)); j++) {
			retVal &= v[i].first.find(*j) != v[i].first.end();
		}
	}
	return retVal;
}

void ConcurrentPlanConcurrency::applyToPlanState(PlanState *state) {
	for(int i = 0; i < _timeLines.size(); i++)
		_timeLines[i]->applyToPlanState(state);
}

void ConcurrentPlanConcurrency::applyToPlanState(
	PlanState *state, set<int> &in) {
	//cout << "ConcurrentPlanConcurrency::applyToPlanState:	" << in.size() <<
	//	endl;
	for(set<int>::iterator i = in.begin(); i != in.end(); i++) {
		//cout << "ConcurrentPlanConcurrency::applyToPlanState:	(" << *i <<
		//	")" << endl;
		_timeLines[*i]->applyToPlanState(state);
	}
}

PlanState *ConcurrentPlanConcurrency::doStep(PlanState *state, set<int> &in) {
	PlanState *retVal = state;
	for(set<int>::iterator i = in.begin(); i != in.end(); i++) {
		retVal = _timeLines[*i]->doStep(retVal);
	}
	return retVal;
}

PlanState *ConcurrentPlanConcurrency::doStep(PlanState *state) {
	PlanState *retVal = state;

	for(int i = 0; i < _timeLines.size(); i++)
		retVal = _timeLines[i]->doStep(retVal);

	return retVal;
}

int ConcurrentPlanConcurrency::getType() {
	return concurrency;
}

void ConcurrentPlanConcurrency::printContents(int actionSpaces, int lineNumber,
	bool cr, int digitsForAction) {
	_timeLines[lineNumber]->printContents(actionSpaces, lineNumber, cr,
			digitsForAction);
	if(cr) cout << endl;
}

int ConcurrentPlanConcurrency::getNTimeSteps() {
	int retVal = 0;
	for(int i = 0; i < _timeLines.size(); i++) {
		int a = _timeLines[i]->getNTimeSteps();
		if(a > retVal) retVal = a;
	}
	return retVal;
}

int ConcurrentPlanConcurrency::getNTotalTimelines() {
	int retVal = 0;
	for(int i = 0; i <  _timeLines.size(); i++) {
		retVal += _timeLines[i]->getNTotalTimelines();
	}
	return retVal;
}

bool ConcurrentPlanConcurrency::doesntInterfere(ParamList &pl) {
	bool retVal = true;
	for(int i = 0; ((i < _timeLines.size()) && (retVal)); i++) {
		retVal = _timeLines[i]->doesntInterfere(pl);
	}
	return retVal;
}

pair<int, int> ConcurrentPlanConcurrency::fillInPlanMat(
	ConcurrentPlanStep ***steps, int startRow, int startCol) {
	pair<int, int> retVal;
	for(int i = 0; i <  _timeLines.size(); i++) {
		pair<int, int> a = _timeLines[i]->fillInPlanMat(
			steps, retVal.first + startRow, startCol);
		retVal.first += a.first;
		if(a.second > retVal.second)
			retVal.second = a.second;
	}
	return retVal;
}

void ConcurrentPlanConcurrency::fillInPlanMatTwo(ConcurrentPlanStep ***steps) {
	for(int i = 0; i <  _timeLines.size(); i++)
		_timeLines[i]->fillInPlanMatTwo(steps);
}

string ConcurrentPlanConcurrency::getString() {
	abort();
}

double ConcurrentPlanConcurrency::computePerformanceTime() {
	_timeToPerform = 0;

	for(int i = 0; i < _timeLines.size(); i++) {
		double newTime = _timeLines[i]->computePerformanceTime();
		if(newTime > _timeToPerform)
			_timeToPerform = newTime;
	}

	return _timeToPerform;
}

int ConcurrentPlanConcurrency::computeStepLen() {
	_stepLen = 0;
	
	for(int i = 0; i < _timeLines.size(); i++) {
		int newTime = _timeLines[i]->computeStepLen();
		if(newTime > _stepLen)
			_stepLen = newTime;
	}

	return _stepLen;
}

PlanState *ConcurrentPlanConcurrency::getRootState() {
	return _rootState;
}


pair<int, int> ConcurrentPlanConcurrency::label(int startRow, int startCol,
	int printTabs) {
	for(int i = 0; i < printTabs; i++) cout << "	";
	//cout << "ConcurrentPlanConcurrency::label:	" << startRow << "	" <<
	//	startCol << "	" << _timeLines.size() << endl;

	pair<int, int> retVal;
	retVal.first = 0;
	retVal.second = 0;

	for(int i = 0; i <  _timeLines.size(); i++) {
		pair<int, int> a =
			_timeLines[i]->label(
				retVal.first + startRow, startCol, printTabs + 1);
		retVal.first += a.first;
		if(a.second > retVal.second)
			retVal.second = a.second;
	}

	//retVal.first -= 1;

	for(int i = 0; i < printTabs; i++) cout << "	";
	//cout << "/ConcurrentPlanConcurrency::label:	" << startRow << "	" <<
	//	startCol << "	" << retVal.first << "	" << retVal.second << endl;
	return retVal;
}

bool ConcurrentPlanConcurrency::isAPL() {
	return false;
}

ParamList *ConcurrentPlanConcurrency::getPL() {
	return NULL;
}
