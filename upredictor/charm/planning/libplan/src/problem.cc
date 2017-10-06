#include "problem.h"
#include "planninggraph.h"

Problem::Problem(Domain &domain, string name) : _domain(domain), _name(name),
	_objectTable(this), _pg(NULL),
	_rootState(new PlanState(this, _pspt)), _goalState(this, _pspt) {}

Problem::~Problem() {}

string Problem::getName() {
	return _name;
}

Domain &Problem::getDomain() {
	return _domain;
}

ObjectTable &Problem::getObjectTable() {
	return _objectTable;
}

PlanStatePredTable &Problem::getPSPT() {
	return _pspt;
}

void Problem::generatePG() {
	_pg = new PlanningGraph(this);
}

PlanningGraph &Problem::getPG() {
	return *_pg;
}

PlanState &Problem::getRootState() {
	return *_rootState;
}

PlanState &Problem::getGoalState() {
	return _goalState;
}
