#include "AnnotationClass.h"
#include "AnnotationObject.h"
#include "AnnotationTypeTable.h"
#include "UBCUtil.h"

AnnotationClass::AnnotationClass(vector<string> fromLine,
	AnnotationTypeTable *att) : _att(att) {
	_id = atoi(fromLine[0].c_str());
	_name = fromLine[1];
	int nFields = atoi(fromLine[2].c_str());
	for (int i = 0; i < nFields; i++) {
		string field = fromLine[(i * 2) + 3];
		string fieldName = fromLine[(i * 2) + 4];
		const char *fieldC = field.c_str();
		int fieldI = atoi(fieldC);
		_fields.push_back(fieldI);
		_fieldNames.push_back(fieldName);
	}

	//act->add(this);
}

AnnotationClass::~AnnotationClass() {}

int AnnotationClass::getID() {
	return _id;
}

string AnnotationClass::getName() {
	return _name;
}

int AnnotationClass::getFieldID(int index) {
	return _fields[index];
}

string AnnotationClass::getFieldNameS(int index) {
	return _fieldNames[index];
}

wstring AnnotationClass::getFieldNameW(int index) {
	return stringToWString(_fieldNames[index]);
}

AnnotationType *AnnotationClass::getFieldType(int index) {
	return _att->getATByID(_fields[index]);
}

size_t AnnotationClass::getNFields() {
	return _fields.size();
}

AnnotationObject *AnnotationClass::createAO() {
	return new AnnotationObject(this);
}
