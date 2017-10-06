#include "minwpin.h"
#include <cstdlib>
#include <iostream>

using namespace std;

MinWPin::MinWPin(Minimizable &min) : _min(min),
	_pinned(new bool[_min.getNParam()]), _nPinned(0),
	_p(new double[_min.getNParam()]) {
	clearPins();
}

MinWPin::~MinWPin() {
	delete []_pinned;
}

void MinWPin::clearPins() {
	for(int i = 0; i < _min.getNParam(); i++) _pinned[i] = false;
	_nPinned = 0;
}

void MinWPin::setAllPins() {
	_nPinned = _min.getNParam();
	for(int i = 0; i < _nPinned; i++) _pinned[i] = true;
}

void MinWPin::pin(int index) {
	_pinned[index] = true;
	_nPinned++;
}

void MinWPin::unpin(int index) {
	_pinned[index] = false;
	_nPinned--;
}

double MinWPin::computeMeasurement(int index, double *p) {
	if(index == 0) setOutputParameters(p);
	double meas = _min.computeMeasurement(index, _p);
	//cout << "MinWPin::computeMeasurement[:" << index << "]:	" << meas <<
	//	"	" << getNMeasurement() << endl;
	return meas;
}

double *MinWPin::getInputParameters() {
	delete _p;
	_p = _min.getInputParameters();

	double *p = new double[getNParam()];
	int ctr = 0;
	for(int i = 0; i < _min.getNParam(); i++)
		if(!_pinned[i]) p[ctr++] = _p[i];

	//cout << "MinWPin::getInputParameters:	" << endl;
	//for(int i = 0; i < 6; i++)
	//	cout << "	p[" << i << "]:	" << p[i] << endl;

	return p;
}

double *MinWPin::getMeasurementVector() {
	return NULL;
}

void MinWPin::setOutputParameters(double *p) {
	//cout << "MinWPin::setOutputParameters:	" << endl;
	//for(int i = 0; i < 6; i++)
	//	cout << "	p[" << i << "]:	" << p[i] << endl;

	int ctr = 0;
	for(int i = 0; i < _min.getNParam(); i++)
		if(!_pinned[i]) _p[i] = p[ctr++];

	_min.setOutputParameters(_p);
}

int MinWPin::getNParam() {
	int nParam = _min.getNParam() - _nPinned;
	//cout << "MinWPin::getNParam():	" << nParam << endl;
	return nParam;
}

int MinWPin::getNMeasurement() {
	return _min.getNMeasurement();
}
