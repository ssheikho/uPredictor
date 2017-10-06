#include "domainmap.h"
#include "domain.h"
#include <iostream>

DomainMap::DomainMap() {}

DomainMap::~DomainMap() {
	for(
		map<string, bool>::iterator iter = _maintainPointer.begin();
		iter != _maintainPointer.end(); iter++) {
		if(iter->second) delete _m[iter->first];
	}
}

void DomainMap::insertDomain(Domain *d, bool maintainPointer) {
	_m[d->getName()] = d;
	_maintainPointer[d->getName()] = maintainPointer;
}

Domain *DomainMap::newDomain(string name) {
	Domain *newDomain = new Domain(name);
	insertDomain(newDomain, true);
	return newDomain;
}

Domain *DomainMap::getDomain(string name) {
	return _m[name];
}
