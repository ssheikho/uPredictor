#ifndef ANNOTATION_ENUM_TYPE_H
#define ANNOTATION_ENUM_TYPE_H

#include "AnnotationType.h"

#include <map>
#include <string>

using namespace std;

class AnnotationEnumType :
	public AnnotationType {
public:
	AnnotationEnumType(int typeID, string name);
	~AnnotationEnumType();

	void addValue(int val, string name);
	int getNValues();
	int getValue(string name);
	string getString(int value);
	int getValueAtIndex(int index);

protected:
	map<int, string> _names;
	map<string, int> _values;
};

#endif