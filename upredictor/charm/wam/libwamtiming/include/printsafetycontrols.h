#ifndef PRINT_SAFETY_CONTROLS_H
#define PRINT_SAFETY_CONTROLS_H

#include "safetycontrols.h"

class PrintSafetyControls : public SafetyControls {
	public:
		PrintSafetyControls(double velFaultLimit, double velWarnLimit);
		~PrintSafetyControls();

		void setVelocityLimit(double fault, double warning);
		double getVelocityFaultLimit();
		double getVelocityWarnLimit();

	protected:
		double _velFaultLimit, _velWarnLimit;
};

#endif
