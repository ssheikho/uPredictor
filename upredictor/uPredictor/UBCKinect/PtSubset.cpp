#include "PtSubset.h"

#include <iostream>

PtSubset::PtSubset(int maxPts, int segment, size_t source, size_t which) 
	: 
	_segment(segment)
	, _source(source)
	, _which(which)
	, _cameraSpacePoints(new CameraSpacePoint[maxPts])
	, _rgb(new unsigned char[maxPts * 3])
{}

PtSubset::~PtSubset() {
	delete[] _cameraSpacePoints;
	delete[] _rgb;
}

void PtSubset::processType(SimplePool<KinectFrame>::PooledPtr t) {
	int nPts = t->_pts.getNPts();
	CameraSpacePoint *pts = t->_pts.getCameraPts();
	int *dsm = t->_sdi._depthSegMap;
	cv::Mat &rgb = t->getImageChannel(_source, _which);
	_ct = 0;
	for(int i = 0; i < nPts; i++) {
		if(dsm[i] == _segment) {
			_cameraSpacePoints[_ct] = pts[i];
			_rgb[_ct * 3] = rgb.data[i * 3];
			_rgb[_ct * 3 + 1] = rgb.data[i * 3 + 1];
			_rgb[_ct * 3 + 2] = rgb.data[i * 3 + 2];
			_ct++;
		}
	}

	TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::fireUpdate(t);
	TypeBroadcaster<Pt3DCollection *>::fireUpdate(this);
}

int PtSubset::getNPts() {
	return _ct;
}

CameraSpacePoint *PtSubset::getCameraPt(int index) {
	return &_cameraSpacePoints[index];
}

CameraSpacePoint *PtSubset::getCameraPts() {
	return _cameraSpacePoints;
}

unsigned char *PtSubset::getRGB() {
	return _rgb;
}
