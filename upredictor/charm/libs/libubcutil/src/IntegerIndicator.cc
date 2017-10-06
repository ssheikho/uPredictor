#include "IntegerIndicator.h"
#include "IntegerIndicatorListener.h"

void IntegerIndicator::addIIListener(IntegerIndicatorListener *iil) {
	_iil.push_back(iil);
}

void IntegerIndicator::fireUpdate() {
	for (int i = 0; i < _iil.size(); i++) _iil[i]->updateII(this);
}