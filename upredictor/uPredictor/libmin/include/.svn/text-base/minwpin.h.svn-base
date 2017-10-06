#ifndef MIN_W_PIN_H
#define MIN_W_PIN_H

#include "minimizable.h"

//JWH Note, this is highly imperfect
class MinWPin : public Minimizable {
	public:
		MinWPin(Minimizable &min);
		~MinWPin();

		void clearPins();
		void setAllPins();
		void pin(int index);
		void unpin(int index);

		double computeMeasurement(int index, double *p);

		double *getInputParameters();
		double *getMeasurementVector();
		void setOutputParameters(double *p);
		int getNParam();
		int getNMeasurement();

	protected:
		Minimizable &_min;
		bool *_pinned;
		int _nPinned;
		double *_p;
};

#endif
