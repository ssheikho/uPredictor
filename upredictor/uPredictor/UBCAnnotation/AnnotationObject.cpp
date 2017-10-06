#include "AnnotationObject.h"
#include "AnnotationClass.h"
#include "AnnotationClassTable.h"
#include "AnnotationType.h"
#include "AnnotationValue.h"

AnnotationObject::AnnotationObject(AnnotationClass *ac) : _ac(ac) {
	populateEmptyFieldsFromClass();
}

AnnotationObject::AnnotationObject(fstream &f, AnnotationClassTable *act) {
	load(f, act);
}

AnnotationObject::~AnnotationObject() {}

AnnotationClass *AnnotationObject::getClass() {
	return _ac;
}

AnnotationValue *AnnotationObject::getAV(int index) {
	AnnotationValue *av = _values[index];
	return av;
}

void AnnotationObject::save(fstream &f) {
	int classID = _ac->getID();
	f.write((char *)&classID, sizeof(int));

	for (int i = 0; i < _values.size(); i++)
		_values[i]->save(f);
}

void AnnotationObject::load(fstream &f, AnnotationClassTable *act) {
	int classID;
	f.read((char *)&classID, sizeof(int));
	_ac = act->getClassByID(classID);
	_ac;

	populateEmptyFieldsFromClass();

	for (int i = 0; i < _values.size(); i++)
		_values[i]->load(f);
}

void AnnotationObject::populateEmptyFieldsFromClass() {
	for (int field = 0; field < _ac->getNFields(); field++) {
		AnnotationType *at = _ac->getFieldType(field);
		AnnotationValue *av = at->createValueInstance();
		_values.push_back(av);
	}
}