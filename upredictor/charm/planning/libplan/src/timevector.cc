#include "timevector.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

TimeVector::TimeVector() {
	_mean = 0;
	_stdDev = 0;
	_variance = 0;
}

TimeVector::~TimeVector() {}

void TimeVector::addTime (double time) {
	_tv.push_back(time);

	_mean = ((_mean*((double)_tv.size()-1))+time)/(_tv.size());

   	double E=0;
   	for(int i=0;i<_tv.size();i++)
		E+=(_tv[i] - _mean)*(_tv[i] - _mean);
	_variance = 1/(double)_tv.size()*E;
   	_stdDev = sqrt(_variance);
}

void TimeVector::printTimes () {

   	for(int i=0;i<_tv.size();i++)
		cout<<_tv[i]<<"\n";

	cout<< "mean: "<<_mean<<"\n";
	cout<< "variance: "<<_variance<<"\n";
	cout<< "std dev: "<<_stdDev<<"\n";
}

double TimeVector::getMean() {
	return _mean;
}

double TimeVector::getStdDev() {
	return _stdDev;
}

double TimeVector::getVariance() {
	return _variance;
}

int TimeVector::getSize() {
	return _tv.size();
}

void TimeVector::saveTimeData(ofstream &outfile) {
	int nElem = _tv.size();
	outfile.write((char *)&nElem, sizeof(nElem));
	for(int i = 0; i < nElem; i++) {
		outfile.write((char *)&_tv[i], sizeof(_tv[i]));
	}
}

void TimeVector::loadTimeData(ifstream &infile) {
	int nElem = 0;//_tv.size();
	infile.read((char *)&nElem, sizeof(nElem));
	for(int i = 0; i < nElem; i++) {
		double inVal;
		infile.read((char *)&inVal, sizeof(inVal));
		_tv.push_back(inVal);
	}

	recompute();
}

void TimeVector::recompute() {
	_mean = 0.0;
	for(int i = 0; i < _tv.size(); i++) {
		_mean += _tv[i];
	}
	_mean /= (double)_tv.size();

   	double E=0.0;
   	for(int i=0;i<_tv.size();i++)
		E+=(_tv[i] - _mean)*(_tv[i] - _mean);
	_variance = 1/(double)_tv.size()*E;
   	_stdDev = sqrt(_variance);
}
