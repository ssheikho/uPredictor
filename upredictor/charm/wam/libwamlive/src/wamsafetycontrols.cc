#include "wamsafetycontrols.h"

WAMSafetyControls::WAMSafetyControls(SafetyModule *sm) : _sm(sm) {
	setVelocityLimit();
}

WAMSafetyControls::~WAMSafetyControls() {}

void WAMSafetyControls::setVelocityLimit(double fault, double warning) {
	_sm->setVelocityLimit(_velFault = fault, _velWarn = warning);
}

double WAMSafetyControls::getVelocityFaultLimit()	{	return _velFault;	}
double WAMSafetyControls::getVelocityWarnLimit() 	{	return _velWarn;	}
