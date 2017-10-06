#ifndef ANNOTATION_CLASS_H
#define ANNOTATION_CLASS_H

#include <string>
#include <vector>

using namespace std;

class AnnotationClassTable;
class AnnotationObject;
class AnnotationType;
class AnnotationTypeTable;

class AnnotationClass {
public:
	AnnotationClass(vector<string> fromLine, AnnotationTypeTable *att);
	~AnnotationClass();

	int getID();
	string getName();
	int getFieldID(int index);
	string getFieldNameS(int index);
	wstring getFieldNameW(int index);
	AnnotationType *getFieldType(int index);
	size_t getNFields();

	AnnotationObject *createAO();

protected:
	AnnotationTypeTable *_att;
	int _id;
	string _name;
	vector<int> _fields;
	vector<string> _fieldNames;
};

#endif