#ifndef ANNOTATION_TYPE_H
#define ANNOTATION_TYPE_H

#include "AnnotationUtil.h"

#include <string>

using namespace std;

class AnnotationValue;

class AnnotationType {
public:
	AnnotationType(int typeID, AnnotationTypes type, string name);
	~AnnotationType();

	AnnotationTypes getType();
	string getName();

	AnnotationValue *createValueInstance();
	
protected:
	int _typeID;
	AnnotationTypes _type;
	string _name;
};

#endif