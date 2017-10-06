#include "CameraModel.h"
#include "FrameDesc.h"

#include <iostream>

using namespace std;

CameraModel::CameraModel(
	libfreenect2::Freenect2Device::IrCameraParams *params
	, FrameDesc &fd)
{
	update(params, fd);
}

CameraModel::~CameraModel() {}

void CameraModel::update(libfreenect2::Freenect2Device::IrCameraParams *params
	, FrameDesc &fd) {
	_uZero = params->cx;
	_vZero = params->cy;
	_alpha = params->fx;
	_beta = params->fy;
	_gamma = 0.0;
	_width = fd.w;
	_height = fd.h;

	cout << "Alpha:	" << _alpha << endl;
	cout << "Beta:	" << _beta << endl;

	for(int i = 0; i <5; i++)	_distortion[i] = 0.0f;
}
