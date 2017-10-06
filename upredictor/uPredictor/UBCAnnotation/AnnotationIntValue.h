#ifndef ANNOTATION_INT_VALUE_H
#define ANNOTATION_INT_VALUE_H

#include "AnnotationValue.h"
//#include "IntValueArray.h"

class AnnotationIntValue : public AnnotationValue
	//, public IntValueArray
{
public:
	AnnotationIntValue(AnnotationType *type);
	virtual ~AnnotationIntValue();

	void set(int val);
	int get();

	void save(fstream &f);
	void load(fstream &f);

	/*
	//From IntValueArray
	void set(int index, int value, void *origin);
	int get(int index);

	bool hasMin(int index);
	bool hasMax(int index);
	int getMinVal(int index);
	int getMaxVal(int index);

	size_t getNVals();
	*/

protected:
	int _value;
};

#endif