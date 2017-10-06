#include "predicatemap.h"
#include <iostream>

PredicateMap::PredicateMap(Domain &domain) : _domain(domain), _ctr(0) {}
PredicateMap::~PredicateMap() {}

void PredicateMap::insert(string name,
	vector<string> &parameters, vector<string> &types) {
	Predicate *p = new Predicate(name, parameters, types, _domain, _ctr);
	_m[name] = _ctr;
	_v.push_back(p);
	_ctr++;
}

Predicate &PredicateMap::getPred(int index) {
	return *_v[index];
}

int PredicateMap::size() {
	return _v.size();
}

string PredicateMap::getName(int i) {
	return _v[i]->getName();
}

int PredicateMap::getIndex(string name) {
	return _m[name];
}

void PredicateMap::printContents() {
	cout << "Predicates:" << endl;
	for (int i = 0; i < _v.size(); i++) {
		cout << "----" << i << "----" << endl;
		_v[i]->printContents();
	}
	cout << "----" << endl;
}
