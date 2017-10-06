#include "objecttable.h"
#include "domain.h"
#include "problem.h"

#include <cstdlib>
#include <iostream>

ObjectTable::ObjectTable(Problem *problem) : _problem(problem), _objectCtr(0) {}
ObjectTable::~ObjectTable() {}

void ObjectTable::populateObjects(vector<string> &ids, string type) {
	int typeI = _problem->getDomain().types().getIndex(type);
	for(int i = 0; i < ids.size(); i++) {
		_objectNames.push_back(ids[i]);
		_objectIDs[ids[i]] = _objectCtr;
		_isA[_objectCtr] = typeI;
		_byType[typeI].push_back(_objectCtr);
		_objectCtr++;
	}
}

void ObjectTable::printContents() {
	cout << "====Objects====" << endl;
	for(map<int, int>::iterator iter = _isA.begin(); iter != _isA.end();
		iter++) {
		cout << "	" << _objectNames[iter->first] << "	" << 
			_problem->getDomain().types().getName(iter->second) << endl;
	}
}

int ObjectTable::getObjectID(string name) {
	return _objectIDs[name];
}

string ObjectTable::getObjectName(int id) {
	return _objectNames[id];
}

bool ObjectTable::isA(int object, int type) {
	if(object >= _objectCtr) abort();
	return _isA[object] == type;
}

vector<int> &ObjectTable::getAllOfType(int type) {
	return _byType[type];
}

int ObjectTable::findFirst(int type) {
	return findNext(0, type);
}

int ObjectTable::findNext(int atOrAfter, int type) {
	int retVal = -1;
	for(int i = atOrAfter; (i < _objectCtr) && (retVal == -1); i++)
		if(isA(i, type)) retVal = i;
	return retVal;
}

int ObjectTable::nObj() {
	return _objectCtr;
}
