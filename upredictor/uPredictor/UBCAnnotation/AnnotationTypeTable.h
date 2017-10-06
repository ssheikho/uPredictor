#ifndef ANNOTATION_TYPE_TABLE_H
#define ANNOTATION_TYPE_TABLE_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class AnnotationType;

class AnnotationTypeTable {
public:
	AnnotationTypeTable(string filename);
	~AnnotationTypeTable();

	AnnotationType *getATByID(int id);
	AnnotationType *getATByIndex(int index);
	int getNAT();

protected:
	void addEnumeratedType(int id, string typeName, int type,
		vector<string> vstrings);

	map<int, AnnotationType *> _at;
	vector<AnnotationType *> _atV;

};

#endif
