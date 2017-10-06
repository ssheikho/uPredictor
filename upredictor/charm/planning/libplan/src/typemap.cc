#include "typemap.h"
#include <iostream>

TypeMap::TypeMap() : _ctr(0) {}
TypeMap::~TypeMap() {}

void TypeMap::insert(string name) {
	_m[name] = _ctr++;
	_v.push_back(name);
}

int TypeMap::size() {
	return _v.size();
}

string TypeMap::getName(int i) {
	return _v[i];
}

int TypeMap::getIndex(string name) {
	return _m[name];
}

void TypeMap::printContents() {
	cout << "Types:" << endl;
	for (int i = 0; i < _v.size(); i++)
		cout << "	" << _v[i] << endl;
}
