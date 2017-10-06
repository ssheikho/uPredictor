#include "DefaultIntValueArray.h"

DefaultIntValueArray::DefaultIntValueArray() {}
DefaultIntValueArray::~DefaultIntValueArray() {}

void DefaultIntValueArray::set(int index, int value, void *origin) {
	if (origin != this)	_val[index] = value;
}

int DefaultIntValueArray::get(int index) {
	return _val[index];
}

bool DefaultIntValueArray::hasMin(int index) {
	return _hasMin[index];
}

bool DefaultIntValueArray::hasMax(int index) {
	return _hasMax[index];
}

int DefaultIntValueArray::getMinVal(int index) {
	return _min[index];
}

int DefaultIntValueArray::getMaxVal(int index) {
	return _max[index];
}

size_t DefaultIntValueArray::getNVals() {
	return _hasMin.size();
}

void DefaultIntValueArray::addValue(bool hasMin, bool hasMax, int min, int max, int val) {
	_hasMin.push_back(hasMin);	_hasMax.push_back(hasMax);
	_min.push_back(min);		_max.push_back(max);		_val.push_back(val);
}