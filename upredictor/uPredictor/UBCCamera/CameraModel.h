#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "libfreenect2/libfreenect2.hpp"

struct FrameDesc;

class CameraModel {
public:
	CameraModel(libfreenect2::Freenect2Device::IrCameraParams *params
		, FrameDesc &fd);
	~CameraModel();

	void update(libfreenect2::Freenect2Device::IrCameraParams *params
		, FrameDesc &fd);

	float _uZero, _vZero, _alpha, _beta, _gamma, _distortion[5];
	unsigned int _width, _height;
};

#endif
