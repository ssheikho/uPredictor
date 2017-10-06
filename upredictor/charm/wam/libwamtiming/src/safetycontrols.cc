#include "safetycontrols.h"

//#include <iostream>
#include <sstream>

SafetyControls::SafetyControls() {}
SafetyControls::~SafetyControls() {}

string SafetyControls::getVelocityFaultLimitString() {
	ostringstream ss;
	ss << getVelocityFaultLimitString();
	return ss.str();
}

string SafetyControls::getVelocityWarnLimitString() {
	ostringstream ss;
	ss << getVelocityWarnLimitString();
	return ss.str();
}
