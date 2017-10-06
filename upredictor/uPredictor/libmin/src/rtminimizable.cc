#include "rtminimizable.h"

double *RTMinimizable::getInputParameters() {
	double *p = new double[getNParam()];
	getInputParameters(p);
	return p;
}
