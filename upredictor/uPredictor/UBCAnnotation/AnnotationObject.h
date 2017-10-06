#ifndef ANNOTATION_OBJECT_H
#define ANNOTATION_OBJECT_H

#include <fstream>
#include <vector>

using namespace std;

class AnnotationClass;
class AnnotationClassTable;
class AnnotationValue;

class AnnotationObject {
public:
	AnnotationObject(AnnotationClass *ac);
	AnnotationObject(fstream &f, AnnotationClassTable *act);
	~AnnotationObject();

	AnnotationClass *getClass();
	AnnotationValue *getAV(int index);

	void save(fstream &f);
	void load(fstream &f, AnnotationClassTable *act);

protected:
	void populateEmptyFieldsFromClass();

	AnnotationClass *_ac;
	vector<AnnotationValue *> _values;
};

#endif