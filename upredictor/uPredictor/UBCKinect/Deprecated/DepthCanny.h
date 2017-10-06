#ifndef DEPTH_CANNY_H
#define DEPTH_CANNY_H

#define NOMINMAX

#include <WinSock2.h>
#include <Kinect.h>

#include <opencv/cv.h>

class DepthCanny {
public:
	DepthCanny(
		cv::Mat &depthD
		, cv::Mat &depthThresh
		, cv::Mat &depthBGR
		);
	~DepthCanny();

	void doCanny(float upperThresh);

protected:
	cv::Mat
		&_depthD
		, &_depthThresh
		, &_depthBGR
		, _depthBlurred
		, _depthBlurredGrey
		, _sobelX, _sobelY
		, _slope
		, _sum
		, _prodX, _prodY
		, _returnImg;
};

#endif