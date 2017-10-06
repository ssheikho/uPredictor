#ifndef SAFETY_CONTROLS_H
#define SAFETY_CONTROLS_H

#include <string>

using namespace std;

class SafetyControls {
	public:
		SafetyControls();
		~SafetyControls();

		virtual void setVelocityLimit(double fault, double warning) = 0;
		virtual double getVelocityFaultLimit() = 0;
		virtual double getVelocityWarnLimit() = 0;

		string getVelocityFaultLimitString();
		string getVelocityWarnLimitString();
};

#endif
