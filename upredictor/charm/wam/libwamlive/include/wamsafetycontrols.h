#ifndef WAM_SAFETY_CONTROLS_H
#define WAM_SAFETY_CONTROLS_H

#include "safetycontrols.h"
#include <barrett/products/safety_module.h>

using namespace barrett;

class WAMSafetyControls : public SafetyControls {
	public:
		WAMSafetyControls(SafetyModule *sm);
		~WAMSafetyControls();

		void setVelocityLimit(double fault = 6.0, double warning = -1.0);
		double getVelocityFaultLimit();
		double getVelocityWarnLimit();

	protected:
		SafetyModule *_sm;
		double _velFault, _velWarn;
};

#endif
