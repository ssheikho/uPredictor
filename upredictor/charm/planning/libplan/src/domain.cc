#include "domain.h"
#include "problem.h"
#include <iostream>

using namespace std;

Domain::Domain() {
	_predicates = new PredicateMap(*this);
	_actions = new ActionMap(*this);
}

Domain::Domain(string name) : _name(name) {
	_predicates = new PredicateMap(*this);
	_actions = new ActionMap(*this);
}

Domain::~Domain() {}

void Domain::setName(string name) {
	_name = name;
}

string Domain::getName() {
	return _name;
}

void Domain::printContents() {
	cout << "Domain:	" << _name << endl;
	_types.printContents();
	_predicates->printContents();
	_actions->printContents();
}

TypeMap &Domain::types() {
	return _types;
}

PredicateMap &Domain::predicates() {
	return *_predicates;
}

ActionMap &Domain::actions() {
	return *_actions;
}

NoConcurTable &Domain::NCT() {
	return _nct;
}

Problem *Domain::newProblem(string name) {
	return _m[name] = new Problem(*this, name);
}

Problem *Domain::getProblem(string name) {
	return _m[name];
}

