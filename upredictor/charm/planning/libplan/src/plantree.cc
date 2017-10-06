#include "plantree.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "plan.h"
#include "planninggraph.h"
#include "planstate.h"
#include <iostream>

PlanTree::PlanTree(int paramList, int state, PlanTree *parent,
	ParamListTable &plt, PlanningGraph *pg) :
	_paramList(paramList), _state(state), _id(-1), _parent(parent), _plt(plt),
	_pg(pg) {
	//cout << "Constructing plan tree" << endl;
}

PlanTree::~PlanTree() {
	for(map<int, PlanTree *>::iterator i = _m.begin(); i != _m.end(); i++)
		delete i->second;
}

void PlanTree::insert(Plan &p, int atActionNumber) {
	int act = p.getParamList(atActionNumber);
	int state = p.getState(atActionNumber + 1);
	if(_m.count(act)) {
		_m[act]->insert(p, atActionNumber + 1);
	} else {
		if(atActionNumber < (p.getNStates() - 1)) {
			PlanTree *pt =  new PlanTree(act, state, this, _plt, _pg);
			_m[act] = pt;
			_v.push_back(pt);
			pt->insert(p, atActionNumber + 1);
		} else {
			//printPlanToHere(true, true);
		}
	}
}

void PlanTree::printPlanToHere(bool end, bool mnemoic) {
	if(_parent) _parent->printPlanToHere(false, mnemoic);
	if(mnemoic) {
		if(_paramList != -1) {
			if(end) {
				_plt.getPL(_paramList).printContents(false);
				cout << endl;
			} else {
				_plt.getPL(_paramList).printContents(false);
				cout << "->";
			}
		}
	} else {
		if(end) {
			cout << "[" << _paramList << "]" << endl;
		} else {
			cout << "[" << _paramList << "]->";
		}
	}
}

map<int, PlanTree *> &PlanTree::getChildren() {
	return _m;
}

PlanTree *PlanTree::getChildByIndex(int index) {
	return _v[index];
}

int PlanTree::getNumChildNodes() {
	return _v.size();
}

int PlanTree::getParamList() {
	return _paramList;
}

int PlanTree::getState() {
	return _state;
}

bool PlanTree::canDoChild(PlanTree *pt) {
	return (_parent == NULL) ? false :
		_pg->getPST().getState(_parent->_state).preconditionsMet(
			_plt.getPL(pt->_paramList));
}

int PlanTree::idLabelTree() {
	idLabelTree(0);
}

int PlanTree::idLabelTree(int startAt) {
	int idTrack = _id = startAt;

	for(map<int, PlanTree *>::iterator i = _m.begin(); i != _m.end(); i++)
		idTrack += i->second->idLabelTree(idTrack);

	return idTrack;
}

int PlanTree::getID() {
	return _id;
}
