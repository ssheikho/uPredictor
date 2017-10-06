#ifndef MINIMIZABLE_H
#define MINIMIZABLE_H

class Minimizable {
	public:	
		virtual double computeMeasurement(int index, double *p) = 0;

		//Allocates p, p will be deleted in runLevMarDif
		virtual double *getInputParameters() = 0;
		virtual double *getMeasurementVector() = 0;
		virtual void setOutputParameters(double *p) = 0;
		virtual int getNParam() = 0;
		virtual int getNMeasurement() = 0;
};

#endif
