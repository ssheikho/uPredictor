#include "actionmap.h"
#include <iostream>

ActionMap::ActionMap(Domain &domain) : _domain(domain) {}
ActionMap::~ActionMap() {}

Action *ActionMap::insert(string name,
	vector<string> &nameList, vector<string> &typeList) {
	Action *retVal = new Action(name, nameList, typeList, _domain, _ctr);
	_v.push_back(retVal);
	_m[name] = _ctr++;
	return retVal;
}

int ActionMap::resolveIndex(string name) {
	return _m[name];
}

Action *ActionMap::getAction(int index) {
	return _v[index];
}

int ActionMap::nActions() {
	return _v.size();
}

void ActionMap::printContents() {
	cout << "Actions:	" << endl;
	for(int i = 0; i < _v.size(); i++)
		_v[i]->printContents();
}
