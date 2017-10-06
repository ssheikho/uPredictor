#include "AnnotationRecTimeValue.h"

AnnotationRecTimeValue::AnnotationRecTimeValue(AnnotationType *type,
	RecPlayer *rp) : AnnotationIntValue(type), _rp(rp) {}

AnnotationRecTimeValue::~AnnotationRecTimeValue() {}

RecPlayer *AnnotationRecTimeValue::getRP() {
	return _rp;
}