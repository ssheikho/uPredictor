#ifndef SPHERE_DESCRIPTION_H
#define SPHERE_DESCRIPTION_H

#include "ValueListener.h"

class SphereDescription {
public:
	SphereDescription(
		double cx = -1.0
		, double cy = 1.0
		, double cz = 10.0
		, double rad = 10
		, int nPts = 1000);
	~SphereDescription();

	ValueListener<double> _cX, _cY, _cZ, _rad;
	ValueListener<long> _nPts;
};

#endif