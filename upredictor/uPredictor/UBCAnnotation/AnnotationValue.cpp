#include "AnnotationValue.h"

AnnotationValue::AnnotationValue(AnnotationType *type) : _type(type) {}

AnnotationValue::~AnnotationValue() {}

AnnotationType *AnnotationValue::getType() {
	return _type;
}