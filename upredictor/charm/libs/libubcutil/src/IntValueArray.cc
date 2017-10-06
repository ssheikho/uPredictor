#include "IntValueArray.h"
#include "IntValueArrayListener.h"

IntValueArray::~IntValueArray() {}

void IntValueArray::addIVAListener(IntValueArrayListener *ival) {
	_ival.push_back(ival);
}

void IntValueArray::removeIVAListener(IntValueArrayListener *ival) {
	vector<IntValueArrayListener *>::iterator iter = find(_ival.begin(), _ival.end(), ival);
	if (iter != _ival.end()) {
		_ival.erase(iter);
	}
}

void IntValueArray::fireUpdate(int index, int value, void *origin) {
	int s = _ival.size();
	for (int i = 0; i < s; i++) {
		//shared_ptr<IntValueArray> iva = shared_ptr<IntValueArray>(this);
		_ival[i]->updateIVAL(this, index, value, origin);
	}
}