#include "SphereDetectorInfo.h"

SphereDetectorInfo::SphereDetectorInfo(FrameDesc &depthFD) :
	_depthSegImg(depthFD.h, depthFD.w, CV_8UC3)
	, _depthSegMap(new int[depthFD.h * depthFD.w])
	, _pts3D(NULL)
{}

SphereDetectorInfo::~SphereDetectorInfo() {
	delete[] _depthSegMap;
}

void SphereDetectorInfo::update(GridParams gp, CameraSpacePoint *pts3D) {
	_gp = gp;
	if(_pts3D) delete [] _pts3D;
	_pts3D = new CameraSpacePoint[gp._nGridCells];
	memcpy(_pts3D, pts3D, sizeof(CameraSpacePoint) * gp._nGridCells);
}

GridParams &SphereDetectorInfo::getGP() {
	return _gp;
}

CameraSpacePoint *SphereDetectorInfo::getCenters() {
	return _pts3D;
}