#include "KinectFrame.h"
#include "FrameDesc.h"
//#include "ProcessingParameters.h"
#include "UBCUtil.h"

#include <opencv2/highgui/highgui.hpp>

#ifdef _WIN32
#include <opencv2/imgproc.hpp>
#elif __linux__
#include <opencv2/imgproc/imgproc.hpp>
#endif

#include <queue>
#include <vector>

KinectFrame::KinectFrame(
	FrameDesc &bgraFD
	, FrameDesc &depthFD
	, TrackIDManager &tidm
	, libfreenect2::Registration &frereg
	) :
	_frereg(frereg)

	, _depthF(512, 424, 4)			, _bgraF(bgraFD.w, bgraFD.h,  4)
	, _depthUndistF(512, 424, 4)	, _depthBGRAF(512, 424, 4)

	//, _depthUndist(depthFD.h, depthFD.w, CV_8UC4, _depthUndistF.data)
	, _bgra(bgraFD.h, bgraFD.w, CV_8UC4, _bgraF.data)
	, _rgba(bgraFD.h, bgraFD.w, CV_8UC4)
	, _rgb(bgraFD.h, bgraFD.w, CV_8UC3)
	, _depthBGRA(depthFD.h, depthFD.w, CV_8UC4, _depthBGRAF.data)
	, _depthRGBA(depthFD.h, depthFD.w, CV_8UC4)
	, _depthRGB(depthFD.h, depthFD.w, CV_8UC3)

	, _sdi(depthFD)
	, _pts(depthFD.h * depthFD.w

	, _frereg

	, depthFD, _depthRGB, _depthUndistF)

	, _c(255.0, 255.0, 255.0)
{
	_hdBGRAImgs[KF_HD_BGRA] = &_bgra;
	_hdRGBAImgs[KF_HD_RGBA] = &_rgba;
	_hdRGBImgs[KF_HD_RGB] = &_rgb;

	_depthBGRAImgs[KF_DEPTH_COLOR_BGRA] = &_depthBGRA;
	_depthRGBImgs[KF_DEPTH_COLOR_RGB] = &_depthRGB;
	_depthRGBImgs[KF_DEPTH_SEGS_RGB] = &_sdi._depthSegImg;
}

KinectFrame::~KinectFrame() {}

void KinectFrame::clear() {
	_boxes.clear();
	_spheres.clear();
}

void KinectFrame::convertHDBGRAToRGBA() {
	cv::cvtColor(_bgra, _rgba, CV_BGRA2RGBA);
}

void KinectFrame::convertHDBGRAToRGB() {
	cv::cvtColor(_bgra, _rgb, CV_BGRA2RGB);
}

void KinectFrame::convertRegBGRAToRGBA() {
	cv::cvtColor(_depthBGRA, _depthRGBA, CV_BGRA2RGBA);
}

void KinectFrame::convertRegBGRAToRGB() {
	cv::cvtColor(_depthBGRA, _depthRGB, CV_BGRA2RGB);
}

void KinectFrame::computeRegistration() {
	_frereg.apply(&_bgraF, &_depthF, &_depthUndistF, &_depthBGRAF);
}

void KinectFrame::computeDepthCameraSpacePts() {
	_pts.computeDepthCameraSpacePts();
}

void KinectFrame::undistortDepth() {
	_frereg.undistortDepth(&_depthF, &_depthUndistF);
}

ArrayPt3DCollection &KinectFrame::getRegisteredPts() {
	return _pts;
}

cv::Mat &KinectFrame::getImageChannel(size_t source, size_t which) {
	cv::Mat *retVal = NULL;
	switch (source) {
	case KF_SOURCE_HD_BGRA:
		retVal = _hdBGRAImgs[which];
		break;
	case KF_SOURCE_HD_RGBA:
		retVal = _hdRGBAImgs[which];
		break;
	case KF_SOURCE_HD_RGB:
		retVal = _hdRGBImgs[which];
		break;
	case KF_SOURCE_DEPTH_BGRA:
		retVal = _depthBGRAImgs[which];
		break;
	case KF_SOURCE_DEPTH_RGBA:
		retVal = _depthRGBAImgs[which];
		break;
	case KF_SOURCE_DEPTH_RGB:
		retVal = _depthRGBImgs[which];
		break;
	}
	return *retVal;
}
