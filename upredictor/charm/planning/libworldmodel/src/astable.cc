#include "astable.h"
#include "actorplan.h"
#include "actorsorter.h"
#include "concurrentplan.h"
#include "concurrentplantable.h"
#include "plantable.h"

#include <iostream>

using namespace std;

ASTable::ASTable(ActorSorter &as, WorldModel &wm) : _as(as), _wm(wm) {}
ASTable::~ASTable() {}

void ASTable::clear() {
	for(int i = 0; i < _v.size(); i++) delete _v[i];
	_v.clear();
}

/*
void ASTable::update(ConcurrentPlanTable &cpt) {
	_sw.resetAndStart();
	
	clear();

	for(int i = 0; i < cpt.getNumberConcurrentPlans(); i++) {
		ConcurrentPlan &cp = cpt.getConcurrentPlan(i);

		cout << "===" << endl;
		cp.printGrid();

		ActorPlan *ap = _as.processConcurrentPlan(&cp);
		insertOrDelete(ap);
	}

	cout << "Time to ActorPlans:	" << _sw.lap() << endl;
	cout << "Numer of ActorPlans:	" << _v.size() << endl;
}
*/

void ASTable::update(PlanTable &pt) {
	_sw.resetAndStart();

	clear();
	for(int i = 0; i < pt.size(); i++) {
		Plan &plan = pt.get(i);
		ActorPlan *ap = _as.processPlan(&plan, _wm);
		//ap->compressPlan(_wm);
		//_v.push_back(ap);
		insertOrDelete(ap);
	}
	cout << "Time to ActorPlans:	" << _sw.lap() << endl;

	/*
	//vector<ActorPlan *>a = _v;
	//_v.clear();
	for(int i = 0; i < _v.size(); i++) {
	//for(int i = 0; i < a.size(); i++) {
		_v[i]->compressPlan(_wm);
		//insertOrDelete(a[i]);
	}
	cout << "Time to Compressed Plans:	" << _sw.lap() << endl;
	*/

	cout << "Numer of ActorPlans:	" << _v.size() << endl;
}

ActorPlan *ASTable::getPlan(int index) {
	return _v[index];
}

int ASTable::getNumPlans() {
	return _v.size();
}

void ASTable::insertOrDelete(ActorPlan *ap) {
	bool hasEquiv = false;
	for(int i = 0; ((i < _v.size()) && (!hasEquiv)); i++) {
		hasEquiv = ap->equals(_v[i]);
	}

	if(hasEquiv) {
		//cout << "Found equiv" << endl;
		delete ap;
	} else {
		_v.push_back(ap);
	}
}
