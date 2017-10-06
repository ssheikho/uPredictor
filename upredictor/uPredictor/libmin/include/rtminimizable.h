#ifndef RT_MINIMIZABLE_H
#define RT_MINIMIZABLE_H

#include <minimizable.h>

class RTMinimizable : public Minimizable {
	public:
		//Allocates p, p will be deleted in runLevMarDif
		virtual void getInputParameters(double *p) = 0;
		virtual int getMaxNParam() = 0;
		virtual int getMaxNMeasurement() = 0;

		double *getInputParameters();
};

#endif
