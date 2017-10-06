#include "IntValueArrayMultiplexer.h"

IntValueArrayMultiplexer::IntValueArrayMultiplexer() {}

IntValueArrayMultiplexer::~IntValueArrayMultiplexer() {
	for (size_t i = 0; i < _deleteOnDestructor.size(); i++) {
		if (_deleteOnDestructor[i]) delete _iva[i];
	}
}

void IntValueArrayMultiplexer::set(int index, int value, void *origin) {
	if (origin != this) {
		size_t s = _iva.size();
		for (size_t i = 0; i < s; i++) {
			IntValueArray *iva = _iva[i];
			int nVals = iva->getNVals();
			if (nVals > index) {
				iva->set(index, value, origin);
			}
		}
		fireUpdate(index, value, origin);
	}
}

int IntValueArrayMultiplexer::get(int index) {
	int retVal = 0;
	bool found = false;
	for (size_t i = 0; (i < _iva.size()) && (!found); i++) {
		IntValueArray *iva = _iva[i];
		if(
			(iva->getNVals() > index) &&
			(_getFromThis[i])
			){
			retVal = iva->get(index);
			found = true;
		}
	}
	return retVal;
}

bool IntValueArrayMultiplexer::hasMin(int index) {
	bool retVal = false;
	for (size_t i = 0; i < _iva.size(); i++) {
		IntValueArray *iva = _iva[i];
		if (iva->getNVals() > index) {
			if (iva->hasMin(index)) retVal = true;
		}
	}
	return retVal;
}

bool IntValueArrayMultiplexer::hasMax(int index) {
	bool retVal = false;
	for (size_t i = 0; i < _iva.size(); i++) {
		IntValueArray *iva = _iva[i];
		if (iva->getNVals() > index) {
			if (iva->hasMax(index)) retVal = true;
		}
	}
	return retVal;
}

int IntValueArrayMultiplexer::getMinVal(int index) {
	int minVal = 0;
	bool foundMinVal = false;
	for (size_t i = 0; i < _iva.size(); i++) {
		IntValueArray *iva = _iva[i];
		int nVals = iva->getNVals();
		if (nVals > index) {
			bool hasmin = iva->hasMin(index);
			if (hasmin) {
				int minTemp = iva->getMinVal(index);
				if ((!foundMinVal) || (minTemp > minVal))
					minVal = minTemp;
				foundMinVal = true;
			}
		}
	}
	return minVal;
}

int IntValueArrayMultiplexer::getMaxVal(int index) {
	int maxVal = 0;
	bool foundMaxVal = false;
	for (size_t i = 0; i < _iva.size(); i++) {
		IntValueArray *iva = _iva[i];
		if (iva->getNVals() > index) {
			if (iva->hasMax(index)) {
				int maxTemp = iva->getMaxVal(index);
				if ((!foundMaxVal) || (maxTemp < maxVal))
					maxVal = maxTemp;
				foundMaxVal = true;
			}
		}
	}
	return maxVal;
}

size_t IntValueArrayMultiplexer::getNVals() {
	size_t nVals = 0;
	size_t s = _iva.size();
	for (size_t i = 0; i < s; i++) {
		size_t newVals = _iva[i]->getNVals();
		if (newVals > nVals) nVals = newVals;
	}
	return nVals;
}

void IntValueArrayMultiplexer::addIVA(IntValueArray *iva,
	bool deleteOnDestructor, bool getFromThis) {
	//iva->addIVAListener(this);
	_iva.push_back(iva);
	_deleteOnDestructor.push_back(deleteOnDestructor);
	_getFromThis.push_back(getFromThis);
}

void IntValueArrayMultiplexer::updateIVAL(IntValueArray *iva, int index, int value,
	void *origin) {
	set(index, value, origin);
}