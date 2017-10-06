#include "SphereDescription.h"

SphereDescription::SphereDescription(
	double cx
	, double cy
	, double cz
	, double rad
	, int nPts) :
	_cX(cx)
	, _cY(cy)
	, _cZ(cz)
	, _rad(rad)
	, _nPts(nPts)
{}

SphereDescription::~SphereDescription() {}