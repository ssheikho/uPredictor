#ifndef ANNOTATION_CLASS_TABLE_H
#define ANNOTATION_CLASS_TABLE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class AnnotationClass;
class AnnotationTypeTable;

class AnnotationClassTable {
public:
	AnnotationClassTable(string filename, AnnotationTypeTable *att);
	~AnnotationClassTable();

	AnnotationClass *getClassByID(int id);
	int getClassIDByIndex(int index);
	int getNClases();

protected:
	void add(AnnotationClass *ac);

	map<int, AnnotationClass *> _ac;
	vector<AnnotationClass *> _acV;

};

#endif
