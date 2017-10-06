#include "AnnotationTable.h"
#include "AnnotationClass.h"
#include "AnnotationClassTable.h"
#include "AnnotationObject.h"
#include "AnnotationTableListener.h"

#include <algorithm>

AnnotationTable::AnnotationTable(AnnotationClassTable *act) : _act(act) {}

AnnotationTable::~AnnotationTable() {}

AnnotationObject *AnnotationTable::addNew(int classID) {
	AnnotationClass *ac = _act->getClassByID(classID);
	AnnotationObject *ao = ac->createAO();
	_ao.push_back(ao);

	for (int i = 0; i < _l.size(); i++) _l[i]->addAnnotationObject(this, ao);

	return ao;
}

AnnotationObject *AnnotationTable::get(size_t index) {
	return _ao[index];
}

void AnnotationTable::deleteObj(AnnotationObject *ao) {
	abort();
	vector <AnnotationObject *>::iterator iter =
		find(_ao.begin(), _ao.end(), ao);
	delete ao;
	_ao.erase(iter);
}

size_t AnnotationTable::getNAnnotation() {
	return _ao.size();
}

void AnnotationTable::clear() {
	for (int i = 0; i < _ao.size(); i++) delete _ao[i];
	_ao.clear();

	for (int i = 0; i < _l.size(); i++) _l[i]->clearAnnotationObjects(this);
}

AnnotationClassTable *AnnotationTable::getACT() {
	return _act;
}

void AnnotationTable::save(fstream &f) {
	int nAnnotation = _ao.size();
	f.write((char *)&nAnnotation, sizeof(int));
	for (int i = 0; i < nAnnotation; i++) {
		AnnotationObject *ao = _ao[i];
		ao->save(f);
	}
}

void AnnotationTable::load(fstream &f) {
	int nAnnotation;// = _ao.size();
	f.read((char *)&nAnnotation, sizeof(int));
	for (int i = 0; i < nAnnotation; i++) {
		AnnotationObject *ao = new AnnotationObject(f, _act);
		_ao.push_back(ao);
		for (int i = 0; i < _l.size(); i++)
			_l[i]->addAnnotationObject(this, ao);
	}
}

void AnnotationTable::addListener(AnnotationTableListener *l) {
	_l.push_back(l);
}