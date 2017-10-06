#include "AnnotationUINT64Value.h"

AnnotationUINT64Value::AnnotationUINT64Value(AnnotationType *type) :
AnnotationValue(type), _value(0) {}

AnnotationUINT64Value::~AnnotationUINT64Value() {}

void AnnotationUINT64Value::set(UINT64 val) {
	_value = val;
}

UINT64 AnnotationUINT64Value::get() {
	return _value;
}

/*
void AnnotationUINT64Value::setUINT64Val(UINT64 v) {
	set(v);
}

UINT64 AnnotationUINT64Value::getUINT64Val() {
	return get();
}
*/

void AnnotationUINT64Value::save(fstream &f) {
	f.write((char *)&_value, sizeof(UINT64));
}

void AnnotationUINT64Value::load(fstream &f) {
	f.read((char *)&_value, sizeof(UINT64));
	_value = _value;
}