#ifndef THREE_D_BB_H
#define THREE_D_BB_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif


class ThreeDBB {
public:
	ThreeDBB();
	ThreeDBB(int *segments, CameraSpacePoint *pts, size_t nPts, int seg);

	~ThreeDBB();

	void update(int *segments, CameraSpacePoint *pts, size_t nPts, int seg);

	double 
		_minX3DBound, _maxX3DBound
		, _minY3DBound, _maxY3DBound
		, _minZ3DBound, _maxZ3DBound
		, _minX3D, _maxX3D, _minY3D, _maxY3D, _minZ3D, _maxZ3D;
};

#endif
