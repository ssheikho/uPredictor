#include "DepthCanny.h"
#include "UBCUtil.h"

#include <opencv2/imgproc.hpp>

//http://aishack.in/tutorials/implementing-canny-edges-scratch/

DepthCanny::DepthCanny(
	cv::Mat &depthD
	, cv::Mat &depthThresh
	, cv::Mat &depthBGR
	) :
	_depthD(depthD)
	, _depthThresh(depthThresh)
	, _depthBGR(depthBGR)
	, _depthBlurred(_depthD.rows, _depthD.cols, CV_32FC1)
	, _depthBlurredGrey(_depthD.rows, _depthD.cols, CV_32FC1)
	, _sobelX(_depthD.rows, _depthD.cols, CV_32FC1)
	, _sobelY(_depthD.rows, _depthD.cols, CV_32FC1)
	, _slope(_depthD.rows, _depthD.cols, CV_32FC1)
	, _sum(_depthD.rows, _depthD.cols, CV_32FC1)
	, _returnImg(_depthD.rows, _depthD.cols, CV_32FC1) {}

DepthCanny::~DepthCanny() {}

void DepthCanny::doCanny(float upperThresh) {
	double min, max;
	cv::GaussianBlur(_depthThresh, _depthBlurred, cv::Size(5, 5), 1.4);
	cv::Sobel(_depthBlurred, _sobelX, CV_32FC1, 1, 0);
	cv::Sobel(_depthBlurred, _sobelY, CV_32FC1, 0, 1);
	cv::divide(_sobelY, _sobelX, _slope);
	cv::multiply(_sobelX, _sobelX, _prodX);
	cv::multiply(_sobelY, _sobelY, _prodY);
	_sum = _prodX + _prodY;
	cv::sqrt(_sum, _sum);

	_returnImg.setTo(cv::Scalar(0));

	cv::minMaxLoc(_sum, &min, &max);
	depthToGray(_sum, _depthBlurredGrey, _depthBGR, max);
}