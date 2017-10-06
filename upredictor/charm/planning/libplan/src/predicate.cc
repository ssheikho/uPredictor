#include "predicate.h"
#include "domain.h"
#include <iostream>

Predicate::Predicate(string name, vector<string> &parameters,
	vector<string> &types, Domain &domain, int index) :
	_name(name), _domain(domain),
	_nparam(parameters.size()),
	_parameters(new string[_nparam]), _types(new int[_nparam]), _index(index) {
	for(int i = 0; i < _nparam; i++) {
		_parameters[i] = parameters[i];
		_types[i] = _domain.types().getIndex(types[i]);
	}
}

Predicate::~Predicate() {
	delete[] _parameters;
	delete[] _types;
}

int Predicate::getNParam() {
	return _nparam;
}

int Predicate::getIndex() {
	return _index;
}

int Predicate::getParamType(int index) {
	return _types[index];
}

string Predicate::getName() {
	return _name;
}

void Predicate::printContents() {
	cout << "Predicate:	" << _name << endl;
	for(int i = 0; i < _nparam; i++)
		cout << "	" << _parameters[i] << "	" <<
			_domain.types().getName(_types[i]) << endl;
}
