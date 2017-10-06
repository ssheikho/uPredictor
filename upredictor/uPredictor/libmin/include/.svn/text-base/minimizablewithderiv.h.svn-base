#ifndef MINIMIZABLEWITHDERIV_H
#define MINIMIZABLEWITHDERIV_H

#include "minimizable.h"

class MinimizableWithDeriv : public Minimizable {
	public:
		//DRG	This function is called with i as the index of the parameter
		//	and j as the index into the measurement vector.
		virtual double computeDerivative(int i, int j, double *p) = 0;
};

#endif

