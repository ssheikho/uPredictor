#ifndef ANNOTATION_VALUE_H
#define ANNOTATION_VALUE_H

#include <fstream>

using namespace std;

class AnnotationType;

class AnnotationValue {
public:
	AnnotationValue(AnnotationType *type);
	virtual ~AnnotationValue();

	AnnotationType *getType();

	virtual void save(fstream &f) = 0;
	virtual void load(fstream &f) = 0;

protected:
	AnnotationType *_type;
};

#endif