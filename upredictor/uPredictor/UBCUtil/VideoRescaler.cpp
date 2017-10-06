#include "VideoRescaler.h"

VideoRescaler::VideoRescaler(int destW, int destH) :
	_out(destH, destW, CV_8UC3)
{}

VideoRescaler::~VideoRescaler() {}

void VideoRescaler::processType(const cv::Mat t) {
	cv::resize(t, _out, cv::Size(_out.cols, _out.rows));
	fireUpdate(_out);
}