#ifndef PROCESSING_PARAMETERS_H
#define PROCESSING_PARAMETERS_H

#include "IndexedToggle.h"
#include "ValueListener.h"

#include <map>
#include <string>

using namespace std;

class ColorBlobParams;

class ProcessingParameters :
	public IndexedToggle
{
public:
	ProcessingParameters(
		long distanceThresh
		);

	~ProcessingParameters();

	ValueListener<long> &getDistanceThresh();
	ValueListener<long> &getLaplaceScale();
	ValueListener<double> &getGradientParam1();
	ValueListener<double> &getGradientParam2();
	ValueListener<double> &getCannyParam1();
	ValueListener<double> &getHandDepth();
	ValueListener<double> &getHandDY();
	ValueListener<double> &getHandDX();

	void updateToggle(size_t index, bool val);
	
	ValueListener<long>
		_distanceThresh
		, _laplaceScale;

	ValueListener<double>
		_gradientParam1
		, _gradientParam2
		, _cannyParam1
		, _handD
		, _handDX
		, _handDY;
};

#endif