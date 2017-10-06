#ifndef VIDEO_RECORDER_H
#define VIDEO_RECORDER_H

#include "KinectFrame.h"
#include "TypeRecipient.h"

#include <opencv2/opencv.hpp>

class VideoRecorder : public TypeRecipient<cv::Mat>
{
public:
	VideoRecorder(wstring fileName, FrameDesc &fd);
	~VideoRecorder();

	cv::VideoWriter getVideoWriter();
	void processType(cv::Mat t);
	void onStartup();

protected:
	cv::VideoWriter _vw;
};

#endif