#include "printsafetycontrols.h"

#include <iostream>

using namespace std;

PrintSafetyControls::PrintSafetyControls(
	double velFaultLimit, double velWarnLimit) : _velFaultLimit(velFaultLimit),
	_velWarnLimit(velWarnLimit) {}

PrintSafetyControls::~PrintSafetyControls() {}

void PrintSafetyControls::setVelocityLimit(double fault, double warning) {
	_velFaultLimit = fault;
	_velWarnLimit = warning;

	cout << "Velocity Fault Limit:	" << fault << endl;
	cout << "Velocity Warning Limit:	" << warning << endl;
}

double PrintSafetyControls::getVelocityFaultLimit() {
	return _velFaultLimit;
}

double PrintSafetyControls::getVelocityWarnLimit() {
	return _velWarnLimit;
}
