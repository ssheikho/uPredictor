#define _EXPORTING
#include "UBCSimpleGeometry.h"

#include <math.h>

double spheredist(CameraSpacePoint *p, double x, double y, double z, double r) {
	double xx = x - p->X;
	double yy = y - p->Y;
	double zz = z - p->Z;

	return fabs(sqrt(xx * xx + yy * yy + zz * zz) - r);
}

double dist(struct UBCSphere *s, double x, double y, double z) {
	double xx = x - s->_x;
	double yy = y - s->_y;
	double zz = z - s->_z;

	return fabs(sqrt(xx * xx + yy * yy + zz * zz) - s->_r);
}