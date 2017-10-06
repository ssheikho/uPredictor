#include "AnnotationClassTable.h"
#include "AnnotationClass.h"
#include "UBCUtil.h"

#include <fstream>
#include <cstdlib>

AnnotationClassTable::AnnotationClassTable(string filename,
	AnnotationTypeTable *att) {
	ifstream f;
	f.open(filename.c_str(), ios::in);

	string line;
	while (getline(f, line)) {
		add(new AnnotationClass(splitString(line), att));
	}

	f.close();
}

AnnotationClassTable::~AnnotationClassTable() {}

AnnotationClass *AnnotationClassTable::getClassByID(int id) {
	return _ac[id];
}

void AnnotationClassTable::add(AnnotationClass *ac) {
	_acV.push_back(ac);
	_ac[ac->getID()] = ac;
}

int AnnotationClassTable::getClassIDByIndex(int index) {
	map<int, AnnotationClass *>::iterator iter = _ac.begin();
	for (int i = 0; i < index; i++) iter++;
	return iter->first;
}

int AnnotationClassTable::getNClases() {
	return _acV.size();
}
