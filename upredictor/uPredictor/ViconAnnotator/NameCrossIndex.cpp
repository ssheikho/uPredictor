#include "NameCrossIndex.h"

#include <iostream>

using namespace std;

NameCrossIndex::NameCrossIndex() {}
NameCrossIndex::~NameCrossIndex() {}

void NameCrossIndex::insert(string name, int index) {
	_indexToName.insert(pair<int, string>(index, name));
	_nameToIndex.insert(pair<string, int>(name, index));
}

string NameCrossIndex::getNameAtIndex(int index) {
	return _indexToName[index];
}

int NameCrossIndex::getIndexWithName(string name) {
	return _nameToIndex[name];
}

void NameCrossIndex::printTable() {
	for(map<int, string>::iterator iter = _indexToName.begin()
		; iter != _indexToName.end(); iter++)
		cout << iter->first << "	" << iter->second << endl;
}
