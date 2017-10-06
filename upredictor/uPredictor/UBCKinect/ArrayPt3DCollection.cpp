#include "ArrayPt3DCollection.h"
#include "Point3DRGB.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

ArrayPt3DCollection::ArrayPt3DCollection(
	int maxPts
	#ifdef _WIN32
	, ICoordinateMapper &cm
	#elif __linux__
	, libfreenect2::Registration &reg
	#endif
	, FrameDesc &depthFD
	, cv::Mat &depthRGB
	, libfreenect2::Frame &depthUndistF) :
	_maxPts(maxPts)
	, _nPts(_maxPts)
	#ifdef _WIN32
	, _cm(cm)
	#elif __linux__
	, _reg(reg)
	#endif
	, _depthFD(depthFD)
	, _cameraSpacePoints(new CameraSpacePoint[_maxPts])
	, _depthRGB(depthRGB)
	, _depthUndistF(depthUndistF)
{}

ArrayPt3DCollection::~ArrayPt3DCollection() {
	delete[] _cameraSpacePoints;
}

void ArrayPt3DCollection::computeDepthCameraSpacePts() {
	#ifdef _WIN32
		_cm.MapDepthFrameToCameraSpace(
			_maxPts, depthData,
			_maxPts, _cameraSpacePoints);
	#elif __linux__
		_reg.getPointsXYZ((float *)_depthUndistF.data, _cameraSpacePoints
			, _depthFD.h, _depthFD.w);
	#endif
}

int ArrayPt3DCollection::getNPts() {
	return _nPts;
}

int ArrayPt3DCollection::getMaxPts() {
	return _maxPts;
}

void ArrayPt3DCollection::setCameraPt(int index, CameraSpacePoint setVal) {
	_cameraSpacePoints[index] = setVal;
}

CameraSpacePoint *ArrayPt3DCollection::getCameraPt(int index) {
	return &_cameraSpacePoints[index];
}

CameraSpacePoint *ArrayPt3DCollection::getCameraPts() {
	return _cameraSpacePoints;
}

unsigned char *ArrayPt3DCollection::getRGB() {
	return (unsigned char*)_depthRGB.data;
}

cv::Mat &ArrayPt3DCollection::getBGRImage() {
	return _depthRGB;
}

void ArrayPt3DCollection::clear() {
	_nPts = 0;
}
