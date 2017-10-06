#include "planstatepredtable.h"
#include "domain.h"
#include "objecttable.h"
#include "planstatepred.h"
#include "problem.h"

#include <cstdlib>
#include <iostream>

PlanStatePredTable::PlanStatePredTable() : _predCtr(0) {}


void PlanStatePredTable::preCacheAllPermutes(Problem *problem) {
	Domain &d = problem->getDomain();
	PredicateMap &pm = d.predicates();
	ObjectTable &ot = problem->getObjectTable();

	for(int i = 0; i < pm.size(); i++)
		insertAllPermutes(problem, pm.getPred(i), ot);
}

void PlanStatePredTable::insertAllPermutes(
	Problem *problem, Predicate &pred, ObjectTable &ot) {
	//cout << "insertAllPermutes" << endl;
	int objs[pred.getNParam()];
	insertAllPermutes(problem, pred, ot, objs, 0);
}

void PlanStatePredTable::insertAllPermutes(
	Problem *problem, Predicate &pred, ObjectTable &ot, int *objs, int pos) {
	if(pos == pred.getNParam()) {
		int *objcpy = new int[pos];
		for(int i = 0; i < pos; i++) objcpy[i] = objs[i];
		//cout << "PRECACHING A PREDICATE" << endl;
		PlanStatePred *p =
			new PlanStatePred(
				pred.getIndex(), pos, objcpy, _predCtr++, problem);
		insert(p);
	} else {
		int type = pred.getParamType(pos);
		vector<int> &objV = ot.getAllOfType(type);
		for(int i = 0; i < objV.size(); i++) {
			objs[pos] = objV[i];
			insertAllPermutes(problem, pred, ot, objs, pos + 1);
		}
	}
}

PlanStatePredTable::~PlanStatePredTable() {
	for(int i = 0; i < _v.size(); i++) {
		delete _v[i];
	}
}

PlanStatePred *PlanStatePredTable::getPredicate(
	int pred, vector<string> &vals, Problem *problem) {
	int *objects = new int[vals.size()];
	ObjectTable &obj = problem->getObjectTable();

	for(int i = 0; i < vals.size(); i++)
		objects[i] = obj.getObjectID(vals[i]);

	return getPredicate(pred, vals.size(), objects, problem);
}

PlanStatePred *PlanStatePredTable::getPredicate(
	int pred, int nobj, int *objs, Problem *problem) {
	PlanStatePred *retVal = NULL;

	vector<PlanStatePred *> &v = _preds[pred];
	for(int i = 0; i < v.size(); i++)
		if(v[i]->equals(pred, nobj, objs))
			retVal = v[i];

	return retVal;
}

void PlanStatePredTable::insert(PlanStatePred *p) {
	_preds[p->getPred()].push_back(p);
	_v.push_back(p);
}
