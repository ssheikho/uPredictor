#include "AnnotationTypeTable.h"
#include "AnnotationEnumType.h"
#include "UBCUtil.h"

#include <sstream>

//stackoverflow.com/questions/5607589/
//right-way-to-split-an-stdstring-into-a-vectorstring
AnnotationTypeTable::AnnotationTypeTable(string filename) {
	ifstream f;
	f.open(filename.c_str(), ios::in);

	string line;
	while (getline(f, line)) {
		vector<string> vstrings = splitString(line);
		int id = atoi(vstrings[0].c_str());
		string typeName = vstrings[1];
		int type = atoi(vstrings[2].c_str());
		switch (type) {
		case 0:
			addEnumeratedType(id, typeName, type, vstrings);
			break;
		default:
			AnnotationType *at =
				new AnnotationType(id, (AnnotationTypes)type, typeName);
			_at[id] = at;
			_atV.push_back(at);
			break;
		}
	}

	f.close();
}

AnnotationTypeTable::~AnnotationTypeTable() {}

void AnnotationTypeTable::addEnumeratedType(int id, string typeName, int type,
	vector<string> vstrings) {
	AnnotationEnumType *aet = new AnnotationEnumType(id, typeName);

	int nElem = atoi(vstrings[3].c_str());
	for (int i = 0; i < nElem; i++)
		aet->addValue(i, vstrings[4 + i]);

	_at[id] = aet;
	_atV.push_back(aet);
}

AnnotationType *AnnotationTypeTable::getATByID(int id) {
	return _at[id];
}

AnnotationType *AnnotationTypeTable::getATByIndex(int index) {
	return _atV[index];
}

int AnnotationTypeTable::getNAT() {
	return _atV.size();
}
