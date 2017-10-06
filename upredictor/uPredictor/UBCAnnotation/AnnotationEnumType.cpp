#include "AnnotationEnumType.h"

AnnotationEnumType::AnnotationEnumType(int typeID, string name) :
AnnotationType(typeID, AnnotationTypes::enumerated, name) {}
AnnotationEnumType::~AnnotationEnumType() {}

void AnnotationEnumType::addValue(int val, string name) {
	_names[val] = name;
	_values[name] = val;
}

int AnnotationEnumType::getNValues() {
	return _values.size();
}

int AnnotationEnumType::getValue(string name) {
	return _values[name];
}

string AnnotationEnumType::getString(int value) {
	return _names[value];
}

int AnnotationEnumType::getValueAtIndex(int index) {
	map<int, string>::iterator iter = _names.begin();
	for (int i = 0; i < index; i++) iter++;
	return iter->first;
}