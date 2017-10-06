#ifndef UBC_SIMPLE_GEOMETRY_H
#define UBC_SIMPLE_GEOMETRY_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#include <Windows.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif

struct UBCSphere {
	double _x, _y, _z, _r, _alpha;
};

double spheredist(CameraSpacePoint *p, double x, double y, double z, double r);
double dist(struct UBCSphere *s, double x, double y, double z);

	
#endif
