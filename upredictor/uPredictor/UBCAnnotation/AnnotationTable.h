#ifndef ANNOTATION_TABLE_H
#define ANNOTATION_TABLE_H

#include <fstream>
#include <vector>

using namespace std;

class AnnotationClassTable;
class AnnotationObject;
class AnnotationTableListener;

class AnnotationTable {
public:
	AnnotationTable(AnnotationClassTable *act);
	~AnnotationTable();

	AnnotationObject *addNew(int classID);
	AnnotationObject *get(size_t index);
	void deleteObj(AnnotationObject *ao);
	size_t getNAnnotation();
	void clear();
	
	AnnotationClassTable *getACT();

	void save(fstream &f);
	void load(fstream &f);

	void addListener(AnnotationTableListener *l);

protected:
	AnnotationClassTable *_act;
	vector <AnnotationObject *> _ao;

	vector <AnnotationTableListener *> _l;
};

#endif