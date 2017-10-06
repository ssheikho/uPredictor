#include "AnnotationIntValue.h"

AnnotationIntValue::AnnotationIntValue(AnnotationType *type) :
AnnotationValue(type), _value(0) {
	AnnotationIntValue *aiv = this;
}

AnnotationIntValue::~AnnotationIntValue() {}

void AnnotationIntValue::set(int val) {
	_value = val;
}

int AnnotationIntValue::get() {
	return _value;
}

void AnnotationIntValue::save(fstream &f) {
	f.write((char *) &_value, sizeof(int));
}

void AnnotationIntValue::load(fstream &f) {
	f.read((char *)&_value, sizeof(int));
}

/*
void AnnotationIntValue::set(int index, int value, void *origin) {
	set(value);
}

int AnnotationIntValue::get(int index) {
	return get();
}

bool AnnotationIntValue::hasMin(int index) {
	return false;
}

bool AnnotationIntValue::hasMax(int index) {
	return false;
}

int AnnotationIntValue::getMinVal(int index) {
	return 0;
}

int AnnotationIntValue::getMaxVal(int index) {
	return 0;
}

size_t AnnotationIntValue::getNVals() {
	return 1;
}
*/