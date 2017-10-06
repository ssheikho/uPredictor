#include "KIDepthSource.h"
#include "CameraModel.h"
#include "FrameDesc.h"

#include <cuda_runtime.h>

#include <cstdlib>

KIDepthSource::KIDepthSource(
	SimplePool<KinectFrame>::PooledPtr kinectFrame
	, FrameDesc &fd
	, CameraModel &cm) :
	_kinectFrame(kinectFrame)
	, _fd(fd)
 {
    _hasColor = true;
    _hasTimestamps = true;
    _isLive = true;
    _depthWidth = fd.w;
    _depthHeight = fd.h;
    _colorWidth = fd.w;
    _colorHeight = fd.w;
    _frame = 0;
    _focalLength.x = cm._alpha;
    _focalLength.y = cm._beta;
    _principalPoint.x = cm._uZero;
    _principalPoint.y = cm._vZero;

	cudaMalloc(&_deviceDepth,_fd.w*_fd.h*sizeof(float));
}

KIDepthSource::~KIDepthSource() {}

uint KIDepthSource::getFrame() const {
	return _frame;
}

void KIDepthSource::setFrame(const uint frame) {
	abort();
}

void KIDepthSource::advance() {
	abort();
}

bool KIDepthSource::hasRadialDistortionParams() const {
	return false;
}

void KIDepthSource::processType(SimplePool<KinectFrame>::PooledPtr kinectFrame) {
	_kinectFrame = kinectFrame;
	_frame = _kinectFrame->_frameNo;
	cudaMemcpy(_deviceDepth, _kinectFrame->_depthUndistF.data
		, _fd.w*_fd.h*sizeof(float), cudaMemcpyHostToDevice);
	//cudaDeviceSynchronize();
}

void KIDepthSource::onStartup() {}

const float *KIDepthSource::getDepth() {
	return (const float *)_kinectFrame->_depthUndistF.data;
}

const float *KIDepthSource::getDeviceDepth() {
	//abort();
	return _deviceDepth;
}

const uchar3 *KIDepthSource::getColor() {
	return (uchar3 *)_kinectFrame->_depthBGRAF.data;
}
