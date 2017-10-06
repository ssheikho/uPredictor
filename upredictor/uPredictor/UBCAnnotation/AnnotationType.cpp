#include "AnnotationType.h"
#include "AnnotationIntValue.h"
#include "AnnotationRecTimeValue.h"
#include "AnnotationUINT64Value.h"

AnnotationType::AnnotationType(int typeID, AnnotationTypes type, string name) :
_typeID(typeID), _type(type), _name(name) {}

AnnotationType::~AnnotationType() {}

AnnotationTypes AnnotationType::getType() {
	return _type;
}

string AnnotationType::getName() {
	return _name;
}

AnnotationValue *AnnotationType::createValueInstance() {
	AnnotationValue *av = NULL;
	switch (_type) {
	case AnnotationTypes::enumerated:
	case AnnotationTypes::recTime:
		av = new AnnotationIntValue(this);
		break;
	case AnnotationTypes::trackId:
		av = new AnnotationUINT64Value(this);
		break;
	}

	return av;
}