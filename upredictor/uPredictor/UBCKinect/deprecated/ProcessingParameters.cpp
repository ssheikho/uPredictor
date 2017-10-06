#include "ProcessingParameters.h"
#include "ColorBlobParams.h"
#include "UBCUtil.h"

#include <fstream>

using namespace std;

ProcessingParameters::ProcessingParameters(
	long distanceThresh
	) :
	_distanceThresh(distanceThresh)
	, _laplaceScale(1)

	, _gradientParam1(1.0)
	, _gradientParam2(1.0)
	, _cannyParam1(1.0)
	, _handD(1.0)
	, _handDX(1.0)
	, _handDY(1.0)
{
}

ProcessingParameters::~ProcessingParameters() {}

ValueListener<long> &ProcessingParameters::getDistanceThresh() {
	return _distanceThresh;
}

ValueListener<long> &ProcessingParameters::getLaplaceScale() {
	return _laplaceScale;
}

ValueListener<double> &ProcessingParameters::getGradientParam1() {
	return _gradientParam1;
}

ValueListener<double> &ProcessingParameters::getGradientParam2() {
	return _gradientParam2;
}

ValueListener<double> &ProcessingParameters::getCannyParam1() {
	return _cannyParam1;
}

ValueListener<double> &ProcessingParameters::getHandDepth() {
	return _handD;
}

ValueListener<double> &ProcessingParameters::getHandDX() {
	return _handDX;
}

ValueListener<double> &ProcessingParameters::getHandDY() {
	return _handDY;
}

void ProcessingParameters::updateToggle(size_t index, bool val) {
	switch (index) {
	case 0:
		//_useMajorityColorChannel = val;
		break;
	case 1:
		//_renderMajColChanAsRed = val;
		break;
	case 2:
		//_renderSegmentsAsBlue = val;
		break;
	}
}